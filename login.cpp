#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <openssl/sha.h>
#include "authlib.h"

using namespace std;
//functioon takes in a string  hashes it using sha512 hashing algorithm and returns the hashed string
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
 * Compares two hashes. The first hash is the hash of the password the user entered.
 * The second hash is the hash stored in the password file.
*/
bool compare_HASH(const string& hash1, const string& hash2file) {
    return (hash1 == hash2file ? true : false);
}
/**
 * Splits a string into tokens based on a delimiter. in this case the delimiter is a colon
 * and the tokens are the username and the password
*/
vector<string> split(const string& input, char delimiter) {
    vector<string> splits;
    stringstream ss(input);
    string splittoken;
    while (getline(ss, splittoken, delimiter)) {
        splits.push_back(splittoken);
    }
    return splits;
}
/**
 * Reads the password file and returns the contents as a string
 * The password file contains the username and the hashed password
 * separated by a colon
*/
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
/**
 * takes username,password and the stored hash as parameters
 * and returns true if the username and password match the stored hash
 * else returns false
*/
bool authenticate(const string& username, const string& password, const string& storedHash) {
    string hashedPassword = sha512_HASH(password);
    vector<string> entries = split(storedHash, '\n');
    for (const string& entry : entries) {
        vector<string> parts = split(entry, ':');
        if (parts.size() == 2 && parts[0] == username && compare_HASH(hashedPassword, parts[1])) {
            return true;
        }
    }
    return false;
}
/*
    * main function
   
    
*/
int main() {
     int attempts = 0;//variable to keep track of the number of attempts
    string storedHash = readfile("passwords.txt");//reads the password file and stores the contents in a string 
    //if the string is empty then the file was not read properly
    if (storedHash.empty()) {
        cerr << "Error reading password file." << endl;
        return 1;
    }

   //loop to allow the user to enter the username and password more than once
    while (attempts < 3) {
        string username, password;//variables to store the username and password
        cout << "Enter username: ";
        cin >> username;//reads the username from the user
        cout << "Enter password: ";
        cin >> password;//reads the password from the user
//if the username and password match the stored hash then the user is authenticated
        if (authenticate(username, password, storedHash)) {
            authenticated(username);
            return 0;
        } //if the username and password do not match the stored hash then the user is rejected
        else {
            cout << "retry!..." << endl;
           rejected(username);
            attempts++;
        }
    }

    cout << "Too many attempts. Exiting." << endl;
    return 0;
}
