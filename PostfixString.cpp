/**
 * author: Vahid Mavaji
 * year: 2001
 */

#include<iostream>
#include<string.h>

template<class T>
class Stack {
    static const int SIZE = 40;
private:
    T stack[SIZE];
    int top;
public:
    Stack() {
        for (int i = 0; i < SIZE; i++) { stack[i] = 0; }
        top = 0;
    }

    T pop();

    void push(T x);

    int isEmpty();

    int isFull();

};

template<class T>
T Stack<T>::pop() {
    if (isEmpty())
        return stack[top];
    else
        top--;

    return stack[top];
}

template<class T>
void Stack<T>::push(T x) {
    if (!isFull()) {
        stack[top] = x;
        top++;
        return;
    } else
        stack[top] = x;

    return;
}

template<class T>
int Stack<T>::isEmpty() {
    return top == 0;
}

template<class T>
int Stack<T>::isFull() {
    return top == SIZE;
}

class PostfixString {
    static const int SIZE = 80;
private:

    char infix[SIZE];
    char postfix[SIZE];

public:
    PostfixString() {
        infix[0] = '\0';
        postfix[0] = '\0';
    }

    int pre(char x);

    void infixToPostfix();

    void calculatePostfix();

    void addToPostfix(char x);
};

void PostfixString::infixToPostfix() {
    int count = 0;
    int pref;
    char ch, popch;

    Stack<char> stack;

    std::cout << "Enter Infix Expression: ";

    std::cin >> infix;

    for (count = 0; count < strlen(infix); count++) {
        ch = infix[count];
        if (ch == '(') {
            stack.push(ch);
            continue;
        }
        if (ch == ')') {
            popch = stack.pop();
            while (popch != '(') {
                addToPostfix(popch);
                popch = stack.pop();
            }

            continue;
        } else if (ch >= 65 /*A*/ && ch <= 90 /*Z*/) {
            addToPostfix(ch);
        } else {
            pref = pre(ch);
            if (stack.isEmpty()) stack.push(ch);
            else {
                int test = 0;
                popch = stack.pop();
                while ((pref <= pre(popch))) {
                    test = 0;
                    addToPostfix(popch);
                    if (!stack.isEmpty())
                        popch = stack.pop();
                    else {
                        test = 1;
                        break;
                    }
                }
                if (!test) stack.push(popch);
                stack.push(ch);
            }
        }
    }
    if (!stack.isEmpty()) {
        while (!stack.isEmpty()) {
            popch = stack.pop();
            addToPostfix(popch);
        }

    }
    std::cout << "Postfix Expression: " << postfix << "\n";
}

void PostfixString::calculatePostfix() {
    float values[26];
    float value;
    int i;
    char ch;
    float operand2, operand1;
    Stack<float> stack;

    do {
        std::cout << "Enter Operand Name (0 for termination): ";
        std::cin >> ch;
        if (ch == '0') break;
        std::cout << "Enter Operand Value:";
        std::cin >> value;
        values[ch - 65 /*A*/] = value;
    } while (1);

    for (i = 0; i < strlen(postfix); i++) {
        ch = postfix[i];
        if (ch >= 65 /*A*/&& ch <= 90 /*Z*/) { stack.push(values[ch - 65 /*A*/]); }
        else {
            operand2 = stack.pop();
            operand1 = stack.pop();

            switch (ch) {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
                default:
                    break;
            }
        }
    }

    std::cout << "Calculated Result is: " << stack.pop();
}

int PostfixString::pre(char x) {
    switch (x) {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            break;
    }
    return 0;
}

void PostfixString::addToPostfix(char x) {
    int n;
    n = (int) strlen(postfix);
    postfix[n] = x;
    postfix[n + 1] = '\0';
}

int main() {
    PostfixString infixString;

    infixString.infixToPostfix();
    infixString.calculatePostfix();

    return 0;
}
