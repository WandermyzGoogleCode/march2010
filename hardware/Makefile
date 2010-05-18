hp=src/hardware
cp=src/crypto

all: hardware test

hardware: ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/aux.cpp
	g++ -lcrypto ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/aux.cpp -o hardware -g
	
test: ${cp}/test.cpp ${cp}/aux.cpp ${cp}/crypto.cpp
	g++ -lcrypto ${cp}/test.cpp ${cp}/aux.cpp ${cp}/crypto.cpp -o test
	
clean:
	rm hardware test