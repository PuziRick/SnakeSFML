mkdir _build
cd _build

cmake -G "MinGW Makefiles" ..
cmake --build .

cd tests
.\TestApp.exe