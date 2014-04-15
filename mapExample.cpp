#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;
void f1(){cout << "test worked1"<< endl;}
void f2(){cout << "test worked2"<< endl;}
void f3(){cout << "test worked3"<< endl;}

int main(){


typedef void (*pfunc)();

map<string, pfunc> funcMap; 
funcMap["f1"] = f1; //and so forth
funcMap["f2"] = f2;
funcMap["f3"] = f3;

pfunc f = funcMap["f1"];
(*f)(); 
}
