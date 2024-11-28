#include"regex.hpp"

std::string nameList[8] = {"UNION", "PLUS", "STAR", "QUESTION", "BRACKET", "CONCATENATION", "TOKEN", "EMPTY"};

//parser automaton used to create regex from file
Fsa parser = Fsa(22);
bool parserInitialized=0;
void initFsa() {
	std::vector<char> alphanumericals = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for(int i=65; i<91; i++) {
		alphanumericals.push_back(i);
		alphanumericals.push_back(i+32);
	}
	std::vector<char> allexceptbrackets = alphanumericals;
	allexceptbrackets.insert(allexceptbrackets.end(), {'+','*',',','|'});
	// --arrows
	// tokens, bracket, union pt1, union pt2
	parser.add_arrow_key(0,1,{')'});	
	parser.add_arrow_key(1,1,alphanumericals);	
	parser.add_arrow_key(1,2,{'('});	
	parser.add_arrow_key(1,3,{'+','*',','});	
	parser.add_arrow_key(3,3,alphanumericals);	
	parser.add_arrow_key(3,4,{'('});
	parser.add_arrow_key(3,5,{')'});	
	parser.add_arrow_key(5,3,{'('});	
	parser.add_arrow_key(5,5,allexceptbrackets);	
	parser.add_arrow_key(3,6,{'|'});	
	parser.add_arrow_key(1,6,{'|'});	
	parser.add_arrow_key(6,7,allexceptbrackets);
	parser.add_arrow_key(7,7,allexceptbrackets);	
	parser.add_arrow_key(7,9,{')'});	
	parser.add_arrow_key(9,7,{'('});	
	parser.add_arrow_key(9,9,allexceptbrackets);	
	parser.add_arrow_key(7,8,{'('});	
	parser.add_arrow_key(6,8,{'('});
	//plus
	parser.add_arrow_key(0,10,{'+'});	
	parser.add_arrow_key(10,11,{')'});	
	parser.add_arrow_key(11,11,allexceptbrackets);	
	parser.add_arrow_key(11,12,{'('});	
	parser.add_arrow_key(11,13,{')'});	
	parser.add_arrow_key(13,11,{'('});	
	//star	
	parser.add_arrow_key(0,14,{'*'});	
	parser.add_arrow_key(14,15,{')'});	
	parser.add_arrow_key(15,15,allexceptbrackets);	
	parser.add_arrow_key(15,16,{'('});	
	parser.add_arrow_key(15,17,{')'});	
	parser.add_arrow_key(17,15,{'('});	
	//question
	parser.add_arrow_key(0,18,{'?'});	
	parser.add_arrow_key(18,19,{')'});	
	parser.add_arrow_key(19,19,allexceptbrackets);	
	parser.add_arrow_key(19,20,{'('});	
	parser.add_arrow_key(19,21,{')'});	
	parser.add_arrow_key(21,19,{'('});	
	//
	/*
	parser.add_arrow_key(,,);	
	parser.add_arrow_key(,,);	
	parser.add_arrow_key(,,);	
	*/
	parserInitialized=1;
}

// -- Constructors ---
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
	if(!parserInitialized)
		initFsa();
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
// -- destructor
Regex::~Regex() {
	
}
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




