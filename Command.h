#include <string>
#include <vector>
#include "hexString.h"

class Command
{


	public:
		Command();
		~Command();
		std::string getRec_Ctrl();
		int getCmd_Type();
		string getRec_Raw();
		int getCmd_ID();
		int getNum_Responses();
		string getReset_Enable();
		string getDirection();
		int getNum_Samples();
		string getParity();
		string getTest();
		string getCtrl_Enable();
		int getCode();





	private:

		std::vector<hexString> Data;	




};
