simdexec : ../src/*cpp
	g++ -std=c++17 $^ -o $@ -msse -mavx2 -mavx

clean : 
	rm ./simdexec
