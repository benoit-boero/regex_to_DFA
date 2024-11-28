#include"fsa.hpp"

// -- constructors
Fsa::Fsa() : cardinal(0), alphabet({}), states({(state){0,0,{}}}), initState(states[0]), nullarrow((arrow){'\0', nullptr})
{}
Fsa::Fsa(int n) : cardinal(n), alphabet({}), states({(state){0,0,{}}}), initState(states[0]), nullarrow((arrow){'\0', nullptr})
{
	for(int i=1; i<n; i++) {
		states.push_back((state){0,i,{}});
	}
}

// -- public functions
state *Fsa::empty_state(int serial) {
	state *ret = new state;
	*ret = (state){0,serial,{}};
	return ret;
}
void Fsa::push_state(state& s) {
	states.push_back(s);	
	cardinal++;
}

void Fsa::delete_state(state& s) {
	states.erase(states.begin()+s.serial);
	for(auto node=states.begin(); node!=states.end(); node++) {
		auto goodArrows = std::remove_if((*node).quiver.begin(), (*node).quiver.end(), [s](arrow a) { return a.target->serial==s.serial; });
		(*node).quiver.erase(goodArrows, (*node).quiver.end());
	}
}

void Fsa::add_arrow(state& s1, state& s2, char c) {
	auto it1 = std::find_if(states.begin(), states.end(), [s1, s2](state s){return s.serial==s1.serial||s.serial==s2.serial;});
	if(it1==states.end()) {
		std::cout << "Trying to add arrow between non-existant states, canceling operation." << std::endl;
		return;
	}
	auto it3 = std::find(alphabet.begin(), alphabet.end(), c);
	if(it3==alphabet.end()) {
		std::cout << "Trying to add an arrow whom key isn't in the alphabet :" << c <<", adding it to the alphabet..." << std::endl;
		alphabet.push_back(c);
	}
	arrow newArr = (arrow){c, &s2};
	s1.quiver.push_back(newArr);
}


// -- private functions

