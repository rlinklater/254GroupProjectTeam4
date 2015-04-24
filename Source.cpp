#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stack>
#include <sstream>
#include <bitset>
using namespace std;
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))



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
	unsigned int x;
	while (!opener.eof()&& counter!=30004)  // had to add the counter bool because .eof wasn't working
	{//81-88
		getline(opener, line);
		string address = "";
		string data = "";
		string bin = "";
		for (int i = 82; i < 90; i++)
		{
			address+=line[i];
		}
		//cout << address << endl;
		//1073743896   //int number for first address
		//1073744920  // int number for first address of second case
		counter++;
		if (address == "40000810" || address == "40000C18") // finds initial line
		{
			cout << counter << ":    ";
			for (int i = 99; i < 107; i++)  //grabs address based on string index
			{
				data += line[i];
			}
			std::stringstream ss;
			ss << hex << data;   //converting hex to int
			ss >> x;
			x = static_cast<int>(x);
			if (address == "40000810")
			{
				x += 1073743896; // adding data to initial address to determine last address
			}
			else if (address == "40000C18")
			{
				x += 1073744920;      //same as above
			}
			cout <<data;
			ss << hex << x;   //converting int to hex (not working)
			string result(ss.str());
			cout <<"  "<< result << endl;
			//bitset< sizeof(x)*CHAR_BIT > bits(x);
			//bin= bits.to_string();     //converts int to binary
		}
		//cout << ARRAY_SIZE(line) << endl << line << endl; // used to get the size of the array (probably delete it later
	}

	cout << "THE END" << endl; // just to show program completion
	return 0;
}
