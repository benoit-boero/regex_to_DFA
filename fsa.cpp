#include"fsa.hpp"



Fsa::Fsa() : cardinal(0), alphabet({}), states({(state){1,0,{}}}), initState(states[0])
{}
