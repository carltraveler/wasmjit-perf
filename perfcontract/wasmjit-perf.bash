[[ $1 -eq "" ]] && echo "please specify a test contract file" && exit 1
cp $1 test.wasm
./wasmjit-perf
