#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#pragma warning( disable : 4996 4800 )

using namespace std;

//Functions needed to calculate CRC
void ReadInput(vector <int> &data, fstream &InputFile);
void ConvertInput(vector <int> &data, vector <char> Rawdata);
void DisplayHexValue(vector <int> data);
void DisplayBinaryValue(vector <bool> BinaryData);
void ConvertToBinaryArray(vector <int> data, vector<bool> &BinaryData);
void PrintStartNumberValue(vector <int> data, vector<bool> BinaryData);
void SetUpCRC_Constant(vector <bool> &CRC_Constant);
void PadBinaryData(vector<bool> &BinaryData);
void OpenFile(fstream &InputFile);
void PrintPropplySpacedBinary(string data);

string CalculateCRC(vector<bool> &BinaryData, vector <bool> CRC_Constant, int FastMode);
string CalculateCRC(vector<bool> &BinaryData, vector <bool> CRC_Constant);
string ConvertCRC(string CRC);

char BinaryToHex(vector<bool> data);

//Additional Functions to Check CRC
bool VerifyCRC(vector<bool> BinaryData);

//Additional Functions to check for Virus Signitures
void GetInput_forVirusCheck(vector <int> &input);
void GetSig(vector <int> &sig);
void GetSigInput(vector <int> &sig);

//Functions to drive menus
void MenuDriver();
void CalculateCRC_Process();
void VerifyCRC_Process();
void VirusCheck();
void StripCRC();


int main()
{	
	MenuDriver();
 	system("PAUSE");
	return 0;
}

//Reads data from the input file, and places each characters into an vector of chars, then calls a function to convert these chars into intigers
void ReadInput(vector <int> &data, fstream &InputFile)
{
	vector <char> RawData;
	while (InputFile.good() == true)
	{
		RawData.push_back(InputFile.get());
	}
	RawData.pop_back(); //Gets rid of error character at end
	ConvertInput(data,RawData);
}

//Display the hex value of the input file
void DisplayHexValue(vector <int> data) 
{
	for (int i = 0; i < (signed) data.size(); i++)
	{
		cout << hex << data[i]; 
	}
}

//Formats and displays the Binary Value of input file
void DisplayBinaryValue(vector <bool> BinaryData)
{
	for (int i = 0; i < (signed) BinaryData.size(); i++)
	{
		cout << BinaryData[i];
		if (i%4==3)
		{
			cout << " ";
		}
		if (i % 32 == 31)
		{
			cout << endl;
		}
	}	
}

// Converts the input file into a vector of bool values
void ConvertToBinaryArray(vector <int> data, vector<bool> &BinaryData)
{
	stringstream Binary;
	stringstream FinalOutput;
	char buffer [33];
	char temp;
	for (int i = 0; i < (signed) data.size(); i++)
	{
		itoa(data[i],buffer,2);
		if (data[i] >= 8)
		{
			for (int j = 0; j < 4; j++)
			{
				temp = buffer[j];
				BinaryData.push_back((bool)(((int)temp) - 48));
			}
		}
		else if ( data[i] >= 4)
		{
			BinaryData.push_back(0);
			for (int j = 0; j < 3; j++)
			{
				temp = buffer[j];
				BinaryData.push_back((bool)(((int)temp) - 48));
			}
		}
		else if ( data[i] >= 2)
		{
			BinaryData.push_back(0);
			BinaryData.push_back(0);
			for (int j = 0; j < 2; j++)
			{
				temp = buffer[j];
				BinaryData.push_back((bool)(((int)temp) - 48));
			}
		}
		else if ( data[i] == 1)
		{
			BinaryData.push_back(0);
			BinaryData.push_back(0);
			BinaryData.push_back(0);
			BinaryData.push_back(1);
		}
		else if ( data[i] == 0)
		{
			BinaryData.push_back(0);
			BinaryData.push_back(0);
			BinaryData.push_back(0);
			BinaryData.push_back(0);
		}

	}
}

//Prints the Starting values of the numbers
void PrintStartNumberValue(vector <int> data, vector<bool> BinaryData)
{
		cout << "The input file (hex): ";
		DisplayHexValue(data);
		cout << endl;
		cout << "The input file (bin): ";
		DisplayBinaryValue(BinaryData);
		cout << endl;
}

//Coverts a vector of chars containing Hex characters to a vector of ints, for easy manipulation. Will close program if illegal character is inputed.
void ConvertInput(vector <int> &data, vector <char> Rawdata)
{
	for (int i = 0; i < (signed) Rawdata.size(); i++)
	{
		if (Rawdata[i] == '0')
			data.push_back(0);
		else if (Rawdata[i] == '1')
			data.push_back(1);
		else if (Rawdata[i] == '2')
			data.push_back(2);
		else if (Rawdata[i] == '3')
			data.push_back(3);
		else if (Rawdata[i] == '4')
			data.push_back(4);
		else if (Rawdata[i] == '5')
			data.push_back(5);
		else if (Rawdata[i] == '6')
			data.push_back(6);
		else if (Rawdata[i] == '7')
			data.push_back(7);
		else if (Rawdata[i] == '8')
			data.push_back(8);
		else if (Rawdata[i] == '9')
			data.push_back(9);
		else if (Rawdata[i] == 'A' || Rawdata[i] == 'a')
			data.push_back(10);
		else if (Rawdata[i] == 'B' || Rawdata[i] == 'b')
			data.push_back(11);
		else if (Rawdata[i] == 'C' || Rawdata[i] == 'c')
			data.push_back(12);
		else if (Rawdata[i] == 'D' || Rawdata[i] == 'd')
			data.push_back(13);
		else if (Rawdata[i] == 'E' || Rawdata[i] == 'e')
			data.push_back(14);
		else if (Rawdata[i] == 'F' || Rawdata[i] == 'f')
			data.push_back(15);
		//If white space, do nothing
		else if (Rawdata[i] == 32 || Rawdata[i] == 9 || Rawdata[i] == 10 || Rawdata[i] == 13) 
		{}
		else
		{
			cout << "Invalid character found in input, \"" << Rawdata[i] <<"\"" << endl;
			cout << "Now terminating program." << endl;
			system("PAUSE");
			exit(2);			
		}
	}
}

void SetUpCRC_Constant(vector <bool> &CRC_Constant)
{
	//CRC Constant is 10000010110001001
	CRC_Constant.push_back(1);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(1);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(1);
	CRC_Constant.push_back(1);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(1);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(0);
	CRC_Constant.push_back(1);
}

	//Adds 16 0's to the binary data file, which is used to calculate the CRC
void PadBinaryData(vector<bool> &BinaryData)
{
	for (int i = 0; i < 16; i++)
	{
		BinaryData.push_back(0);
	}
}


string CalculateCRC(vector<bool> &BinaryData, vector <bool> CRC_Constant)
{
	char input[2]; 
	int fastmode = 0;
	if (BinaryData.size() > 64)
	{

		cout << endl << "The input file has more then 16 HEX characters in it. Displaying a large number" << endl;
		cout << "of lines in the console can greatly slow down the program." << endl << endl;
		cout << "Would you like to turn off console text for the calculation of the CRC?" << endl << endl;
		cout << "1. Yes" << endl << "2. No" << endl;
		cin.get(input,2);
		cin.clear();
		fflush(stdin);
		if (input[0] == '1')
		{
			fastmode = 1;
		}
	}
	return CalculateCRC(BinaryData, CRC_Constant, fastmode);
}
//Calculates the value of the CRC, while modifying the Binary Data Object. Returns the last 16 bits as a string. 
string CalculateCRC(vector<bool> &BinaryData, vector <bool> CRC_Constant, int FastMode)
{
	stringstream CRC;
	for (int i = 0; i < (signed) (BinaryData.size() - 16); i++)
	{
		if (BinaryData[i] == 1)
		{
			for (int j = 0; j < 16; j++)
			{
				BinaryData[i+j] = BinaryData[i+j] ^ CRC_Constant[j]; //XOR the two bools together
			}
		}
		if (FastMode != 1)
		{
			DisplayBinaryValue(BinaryData);
			cout << endl;
		}
	}
	for (int j = 0; j < 16; j++)
	{
		CRC <<  (BinaryData[(BinaryData.size() - 16)+j]);
	}
	return CRC.str();
}

//Checks that all values in the vector of bools are zero. If so, the CRC was accurate.
bool VerifyCRC(vector<bool> BinaryData)
{
	bool failbit = false;
	for (int i = 0; i < (signed) BinaryData.size(); i++)
	{
		if (BinaryData[i] == true)
			failbit = true;
	}
	cout << "Did CRC Check Pass? [Yes or No]: " ;
	if (failbit)
		cout << "No" << endl;
	else cout << "Yes" << endl;
	return !failbit;
}

//Converts the 16 binary digits to 4 hex characters, to append to the input file
string ConvertCRC(string CRC)
{
	string HexCRC;
	vector <bool> hex1, hex2, hex3, hex4;
	int i = 0;
	for (i;i<4;i++)
		hex1.push_back((bool)(CRC[i]-48));
	for (i;i<8;i++)
		hex2.push_back((bool)(CRC[i]-48));
	for (i;i<12;i++)
		hex3.push_back((bool)(CRC[i]-48));
	for (i;i<16;i++)
		hex4.push_back((bool)(CRC[i]-48));
	
	HexCRC.push_back(BinaryToHex(hex1));
	HexCRC.push_back(BinaryToHex(hex2));
	HexCRC.push_back(BinaryToHex(hex3));
	HexCRC.push_back(BinaryToHex(hex4));


	return HexCRC;
}

//Converts a vector of 4 binary digits to a hex character
char BinaryToHex(vector<bool> data)
{
	int number = 0;
	if (data[0] == true) number+=8;
	if (data[1] == true) number+=4;
	if (data[2] == true) number+=2;
	if (data[3] == true) number+=1;

	if (number == 0) return '0';
	else if (number == 1) return '1';
	else if (number == 2) return '2';
	else if (number == 3) return '3';
	else if (number == 4) return '4';
	else if (number == 5) return '5';
	else if (number == 6) return '6';
	else if (number == 7) return '7';
	else if (number == 8) return '8';
	else if (number == 9) return '9';
	else if (number == 10) return 'A';
	else if (number == 11) return 'B';
	else if (number == 12) return 'C';
	else if (number == 13) return 'D';
	else if (number == 14) return 'E';
	else return 'F';
}

//Drives the process of Calculating the CRC
void CalculateCRC_Process()
{
	fstream InputFile;
	vector <int> data;
	vector <bool> BinaryData;
	vector <bool> CRC_Constant; //The value that is used to XOR with the binary input data
	string CRC;
	


	OpenFile(InputFile);
	ReadInput(data, InputFile);
	ConvertToBinaryArray(data, BinaryData);
	PrintStartNumberValue(data, BinaryData);
	SetUpCRC_Constant(CRC_Constant);
	PadBinaryData(BinaryData);
	CRC = CalculateCRC(BinaryData,CRC_Constant);
	
	cout << endl << "Thus, the CRC is ";
	PrintPropplySpacedBinary(CRC);
	cout << "(bin), which is ";

	CRC = ConvertCRC(CRC);

	cout << CRC << "(hex)." << endl;

	InputFile.clear();
	InputFile << CRC;

	cout << "CRC has been appended to the end of the input file." << endl;

	//Done to redisplay the new value of the file.
	cout << "Reading input file again: ";
	DisplayHexValue(data);
	cout << CRC << endl;
	InputFile.close();
	cout << endl;
}

//Opens a file and checks if it opened correctly. If the file did not open correctly, exit the program.
void OpenFile(fstream &InputFile)
{
	char FileName[256];
	do
	{	
		cout << "Please input file name: " << endl;
		cin.get (FileName,256);
		cin.clear();
		fflush(stdin);

		InputFile.open(FileName);
		cout << endl;

		if (InputFile.fail())
		{
			cout << "File Failed to open. Please input anther file name." << endl;
		}
	} while (InputFile.fail());
}

//Drives the process of Verifying the CRC
void VerifyCRC_Process()
{
	fstream InputFile;
	vector <int> data;
	vector <bool> BinaryData;
	vector <bool> CRC_Constant; //The value that is used to XOR with the binary input data
	string CRC;
	OpenFile(InputFile);
	ReadInput(data, InputFile);
	ConvertToBinaryArray(data, BinaryData);
	PrintStartNumberValue(data, BinaryData);
	SetUpCRC_Constant(CRC_Constant);
	CalculateCRC(BinaryData,CRC_Constant);
	VerifyCRC(BinaryData);
	InputFile.close();
}

//Drives the Menus
void MenuDriver()
{
	char input[2];
	cout << "This program is designed to check the CRC of Plaintext files," << endl << "and do simple Virus Signiture Checks." << endl ;
	bool stop = false;
	while (!stop)
	{
		cout << endl;
		cout << "Please select a Menu Option." << endl;
		cout << "1. Calculate CRC." << endl;
		cout << "2. Verify CRC." << endl;
		cout << "3. Verify and Strip CRC." << endl;
		cout << "4. Scan for virus." << endl;
		cout << "5. Exit" << endl;
		cin.get(input,2);
		cin.clear();
		fflush(stdin);
		if (input[0] == '1')
		{	
			CalculateCRC_Process();
		}
		else if (input[0] == '2')
		{
			VerifyCRC_Process();
		}
		else if (input[0] == '3')
		{
			StripCRC();
		}
		else if (input[0] == '4')
		{
			VirusCheck();
		}
		else if (input[0] == '5')
		{
			return;
		}
		else
		{
			cout << "Invalid input selected." << endl << endl;
		}
	}
}

//Drives the proocess of checking the Virus Signiture
void VirusCheck()
{
	vector <int> input;
	vector <int> sig;
	
	GetInput_forVirusCheck(input);
	GetSig(sig);
	int WildCardCount = 0;
	int CharacterSpot = 0;
	int SigFound = 0;

	if (sig.size() <= 1)
	{
		cout << "Virus Signiture is to short. Must be at least 2 HEX Characters longs." << endl;
		return;
	}

	if (sig.size() >= input.size())
	{
		cout << "Virus Signiture is to long. Must be shorter then input." << endl;
		return;	
	}

	for (int i = 0; i < (signed) (input.size() - sig.size()); i++)
	{
		int j;
		WildCardCount = 0;
		for ( j = 0; j < (signed) sig.size(); j++)
		{
			if (input[i+j] != sig[j])
			{
				WildCardCount++;
				CharacterSpot = i+j;
			}
			
			if (WildCardCount >= 2)
			{
				break;
			}
		}
		if (WildCardCount == 0)
		{
			cout << "Virus Signature found at location " << i+1 << ". It is an exact match." << endl;
			SigFound++;
		}
		
		if (WildCardCount == 1)
		{
			cout << "Virus Signature found at location " << i+1 << ". It has a WildCard at Character Number " << i+j << endl;
			SigFound++;
		}
	}
	if (SigFound == 0)
	{
		cout << "No Virus Detected." << endl;
	}
}

//Open the input file to be checked, and converts it to a vector of ints
void GetInput_forVirusCheck(vector <int> &input)
{
	fstream InputFile;
	cout << "Ready for file to be checked. ";
	OpenFile(InputFile);
	ReadInput(input, InputFile);
	InputFile.close(); 
}

//Gets the virus signiture, and converts them into a vector of ints
void GetSig(vector <int> &sig)
{
	char input[2];
	cin.clear();
	fflush(stdin);
	cout << "Would you like to input the signiture by hand, or load from a file?" << endl;
	cout << "1. Input by hand." << endl << "2. Open a file" << endl;
	cin.get(input,2);
	cin.clear();
	fflush(stdin);
	if (input[0] != '2')
	{	
		GetSigInput(sig);
	}
	else
	{
		fstream InputFile;
		OpenFile(InputFile);
		ReadInput(sig, InputFile);
		InputFile.close(); 
		cout << endl << "Virus Signiture: ";
		for (int i = 0; i < (signed) sig.size(); i++)
		{
			cout << hex << sig[i];
		}
		cout << dec << endl;
	}
}

//Takes user input in hex characters, and converts them into a vector of ints
void GetSigInput(vector <int> &sig)
{
	vector <char> RawData;
	char input[256];
	cout << "Please input the Virus Signiture now: " << endl;
	cin.get(input,256);
	cin.clear();
	fflush(stdin);
	for (int i = 0; input[i] != 0; i++)
	{
		RawData.push_back(input[i]);
	}
	ConvertInput(sig,RawData);
}

//Places a space every 4 binary characters in a string
void PrintPropplySpacedBinary(string data)
{
	for (int i = 0; i < (signed)data.size(); i++)
	{
		cout << data[i];
		if (i % 4 == 3)
		{
			cout << ' ';
		}
	}
}

void StripCRC()
{
	fstream InputFile;
	vector <int> data;
	vector <bool> BinaryData;
	vector <bool> CRC_Constant; //The value that is used to XOR with the binary input data
	string CRC;
	char FileName[256];
	do
	{	
		cout << "Please input file name: " << endl;
		cin.get (FileName,256);
		cin.clear();
		fflush(stdin);

		InputFile.open(FileName);
		cout << endl;

		if (InputFile.fail())
		{
			cout << "File Failed to open. Please input anther file name." << endl;
		}
	} while (InputFile.fail());

	ReadInput(data, InputFile);
	ConvertToBinaryArray(data, BinaryData);
	PrintStartNumberValue(data, BinaryData);
	SetUpCRC_Constant(CRC_Constant);
	CalculateCRC(BinaryData,CRC_Constant);
	bool VerifyOK = VerifyCRC(BinaryData);
	InputFile.close();


	if (VerifyOK == true)
	{
		cout << endl << "CRC has been Verifyed, now removing." << endl;
		ofstream output;
		output.open(FileName);
		cout << "New contents of file: ";
		for (int i = 0; i < (signed) data.size() - 4; i++)
		{
			output << hex << data[i];
			cout << hex << data[i];
		}
		cout << endl;
	}
	else
	{
		cout << endl << "CRC Verify failed, can not strip." << endl;
	}
}