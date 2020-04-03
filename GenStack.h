#include <iostream>
using namespace std;

template <class T>
class GenStack {
  public:
    GenStack(); //default constructor
    GenStack(int maxSize); //overload constructor
    ~GenStack(); //destructor

    //functions
    void push(T c);
    T pop();

    //helper functions
    bool isFull();
    bool isEmpty();
    T peek();

    //variables
    int mSize; //max size of stack
    int top; //keeps track of indicies representing top of the stack

    T *myArray;
};


//default constructor
template <class T>
GenStack<T>::GenStack() {
  myArray = new T[128];
  mSize = 128;
  top = -1;
}

//overload constructor
template <class T>
GenStack<T>::GenStack(int maxSize) {
  myArray = new T[maxSize];
  mSize = maxSize;
  top = -1;
}

//destructor
template <class T>
GenStack<T>::~GenStack() {
  delete myArray;
  cout << "Array has been deleted" << endl;
}

//push, also increases size if stack is full
template <class T>
void GenStack<T>::push(T c) {
  if(isFull() == true) {
    //create new stack with double the space
    T* newStack = new T[mSize * 2];

    //fill the new stack with values from the old stack
    for(int i = 0; i < mSize; ++i) {
      newStack[i] = myArray[i];
    }

    //delete the old stack array
    delete myArray; // i dont think this is properly deleting the old array
    //rename newStack to myArray
    myArray = newStack;
    //update max size variable
    mSize *= 2;
  }
  //push new value to the stack
  myArray[++top] = c;
}

//pop
template <class T>
T GenStack<T>::pop() {//not done
  if(isEmpty() == true) {
    cout << "Error: The stack is empty.\n";
    exit(1);
  }
  else
    return myArray[top--];
}

//check if empty
template <class T>
bool GenStack<T>::isEmpty() {
  return top == -1;
}

//check if full
template <class T>
bool GenStack<T>::isFull() {
  return top == mSize-1;
}

//peek
template <class T>
T GenStack<T>::peek() {
  if(isEmpty() == true) {
    cout << "Error: The stack is empty.";
    exit(1);
  }
  else
    return myArray[top];
}
