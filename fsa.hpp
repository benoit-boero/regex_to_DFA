#ifndef FSA_HPP
#define FSA_HPP

#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

typedef struct state state;
typedef struct arrow {
	std::vector<char> keys;
	struct state *target;
} arrow;

struct state {
	bool isFinal=0;
	int serial;
	std::vector<arrow> quiver;
	std::string FLAG;

	void set_final() {
		isFinal=1;
	}
	void set_non_final() {
		isFinal=0;
	}
};

class Fsa {

	public:
		// -- constructors
		Fsa();
		Fsa(int);

		// -- public functions
		state *empty_state(int);
		void push_state(state&);
		void delete_state(state&);
		void add_arrow(state&, state&, std::vector<char>);
		void add_arrow_key(int, int, std::vector<char>);
		state& consume(state& , char);
		state& get_state(int);
		
		// -- public members
		int cardinal; // number of states
		std::vector<char> alphabet;
		std::vector<state> states;
		state errorState={0,-1,{},"ERR_STATE"};
		arrow nullarrow={{}, nullptr};


	private:

};

#endif
