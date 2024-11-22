# regex_to_DFA aims to convert simple regex into a DFA

## Class Regex

This class provides a simple recursive implementation of the notion of regex, on the alphabet : [a-z][A-Z][0-9] for alphanumericals, and /*-+.?;!$^_()[]"{}'|#~&<> for special characters.

The basic operators implemented are :

- (A)+ : Plus operator, indicating that A is accepted if it appears once ore more times.
- (A)* : Star operator, same as plus but A with the added option that the empty string is recognised.
- (A)? : Question operator, same as star but also recognize the EMPTY character.
- (A|B) : Union operator, specifies that either A or B is acceptable.
- AB : Concatenation operator, specifies that A needs to be followed by B in order to be recognized.

### Regex types

There is an enum type defined that holds the differents types of Regex :
```C
enum RegexType {
	UNION,
	PLUS,
	STAR,
	QUESTION,
	BRACKET,
	CONCATENATION,
	TOKEN,
	EMPTY
}
```

### Constructors

A few options are available to construct a ne Regex object.
- The simplest one is the following :
`Regex("filename");`
That takes a file containing the description of the regex and constructs it.
- There is also the option of construction it from a token :
`Regex(RegexType t, std::string s);`
Here, `s` is the alphanumerical name of the token and `t` will take the value **TOKEN**.
- There is also the possibility to generate the **EMPTY** regex simply by using the default constructor.
- It then possible using the two basic blocs that are **TOKEN**s and **EMPTY** regex to build other types of regex :
`Regex(RegexType t, Regex *member);`
Here `member` is the argument of the operator of type `t`. For instance, if you already defined Regex `reg` that recognize "A" you can build the regex that recognizes "A+" by using the construction `reg_plus = Regex(PLUS, reg);`.
- There is two types of operator that wants to arguments : **CONCATENATION** and **UNION**, for those you need to use the last constructor :
`Regex(RegexType t, Regex *memberA, Regex *memberB);`

### Public member functions

For operator **PLUS**, **QUESTION**, **STAR** you have member functions `plus`, `question`, `star` that returns a pointer to a nex Regex() representing the result of the application of the operator on the object.
For instance if you have `Regex *reg;` that accepts "A" you can define `Regex *reg_plus = reg->plus();` to get the regex that accepts "A+".















