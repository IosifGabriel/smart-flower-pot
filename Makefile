smart_flower_pot: src/main.cpp
	g++ $< -o build/$@ src/server.cpp -lpistache -lcrypto -lssl -lpthread