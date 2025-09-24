#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string add(string a, string b);
string multi(string a, string b);
string sin_multi(string a, char b);

int main()
{
	string a;
	string b;
	cout << "Enter two numbers: ";
	cin >> a >> b;
	cout << multi(a, b) << endl;
	return 0;    
}

string add(string a, string b)
{
	string result = "";
	int i = a.length() - 1, j = b.length() - 1, carry = 0, sum = 0;
	while (j >= 0 || i >= 0 || carry){
		sum  = 0;
		if (i >= 0) sum += a[i] - '0'; i--;
		if (j >= 0) sum += b[j] - '0'; j--;
		sum += carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
	}
	reverse(result.begin(), result.end());
	return result;
}

string multi(string a, string b)
{
	int k = b.length() - 1;
	string result = "0";
	for (int i = k; i >= 0; i--){
		string practical = sin_multi(a, b[i]);
		for (int j = k - i; j > 0; j--){
			practical += "0";
		}
		result = add(result, practical);
	}
	return result;
}

string sin_multi(string a, char b)
{
	string result = "";
	int back1 = 0;
	for (int i = a.length() - 1; i >= 0; i--){
		if (a[i] - '0' == 0) back1++;
		if (a[i] - '0' != 0) break;
	}
	if (b - '0' == 0) return "0";
	int i = a.length() - 1 - back1, carry = 0;
	while (i >= 0 || carry){
		int sum  = 0;
		if (i >= 0) sum = (a[i] - '0') * (b - '0'); i--;
		sum += carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
	}
	reverse(result.begin(), result.end());
	for (int i = 1; i <= back1; i++){
		result = result + "0";
		}
	return result;
}