/*
 * TransportManager.cpp
 *
 *  Created on: 14 Dec 2022
 *      Author: smaha
 */
#include "SlaveManager.h"
#include "TransportManager.h"
//#include "tcp.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
//#include <jsoncpp/json/json.h>
//#include <fstream>
//#include <settings.conf>

TransportManager::TransportManager() {
	// TODO Auto-generated constructor stub
	//this->tcp = new tcp(8080);

}

TransportManager::~TransportManager() {
	// TODO Auto-generated destructor stub
}

void TransportManager::init(SlaveManager* sm){
	this->sm = sm;
	this->curtcp = new tcp(8080, sm);

}

//std::ifstream settings_file("settings.conf", std::ifstream::binary);
//Json::Value settings;
//settings_file >> settings ;
//
//int port = settings["port"];


//tcp* tcp1 = new tcp(8080);
//std:: ifstream cFile ("settings.conf");

void TransportManager::start(){

	this->curtcp->start();
}

