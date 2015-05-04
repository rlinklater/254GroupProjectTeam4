#ifndef CommandClass
#define CommandClass
#include <string>
#include <vector>
#include "hexString.h"

enum WhichCommand {SDWrite, SDRead, DSWrite, DSRead};

class Command
{


	public:
		Command();
		~Command();
		void AddFirstLine(int Line, WhichCommand Type, hexString LineCount);
		void AddData(int Line, std::string CommandData, hexString Address);
		std::string FetchNextCommand();
		std::string PrintAllCommands();
		bool MoreCommands();
		void ResetPrintPosition();
		void Reset();
		std::string getRec_Ctrl();
		std::string getCmd_Type();
		std::string getRec_Raw();
		std::string getCmd_ID();
		std::string getNum_Responses();
		std::string getReset_Enable();
		std::string getDirection();
		std::string getNum_Samples();
		std::string getParity();
		std::string getTest();
		std::string getCtrl_Enable();
		std::string getCode();

	private:

		hexString Data[45];
		std::vector<std::string> CommandsProcessed;
		int PrintCounter;
		hexString SDBaseAddress;
		hexString DSBaseAddress;
		WhichCommand Type;
		void AddPrintLine(int Line, int Position);
		int LastPos;
};

#endif
