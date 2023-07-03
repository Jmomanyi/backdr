#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

#include <string.h>
#include "authlib.h"
#include "login.h"
#include <openssl/sha.h>

using namespace std;



string sha256(const string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();
}

// @param  string name - username of person attempting to login
// @return string      - hashed password of $name from password file if match found. Returns empty string if no match
string readIn(string name) {
	string user, pass, line;					//Initialising strings
	ifstream inFile;						//Initalise file stream
	inFile.open("passwords.txt");					//Opens password database file
	if (inFile.is_open()) {						//Check file is open
		while (getline(inFile, line)) {				//While line is not empty
			user = line.substr(0, line.find(":"));		//Set user to text before the delimeter ":"
			pass = line.substr(line.find(":") + 1);		//Set pass to text after the delimeter ":"
			if (user == name) {				//If user is equal to name
				return pass;				//Return hashed password of user
			}
		}
	}
	return "";
}

//woid
//ref[1]
void vo1d(string str) {
	const char aaaaaa[37] = { 'x', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' }; //intialise aaaaaa
    const string aaa[37] = { "     ", "- ", " ---", " - -", " --", "-", "-- -", "  -", "----", "--", "-   ", " - ", "- --",  "  ", " -", "   ", "-  -", "  - ", "- -", "---", "_", "-- ", "--- ", "-  ", "     ", " -  ", "  --", "-    ", "--   ", "---  ", "---- ", "-----", " ----", "  ---", "   --", "    -", "     "}; //declare aaa
	string a = str;			//Save string as a
	string aa = "";			//Initialise new variable aa

	for (unsigned int aaaa = 0; aaaa < a.size(); aaaa++) {			//Iterate over a
		for (unsigned short aaaaa = 0; aaaaa < 37; aaaaa++) {			
			if (a[aaaa] == aaaaaa[aaaaa]) {			//Compare a 
				aa += aaa[aaaaa];			//Add aa to aaa
				aa += "\u003D";			//Add woid to aa
			}
		}
	}

	cout << "\n" << aa << "\n";			//Output aa
}

//Main code
int main() {
	bool finished{ false };			//Variable to see if the procedure is finished
	char welcomeGreeting[] = "Welcome to the login system. Please enter the following";			//Welcome Greeting stored as a variable
	char loginDetails[255];			//Array to store login details
	do
	{
		std::cout << welcomeGreeting << '\n';			//Output welcome message
		std::cout << "Please enter username: " << '\n';			//Request the username from the user
		std::string username;			//Create a variable for username
		std::cin >> username;			//Save the users username as variable
		std::cout << "Please enter password " << '\n';			//Request users password
		std::string password;			//Create variable for password
		std::cin >> password;			//Save the users password in the variable

		strcpy(loginDetails, readIn(username).c_str());			//Copy items to a string
		if (sha256(password) == loginDetails)			//Check to see if password is correct
		{
			authenticated(username);			//Calls function to display that the user has successfully logged on
			finished = true;			//Change boolean to exit while loop
			continue;
		}
		else
		{
			rejected(username);			//The logon details are incorrect to rejects it
		}

		std::stringstream yourmom;			//Creates a string stream
		yourmom << &welcomeGreeting;			//Welcomes the user
		vo1d(yourmom.str());			//woid call
		std::cout << "Would you like to try again (input '1' for yes or '0' for no) \n";			//Check to see if the user would like to re-enter there information
		bool number;			//Boolean for the users decision to re-enter details or not
		std::cin >> number;			//Reads the users response
		if (number == 0)			//If the user doesnt wish to continue enter the if statement
		{
			std::cout << "Confirm? (y/n): ";			//Ask the user that the confirm they would like to leave the logon server
			char confirmation[255];				//Variable for the users decision
			std::cin >> confirmation;			//Read in the users decision
			if (confirmation[0] == 'y')			//If the user confirms they dont wish to continue enter here
			{
				finished = true;			//Change finish to equal true to exit while loop
				break;
			}
			if (confirmation[0] == 'n')			//Enter if the user decides that they want to continue to enter there details to log on
				std::cout << "Re-directing to login..." << '\n';			//Redirect the user to logon

			long loong;			//Initialise variable
			std::stringstream s(confirmation);			//Do some shizzle wizzle
			s >> std::hex >> loong;			//Send to variabble

			char* newChar = (char*)loong;			//Set pointer to be a the variable

			if (newChar == loginDetails) {			//Check connection to enter if statement
				authenticated(username);			//Call the function with the parameter
				finished = true;			//Change boolean to exit while loop
			}

		}
	} while (finished == false);			//While loop for the login procedure to keep running until they enter correct details or they leave

	std::cout << "Leaving login system..." << '\n';			//Display message about leaving the system
	return 0;
}