all : put get

put : put.cc
	g++ -std=c++17 $^ -o $@ -letcd-cpp-api -lcpprest
get : get.cc
	g++ -std=c++17 $^ -o $@ -letcd-cpp-api -lcpprest
clean :
	rm -f put get