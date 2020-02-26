#### wasmjit-perf

​	perf the  jit performance of eos-vm and ontio-wasmjit

#### usage

​	a. use `cargo build --release`  to get the ontio-wasmjit binary. copy to perfcontract directory.

​	b. bash compile.bash to compile the eos-vm jit binary. copy to perfcontract directory.

​	c. enter perfcontract directory.  run `./wasmjit-perf.bash filename` to get the run time consumed of test file. run `./eosvm_jit` to get the run time consumed of  test file.

#### license

This project is licensed under the [MIT license](LICENSE).
