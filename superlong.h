#ifndef SUPERLONG_H
#define SUPERLONG_H

#include <string>
#include <cstdlib>
#include <vector>

class Superlong{
	private:
	char* val;

	public:
	/***********Constructors***********/
	Superlong();
	Superlong(std::string numstr);
	Superlong(const Superlong& obj);
	~Superlong();
	const int getSize() const;
	/************Assignment************/
	Superlong& operator=(const Superlong& rhs);
	Superlong& operator=(const std::string& rhs);
	/************Comparison************/
	bool operator==(const Superlong& rhs) const;
	bool operator==(const std::string& rhs) const;
	bool operator<(const Superlong& rhs) const;
	bool operator>(const Superlong& rhs) const;
	/************Increments************/
	Superlong& operator++();
	/*********Math Operations**********/
	const Superlong operator+(const Superlong& rhs);
	const Superlong operator-(const Superlong& rhs);
	const Superlong operator*(const Superlong& rhs);
	/**************Stream**************/
	friend std::ostream& operator<<(std::ostream& os, const Superlong& obj);
	/**************Helper**************/
	friend Superlong multHelper(const Superlong& lhs, const Superlong& rhs);
};
#endif
