#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "hexString.h"
#include "Command.h"
using namespace std;


string dataline(string s);

int main()
{//grabs "log.txt" from the current directory
	string filename="log.txt";
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
	hexString data;  //takes data from data column
	hexString stod;  // initializer for s-to-d
	hexString stodlow; //word 0 and 1 of instructions  s-to-d
	hexString stodhigh;
	hexString dtos;   //initializer for d-to-s
	hexString dtoslow; //word 0 to 1 of instructions for d-to-s
	hexString dtoshigh;

	stod="40000810";  // initializer for s-to-d
	stodlow= "40000818"; //word 0 and 1 of instructions  s-to-d
	dtos="40000C10";   //initializer for d-to-s
	dtoslow= "40000C18"; //word 0 to 1 of instructions for d-to-s


	int sord=0;

	while (!opener.eof()&& counter!=30004)  // had to add the counter bool because .eof wasn't working
	{//81-88
		getline(opener, line);
		hexString address = "";
		string bin = "";
		for (int i = 82; i < 90; i++)
		{
			address+=line[i];
		}
		counter++;
		
		if(address<=stodlow && address>=stodhigh && sord==1)
		{
		   
		}
		else if(address<=dtoslow && address>=dtoshigh && sord==2)
		{
		  
		}
		else if (address == stod || address == dtos) // finds initial line
		{
			cout << counter << ":    ";
			for (int i = 99; i < 107; i++)  //grabs address based on string index
			{
				data += line[i];
			}
			
			if (address == stodlow)
			{
				data += stodlow; // adding data to initial address to determine last address
				stodhigh=data;
				data="";
				sord=1;
			}
			else if (address == dtoslow)
			{
				data += dtoslow;      //same as above
				dtoshigh=data;
				data="";
				sord=2;
			}

		}
		else
			sord=0;
		//cout << ARRAY_SIZE(line) << endl << line << endl; // used to get the size of the array (probably delete it later
	}

	cout << "THE END" << endl; // just to show program completion
	return 0;
}



string dataline(string s)
{
  string x="";
 for (int i = 99; i < 107; i++)  //grabs address based on string index
  {
    x += s[i];
  } 
  return x;
}
