/*
 * SlaveManager.h
 *
 *  Created on: 14 Dec 2022
 *      Author: smaha
 */

#ifndef SLAVEMANAGER_H_
#define SLAVEMANAGER_H_
#include <string> // for string class
#include <iostream>
#include "Message.h"
#include "ModbusTypeDefs.h"
//#include "Logic.h"
#include "HoldingRegsTable.h"
#include "CoilsRegsTable.h"

using namespace std;
using namespace Modbus;  // NOLINT

typedef void (*OnRegisterChange)(uint16_t address, uint16_t value);


/*Slave (server)*/
class SlaveManager {
public:
	//Logic* logic; NEED to be removed update accordingly
	HoldingRegsTable* holding;
	CoilsRegsTable* coils;
	SlaveManager();
	virtual ~SlaveManager();


	/*takes message as a string and it's length*/
	Message* handleMSG(Message* m, int len, int sideEffect);

	bool setRegisterChangeHandler(OnRegisterChange handler, uint8_t table, uint16_t address);



};

#endif /* SLAVEMANAGER_H_ */
