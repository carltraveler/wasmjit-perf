sudo apt install g++
srcfile=$1
dir=$2
[[ "$srcfile" == "" ]] && srcfile="eosvm_jit.cpp"
[[ "$dir" == "" ]] && dir=$(pwd) || dir=$(pwd)/$2
outputfile=${dir}/${srcfile%.*}
g++ $srcfile -I eos-vm/include/ -std=gnu++17 -lpthread -o $outputfile -O3
