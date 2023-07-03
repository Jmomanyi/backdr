#include <iostream>
#include "authlib.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "openssl/sha.h"

using namespace std;

//sha256 takes the password entered as a string and hashes it to be
//like the passwords stored in passwords.txt
string sha256(const string pass) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pass.c_str(), pass.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
  //Setting up the necessary variables. Auth is false to begin with due to
  //presumption that the user will not be allowed access.
  bool auth = false;
  string line, user, pass, userx, passx;
  //Opening the password file to read the usernames and hashed passwords
  ifstream pwdb ("passwords.txt");
  if (pwdb.is_open()) {
    //The user is asked for and enters a username
    cout << "Enter Username" << endl;
    getline(cin, userx);
    while (getline (pwdb,line)) {
      //Getting the usernames and passwords from the txt file
      user = line.substr(0, line.find(':'));
      pass = line.substr(line.find(':')+1, line.length());
      //Passwords are not checked unless there is a correct username.
      if (userx == user) {
        //Asking the user for a password to the account.
        //Password entered is fully visible in command line.
        //Hiding it would be good practice but because it isn't required won't bother to save length.
        cout << "User accepted " << userx << endl;
        cout << "Enter Password:" << endl;
        getline (cin, passx);
        passx = sha256(passx);
        //If the password is correct auth is set to true.
        //Otherwise the user is given another chance to enter a correct password.
        if (passx == pass){
          auth = true;
        } else {
          //Asking for the users password again
          cout << "Incorrect Password. Please re-enter:" << endl;
          getline (cin, passx);
          passx = sha256(passx);
          //If the password is correct auth is set to true
          //Otherwise the user is given a final chance to enter a correct password
          if (passx == pass){
            auth =  true;
          } else {
            //Asking for the users password for the final time
            cout << "Last attempt. Please re-enter:" << endl;
            getline (cin, pass);
            pass = sha256(pass);
            //If the password is correct auth is set to true.
            //Otherwise auth remains false and the user will not be able to log in.
            if (passx == pass){
              auth = true;
            }
          }
        }
      }
    }
  }
  //If they match a combination in the text file
  //then the user is authenticated. If not the user is rejected.
  if (auth) authenticated(userx);
  else rejected(userx);
}