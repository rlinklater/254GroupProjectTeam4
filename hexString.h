#ifndef hexStringClass
#define hexStringClass
#include <string>
#include <iostream>
#include <sstream>
 

class hexString{
 		friend std::ostream& operator<<(std::ostream &Left, hexString &Right);
		friend bool operator < ( hexString Left,  hexString Right);
		friend bool operator < ( hexString Left,  unsigned long long int Right);
		friend bool operator < ( hexString Left,  std::string Right);
		friend bool operator < ( unsigned long long int Left,  hexString Right);
		friend bool operator < ( std::string Left,  hexString Right);
		friend bool operator < ( hexString Left,  const char Right[]);
		friend bool operator < ( const char Left[],  hexString Right);
		
		friend bool operator <= ( hexString Left,  hexString Right);
		friend bool operator <= ( hexString Left,  unsigned long long int Right);
		friend bool operator <= ( hexString Left,  std::string Right);
		friend bool operator <= ( unsigned long long int Left,  hexString Right);
		friend bool operator <= ( std::string Left,  hexString Right);
		friend bool operator <= ( hexString Left,  const char Right[]);
		friend bool operator <= ( const char Left[],  hexString Right);
		
		friend bool operator > ( hexString Left,  hexString Right);
		friend bool operator > ( hexString Left,  unsigned long long int Right);
		friend bool operator > ( hexString Left,  std::string Right);
		friend bool operator > ( unsigned long long int Left,  hexString Right);
		friend bool operator > ( std::string Left,  hexString Right);
		friend bool operator > ( hexString Left,  const char Right[]);
		friend bool operator > ( const char Left[],  hexString Right);

		friend bool operator >= ( hexString Left,  hexString Right);
		friend bool operator >= ( hexString Left,  unsigned long long int Right);
		friend bool operator >= ( hexString Left,  std::string Right);
		friend bool operator >= ( unsigned long long int Left,  hexString Right);
		friend bool operator >= ( std::string Left,  hexString Right);
		friend bool operator >= ( hexString Left,  const char Right[]);
		friend bool operator >= ( const char Left[],  hexString Right);
		
		friend bool operator == ( hexString Left,  hexString Right);
		friend bool operator == ( hexString Left,  unsigned long long int Right);
		friend bool operator == ( hexString Left,  std::string Right);
		friend bool operator == ( unsigned long long int Left,  hexString Right);
		friend bool operator == ( std::string Left,  hexString Right);
		friend bool operator == ( hexString Left,  const char Right[]);
		friend bool operator == ( const char Left[],  hexString Right);
		
		friend bool operator != ( hexString Left,  hexString Right);
		friend bool operator != ( hexString Left,  unsigned long long int Right);
		friend bool operator != ( hexString Left,  std::string Right);
		friend bool operator != ( unsigned long long int Left,  hexString Right);
		friend bool operator != ( std::string Left,  hexString Right);
		friend bool operator != ( hexString Left,  const char Right[]);
		friend bool operator != ( const char Left[],  hexString Right);
		
		friend hexString operator + (const hexString Left, const hexString Right);
		friend hexString operator + (const hexString Left, const unsigned long long int Right);
		friend hexString operator + (const hexString Left, const std::string Right);
		friend hexString operator + (const unsigned long long int Left, const hexString Right);
		friend hexString operator + (const std::string Left, const hexString Right);
		friend hexString operator + (const hexString Left, const char * Right);
		friend hexString operator + (const char * Left, const hexString Right);
		
		friend hexString operator - (const hexString Left, const hexString Right);
		friend hexString operator - (const hexString Left, const unsigned long long int Right);
		friend hexString operator - (const hexString Left, const std::string Right);
		friend hexString operator - (const unsigned long long int Left, const hexString Right);
		friend hexString operator - (const std::string Left, const hexString Right);
		friend hexString operator - (const hexString Left, const char * Right);
		friend hexString operator - (const char * Left, const hexString Right);
	public:
		hexString();
		hexString(const std::string newHexString);
		hexString(const hexString& newHexString);
		hexString(const char newHexString[] );
		hexString(unsigned long long int newHexString);
		~hexString();
		int getBits(int Bit);
		int getBits(int Bit1, int Bit2);
		unsigned long long int toInt();
		std::string toString();
		
		void operator = (const hexString& Right);
		void operator = (const unsigned long long int Right);
		void operator = (const std::string Right);
		void operator = (const char Right[]);
		
		void operator += (hexString Right);
		void operator += (const unsigned long long int Right);
		void operator += (const std::string Right);
		void operator += (const char Right[]);
		
		void operator -= (hexString Right);
		void operator -= (const unsigned long long int Right);
		void operator -= (const std::string Right);
		void operator -= (const char Right[]);
		
		void operator ++ (int) ;
		void operator ++ ();
		
		void operator -- (int);
		void operator -- ();
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

#endif