all:
	g++ src/main.cpp src/binpol.cpp -o LR13
test:
	g++ tests/test.cpp src/binpol.cpp -pthread -lgtest -o RunTests
UI:
	g++ -x c++ src/main.cpp src/UI.cpp src/binpol.cpp ../UI/UI.h -o LR13
