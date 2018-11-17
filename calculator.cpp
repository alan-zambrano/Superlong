#include <iostream>
#include <string>
#include <cctype>   //isdigit()
#include <cmath>    //pow()
#include <algorithm>//remove_if()

bool isop(char op){
	return op == '*' || op == '/' || op == '+' || op == '-' || op == '^';
}
int solveBinom(int L, char op, int R){
	if(!isop(op)){
		std::cout << "invalid op " << op << std::endl;
		exit(0);
	}
	if(op == '*')
		return L * R;
	else if(op == '/')
		return L/R;
	else if(op == '+')
		return L+R;
	else if(op == '-')
		return L-R;
	else if(op == '^')
		return pow(L,R);
}
//expressions should follow the following regex
//digit|"("(op|")")
int solveExpr(std::string::iterator& iter, std::string& expr){
	int currVal = 0;
	char currOp = '+';


	while(iter != expr.end()){
		int RHS = 0;
		//parse digit
		if(isdigit(*iter)){
			for(; isdigit(*iter); ++iter){
				RHS <<= 1;
				RHS += *iter - '0';
			}
			currVal = solveBinom(currVal, currOp, RHS);
		}
		else if(*iter == '('){
			currVal = solveBinom(currVal, currOp, solveExpr(++iter, expr));
		}
		else{
			std::cout << "wrong order of char " << *iter <<  std::endl;
			exit(0);
		}
		//this condition is not working
		if(iter == expr.end()){
			return currVal;
		}

		if(isop(*iter)){
			currOp = *iter;
			++iter;
		}
		else if(*iter == ')'){
			++iter;
			return currVal;
		}
		else{
			std::cout << "wrong order of char " << *iter << std::endl;
			exit(0);
		}
	}
}

int main(){
	std::string expr;
	
	std::cin >> expr;
	//remove whitespace
	//https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
	expr.erase(std::remove_if(expr.begin(), expr.end(), isspace), expr.end());
	std::string::iterator iter = expr.begin();
	//int ans = solveExpr(iter, expr);
	std::cout << solveExpr(iter, expr) << std::endl;
} 
