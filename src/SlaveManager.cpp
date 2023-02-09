/*
 * SlaveManager.cpp
 *
 *  Created on: 14 Dec 2022
 *      Author: smaha
 */

#include "SlaveManager.h"
#include "Logic.h"
#include "HoldingRegsTable.h"
#include "CoilsRegsTable.h"
#include <map>



SlaveManager::SlaveManager() {
	// TODO Auto-generated constructor stub
	//	logic = new Logic();
	holding = new HoldingRegsTable();
	coils = new CoilsRegsTable();

}

SlaveManager::~SlaveManager() {
	// TODO Auto-generated destructor stub
}
//hi
/*NEEDS TO BE UPDATED*/
Message* SlaveManager::handleMSG(Message* m, int len, int sideEffect){

	printf("handleMSG Message consructor data pointer0 %x \n", m->getData()[0]);
	printf("handleMSG Message consructor data pointer1 %x \n", m->getData()[1]);
	printf("handleMSG Message consructor data pointer2 %x \n", m->getData()[2]);
	printf("handleMSG Message consructor data pointer3 %x \n", m->getData()[3]);
	uint16_t address = ((uint16_t)*m->getData()<< 8) | *(m->getData()+1);
	uint16_t value = ((uint16_t)*(m->getData()+2) << 8) | *(m->getData()+3);
	//	Logic* logic = new Logic();
	//	HoldingRegsTable* holding = new HoldingRegsTable();
	//	CoilsRegsTable* coils = new CoilsRegsTable();
	printf( "MY MSG SLAVE :%x\n",m->getFunctionCode());
	//logic->logicMsg(m, len);

	//ADD THE SWITCH CASE HERE
	switch(m->getFunctionCode()){
	case READ_DISCR_INPUT:
		return m;
		break;

	case READ_HOLD_REGISTER:
		printf("READ HOLD \n");
		holding->readHoldingRegisters(m);
		return m;
		break;



	case WRITE_COIL :
		printf("write coil \n");
		coils->WriteSingleCoil(m);
		return m;
		break;

	case WRITE_HOLD_REGISTER:
		printf("WRITE_HOLD_REGISTER \n");
		holding->WriteSingleRegister(m, sideEffect);
//		if (holding->cbTable.find(address) == holding->cbTable.end()) {
//			printf("address of lisht update %x\n",&Light::update);
//		}
		return m;
		break;


	case WRITE_MULT_COILS:
		printf("WRITE_MULT_COILS \n");
		coils->writeMultipleCoils(m);
		return m;
		break;


	case WRITE_MULT_REGISTERS:
		printf("WRITE_MULT_REGISTERS \n");
		holding->WriteMultipleRegisters(m);
		printf("val at regtable[0] %x \n",holding->regTable.at(0));
		return m;
		break;


	case READ_COIL:
		printf("READ COIL \n");
		coils->ReadCoils(m);
		return m;
		break;


	default:
		printf("what the hell\n");
		uint8_t error [2] = { 0x80|m->getFunctionCode(),0x01 };
		return m;
		break;
	}
}


bool SlaveManager::setRegisterChangeHandler(OnRegisterChange handler, uint8_t table, uint16_t address){
	printf("got to setRegisterChangeHandler\n");

	switch(table){
	case READ_COIL:
		//setCoil
		return coils->setCoils(address, handler);
		break;


	case READ_HOLD_REGISTER:
		//setHolding
		return holding->setHolding(address, handler);
		break;


	default:
		printf("GOT TO default\n");
		return false;
		break;
	}
	return false;
}

