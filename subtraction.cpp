#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <fstream>
#include <array>
#include <regex>


#include "spfunctions.cpp"

using namespace std; 

string sum(string num1, string num2){
	if( num1.length() != num2.length()){
		throw invalid_argument("num1 and num2 should be the same size");
	}

	int rest = 0;
	string res(num1.length(), '0');
	
	for(int i = num1.length() - 1 ; i >= 0; i--){
		int resFull  = num1[i] + num2[i] + rest - '0'*2;  
		res[i] = resFull%10 + '0';
		rest = resFull/10;
	}
		
	///if(rest != 0 ){
		//cout << rest << " - res" << endl;
	//}*/
	return res;	
}

string nineCompliment(string num){
	string maxNum(num.length(), '9');
	string res(num.length(), '0');
	
	for(int i = num.length() - 1 ; i >= 0; i--){
		int resFull  = maxNum[i] - num[i] ;  
		res[i] = resFull + '0';
	}
	return res;
}

string tenCompliment(string num){
	string one(num.length(), '0');
	one[num.length() - 1] = '1';
	return sum(nineCompliment(num), one);
}


string usub(string num1, string num2){
	if( num1.length() != num2.length()){
		throw invalid_argument("num1 and num2 should be the same size");
	}
	string res = sum(num1 , tenCompliment(num2));
	return res;	
}
string printuSub(string num){		
	if(num[0] == '9'){
		num = tenCompliment(num);//'-' + res;
		num = num.substr(1);
		num = '-' + num;
	}
	else{
		num = num.substr(1);
	}
	return num;
}



/*string usum2(string num1, string num2){
	if( num1.length() != num2.length()){
		throw invalid_argument("num1 and num2 should be the same size");
	}
	string returnNumber(num1.length(), '0');
	returnNumber[num1.length() - 1] = '1';
	//int ost;
	//return sum(sub9(sum(sum(num1 , sub9(num2)), returnNumber), ost),returnNumber, ost );
	return "a";
	
}*/


string binarySum( string binary1, string binary2, int& ostReturn) {

	assert(binary1.length() == binary2.length()); 
	
	int len = binary1.length();
	
    string res(len, '0'); 
    
    int carry = 0;

    for (int i = len - 1; i >= 0; i--) {
        int digit1 = binary1.at(i) - '0';
        int digit2 = binary2.at(i) - '0'; 

        int sum = digit1 + digit2 + carry;

        res[i] = char(sum % 2 + '0');

        carry = sum / 2; 
    }
	ostReturn = carry;
    return res;
}

string binarySubstract( string binary) {
	int len = binary.length();
    string res(len, '0'); 
    
    for (int i = len - 1; i >= 0; i--) {

		if(binary[i] == '0'){
			res[i] = '1';
		}
		else if(binary[i] == '1'){
			res[i] = '0';
		}
		else{
			throw invalid_argument("num should is not 0 or 1");
		}
        // =  binaryM[i] - binary[i] + '0';2
		
    }

    return res;
}

string increment(string binary1){
	int len = binary1.length();
    string binary2(len, '0');
    binary2.at(len - 1) = '1';
    int ostIgnored;
	return binarySum(binary1, binary2, ostIgnored);
}


string ubinarySub(string binary1, string binary2){
	if( binary1.length() != binary2.length()){
		throw invalid_argument("binary1 and binary2 should be the same size");
	}	
	int ost;

	string res = increment(binarySum(binary1 , binarySubstract(binary2), ost));
	//cout << res << endl;
	if(ost == 0){
		res = increment(binarySubstract(res));//'-' + res;
		res = '+' + res;
	} 
	
	return res;
}



int main(){
	//int ost;
	//cout << binarySum("100", "010", ost) << endl<< "ost = " << ost << endl;  
	cout << "res = " << printuSub(sum(usub("0111", "0123" ), "0001" )) <<  endl;  
}
