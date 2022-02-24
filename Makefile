CXX = g++
CFLAGS = -std=c++17 -Og -g -Idependencies/include -Ldependencies/lib -lCppWebServer

all: json_test

json_test: main.cpp
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	rm *.o json_test