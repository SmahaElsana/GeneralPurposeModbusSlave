//============================================================================
// Name        : gpms.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include "TransportManager.h"
#include "SlaveManager.h"
#include "Logic.h"
#include <fstream>

#include "json.hpp"
//#include "./json-develop/include/nlohmann/json.hpp"
//#include "rapidjson/document.h"
//using namespace rapidjson;


// for convenience
using json = nlohmann::json;

using namespace std;
using std::ifstream;




int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	SlaveManager* sm = new SlaveManager();
	TransportManager* transportm =  new TransportManager();
	transportm->init(sm);
	Logic* logic = new Logic(sm);
	logic->init();

	transportm->start();


// ...
//Document document;
//document.Parse(json);

	/* fstream strm;
	    strm.open("/home/smaha/itWork/gpms/src/settings.conf", ios_base::in);
	    if (!strm.is_open()) {
	        cout << "Open file failed" << endl;
	        return 1;
	    }

	    char arr[150];
	    strm.get(arr, 150, EOF);
	    strm.close();

	    cout << arr << endl;
	    return 0;
*/

	/*std::ifstream f("data.json");
	json data = json::parse(f);
	// Access the values existing in JSON data
	string name = data.value("name", "not found");
	string grade = data.value("grade", "not found");
	// Access a value that does not exist in the JSON data
	string email = data.value("email", "not found");
	// Print the values
	cout << "Name: "<< name << endl;
	cout << "Grade: " << grade << endl;
	cout << "Email: " << email << endl;*/

	return 0;


/*
	// jdEmployees
	  json jdEmployees =  {
	    {"firstName","Sean"},
	    {"lastName","Brown"},
	    {"StudentID",21453},
	    {"Department","Computer Sc."}};

	   // Access the values
	   std::string fName = jdEmployees.value("firstName", "oops");
	   std::string lName = jdEmployees.value("lastName", "oops");
	   int sID = jdEmployees.value("StudentID", 0);
	   std::string dept = jdEmployees.value("Department", "oops");

	   // Print the values
	   std::cout << "First Name: " << fName << std::endl;
	   std::cout << "Last Name: " << lName << std::endl;
	   std::cout << "Student ID: " << sID << std::endl;
	   std::cout << "Department: " << dept << std::endl;

	   return 0;
	   */
}
