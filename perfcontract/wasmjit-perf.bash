echo "wasmjit test file $1"
[[ $1 == "" ]] && echo "please specify a test contract file" && exit 1
cp $1 test.wasm
./wasmjit-perf
