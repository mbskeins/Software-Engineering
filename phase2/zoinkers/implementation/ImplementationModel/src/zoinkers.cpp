#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "zoinkers.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main() {
	

	testing testClient;
	bool login = testClient.logIn();

	if (login == true) {
	
		testClient.systemStart();
	
	}
	else {}

	//zoinkers mainSystem;
	//mainSystem.systemStart();
	cout << "Now exiting the system" << endl;

	system("PAUSE");
	return 0;
}


