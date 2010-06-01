hp=src/hardware
cp=src/crypto
ip=src/include

all: hardware_caller test caller_tester define vc_caller gen_key_user0

caller_tester: ${hp}/caller_tester.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp ${ip}/data.h ${ip}/crypto.h
	g++ -lcrypto ${hp}/caller_tester.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp -o caller_tester -g

hardware_caller: ${hp}/hardware_caller.cpp ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/auxi.cpp ${ip}/data.h ${ip}/crypto.h
	g++ -lcrypto ${hp}/hardware_caller.cpp ${hp}/hardware.cpp ${cp}/crypto.cpp ${cp}/auxi.cpp -o hardware_caller -g
	
test: ${cp}/test.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp ${ip}/data.h ${ip}/crypto.h
	g++ -lcrypto ${cp}/test.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp -o test
	
define: ${hp}/define.cpp ${ip}/data.h ${ip}/crypto.h
	g++ ${hp}/define.cpp -o define -g
	
vc_caller: ${cp}/vc_caller.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp
	g++ ${cp}/vc_caller.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp -lcrypto -o vc_caller
	
gen_key_user0: ${cp}/gen_key_user0.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp
	g++ -lcrypto ${cp}/gen_key_user0.cpp ${cp}/auxi.cpp ${cp}/crypto.cpp -o gen_key_user0
	
clean:
	rm hardware_caller test caller_tester define vc_caller gen_key_user0