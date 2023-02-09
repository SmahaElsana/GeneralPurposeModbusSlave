/*
 * HoldingRegsTable.cpp
 *
 *  Created on: 30 Dec 2022
 *      Author: smaha
 */
#include <iostream>
#include "HoldingRegsTable.h"




HoldingRegsTable::HoldingRegsTable() {
	// TODO Auto-generated constructor stub
	//regTable.insert(std::make_pair(0,0));
	printf("holding register constructor /n");
}

HoldingRegsTable::~HoldingRegsTable() {
	// TODO Auto-generated destructor stub
}

void HoldingRegsTable::WriteSingleRegister(Message* msg,int sideEffect){
	//uint8_t ExceptionCode = 0;
	uint16_t address = ((uint16_t)*msg->getData()<< 8) | *(msg->getData()+1);
	uint16_t value = ((uint16_t)*(msg->getData()+2) << 8) | *(msg->getData()+3);

	if(value < 0 || value > 0xFFF0){
		//	ExceptionCode = ILLEGAL_DATA_VALUE;
		msg->setTxError(ILLEGAL_DATA_VALUE);
		return;

	}
	else if(address < lowerAddress || address > upperAddress){
		//	ExceptionCode = ILLEGAL_DATA_ADDRESS;
		msg->setTxError(ILLEGAL_DATA_ADDRESS);
		printf("HOLDING WRITE SINGLE ILLEGAL ADDRESS\n");
		return;
	}

	printf(" address %x\n", address);
	printf(" value %x\n", value);

	regTable.insert(std::make_pair(address,value));
	if(regTable.at(address) != value){
		//ExceptionCode = SERVER_DEVICE_FAILURE;
		msg->setTxError(SERVER_DEVICE_FAILURE);
		return;
	}

	if(sideEffect){
		(this->cbTable.at(address))(address,value);
	}
	printf("regTable val at %d is %x \n",address,regTable.at(address));
}

/*
 * byte - function code
 * 2 byte - starting address
 * 2 byte - quantity of registers
 * byte - count
 * 2*N bytes- registers value
 * */
void HoldingRegsTable::WriteMultipleRegisters(Message* msg, int sideEffect){
	uint16_t startingAddress = ((uint16_t)*msg->getData()<< 8) | *(msg->getData()+1);
	uint16_t quantity = ((uint16_t)*(msg->getData()+2) << 8) | *(msg->getData()+3);
	uint16_t* rgisters = (uint16_t*)(msg->getData()+5);
	uint8_t count = *(msg->getData()+4);
	if(quantity > 0X007B || quantity < 0x0001 || quantity*2 != count){
		msg->setTxError(ILLEGAL_DATA_VALUE);
		return;
	}
	if(startingAddress <lowerAddress || startingAddress > upperAddress || startingAddress+ quantity > upperAddress){
		msg->setTxError(ILLEGAL_DATA_ADDRESS);
		return;
	}

	for(int i=0; i < quantity; i++){
		//printf("starting %x \n",(startingAddress+i));
		//printf("register %x \n",(rgisters[i]));
		//printf("TRIAL %x \n",0XFFFF);

		regTable.insert(std::make_pair((startingAddress+i),(uint16_t)*(rgisters+i)));
		//regTable[startingAddress+i] = (uint16_t)*(rgisters+i);
		printf("VALUE IN REG %X \n",regTable.at((startingAddress+i)));



		if(regTable.at((startingAddress+i)) != (uint16_t)*(rgisters+i)){
			//ExceptionCode = SERVER_DEVICE_FAILURE;
			msg->setTxError(SERVER_DEVICE_FAILURE);
			return;
		}

		//check this line again
		if(sideEffect){
				(this->cbTable.at(startingAddress+i))(startingAddress+i,(uint16_t)*(rgisters+i));
			}
	}
	printf("MAP SIZE IS %X \n", regTable.size());

	msg->setLen(12);





}

void HoldingRegsTable::readHoldingRegisters(Message* msg){
	//printf("MAP SIZE IS %X \n", regTable.size());
	//printf("MAP[0] %X \n", regTable[0]);
	uint16_t startingAddress = ((uint16_t)*msg->getData()<< 8) | *(msg->getData()+1);
	uint16_t quantity = ((uint16_t)*(msg->getData()+2) << 8) | *(msg->getData()+3);

	if(quantity > 0X007D || quantity < 0x0001){
		msg->setTxError(ILLEGAL_DATA_VALUE);
		return;
	}
	if(startingAddress <lowerAddress || startingAddress > upperAddress || startingAddress+ quantity > upperAddress){
		msg->setTxError(ILLEGAL_DATA_ADDRESS);
		return;
	}

	//regTable.insert({0,0xFFFF});

	uint16_t* reply = new uint16_t [quantity<<1];
	printf("MAP SIZE IS %x \n", regTable.size());
	printf("QUANTITY %x \n", quantity);
	printf("QUANTITY <<1 %x \n", quantity<<1);
	for(int i=0; i < quantity; i++){
		printf("address %x \n",(startingAddress+i));

		//return default values when there aren't any values
		if (regTable.find((uint16_t)(startingAddress+i)) == regTable.end()) {
			reply[i] = 0XFF;
		}
		else{
			printf("register %x \n",regTable.at((uint16_t)(startingAddress+i)));
			//printf("TRIAL %x \n",0XFFFF);
			//if(regTable.at((startingAddress+i)))
			reply[i] = regTable.at((uint16_t)(startingAddress+i));
		}

		printf("reply %x \n",reply[i]);

		if(reply[i]!= regTable.at((uint16_t)(startingAddress+i))){
			//ExceptionCode = SERVER_DEVICE_FAILURE;
			msg->setTxError(SERVER_DEVICE_FAILURE);
			return;
		}
		msg->setLen(quantity<<1);
	}
}

bool HoldingRegsTable::setHolding(uint16_t address, OnRegisterChange handler){
	this->cbTable.insert({address, handler});
	return true;
}


