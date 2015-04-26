#include <string>
#include <iostream>
#include <sstream>
 

class hexString{
 		friend std::ostream& operator<<(std::ostream &Left, hexString &Right);
		friend bool operator < (hexString &Left, hexString &Right);
		friend bool operator < (hexString &Left, unsigned long long int Right);
		friend bool operator < (hexString &Left, std::string &Right);
		friend bool operator < (unsigned long long int Left, hexString &Right);
		friend bool operator < (std::string &Left, hexString &Right);
		friend bool operator < (hexString &Left, char &Right);
		friend bool operator < (char &Left, hexString &Right);
		
		friend bool operator <= (hexString &Left, hexString &Right);
		friend bool operator <= (hexString &Left, unsigned long long int Right);
		friend bool operator <= (hexString &Left, std::string &Right);
		friend bool operator <= (unsigned long long int Left, hexString &Right);
		friend bool operator <= (std::string &Left, hexString &Right);
		friend bool operator <= (hexString &Left, char &Right);
		friend bool operator <= (char &Left, hexString &Right);
		
		friend bool operator > (hexString &Left, hexString &Right);
		friend bool operator > (hexString &Left, unsigned long long int Right);
		friend bool operator > (hexString &Left, std::string &Right);
		friend bool operator > (unsigned long long int Left, hexString &Right);
		friend bool operator > (std::string &Left, hexString &Right);
		friend bool operator > (hexString &Left, char &Right);
		friend bool operator > (char &Left, hexString &Right);

		friend bool operator >= (hexString &Left, hexString &Right);
		friend bool operator >= (hexString &Left, unsigned long long int Right);
		friend bool operator >= (hexString &Left, std::string &Right);
		friend bool operator >= (unsigned long long int Left, hexString &Right);
		friend bool operator >= (std::string &Left, hexString &Right);
		friend bool operator >= (hexString &Left, char &Right);
		friend bool operator >= (char &Left, hexString &Right);
		
		friend bool operator == (hexString &Left, hexString &Right);
		friend bool operator == (hexString &Left, unsigned long long int Right);
		friend bool operator == (hexString &Left, std::string &Right);
		friend bool operator == (unsigned long long int Left, hexString &Right);
		friend bool operator == (std::string &Left, hexString &Right);
		friend bool operator == (hexString &Left, char &Right);
		friend bool operator == (char &Left, hexString &Right);
		
		friend bool operator != (hexString &Left, hexString &Right);
		friend bool operator != (hexString &Left, unsigned long long int Right);
		friend bool operator != (hexString &Left, std::string &Right);
		friend bool operator != (unsigned long long int Left, hexString &Right);
		friend bool operator != (std::string &Left, hexString &Right);
		friend bool operator != (hexString &Left, char &Right);
		friend bool operator != (char &Left, hexString &Right);
		
		friend hexString operator + (hexString Left, hexString Right);
		friend hexString operator + (hexString Left, unsigned long long int Right);
		friend hexString operator + (hexString Left, std::string &Right);
		friend hexString operator + (unsigned long long int Left, hexString Right);
		friend hexString operator + (std::string &Left, hexString Right);
		friend hexString operator + (hexString Left, char &Right);
		friend hexString operator + (char &Left, hexString Right);
		
		friend hexString operator - (hexString Left, hexString Right);
		friend hexString operator - (hexString Left, unsigned long long int Right);
		friend hexString operator - (hexString Left, std::string &Right);
		friend hexString operator - (unsigned long long int Left, hexString Right);
		friend hexString operator - (std::string &Left, hexString Right);
		friend hexString operator - (hexString Left, char &Right);
		friend hexString operator - (char &Left, hexString Right);
	public:
		hexString();
		hexString(std::string newHexString);
		hexString(const char * newHexString);
		hexString(unsigned long long int newHexString);
		~hexString();
		int getBits(int Bit);
		int getBits(int Bit1, int Bit2);
		unsigned long long int toInt();
		
		hexString& operator = (hexString Right);
		hexString& operator = (unsigned long long int Right);
		hexString& operator = (std::string &Right);
		hexString& operator = (const char *Right);
		
		hexString& operator += (hexString &Right);
		hexString& operator += (unsigned long long int Right);
		hexString& operator += (std::string &Right);
		hexString& operator += (char &Right);
		
		hexString& operator -= (hexString &Right);
		hexString& operator -= (unsigned long long int Right);
		hexString& operator -= (std::string &Right);
		hexString& operator -= (char &Right);
		
		hexString operator ++ (int) ;
		hexString& operator ++ ();
		
		hexString operator -- (int);
		hexString& operator -- ();
	private:
		std::string hexValue;
		unsigned long long int intValue;
		
		bool isLegalChar(char testChar);
		int hexToInt(char Hex);
		char intToHex(int Int);
		void setIntValue();
		void setHexValue();
		int getBit(int WhichBit, char HexChar);
};