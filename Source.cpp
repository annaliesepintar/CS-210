/*This program reads the text records of the grocery store, calculates how many of each item was sold, and displays a histogram of the data.
* 
* Author of functions menu, menuChoice, histogram, read, write, listItems, and frequencyOfItems: Annaliese Pintar
* Date: 04-17-2022
* 
*/
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//function prototypes
void menu();
int menuChoice();
void histogram();
void CallProcedure(string pName);
int callIntFunc(string proc, string param);
int callIntFunc(string proc, int param);

void main()
{
	int choice = 0;	//user menu choice

	//loop continues until user chooses menu option 4
	while (choice != 4) {
		choice = menuChoice();
	}

}

/*This function displays a menu of options for user to choose from. They can list the items, get the number of times an item was sold, and display a histogram
* 
* Parameters: N/A
* 
* Returns: N/A
*/
void menu() {
	cout << "Menu" << endl;
	cout << "1: List items purchased and the number of times each item was purchased" << endl;
	cout << "2: Get how many times a specific item was purchased" << endl;
	cout << "3: Display a histogram of items purchased" << endl;
	cout << "4: Exit program" << endl;
	cout << "Select an option from the menu: ";
}

/*This function gets user input for menu choice and calls the correct function based off their choice or exits the program.
* 
* Parameters: N/A
* 
* Returns: userChoice - an int the is user input for their menu choice
*/
int menuChoice() {
	int userChoice;		//user input menu choice
	bool error;			//if input is invalid, error will be set to true
	ifstream inputFile;	//file with item names and frequency
	string itemLookUp;	//name of item user wants to look up


	//loop will continue if user iput it invalid
	do {
		error = false;

		menu();	//call menu display function

		cin >> userChoice;	//get user input for menu choice

		//switch case for user's choice from menu
		switch (userChoice) {
		
		//if user selects option 1, items and their frequency are listed
		case 1:
			system("CLS");
			CallProcedure("listItems");
			cout << endl;
			break;

		//if user selects option 2, frequency of item chosen by user will be displaces
		case 2:
			system("CLS");
			cout << "Enter name of item you'd like to look up: ";
			
			//loop will continue while input is invalid
			 do{
				error = false;
				cin >> itemLookUp;
				if (callIntFunc("frequencyOfItem", itemLookUp) == -1) {
					system("CLS");
					cout << "ERROR: That item is not on the list of purchased items. Enter a different item: " << endl;
					error = true;
				}

			}while (error == true);
			system("CLS");
			cout << itemLookUp << " purchased " << callIntFunc("frequencyOfItem", itemLookUp) << " time(s)." << endl;
			cout << endl;
			break;

		//if user selects option 3, histogram will be displayed
		case 3:
			system("CLS");
			histogram();
			cout << endl;
			break;

		//if user selects option 4, program will end
		case 4:
			break;

		//if 1, 2, 3, or 4 are not selected, user input is invalid, error will be true, and loop will continue
		default:
			system("CLS");

			cout << "ERROR: That is not an option. Select option 1, 2, 3, or 4 from menu" << endl;

			//input was invalid so error is true
			error = true;

			//if input was not an int, clear error and buffer
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			break;
		}
	} while (error == true);

	return userChoice;
}

/*This function displays a histogram of the data
* 
* Parameters: N/A
* 
* Returns: N/A
*/
void histogram() {
	ifstream file;	//file with items listed and their frequency

	//call function to write data from provided input file to frequency.dat
	CallProcedure("write");

	//open file
	file.open("frequency.dat");

	//if file opens get item and number of item from file until file reaches the end
	if (file.is_open()) {

		//loop will continues until end of file
		while (true) {
			string item;	//purchased item
			int num;		//num times item was purchased

			file >> item;	//get item from file
			file >> num;	//get num of item from file

			//if end of file is reached, exit while loop
			if (file.eof()) {
				break;
			}

			//display the amount of each item represented by equal signs
			cout << left << setw(14) << item << " ";
			for (int i = 0; i < num; ++i) {
				cout << "=";
			}

			cout << endl;
		}

		//close file
		file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}


}

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}