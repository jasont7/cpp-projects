#ifndef EXPRESSION_TREE_HPP
#define EXPRESSION_TREE_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <cmath> //For exp(), log(), sin(), cos() and pow()

class TreeNode;
typedef std::shared_ptr<TreeNode> TreeNodePtr;

class TreeNode{
public:
	TreeNode(){}
	virtual ~TreeNode(){
	}

	//Functions to implement for each of the classes below
	//(put your implementations in expression_tree.cpp)
	/* evaluate(x)
	   Return the result of evaluating this node with the
	   given value of x.
	*/
	virtual double evaluate( double x ) = 0;
	/* differentiate()
	   Return a new TreeNode corresponding to the derivative
	   of this node.
	*/
	virtual TreeNodePtr differentiate( ) = 0;
	/* duplicate()
	   Copy this node (and all of its children) and return
	   a pointer to the copy.
	*/
	virtual TreeNodePtr duplicate() = 0;
	
	//Functions to assist with parsing and printing	
	virtual std::string to_string() = 0;
	virtual int precedence() = 0;
protected:
	//Function to format double constant values for display
	static std::string format_constant(double c){
		std::stringstream s;
		s << std::setprecision(3) << c;
		return s.str();
	}
	std::string child_to_string( TreeNodePtr child ){
		std::string s = child->to_string();
		if (precedence() < child->precedence())
			s = "(" + s + ")";
		return s;
	}
};


/* TreeNodeConstant represents constant literals (like 3 or 10.6) */
class TreeNodeConstant: public TreeNode{
public:
	TreeNodeConstant(double c){
		constant_value = c;
	}
	virtual double evaluate(double x);
	virtual TreeNodePtr differentiate();
	virtual TreeNodePtr duplicate();
	virtual std::string to_string(){
		return format_constant(constant_value);
	}
	virtual int precedence(){ return 0; }
private:
	double constant_value;
};


/* TreeNodeX represents occurrances of the variable x in the expression */
class TreeNodeX: public TreeNode{
public:
	TreeNodeX(){
	}
	virtual double evaluate(double x);
	virtual TreeNodePtr differentiate();
	virtual TreeNodePtr duplicate();
	virtual std::string to_string(){
		return "x";
	}
	virtual int precedence(){ return 0; }
};


/* TreeNodePlus represents the + operator */
class TreeNodePlus: public TreeNode {
public:
	TreeNodePlus(TreeNodePtr left_operand, TreeNodePtr right_operand) {
		left = left_operand;
		right = right_operand;
	}
	virtual double evaluate(double x);
	virtual TreeNodePtr differentiate();
	virtual TreeNodePtr duplicate();
	virtual std::string to_string(){
		return child_to_string(left) + " + " + child_to_string(right);
	}
	virtual int precedence() { return 6; }
private:
	TreeNodePtr left;
	TreeNodePtr right;
};


/* TreeNodeMinus represents the - operator */
class TreeNodeMinus: public TreeNode{
public:
	TreeNodeMinus( TreeNodePtr left_operand, TreeNodePtr right_operand ){
		left = left_operand;
		right = right_operand;
	}
	virtual double evaluate( double x );
	virtual TreeNodePtr differentiate( );
	virtual TreeNodePtr duplicate( );
	virtual std::string to_string(){
		return child_to_string(left) + " - " + child_to_string(right);
	}
	virtual int precedence(){ return 5; }
private:
	TreeNodePtr left;
	TreeNodePtr right;
};


/* TreeNodeMultiply represents the * operator */
class TreeNodeMultiply: public TreeNode {
public:
	TreeNodeMultiply(TreeNodePtr left_operand, TreeNodePtr right_operand){
		left = left_operand;
		right = right_operand;
	}
	virtual double evaluate(double x);
	virtual TreeNodePtr differentiate();
	virtual TreeNodePtr duplicate();
	virtual std::string to_string(){
		return child_to_string(left) + "*" + child_to_string(right);
	}
	virtual int precedence(){ return 4; }
private:
	TreeNodePtr left;
	TreeNodePtr right;
};


/* TreeNodeDivide represents the / operator */
class TreeNodeDivide: public TreeNode{
public:
	TreeNodeDivide( TreeNodePtr left_operand, TreeNodePtr right_operand ){
		left = left_operand;
		right = right_operand;
	}
	virtual double evaluate( double x );
	virtual TreeNodePtr differentiate( );
	virtual TreeNodePtr duplicate( );
	virtual std::string to_string(){
		return child_to_string(left) + "/" + child_to_string(right);
	}
	virtual int precedence(){ return 3; }
private:
	TreeNodePtr left;
	TreeNodePtr right;
};


/* TreeNodeConstantPower represents exponentiation by a constant (direct exponentiation by a non-constant is not supported) */
class TreeNodeConstantPower: public TreeNode{
public:
	TreeNodeConstantPower(TreeNodePtr left_operand, double c){
		left = left_operand;
		exponent = c;
	}
	virtual double evaluate( double x );
	virtual TreeNodePtr differentiate();
	virtual TreeNodePtr duplicate();
	virtual std::string to_string(){
		return child_to_string(left) + "^" + format_constant(exponent);
	}
	virtual int precedence(){ return 2; }
private:
	TreeNodePtr left;
	double exponent;
};


/* TreeNodeExpFunction represents the exp() function, which evaluates e^x */
class TreeNodeExpFunction: public TreeNode{
public:
	TreeNodeExpFunction(TreeNodePtr arg) {
		argument = arg;
	}
	virtual double evaluate(double x);
	virtual TreeNodePtr differentiate( );
	virtual TreeNodePtr duplicate( );
	virtual std::string to_string(){
		return "exp(" + argument->to_string() + ")";
	}
	virtual int precedence(){ return 1; }
private:
	TreeNodePtr argument;
};


/* TreeNodeLogFunction represents the log() function, which evaluates the natural logarithm */
class TreeNodeLogFunction: public TreeNode{
public:
	TreeNodeLogFunction(TreeNodePtr arg){
		argument = arg;
	}
	virtual double evaluate( double x );
	virtual TreeNodePtr differentiate( );
	virtual TreeNodePtr duplicate( );
	virtual std::string to_string(){
		return "log(" + argument->to_string() + ")";
	}
	virtual int precedence(){ return 1; }
private:
	TreeNodePtr argument;
};


/* TreeNodeSinFunction represents the sin() function */
class TreeNodeSinFunction: public TreeNode{
public:
	TreeNodeSinFunction(TreeNodePtr arg){
		argument = arg;
	}
	virtual double evaluate(double x);
	virtual TreeNodePtr differentiate( );
	virtual TreeNodePtr duplicate( );
	virtual std::string to_string(){
		return "sin(" + argument->to_string() + ")";
	}
	virtual int precedence(){ return 1; }
private:
	TreeNodePtr argument;
};


/* TreeNodeCosFunction represents the cos() function */
class TreeNodeCosFunction: public TreeNode{
public:
	TreeNodeCosFunction(TreeNodePtr arg){
		argument = arg;
	}
	virtual double evaluate( double x );
	virtual TreeNodePtr differentiate( );
	virtual TreeNodePtr duplicate( );
	virtual std::string to_string(){
		return "cos(" + argument->to_string() + ")";
	}
	virtual int precedence(){ return 1; }
private:
	TreeNodePtr argument;
};






//Defined in parser.cpp
TreeNodePtr parse_expression( std::string expression_string );

#endif