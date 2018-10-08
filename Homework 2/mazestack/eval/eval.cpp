//
//  main.cpp
//  eval
//
//  Created by Vanessa Lee on 2/3/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <stack>
#include <cctype>
#include "Map.h"
using namespace std;

string infixToPostfix(string infix);
bool isOperator(char c);
bool isOperand(char c);
int operatorWeight(char c);
bool greaterPrecedence(char c1, char c2);
bool validInfix(const string infix);
bool validParentheses(const string infix);
int operatorCount(const string infix);
int operandCount(const string infix);
bool inMap(const string infix, const Map& m);
bool divideByZero(string postfix, const Map& m);
int eval(const string postfix, const Map& m);

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    postfix = infixToPostfix(infix);
    
    if(!validInfix(infix))
        return 1;
    else if(validInfix(infix) && !inMap(infix, values))
        return 2;
    else if(divideByZero(postfix, values))
        return 3;
    
    result = eval(postfix, values);
    
    return 0;
}

string infixToPostfix(const string infix) {
    stack<char> charStack;
    string postfix = "";
    
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == ' ')
            continue;
        
        if (isOperand(infix[i])) {
            postfix += infix[i];
        }
        
        if (infix[i] == '(')
            charStack.push(infix[i]);
        
        if (isOperator(infix[i])) {
            while(!charStack.empty() && charStack.top() != '(' && greaterPrecedence(charStack.top(), infix[i])) {
                postfix += charStack.top();
                charStack.pop();
            }
            
            charStack.push(infix[i]);
        }
        
        if (infix[i] == ')') {
            while(charStack.top() != '(') {
                //if (isOperator(charStack.top()))
                postfix += charStack.top();
                charStack.pop();
            }
            
            charStack.pop();
        }
    }
    
    while(!charStack.empty()) {
        postfix += charStack.top();
        charStack.pop();
    }
    
    return postfix;
}

bool isOperator(char c) {
    char validOperands[4] = {'+', '-', '/', '*'};
    
    for (int i = 0; i < 4; i++) {
        if (c == validOperands[i])
            return true;
    }
            
    return false;
}

bool isOperand(char c) {
    if (c >= 'a' && c <= 'z')
        return true;
    
    return false;
}

int operatorWeight(char c) {
    int weight = 0;
    
    switch (c) {
        case '+':
        case '-':
            weight = 1;
            break;
        case '*':
        case '/':
            weight = 2;
            break;

    }
    return weight;
}

bool greaterPrecedence(char c1, char c2) {
    int weight1 = operatorWeight(c1);
    int weight2 = operatorWeight(c2);
    
    if (weight1 < weight2)
        return false;
    
    return true;
}

bool validInfix(const string infix) {
    for (int i = 0; i < infix.size(); i++) {
        if (!isOperand(infix[i]) && !isOperator(infix[i]) && infix[i] != ' ' && infix[i] != '(' && infix[i] != ')')
            return false;
    }
    
    if(!validParentheses(infix))
        return false;
    
    if(operandCount(infix) - operatorCount(infix) != 1)
        return false;
    
    return true;
}

bool validParentheses(const string infix) {
    int leftPar = 0;
    int rightPar = 0;
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == '(')
            leftPar++;
        if (infix[i] == ')')
            rightPar++;
    }
    
    return leftPar == rightPar;
}

int operatorCount(const string infix) {
    int operators = 0;
    
    for (int i = 0; i < infix.size(); i++) {
        if(isOperator(infix[i]))
            operators++;
    }
    
    return operators;
}

int operandCount(const string infix) {
    int operands = 0;
    
    for (int i = 0; i < infix.size(); i++) {
        if(isOperand(infix[i]))
            operands++;
    }
    
    return operands;
}

bool inMap(const string infix, const Map& m) {
    for (int i = 0; i < infix.size(); i++) {
        if(isOperand(infix[i])) {
            if(!m.contains(infix[i]))
                return false;
        }
    }
    return true;
}

bool divideByZero(string postfix, const Map& m) {
    stack<char> charStack;
    
    for (int i = 0; i < postfix.size(); i++) {
        if (isOperand(postfix[i])) {
            ValueType v;
            m.get(postfix[i], v);
            charStack.push(v);
        }
        else {
            int operand2 = charStack.top();
            charStack.pop();
            int operand1 = charStack.top();
            charStack.pop();
            
            int ans = 0;
            
            switch (postfix[i]) {
                case '-':
                    ans = operand1 - operand2;
                    break;
                case '+':
                    ans = operand1 + operand2;
                    break;
                case '*':
                    ans = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0)
                        return true;
                    else
                        ans = operand1 / operand2;
                    break;
            }
            charStack.push(ans);
        }
    }
    
    return false;
}

int eval(const string postfix, const Map& m) {
    if(postfix.size() == 1) {
        ValueType v;
        m.get(postfix[0], v);
        return v;
    }
    
    stack<char> charStack;
    
    for (int i = 0; i < postfix.size(); i++) {
        if (isOperand(postfix[i])) {
            ValueType v;
            m.get(postfix[i], v);
            charStack.push(v);
        }
        else {
            int operand2 = charStack.top();
            charStack.pop();
            int operand1 = charStack.top();
            charStack.pop();
            
            int ans = 0;
            
            switch (postfix[i]) {
                case '-':
                    ans = operand1 - operand2;
                    break;
                case '+':
                    ans = operand1 + operand2;
                    break;
                case '*':
                    ans = operand1 * operand2;
                    break;
                case '/':
                    ans = operand1 / operand2;
                    break;
            }
            charStack.push(ans);
        }
    }
    
    return charStack.top();
}
/*
int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}
*/
