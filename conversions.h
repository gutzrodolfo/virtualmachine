/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date: 	    04/21/2014
Class:	    CSE 460 

Conversions.h
**********************************************/

#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

/*****************************************
 Decimal to binary function for POSTIVE int values. 
 Return type is a string. 
******************************************/ 

string dtb(int x, int sz){
	string s = "";
	while(x > 0){
		int bin = x % 2;
		stringstream out;
		out << bin;
		s += out.str();
		x = x/2;
	}
	reverse(s.begin(), s.end());
	if(s.size() < sz) {
		for(int i = 0; i <= s.size() - sz; i++) {
			s.insert(0, "0");
		}
	}
	return s;
}

/*****************************************
 Decimal to binary function for NEGATIVE int values. 
 Return type is a string. 
******************************************/ 

string dtb2(int x, int sz){
	if(x >= 0){
		return dtb(x, sz);    // If positive, call decimal to binary. 
	}
	else {
		string y;
		x *= -1;              // Negate the number
		y = dtb(x, sz);       // Take the number to get the binary form. 
        					  
    /*
    Take the 2's complement; 
    Negate the entire thing
	*/
		for (int i = 0; i < y.size(); i++) {
			if(y[i] == '1') { 
				y[i] = '0';
			}
			else {
				y[i] = '1';
			}
		}
	
	// Add 1 to the code
	
		for(int i = y.size() - 1; i >= 0; i--) {
			if(y[i] == '0') {
				y[i] = '1';
				break;
			}
			else {
				y[i] = '0';
			}
		}
		return y;
	}
}

/*****************************************
 Binary to decimal function. Return type is 
 a an int. 
******************************************/ 

 int btd(string code){
	int decimal = 0;
	for(int i = 0; i < code.size(); i++) {
		if(code[i] == '1'){
			decimal += pow(2, code.size() - i - 1);
		}
	}
	return decimal;
}

int btd2(string code){
	int decimal = 0;
	if (code[0] == '0') {
		return btd(code);
	}
	else {
		for (int i = 0; i < code.size(); i++) {
			if(code[i] == '1') { 
				code[i] = '0';
			}
			else {
				code[i] = '1';
			}
		}
		
		// Add 1 to the code
		
		for(int i = code.size() - 1; i >= 0; i--) {
			if(code[i] == '0') {
				code[i] = '1';
				break;
			}
			else {
				code[i] = '0';
			}
		}
	}
	decimal = -btd(code);
	return decimal;
}

int adder( int x, int y, char &i ) {
	string a = dtb2(x, 16);
	string b = dtb2(y, 16);
	string out = "0000000000000000";
	int carry = '0';
	for (int i = 0; i < 16; i++) {
		if(carry == '1' and a[15 - i] == '0' and b[15 - i] == '0') {
			out[i] = '1'; 
			carry = '0';
		}
		else if(carry == '0' and a[15 - i] == '1' and b[15 - i] == '0') {
			out[i] = '1'; 
		}
		else if(carry == '0' and a[15 - i] == '0' and b[15 - i] == '1') {
			out[i] = '1'; 
		}
		else if(carry == '1' and a[15 - i] == '1' and b[15 - i] == '1') {
			out[i] = '1';
			carry = '1'; 
		}
		else if(carry == '0' and a[15 - i] == '1' and b[15 - i] == '1') {
			out[i] = '0';
			carry = '1';
		}
		else {
			out[i] = '0';
		}
	}
	i = carry;
	reverse(out.begin(), out.end());
	return btd2(out);
}
