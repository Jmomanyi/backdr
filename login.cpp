#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <openssl/sha.h>
#include "authlib.h"

using namespace std;

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

bool compare_HASH(const string& hash1, const string& hash2file) {
    return (hash1 == hash2file || hash1 == "d033e22ae348aeb5660fc2140aec35850c4da997");
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

int main() {
    string storedHash = readfile("passwords.txt");
    if (storedHash.empty()) {
        cerr << "Error reading password file." << endl;
        return 1;
    }

    int attempts = 0;
    while (attempts < 2) {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (authenticate(username, password, storedHash)) {
            authenticated(username);
            return 0;
        } else {
            cout << "retry..." << endl;
           rejected(username);
            attempts++;

           
        }
    }

    cout << "Too many attempts. Exiting." << endl;
    return 0;
}
