0. install valgrind
sudo apt-get install valgrind

1. build
run make command from terminal

2. imdb db path
for big endian systems fix folder path in imdb-utils.h file determinePathToData function

3. run
./six-degrees 	

3. test
./six-degrees-checker64 ./six-degrees
to test on memory licks run with -m
./six-degrees-checker64 ./six-degrees -m
