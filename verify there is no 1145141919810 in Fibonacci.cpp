#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    unsigned long long a1 = 1, a2 = 1, temp;
    cout << a1 << endl;
    cout << a2 << endl;

    while(1){
        temp = a1;
        a1 = a2;
        a2 = temp + a2;
        cout << a2 << endl;
        if (a2 >= 1145141919810){
            break;
        }
        Sleep(100);
    }

    cout << endl;
    return 0;
}