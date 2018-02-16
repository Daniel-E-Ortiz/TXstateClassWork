-- to run:

./agent.o <ServerIP> <PORT> <"ACTION">
./server.o <PORT>

-- to compile (if necessary)

g++ -std=c++11 -o server.o server.cpp
gcc -o agent.o agent.c





Yes it needs "" for some reason...