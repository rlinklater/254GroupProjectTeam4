#include <string>
#include <iostream>
#include <vector>
#include "Command.h"

using namespace std;

Command::Command()
{
	Data = {};	// populate Data vector
}

Command::~Command() {}




string Command::getRec_Ctrl()
{
	int bitValue = Data[0].getBits(13, 14);
	switch (bitValue)
	{
		case 0: return "No recording";
		case 2: return "No processing";
		case 3: return "Processing and recording";
	}
}

int Command::getCmd_Type()
{
	// to be filled...
}

bool Command::getRec_Raw()
{
	// to be filled...
}

int Command::getCmd_ID()
{
	// to be filled...
}

int Command::getNum_Responses()
{
	// to be filled...
}

bool Command::getReset_Enable()
{
	// to be filled...
}

bool Command::getDirection()
{
	// to be filled...
}

int Command::getNum_Samples()
{
	// to be filled...
}

bool Command::getParity()
{
	// to be filled...
}

bool Command::getTest()
{
	// to be filled...
}

bool Command::getCtrl_Enable()
{
	// to be filled...
}

int Command::getCode()
{
	// to be filled...
}

