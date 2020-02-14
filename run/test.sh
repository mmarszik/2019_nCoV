rm 2019_nCoV

echo 'avx2'

g++ -O3 -std=c++14 -fprofile-generate -mavx2 -DTEST2 -DUSE_RND_WYHASH64_0 -I../vendor ../main.cpp ../vendor/MRndCPP/*.cpp ../vendor/MiscCPP/m_limits.cpp ../vendor/MxCPP/mx_array.cpp -o 2019_nCoV
./2019_nCoV
rm 2019_nCoV

g++ -O3 -std=c++14 -fprofile-use -mavx2 -DTEST2 -DUSE_RND_WYHASH64_0 -I../vendor ../main.cpp ../vendor/MRndCPP/*.cpp ../vendor/MiscCPP/m_limits.cpp ../vendor/MxCPP/mx_array.cpp -o 2019_nCoV
time ./2019_nCoV
rm 2019_nCoV

g++ -O3 -std=c++14 -mavx2 -DTEST2 -DUSE_RND_WYHASH64_0 -I../vendor ../main.cpp ../vendor/MRndCPP/*.cpp ../vendor/MiscCPP/m_limits.cpp ../vendor/MxCPP/mx_array.cpp -o 2019_nCoV
time ./2019_nCoV
rm 2019_nCoV



echo 'no avx2'

g++ -O3 -std=c++14 -fprofile-generate -DTEST1 -DUSE_RND_WYHASH64_0 -I../vendor ../main.cpp ../vendor/MRndCPP/*.cpp ../vendor/MiscCPP/m_limits.cpp ../vendor/MxCPP/mx_array.cpp -o 2019_nCoV
./2019_nCoV
rm 2019_nCoV

g++ -O3 -std=c++14 -fprofile-use -DTEST1 -DUSE_RND_WYHASH64_0 -I../vendor ../main.cpp ../vendor/MRndCPP/*.cpp ../vendor/MiscCPP/m_limits.cpp ../vendor/MxCPP/mx_array.cpp -o 2019_nCoV
time ./2019_nCoV
rm 2019_nCoV

g++ -O3 -std=c++14 -DTEST1 -DUSE_RND_WYHASH64_0 -I../vendor ../main.cpp ../vendor/MRndCPP/*.cpp ../vendor/MiscCPP/m_limits.cpp ../vendor/MxCPP/mx_array.cpp -o 2019_nCoV
time ./2019_nCoV
rm 2019_nCoV



