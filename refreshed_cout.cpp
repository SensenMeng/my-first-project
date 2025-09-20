#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <unistd.h>

#define OBJ 50
#define TIM 10000

using namespace std;

void PriSecToE(string, int);
int GenRan(int);

int main()
{
	string words;
	getline(cin, words);
	int size = words.length();
	
	for (int i = 0; i < size; i++){
		if (i == 0){
			for (int j = 0; j < OBJ; j++){
				int k = GenRan(size - 1);
				cout << words[k];
				cout << endl;
				//usleep(TIM);
			}
			cout << words[0] << endl;
			usleep(TIM);
		}
		else{
			for (int j = 0; j < OBJ; j++){
				int k = GenRan(size - 1);
				PriSecToE(words, i);
				cout << words[k];
				cout << endl;
				usleep(TIM);
			}
			PriSecToE(words, i+1);
			cout << endl;
		}
		usleep(TIM);
	}
	return 0;
}

void PriSecToE(string a, int b)
{
	for (int i = 0; i < b; i++){
		cout << a[i];
		//usleep(TIM);
		} 
}

int GenRan(int a)
{
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);
	return rand() % (a + 1);
}