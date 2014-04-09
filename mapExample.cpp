#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;
void f1(string params){cout << "test worked1"<< endl;}
void f2(string params){cout << "test worked2"<< endl;}
void f3(string params){cout << "test worked3"<< endl;}

int main(){


typedef void (*pfunc)(string);

map<string, pfunc> funcMap; 
funcMap["f1"] = f1; //and so forth
funcMap["f2"] =f2;
funcMap["f3"] =f3;

pfunc f = funcMap["f1"];
(*f)("Test"); 
}
