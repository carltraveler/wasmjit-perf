#![cfg_attr(
    feature = "cargo-clippy",
    allow(clippy::missing_safety_doc, clippy::new_without_default)
)]

use cranelift_wasm::DefinedMemoryIndex;
use ontio_wasmjit::chain_api::{ChainCtx, ChainResolver};
use ontio_wasmjit::error::Error as JITError;
use ontio_wasmjit::executor::build_module;
pub use ontio_wasmjit::resolver::Resolver;
use ontio_wasmjit_environ::BuildOption;
use ontio_wasmjit_runtime::{ExecMetrics, VMContext, VMFunctionBody, VMFunctionImport};
use std::fs::File;
use std::io::Read;
use std::panic;
use std::time::SystemTime;
pub use wasmjit_capi::{
    bytes_from_vec, bytes_null, bytes_to_boxed_slice, wasmjit_bytes_t, wasmjit_chain_context_t,
    wasmjit_instance_destroy, wasmjit_instance_invoke, wasmjit_instantiate, wasmjit_resolver_t,
    wasmjit_result_err_trap, wasmjit_result_success, wasmjit_result_t, wasmjit_slice_t,
};

pub fn read_wasm_file(fpath_str: &str) -> Vec<u8> {
    let mut file = File::open(&fpath_str).expect("couldn't open");
    let mut s = Vec::new();
    file.read_to_end(&mut s).expect("read file error");
    s
}
#[no_mangle]
pub unsafe extern "C" fn ontio_debug(vmctx: *mut VMContext, input_ptr: u32, ptr_len: u32) {
    panic::catch_unwind(|| {
        let instance = (&mut *vmctx).instance();
        let memory = instance
            .memory_slice_mut(DefinedMemoryIndex::from_u32(0))
            .unwrap();
        let start = input_ptr as usize;
        let end = start
            .checked_add(ptr_len as usize)
            .expect("out of memory bound");
        let msg = String::from_utf8_lossy(&memory[start..end]).to_string();
        println!("{:?}", msg)
    })
    .unwrap_or_else(|e| {
        // here just for test
        panic!(e)
    });
}
pub struct TestChainResolver {
    inner: ChainResolver,
}

impl TestChainResolver {
    pub fn new() -> Self {
        let cr = ChainResolver;
        Self { inner: cr }
    }
}

impl Resolver for TestChainResolver {
    fn resolve(&mut self, module: &str, field: &str) -> Option<VMFunctionImport> {
        match field {
            "ontio_debug" => Some(VMFunctionImport {
                body: ontio_debug as *const VMFunctionBody,
            }),
            _ => self.inner.resolve(module, field),
        }
    }
}

pub fn call_invoke(name: &str, chain: ChainCtx) -> Result<(), JITError> {
    let wasm = read_wasm_file(name);
    let start0 = SystemTime::now();
    let module = build_module(&wasm, BuildOption::new().gas_metering(false)).unwrap();
    println!(
        "compiler time: {:?}",
        SystemTime::now().duration_since(start0).unwrap()
    );
    //println!("compiler elapsed : {:?}", start0.elapsed().unwrap());

    let mut resolver = TestChainResolver::new();
    let mut instance = module.instantiate(&mut resolver).unwrap();

    let start = SystemTime::now();
    instance.invoke(Box::new(chain)).unwrap();
    println!(
        "run time: {:?}",
        SystemTime::now().duration_since(start).unwrap(),
    );
    //println!("run elapsed : {:?}", start.elapsed().unwrap());
    Ok(())
}

fn make_chain() -> ChainCtx {
    let exec_metrics = ExecMetrics::new(u64::max_value(), 1, 10000, 100_000_u64);
    ChainCtx::new(
        1,
        1u32,
        [1u8; 32],
        [1u8; 32],
        Vec::new(),
        Vec::new(),
        Vec::new(),
        exec_metrics,
        0,
    )
}

fn main() {
    call_invoke("test.wasm", make_chain()).unwrap();
}
