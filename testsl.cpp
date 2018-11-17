#include <iostream>
#include "superlong.h"

int main(){
	Superlong a("251235489720");
	Superlong b("5264");
	Superlong c;
	c = a*b;
	std::cout << c << std::endl;
	++c;
	std::cout << c << std::endl;
}
