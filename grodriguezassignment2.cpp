#include <iostream>
#include <cstring>
#include <stack>

int findPosition(std::string str) {
    //create a stack to hold the brackets
    std::stack<char> temp;
    int index = 0;
    int position = 0;

    for (char c : str) {
        index++;
        
        //only runs if a bracket is used
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            //if the stack is empty...
            if (temp.empty()) {
                //add character to it
                temp.push(c);
                position = index; //precaution if the first item is a closing bracket
            } else if (temp.top() == '(' && c == ')') {
                temp.pop(); //removes ( from temp if a matching ) is found in str
            } else if (temp.top() == '[' && c == ']') {
                temp.pop(); //removes [ from temp if a matching ] is found in str
            } else if (temp.top() == '{' && c == '}') {
                temp.pop(); //removes { from temp if a matching } is found in str
            } else {
                
                //adds the bracket if it's another opening one
                temp.push(c);
                position = index;

            }
        }
    }
    
    return position;
}
    
bool isBalanced(std::string str) {
        //create a stack to hold the brackets
    std::stack<char> temp;
    int position;

    for (char c : str) {
        //only runs if a bracket is used
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            //if the stack is empty...
            if (temp.empty()) {
                //add character to it
                temp.push(c);
            } else if (temp.top() == '(' && c == ')') {
                temp.pop(); //removes ( from temp if a matching ) is found in str
            } else if (temp.top() == '[' && c == ']') {
                temp.pop(); //removes [ from temp if a matching ] is found in str
            } else if (temp.top() == '{' && c == '}') {
                temp.pop(); //removes { from temp if a matching } is found in str
            } else {
                //adds the bracket if it's another opening one
                temp.push(c);
            }
        }
    }

    //after revising all brackets, a balanced equation should leave temp empty
    if (temp.empty()) {
        return true;
    } else {
        return false;
    }
}

int main() {
    //variables
    std::string s;
    
    //prompt user to enter a line
    std::cout << "Please enter your line of code: " << std::endl;
    getline(std::cin, s, '\n');

    //check if code is balanced and output results
    if (isBalanced(s) == 0) {
        std::cout << "The expression is not balanced!" << std::endl;
        std::cout << "The error begins at position " << findPosition(s) << "." << std::endl;
    } else if (isBalanced(s) == 1) {
        std::cout << "The expression is balanced!" << std::endl;
        std::cout << "Every bracket is in its pair." << std::endl;
    }

    return 0;
}