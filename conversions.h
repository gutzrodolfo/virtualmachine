#include <math.h>
#include <string>
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
