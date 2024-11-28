#ifndef REGEX_HPP
#define REGEX_HPP

#include<string>
#include<iostream>
#include<fstream>
#include"fsa.hpp"

enum RegexType {
	UNION,
	PLUS,
	STAR,
	QUESTION,
	BRACKET,
	CONCATENATION,
	TOKEN,
	EMPTY
};

extern std::string nameList[8];
extern Fsa parser;
extern bool parserInitialized;

class Regex {
	public:

		// -- constructors
		Regex();
		Regex(RegexType, std::string); // Create Token regex
		Regex(std::string); // Create Regex from file
		Regex(RegexType, Regex*);
	       	Regex(RegexType, Regex*, Regex*);
		// -- destructor
		virtual ~Regex();	
		// -- public functions
		// operators
		Regex *bracket();
		Regex *unite(Regex*);
		Regex *plus();
		Regex *star();
		Regex *question();
		Regex *concatenate(Regex*);
		//accessors
		RegexType getType();	
		//display
		void printReg();
		void printRegTree();
	private:
		RegexType type;
		std::string name;
		int numberOfMembers=0;
		Regex *memberA;
		Regex *memberB;

		int printRecursion=0;
		void printRegTreePrivate();
		void printTabs();

};


#endif
