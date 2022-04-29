#include "BigInt.h"
#include <sstream>	//istringstream
//https://www.twblogs.net/a/5b8a17392b71775d1ce55f47


int main()
{
	string line;
	istringstream istr;
	string cmd;
	/*
		做一個vector紀錄左右括弧的位置，
		每次讀到左括弧就push_back到[i][0]
		直到讀到右括弧，開始i-- 並push_back[i][1]
	*/
	/*
	while (getline(std::cin, line))
	{
		istr.str(line);
		istr >> cmd;
		if (cmd == "Set")
		{
			istr >> cmd;
			if (cmd == "Integer")
			{

			}
			else if (cmd == "Decimal")
			{

			}
		}
	}
	*/

	string a = "1.5 + 3 * ( -(-5) )";
	//getline
	BigInt ans(a);
	cout << ans;
}
