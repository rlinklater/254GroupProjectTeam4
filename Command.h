#ifndef CommandClass
#define CommandClass
#include <string>
#include <vector>
#include "hexString.h"

enum WhichCommand {SDWrite, SDRead, DSWrite, DSRead};

class Command
{


	public:
		Command(int Line, WhichCommand Type, hexString LineCount);
		~Command();
		void AddData(int Line, std::string CommandData, hexString Address);
		std::string FetchNextCommand();
		std::string PrintAllCommands();
		bool MoreCommands();
		void ResetPrintPosition();
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

		hexString Data[45];
		std::vector<std::string> CommandsProcessed;
		int PrintCounter;
		hexString SDBaseAddress;
		hexString DSBaseAddress;
		WhichCommand Type;
		void AddPrintLine(int Line, int Position);




};

#endif
