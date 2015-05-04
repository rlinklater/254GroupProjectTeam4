#include <string>
#include <iostream>
#include <vector>
#include "Command.h"

Command::Command(){
	//Constructor.  Initialize array.  Set base addresses for calculation.
	for (int i = 0; i < 45; i++){
		Data[i] = (unsigned long long int) 0;
	}
	SDBaseAddress = "40000818";
	DSBaseAddress = "40000C20";	
}
	
void Command::AddFirstLine(int Line, WhichCommand tempType, hexString LineCount){
	//Add the first line of a command block.  Also set object property for type of command.
	std::string ThisLine;
	Type = tempType;
	ThisLine = "Line " + std::to_string(Line) + ": ";
	if (Type == SDWrite) {ThisLine += "Write S-to-D command: ";}
	if (Type == SDRead) {ThisLine += "Read S-to-D command: ";}
	if (Type == DSWrite) {ThisLine += "Write D-to-S command: ";}
	if (Type == DSRead) {ThisLine += "Read D-to-S command: ";}
	ThisLine += std::to_string(LineCount.toInt()/2);   //2 bytes per word.
	ThisLine += " words";
	CommandsProcessed.push_back(ThisLine);	
}

Command::~Command() {}

void Command::AddData(int Line, std::string CommandData, hexString Address){
	//Add a line of data from the log file.
	//Type determines base address, which translates to array position.
	// (In a fuller implemenation, all Data spaces could be expected to be used.)
	if ((Type == SDRead) || (Type == SDWrite)) {
		Address -= SDBaseAddress;
	} else {
		Address -= DSBaseAddress;
	}
	//Calculate array position.
	int Position1 = Address.toInt();
	Position1 /= 2;
	int Position2 = Position1 + 1;
	std::string Command1 = CommandData.substr(0,4);
	std::string Command2 = CommandData.substr(4,4);
	//Store command in correct order (either descending or descending based on how 
	//commands are encountered in the log file.
	Data[Position1] = Command1;
	Data[Position2] = Command2;	
	if (LastPos == 0 && Position1 > 20){LastPos = 45;}
	if (LastPos <= Position1) { AddPrintLine(Line, Position1);}
	AddPrintLine(Line, Position2);
	if (LastPos > Position1){ AddPrintLine(Line, Position1);}
	LastPos = Position1;
}

bool Command::MoreCommands(){
	//For optionally printing a command line-by-line.  Determines if 
	//Commands remain to be printed.
	return (PrintCounter >= CommandsProcessed.size());
}

//A counter used if line-by-line printing is used.
void Command::ResetPrintPosition(){PrintCounter = 0;}

void Command::AddPrintLine(int Line, int Position){
	//Based on current data and address, create a string with the output line and store it
	//in commands processed vector.
	std::string ThisLine;
	ThisLine = "Line " + std::to_string(Line) + ": Word ";
	ThisLine += std::to_string(Position);
	ThisLine += ": ";
	switch (Position){
		case 0 : 	ThisLine += "Rec_Ctrl = " + getRec_Ctrl();break;
		case 1 : 	ThisLine += "Cmd_Type = " + getCmd_Type();break;
		case 4 : 	ThisLine += "Rec_Raw = " + getRec_Raw();break;
		case 5 : 	ThisLine += "Cmd_ID = " + getCmd_ID();	break;
		case 10 : 	ThisLine += "Num_Responses = " + getNum_Responses();break;
		case 15 : 	ThisLine += "Reset_Enable = " + getReset_Enable();break;
		case 22 : 	ThisLine += "Direction = " + getDirection();break;
		case 32 : 	ThisLine += "Num_Samples = " + getNum_Samples();break;
		case 37 : 	ThisLine += "Parity = " + getParity();break;
		case 38 : 	ThisLine += "Test = " + getTest();break;
		case 40 : 	ThisLine += "Ctrl_Enable = " + getCtrl_Enable();break;
		case 41 : 	ThisLine += "Code = " + getCode();break;
		default : return;
	}
	CommandsProcessed.push_back(ThisLine);	
}

std::string Command::FetchNextCommand(){
	//For optional line-by-line printing, get the next line of the
	//command block to print.
	std::string RetVal;
	if (PrintCounter < CommandsProcessed.size()){
		RetVal = CommandsProcessed[PrintCounter];
	}
	PrintCounter++;
	return RetVal;
}

std::string Command::PrintAllCommands(){
	//Return a single string with whole command block concatenated.  
	//Used in this project in main.
	std::string RetVal;
	for (int i = 0; i < CommandsProcessed.size(); i++){
		RetVal += CommandsProcessed[i] + "\n";
	}	
	if (RetVal != "") {RetVal += "\n";}
	return RetVal;	
}

void Command::Reset(){
	//Reset object (allows reuse of a single object for data collection.
	for (int i = 0; i < 45; i++){
		Data[i] = (unsigned long long int) 0;
	}
	CommandsProcessed.clear();
	PrintCounter = 0;
	LastPos = 0;
}

std::string Command::getRec_Ctrl()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[0].getBits(13, 14);
	switch (bitValue)
	{
		case 0: return "0 (no recording)";
		case 2: return "2 (no processing)";
		case 3: return "3 (processing & recording)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getCmd_Type()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[1].getBits(13, 15);
	switch (bitValue)
	{
		case 4: return "4 (Type A)";
		case 5: return "5 (Type B)";
		case 6: return "6 (Type C)";
	}
	return std::to_string(bitValue) + " (unknown)";
}
std::string Command::getRec_Raw()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[4].getBits(0);
	switch (bitValue)
	{
		case 0: return "0 (disable)";
		case 1: return "1 (enable)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getCmd_ID()
{
	//Get value of corresponding command from the log.
	return std::to_string(Data[5].getBits(0,6));
}

std::string Command::getNum_Responses()
{
	//Get value of corresponding command from the log.
	return std::to_string(Data[10].getBits(11,15));
}

std::string Command::getReset_Enable()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[15].getBits(2);
	switch (bitValue)
	{
		case 0: return "0 (disable)";
		case 1: return "1 (enable)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getDirection()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[22].getBits(3);
	switch (bitValue)
	{
		case 0: return "0 (Right)";
		case 1: return "1 (Left)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getNum_Samples()
{
	//Get value of corresponding command from the log.
	return std::to_string(Data[32].getBits(0,14));
}

std::string Command::getParity()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[37].getBits(15);
	switch (bitValue)
	{
		case 0: return "0 (even)";
		case 1: return "1 (odd)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getTest()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[38].getBits(14);
	switch (bitValue)
	{
		case 0: return "0 (disable)";
		case 1: return "1 (enable)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getCtrl_Enable()
{
	//Get value of corresponding command from the log.
	int bitValue = Data[40].getBits(7);
	switch (bitValue)
	{
		case 0: return "0 (disable)";
		case 1: return "1 (enable)";
	}
	return std::to_string(bitValue) + " (unknown)";
}

std::string Command::getCode()
{
	//Get value of corresponding command from the log.
	return std::to_string(Data[41].getBits(8,14));
}

