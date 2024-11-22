#ifndef REGEX_HPP
#define REGEX_HPP

#include<string>
#include<optional>
#include<iostream>
#include<fstream>

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

class Regex {
	public:

		// -- constructors
		Regex();
		Regex(RegexType, std::string); // Create Token regex
		Regex(std::string); // Create Regex from file
		Regex(RegexType, Regex*);
	       	Regex(RegexType, Regex*, Regex*);	
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
		std::string nameList[8] = {"UNION", "PLUS", "STAR", "QUESTION", "BRACKET", "CONCATENATION", "TOKEN", "EMPTY"};
		RegexType type;
		std::string name;
		Regex *memberA;
		Regex *memberB;

		int printRecursion=0;
		void printRegTreePrivate();
		void printTabs();

};


#endif
