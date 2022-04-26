#include "BigInt.h"

vector<BigInt*> BigInt::All;

BigInt::BigInt(bool t, string n, string d)
{
	this->type = t;
	this->name = n;
	this->digits = d;
	//dotPlace
}

void BigInt::process(string s)
{
	//"1.5 + 3 * ( -(-5) )"
	string nowStr;
	string nextStr;
	vector<int> paren[2];//左右括弧
	int j = 0;
	int now;
	for (int i = 0; i < s.length(); i++)		//從右括弧編號最大開始做
	{
		if (s[i] == '(')
		{
			paren[0].push_back(i);
			paren[1].push_back(-1);
			now = paren[0].size() - 1;
		}
		if (s[i] == ')')
		{
			while (paren[1][now] != -1)
				now--;
			paren[1][now] = i;
		}
	}
	//reverse(paren[1].begin(), paren[1].end());
	//優先權:從reverse.back開始實作

	BigInt ans;
	for (int i = paren[0].size() - 1; i >= 0; i--)
	{
		for (int j = paren[0][i] + 1; j < paren[1][i]; j++)
		{
			if (s[j] == '+' || s[j] == '-' || s[j] == '*' || s[j] == '/')
			{
				nextStr = "";//1+3.14
				//input until not dot or num

			}
			else
			{
				nowStr += s[j];
			}

		}
	}

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
		{
			switch (s[j])
			{
			case '!'://階乘

				break;
			case '^'://power

				break;
			default:
				nowStr += s[i];
			};
		}

	}

}

BigInt BigInt::operator+(const BigInt rhs) const
{
	BigInt ans;
	if (type || rhs.type)//至少一個是decimal -> 輸出decimal
	{
		ans.type = 1;
	}


}

BigInt BigInt::operator-(const BigInt rhs) const
{

}

BigInt BigInt::operator*(const BigInt rhs) const
{

}

//  (1 / 3) * 3 = 1 -> 先乘後除
BigInt BigInt::operator/(const BigInt rhs) const	// (digit - '0') / (rhs.digit - '0') -> A / B
{
	BigInt c;
	bool ansType;		
	bool ansSign;		
	string ansDigits = "";
	int ansDotPlace;

	int lenA = digits.size();
	int lenB = rhs.digits.size();

	string A = digits;
	string B = rhs.digits;
	string tempStr = A;
	string remain;

	if (A == "0") {
		ansDigits = "0";
		c.setDigits(ansDigits);
		return c;
	}
	if (B == "0") {
		ansDigits = "default";		// 錯誤
		c.setDigits(ansDigits);
		return c;
	}


	if (sign == 0 && rhs.sign == 0) {
		ansSign = 0;		//正數
	}
	else {
		ansSign = 1;		//負數
	}


	if (lenA > lenB) {
		// if 12,345,678 / 234,567 then ansDigits = 52 ; remain 148,194
		while (tempStr = substraction(tempStr, B) >= '0') {		// A - B = tempStr
			ansDigits = addition(ansDigits, 1);			
		}
	}
	else if (lenA == lenB) {
		bool chkAB = false;		// chkAB = false if A < B
		int dotA;
		int dotB;
		for (int i = 0; i < lenA; i++) {
			if (A[i] == '.') {
				dotA = i;
			}
			if (B[i] == '.') {
				dotB = i;
			}
		}
		if (dotA > dotB) {
			chkAB = true;
		}
		else {		// dotA == dotB
			for (int i = 0; i < lenA; i++) {
				if (A[i] - '0' > B[i] - '0') {
					chkAB = true;
					break;
				}
				else if (A[i] - '0' < B[i] - '0') {
					break;
				}
			}
		}
		if (chkAB == true) {
			//if 23,456,789 / 12,345,678 then ansDigits = 1 ; remain 11,111,111
			while (tempStr = substraction(tempStr, B) >= '0') {		// tempStr = A - B
				ansDigits = addition(ansDigits, 1);
			}
		}
		else {		// chk = false ; lenA = lenB ; A < B
			ansDigits += "0.";
			A += "0";
			// now A > B
			tempStr = A;
			while (tempStr = substraction(tempStr, B) >= '0') {		// A - B = tempStr
				//ansDigits 小數位數接下去
			}
		}
	}
	else {		// lenA < lenB ; A < B
		ansDigits += "0.";
		A += "0";
		int countZero = 0;
		if (A[0] > B[0]) {		// for example : 234567 / 12345678 = 0.0189999286
			countZero = lenB - lenA - 1;
			while (countZero > 0) {
				ansDigits += "0";
				A += "0";
				countZero--;
			}
			// now A > B
			tempStr = A;
			while (tempStr = substraction(tempStr, B) >= '0') {		// A - B = tempStr
				//ansDigits 小數位數接下去
			}
		}
		else if (A[0] < B[0]) {		// for example : 123456 / 23456789 = 0.0052631245
			countZero = lenB - lenA;
			while (countZero > 0) {
				ansDigits += "0";
				A += "0";
				countZero--;
			}
			// now A > B
			tempStr = A;
			while (tempStr = substraction(tempStr, B) >= '0') {		// A - B = tempStr
				//ansDigits 小數位數接下去
			}
		}
	}

	// 有餘數 -> ansDigits以小數下100位回傳
	if (tempStr != "0") {
		remain = tempStr;		// ansDigits += remain / B
		ansType = 1;		//小數
		ansDigits += ".";
		// remain < B ; lenRemain = or < lenB 
		if (int lenRemain = remain.length() == lenB) {
			remain += "0";
			// now remain > B
			while (remain = substraction(remain, B) >= '0') {		// A - B = tempStr
				//ansDigits 小數位數接下去
			}
		}
		else {
			remain += "0";
			int countZero = 0;
			lenRemain = remain.length();
			if (remain[0] > B[0]) {		// for example : 234567 / 12345678 = 0.0189999286
				countZero = lenB - lenRemain - 1;
				while (countZero > 0) {
					ansDigits += "0";
					remain += "0";
					countZero--;
				}
				// now remain > B
				while (remain = substraction(remain, B) >= '0') {		// A - B = tempStr
					//ansDigits 小數位數接下去
				}
			}
			else if (remain[0] < B[0]) {		// for example : 123456 / 23456789 = 0.0052631245
				countZero = lenB - lenRemain;
				while (countZero > 0) {
					ansDigits += "0";
					remain += "0";
					countZero--;
				}
				// now remain > B
				while (remain = substraction(remain, B) >= '0') {		// A - B = tempStr
					//ansDigits 小數位數接下去
				}
			}
		}

		for (int i = 0; i < ansDigits.length(); i++) {
			if (ansDigits[i] == '.') {
				ansDotPlace = i;
				break;
			}
		}
	}

	// 沒餘數
	else {
		ansType = 0;		//整數
		ansDotPlace = 0;
	}

	c.setType(ansType);
	c.setSign(ansSign);
	c.setDigits(ansDigits);			// how to return in decimal ?
	c.setDotPlace(ansDotPlace);
	return c;

}


void BigInt::operator=(const BigInt& rhs)
{
	type = rhs.type;
	//name不用改
	digits = rhs.digits;
	dotPlace = rhs.dotPlace;
}

ostream& operator<<(ostream& strm, const BigInt& now)
{
	strm << now.digits;
	return strm;
}
