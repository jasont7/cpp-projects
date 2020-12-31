#include <string>
#include <cmath> //For exp(), log(), sin(), cos() and pow()
#include "expression_tree.hpp"


/* Constant */
double TreeNodeConstant::evaluate(double x) {
    // we do not use the x, so we ignore it
    // this stops the compiler from issuing a parameter non-used warning/error
    std::ignore = x;
	return this->constant_value;
}
TreeNodePtr TreeNodeConstant::differentiate(){
	//Derivative of a constant is 0
	TreeNodePtr diffNode = std::make_shared<TreeNodeConstant>(0);
	return diffNode;
}
TreeNodePtr TreeNodeConstant::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeConstant>(this->constant_value);
	return duplicate;
}


/* Literal X */
double TreeNodeX::evaluate(double x){
	return x;
}
TreeNodePtr TreeNodeX::differentiate(){
	//Derivative of x is 1
	TreeNodePtr diffNode = std::make_shared<TreeNodeConstant>(1);
	return diffNode;
}
TreeNodePtr TreeNodeX::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeX>();
	return duplicate;
}


/* Plus operator */
double TreeNodePlus::evaluate(double x) {
	double leftEval = this->left->evaluate(x);
	double rightEval = this->right->evaluate(x);
	return leftEval + rightEval;
}
TreeNodePtr TreeNodePlus::differentiate() {
	//Derivative of a + b is the sum of the derivatives of each.
	TreeNodePtr diffNode = std::make_shared<TreeNodePlus>(this->left->differentiate(), this->right->differentiate());
	return diffNode;
}
TreeNodePtr TreeNodePlus::duplicate() {
	TreeNodePtr duplicate = std::make_shared<TreeNodePlus>(this->left->duplicate(), this->right->duplicate());
	return duplicate;
}


/* Minus operator */
double TreeNodeMinus::evaluate( double x ){
	double leftEval = this->left->evaluate(x);
	double rightEval = this->right->evaluate(x);
	return leftEval - rightEval;
}
TreeNodePtr TreeNodeMinus::differentiate(){
	//Derivative of a - b is the difference of the derivatives of each.
	TreeNodePtr diffNode = std::make_shared<TreeNodeMinus>(this->left->differentiate(), this->right->differentiate());
	return diffNode;
}
TreeNodePtr TreeNodeMinus::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeMinus>(this->left->duplicate(), this->right->duplicate());
	return duplicate;
}


/* Multiplication operator */
double TreeNodeMultiply::evaluate(double x){
	double leftEval = this->left->evaluate(x);
	double rightEval = this->right->evaluate(x);
	return leftEval * rightEval;
}
TreeNodePtr TreeNodeMultiply::differentiate(){
	// (a * b)' = (a' * b) + (a * b')
	TreeNodePtr diffLeft = std::make_shared<TreeNodeMultiply>(this->left->differentiate(), this->right->duplicate());
	TreeNodePtr diffRight = std::make_shared<TreeNodeMultiply>(this->left->duplicate(), this->right->differentiate());
	TreeNodePtr diffNode = std::make_shared<TreeNodePlus>(diffLeft, diffRight);
	return diffNode;
}
TreeNodePtr TreeNodeMultiply::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeMultiply>(this->left->duplicate(), this->right->duplicate());
	return duplicate;
}


/* Division operator */
double TreeNodeDivide::evaluate(double x){
	double leftEval = this->left->evaluate(x);
	double rightEval = this->right->evaluate(x);
	return leftEval / rightEval;
}
TreeNodePtr TreeNodeDivide::differentiate(){
	// (a / b)' = ((a' * b) - (a * b')) / b^2
	TreeNodePtr dll = std::make_shared<TreeNodeMultiply>(this->left->differentiate(), this->right->duplicate());
	TreeNodePtr dlr = std::make_shared<TreeNodeMultiply>(this->left->duplicate(), this->right->differentiate());
	TreeNodePtr dl = std::make_shared<TreeNodeMinus>(dll, dlr);
	TreeNodePtr dr = std::make_shared<TreeNodeConstantPower>(this->right->duplicate(), 2);

	TreeNodePtr diffNode = std::make_shared<TreeNodeDivide>(dl, dr);
	return diffNode;
}
TreeNodePtr TreeNodeDivide::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeDivide>(this->left->duplicate(), this->right->duplicate());
	return duplicate;
}


/* Constant power operator (the exponent will always be a fixed value) */
double TreeNodeConstantPower::evaluate(double x){
	double baseEval = this->left->evaluate(x);
	return std::pow(baseEval, this->exponent);
}
TreeNodePtr TreeNodeConstantPower::differentiate(){
	// (a ^ c)' = (c * a') * (a ^ (c-1))
	TreeNodePtr expNode = std::make_shared<TreeNodeConstant>(this->exponent);
	TreeNodePtr dl = std::make_shared<TreeNodeMultiply>(expNode, this->left->differentiate());
	TreeNodePtr dr = std::make_shared<TreeNodeConstantPower>(this->left->duplicate(), (this->exponent)-1);
	TreeNodePtr diffNode = std::make_shared<TreeNodeMultiply>(dl, dr);
	return diffNode;
}
TreeNodePtr TreeNodeConstantPower::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeConstantPower>(this->left->duplicate(), this->exponent);
	return duplicate;
}


/* exp function */
double TreeNodeExpFunction::evaluate(double x){
	double argEval = this->argument->evaluate(x);
	return std::exp(argEval);
}
TreeNodePtr TreeNodeExpFunction::differentiate(){
	// (exp(f(x)))' = (exp(f(x))) * f'(x)
	TreeNodePtr dl = std::make_shared<TreeNodeExpFunction>(this->argument->duplicate());
	TreeNodePtr diffNode = std::make_shared<TreeNodeMultiply>(dl, this->argument->differentiate());
	return diffNode;
}
TreeNodePtr TreeNodeExpFunction::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeExpFunction>(this->argument->duplicate());
	return duplicate;
}


/* log function */
double TreeNodeLogFunction::evaluate(double x){
	double argEval = this->argument->evaluate(x);
	return std::log(argEval);
}
TreeNodePtr TreeNodeLogFunction::differentiate(){
	// (log(f(x)))' = f'(x) / f(x)
	TreeNodePtr diffNode = std::make_shared<TreeNodeDivide>(this->argument->differentiate(), this->argument->duplicate());
	return diffNode;
}
TreeNodePtr TreeNodeLogFunction::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeLogFunction>(this->argument->duplicate());
	return duplicate;
}


/* sin function */
double TreeNodeSinFunction::evaluate(double x){
	double argEval = this->argument->evaluate(x);
	return std::sin(argEval);
}
TreeNodePtr TreeNodeSinFunction::differentiate(){
	// (sin(f(x)))' = cos(f(x)) * f'(x)
	TreeNodePtr cosNode = std::make_shared<TreeNodeCosFunction>(this->argument->duplicate());
	TreeNodePtr diffNode = std::make_shared<TreeNodeMultiply>(cosNode, this->argument->differentiate());
	return diffNode;
}
TreeNodePtr TreeNodeSinFunction::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeSinFunction>(this->argument->duplicate());
	return duplicate;
}


/* cos function */
double TreeNodeCosFunction::evaluate(double x){
	double argEval = this->argument->evaluate(x);
	return std::cos(argEval);
}
TreeNodePtr TreeNodeCosFunction::differentiate(){
	// (cos(f(x)))' = -1 * (sin(f(x)) * f'(x))
	TreeNodePtr dl = std::make_shared<TreeNodeConstant>(-1);
	TreeNodePtr sinNode = std::make_shared<TreeNodeSinFunction>(this->argument->duplicate());
	TreeNodePtr dr = std::make_shared<TreeNodeMultiply>(sinNode, this->argument->differentiate());

	TreeNodePtr diffNode = std::make_shared<TreeNodeMultiply>(dl, dr);
	return diffNode;
}
TreeNodePtr TreeNodeCosFunction::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeCosFunction>(this->argument->duplicate());
	return duplicate;
}