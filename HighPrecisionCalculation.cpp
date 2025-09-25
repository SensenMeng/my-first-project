#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string add(string a, string b);
string multi(string a, string b);
string sin_multi(string a, char b);
string power(string a, string b);
string minusnum(string a, string b); 
string dividenum(string a, string b);
string restnum(string a, string b);
bool compare(string a, string b);
void RemoveLeadingZero(string& a);

int main()
{
	cout << "1. add\n2. minus\n3. multi\n4. divide\n5. rest\n6. power" << endl;
	cout << "Choose your mode:";
	int mode;
	cin >> mode;
	if (mode != 1 && mode != 2 && mode != 3 &&	mode != 4 && mode !=5 && mode != 6){
		cout << "Wrong number or word!!! Please be careful!!!" << endl;
		return 0;
	}
	cout << "Enter two numbers: ";
	string a, b;
	cin >> a >> b;
	switch (mode){
		case 1: cout << add(a, b) << endl; break;
		case 2: cout << minusnum(a, b) << endl; break;
		case 3: cout << multi(a, b) << endl; break;
		case 4: cout << dividenum(a, b) << endl; break;
		case 5: cout << restnum(a, b) << endl; break;
		case 6: cout << power(a, b) << endl; break;
		}
	return 0;    
}

string add(string a, string b)
{
	RemoveLeadingZero(a);
	RemoveLeadingZero(b);
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

string power(string a, string b)
{
	string result = a, result1 = a;
	for (int i = 1; i < stoi(b); i++){
		result = multi(result, result1);
	}
	return result;
}

string multi(string a, string b)
{
	RemoveLeadingZero(a);
	RemoveLeadingZero(b);
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

string minusnum(string a, string b)
{
	RemoveLeadingZero(a);
	RemoveLeadingZero(b);
	if (!compare(a, b)) return '-' + minusnum(b, a);
	string result = "";
	int i = a.length() - 1, j = b.length() - 1, carry = 0, sum = 0;
	while (j >= 0 || i >= 0 || carry){
		sum  = 0;
		if (i >= 0) sum += a[i] - '0'; i--;
		if (j >= 0) sum -= b[j] - '0'; j--;
		sum -= carry;
		carry = 0;
		if (sum < 0){
			carry++;
			sum = sum + 10;
		}
		result.push_back(sum + '0');
	}
	reverse(result.begin(), result.end());
	for (int k = 0; k < result.length(); k++){
		if (result[k] - '0' != 0)
			break;
		result.erase(k,1);
	}
	return result;
}

string dividenum(string a, string b)
{
	RemoveLeadingZero(a);
	RemoveLeadingZero(b);
	if (b == "0"){
		return "Error: Division by zero!";
	}
	if (!compare(a, b))
		return "0";
	string result = "", resultv = "";
	int i = a.length(), j = b.length();
	for (int k = 0; k <= i - j; k++){
		result += "0";
		resultv += "0";
	}
	for (int k = 0; k <= i - j; k++){
		for (int m = 0; m < 10; m++){
			resultv[k] = m + '0';
			if(compare(a, multi(b, resultv))){
				result[k] = m + '0';
				resultv[k] = m + '0';
			}
			else{
				resultv[k] = (m - 1) + '0';
				break;
			}
		}
	}
	RemoveLeadingZero(result);
	return result;
}

string restnum(string a, string b)
{
	string result = minusnum(a, multi(b, dividenum(a, b)));
	RemoveLeadingZero(result);
	return result;
}

bool compare(string a, string b)
{
	int i = a.length() - 1, j = b.length() - 1;
	if (i > j)
	    return true;
	if (i < j)
		return false;
	for (int k = 0; k <= i; k++){
		if (a[k] - '0' < b[k] - '0')
			return false;
		if (a[k] - '0' > b[k] - '0')
			return true;
	}
	return 1;
}

void RemoveLeadingZero(string& a)
{
	while (1){
		if (a[0] - '0' != 0)
		break;
		a.erase(0,1);
	}
}