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
		bool getRec_Raw();
		int getCmd_ID();
		int getNum_Responses();
		bool getReset_Enable();
		bool getDirection();
		int getNum_Samples();
		bool getParity();
		bool getTest();
		bool getCtrl_Enable();
		int getCode();





	private:

		std::vector<hexString> Data;	




};