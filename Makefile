server:
	mkdir -p build
	ghc -optl-static -dynamic calc.hs -odir build -hidir build
	clang++ -c server.cpp -std=c++17 -Wall -Wextra -Werror -o build/server.o -I`ghc --print-libdir`/include
	ghc -dynamic -no-hs-main -o build/server build/server.o build/MyModule.o -lpthread -lboost_system -lstdc++


client:
	mkdir -p build
	clang++ client.cpp -std=c++17 -Wall -Wextra -Werror -o build/client -lpthread -lboost_system


all:
	client
	server


.PHONY: clean
clean:
	rm -rf build
	rm -rf *_stub.h
