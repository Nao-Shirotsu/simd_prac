simdexec_noopt : ../src/*cpp
	g++ -O0 -std=c++17 $^ -o $@ -msse -mavx2 -mavx

simdexec_opt3 : ../src/*cpp
	g++ -O3 -std=c++17 $^ -o $@ -msse -mavx2 -mavx

clean : 
	rm ./simdexec*
