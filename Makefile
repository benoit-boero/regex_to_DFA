all:
	@g++ -o regexToDFA -Wall fsa.cpp regex.cpp main.cpp
