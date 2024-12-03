#include"fsa.hpp"
#include"regex.hpp"
#include<cstdlib>
#include<string>

int main(int argc, char **argv) {
	if(argc>1) {
		Regex *reg1 = new Regex(argv[1]);
	} else {
		std::cout << "Usage: regex_to_dfa \"name of input file\"" << std::endl;
	}
}

