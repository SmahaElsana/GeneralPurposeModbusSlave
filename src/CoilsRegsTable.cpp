/*
 * CoilsRegsTable.cpp
 *
 *  Created on: 29 Dec 2022
 *      Author: smaha
 */
#include <iostream>
#include "CoilsRegsTable.h"

CoilsRegsTable::CoilsRegsTable(){
	// TODO Auto-generated constructor stub

}

CoilsRegsTable::~CoilsRegsTable() {
	// TODO Auto-generated destructor stub
}

void CoilsRegsTable:: WriteSingleCoil(Message* msg, int sideEffect){
	//	uint8_t ExceptionCode = 0;
	uint16_t address = ((uint16_t)*msg->getData()<< 8) | *(msg->getData()+1);
	uint16_t value = ((uint16_t)*(msg->getData()+2)<< 8) | *(msg->getData()+3);
	//should return after the first error
	if(value != 0xFF00 && value != 0x0000){
		//ExceptionCode = 0x03;
		msg->setTxError(ILLEGAL_DATA_VALUE);
		return;
	}
	else if(address < 0 || address > 0xFFFF){
		msg->setTxError(ILLEGAL_DATA_ADDRESS);
		return;
	}

	printf(" address %x\n", address);
	printf(" value %x\n", value);



	if(value == 0xFF00){
		regTable.insert({address,1});
		if(regTable.at(address) != 1){
			msg->setTxError(SERVER_DEVICE_FAILURE);
			return;
		}

	}
	else{
		regTable.insert({address,0});
		if(regTable.at(address) != 0){
			msg->setTxError(SERVER_DEVICE_FAILURE);
			return;
		}
	}
	if(sideEffect){
		(this->cbTable.at(address))(address,value);
	}

	printf("ALL GOOD\n");
}


/*
 * byte - function code
 * 2 byte - starting address
 * 2 byte - quantity of outputs
 * byte - count
 * N bytes- outputs value
 * */
void CoilsRegsTable::writeMultipleCoils(Message* msg, int sideEffect){
	printf("GOT TO COILS \n");
	uint16_t startingAddress = ((uint16_t)*msg->getData()<< 8) | *(msg->getData()+1);
	uint16_t quantity = ((uint16_t)*(msg->getData()+2)<< 8) | *(msg->getData()+3);
	printf("QUANTITY %x \n", quantity);
	int count = *(msg->getData()+4);
	printf("COUNT %x \n", count);
	uint8_t q = *(msg->getData()+4);

	printf("Q %x \n", q);


	uint8_t* outputs = (msg->getData()+5);

	if(quantity > 0X007B || quantity < 0x0001 || quantity != count*2){
		msg->setTxError(ILLEGAL_DATA_VALUE);
		return;
	}
	if(startingAddress <lowerAddress || startingAddress > upperAddress || startingAddress+ quantity > upperAddress){
		msg->setTxError(ILLEGAL_DATA_ADDRESS);
		return;
	}
	printf("DONE CHECKING \n");

	int loop = quantity%8 ==0? quantity/8 : quantity/8 +1;
	printf("loop : %d \n",loop);
	int icount = 0;
	uint8_t cur;
	uint8_t curbit;

	for(int i=0; i < count; i++){
		//cur = *(outputs+i);
		cur = *(msg->getData()+5+i);
		printf(" cur byte %x \n", cur);
		for(int bit=0; bit<8 & icount < quantity; bit++){

			curbit = cur & 0x01;
			printf(" curbit byte %x \n", curbit);

			printf("start %x \n", startingAddress+icount);
			printf("value %x \n", curbit);

			if(curbit != 0){
				regTable.insert({startingAddress+icount,1});
			}
			else{
				regTable.insert({startingAddress+icount,0});
			}
			icount ++;
			cur = cur >> 1;
		}






		/*	if(regTable.at((startingAddress+i)) != *(outputs+i)){
			//ExceptionCode = SERVER_DEVICE_FAILURE;
			msg->setTxError(SERVER_DEVICE_FAILURE);
			return;
		}*/
	}

	msg->setLen(12);

}


void CoilsRegsTable:: ReadCoils(Message* msg){
	uint16_t startingAddress = ((uint16_t)*msg->getData()<< 8) | *(msg->getData()+1);
	uint16_t quantity = ((uint16_t)*(msg->getData()+2) << 8) | *(msg->getData()+3);
	printf("QUANTITY %x \n", quantity);
	printf("STARTING ADDRESS %x \n", startingAddress);

	if(startingAddress < lowerAddress || startingAddress > upperAddress || startingAddress + quantity  > upperAddress){
		//Exception 02
		msg->setTxError(ILLEGAL_DATA_ADDRESS);
		return;
	}

	if(quantity< 0x0001|| quantity> 0x07D0){
		//Exception 03
		msg->setTxError(ILLEGAL_DATA_VALUE);
		return;
	}

	int loop = quantity%8 == 0? quantity/8 : quantity/8+1;
	int count = 0;
	uint16_t *reply=new uint16_t[loop];
	for(int i=0; i<loop; i++){
		for(int bit=0; bit<8 & count< quantity; bit++){

			if (regTable.find((startingAddress+bit)) == regTable.end()) {
				reply[bit] = 0XFF;
			}
			else{
				reply[bit] = regTable.at(startingAddress+bit);
			}
			printf("replay[%d] %x\n",bit, reply[bit]);
			count++;
		}

	}


}

bool CoilsRegsTable::setCoils(uint16_t address, OnRegisterChange handler){
	printf("got to setCoils \n");
	this->cbTable.insert({address, handler});
	printf("DOne INSERTING address %x TO CB COILS\n", address);
	return true;
}

/*OnRegisterChange CoilsRegsTable::applyHandler(uint16_t address){
	return this->cbTable.at(address);
}*/

