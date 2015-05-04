#include <string>
#include <iostream>
#include <sstream>
#include "hexString.h"

hexString::hexString(){
	hexValue = "";
	intValue = -1;
}

hexString::hexString(const std::string newHexString){
	//Constructor from a string value.
	std::string temp = "";
	
	//strip out any illegal characters and whitespace
	for (int j = 0; j < newHexString.length(); j++){
		if (isLegalChar(newHexString[j])) {
			temp += newHexString[j];
		}
		//Convert lowercase characters to uppercase  ASCII a-f
		if (newHexString[j] > 96 && newHexString[j] < 103){
			char tempchar = newHexString[j] - 32;
			temp += tempchar;
		}
	}
		
	hexValue = temp;
	setIntValue();
}

hexString::hexString(const hexString& newHexString){
	//Constructor from another hexString
	hexValue = newHexString.hexValue;
	intValue = newHexString.intValue;
}

hexString::hexString(const char newHexChar[]){
	//Constructor from a string literal
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
	setIntValue();
}

bool hexString::isLegalChar(char testChar){
	//Determines if character is a hex character.
	if (testChar > 47 && testChar < 58) {return true;}  //ASCII 0-9
	if (testChar > 64 && testChar < 71) {return true;}  //ASCII A-F
	return false;
}

hexString::hexString(unsigned long long int newHexString){
	//Constructor from an int value.
	intValue = newHexString;
	setHexValue();
}

hexString::~hexString(){
	//Empty destructor.
}

int hexString::getBits(int bit){
	//One version of the getBits function, for a single bit.
	return getBit((bit % 4), hexValue[3 - (bit/4)]);
}

int hexString::getBit(int whichBit, char hexChar){
	//Internal function to set the value of bits mathematically.
	//Returns the requested bit.
	int value = hexToInt(hexChar);
	int bit[4] = {0,0,0,0};
	if (value > 7){bit[3] = 1; value -= 8;}
	if (value > 3){bit[2] = 1; value -= 4;}
	if (value > 1){bit[1] = 1; value -= 2;}
	bit[0] = value;
	return bit[whichBit];	
}

int hexString::getBits(int Bit1, int Bit2){
	//The other version of the getBits function, for multiple bits.
	int highBit, lowBit;
	
	//Order doesn't matter, this function determines which bit is higher and
	//responds properly.
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
	
	//Extract bits mathematically.
	for (int i = 0; i <= j; i++){
		retVal += (getBit(((lowBit+i) % 4), hexValue[l-((lowBit+i)/4)]) * pow);
		pow *= 2;
	}
	return retVal;
}

unsigned long long int hexString::toInt(){
	//Accessor for int value of teh hexString.
	return intValue;
}

//Accessor for string value of the hexString.
std::string hexString::toString(){return hexValue;}

int hexString::hexToInt(char Hex){
	//Internal function to get the int value of a hex character.
	std::string Numerals = "0123456789ABCDEF";
	for (int i = 0; i < 16; i++){
		if (Numerals[i] == Hex) {return i;}
	}
	return -1;
}

char hexString::intToHex(int Int){
	//Internal function to get the hex value of an int character.
	std::string Numerals = "0123456789ABCDEF";
	if (Int < 0 || Int > 16) {return -1;}
	return Numerals[Int];
}

void hexString::setIntValue(){
	//Internal function.  Convert hex to int using non-recursive method.
	unsigned long long int pow = 1;
	intValue = 0;
	
	for (int i = hexValue.length(); i > 0; i--) {
		intValue += pow * hexToInt(hexValue[i-1]);
		pow *= 16;
	}	
}

void hexString::setHexValue(){
	//Internal function. Convert int to hex using non-recursive method.
	unsigned long long int tempInt = intValue;
	hexValue = "";
	
	while (tempInt > 15) {
		hexValue = intToHex(tempInt%16) + hexValue;
		tempInt /= 16;
	}
	hexValue = intToHex(tempInt) + hexValue;	
} 

//Operator overloads follow.  All operators are designed to be used with any combination of hexString, int, string, and char (for string literals)

void hexString::operator = (const hexString& Right){
	hexValue = Right.hexValue;
	intValue = Right.intValue;
}

void hexString::operator = (const unsigned long long int  Right){
	intValue = Right;
	setHexValue();
}

void hexString::operator = (const std::string Right){
	std::string temp = "";
	
	//strip out any illegal characters and whitespace
	for (int j = 0; j < Right.length(); j++){
		if (isLegalChar(Right[j])) {
			temp += Right[j];
		}
		//Convert lowercase characters to uppercase  ASCII a-f
		if (Right[j] > 96 && Right[j] < 103){
			char tempchar = Right[j] - 32;
			temp += tempchar;
		}
	}
		
	hexValue = temp;
	setIntValue();;
}

void hexString::operator = (const char Right[]){
	std::string temp = "";
	std::string newHexString(Right);
	
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
	setIntValue();
}

void hexString::operator += (hexString Right){
	intValue += Right.toInt();
	setHexValue();
}

void hexString::operator += (const unsigned long long int Right){
	intValue += Right;
	setHexValue();
}

void hexString::operator += (const std::string Right){
	intValue += hexString(Right).toInt();
	setHexValue();
}

void hexString::operator += (const char Right[]){
	intValue += hexString(Right).toInt();
	setHexValue();
}

void hexString::operator -= (hexString Right){
	intValue -= Right.toInt();
	setHexValue();
}

void hexString::operator -= (const unsigned long long int Right){
	intValue -= Right;
	setHexValue();
}

void hexString::operator -= (const std::string Right){
	intValue -= hexString(Right).toInt();
	setHexValue();
}

void hexString::operator -= (const char Right[]){
	intValue -= hexString(Right).toInt();
	setHexValue();
}

void hexString::operator ++ (int){
	hexString temp(hexValue);	
	intValue++;
	setHexValue();
}

void hexString::operator ++ (){
	intValue++;
	setHexValue();
}

void hexString::operator -- (int){
	hexString temp(hexValue);
	intValue--;
	setHexValue();
}

void hexString::operator -- (){
	intValue--;
	setHexValue();
}


std::ostream& operator<<(std::ostream &left, hexString &right){
	left << right.hexValue;
	return left;
}

bool operator < ( hexString Left,  hexString Right){return (Left.toInt() < Right.toInt());}
bool operator < ( hexString Left,  unsigned long long int Right){return (Left.toInt() < Right);}
bool operator < ( hexString Left,  std::string Right){return (Left.toInt() < hexString(Right).toInt());}
bool operator < ( unsigned long long int Left,  hexString Right){return (Left < Right.toInt());}
bool operator < ( std::string Left,  hexString Right){return (hexString(Left).toInt() < Right.toInt());}
bool operator < ( hexString Left,  const char Right[]){return (Left.toInt() < hexString(Right).toInt());}
bool operator < ( const char Left[],  hexString Right){return (hexString(Left).toInt() < Right.toInt());}

bool operator <= ( hexString Left,  hexString Right){return (Left.toInt() <= Right.toInt());}
bool operator <= ( hexString Left,  unsigned long long int Right){return (Left.toInt() <= Right);}
bool operator <= ( hexString Left,  std::string Right){return (Left.toInt() <= hexString(Right).toInt());}
bool operator <= ( unsigned long long int Left,  hexString Right){return (Left <= Right.toInt());}
bool operator <= ( std::string Left,  hexString Right){return (hexString(Left).toInt() <= Right.toInt());}
bool operator <= ( hexString Left,  const char Right[]){return (Left.toInt() <= hexString(Right).toInt());}
bool operator <= ( const char Left[],  hexString Right){return (hexString(Left).toInt() <= Right.toInt());}


bool operator > ( hexString Left,  hexString Right){return (Left.toInt() > Right.toInt());}
bool operator > ( hexString Left,  unsigned long long int Right){return (Left.toInt() > Right);}
bool operator > ( hexString Left,  std::string Right){	return (Left.toInt() > hexString(Right).toInt());}
bool operator > ( unsigned long long int Left,  hexString Right){return (Left > Right.toInt());}
bool operator > ( std::string Left,  hexString Right){return (hexString(Left).toInt() > Right.toInt());}	
bool operator > ( hexString Left,  const char Right[]){return (Left.toInt() > hexString(Right).toInt());}
bool operator > ( const char Left[],  hexString Right){return (hexString(Left).toInt() > Right.toInt());}


bool operator >= ( hexString Left,  hexString Right){return (Left.toInt() >= Right.toInt());}
bool operator >= ( hexString Left,  unsigned long long int Right){return (Left.toInt() >= Right);}
bool operator >= ( hexString Left,  std::string Right){return (Left.toInt() >= hexString(Right).toInt());}
bool operator >= ( unsigned long long int Left,  hexString Right){return (Left >= Right.toInt());}
bool operator >= ( std::string Left,  hexString Right){return (hexString(Left).toInt() >= Right.toInt());}
bool operator >= ( hexString Left,  const char Right[]){return (Left.toInt() >= hexString(Right).toInt());}
bool operator >= ( const char Left[],  hexString Right){return (hexString(Left).toInt() >= Right.toInt());}

		
bool operator == ( hexString Left,  hexString Right){return (Left.hexValue == Right.hexValue);}
bool operator == ( hexString Left,  unsigned long long int Right){return (Left.toInt() == Right);}
bool operator == ( hexString Left,  std::string Right){return (Left.hexValue == Right);}
bool operator == ( unsigned long long int Left,  hexString Right){return (Left == Right.toInt());}
bool operator == ( std::string Left,  hexString Right){return (Left == Right.hexValue);}
bool operator == ( hexString Left,  const char Right[]){return (Left.toInt() == hexString(Right).toInt());}
bool operator == ( const char Left[],  hexString Right){return (hexString(Left).toInt() == Right.toInt());}

		
bool operator != ( hexString Left,  hexString Right){return (Left.hexValue != Right.hexValue);}
bool operator != ( hexString Left,  unsigned long long int Right){return (Left.toInt() != Right);}
bool operator != ( hexString Left,  std::string Right){return (Left.hexValue != Right);}
bool operator != ( unsigned long long int Left,  hexString Right){return (Left != Right.toInt());}
bool operator != ( std::string Left,  hexString Right){return (Left != Right.hexValue);}
bool operator != ( hexString Left,  const char Right[]){return (Left.toInt() != hexString(Right).toInt());}
bool operator != ( const char Left[],  hexString Right){return (hexString(Left).toInt() != Right.toInt());}


hexString operator + (const hexString Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() + Right.intValue;
	return RetVal;
}

hexString operator + (const hexString Left, const unsigned long long int Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() + Right;
	return RetVal;
}

hexString operator + (const hexString Left, const std::string Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() + hexString(Right).toInt();
	return RetVal;
}

hexString operator + (const unsigned long long int Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = Left + Right.intValue;
	return RetVal;
}

hexString operator + (const std::string Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() + Right.intValue;
	return RetVal;
}

hexString operator + (const hexString Left,  const char * Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() + hexString(Right).toInt();
	return RetVal;
}

hexString operator + (const char * Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() + Right.intValue;
	return RetVal;
}

hexString operator - (const hexString Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() - Right.intValue;
	return RetVal;
}

hexString operator - (const hexString Left, const unsigned long long int Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() - Right;
	return RetVal;
}

hexString operator - (const hexString Left, const std::string Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() - hexString(Right).toInt();
	return RetVal;
}

hexString operator - (const unsigned long long int Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = Left - Right.intValue;
	return RetVal;
}

hexString operator - (const std::string Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() - Right.intValue;
	return RetVal;
}

hexString operator - (const hexString Left,  const char * Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() - hexString(Right).toInt();
	return RetVal;
}

hexString operator - (const char * Left, const hexString Right){
	hexString RetVal;
	RetVal.intValue = hexString(Left).toInt() - Right.intValue;
	return RetVal;
}

