### This Makefile copies the password file and authlib files into every
### directory and then compiles all login procedures in all directories

### type  'make'  in this directory (on a QMB Lab PC's Ubuntu Linux system)

all:
	for i in */; do cp passwords.txt authlib.h authlib.cpp $$i/; done
	for i in */; do make -C $$i; done
