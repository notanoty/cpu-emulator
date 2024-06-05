#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <fstream>
#include <array>


#include "spfunctions.cpp"

using namespace std;



string binarySum( string binary1, string binary2) {

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

    return res;
}




string binarySumTest(string binary1, string binary2){
	
	assert(binary1.length() == binary2.length()); 
	
	int len = binary1.length();
    string res = binary1; 
    
    for (int i = len - 1; i >= 0; i--) { // 10000 1
		if(binary2.at(i) == '1'){ 
			for(int j = i; j >= 0; j--){
				if(res.at(j) == '1'){
					res.at(j) = '0';
				}
				else{
					res.at(j) = '1';
					break;
				}
			}
		}	
    }
    return res;
}





string binarySubstract( string binary1, string binary2) {
	assert(binary1.length() == binary2.length()); 
	int len = binary1.length();
	
    string res(len, '0'); 
    
    int carry = 0;



    for (int i = len - 1; i >= 0; i--) {
        int digit1 = binary1[i] - '0'; 
        int digit2 = binary2[i] - '0'; 

        int sum = digit1 - digit2 -carry;
		if (sum == 1){
			res[i] = '1';	
			carry = 0;
		}
		else if ( sum == 0){
			res[i] = '0';
			carry = 0;	
		}
		else if ( sum == -1){
			res[i] = '1';
			carry = 1;	
		}
		else if( sum == -2){
			res[i] = '0';
			carry = 1;	
		}
		else{
			cout << "error in binarySubstract" << endl;
			exit(1);
		}
    }

    return res;
}

string increment(string binary1){

	int len = binary1.length();
    string binary2(len, '0');
    binary2.at(len - 1) = '1';
	return binarySum(binary1, binary2);

	
/*	int len = binary1.length();
    string res(len, '0');
    
    for (int i = len - 1; i >= 0; i--) { // 10000 1
		if(binary1.at(i) == '1'){ 
			res.at(i) = '0';
		}	
		else{
			res.at(i) = '1';
			break;
		}
    }
    return res;*/
}

string decrement(string binary1){
	int len = binary1.length();
    string binary2(len, '0');
    binary2.at(len - 1) = '1';
	return binarySubstract(binary1, binary2);
}


string binaryMultiplication(string binary1, string binary2) {
	assert(binary1.length() == binary2.length()); 
	int len = binary1.length();
	
    string res(len, '0'); 
	string zeros = "";

	for(int i = len - 1; i >= 0; i-- ){
		if(binary1[i] == '1'){

			string sum =  getLastSymbols(binary2 + zeros, len);

			res = binarySum(sum , res);
			res = getLastSymbols(res, len);

		}
		zeros = '0' + zeros;
	}	
	return res;
}

string equalSizes(string binaryNum,int len ){
	string freeString(len - binaryNum.length(), '0');
	return  freeString + binaryNum;
}

string binaryDivision(string binary1, string binary2) { // !!!!!!!!
	assert(binary2.length() == binary2.length());

    int len = binary1.length();
    string res;
	string diviser = "";
    string dividend = "";
    for (int i = 0; i < len; i++) {
   	//	if(){
   			
   	//	}
    }

    return res;
}






/*
int main(){
	cout << decrement("000000") << endl;
}*/
