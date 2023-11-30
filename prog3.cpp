// Name: Emilio Maset
// File Name: prog3.cpp
// Date: 23 October, 2023
// Program Description: Driver file for program to evaluate a postfix expression

#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

void fileValidityChecker(int argc, ifstream &inFile);
bool isOperator(string testString);
bool isOperand(string testString);
string evaluateExpression(Stack &stack, string expressionToBeEvaluated);
int performOneOperation(int popValue1, int popValue2, char op);

int main(int argc, char* argv[]) {
    ifstream inFile(argv[1]);
    fileValidityChecker(argc, inFile);

    Stack stack;
    string oneLineFromFile;

    while (getline(inFile, oneLineFromFile)) {

        if (int(oneLineFromFile[oneLineFromFile.length()-1]) == 13
            || int(oneLineFromFile[oneLineFromFile.length()-1]) == 10) // trims carriage return and new line from end of string
            oneLineFromFile = oneLineFromFile.substr(0, oneLineFromFile.length()-1);

        cout << oneLineFromFile << evaluateExpression(stack, oneLineFromFile) << endl;
        stack.clear();
    }

    return 0;
} // end of main

//===========================================================================================================================================================

void fileValidityChecker(int argc, ifstream &inFile) {
    if (argc == 1) {
        cout << "No file name entered";
        exit(0);
    }

    if (!inFile) {
        cout << "File not found";
        exit(0);
    }
}

//===========================================================================================================================================================

bool isOperator(string testString) {
    return ( testString == "+" || testString == "-" || testString == "*" || testString == "/" || testString == "%" || testString == "^");
}

//===========================================================================================================================================================

bool isOperand(string testString) {
    return atoi(testString.c_str()) > 0;
}

//===========================================================================================================================================================

string evaluateExpression(Stack &stack, string expressionToBeEvaluated) {
    int popValue1;
    int popValue2;

    char expressionCStringVersion[80];
    strcpy(expressionCStringVersion, expressionToBeEvaluated.c_str()); // copy c++ string into c-type string in order to tokenize

    char *token = strtok(expressionCStringVersion, " ");

    while (token != NULL) {
        if (!isOperator(token) && !isOperand(token)) // if token is not one of the valid operators (nor a number), it is invalid
            return " (Error : invalid operator)";

        if (isOperand(token)) { // push a number onto the stack
            stack.push(atoi(token));
        }

        if (isOperator(token) && !isOperand(token)) { // if it's a valid operator, perform the operation if allowed
            popValue1 = stack.pop();
            popValue2 = stack.pop();
            if (popValue1 != -1 && popValue2 != -1) // if there are at least two values available to be popped from the stack, perform the operation
                stack.push(performOneOperation(popValue1, popValue2, *token));

            else // if there are not at least to operands on the stack, then there are too many operators in the expression
                return " (Error : too many operators)";
        }

        token = strtok(NULL, " ");
    }

    if (!stack.isEmpty()) {
        int result = stack.pop();
        if (stack.isEmpty()) // if the stack is empty after popping one value, then the expression was valid and the popped value is result
            return " = " + to_string(result);
        else // if there are still values on the stack after popping one, there were too many operands in the expression
            return " (Error : too many operands)";
    }

    return "";
}
//===========================================================================================================================================================

int performOneOperation(int popValue1, int popValue2, char op) {
    switch (op) {
        case '+':
            return (popValue2 + popValue1);
        case '-':
            return (popValue2 - popValue1);
        case '*':
            return (popValue2 * popValue1);
        case '/':
            return (popValue2 / popValue1);
        case '%':
            return (popValue2 % popValue1);
        case '^':
            return pow(popValue2, popValue1);
        default:
            return -99;
    }
}