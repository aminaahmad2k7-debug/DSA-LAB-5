#include <iostream>
#include <string>
using namespace std;

// Node for character stack
struct CharNode {
    char data;
    CharNode* next;
    CharNode(char c) : data(c), next(nullptr) {}
};

// Linked-node Stack for characters
class CharStack {
private:
    CharNode* topNode;
public:
    CharStack() : topNode(nullptr) {}

    ~CharStack() {
        clear();
    }

    void push(char c) {
        CharNode* newNode = new CharNode(c);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        CharNode* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char top() const {
        if (isEmpty()) {
            return '\0';
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        CharNode* current = topNode;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Function to check if brackets match
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}

// Check balance of parentheses, brackets, braces
bool checkBalance(const string& expr, CharStack& stack) {
    stack.clear();

    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.isEmpty()) {
                return false;   // Extra closing bracket
            }
            char topChar = stack.pop();
            if (!isMatchingPair(topChar, c)) {
                return false;   // Mismatched brackets
            }
        }
    }

    return stack.isEmpty();     // Extra opening brackets if not empty
}

int main() {
    CharStack stack;
    string expr;
    char choice;

    cout << "=== Task 1: Expression Parentheses Checker ===" << endl;
    cout << "Linked Stack Implementation" << endl << endl;

    do {
        cout << "Enter an expression: ";
        getline(cin, expr);

        bool balanced = checkBalance(expr, stack);

        cout << "\nExpression: \"" << expr << "\"" << endl;
        if (balanced) {
            cout << "Result: Balanced" << endl;
        }
        else {
            cout << "Result: Not Balanced" << endl;
        }

        cout << "Stack status ";
        stack.display();
        cout << endl;

        // Optional: Demonstrate stack operations
        cout << "Do you want to test another expression? (y/n): ";
        cin >> choice;
        cin.ignore();   // clear the newline left by cin

        cout << "----------------------------------------" << endl;

    } while (choice == 'y' || choice == 'Y');

    // Final demonstration of stack operations
    cout << "\n=== Stack Operations Demo ===" << endl;
    stack.clear();
    stack.push('(');
    stack.push('[');
    stack.push('{');
    cout << "After pushing '(', '[', '{':" << endl;
    stack.display();
    cout << "Top element: " << stack.top() << endl;
    cout << "IsEmpty: " << (stack.isEmpty() ? "Yes" : "No") << endl;
    cout << "Popped: " << stack.pop() << endl;
    stack.display();
    stack.clear();
    cout << "After clear:" << endl;
    stack.display();

    return 0;
}