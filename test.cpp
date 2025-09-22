#include <iostream>
#include <string>
using namespace std;

int sequence[] = {1, 2, 3, 4, 5, 0, 0, 0};
int length = 5;

void shiftRight(int arr[], int n) {
    for(int i = length; i >= n; --i) {
        sequence[i + 1] = sequence[i];
        // cout << sequence[i] << endl;
    }
    length++;
}

void shiftLeft(int index) {
    for (int i = index; i < length - 1; ++i) {
        sequence[i] = sequence[i + 1];
    }
    --length;
}


int main() {
        int replaceVar = 9;
        int first = 2;
        int second = 3;
        for(int i = 0; i < length; i++) {
            if(sequence[i] == first && sequence[i + 1] == second) {
                shiftLeft(i);
                sequence[i] = replaceVar;
            }
        }
        for(int i = 0; i < length; ++i) {
            cout << sequence[i] << endl;
        }
   
}