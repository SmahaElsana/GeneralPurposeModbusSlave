/*
 * HoldingRegsTable.h
 *
 *  Created on: 30 Dec 2022
 *      Author: smaha
 */

#ifndef HOLDINGREGSTABLE_H_
#define HOLDINGREGSTABLE_H_
#include "RegsTable.h"
#include "ModbusError.h"
#include <stdint.h>
#include <map>
#include <functional>
typedef void (*OnRegisterChange)(uint16_t address, uint16_t value);



class HoldingRegsTable : public RegsTable<uint16_t>{
public:
	HoldingRegsTable();
	virtual ~HoldingRegsTable();
	//((uint16_t)d2 << 8) | d1;
	void WriteSingleRegister(Message* msg,int sideEffect);
	void WriteMultipleRegisters(Message* msg, int sideEffect);
	void readHoldingRegisters(Message* msg);
	bool setHolding(uint16_t address, OnRegisterChange handler);

	//	bool setRegisterChangeHandler(OnRegisterChange handler, uint8_t table, uint16_t address);


};

#endif /* HOLDINGREGSTABLE_H_ */
