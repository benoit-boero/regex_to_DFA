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
		
		// -- public members
		int cardinal; // number of states
		std::vector<char> alphabet;
		std::vector<state> states;
		state initState;
		state errorState;
		arrow nullarrow;


	private:

};

#endif
