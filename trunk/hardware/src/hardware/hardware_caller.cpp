/*
 * hardware_caller.cpp
 *
 *  Created on: 2010-5-18
 *      Author: spaceflyer
 */

#include "../include/lock.h"
#include "../include/hardware.h"
#include "../include/crypto.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//const char
//		* OPHELP =
//				"\
//make\t:\tmake a new hardware.\n\
//getpub\t:\tget public key. The public key will be written to the input file.\n\
//reg\t:\tregister a new user. The time result will be written to the input file.\n\
//update\t:\tupdate user entry. The time result will be written to the input file.\n\
//request\t:\tget updated entries for one update request.\n\
//getind\t:\tget the index of a encrypted phone number.\n\
//\nSee doc/file.format to see detailed input and output format.\n\
//";

const int OPN = 10;
const char* OPS[] = { "makeSafeCore", "getPublicKey", "makeNewUserEntry",
		"makeUpdateUserEntry", "refreshEntries", "refreshEntry", "getIndex",
		"shiftToNextKey", "getUpdateEntry", "getCurrentCounter" };

/**
 * @return
 * 		0: success
 * 		1: bad input
 * 		2: currentCounter too large
 * 		3: failed
 */
int main(int argc, char* argv[]) {
	if (argc != 4 && argc != 3) {
		printf("Usage %s: <hardware_file> <op_type> [<input_file>]\n", argv[0]);
		return 1;
	}
	string op = argv[2];
	int opID = -1;
	for (int i = 0; i < OPN; i++)
		if (op == OPS[i])
			opID = i;

	if (opID == -1) {
		printf("Bad op: %s\n", op.c_str());
		return 1;
	}

	int res = 0;

	if (op == "makeSafeCore") {
		string codeword;
		codeword = getpass("Enter new private code:");
		int fd = getExclusiveFd(argv[1]);
		FILE* file = fdopen(fd, "wb");
		if (file == NULL) {
			printf("Failed to open file: %s\n", argv[1]);
			res = 3;
		}
		SafeCore::makeSafeCore(file, generatePrivateKey(codeword));
		fclose(file);
		close(fd);
		return 0;
	} else if (op == "shiftToNextKey") {
		int fd = getExclusiveFd(argv[1]);
		FILE* file = fdopen(fd, "rb+");
		if (file == NULL) {
			printf("Failed to open file: %s\n", argv[1]);
			res = 3;
		}
		SafeCore *core = SafeCore::loadSafeCore(file);
		core->shiftToNextKey();
		fseek(file, 0, SEEK_SET);
		core->save(file);
		fclose(file);
		close(fd);
		return 0;
	}

	if (argc != 4) {
		printf("Need 3 arguments!\n");
		return 1;
	}

	int fd = getExclusiveFd(argv[1]);
	FILE* file = fdopen(fd, "rb+");
	if (file == NULL) {
		printf("Failed to open file: %s\n", argv[1]);
		res = 3;
	}

	SafeCore *core = 0;
	if (res == 0) {
		core = SafeCore::loadSafeCore(file);
		if (core->getCurrentCounter() >= core->MAX_COUNT)
			res = 2;
	}

	int iofd = getExclusiveFd(argv[3]);
	FILE *iofile = fdopen(iofd, "rb+");
	if (iofile == NULL) {
		printf("Failed to open file: %s\n", argv[3]);
		res = 3;
	}

	if (res == 0) {
		if (op == "getPublicKey") {
			do {
				PublicKeyToTransfer key = core->getPublicKey();
				if (fwrite(&key, sizeof(key), 1, iofile) != 1) {
					printf("Write key failed.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "getCurrentCounter") {
			do {
				freopen(argv[3], "w", iofile);
				int count = core->getCurrentCounter();
				if (fprintf(iofile, "%d\n", count) < 0) {
					printf("Write count failed.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "getIndex") {
			do {
				EncryptedPhoneNumber epn;
				if (fread(&epn, sizeof(epn), 1, iofile) != 1) {
					printf("Read EncryptedPhoneNumber failed.\n");
					res = 3;
					break;
				}
				Index ind;
				if (!core->getIndex(epn, ind)) {
					res = 3;
					break;
				}
				fseek(iofile, 0, SEEK_SET);
				if (fwrite(&ind, sizeof(Index), 1, iofile) != 1) {
					printf("Write index failed.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "makeNewUserEntry") {
			do {
				bool hasOld;
				UserEntry oldEntry, inputEntry, outputEntry;
				if (fread(&hasOld, sizeof(hasOld), 1, iofile) != 1 || fread(
						&oldEntry, sizeof(oldEntry), 1, iofile) != 1 || fread(
						&inputEntry, sizeof(inputEntry), 1, iofile) != 1) {
					printf("Failed to read parameters.\n");
					res = 3;
					break;
				}
				if (!core->makeNewUserEntry(hasOld, oldEntry, inputEntry,
						outputEntry)) {
					res = 3;
					break;
				}
				fseek(iofile, 0, SEEK_SET);
				if (fwrite(&outputEntry, sizeof(outputEntry), 1, iofile) != 1) {
					printf("Failed to write result.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "makeUpdateUserEntry") {
			do {
				UserEntry oldEntry, inputEntry, outputEntry;
				if (fread(&oldEntry, sizeof(oldEntry), 1, iofile) != 1
						|| fread(&inputEntry, sizeof(inputEntry), 1, iofile)
								!= 1) {
					printf("Failed to read parameters.\n");
					res = 3;
					break;
				}
				if (!core->makeUpdateUserEntry(oldEntry, inputEntry,
						outputEntry)) {
					res = 3;
					break;
				}
				fseek(iofile, 0, SEEK_SET);
				if (fwrite(&outputEntry, sizeof(outputEntry), 1, iofile) != 1) {
					printf("Failed to write result.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "refreshEntries") {
			do {
				Index firstIndex, secondIndex;
				UserEntry firstEntry, secondEntry;
				if (fread(&firstIndex, sizeof(firstIndex), 1, iofile) != 1
						|| fread(&firstEntry, sizeof(firstEntry), 1, iofile)
								!= 1 || fread(&secondIndex,
						sizeof(secondIndex), 1, iofile) != 1 || fread(
						&secondEntry, sizeof(secondEntry), 1, iofile) != 1) {
					printf("Failed to read parameters.\n");
					res = 3;
					break;
				}
				if (!core->refreshEntries(firstIndex, firstEntry, secondIndex,
						secondEntry)){
					res = 3;
					break;
				}
				fseek(iofile, 0, SEEK_SET);
				if (fwrite(&firstIndex, sizeof(firstIndex), 1, iofile) != 1
						|| fwrite(&firstEntry, sizeof(firstEntry), 1, iofile)
								!= 1 || fwrite(&secondIndex,
						sizeof(secondIndex), 1, iofile) != 1 || fwrite(
						&secondEntry, sizeof(secondEntry), 1, iofile) != 1) {
					printf("Failed to write result.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "refreshEntry") {
			do {
				Index index;
				UserEntry entry;
				if (fread(&index, sizeof(index), 1, iofile) != 1 || fread(
						&entry, sizeof(entry), 1, iofile) != 1) {
					printf("Failed to read parameters.\n");
					res = 3;
					break;
				}
				core->refreshEntry(index, entry);
				fseek(iofile, 0, SEEK_SET);
				if (fwrite(&index, sizeof(index), 1, iofile) != 1 || fwrite(
						&entry, sizeof(entry), 1, iofile) != 1) {
					printf("Failed to write result.\n");
					res = 3;
					break;
				}
			} while (false);
		} else if (op == "getUpdateEntry") {
			do {
				UserEntry operateUser, targetUser;
				UpdateEntry resEntry;
				TimeType threshold;
				bool updated;
				if (fread(&operateUser, sizeof(operateUser), 1, iofile) != 1
						|| fread(&targetUser, sizeof(targetUser), 1, iofile)
								!= 1 || fread(&threshold, sizeof(threshold), 1,
						iofile) != 1) {
					printf("Failed to read parameters.\n");
					res = 3;
					break;
				}
				if (!core->getUpdateEntry(operateUser, targetUser, resEntry,
						threshold, updated)) {
					res = 3;
					break;
				}
				fseek(iofile, 0, SEEK_SET);
				if (fwrite(&resEntry, sizeof(resEntry), 1, iofile) != 1
						|| fwrite(&updated, sizeof(updated), 1, iofile) != 1) {
					printf("Failed to write result.\n");
					res = 3;
					break;
				}
			} while (false);
		} else
			assert(0);
	}

	if (iofile != NULL) {
		fclose(iofile);
		close(iofd);
	}
	if (core != NULL) {
		printf("Call completed, core counter = %d\n", core->getCurrentCounter());
		core->save(file);
		delete core;
	}
	if (file != NULL) {
		fclose(file);
		close(fd);
	}
	return res;
}
