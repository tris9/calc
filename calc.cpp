#include "MyVector.h"
#include "MyStack.h"
#include "MyQueue.h"
#include <string>
#include <stdlib.h>

/**
 * calc.cpp
 * A simple infix arithmetic expression evaluator
 * Uses Dijkstra's Shunting-yard Algorithm to transform infix to postfix
 * then evaluate it. Currently supports operators +,-,*,/ and parenthesis ()
 *
 **/

using namespace std;

/**
 * Checks if the string str contains char c
 * @params 
 * string str, the string to check
 * char c, the char to check for
 * @return
 * true if char c is contained in the string str, false otherwise
 **/
bool contains(string str, char c){
	for(unsigned int i = 0; i < str.length(); i++){
		if(str[i] == c){
			return true;
		}
	}
	return false;
}

/**
 * Checks if char c is one of the valid operators
 * @param
 * char c, the char to check
 * @return
 * true if c is one of +,-,*,/ and false otherwise
 **/
bool isOperator(char c){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
 * Checks if operator a has higher or equal precedence than operator b
 * Precedence is order as: * >= / > + >= -
 * @param
 * char a, the first char to compare against
 * char b, the second char to compare
 * @return
 * true if a has higher precendence than b
 **/
bool compOperator(char a, char b){
	return ((a == '*' || a == '/') && (b == '+' || b == '-')) || (a == b) || (a == '+' && b == '-') || (a == '-' && b == '+') || (a == '*' && b == '/') || (a == '/' && b == '*');
}

/**
 * Checks if the character array str can be formatted as a double
 * @param
 * char* str, the character array to check
 * @return
 * returns true if that char array can be formatted as a double and
 * false otherwise
 **/
bool isDouble(const char* str)
{
    char* endptr = 0;
    strtod(str, &endptr);

    if(*endptr != '\0' || endptr == str)
        return false;
    return true;
}

/**
 * Arranges a string into a queue broken up by numbers and operators
 * @param
 * string str, the string to transform
 * MyQueue<string> *q, a pointer to the queue to store the transformed
 * string
 * @returns
 * populates q with strings representing numbers and operators
 * returns an integer representing either success (0) or an error code
 **/
int strToQueue(string str, MyQueue<string> *q){
	
	string num = "";
	
	//iterate through entire string
	for(unsigned int i = 0; i < str.length(); i++){
		if(isdigit(str[i])){	//if its a digit add it to the current string
			num.push_back(str[i]);
		}else if(str[i] == '.'){	//a dot counts as part as a number but only once
			if(contains(num,str[i])){	//error if malformed number
				return -1;
			}else{
				num.push_back(str[i]);
			}	
		}else if(isOperator(str[i])){	//if we hit an operator then enqueue the number and the operator seperately
			if(i == 0 || i == str.length() - 1){
				return -1;
			}else if(str[i-1] == '(' && str[i] == '-'){
				num.push_back(str[i]);
			}else if(str[i-1] == '(' || str[i-1] == ')'){
				num.push_back(str[i]);
				q->push(num);
				num = "";
			}else{
				q->push(num);
				num = "";
				num.push_back(str[i]);
				q->push(num);
				num = "";
			}
		}else if(str[i] == '(' || str[i] == ')'){	//if we hit a bracket we break and add the number
			if(i == 0){
				num.push_back(str[i]);
				q->push(num);
				num = "";
			}else if(isdigit(str[i-1])){
				q->push(num);
				num = "";
				num.push_back(str[i]);
				q->push(num);
				num = "";
			}else{
				num.push_back(str[i]);
				q->push(num);
				num = "";
			}
		}else{ //error if invalid character
			return -2;
		}
	}
	
	//check if the we have only a single number
	if(str.length() != 0 && str[str.length() - 1] != ')'){
		q->push(num);
	}

	return 0;
}

/**
 * Transforms qIn in infix notation and stores it into
 * qOut in postfix notation
 * @param
 * MyQueue<string> *qIn, a pointer to a queue storing an
 * expression in infix notation
 * MyQueue<string> *qOut, a pointer to a queue storing the
 * result of the expression in postfix notation
 * @return
 * returns the qOut populated with the expression from qIn
 * in postfix notation. Also returns an int representing
 * an error code
 **/
int postfix(MyQueue<string> *qIn, MyQueue<string> *qOut){
	
	MyStack<string> *op = new MyStack<string>();

	while(!qIn->isEmpty()){		//iterate through input queue
		string token = qIn->pop();
		if(isDouble(&token[0])){	//if its a double add to output queue
			qOut->push(token);
		}else if(isOperator(token[0])){		//if its a operator add to operator stack
			while(!op->isEmpty() && compOperator(op->peek()[0],token[0])){	//check precedence of operators
				qOut->push(op->pop());
			}
			op->push(token);
		}else if(token[0] == '('){	//add left bracket to operator stack
			op->push(token);
		}else if(token[0] == ')'){	//if we hit a right bracket pop until left bracket
			while(!op->isEmpty() && op->peek()[0] != '('){
				qOut->push(op->pop());	
			}
			if(op->isEmpty()){	//error if our op stack is empty and we still have a bracket
				return -1;
			}else if(op->peek()[0] == '('){	//discard left bracket
				op->pop();
			}
		}else{	//error if the expression is not correct
			return -2;
		}	
	}
	
	//pop off the rest of the operator stack
	while(!op->isEmpty()){
		if(op->peek()[0] == '(' || op->peek()[0] == ')'){
			return -1;
		}
		qOut->push(op->pop());
	}

	delete op;
	op = NULL;

	return 0;
}

/**
 * Evaluates the queue q in postfix notation to a 
 * double value
 * @param
 * MyQueue<string> *q, a pointer to a queue in postifix notation
 * @return
 * returns a double which is the result of evaluating the 
 * postfix notation
 **/
double evaluate(MyQueue<string> *q){
	MyStack<double> *eval = new MyStack<double>();
	double result = 0;
	while(!q->isEmpty()){	//iterate through entire queue
		if(isDouble(&q->peek()[0])){	//if its a number, convert it and push it to the eval stack
			eval->push(atof(&q->pop()[0]));
		}else{		//otherwise its and operator and we evalute the last two pushed values
			string token = q->pop();
			double b = eval->pop();
			double a = eval->pop();;
			switch(token[0]) {
				case '+':	
					result = a + b;					
					break;
			  	case '-':
			    		result = a - b;
					break;
				case '*':
					result = a * b;
				       break;
				case '/':
					result = a / b;
					break;       
				default:
					result = 0.0;
			    		break;
			}
			eval->push(result);
		}
	}
	result = eval->pop();
	delete eval;
	eval = NULL;	
	return result;
}

/**
 * The main driver code, gets an infix expression from the user
 * and evaluates it by transforming it to postfix notation. Runs
 * in an infinite loop and only exits if the user types "exit"
 **/
int main(){

	string str;
	while(1){
		cout << "Enter an expression: " << endl;
		cin >> str;
		cout << endl;
		
		if(str.compare("exit") == 0){
			break;
		}

		MyQueue<string> *queue = new MyQueue<string>();
		
		MyQueue<string> *outQueue = new MyQueue<string>();

		int err = strToQueue(str,queue);
		
		if(err == 0){
			
			err = postfix(queue, outQueue);

			if(err == 0){
				double val = evaluate(outQueue);
				cout << "Result: " << val << endl;
			}else{
				if(err == -1){
					cout << "ERROR: Mismatched Parenthesis" << endl;
				}else if(err == -2){
					cout << "ERROR: Malformed Expression" << endl;
				}
			}
			
		}else{
			if(err == -1){
				cout << "ERROR: Malformed Number" << endl;
			}else if(err == -2){
				cout << "ERROR: Invalid Character" << endl;
			}
		}

		delete queue;
		queue = NULL;	

		delete outQueue;
		outQueue = NULL;

	}
	return 0;
}
