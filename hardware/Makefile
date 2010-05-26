hp=src/hardware
cp=src/crypto
ip=src/include

all: hardware_caller test caller_tester define

caller_tester: ${hp}/caller_tester.cpp ${cp}/aux.cpp ${cp}/crypto.cpp ${ip}/data.h ${ip}/crypto.h
	g++ -lcrypto ${hp}/caller_tester.cpp ${cp}/aux.cpp ${cp}/crypto.cpp -o caller_tester -g

hardware_caller: ${hp}/hardware_caller.cpp ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/aux.cpp ${ip}/data.h ${ip}/crypto.h
	g++ -lcrypto ${hp}/hardware_caller.cpp ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/aux.cpp -o hardware_caller -g
	
test: ${cp}/test.cpp ${cp}/aux.cpp ${cp}/crypto.cpp ${ip}/data.h ${ip}/crypto.h
	g++ -lcrypto ${cp}/test.cpp ${cp}/aux.cpp ${cp}/crypto.cpp -o test
	
define: ${hp}/define.cpp ${ip}/data.h ${ip}/crypto.h
	g++ ${hp}/define.cpp -o define -g
	
clean:
	rm hardware_caller test caller_tester define