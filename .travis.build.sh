#!/bin/bash
set -e
set -x

cargo build --release

cp target/release/wasmjit-perf perfcontract/
bash compile.bash eosvm_jit.cpp perfcontract/
cd perfcontract/

./wasmjit-perf.bash re
./wasmjit-perf.bash sha256
./wasmjit-perf.bash md5
./wasmjit-perf.bash des

./eosvm_jit re
./eosvm_jit sha256
./eosvm_jit md5
./eosvm_jit des
