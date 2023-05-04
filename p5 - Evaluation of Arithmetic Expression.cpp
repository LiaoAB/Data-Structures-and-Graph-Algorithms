#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool isOperator(char ch);
int orderBy(char ch);
void convertPost(char input[], char post[], char variable[], double variable_value[], int pos, int check);
double countValue(char post[]);
string toString(double n);

int main() {
  // declare variable
  char input[500] = {'\0'}, post[500] = {'\0'}, variable[500] = {'\0'};
  double variable_value[500] = {0};
  int pos = 0;
  double value[52];

  // while getting input
  while (cin >> input) {
    int token = -1;
    
    // check if it has variable to be print,
    // or only calculate value
    if (input[0] >= 'a' && input[0] <= 'z'){
      token = input[0] - 'a';
    }
    if(input[0] >= 'A' && input[0] <= 'Z'){
      token = input[0] - 'A' + 26;
    }
    convertPost(input, post, variable, variable_value, pos, 0);
    double result = countValue(post);
    if (token != -1 && input[1] == '='){
      value[token] = result;
      cout << input[0] << "=" << result << endl;
    }else{
      cout << result << endl;
    }
    pos++;
  }

  return 0;
}
class Stack {
private:
  int topIndex;
  double *stack;

public:
  Stack() : topIndex(-1) { stack = new double[1]; }
  bool isEmpty();       // verify if the current stack is empty
  void push(double n); // put the element on the top of the stack
  void pop();           // pop off the element on the top of the stack
  double top();         // return the element on the top of the stack
  int size();           // return the stack size 
};

bool Stack::isEmpty() {
  // verify if the current stack is empty
  return (topIndex == -1);
}

void Stack::push(double n) {
  // put the element on the top of the stack
  stack[++topIndex] = n;
}

void Stack::pop() {
  if (isEmpty()) {
    // check if the stack is empty
    cout << "The stack is empty." << endl;
    return;
  }
  // pop off the element on the top of the stack
  stack[topIndex] = 0;
  topIndex--;
}

double Stack::top() {
  // return the element on the top of the stack
  if (isEmpty()) {
    return -1;
  }
  return stack[topIndex];
}

int Stack::size() {
  // return the stack size
  return topIndex + 1;
}

bool isOperator(char ch) {
  //check if the current character is an operator
  switch (ch) {
  case '+':
  case '-':
  case '*':
  case '/':
    return true;
  default:
    return false;
  }
}
int orderBy(char ch) {
  // define the order of the characters in mathematic
  switch (ch) {
  case '(':
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return -1;
  }
}

void convertPost(char input[], char post[], char variable[], double variable_value[], int pos, int check) {
  // declare a stack and give the initial elements in the stack
  Stack stk1;
  stk1.push('#');
  int i = 0, j = 0;

  // check if the character is an variable and already exists
  // if yes, count its value and store it in variable_value[]
  // if no, print "Variable does not exist." and return
  while (input[i] != '\0') {
    if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
      if (input[i + 1] == '=' && check == 0) {
        variable[pos] = input[i];
        convertPost(input, post, variable, variable_value, pos, 1);
        variable_value[pos] = countValue(post);
        pos++;
      } else {
        int k = 0;
        while (variable[k] != '\0') {
          if (input[i] == variable[k]) {
            const char *tmp;
            double tmpdb = variable_value[k];
            tmp = toString(tmpdb).c_str();
            int m = 0;
            while (tmp[m] != '\0') {
              post[j++] = tmp[m];
              m++;
            }
            break;
          }
          k++;
        }
        if(variable[k] == '\0'){
          cout << "Variable does not exist." <<endl;
          return;
        }
      }
    }

    // if current variable is number or .,
    // store into stack that defined in the first
    if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
      post[j++] = input[i];
    } else if (input[i] == '(') {
      stk1.push(input[i]);
    } else if (input[i] == ')') {
      while (stk1.top() != '(') {
        post[j++] = ' ';
        post[j++] = stk1.top();
        stk1.pop();
      }
      stk1.pop();
    } else if (isOperator(input[i])) {
      post[j++] = ' ';
      if (stk1.isEmpty()) {
        stk1.push(input[i]);
      } else {
        while (orderBy(input[i]) <= orderBy(stk1.top())) {
          post[j++] = stk1.top();
          post[j++] = ' ';
          stk1.pop();
        }
        stk1.push(input[i]);
      }
    }
    i++;
  }

  // while stack is not empty,
  // pop the top of the stack and store it into post[],
  // it will be use to count value
  while (stk1.size()) {
    post[j++] = ' ';
    post[j++] = stk1.top();
    stk1.pop();
  }
  post[j - 1] = '\0';
}

double countValue(char post[]) {
  // declare a stack and variables
  Stack stk1;
  int i = 0;
  double result = 0;
  double x1 = 0, x2 = 0;

  // while post[] is not empty -> more calculation needed
  while (post[i] != '\0') {
    // if you encounter a number, 
    // convert its value from a string to a number and save it
    if (post[i] >= '0' && post[i] <= '9') {
      double x = 0;
      int n = 0;
      while (post[i] >= '0' && post[i] <= '9') {
        x = x * 10 + (post[i] - '0');
        i++;
      }
      if (post[i] == '.') {
        i++;
        while (post[i] >= '0' && post[i] <= '9') {
          x = x * 10 + (post[i] - '0');
          i++;
          n++;
        }
      }
      while (n) {
        x /= 10;
        n--;
      }
      stk1.push(x);
    } else if (post[i] == ' ') {
      // if a space is encountered, skip to the next
      i++;
    } else if (post[i] == '+') {
      // if a '+' is encountered, 
      // count x2 + x1 and put it on top of the stack
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 + x1;
      stk1.push(temp);
      i++;
    } else if (post[i] == '-') {
      // if a '-' is encountered, 
      // count x2 - x1 and put it on top of the stack
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 - x1;
      stk1.push(temp);
      i++;
    } else if (post[i] == '*') {
      // if a '*' is encountered, 
      // count x2 * x1 and put it on top of the stack
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 * x1;
      stk1.push(temp);
      i++;
    } else if (post[i] == '/') {
      // if a '/' is encountered, 
      // count x2 / x1 and put it on top of the stack
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 / x1;
      stk1.push(temp);
      i++;
    }
  }

  // return the value on top of the stack
  result = stk1.top();
  return result;
}

string toString(double n) {
  // input a double, return it as a string
  stringstream ss;
  ss << n;
  return ss.str();
}
