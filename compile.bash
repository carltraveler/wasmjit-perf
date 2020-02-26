[[ $1 -eq "" ]] && srcfile="eosvm_jit.cpp" && outputfile="eosvm_jit"
g++ $srcfile -I eos-vm/include/ -std=gnu++17 -lpthread -o $outputfile -O3
