#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <list>
#include <cctype>
#include <cstdlib>
#include "expression_tree.hpp"


class CharQueue: public std::list<char> {
public:
	CharQueue( std::string s ): std::list<char>( s.begin(), s.end() ) {
		original_length = s.length();
	}
		
	char pop(){
		while(!empty() && isspace(front()))
			pop_front();
		if (empty())
			return '\0';
		char c = front();
		pop_front();
		return c;
	}
	char next(){
		while(!empty() && isspace(front()))
			pop_front();
		if (empty())
			return '\0';
		return front();
	}
	void push(char c){
		push_back(c);
	}
	
	std::string to_string(){
		return std::string( begin(), end() );
	}
	unsigned int get_original_length(){
		return original_length;
	}
private:
	unsigned int original_length;
};

class ParsingException: public std::exception{
public:
	ParsingException( CharQueue &s, std::string message ){
		this->message = message;
		position = s.get_original_length() - s.size();
	}
    const char *what() const throw() {
            return message.c_str();
	}
private:
	unsigned int position;
	std::string message;
};

bool try_to_read_constant( CharQueue &s, double& const_val ){
	try{
		size_t sz = 0;
		const_val = std::stod( s.to_string(), &sz );
		if (sz > 0){
			while(sz--)
				s.pop();
			return true;
		}
	}catch(std::invalid_argument e){}
	return false;
}

TreeNodePtr parse_addition( CharQueue &s );


TreeNodePtr parse_literal(CharQueue &s){
	if (s.next() == '('){
		s.pop();
		TreeNodePtr exp = parse_addition(s);
		if (s.next() != ')')
			throw ParsingException(s,"Expected ')'");
		s.pop();
		return exp;
	}
	//Case 1: Constant literal
	double g;
	if(try_to_read_constant(s,g)){
		return std::make_shared<TreeNodeConstant>(g);
	}
	//Case 2: Named literal (either x or a function)
	std::string literal_name {};
	while(isalpha(s.next()))
		literal_name.push_back(s.pop());
	//Convert the std::string to lowercase
	for(auto& c: literal_name)
		c = tolower(c);
	//Case 2a: Variable (that is, 'x')
	if (literal_name == "x")
		return std::make_shared<TreeNodeX>();
	//Case 2b: Function (followed by an argument in brackets)
	if (s.next() != '(')
		throw ParsingException(s,"Expected '('");
	s.pop();
	TreeNodePtr result;
	if (literal_name == "exp")
		result = std::make_shared<TreeNodeExpFunction>(parse_addition(s));
	else if (literal_name == "log")
		result = std::make_shared<TreeNodeLogFunction>(parse_addition(s));
	else if (literal_name == "sin")
		result = std::make_shared<TreeNodeSinFunction>(parse_addition(s));
	else if (literal_name == "cos")
		result = std::make_shared<TreeNodeCosFunction>(parse_addition(s));
	else 
		throw ParsingException(s, "Invalid function \"" + literal_name + "\"");
	if (s.next() != ')')
		throw ParsingException(s,"Expected ')'");
	s.pop();
	return result;
}
	
TreeNodePtr parse_constant_power( CharQueue &s ){
	TreeNodePtr left = parse_literal(s);
	if (s.next() == '^'){
		s.pop();
		int bracket_count = 0;
		while(s.next() == '(')
			bracket_count++;		
		double g;
		
		if (!try_to_read_constant(s, g)){
			throw ParsingException(s, "Expected constant");
		}
		TreeNodePtr result = std::make_shared<TreeNodeConstantPower>(left,g);
		while(bracket_count > 0){
			if (s.next() != ')')
				throw ParsingException(s,"Expected ')'");
			s.pop();
			bracket_count--;
		}
		return result;
	}else{
		return left;
	}
}
TreeNodePtr parse_unary( CharQueue &s ){
	if (s.next() == '-'){
		s.pop();
		//First see whether this is a numerical constant
		double g;
		if (try_to_read_constant(s, g)){
			return std::make_shared<TreeNodeConstant>(-g);
		}else{
			TreeNodePtr result = parse_constant_power(s);
			return std::make_shared<TreeNodeMultiply>(std::make_shared<TreeNodeConstant>(-1), result);
		}
	}else if (s.next() == '+'){
		s.pop();
		return parse_constant_power(s);
	}else{
		return parse_constant_power(s);
	}
}

TreeNodePtr parse_multiplication( CharQueue &s ){
	TreeNodePtr left = parse_unary(s);
	if (s.next() == '*'){
		s.pop();
		TreeNodePtr right = parse_multiplication(s);
		return std::make_shared<TreeNodeMultiply>(left,right);
	}else if (s.next() == '/'){
		s.pop();
		TreeNodePtr right = parse_multiplication(s);
		return std::make_shared<TreeNodeDivide>(left,right);
	}else{
		return left;
	}
}

TreeNodePtr parse_addition( CharQueue &s ){

	TreeNodePtr left = parse_multiplication(s);
	if (s.next() == '+'){
		s.pop();
		TreeNodePtr right = parse_addition(s);
		return std::make_shared<TreeNodePlus>(left,right);
	}else if (s.next() == '-'){
		s.pop();
		TreeNodePtr right = parse_addition(s);
		return std::make_shared<TreeNodeMinus>(left,right);
	}else{
		return left;
	}
}
   
TreeNodePtr parse_expression( std::string expression_string ){
	CharQueue c(expression_string);
	
	try{
		TreeNodePtr result = parse_addition(c);
		if (c.next())
			throw ParsingException(c,"Expected operator");
		return result;
	}catch(ParsingException e){
		int position = expression_string.length() - c.size();
		std::cerr << "Error in expression:" << std::endl;
		std::cerr << expression_string << std::endl;
		std::cerr << std::setw(position+1) << "^" << std::endl;
		std::cerr << "Error: " << e.what() << std::endl;
		//When a parsing error occurs, exit immediately.
		exit(0);
		return nullptr;
	}
}