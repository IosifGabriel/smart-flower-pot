smart_flower_pot: src/main.cpp
	g++ $< -o build/$@ -lpistache -lcrypto -lssl -lpthread