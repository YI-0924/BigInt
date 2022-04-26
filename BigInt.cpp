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

// 以分數輸出，最後的答案再轉為小數(下100位)
BigInt BigInt::operator/(const BigInt rhs) const	// (digit - '0') / (rhs.digit - '0') -> A / B
{
	BigInt c;
	bool ansType;		//整/整=整  整/整=小  整/小=整  小/整=整  整/小=小  小/整=小  小/小=小  小/小=整
	bool ansSign;		
	string ansDigits = "";
	int ansDotPlace;

	int lenA = digits.size();
	int lenB = rhs.digits.size();
	int dLen;
	string trans = "0";		// string to int is -trans ; int to string is +trans
	string A = digits;
	string B = rhs.digits;
	string tempStr = A;
	string remain;

	if (sign == 0 && rhs.sign == 0) {
		ansSign = 0;		//正數
	}
	else {
		ansSign = 1;		//負數
	}

	//============ A >= B =============
	dLen = lenA - lenB;

	// let lenA = lenB. For example : 12345678 / 234567 -> 12345678 / 00234567
	/*for (int i = lenA - 1; i >= 0; i--) {
		if (i >= dLen) {
			B[i] = B[i - dLen];
		}
		else {
			B[i] = '0';
		}
	}*/
	
	//use the substraction and addition to count ansDigits and remainder
	while (tempStr = substraction(tempStr, B) >= '0') {		// A - B = tempStr
		ansDigits = addition(ansDigits, 1);			// if 12345678 / 234567 then ansDigits = 52
	}

	// 是否有餘數
	if (tempStr != "0") {
		remain = tempStr;		// if 12345678 / 234567 then remain = 148194
		ansType = 1;		//小數 -> 應該以分數回傳
	}
	else {
		ansType = 0;		//整數
		ansDotPlace = 0;
	}

	c.setType(ansType);
	c.setSign(ansSign);
	c.setDigits(ansDigits);
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
