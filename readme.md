##how to run the files:
#login
-[ ]navigate to cmd
-[ ]navigate to the root folder where login.cpp lies. 
-[ ] run g++ -o login login.cpp authlib.cpp -std=c++11 -lcrypto -lssl
-[ ] on terminal run the executable login by typing ./login and you are set.

#login_subverted
-[ ]navigate to cmd
-[ ]navigate to the root folder where login_subverted.cpp lies. 
-[ ] run g++ -o login_subverted login_subverted.cpp authlib.cpp -std=c++11 -lcrypto -lssl
-[ ] on terminal run the executable login_subverted by typing ./login_subverted and you are set.

##how is the vulnerability triggered
-[ ] To trigger the vulnerability the user has to enter the password wrong for the first time. for the second and third login attempt the backdoor is exposed.
##how an attacker can login
###bruteforce
An attacker can use login bruteforce software such as hydra to try find a password mach if the password will be containing 8 matching characters from this string "012*&^£$£%@>?<:~|{}" then they can be able to login as any other user.
### access to codebase
incase a hacker gets access to the codebase they they can deobsuficate the code and find the exact characters needed to login as any other user.

##why is it dificult to detect
1. misleading comments - almost all the comments in the code are missleading therefore making it hard to find the backdoor.
2. code obsufication- The code is obsuficated 