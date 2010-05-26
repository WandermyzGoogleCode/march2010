/*
 * defineSize.cpp
 *
 *  Created on: 2010-5-26
 *      Author: spaceflyer
 */

#include "../include/data.h"
#include "../include/hardware.h"
#include <iostream>
using namespace std;

void defineSize(const char* name, int size){
	printf("\tdefine('SIZE_%s', %d);\n", name, size);
}

void define(const char* name, int value){
	printf("\tdefine('%s', %d);\n", name, value);
}

int main()
{
	printf("<?php\n");
	defineSize("Index", sizeof(Index));
	defineSize("EncryptedPhoneNumber", sizeof(EncryptedPhoneNumber));
	defineSize("UserEntry", sizeof(UserEntry));
	defineSize("UpdateEntry", sizeof(UpdateEntry));
	defineSize("UpdateRequest", sizeof(UpdateRequest));
	defineSize("UpdatePackage", sizeof(UpdatePackage));
	defineSize("PhoneNumber", sizeof(PhoneNumber));
	defineSize("TimeType", sizeof(TimeType));
	define("MAX_COUNTER", SafeCore::MAX_COUNT);
	define("MAX_NAME_LENGTH", MAX_NAME_LENGTH);
	define("MAX_STATUS_LENGTH", MAX_STATUS_LENGTH);
	define("MAX_CONNECTION", MAX_CONNECTION);
	define("MAX_REQ_NUM", MAX_REQ_NUM);
	printf("?>\n");
}
