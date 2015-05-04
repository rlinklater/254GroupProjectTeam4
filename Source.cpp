#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "hexString.h"
#include "Command.h"
using namespace std;


hexString dataline(string s);//takes the string from the data column
hexString addressline(string s);//takes the string from the address column
string rwline(string s);
double ReadTime(string s);
string GetTotalTime(double cmdTime, int cmdCount);

int main(int argc, char* argv[])
{	//grabs "log.txt" from the current directory
	//Setup input and output files.  Input specified on command line.  Output is "output.log"
	string outFileName = "output.log";
	string filename = argv[1];
	ifstream opener;
	opener.open(filename.c_str());
	if (!opener.is_open())
	{
		cout << "Could not open the input file!\n";
		return 1;
	}
	
	ofstream outFile;
	outFile.open(outFileName, ios::out);
	if (!outFile.is_open())
	{
		cout << "Could not open the output file!\n";
		return 1;
	}

	//main functions
	string line;
	int counter = 0;

	//Object to hold the data for each command.
	Command cmd;

	hexString data;  			//takes data from data column
	hexString address;			//takes address from the address column

	hexString s_tod = "40000810";  	// Address of S-D command start
	hexString stodlow = "40000818"; 	// Address range of S-D command data
	hexString stodhigh ="40000C14";
	hexString d_tos = "40000C18";   	// Address of D-S command start
	hexString dtoslow = "40000C20";	// Address range of D-S command data
	hexString dtoshigh = "4000101C";
	double cmdTime[4] = {0,0,0,0};
	int cmdCount[4] = {0,0,0,0};
	WhichCommand cmdCurrent;
	bool GetTime = false;

	//loop through each line and extract commands where found.
	while (getline(opener, line)) 
	{//81-88
		
		counter++;
		
		//don't try to process empty lines
		if (line == ""){continue;}
		
		//extract data and address of current line
		address=addressline(line);
		data=dataline(line);
		
		//see if time should be checked (based on command in previous line.
		if (GetTime) {
			cmdCount[cmdCurrent]++;
			cmdTime[cmdCurrent] += ReadTime(line);
		}
		GetTime = false;

		if(address >= stodlow && address <= stodhigh) //s-to-d instructions
		{
			cmdCurrent = (rwline(line) == "Wr" ? SDWrite : SDRead);
			cmd.AddData(counter, data.toString(), address);
			GetTime = true;
		}
		else if(address >= dtoslow && address <= dtoshigh) //d-to-s instructions
		{
			cmdCurrent = (rwline(line) == "Wr" ? DSWrite : DSRead);
			cmd.AddData(counter, data.toString(), address);
			GetTime = true;
		}
		if (address == s_tod) //start of s-d block
		{
			outFile << cmd.PrintAllCommands();
			cmd.Reset();
			cmdCurrent = (rwline(line) == "Wr" ? SDWrite : SDRead);
			cmd.AddFirstLine(counter, cmdCurrent , data);
			GetTime = true;
		}
		else if (address == d_tos) // start of d-s block
		{
			outFile << cmd.PrintAllCommands();
			cmd.Reset();
			cmdCurrent = (rwline(line) == "Wr" ? DSWrite : DSRead);
			cmd.AddFirstLine(counter, cmdCurrent, data);
			GetTime = true;
		}
	}
	
	//output the current command at the end.
	outFile << cmd.PrintAllCommands();
	
	//output time statistics
	outFile <<  "Read S-to-D: " << GetTotalTime(cmdTime[SDRead], cmdCount[SDRead]) << endl;
	outFile <<  "Read D-to-S: " << GetTotalTime(cmdTime[DSRead], cmdCount[DSRead]) << endl;
	outFile <<  "Write S-to-D: " << GetTotalTime(cmdTime[SDWrite], cmdCount[SDWrite]) << endl;
	outFile <<  "Write D-to-S: " << GetTotalTime(cmdTime[DSWrite], cmdCount[DSWrite]) << endl;

	//close files and exit
	opener.close();
	outFile.close();
	return 0;
}

double ReadTime(string s){
	//extract time value from the current line.
	double RetVal;
	int i = 26;
	char strTime = s[26];
	while (s[i] != ' '){i--;}
	RetVal = stod(s.substr(i,25-i));
	if (strTime == 'm'){RetVal *= 1000000;}
	if (strTime == 'u'){RetVal *= 1000;}
	return RetVal;
}

string GetTotalTime(double cmdTime, int cmdCount){
	//calculate the time statistics for a given command.
	string RetVal;
	int Magnitude;
	string MagValues[5] = {"","Kilo", "Mega", "Giga", "Tera"};
	double tmpTime = cmdCount * 32000000000;  // 32 bits / word and convert ns -> s
	if (cmdTime != 0) {tmpTime /= cmdTime;}
	
	//Shorten time to human-readable format
	while (tmpTime > 1000) {
		tmpTime /= 1000;
		Magnitude++;
	}
	
	string TimeValue = to_string(tmpTime);
	int i = 0;
	while (TimeValue[i] != '.'){i++;}
	
	//extract two decimal places and return as string.
	RetVal = TimeValue.substr(0,i+3);
	RetVal += " " + MagValues[Magnitude] + "bits/sec";
	return RetVal;
}

hexString dataline(string s)
{
	//Get data based on current input line
	string x="";
	for (int i = 99; i < 107; i++) 
	{
		x += s[i];
	} 
	return x;
}

hexString addressline(string s)
{	
	//Get address based on current input line
	string x="";
	for (int i = 82; i < 90; i++)
	{
		x+=s[i];
	}
	return x;
}

// Return Read or Write depending on current operation.
string rwline(string s){return s.substr(118,2);}
