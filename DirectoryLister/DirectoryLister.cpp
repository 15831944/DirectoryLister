// DirectoryLister.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <iostream>
#include <string>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	// Save the current working directory
	char *currentdir;
	currentdir = _getcwd(NULL,128);


	// Change to the specified working directory
	string path;
	cout << "Enter the path to report: ";
	cin >> path;
	_chdir(path.c_str());

	string desc;
	cout << "Enter the file description: ";
	cin >> desc;


	// Print the name of the working directory
	path = _getcwd(NULL,128);
	cout << path << endl;
	for (unsigned int x = 0; x < path.length(); x++)
		cout << "-";
	cout << endl;

	// List the files in the directory
	int cnt = 0;
	intptr_t file;
	_finddata_t filedata;
	file = _findfirst(desc.c_str(),&filedata);
	if (file != -1)
	{
		cout << "DIR\tRDO\tSYS\tARCH\tHIDE\tFILENAME" << endl;
		do
		{
			//cout << filedata.name << endl;
			if (filedata.attrib & _A_SUBDIR) cout << "Y"; cout << "\t";
			if (filedata.attrib & _A_RDONLY) cout << "Y"; cout << "\t";
			if (filedata.attrib & _A_SYSTEM) cout << "Y"; cout << "\t";
			if (filedata.attrib & _A_ARCH) cout << "Y"; cout << "\t";
			if (filedata.attrib & _A_HIDDEN) cout << "Y"; cout << "\t";
			cout << filedata.name;
			cout << endl;
			if (cnt == 20)
			{
				cout << "--more--" << endl;
				while (!_kbhit()) ; // Wait for a key press
				_getch(); // Clear the key buffer

				cnt = 0;
			}
			cnt++;
		} while (_findnext(file,&filedata) == 0);
	}
	else
	{
		cout << "No described files found" << endl;
	}
	_findclose(file);

	// Return to the original working directory
	_chdir(currentdir);
	free(currentdir);

	//cout << "--done--" << endl;
	//while (!_kbhit()) ; // Wait for a key press
	//_getch(); // Clear the key buffer

	return 0;
}

