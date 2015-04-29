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
	int bitValue = Data[1].getBits(13, 15);
	switch (bitValue)
	{
		case 4: return "Type A";
		case 5: return "Type B";
		case 6: return "Type C";
	}
}
string Command::getRec_Raw()
{
	int bitValue = Data[4].getBits(0);
	switch (bitValue)
	{
		case 0: return "Disable";
		case 1: return "Enable";
		
	}
}

int Command::getCmd_ID()
{
	return Data[5].getBits(0,6);
	
}

int Command::getNum_Responses()
{
	return Data[10].getBits(11,15);
}

string Command::getReset_Enable()
{
	int bitValue = Data[15].getBits(2);
	switch (bitValue)
	{
		case 0: return "Disable";
		case 1: return "Enable";
		
	}
}

string Command::getDirection()
{
	int bitValue = Data[22].getBits(3);
	switch (bitValue)
	{
		case 0: return "Right";
		case 1: return "Left";
		
	}
}

int Command::getNum_Samples()
{
	return Data[32].getBits(0,14);
}

string Command::getParity()
{
	int bitValue = Data[37].getBits(15);
	switch (bitValue)
	{
		case 0: return "Even";
		case 1: return "Odd";
		
	}
}

string Command::getTest()
{
	int bitValue = Data[38].getBits(14);
	switch (bitValue)
	{
		case 0: return "Disable";
		case 1: return "Enable";
		
	}
}

string Command::getCtrl_Enable()
{
	int bitValue = Data[40].getBits(7);
	switch (bitValue)
	{
		case 0: return "Disable";
		case 1: return "Enable";
		
	}
}

int Command::getCode()
{
	return Data[41].getBits(8,14);
}

