#include <string>
#include <iostream>
#include <vector>
#include "Command.h"

Command::Command(int Line, WhichCommand Type, hexString LineCount){
	SDBaseAddress = "40000818";
	DSBaseAddress = "40000C20";
	string ThisLine;
	ThisLine = "Line " + Line + ": ";
	if (Tpye == WhichCommand.SDWrite) {ThisLine += "Write S-to-D command: ";}
	if (Tpye == WhichCommand.SDRead) {ThisLine += "Read S-to-D command: ";}
	if (Tpye == WhichCommand.DSWrite) {ThisLine += "Write D-to-S command: ";}
	if (Tpye == WhichCommand.DSRead) {ThisLine += "Write D-to-S command: ";}
	ThisLine += std::to_string(LineCount.toInt());
	ThisLine += " words";
	CommandsProcessed.push_back(ThisLine);	
	
}

Command::~Command() {}

void Command::AddData(int Line, string CommandData, hexString Address){
	hexString Position;
	Position = Address;
	if ((Type == WhichCommand.SDRead) || (Type == WhichCommand.SDWrite)) {
		Position -= SDBaseAddress;
	} else {
		Position -= DSBaseAddress;
	}
	int Position1 = Position.toInt();
	Position1 /= 16;
	int Position2 = Position1 + 1;
	string Command1 = CommandData.substr(0,4);
	string Command2 = CommandData.substr(4,4);
	Data[Position1] = Command1;
	Data[Position2] = Command2;
	
	AddPrintLine(Line, Position1);
	AddPrintLine(Line, Position2);	
}

bool MoreCommands(){
	return (PrintCounter >= CommandsProcessed.size());
}

void ResetPrintPosition(){PrintCounter = 0;}

void AddPrintLine(int Line, int Position){
	string ThisLine;
	ThisLine = "Line " + Line + ": Word ";
	ThisLine += std::to_string(Position);
	ThisLine += ": ";
	switch (Position){
		case 0 : ThisLine += "Rec_Ctrl = " + getRec_Ctrl();
		case 1 : ThisLine += "Cmd_Type = " + getCmd_Type();
		case 4 : ThisLine += "Rec_Raw = " + getRec_Raw();
		case 5 : ThisLine += "Cmd_ID = " + getCmd_ID();
		case 10 : ThisLine += "Num_Responses = " + getNum_Responses();
		case 15 : ThisLine += "Reset_Enable = " + getReset_Enable();
		case 22 : ThisLine += "Direction = " + getDirection();
		case 32 : ThisLine += "Num_Samples = " + getNum_Samples();
		case 37 : ThisLine += "Parity = " + getParity();
		case 38 : ThisLine += "Test = " + getTest();
		case 40 : ThisLine += "Ctrl_Enable = " + getCtrl_Enable();
		case 41 : ThisLine += "Code = " + getCode();
	}
	
}

std::string Command::FetchNextCommand(){
	string RetVal;
	if (PrintCounter < CommandsProcessed.size()){
		RetVal << CommandsProcessed[PrintCounter];
	}
	PrintCounter++;
	return RetVal;
}

std::string Command::PrintAllCommands(){
	for (int i = 0; i < CommandsProcessed.size(); i++){
		cout << CommandsProcessed[i] << endl;
	}	
}

std::string Command::getRec_Ctrl()
{
	int bitValue = Data[0].getBits(13, 14);
	switch (bitValue)
	{
		case 0: return "No recording";
		case 2: return "No processing";
		case 3: return "Processing and recording";
	}
}

std::string Command::getCmd_Type()
{
	int bitValue = Data[1].getBits(13, 15);
	switch (bitValue)
	{
		case 4: return "Type A";
		case 5: return "Type B";
		case 6: return "Type C";
	}
}
std::string Command::getRec_Raw()
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

std::string Command::getReset_Enable()
{
	int bitValue = Data[15].getBits(2);
	switch (bitValue)
	{
		case 0: return "Disable";
		case 1: return "Enable";
		
	}
}

std::string Command::getDirection()
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

std::string Command::getParity()
{
	int bitValue = Data[37].getBits(15);
	switch (bitValue)
	{
		case 0: return "Even";
		case 1: return "Odd";
		
	}
}

std::string Command::getTest()
{
	int bitValue = Data[38].getBits(14);
	switch (bitValue)
	{
		case 0: return "Disable";
		case 1: return "Enable";
		
	}
}

std::string Command::getCtrl_Enable()
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

