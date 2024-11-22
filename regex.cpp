
#include"regex.hpp"

// -- Constructors ---
// I don't know how dirty is the *emptyRegex trick in order to have null references.
Regex::Regex() : type(EMPTY), name(nameList[EMPTY]), memberA(nullptr), memberB(nullptr)
{};
Regex::Regex(RegexType t, std::string text) : type(TOKEN), name(text), memberA(nullptr), memberB(nullptr)
{};
Regex::Regex(RegexType t, Regex *memberA) : type(t), name(nameList[t]), memberA(memberA), memberB(nullptr)
{};
Regex::Regex(RegexType t, Regex *memberA, Regex *memberB) : type(t), name(nameList[t]), memberA(memberA), memberB(memberB)
{};
Regex::Regex(std::string nf) : type(EMPTY), name(nameList[EMPTY]), memberA(nullptr), memberB(nullptr) 
{
	char c;
	std::ifstream input(nf);
	if(input.is_open()) {
		while(c!=EOF) {
			std::cout << c;
			c = input.get();
			while(c==' '||c=='\n') {
				c = input.get();
			}
		}
	input.close();
	} else {
		std::cout << "Error while opening file :" << nf << ". Returning EMPTY regex." << std::endl;
	}
};

// -- public functions ---
// operations on regex
Regex *Regex::bracket() {
	return new Regex(BRACKET, this);
}
Regex *Regex::plus() {
	return new Regex(PLUS, this);
}
Regex *Regex::star() {
	return new Regex(STAR, this);
}
Regex *Regex::question() {
	return new Regex(QUESTION, this);
}
Regex *Regex::unite(Regex* R) {
	return new Regex(UNION, R, this);
}
Regex *Regex::concatenate(Regex* R) {
	return new Regex(CONCATENATION, R, this);
}
// Accessors
RegexType Regex::getType() {
	return type;
}
// display the regex
void Regex::printReg() {
	if(type==TOKEN)
		std::cout << name;
	else if(type==PLUS) {
		std::cout << "(";
		memberA->printReg(); 
		std::cout << ")+";
	}
	else if(type==STAR) {
		std::cout << "(";
		memberA->printReg();
		std::cout << ")*";
	}
	else if(type==QUESTION) {
		std::cout << "(";
		memberA->printReg();
		std::cout << ")?";
	}
	else if(type==EMPTY) {
		std::cout << "()";
	}
	else if(type==UNION) {
		std::cout << "(";
		memberA->printReg();
		std::cout << "|";
		memberB->printReg();
		std::cout << ")";
	}
	else if(type==BRACKET) {
		std::cout << "(";
		memberA->printReg();
		std::cout << ")";
	}
	else if(type==CONCATENATION) {
		std::cout << "(";
		memberA->printReg();
		memberB->printReg();
		std::cout << ")";
	}	
}
void Regex::printTabs() {
	for(int i=0; i<printRecursion; i++)
		std::cout << "\t";
}
void Regex::printRegTree() {
	this->printRecursion=0;
	this->printRegTreePrivate();
}
// display the regex in a tree form
void Regex::printRegTreePrivate() {
	printTabs();
	if(type==TOKEN) {
		std::cout << "TOKEN " << name << std::endl;
	}
	else if(type==PLUS) {
		std::cout << "PLUS" << std::endl;
		memberA->printRecursion=this->printRecursion+1;
		memberA->printRegTreePrivate(); 
	}
	else if(type==STAR) {
		std::cout << "STAR" << std::endl;
		memberA->printRecursion=this->printRecursion+1;
		memberA->printRegTreePrivate();
	}
	else if(type==QUESTION) {
		std::cout << "QUESTION" << std::endl;
		memberA->printRecursion=this->printRecursion+1;
		memberA->printRegTreePrivate() ;
	}
	else if(type==EMPTY) {
		std::cout << "EMPTY";
	}
	else if(type==UNION) {
		std::cout << "UNION" << std::endl;
		memberA->printRecursion=this->printRecursion+1;
		memberB->printRecursion=this->printRecursion+1;
		memberA->printRegTreePrivate();
		std::cout << std::endl;
		memberB->printRegTreePrivate();
		std::cout << std::endl;
	}
	else if(type==BRACKET) {
		std::cout << "BRACKET";
		memberA->printRecursion=this->printRecursion+1;
		memberA->printRegTreePrivate();
	}
	else if(type==CONCATENATION) {
		std::cout << "CONCATENATION" << std::endl;
		memberA->printRecursion=this->printRecursion+1;
		memberB->printRecursion=this->printRecursion+1;
		memberA->printRegTreePrivate();
		std::cout << std::endl;
		memberB->printRegTreePrivate();
		std::cout << std::endl;
	}	
}




