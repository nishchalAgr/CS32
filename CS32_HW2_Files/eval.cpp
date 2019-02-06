#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

//int test = 0;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result);
bool checkString(string temp, const Set& trueValues, const Set& falseValues, int& x);
int order(char a);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {

	postfix = "";

	//cout << "test #" << test << endl;
	//test++;

	string temp;
	for (int i = 0; i < infix.size(); i++) {

		if (infix[i] != ' ')
			temp += infix[i];

	}

	infix = temp;

	int ans = 0;

	stack<ItemType> oper;

	//cout << 1 << endl;

	if (!checkString(infix, trueValues, falseValues, ans) && ans != 2 && ans != 3) return 1;

	//cout << 1 << endl;

	if (ans == 2) return ans;

	//cout << 1 << endl;
	
	if (ans == 3) return ans;

	//cout << 1 << endl;

	for (int i = 0; i < infix.size(); i++) {
	
		char current = infix[i];

		if (isalpha(current) || current == '(') oper.push(current);

		else if (current == ')') {
		
			while (oper.top() != '(' && !oper.empty()) {
			
				postfix += oper.top();
				oper.pop();
			
			}
		
			oper.pop();

		}

		else if (current == '!' || current == '&' || current == '|') {
		
			while (!oper.empty() && oper.top() != '(' && order(current) <= order(oper.top())) {
			
				postfix += oper.top();
				oper.pop();
			
			}
	
			oper.push(current);

		}

	}

	while (!oper.empty()) {
	
		postfix += oper.top();
		oper.pop();
	
	}

	stack<bool> operand;

	bool operA;
	bool operB;

	for (int i = 0; i < postfix.size(); i++) {
	
		if (isalpha(postfix[i])) {
		
			if (trueValues.contains(postfix[i])) operand.push(true);

			else if (falseValues.contains(postfix[i])) operand.push(false);
		
		}

		else {
		
			if (postfix[i] == '!') {
			
				operand.top() = !operand.top();
			
			}

			else {

				operA = operand.top();
				operand.pop();

				operB = operand.top();
				operand.pop();

				if (postfix[i] == '|') operand.push(operA | operB);

				else if (postfix[i] == '&') operand.push(operA && operB);
			}
		
		}
	
	}

	/*cout << "postfix: " << postfix << endl;
	cout << "result: " << result << endl;
	cout << endl << endl;*/

	result = operand.top();
	return 0;

}

bool isOperator(char a) {

	return (a == '(' || a == ')' || a == '|' || a == '&' || a == '!');

}

bool checkString(string temp, const Set& trueValues, const Set& falseValues, int& x) {

	if (temp == "") return false;

	int open = 0;
	int close = 0;

	bool tVal;
	bool fVal;

	for (int i = 0; i < temp.size(); i++) {
	
		tVal = trueValues.contains(temp[i]);
		fVal = falseValues.contains(temp[i]);

		if (isalpha(temp[i]) && !tVal && !fVal) { 
		
			x = 2;  
			return false;

		}
		
		if (isalpha(temp[i]) && tVal && fVal) { 
		
			x = 3;
			return false;

		}

		if (!isalpha(temp[i]) && (temp[i] != '(' && temp[i] != ')' && temp[i] != '|' && temp[i] != '&' && temp[i] != '!'))

		if (isupper(temp[i]) || isdigit(temp[i])) return false;

		if (i != temp.size() - 1 && isalpha(temp[i]) && isalpha(temp[i + 1])) return false;

		if (temp[i] == '&') {
		
			if (i == temp.size()) return false;

			if (temp[i + 1] != '(' && temp[i + 1] != '!' && isOperator(temp[i + 1])) return false;
		
		}

		else if (temp[i] == '|') {

			if (i == temp.size() - 1) return false;

			if (temp[i + 1] != '(' && temp[i + 1] != '!' && isOperator(temp[i+1])) return false;

		}

		else if (temp[i] == '!') {
		
			if (i == temp.size() - 1) return false;

			if (temp[i + 1] == '&' || temp[i + 1] == '|') return false;
		
		}

		else if (temp[i] == '(') {
		
			open++;
			if (i == temp.size() - 1) return false;

			if (i != 0 && isalpha(temp[i - 1])) return false;

			if (temp[i + 1] == ')') return false;
		
		}

		else if (temp[i] == ')') {
		
			close++;
			if (i != temp.size() - 1 && temp[i + 1] == '(') return false;

			if (temp[i + 1] == '!') return false;
		
		}
	
	}

	return (open == close);

}

int order(char a) {
	
	switch (a) {
	
		case '!': return 3;
		case '&': return 2;
		case '|': return 1;
	
	}

}

//int main()
//{
//	string truechars = "tywz";
//	string falsechars = "fnx";
//	set trues;
//	set falses;
//	for (int k = 0; k < truechars.size(); k++)
//		trues.insert(truechars[k]);
//	for (int k = 0; k < falsechars.size(); k++)
//		falses.insert(falsechars[k]);
//
//	string pf;
//	bool answer;
//	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" &&  answer);//0
//	assert(evaluate("y|", trues, falses, pf, answer) == 1);//1
//	assert(evaluate("n t", trues, falses, pf, answer) == 1);//2
//	assert(evaluate("nt", trues, falses, pf, answer) == 1);//3
//	assert(evaluate("()", trues, falses, pf, answer) == 1);//4
//	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);//5
//	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);//6
//	assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);//7
//	assert(evaluate("", trues, falses, pf, answer) == 1);//8
//	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
//		&& pf == "ff!tn&&|" && !answer); //9
//	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);//10
//	trues.insert('x');
//	assert(evaluate("((x))", trues, falses, pf, answer) == 3);//11
//	falses.erase('x');
//	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x"  &&  answer);//12
//	trues.erase('w');
//	assert(evaluate("w| f", trues, falses, pf, answer) == 2);//13
//	falses.insert('w');
//	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);//14
//	cout << "passed all tests" << endl;
//}
