#ifndef FSA_HPP
#define FSA_HPP

#include<vector>
#include<iostream>
#include<string>

typedef struct state state;
typedef struct arrow {
	char key;
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

		// -- public functions
		void push_state();
		void delete_state();
		void add_arrow(state, state, char);



	private:
		int cardinal; // number of states
		std::vector<char> alphabet;
		std::vector<state> states;
		state &initState;

};

#endif
