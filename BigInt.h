#pragma once

#include <iostream>
#include <string> //getline
#include <vector>

using namespace std;

class BigInt {
private:
	bool type;	//0:Integer	1:Decimal
	bool sign;  //0:正 1:負
	string name;
	string digits;
	int dotPlace;
	static vector<BigInt*> All; //存所有變數

public:
	BigInt() { name = ""; };
	BigInt(string n) { name = n; };
	BigInt(bool, string, string);

	void process(string);
	BigInt operator+(BigInt) const;
	BigInt operator-(const BigInt rhs) const;
	BigInt operator*(const BigInt rhs) const;
	BigInt operator/(const BigInt rhs) const;
	void operator=(const BigInt&);

	void setType(bool t) { type = t; }
	void setSign(bool s) { sign = s; }
	void setDigits(string dgt) { digits = dgt; }
	void setDotPlace(int d) { dotPlace = d; }

	friend ostream& operator<<(ostream&, const BigInt&);
};
