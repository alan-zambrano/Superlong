#include "superlong.h"
#include <iostream>
#include <cstdlib> //malloc(), free()
#include <cctype>  //isdigit()
#define MAX_SIZE 30

int min(int a, int b){
	return a>b?b:a;
}

int max(int a, int b){
	return a>b?a:b;
}

bool isValid(std::string s){
	for(std::string::iterator iter = s.begin(); iter != s.end(); iter++){
		if(!isdigit(*iter)){
			return false;
		}
	}
	return true;
}

/****Default Constructor****/
Superlong::Superlong(){
	//std::cout << "created object " << this << std::endl;
	val = (char*)malloc(sizeof(char)*MAX_SIZE);
	for(int i = 0; i < MAX_SIZE; i++){
		val[i] = '0';
	}
}
/****Parameterized Constructor(string)****/
Superlong::Superlong(std::string numstr){
	//std::cout << "created object " << this << std::endl;
	if(!isValid(numstr)){
		std::cout << "invalid string constructor" << std::endl;
		exit(0);
	}
	if(numstr.size() > MAX_SIZE){
		std::cout << "string greater than max capacity" << std::endl;
	}
	val = (char*)malloc(sizeof(char)*MAX_SIZE);
	std::string::reverse_iterator rit = numstr.rbegin();
	int i = 0;

	for(; rit != numstr.rend(); rit++, i++){
		this->val[i] = *rit;
	}
	for(;i < MAX_SIZE; i++){
		this->val[i] = '0';
	}
}
/****Copy Constructor****/
Superlong::Superlong(const Superlong& obj){
	//std::cout << "created object " << this << std::endl;
	val = (char*)malloc(sizeof(char)*MAX_SIZE);
	for(int i = 0; i < MAX_SIZE; i++){
		this->val[i] = obj.val[i];
	}
}

Superlong::~Superlong(){
	//std::cout << "destroyed object " << this << std::endl;
	free(val);
}

const int Superlong::getSize() const{
	for(int i = MAX_SIZE -1; i >= 0; --i){
		if(this->val[i] != '0'){
			return i+1;
		}
	}
	return 0;
}

Superlong& Superlong::operator=(const Superlong& rhs){
	//check for self assignment
	if(this == &rhs){
		return *this;
	}
	for(int i = 0; i < MAX_SIZE; i++){
		this->val[i] = rhs.val[i];
	}
	return (*this);
}

Superlong& Superlong::operator=(const std::string& rhs){
	if(!isValid(rhs)){
		std::cout << "invalid string assignment" << std::endl;
		exit(0);
	}
	if(rhs.size() > MAX_SIZE){
		std::cout << "rhs assignment greater than max capacity" << std::endl;
	}
	std::string::const_reverse_iterator rit = rhs.rbegin();
	int i = 0;
	for(; rit != rhs.rend(); rit++, i++){
		this->val[i] = *rit;
	}
	for(;i < MAX_SIZE; i++){
		this->val[i] = '0';
	}
	return (*this);
}

bool Superlong::operator==(const Superlong& rhs) const{
	for(int i = 0; i < MAX_SIZE; i++){
		if(this->val[i] != rhs.val[i])
			return false;
	}
	return true;
}

bool Superlong::operator==(const std::string& rhs) const{
	if(rhs.size() != this->getSize()){
		return false;
	}
	int thisInd = 0;
	std::string::const_reverse_iterator rit = rhs.rbegin();
	for(; rit != rhs.rend(); rit++, thisInd++){
		if(*rit != this->val[thisInd]){
			return false;
		}
	}
	return true;
}

bool Superlong::operator<(const Superlong& rhs) const{
	for(int i = MAX_SIZE-1; i >= 0; i--){
		if(this->val[i] < rhs.val[i])
			return true;
		else if(this->val[i] > rhs.val[i])
			return false;
	}
	return false;
}

bool Superlong::operator>(const Superlong& rhs) const{
	for(int i = MAX_SIZE-1; i >= 0; i--){
		if(this->val[i] > rhs.val[i])
			return true;
		else if(this->val[i] < rhs.val[i])
			return false;
	}
	return false;
}

Superlong& Superlong::operator++(){
	bool carry = false;
	int i = 0;
	do{
		if(i >= 30){
			std::cout << "overflow" << std::endl;
			exit(0);
		}
		carry = this->val[i] == '9';
		if(carry){
			this->val[i] = '0';
		}
		else{
			this->val[i]++;
			break;
		}
		i++;

	}while(carry);

	return *this;
}

const Superlong Superlong::operator+(const Superlong& rhs){
	bool carry = false;
	Superlong result;

	for(int i = 0; i < MAX_SIZE; i++){
		result.val[i] = (this->val[i]-'0' + rhs.val[i]-'0' + carry) % 10 + '0';
		carry = (this->val[i]-'0' + rhs.val[i]-'0' + carry) > 9;
	}
	if(carry){
		std::cout << "overflow" << std::endl;
	}

	return result;
}

const Superlong Superlong::operator-(const Superlong& rhs){
	bool carry = false;
	int res;
	Superlong result;
	if(*this < rhs){
		std::cout << "underflow" << std::endl;
		exit(0);
	}

	for(int i = 0; i < MAX_SIZE; i++){
		res = ((this->val[i]) - (rhs.val[i]) - carry);
		carry = res < 0;
		if(carry)
			result.val[i] = res + 10 + '0';
	}
	if(carry){
		std::cout << "cannot return negative number" << std::endl;
		exit(0);
	}
	return result;
}
const Superlong multHelper(const Superlong& lhs, const Superlong& rhs){
	Superlong result;
	for(Superlong i("0"); i < rhs; ++i){
		result = result + lhs;
	}
	return result;
}
const Superlong Superlong::operator*(const Superlong& rhs){
	Superlong result;
	if(rhs == "0" || *this == "0"){
		return result;
	}
	if(rhs == "1"){
		return *this;
	}else if(*this == "1"){
		return rhs;
	}
	for(Superlong i("0"); i < rhs; ++i){
		result = result + *this;
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Superlong& obj){
	for(int i = obj.getSize()-1; i >= 0; i--){
		os << obj.val[i];
	}
	return os;
}
