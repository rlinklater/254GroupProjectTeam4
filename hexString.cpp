#include <string>
#include <iostream>
#include <sstream>
#include "hexString.h"

hexString::hexString(){
	hexValue = "";
	intValue = -1;
}

hexString::hexString(std::string newHexString){
	std::string temp = "";
	
	//strip out any illegal characters and whitespace
	for (int j = 0; j < newHexString.length(); j++){
		if (isLegalChar(newHexString[j])) {
			temp += newHexString[j];
		}
		//Convert lowercase characters to uppercase  ASCII a-f
		if (newHexString[j] > 96 && newHexString[j] < 103){
			newHexString[j] -= 32;
			temp += newHexString[j];
		}
	}
		
	hexValue = temp;
	intValue = -1;
}

hexString::hexString(const char * newHexChar){
	std::string temp = "";
	std::string newHexString(newHexChar);
	
	//strip out any illegal characters and whitespace
	for (int j = 0; j < newHexString.length(); j++){
		if (isLegalChar(newHexString[j])) {
			temp += newHexString[j];
		}
		//Convert lowercase characters to uppercase  ASCII a-f
		if (newHexString[j] > 96 && newHexString[j] < 103){
			newHexString[j] -= 32;
			temp += newHexString[j];
		}
	}
		
	hexValue = temp;
	intValue = -1;
}

bool hexString::isLegalChar(char testChar){
	if (testChar > 47 && testChar < 58) {return true;}  //ASCII 0-9
	if (testChar > 64 && testChar < 71) {return true;}  //ASCII A-F
	return false;
}

hexString::hexString(unsigned long long int newHexString){
	intValue = newHexString;
	setHexValue();
}

hexString::~hexString(){

}

int hexString::getBits(int bit){
	return getBit((bit % 4), hexValue[int(bit/4)]);
}

int hexString::getBit(int whichBit, char hexChar){
	int value = hexToInt(hexChar);
	int bit[4] = {0,0,0,0};
	if (value > 7){bit[3] = 1; value -= 8;}
	if (value > 3){bit[2] = 1; value -= 4;}
	if (value > 1){bit[1] = 1; value -= 2;}
	bit[0] = value;
	return bit[whichBit];	
}

int hexString::getBits(int Bit1, int Bit2){
	int highBit, lowBit;
	
	if (Bit1 > Bit2){
		highBit = Bit1;
		lowBit = Bit2;
	} else {
		highBit = Bit2;
		lowBit = Bit1;
	}
	
	int j = highBit - lowBit;
	int pow = 1;
	int l = hexValue.length()-1;
	int retVal = 0;
	
	for (int i = 0; i <= j; i++){
		retVal += (getBit(((lowBit+i) % 4), hexValue[l-((lowBit+i)/4)]) * pow);
		pow *= 2;
	}
	return retVal;
}

unsigned long long int hexString::toInt(){
	if (intValue == -1){setIntValue();}
	return intValue;
}

int hexString::hexToInt(char Hex){
	std::string Numerals = "0123456789ABCDEF";
	for (int i = 0; i < 16; i++){
		if (Numerals[i] == Hex) {return i;}
	}
	return -1;
}

char hexString::intToHex(int Int){
	std::string Numerals = "0123456789ABCDEF";
	if (Int < 0 || Int > 16) {return -1;}
	return Numerals[Int];
}

void hexString::setIntValue(){
	unsigned long long int pow = 1;
	intValue = 0;
	
	for (int i = hexValue.length(); i > 0; i--) {
		intValue += pow * hexToInt(hexValue[i-1]);
		//std::cout << (i-1) << "   -   " << hexValue[i-1] << "   -   " << hexToInt(hexValue[i-1]) << "   -   " << pow  << "   -   " << intValue << "\n";
		pow *= 16;
	}	
}

void hexString::setHexValue(){
	unsigned long long int tempInt = intValue;
	hexValue = "";
	
	while (tempInt > 15) {
		hexValue = intToHex(tempInt%16) + hexValue;
		tempInt /= 16;
	}
	hexValue = intToHex(tempInt) + hexValue;	
} 

hexString& hexString::operator = (hexString Right){
	hexValue = Right.hexValue;
	return *this;
}

hexString& hexString::operator = (unsigned long long int  Right){
	intValue = Right;
	setHexValue();
	return *this;
}

hexString& hexString::operator = (std::string &Right){
	hexValue = Right;
	return *this;
}

hexString& hexString::operator = (const char *Right){
	hexValue = std::string(Right);
	return *this;
}

hexString& hexString:: operator += (hexString &Right){
	if (intValue == -1){setIntValue();}
	intValue += Right.toInt();
	setHexValue();
	return *this;
}

hexString& hexString:: operator += (unsigned long long int Right){
	if (intValue == -1){setIntValue();}
	intValue += Right;
	setHexValue();
	return *this;
}

hexString& hexString:: operator += (std::string &Right){
	if (intValue == -1){setIntValue();}
	intValue += hexString(Right).toInt();
	setHexValue();
	return *this;
}

hexString& hexString:: operator += (char &Right){
	if (intValue == -1){setIntValue();}
	intValue += hexString(Right).toInt();
	setHexValue();
	return *this;
}

hexString& hexString:: operator -= (hexString &Right){
	if (intValue == -1){setIntValue();}
	intValue -= Right.toInt();
	setHexValue();
	return *this;
}

hexString& hexString:: operator -= (unsigned long long int Right){
	if (intValue == -1){setIntValue();}
	intValue -= Right;
	setHexValue();
	return *this;
}

hexString& hexString:: operator -= (std::string &Right){
	if (intValue == -1){setIntValue();}
	intValue -= hexString(Right).toInt();
	setHexValue();
	return *this;
}

hexString& hexString:: operator -= (char &Right){
	if (intValue == -1){setIntValue();}
	intValue -= hexString(Right).toInt();
	setHexValue();
	return *this;
}

hexString hexString:: operator ++ (int){
	hexString temp(hexValue);	
	if (intValue == -1){setIntValue();}
	intValue++;
	setHexValue();
	return temp;
}

hexString& hexString:: operator ++ (){
	if (intValue == -1){setIntValue();}
	intValue++;
	setHexValue();
	return *this;
}

hexString hexString:: operator -- (int){
	hexString temp(hexValue);
	if (intValue == -1){setIntValue();}
	intValue--;
	setHexValue();
	return temp;
}

hexString& hexString:: operator -- (){
	if (intValue == -1){setIntValue();}
	intValue--;
	setHexValue();
	return *this;
}


std::ostream& operator<<(std::ostream &left, hexString &right){
	left << right.hexValue;
	return left;
}

bool operator < (hexString &Left, hexString &Right){return (Left.toInt() < Right.toInt());}
bool operator < (hexString &Left, unsigned long long int Right){return (Left.toInt() < Right);}
bool operator < (hexString &Left, std::string &Right){return (Left.toInt() < hexString(Right).toInt());}
bool operator < (unsigned long long int Left, hexString &Right){return (Left < Right.toInt());}
bool operator < (std::string &Left, hexString &Right){return (hexString(Left).toInt() < Right.toInt());}
bool operator < (hexString &Left, char &Right){return (Left.toInt() < hexString(Right).toInt());}
bool operator < (char &Left, hexString &Right){return (hexString(Left).toInt() < Right.toInt());}

bool operator <= (hexString &Left, hexString &Right){return (Left.toInt() <= Right.toInt());}
bool operator <= (hexString &Left, unsigned long long int Right){return (Left.toInt() <= Right);}
bool operator <= (hexString &Left, std::string &Right){return (Left.toInt() <= hexString(Right).toInt());}
bool operator <= (unsigned long long int Left, hexString &Right){return (Left <= Right.toInt());}
bool operator <= (std::string &Left, hexString &Right){return (hexString(Left).toInt() <= Right.toInt());}
bool operator <= (hexString &Left, char &Right){return (Left.toInt() <= hexString(Right).toInt());}
bool operator <= (char &Left, hexString &Right){return (hexString(Left).toInt() <= Right.toInt());}


bool operator > (hexString &Left, hexString &Right){return (Left.toInt() > Right.toInt());}
bool operator > (hexString &Left, unsigned long long int Right){return (Left.toInt() > Right);}
bool operator > (hexString &Left, std::string &Right){	return (Left.toInt() > hexString(Right).toInt());}
bool operator > (unsigned long long int Left, hexString &Right){return (Left > Right.toInt());}
bool operator > (std::string &Left, hexString &Right){return (hexString(Left).toInt() > Right.toInt());}	
bool operator > (hexString &Left, char &Right){return (Left.toInt() > hexString(Right).toInt());}
bool operator > (char &Left, hexString &Right){return (hexString(Left).toInt() > Right.toInt());}


bool operator >= (hexString &Left, hexString &Right){return (Left.toInt() >= Right.toInt());}
bool operator >= (hexString &Left, unsigned long long int Right){return (Left.toInt() >= Right);}
bool operator >= (hexString &Left, std::string &Right){return (Left.toInt() >= hexString(Right).toInt());}
bool operator >= (unsigned long long int Left, hexString &Right){return (Left >= Right.toInt());}
bool operator >= (std::string &Left, hexString &Right){return (hexString(Left).toInt() >= Right.toInt());}
bool operator >= (hexString &Left, char &Right){return (Left.toInt() >= hexString(Right).toInt());}
bool operator >= (char &Left, hexString &Right){return (hexString(Left).toInt() >= Right.toInt());}

		
bool operator == (hexString &Left, hexString &Right){return (Left.hexValue == Right.hexValue);}
bool operator == (hexString &Left, unsigned long long int Right){return (Left.toInt() == Right);}
bool operator == (hexString &Left, std::string &Right){return (Left.hexValue == Right);}
bool operator == (unsigned long long int Left, hexString &Right){return (Left == Right.toInt());}
bool operator == (std::string &Left, hexString &Right){return (Left == Right.hexValue);}
bool operator == (hexString &Left, char &Right){return (Left.toInt() == hexString(Right).toInt());}
bool operator == (char &Left, hexString &Right){return (hexString(Left).toInt() == Right.toInt());}

		
bool operator != (hexString &Left, hexString &Right){return (Left.hexValue != Right.hexValue);}
bool operator != (hexString &Left, unsigned long long int Right){return (Left.toInt() != Right);}
bool operator != (hexString &Left, std::string &Right){return (Left.hexValue != Right);}
bool operator != (unsigned long long int Left, hexString &Right){return (Left != Right.toInt());}
bool operator != (std::string &Left, hexString &Right){return (Left != Right.hexValue);}
bool operator != (hexString &Left, char &Right){return (Left.toInt() != hexString(Right).toInt());}
bool operator != (char &Left, hexString &Right){return (hexString(Left).toInt() != Right.toInt());}


hexString operator + (hexString Left, hexString Right){return (hexString(Left.toInt() + Right.intValue));}
hexString operator + (hexString Left, unsigned long long int Right){return (hexString(Left.toInt() + Right));}
hexString operator + (hexString Left, std::string &Right){return(hexString(Left.toInt() + hexString(Right).toInt()));}
hexString operator + (unsigned long long int Left, hexString Right){return (hexString(Left + Right.toInt()));}
hexString operator + (std::string &Left, hexString Right){return(hexString(hexString(Left).toInt() + Right.toInt()));}
hexString operator + (hexString Left, char &Right){return(hexString(Left.toInt() + hexString(Right).toInt()));}
hexString operator + (char &Left, hexString Right){return(hexString(hexString(Left).toInt() + Right.toInt()));}

hexString operator - (hexString Left, hexString Right){return (hexString(Left.toInt() - Right.intValue));}
hexString operator - (hexString Left, unsigned long long int Right){return (hexString(Left.toInt() - Right));}
hexString operator - (hexString Left, std::string &Right){return(hexString(Left.toInt() - hexString(Right).toInt()));}
hexString operator - (unsigned long long int Left, hexString Right){return(hexString(Left - Right.toInt()));}
hexString operator - (std::string &Left, hexString Right){return(hexString(hexString(Left).toInt() - Right.toInt()));}
hexString operator - (hexString Left, char &Right){return(hexString(Left.toInt() - hexString(Right).toInt()));}
hexString operator - (char &Left, hexString Right){return(hexString(hexString(Left).toInt() - Right.toInt()));}

