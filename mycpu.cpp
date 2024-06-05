#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <fstream>
#include <array>

#include "operations.cpp"


//#define BASIC_BIN_STRING "00000000"
//#define BASIC_BIN_STRING_SIZE 8



using namespace std;

string a(){
	return "hello";
}

string getLast8Symbols(string str) {
    if (str.length() < 8) {
        return str; 
    }
    return str.substr(str.length() - 8); 
}
/*
string getLastSymbols(string str, long unsigned int len) {
    if (str.length() < len) {
    	string freeString( len - str.length(), '0');
        return freeString + str; 
    }
    return str.substr(str.length() - len); 
}
*/

string bit16(string binNum){
	if (binNum.length() <= 16){
		string freeString( 16 - binNum.length(), '0');
		return freeString + binNum;
	}
	else{
		return getLastSymbols(binNum, 16);
	}
}

string bit8(string binNum){
	if (binNum.length() <= 8){
		string freeString( 8 - binNum.length(), '0');
		return freeString + binNum;
	}
	else{
		return getLastSymbols(binNum, 8);
	}
}

string bit4(string binNum){
	if (binNum.length() <= 4){
		string freeString( 4 - binNum.length(), '0');
		return freeString + binNum;
	}
	else{
		return getLastSymbols(binNum, 4);
	}
}



string bitAny(string binNum,  long unsigned int size){
	if (binNum.length() <= size){
		string freeString( size - binNum.length(), '0');
		return freeString + binNum;
	}
	else{
		return getLastSymbols(binNum, size);
	}
}
unsigned countBits(unsigned int number)
{    
	// log function in base 2
    // take only integer part
	return (int)log2(number)+1;
}

int binStringToInt(string text){
	int res = 0;

	int len = text.length();
	int i = len - 1;
	int j = 0;

	for(; i >= 0; i--, j++){
		if( text [i] == '1'){
			res += pow(2,j);
		}		
	}
	return res; 
}

string intToBinString( int num){
	if(num == 0){
		return "0";
	}
	int bits = countBits(num);
	
	string res(bits, '0');

	for(int i = 0, j = bits - 1; i < bits ; i++, j--){
		int numPower = pow(2, j);
		if(num - numPower >= 0){
			res[i] = '1';
			num -= numPower;
		}
			
	}
		
	return res;		
}

string intToBinStringSize( int num, int size){
	if(num == 0){
		string res(size, '0');
		return res;
	}
	int bits = countBits(num);
	
	string res(bits, '0');

	for(int i = 0, j = bits - 1; i < bits ; i++, j--){
		int numPower = pow(2, j);
		if(num - numPower >= 0){
			res[i] = '1';
			num -= numPower;
		}
			
	}
	
	return getLastSymbols(res, size);		
}


string hexToBinary( char symbol){
	string hexSymbols = "0123456789ABCDEF"; 
	for(int i = 0; i < 16; i ++){
		if(hexSymbols[i] == symbol){
			return intToBinStringSize(i, 4);
		}
	} 
	cout << "not a number" << endl;
	exit(1);
}

/*
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
*/

void cpu(bool cond, string line){ 
	string r0 = "0000"; 
	string r1 = "0000";
	string ip = "0000";
	string is = "0000";
	array<string, 16> arrayS;
	if(!cond){
		array<int, 16> arrayInt = {9,13,14,14,
						    	   5,7,13,10,
						    	   0,0,2,0,
						    	   0,4,15,0} ;
						 
		
		//cout << "1" << endl;
		for(int i = 0; i < 16; i ++){
			arrayS.at(i) = intToBinStringSize(arrayInt[i], 4);
		}
	}
	else{
		for(long unsigned int i = 0; i < line.length(); i ++){
			arrayS.at(i) = hexToBinary(line.at(i));
		}
	}
	//cout << "2" << endl;
	while(true){
		
		is = arrayS.at(binStringToInt(ip));

		cout << "r0: " << binStringToInt(r0) << " " << r0 << endl;
		cout << "r1: " << binStringToInt(r1) << " " << r1 << endl;
		cout << "ip: " << binStringToInt(ip) << " " << ip << endl;
		cout << "is: " << binStringToInt(is) << " " << is << endl << endl;

		
		if( is.compare("0000") == 0){ //0
			cout << "end" << endl;
			break;
		}
		else if( is.compare("0001") == 0){//1
			r0 = binarySum (r0,r1);
			ip = binarySum(ip, "0001");
		}	
		else if( is.compare("0010") == 0){ //2
			r0 = binarySubstract (r0,r1);
			ip = binarySum(ip, "0001");
		}
		else if( is.compare("0011") == 0){ //3
			r0 = binarySum(r0, "0001");
			ip = binarySum(ip, "0001");
		}		
		else if(is.compare("0100") == 0){ //4
			r1 = binarySum(r1, "0001");
			ip = binarySum(ip, "0001");
		}		
		else if( is.compare("0101") == 0){ //5
			//cout << "res before =" << r0 << endl;
			r0 = binarySubstract(r0, "0001");
			//cout << "res =" << r0 << endl;
			ip = binarySum(ip, "0001");
		}		
		else if( is.compare("0110") == 0){ //
			r1 = binarySubstract(r1, "0001");
			ip = binarySum(ip, "0001");
		}
		else if( is.compare("0111") == 0){ //7
			cout << "beep" << endl;
			ip = binarySum(ip, "0001");
		}
		else if( is.compare("1000") == 0){ //8
			cout << binStringToInt(arrayS.at(binStringToInt(ip) + 1)) << endl;
			ip = binarySum(ip, "0010");
		}			
		else if( is.compare("1001") == 0){ //9
			
			r0 = arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1)));
			ip = binarySum(ip, "0010");
		}		
		else if( is.compare("1010") == 0){ //10
			r1 = arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1)));
			cout << "r1: " << binStringToInt(r1) << endl;
			ip = binarySum(ip, "0010");
		}	
		else if( is.compare("1011") == 0){ //11
			arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1))) = r0;
			ip = binarySum(ip, "0010");
		}
		else if( is.compare("1100") == 0){ //12
			arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1))) = r1;
			ip = binarySum(ip, "0010");
		}		
		else if( is.compare("1101") == 0){ //13
			ip = arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1))); //+ 1    13 15
		}		
		else if( is.compare("1110") == 0){ //14
			if ( r0.compare("0000") == 0){
				ip = arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1)));	
			}	
			else{
				ip = binarySum(ip, "0010");
			}	
			
		}
		else if( is.compare("1111") == 0){ //15
			if (r0.compare("0000") != 0){
				ip = arrayS.at(binStringToInt (arrayS.at(binStringToInt(ip) + 1)));		
			}
			else{
				ip = binarySum(ip, "0010");
			}	
		}
		else{
			cout << "something went wrog" << endl;
			exit(1);
		}			

		sleep(1);
	} 
}




int main() {//int size, char** fileName
	/*if(size > 1){
		cout << size << endl;
		return 1;
	}*/
	//cout << fileName << endl;
	string str1 = "11111";
	string str2 = "000000011";
	string str3 = "19200012300";
	//unsigned char a = 254;
	//unsigned char res = a + 2;
	/*
    ifstream inputFile(fileName[1]);
	string line;
	
    if (inputFile.is_open()) {
        getline(inputFile, line);    
        inputFile.close();
    } else {
        cout << "Failed to open the file." << endl;
    }
	*/
	
	//cpu(false, line);
	cout << binaryDivision("1111", "0011" )<< endl ;//binStringToInt(binarySum(str1, str2)) //binarySumTest(str1, str2)


	
	return 0;
}
