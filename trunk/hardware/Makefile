hp=src/hardware
cp=src/crypto

all: hardware_caller test caller_tester

caller_tester: ${hp}/caller_tester.cpp ${cp}/aux.cpp ${cp}/crypto.cpp
	g++ -lcrypto ${hp}/caller_tester.cpp ${cp}/aux.cpp ${cp}/crypto.cpp -o caller_tester -g

hardware_caller: ${hp}/hardware_caller.cpp ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/aux.cpp
	g++ -lcrypto ${hp}/hardware_caller.cpp ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/aux.cpp -o hardware_caller -g
	
test: ${cp}/test.cpp ${cp}/aux.cpp ${cp}/crypto.cpp
	g++ -lcrypto ${cp}/test.cpp ${cp}/aux.cpp ${cp}/crypto.cpp -o test
	
clean:
	rm hardware_caller test caller_tester