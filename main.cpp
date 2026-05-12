#include <iostream>
#include <string>
using namespace std;

struct Stack {
    char data[100];
    int top;
};

int main() {

    string word;
    string reversed = "";

    Stack stack;
    stack.top = -1;

    cout << "Enter a word: ";
    cin >> word;

    // PUSH
    for (int i = 0; i < word.length(); i++) {
        stack.top++;
        stack.data[stack.top] = word[i];
    }

    // POP
    while (stack.top != -1) {
        reversed += stack.data[stack.top];
        stack.top--;
    }

    // CHECK PALINDROME
    if (word == reversed) {
        cout << "It is a Palindrome." << endl;
    }
    else {
        cout << "It is NOT a Palindrome." << endl;
    }

    return 0;
}
