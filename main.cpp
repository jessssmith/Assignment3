#include "GenStack.h"
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
using namespace std;

int main(int argc, char** argv) {
  string file = ""; //name of the file
  int numLines = 0;
  char currDelimiter;
  char resp = 'y';
  int numErrors = 0;

  if(argc == 1) {
    //if the user put no command line arguments
    cerr << "Please enter the name of the file as a command line argument" << endl;
    exit(1);
  }
  else {
    //assign file name from command line argument to string variable
    file = argv[1];
  }

  while(numErrors == 0) {
    //create stack to store
    GenStack<char> *s = new GenStack<char>[2];

    ifstream inFile (file);

    //make sure the file was opened properly
    if(inFile.is_open()) {
      string line = "";
      while(getline(inFile, line)) {
        numLines++;
        for(int i = 0; i < line.length(); ++i) {
          //check for comments
          if(line.at(i) == '/' && line.at(i + 1) == '/')
            i = line.length();
          //check for strings
          else if(line.at(i) == '"') {
            //loop continue iterating through line in new loop until next " is found
            for(int j = i+1; j < line.length(); ++j) {
              if(line.at(j) == '"') {
                //continue original loop from this point
                i = j;
                //exit the nested loop
                j = line.length();
              }
            }
          }
          else if(line.at(i) == '{' || line.at(i) == '(' || line.at(i) == '[')
            s->push(line.at(i));
          //match closing delimiter with openging one from the stack 
          else if(line.at(i) == '}' || line.at(i) == ')' || line.at(i) == ']') {
            if(s->isEmpty() == false) {
              currDelimiter = s->pop();
              if(currDelimiter == '{' && line.at(i) != '}') {
                cout << file << " line " << numLines << ": error: expected '}' found " << line.at(i) << endl;
                exit(1);
              }
              else if(currDelimiter == '(' && line.at(i) != ')') {
                cout << file << " line " << numLines << ": error: expected ')' found " << line.at(i) << endl;
                exit(1);
              }
              else if(currDelimiter == '[' && line.at(i) != ']') {
                cout << file << " line " << numLines << ": error: expected ']' found " << line.at(i) << endl;
                exit(1);
              }
            }
            else {
              cout << file << " line " << numLines << ": error: reached end of file. Missing delimiter of type '" << line.at(i) << "'" << endl;
              exit(1);
            }
          }
        }
      }
      //close File
      inFile.close();
    }
    else {
      cerr << "File was not opened properly" << endl;
      exit(1);
    }

    //make sure there is nothing lest in the stack
    if(s->isEmpty() == false) {
      cout << file << " line " << numLines << ": error: reached end of file. Missing delimiter of type '" << s->pop() << "'" << endl;
      exit(1);
    }

  //prompt for new file or exit the program
    cout << file << " has no errors\nWould you like to check another file? (y/n) " << endl;
    cin >> resp;
    char c = tolower(resp);
    resp = c;
    if(resp == 'n')
      exit(1);
    if(resp == 'y') {
      cout << "Enter the name of the file you would like to check: " << endl;
      cin >> file;
      numErrors = 0;
    }
  }
}
