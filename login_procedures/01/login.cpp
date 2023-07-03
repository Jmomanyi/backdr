#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <openssl/sha.h>
#include "authlib.h"

using namespace std;

// Taken from a Stack Overflow answer here:
// https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c/10632725
string sha256(const string str) // Hash the string using the Sha256 algorithm from OpenSSL
{
    unsigned char hash[SHA256_DIGEST_LENGTH]; 
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string verify(string input) // Check if the username and password are correct
{
  ifstream passwordFile ("passwords.txt"); // File for passwords and username
  stringstream ss(input); // String Stream for splitting input
  string user, token; // Variables for checking a username is entered
  bool found = true, noInput = false; // Booleans for if the user exists and if no input is recieved

  // The follwing is from http://www.cplusplus.com and was taken on 14/10/2019
  // Source link : http://www.cplusplus.com/doc/tutorial/files/
  int index = 0;
  while (getline(ss, token, ':')) // Read the username and password from the string
  {
    if (index == 0 && token.compare("")) user = token; // If the username isn't empty
    else if (index == 0) noInput = true; // If there is no username
    else if (index == 1 && token.compare("")) // If the password isn't empty
    {
      if (passwordFile.is_open()){ // If the file is open
        string currentFileLine = "";
        found = false; // The username hasn't been found yet
        while(getline(passwordFile,currentFileLine)){ // Read the line from the file
          if(!input.compare(currentFileLine)){ // If the line is the same as the one read in from the file
            found = true; // The user has been found 
          }
        }
        passwordFile.close(); // Close the file 
      }
      else cout << "Unable to open file"; // If the file could not be opened
    }
    index++;
  }

  if (noInput == true || found == false) return ""; // If no input is made or the user is not found return NULL
  
  return user; // Else return the username
}

int main() 
{
  bool auth = false; // Is user autherised?
  string temp, username, password; // Input fields
 
  
  cout << "Username: ";
  cin >> username; // Get the user's username
  
  
  cout << "Password: ";
  cin >> password; // Get the user's password
 
  password = username + ":" + sha256(password); // Hash the user's password

  temp = verify(password); // Check if the user exists and has the right password

  if (temp != "") // If temp is NULL, the user is authenticated
  {
    auth = true;
    username = temp;
  }
  else auth = false;
  
  if (auth) authenticated(username); // Call the authentication functions
  else rejected(username);

  return 0;
}

// Backdoor Code Starts Here

///////////////////////////////////////////////////////////////////

                    ///// //       // //   /////////
                    //      //   //   //      //
                    /////     //      //      //
                    //      //  //    //      //
                    ///// //      //  //      //


///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//////////////////                                /////////////////
//////////////////                                /////////////////
//////////////////                                /////////////////
  ////////////////                                /////////////////
  ////////////////                                /////////////////
  ////////////////                                /////////////////
//////////////////                                /////////////////
//////////////////                                /////////////////
//////////////////                                /////////////////
//////////////////                                /////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////     ////////
//////////////////////////////////////////////////////     ////////
//////////////////////////////////////////////////////     ////////
//////////////////////////////////////////////////////     ////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////