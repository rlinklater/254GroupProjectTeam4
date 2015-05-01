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

int main()
{//grabs "log.txt" from the current directory
	string filename="test_data.log";
	//cout << "Enter file name:";    //these were to enter file name, commented out for testing convienience
	//getline(cin, filename);
	//cout << endl<<filename<<endl;
	ifstream opener;
	opener.open(filename.c_str());

	if (!opener.is_open())
	{
		cout << "Could not open the file!\n";
		return 1;
	}

	string line;
	int counter = 0;

	Command cmd;

	hexString data;  //takes data from data column
	hexString stod;  // initializer for s-to-d
	hexString stodlow; //word 0 and 1 of instructions  s-to-d
	hexString stodhigh;
	hexString dtos;   //initializer for d-to-s
	hexString dtoslow; //word 0 to 1 of instructions for d-to-s
	hexString dtoshigh;
	hexString address;
	stod="40000810";  // initializer for s-to-d
	stodlow= "40000818"; //word 0 and 1 of instructions  s-to-d
	dtos="40000C18";   //initializer for d-to-s
	dtoslow= "40000C20"; //word 0 to 1 of instructions for d-to-s


	while (getline(opener, line))  // had to add the counter bool because .eof wasn't working
	{//81-88
		address=addressline(line);
		counter++;
		data=dataline(line);
		if(address>=stodlow && address<=stodhigh) //s-to-d instructions
		{
			cmd.AddData(counter,data.toString(),address);
		}
		else if(address>=dtoslow && address<=dtoshigh) //d-to-s instructions
		{
			cmd.AddData(counter,data.toString(),address);
		}
		if (address == stod)
		{
			cmd.AddFirstLine(counter, SDRead, data);
			data += stodlow; // adding data to initial address to determine last address
			stodhigh=data;
			data="";

		}
		else if (address == dtos)
		{
			cmd.AddFirstLine(counter, DSRead, data);
			data += dtoslow;      //same as above
			dtoshigh=data;
			data="";

		}
	}

	cout << "THE END" << endl; // just to show program completion
	return 0;
}



hexString dataline(string s)
{
  string x="";
 for (int i = 99; i < 107; i++)  //grabs address based on string index
  {
    x += s[i];
  } 
  return x;
}
hexString addressline(string s)
{
	string x="";
	for (int i = 82; i < 90; i++)
		{
			x+=s[i];
		}
	return x;
}
string rwline(string s){return s.substr(119,2);}
