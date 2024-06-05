#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <fstream>
#include <array>
#include <regex>


#include "operations.cpp"
//#include "spfunctions.cpp"

 

string commandAssembly(smatch matches){
    //cout << text << endl;

    int num = stoi(matches[3].str() );
    //cout  << matches[0].str() << " -> " << getOperationCodeName(matches[1].str()) +  getPrefix(matches[2].str()) + intToBinStringSize(num, 10) << endl; 
    return getOperationCodeName(matches[1].str()) +  getPrefix(matches[2].str()) + intToBinStringSize(num, 10);	
}

string getDataNumbers(string data){
    //int num = stoi(data );
    return	intToBinStringSize(stoi(data), 16);
}

string assembly(string text){
    vector<string> resVector= {};
    
    //regex rgx("(^\n*)[\n(^\n*)]*");
    vector<string> commands = splitString(text);

    regex rgxNormal(" *(\\w+) +([=$@])?(\\d+) *(?:;.+|.*)"); 
    regex rgxData(" *DATA +(\\d+[ *, *\\d+ *]*) *(?:;.+|.*)");
    regex rgxORG(" *ORG +(\\d+) *(?:;.+|.*)");
    regex rgxBSS(" *BSS +(\\d+) *(?:;.+|.*)");
    regex rgxEMPTY(" *(?:;.+|.*)"); 
    if(commands.size() != 0){
	int words = 0; 
	int previousIndex = 1; 
	string origin;
	for (size_t i = 0; i < commands.size(); i++  ) {
	    smatch matches;
	    //cout <<  i << ": "<<"words = " << words << endl;
	    if(regex_match(commands[i], rgxData)){
			regex_search(commands[i], matches, rgxData);
			vector<string> data =  splitStringSymbol( matches[1].str(), ',');
			words +=  data.size();
			for(size_t j = 0; j < data.size(); j++){
			    resVector.push_back(getDataNumbers(data[j]));	
			}
			//cout << matches[1].str() << endl;
	    }			
	    else if(regex_match(commands[i], rgxORG)){ 
			regex_search(commands[i], matches, rgxORG);
			origin = intToBinStringSize( stoi(matches[1].str()) , 10);
			resVector.push_back(origin);
			resVector.push_back("placeholder ORG"); 
			resVector.at(previousIndex) = intToBinStringSize(words, 10);
			previousIndex = resVector.size() - 1; 
			words = 0; 
		
	    }			
	    else if(regex_match(commands[i], rgxBSS)){ 
			regex_search(commands[i], matches, rgxBSS);
			resVector.push_back( binarySum( binarySum(origin, intToBinStringSize(words, 10)) , intToBinStringSize(stoi(matches[1].str()),10) ));
			resVector.push_back("placeholder BSS"); 
			resVector.at(previousIndex) = intToBinStringSize(words, 10);
			previousIndex = resVector.size() - 1; 
			words = 0; 
		
	    }
	    else if( regex_match(commands[i], rgxNormal)){
			regex_search(commands[i], matches, rgxNormal);
			resVector.push_back(commandAssembly(matches)); 
			words ++; 
			//int num = stoi(matches[3].str() );
			//resVector.push_back(getOperationCodeName(matches[1].str()) +  getPrefix(matches[2].str()) + intToBinStringSize(num, 10));	
	    }	
	    else if( !regex_match(commands[i], rgxEMPTY)){
			cout << "Text does not match" << endl;
	    }	
	
	}
	cout <<  "words = " << words << endl;
	resVector.at(previousIndex) = intToBinStringSize(words, 10);
	    
    }
    else{
	cout << "something went wrong" << endl;
	exit(1);
    }
    //string str = 
    //cout << __FUNCTION__ << " finished" << endl;
    return vecToString(resVector);//resVector; string str(vect.begin(),vect.end())
    //return ")";
}


void initializeMemory (vector<string>& memory){
    for(size_t i = 0; i < memory.size(); i ++){
		string cell(16, '0');
		memory[i] = cell;  
    }
    //cout << __FUNCTION__ << " finished" << endl;
    //return memory;
}
vector<string> allocMemory(string bigBinNumber){
	
	int size = 0;
	
	while(bigBinNumber.length() != 0 ){
		int origin = binStringToInt(bigBinNumber.substr(0,10));	
		int words = binStringToInt(bigBinNumber.substr(10,10));
		bigBinNumber = bigBinNumber.substr(20);	
		
		if(size < words + origin){
			size = words + origin;
		}
		int endPoint = origin + words;
		for(int i = origin; i < endPoint; i += 1){
		   	bigBinNumber = bigBinNumber.substr(16);
		} 
				
	}  
	vector<string> res(size + 1);
	initializeMemory(res);
	//cout << __FUNCTION__ << " finished" << endl;
	return res;	
}


vector<string> writeBinCode(string bigBinNumber){
   	vector<string> memory = allocMemory(bigBinNumber);
    //initializeMemory(memory);
    

    while(bigBinNumber.length() != 0 ){
		int origin = binStringToInt(bigBinNumber.substr(0,10));	
		int words = binStringToInt(bigBinNumber.substr(10,10));	
		//cout << "words = " << words << endl; 
		//cout << "origin id = " << origin << endl << "words = " << words << endl;
	    bigBinNumber = bigBinNumber.substr(20);
		int endPoint = origin + words;
		for(int i = origin; i < endPoint; i += 1){
		    memory.at(i) = bigBinNumber.substr(0,16);
		    cout << "number = " << 	getOperationFieldName(getOperationField(memory.at(i))) << "(" << binStringToInt(memory.at(i)) << ")"<< endl; 
		    bigBinNumber = bigBinNumber.substr(16);
		} 	
    }
    //cout << __FUNCTION__ << " finished" << endl;
    return memory;
}
// name("add 5 \n load 10 \n data 32, 48 ") -> ("1000 00 0000000000","0001 00 0000000000",  ["0100000000000000", "000010010000100000"] data  )
