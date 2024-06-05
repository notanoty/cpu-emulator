#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <fstream>
#include <array>
#include <regex>

using namespace std;


string getLastSymbols(string str, long unsigned int len) {
    if (str.length() < len) {
    	string freeString( len - str.length(), '0');
        return freeString + str; 
    }
    return str.substr(str.length() - len); 
}

string vecToString(vector<string> a)
{
    int i;
	int size = a.size();
    string s = "";
    
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


string getOperationField(string operation){
	assert(operation.length() == 16);
	return operation.substr(0,4);
}
 
string getAdressModeField(string operation){
	assert(operation.length() == 16);
	return operation.substr(4,2);
} 

string getAddressField(string operation){
	assert(operation.length() == 16);
	return operation.substr(6);
} 

string getOperationFieldName(string command){
		if( command.compare("0000") == 0){ //     0 	HATL
			return string("HALT");
		}
		else if( command.compare("0001") == 0){// 1  	LOAD
			return string("LOAD");
		}	
		else if( command.compare("0010") == 0){ //2 	STORE
			return string("STORE");
		}
		else if( command.compare("0011") == 0){ //3 	CALL 
			return string("CALL");
		}		
		else if(command.compare("0100") == 0){ // 4		BR
			return string("BR");
		}		
		else if( command.compare("0101") == 0){ //5 	BREQ
			return string("BREQ");
		}		
		else if( command.compare("0110") == 0){ //6 	BRGE
			return string("BRGE");
		}
		else if( command.compare("0111") == 0){ //7 	BRLT
			return string("BRLT");
		}
		else if( command.compare("1000") == 0){ //8 	ADD
			return string("ADD");
		}			
		else if( command.compare("1001") == 0){ //9 	SUB
			return string("SUB");
		}		
		else if( command.compare("1010") == 0){ //10 	MUL 
			return string("MUL");
		}	
		else if( command.compare("1011") == 0){ //11 	DIV
			return string("DIV");
		}	
		else if( command.compare("1100") == 0){ //11 	PRINT
			return string("PRINT");
		}
		else{
			cout << endl << "this command does not exist: " << command<< endl;
			exit(1);
			
		}			
}



string getOperationCodeName(string command){
		if( command.compare("HALT") == 0){ //     0 	HATL
			return string("0000");
		}
		else if( command.compare("LOAD") == 0){// 1  	LOAD
			return string("0001");
		}	
		else if( command.compare("STORE") == 0){ //2 	STORE
			return string("0010");
		}
		else if( command.compare("CALL") == 0){ //3 	CALL 
			return string("0011");
		}		
		else if(command.compare("BR") == 0){ // 4		BR
			return string("0100");
		}		
		else if( command.compare("BREQ") == 0){ //5 	BREQ
			return string("0101");
		}		
		else if( command.compare("BRGE") == 0){ //6 	BRGE
			return string("0110");
		}
		else if( command.compare("BRLT") == 0){ //7 	BRLT
			return string("0111");
		}
		else if( command.compare("ADD") == 0){ //8 	ADD
			return string("1000");
		}			
		else if( command.compare("SUB") == 0){ //9 	SUB
			return string("1001");
		}		
		else if( command.compare("MUL") == 0){ //10 	MUL 
			return string("1010");
		}	
		else if( command.compare("DIV") == 0){ //11 	DIV
			return string("1011");
		}	
		else if( command.compare("PRINT") == 0){ //11 	PRINT
			return string("1100");
		}
		else{
			cout << endl << "this command does not exist: \"" << command<<"\"" << endl;
			exit(1);
			
		}			
}
string getPrefix(string command){
		if( command.compare("") == 0){ //     0 	HATL
			return string("00");
		}
		else if( command.compare("=") == 0){// 1  	LOAD
			return string("01");
		}	
		else if( command.compare("$") == 0){ //2 	STORE
			return string("10");
		}
		else if( command.compare("@") == 0){ //3 	CALL 
			return string("11");
		}		
		else{
			cout << endl << "this smt does not exist" << endl;
			exit(1);		
		}			
}
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

vector<string> splitStringSymbol(string str, char symbol)
{
    std::vector<std::string> tokens;
 
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, symbol)) {
        tokens.push_back(token);
    }
 
    return tokens;
}

vector<string> splitString(string str)
{
    std::vector<std::string> tokens;
 
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, '\n' )) {
        tokens.push_back(token);
    }
 
    return tokens;
}
