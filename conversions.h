#include <math.h>
#include <string>
#include <sstream>

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

string dtb2(int x, int sz){
	if(x >= 0){
		return dtb(x, sz);          //If positive just call decimal to binary
	}
	else {
		string y;
		x *= -1;                    //Negate the number
		y = dtb(x, sz);             //Take the number get the binary form
                                    //Take the 2's complement now
                                    //Negate the entire thing
		for (int i = 0; i < y.size(); i++) {
			if(y[i] == '1') { 
				y[i] = '0';
			}
			else {
				y[i] = '1';
			}
		}
		//Add 1 to the code
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
	for(int i = 1; i < code.size(); i++) {
		if(code[i] == '1'){
			decimal += pow(2, code.size() - i - 1);
		}
	}
	if (code[0] == '1') {
		decimal *= -1;
	}
	return decimal;
}

int adder(int x, int y, char &i) {
	string a = dtb2(x, 16);
	string b = dtb2(y, 16);
	string out = "0000000000000000";
	int carry = '0';
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < 16; i++) {
		if(carry == '1' and a[i] == '0' and b[i] == '0') {
			out[i] = '1'; 
			carry = '0';
		}
		else if(carry == '0' and a[i] == '1' and b[i] == '0') {
			out[i] = '1'; 
		}
		else if(carry == '0' and a[i] == '0' and b[i] == '1') {
			out[i] = '1'; 
		}
		else if(carry == '1' and a[i] == '1' and b[i] == '1') {
			out[i] = '1';
			carry = '1'; 
		}
		else if(carry == '0' and a[i] == '1' and b[i] == '1') {
			out[i] = '0';
			carry = '1';
		}
		else {
			out[i] = '0';
		}
	}
	i = carry;
	return btd2(out);
}
