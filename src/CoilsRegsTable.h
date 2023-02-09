/*
 * CoilsRegsTable.h
 *
 *  Created on: 29 Dec 2022
 *      Author: smaha
 */

#ifndef COILSREGSTABLE_H_
#define COILSREGSTABLE_H_
#include "RegsTable.h"
#include "Message.h"
#include "ModbusError.h"
typedef void (*OnRegisterChange)(uint16_t address, uint16_t value);


class CoilsRegsTable: public RegsTable<bool>{
public:
	CoilsRegsTable();
	//:RegsTable<int>()

	virtual ~CoilsRegsTable();
	void WriteSingleCoil(Message* msg, int sideEffect);
	void writeMultipleCoils(Message* msg, int sideEffect);
	void ReadCoils (Message* msg);
	bool setCoils(uint16_t address, OnRegisterChange handler);
	OnRegisterChange applyHandler(uint16_t address);
};

#endif /* COILSREGSTABLE_H_ */
