all:sync async main

sync:sync.cc
	g++ -std=c++17 $^ -o $@ -lpthread -lspdlog

async:async.cc
	g++ -std=c++17 $^ -o $@ -lpthread -lspdlog

main:main.cc
	g++ -std=c++17 $^ -o $@ -lpthread -lgflags

clean:
	rm -f sync async main