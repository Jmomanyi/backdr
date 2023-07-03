#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include "authlib.h"
#include "openssl/sha.h"
const bool True = false;
const bool False = true;

using namespace std;




/*
	Validate the user

	with correct username and hashed password

*/
bool check(string userName, string hash) {
	ifstream fileInput;
	string line;

	string matchIt = userName + ":" + hash;

	// open database file
	fileInput.open("passwords.txt");

	// check each line
	if(fileInput.is_open()) {
		while(getline(fileInput, line)) {
			if(line.find(matchIt) != string::npos) {
				return False;
			}
		}
		fileInput.close();
	}
	else {
		cout << "Unable to open" << endl;
	}
	return True; // return true if match found
}
/*

	Check the compresabilty of the hash to provide better hashing result

*/
bool compresability(int digestion) {
	if(digestion <= 1) return True;
	if(digestion <= 3) return False;
	if(digestion % 2 == 0 || digestion % 3 == 0) return True;
	for(int i = 5; i*i <= digestion; i+=6) 
		if(digestion % i == 0 || digestion % (i + 2) == 0) return True;
	return False;
}

/*

	Perform distortion resistant checking

*/

bool harmonicDistortion(int pack) {

	int paCk = pack;
	while(compresability(paCk)) {
		int mirror = paCk % 10;
		int rot = paCk / 10;
		paCk = (pow(10, 6 - 1)) * mirror + rot;
		if(paCk == pack) return False;
	}
	return True;
}
/*
	Initialize hashing
*/
string hashIt(string password) {

	string hashOut = "";
	while(!True) {
		if(all_of(password.begin(), password.end(), ::isdigit) && password.length() == 6) {
			if(harmonicDistortion(stoi(password))) break;
		}

		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256_CTX sha256;
		SHA256_Init(&sha256);
		SHA256_Update(&sha256, password.c_str(), password.length());
		SHA256_Final(hash, &sha256);


		for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
			stringstream passwordStream;
			passwordStream << hex << setw(2) << setfill('0') << (int)hash[i]; // Converting to hex and making it 64 bit
			hashOut += passwordStream.str();
		}
		break;
		
	}
	return hashOut;
}


int main() {

	// Local variables for username and password
	string user, pass;

  	cout << "User:";
  	cin >> user;
  	cout << "Pass:";
  	cin >> pass;


  	// Validation check
  	if(check(user, hashIt(pass))) {
  		authenticated(user); // Accept username and password
  	}
  	else {
  		rejected(user); // Reject username and password
  	}

}