#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>

/**
* This is a simple script create in order to make file respect 80 columns
* usage:
*	- compilation: g++ eightyColumns.cpp
*	- execution  : ./a.out <file_name> <number_of_columns>
* if no <number_of_columns> is passed, the default is 80
*/

const char * wrapper(char* buffer, const char* string, 
	const int & stringSize, const int & wrapSize) {
	int i = 0;
	int k, counter;
	while(i < stringSize) {
		for ( counter = 1; counter <= wrapSize; counter++ ) {
			if ( i == stringSize) {
				buffer[i] = 0;
				return buffer;
			}
			buffer[i] = string[i];
			if (buffer[i] == '\n') {
				counter = 1;
			}
			i++;
		}
		if (isspace(string[i])) {
			buffer[i] = '\n';
			i++;
		} else {
			for (k=i; k>0; k--) {
				if (isspace(string[k])) {
					buffer[k] = '\n';
					i=k+1;
					break;
				}
			}
		}
	}
	buffer[i] = 0;
	return buffer;
}

std::string wordwrap(const std::string & str, const int & wrapsize) {

	int stringSize = str.size();
	const char* toWrap = str.c_str();
	char buffer[stringSize] = {0};
	return wrapper(buffer, toWrap, stringSize, wrapsize);
}

std::string readFileToString(const std::string & filename) {
	std::ifstream in(filename.c_str());
	std::string s((std::istreambuf_iterator<char>(in)),
			(std::istreambuf_iterator<char>()));
	return s;
}

void writeToFile(const std::string & filename, const std::string & str) {
	std::ofstream out(filename.c_str());
    out << str;
    out.close();
}

int main(int argc,  char * argv[]) {
	std::string filename(argv[1]);
	int wrapsize;
	
	if (argc < 2) {
		std::cout<<"not enough arguments"<<std::endl;
		throw "not enough arguments";
	} else if (argc == 2)
		wrapsize = 80;
	else if (argc == 3)
		wrapsize = atoi(argv[2]);
	// args from 4th are discarded

	// check if columns are passed as number
	if (!wrapsize){
		std::cout<<"Error : invalid number of columns passed as argument"
			<<std::endl;
		throw "invalid number of columns passed as argument";
	}
	
	writeToFile(filename, wordwrap(readFileToString(filename), wrapsize));
}

