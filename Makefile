smart_flower_pot: src/main.cpp
	g++ $< -o build/$@ src/server.cpp src/device.cpp -lpistache -lcrypto -lssl -lpthread