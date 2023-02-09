/*
 * Logic.h
 *
 *  Created on: 14 Dec 2022
 *      Author: marwa
 */


#ifndef LOGIC_H_
#define LOGIC_H_
#include <iostream>
#include "Message.h"
#include "Light.h"
#include "SlaveManager.h"
using namespace std;




class Logic {
public:
	//slave here
	SlaveManager* sm;

	Logic();
	Logic(SlaveManager* sm);
	virtual ~Logic();
	void init();
	void logicMsg(Message* m, int len);
	Light* createLight ();//rethink it
	static void Mode(uint16_t address, uint16_t value);
	static void On(uint16_t address, uint16_t value);
	static void SetTemperature(uint16_t address, uint16_t value);
	static void Temperature(uint16_t address, uint16_t value);
	static void FanSpeed(uint16_t address, uint16_t value);

};

#endif /* LOGIC_H_ */
