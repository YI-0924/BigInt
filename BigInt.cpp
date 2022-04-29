#include "BigInt.h"

vector<BigInt*> BigInt::All;

string addition(string A, string B);
string subtraction(string A, string B);

BigInt::BigInt(bool t, string n, string d)
{
	this->type = t;
	this->name = n;
	this->digits = d;
	this->dotPlace = digits.find('.');
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

	//乘除放一起時，先乘後除
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
	BigInt c;
	bool ansType;
	bool ansSign;
	string ansDigits = "";
	int ansDotPlace;

	if (sign == 0 && rhs.sign == 0) {		// 正+正
		ansDigits = addition(digits, rhs.digits);
		ansSign = 0;
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != 0) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	else if (sign == 1 && rhs.sign == 1) {		// 負+負
		string a = digits;
		a.erase(0, 1);
		string b = rhs.digits;
		b.erase(0, 1);
		ansDigits = addition(a, b);		// 以正+正去運算
		ansDigits = '-' + ansDigits;		// 把負號加回來
		ansSign = 1;
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != 0) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	else {
		if (sign == 0 && rhs.sign == 1) {		// 正+負 = 正-正
			ansDigits = subtraction(digits, rhs.digits);
		}
		else {		//sign == 1 && rhs.sign == 0		//負+正 = 正-正
			ansDigits = subtraction(rhs.digits, digits);

		}
		if (ansDigits[0] == '-') {
			ansSign = 1;
		}
		else {
			ansSign = 0;
		}
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != 0) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}

	c.type = ansType;
	c.sign = ansSign;
	c.digits = ansDigits;
	c.dotPlace = ansDotPlace;

	return c;
}

BigInt BigInt::operator-(const BigInt rhs) const
{
	BigInt c;
	bool ansType;
	bool ansSign;
	string ansDigits = "";
	int ansDotPlace;

	if (sign == 0 && rhs.sign == 0) {		// 正-正
		ansDigits = subtraction(digits, rhs.digits);
		if (ansDigits[0] == '-') {
			ansSign = 1;
		}
		else {
			ansSign = 0;
		}
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != 0) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	else if (sign == 1 && rhs.sign == 1) {		// 負-負 = 負(正-正)
		string a = digits;
		a.erase(0, 1);
		string b = rhs.digits;
		b.erase(0, 1);
		ansDigits = subtraction(a, b);		// 以正-正去運算
		if (ansDigits[0] == '-') {
			ansDigits.erase(0, 1);			// 把負號去掉
		}
		else {
			ansDigits = '-' + ansDigits;		// 把負號加回來
		}
		if (ansDigits[0] == '-') {
			ansSign = 1;
		}
		else {
			ansSign = 0;
		}
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != 0) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	else {
		string a = digits;
		a.erase(0, 1);
		string b = rhs.digits;
		b.erase(0, 1);

		if (sign == 0 && rhs.sign == 1) {		// 正-負 = 正+正
			ansDigits = addition(digits, rhs.digits);
		}
		else {		//sign == 1 && rhs.sign == 0		//負-正 = 負(正+正)
			ansDigits = addition(rhs.digits, digits);

		}
		if (ansDigits[0] == '-') {
			ansSign = 1;
		}
		else {
			ansSign = 0;
		}
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != 0) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}

	c.type = ansType;
	c.sign = ansSign;
	c.digits = ansDigits;
	c.dotPlace = ansDotPlace;

	return c;
}

BigInt BigInt::operator*(const BigInt rhs) const
{
	BigInt c;
	string ans;
	bool ansType;
	int decPt = dotPlace + rhs.dotPlace;
	int len1 = digits.size();
	int len2 = rhs.digits.size();
	// 101 0s
	string dec_0 = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	// judge ans int or dec
	if (type == 0 && rhs.type == 0)
		ansType = false;
	else
		ansType = true;

	if (digits == "0" || rhs.digits == "0" || digits == dec_0 || rhs.digits == dec_0)
		if (ansType == false)
			ans = "0";
		else
			ans = dec_0;

	else
	{
		vector <int> res(len1 + len2, 0);
		int _1 = 0;
		int _2 = 0;

		for (int i = len1 - 1; i >= 0; i--)
		{
			int cry = 0;
			int n1 = digits[i] - '0';

			// shift pos to l after every multiplication of a digit in rhs
			_2 = 0;
			// go from right to left in rhs
			for (int j = len2 - 1; j >= 0; j--)
			{
				// take current digit of second number
				int n2 = rhs.digits[j] - '0';
				// multiply with current digit of 1st num & add res to prev stored res at current pos
				int sum = n1 * n2 + res[_1 + _2] + cry;
				// carry for next iteration
				cry = sum / 10;
				res[_1 + _2] = sum % 10;
				_2++;
			}
			// store carry in next cell
			if (cry > 0)
				res[_1 + _2] += cry;
			// shift pos to left after every multiplication of a digit og       
			_1++;
		}

		// ignore 0s from the right
		int q = res.size() - 1;
		while (q >= 0 && res[q] == 0)
			q--;
		while (q >= 0)
			ans += to_string(res[q--]);

		if (ansType == 1)
			// retain only first 100 digits after decimal point
			ans.erase(decPt + 100);
	}
	c.setDigits(ans);
	c.setDotPlace(decPt);
	c.setType(ansType);
	return c;

}

//  (1 / 3) * 3 = 1 -> 先乘後除(process 裡面判斷)
BigInt BigInt::operator/(const BigInt rhs) const	// (digit - '0') / (rhs.digit - '0') -> A / B
{
	BigInt c;
	bool ansType;		
	bool ansSign;		
	string ansDigits = "0";
	int ansDotPlace = 0;

	int lenA = digits.size();
	int lenB = rhs.digits.size();

	bool chkAB = false;		// chkAB = false if A < B
	int dotA = 0;
	int dotB = 0;

	string A = digits;
	string B = rhs.digits;
	string tempStr = A;
	string remain;

	int countZero = 0;
	int carry = 0;
	int num;
	string numStr;
	int countDecimal = 0;		// countDecimal need <= 100
	int lenRemain = 0;

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
		// if 12,345,678 / 234,567 = 52.6317768484 ; remain 148,194
		while ((tempStr = subtraction(tempStr, B)) >= "0") {		// A - B = tempStr
			ansDigits = addition(ansDigits, "1");		
		}
		if (tempStr != "0") {
			ansDigits += '.';		// now ansDigits = 52.
		}
		carry = 1;
		num = pow(10, (-1) * carry);
		numStr = num + '0';
	}
	else if (lenA == lenB) {
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
		else {		// dotA <= dotB
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
			//if 23,456,789 / 12,345,678 = 1.9000000648 ; remain 11,111,111
			while ((tempStr = subtraction(tempStr, B)) >= "0") {		// tempStr = A - B
				ansDigits = addition(ansDigits, "1");		
			}
			if (tempStr != "0") {
				ansDigits += '.';		// now ansDigits = 1.
			}
			carry = 1;
			num = pow(10, (-1) * carry);
			numStr = num + '0';
		}
		else {		// chk = false ; lenA = lenB ; A < B
			ansDigits += "0.";
			A += "0";
			// now A > B
			tempStr = A;
			//while ((tempStr = subtraction(tempStr, B)) >= "0") {		// A - B = tempStr
				//ansDigits 小數位數接下去		// now ansDigits = 0.
			//}
			carry = 1;
			num = pow(10, (-1) * carry);
			numStr = num + '0';
		}
	}
	else {		// lenA < lenB ; A < B
		ansDigits += "0.";
		A += "0";
		if (A[0] > B[0]) {		// for example : 234567 / 12345678 = 0.0189999286
			countZero = lenB - lenA - 1;
			carry = lenB - lenA;
			while (countZero > 0) {
				ansDigits += "0";
				A += "0";
				countZero--;
			}
			// now A > B -> 23456700 / 12345678
			tempStr = A;
			num = pow(10, carry * (-1));
			numStr = num + '0';
			while ((tempStr = subtraction(tempStr, B)) >= "0") {		// A - B = tempStr
				ansDigits = addition(ansDigits, numStr);		// remain 23456700 - 12345678 = 11,111,022		// now ansDigits = 0.01
			}
			carry++;
			num = pow(10, (-1) * carry);
			numStr = num + '0';
			countDecimal = num;
		}
		else if (A[0] < B[0]) {		// for example : 123456 / 23456789 = 0.0052631245
			countZero = lenB - lenA;
			carry = lenB - lenA + 1;
			while (countZero > 0) {
				ansDigits += "0";
				A += "0";
				countZero--;
			}
			// now A > B
			tempStr = A;
			num = pow(10, (-1) * carry);
			numStr = num + '0';
			while ((tempStr = subtraction(tempStr, B)) >= "0") {		// A - B = tempStr
				ansDigits = addition(ansDigits, numStr);		// now ansDigits = 0.005
			}
			carry++;
			num = pow(10, (-1) * carry);
			numStr = num + '0';
			countDecimal = num;
		}
	}

	// 有餘數 -> ansDigits以小數下100位回傳
	lenRemain = remain.length();
	if (tempStr != "0") {
		remain = tempStr;		// ansDigits += remain / B
		ansType = 1;		//小數

		// remain < B ; lenRemain = or < lenB 
		if (lenRemain == lenB) {
			while (countDecimal <= 100 || remain != "0") {
				remain += "0";
				// now remain > B
				while ((remain = subtraction(remain, B)) >= "0") {		// A - B = tempStr
					ansDigits = addition(ansDigits, numStr);
				}
				carry++;
				num = pow(10, (-1) * carry);
				numStr = num + '0';
				countDecimal++;
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
				while (countDecimal <= 100 || remain != "0") {
					while ((remain = subtraction(remain, B)) >= "0") {		// A - B = tempStr
						ansDigits = addition(ansDigits, numStr);
					}
					carry++;
					num = pow(10, (-1) * carry);
					numStr = num + '0';
					countDecimal++;
					remain += "0";
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
				while (countDecimal <= 100 || remain != "0") {
					while ((remain = subtraction(remain, B)) >= "0") {		// A - B = tempStr
						ansDigits = addition(ansDigits, numStr);
					}
					carry++;
					num = pow(10, (-1) * carry);
					numStr = num + '0';
					countDecimal++;
					remain += "0";
				}
			}
		}

		ansDotPlace = ansDigits.find('.');

	}

	// 沒餘數
	else {
		ansType = 0;		//整數
		ansDotPlace = 0;
	}

	c.setType(ansType);
	c.setSign(ansSign);
	c.setDigits(ansDigits);		//小數
	c.setDotPlace(ansDotPlace);
	return c;

}

string addition(string A, string B)		// 都會是正+正 (但可能有小數)
{
	int dot1 = A.find('.');
	int dot2 = B.find('.');
	int carry = 0;
	int len;
	int dot;
	int digit1 = 0, digit2 = 0;
	int base = '0';

	if (dot1 > dot2) {		// A > B (小數 + 小數) eg: 123.45 + 67.891
		for (int i = dot2; i <= dot1; i++) {
			B = '0' + B;		// 067.891
		}
		len = max(A.length(), B.length());
		A.erase(dot1, 1);		// 12345
		B.erase(dot2, 1);		// 067891
	}
	else if (dot1 < dot2) {		// A < B (小數 + 小數) eg: 12.345 + 678.9
		for (int i = dot1; i <= dot2; i++) {
			A = '0' + A;		// 012.345
		}
		len = max(A.length(), B.length());
		A.erase(dot1, 1);		// 012345
		B.erase(dot2, 1);		// 6789
	}
	else {
		if (dot1 == 0 && dot2 == 0) {		// 整數 + 整數
			len = max(A.length(), B.length());
		}
		else {		// 小數 + 小數 eg: 123.45 + 678.9
			len = max(A.length(), B.length());
			A.erase(dot1, 1);		// 12345
			B.erase(dot2, 1);		// 6789
		}
	}

	dot = max(dot1, dot2);

	if (A.length() < B.length())
	{
		A.swap(B);
	}
	for (int i = 0; i < len; i++)
	{
		digit1 = A[A.length() - 1 - i] - base;
		if (i < B.length())
		{
			digit2 = B[B.length() - 1 - i] - base;
		}
		A[len - 1 - i] = ((digit1 + digit2 + carry) % 10) + base;
		if (digit1 + digit2 + carry >= 10)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		digit1 = 0;
		digit2 = 0;
	}

	if (carry == 1) {
		A = '1' + A;
		dot++;
	}

	if (dot != 0) {
		A.insert(dot, ".");
	}

	return A;
}

string subtraction(string A, string B)		// 都會是正-正 (但可能有小數)
{
	int dot1 = A.find('.');
	int dot2 = B.find('.');
	int carry = 0;
	int len;
	int dot;
	int digit1 = 0, digit2 = 0;
	int base = '0';
	string ans = "";
	char ansSign;

	if (dot1 > dot2) {		// A > B (小數 - 小數) eg: 123.45 - 67.891
		for (int i = dot2; i <= dot1; i++) {
			B = '0' + B;		// 067.891
		}
		len = max(A.length(), B.length());
		A.erase(dot1, 1);		// 12345
		B.erase(dot2, 1);		// 067891
		ansSign = '+';
	}
	else if (dot1 < dot2) {		// A < B (小數 - 小數) eg: 12.345 - 678.91
		for (int i = dot1; i <= dot2; i++) {
			A = '0' + A;		// 012.345
		}
		len = max(A.length(), B.length());
		A.erase(dot1, 1);		// 012345
		B.erase(dot2, 1);		// 6789
		ansSign = '-';
		A.swap(B);
	}
	else {
		if (dot1 == 0 && dot2 == 0) {		// 整數 - 整數
			len = max(A.length(), B.length());
			if (A.length() > B.length()) {
				ansSign = '+';
			}
			else if (A.length() == B.length()) {
				for (int i = 0; i < len; i++) {
					if (A[i] > B[i]) {
						ansSign = '+';
						break;
					}
					else if (A[i] < B[i]) {
						ansSign = '-';
						A.swap(B);
						break;
					}
				}
			}
			else {
				ansSign = '-';
				A.swap(B);
			}
		}
		else {		// 小數 - 小數 eg: 123.45 - 678.9
			len = max(A.length(), B.length());
			A.erase(dot1, 1);		// 12345
			B.erase(dot2, 1);		// 6789
			for (int i = 0; i < len; i++) {
				if (A[i] > B[i]) {
					ansSign = '+';
					break;
				}
				else if (A[i] < B[i]) {
					ansSign = '-';
					A.swap(B);
					break;
				}
			}
		}
	}

	dot = max(dot1, dot2);

	// now A > B
	int len1 = A.length() - 1;
	int borrow = 0;

	for (int i = 0; i < len1; i++) {
		ans[i] = (ans[i] - '0') + ((A[i] - '0') - (B[i] - '0') - borrow) + '0';
		if (ans[i] - '0' < 0) {
			borrow = 1;
			ans[i] = (ans[i] - '0') + 10 + '0';
		}
		else {
			borrow = 0;
		}
	}

	if (ansSign == '-') {
		ans = '-' + ans;
	}

	if (dot != 0) {
		ans.insert(dot, ".");
	}

	return ans;
	
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
	//if ansDigits = default -> 分母為0

	strm << now.digits;
	return strm;
}
