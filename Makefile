CXX = g++
CFLAGS = -std=c++17 -Og -g -Idependencies/include -Ldependencies/lib -lCppWebServer

all: json

json: main.cpp
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	rm *.o json