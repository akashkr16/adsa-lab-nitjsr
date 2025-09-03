#include <stdio.h>
#include <ctype.h>   // for isdigit
#include <string.h>  // for strlen

#define MAX 100

// Stack implementation
char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop() {
    if (top >= 0)
        return stack[top--];
    return -1;
}

char peek() {
    if (top >= 0)
        return stack[top];
    return -1;
}

int precedence(char op) {
    if (op == '/' || op == '*')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    int i, k = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isdigit(c)) { // operand → directly to output
            postfix[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 && precedence(peek()) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }

    // pop remaining operators
    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
