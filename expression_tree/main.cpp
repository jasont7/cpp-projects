#include <iostream>
#include <stdexcept>
#include <string>
#include "expression_tree.hpp"


int main(){

	std::string expression_string;
	std::string line;
	double x_val;
	std::cerr << "Enter a function f(x): ";
	std::getline(std::cin, expression_string);
	
	std::cerr << "Enter a value of x: ";
	std::getline(std::cin, line);
	std::cerr << std::endl;
	try{
		x_val = std::stod(line);
	}catch(std::invalid_argument e){
		std::cout << "Invalid value \"" << line << "\"" << std::endl;
		return 1;
	}
	
	
	TreeNodePtr F = parse_expression( expression_string );
	std::cout << "f(x) = " << F->to_string() << std::endl;
	std::cout << "f("<<x_val<<") = " << F->evaluate(x_val) << std::endl;
	TreeNodePtr F_prime = F->differentiate();
	std::cout << "f'(x) = " << F_prime->to_string() << std::endl;
	std::cout << "f'("<<x_val<<") = " << F_prime->evaluate(x_val) << std::endl;

	return 0;
}
