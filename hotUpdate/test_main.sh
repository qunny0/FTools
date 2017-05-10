
g++ -c FileEncrypt.cpp -o FileEncrypt.o

g++ -g FileEncrypt.o Main.cpp -I. -o main

./main "./tmpData/Tencent/1.0/willZipResAndSrcFile/luascript" "./tmpData/Tencent/1.0/willZipResAndSrcFile/Encrypt/"
