#include"fsa.hpp"

// -- constructors
Fsa::Fsa() : cardinal(0), alphabet({}), states({(state){1,0,{}}}), initState(states[0]), nullarrow((arrow){'\0', nullptr})
{}

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


// -- private functions

