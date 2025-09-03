//Evaluate Expression from Command Line


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// ===== Stack for numbers =====
int stack[MAX];
int top = -1;

void push(int val) {
    stack[++top] = val;
}

int pop() {
    return stack[top--];
}

// ===== Stack for operators =====
char opStack[MAX];
int opTop = -1;

void pushOp(char c) {
    opStack[++opTop] = c;
}

char popOp() {
    return opStack[opTop--];
}

char peekOp() {
    return opStack[opTop];
}

int precedence(char op) {
    if (op == '/' || op == '*')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Apply operator to two operands
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Evaluate infix expression
int evaluate(char *exp) {
    int i, num;

    for (i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == ' ')
            continue;

        // If number
        if (isdigit(exp[i])) {
            num = 0;
            while (i < strlen(exp) && isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            i--; // step back
            push(num);
        }
        // If '('
        else if (exp[i] == '(') {
            pushOp(exp[i]);
        }
        // If ')'
        else if (exp[i] == ')') {
            while (opTop != -1 && peekOp() != '(') {
                int val2 = pop();
                int val1 = pop();
                char op = popOp();
                push(applyOp(val1, val2, op));
            }
            popOp(); // remove '('
        }
        // If operator
        else {
            while (opTop != -1 && precedence(peekOp()) >= precedence(exp[i])) {
                int val2 = pop();
                int val1 = pop();
                char op = popOp();
                push(applyOp(val1, val2, op));
            }
            pushOp(exp[i]);
        }
    }

    // remaining ops
    while (opTop != -1) {
        int val2 = pop();
        int val1 = pop();
        char op = popOp();
        push(applyOp(val1, val2, op));
    }

    return pop();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    printf("%d\n", evaluate(argv[1]));
    return 0;
}
