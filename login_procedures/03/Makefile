ALLCPP=$(wildcard *.cpp)
SOURCES=$(filter-out authlib.cpp,$(ALLCPP))
TARGETS=$(patsubst %.cpp,%,$(SOURCES))
CPPFLAGS=-Wall -pedantic -Wextra -std=c++11
C=g++

all: $(TARGETS)

authlib.o: authlib.cpp
	$C $(CPPFLAGS) -c authlib.cpp

%: %.cpp authlib.o
	$C $(CPPFLAGS) $< authlib.o -lcrypto -o $@

%: %.cpp login.cpp
	$C $(CPPFLAGS) -c login.cpp

%: %.cpp login-subverted.cpp
	$C $(CPPFLAGS) -c login-subverted.cpp

clean:
	rm -f $(TARGETS)
	rm -f *~ *.o a.out
