#ifndef CommandClass
#define CommandClass
#include <string>
#include <vector>
#include "hexString.h"

class Command
{


	public:
		Command();
		~Command();
		std::string getRec_Ctrl();
		std::string getCmd_Type();
		std::string getRec_Raw();
		int getCmd_ID();
		int getNum_Responses();
		std::string getReset_Enable();
		std::string getDirection();
		int getNum_Samples();
		std::string getParity();
		std::string getTest();
		std::string getCtrl_Enable();
		int getCode();





	private:

		std::vector<hexString> Data;	




};

#endif
