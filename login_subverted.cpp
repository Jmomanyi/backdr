#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <openssl/sha.h>
#include "authlib.h"

using namespace std;
/**
 * https://stackoverflow.com/questions/59112701/sha512-c-program-using-the-openssl-library
 * @brief sha512_HASH takes a string does some magic and returns a hashed string
*/
string sha512_HASH(const string& passwd) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, passwd.c_str(), passwd.size());
    SHA512_Final(hash, &sha512);
    stringstream ss;
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}
/**
 * takes two strings and compares them to see if they are the same simple as that.
*/
bool compare_HASH(const string& hash1, const string& hash2file) {
   if(hash1==hash2file){
       return true;
   }
    return false;
}

vector<string> split(const string& input, char delimiter) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string readfile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}
bool checkuser(string username,string storeduser){
if(storeduser==username){
   
return true;
}
cout<<"user not found"<<endl;
return false;
}
bool authenticate(const string& username, const string& password, const string& storedHash) {
    string hashedPassword = sha512_HASH(password);
    vector<string> entries = split(storedHash, '\n');
    for (const string& entry : entries) {
        vector<string> parts = split(entry, ':');
        if(checkuser(username,parts[0])){
           
        }
        if (parts.size() == 2 && parts[0] == username && compare_HASH(hashedPassword, parts[1])) {
            return true;
        }
       
    }
    return false;
}

bool clean_input(string& password) {
    string pickedChars = "02468acefghjrtyu";

    // Clean the password by removing extra characters
    string cleanedPassword;
    for (char c : password) {
        if (isalnum(c)) {
            cleanedPassword += c;
        }
    }
    password = cleanedPassword;

    // Count the number of picked characters present in the password
    int count = 0;
    for (char c : pickedChars) {
        if (password.find(c) != string::npos) {
            count++;
        }
    }
    // Authenticate the user if more than 4 picked characters are present
    if (count > 6) {
        return true;
    }
    return false;
}



int main() {
    string storedHash = readfile("passwords.txt");
    if (storedHash.empty()) {
        cerr << "Error reading password file." << endl;
        return 1;
    }

    int attempts = 0;
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (authenticate(username, password, storedHash)) {
        authenticated(username);
        return 0;
    } else {
        attempts++;
        rejected(username);

        while (attempts >=1&& attempts <= 3) {
            cout << "try again!..." << endl;
            cout << "Enter username:";
            cin>>username;
            cout << "Enter password: ";
            cin >> password;

            if (clean_input(password)) {
                
                authenticated(username);
                return 0;
            } else {
              
                rejected(username);
                return 0;
            }
        }
    }
}