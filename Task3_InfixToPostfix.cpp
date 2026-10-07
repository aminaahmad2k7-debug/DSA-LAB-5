#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Node for character stack (operators)
struct CharNode {
    char data;
    CharNode* next;
    CharNode(char c) : data(c), next(nullptr) {}
};

// Character Stack
class CharStack {
private:
    CharNode* topNode;
public:
    CharStack() : topNode(nullptr) {}
    ~CharStack() { clear(); }

    void push(char c) {
        CharNode* newNode = new CharNode(c);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        CharNode* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char top() const {
        if (isEmpty()) return '\0';
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void clear() {
        while (!isEmpty()) pop();
    }
};

// Node for number stack (evaluation)
struct NumNode {
    double data;
    NumNode* next;
    NumNode(double d) : data(d), next(nullptr) {}
};

// Number Stack for evaluation
class NumStack {
private:
    NumNode* topNode;
public:
    NumStack() : topNode(nullptr) {}
    ~NumStack() { clear(); }

    void push(double d) {
        NumNode* newNode = new NumNode(d);
        newNode->next = topNode;
        topNode = newNode;
    }

    double pop() {
        if (isEmpty()) return 0.0;
        NumNode* temp = topNode;
        double val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    double top() const {
        if (isEmpty()) return 0.0;
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void clear() {
        while (!isEmpty()) pop();
    }
};

// Precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

// Check if character is operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

// Convert Infix to Postfix
string infixToPostfix(const string& infix, CharStack& opStack) {
    opStack.clear();
    string postfix = "";

    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];

        // Skip whitespace
        if (isspace(c)) continue;

        // Operand (digit) - support multi-digit numbers
        if (isdigit(c)) {
            string numStr = "";
            while (i < infix.length() && isdigit(infix[i])) {
                numStr += infix[i];
                i++;
            }
            i--; // adjust for loop increment
            postfix += numStr + " ";
        }
        // Opening parenthesis
        else if (c == '(') {
            opStack.push(c);
        }
        // Closing parenthesis
        else if (c == ')') {
            while (!opStack.isEmpty() && opStack.top() != '(') {
                postfix += opStack.pop();
                postfix += " ";
            }
            if (opStack.isEmpty() || opStack.top() != '(') {
                return "";  // Mismatched parentheses
            }
            opStack.pop(); // remove '('
        }
        // Operator
        else if (isOperator(c)) {
            while (!opStack.isEmpty() && opStack.top() != '(' &&
                precedence(opStack.top()) >= precedence(c)) {
                postfix += opStack.pop();
                postfix += " ";
            }
            opStack.push(c);
        }
        else {
            return "";  // Invalid character
        }
    }

    // Pop remaining operators
    while (!opStack.isEmpty()) {
        if (opStack.top() == '(') {
            return "";  // Mismatched parentheses
        }
        postfix += opStack.pop();
        postfix += " ";
    }

    // Trim trailing space
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

// Evaluate Postfix expression
bool evaluatePostfix(const string& postfix, NumStack& numStack, double& result) {
    numStack.clear();

    if (postfix.empty()) {
        return false;
    }

    size_t i = 0;
    while (i < postfix.length()) {
        // Skip spaces
        while (i < postfix.length() && isspace(postfix[i])) i++;
        if (i >= postfix.length()) break;

        // Number
        if (isdigit(postfix[i])) {
            string numStr = "";
            while (i < postfix.length() && isdigit(postfix[i])) {
                numStr += postfix[i];
                i++;
            }
            double num = stod(numStr);
            numStack.push(num);
        }
        // Operator
        else if (isOperator(postfix[i])) {
            if (numStack.isEmpty()) return false;
            double b = numStack.pop();
            if (numStack.isEmpty()) return false;
            double a = numStack.pop();

            char op = postfix[i];
            double res = 0.0;

            switch (op) {
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/':
                if (b == 0.0) {
                    cout << "Error: Division by zero!" << endl;
                    return false;
                }
                res = a / b;
                break;
            case '%':
                if (b == 0.0) {
                    cout << "Error: Modulus by zero!" << endl;
                    return false;
                }
                res = fmod(a, b);
                break;
            default:
                return false;
            }
            numStack.push(res);
            i++;
        }
        else {
            return false;
        }
    }

    if (numStack.isEmpty()) return false;
    result = numStack.pop();

    if (!numStack.isEmpty()) return false;

    return true;
}

// Check for balanced parentheses
bool hasBalancedParentheses(const string& expr) {
    CharStack s;
    for (char c : expr) {
        if (c == '(') s.push(c);
        else if (c == ')') {
            if (s.isEmpty()) return false;
            s.pop();
        }
    }
    return s.isEmpty();
}

int main() {
    CharStack opStack;
    NumStack numStack;
    string expr;
    char choice;

    cout << "=== Task 3: Infix to Postfix Conversion and Evaluation ===" << endl;
    cout << "Linked Stack Implementation" << endl << endl;

    do {
        cout << "Enter an arithmetic expression: ";
        getline(cin, expr);

        if (expr.empty()) {
            cout << "Error: Empty expression." << endl;
        }
        else if (!hasBalancedParentheses(expr)) {
            cout << "Error: Mismatched parentheses." << endl;
        }
        else {
            string postfix = infixToPostfix(expr, opStack);

            if (postfix.empty()) {
                cout << "Error: Invalid expression or mismatched parentheses." << endl;
            }
            else {
                cout << "\nPostfix Expression: " << postfix << endl;

                double result = 0.0;
                bool success = evaluatePostfix(postfix, numStack, result);

                if (success) {
                    cout << "Result: " << result << endl;
                }
                else {
                    cout << "Evaluation failed." << endl;
                }
            }
        }

        // Clear stacks
        opStack.clear();
        numStack.clear();

        cout << endl;
        cout << "Do you want to evaluate another expression? (y/n): ";
        cin >> choice;
        cin.ignore();

        cout << "----------------------------------------" << endl;

    } while (choice == 'y' || choice == 'Y');

    cout << "Program ended. All memory released." << endl;

    return 0;
}