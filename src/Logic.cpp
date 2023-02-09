/*
 * Logic.cpp
 *
 *  Created on: 14 Dec 2022
 *      Author: marwa
 */

#include "Logic.h"
#define MAIN_LED 0x03

Logic::Logic() {
	// TODO Auto-generated constructor stub

}

// add logic init where we initialize all lghts
Logic::Logic(SlaveManager* sm){
	this->sm = sm;
	//move this to init
	//this->sm->setRegisterChangeHandler(ledChange, READ_HOLD_REGISTER, MAIN_LED);//#table 0x03 -> holding

}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

void Logic::init(){
//create register 0 with callback function -> ledChange
	//change numbers to constants
	printf("got to init \n");
	this->sm->setRegisterChangeHandler(On, READ_COIL, 0x30);
	this->sm->setRegisterChangeHandler(Mode, READ_HOLD_REGISTER, 0x7);
	this->sm->setRegisterChangeHandler(SetTemperature, READ_HOLD_REGISTER, 0x9);
	this->sm->setRegisterChangeHandler(Temperature, READ_HOLD_REGISTER, 0);
	this->sm->setRegisterChangeHandler(FanSpeed, READ_HOLD_REGISTER, 0x8);


}


void Logic::logicMsg(Message* m,int len ){

	//	char mybuff [len*2];
	//		mybuff[len*2] = 0;
	//		for(int j = 0; j < len; j++)
	//			sprintf(&mybuff[2*j], "%02X", s[j]);
	//		cout<<mybuff<<endl;
	printf("logic msg : %x\n", m->getFunctionCode());

}

Light* Logic:: createLight (){
	Light* light = new Light();
	printf("light created");
	return light;
}


void Logic::On(uint16_t address, uint16_t value){
	printf("On address %x change to value %x \n",address, value);
}
void Logic::Mode(uint16_t address, uint16_t value){
	printf("Mode address %x change to value %x \n",address, value);
}
void Logic::SetTemperature(uint16_t address, uint16_t value){
	printf("SetTemperature address %x change to value %x \n",address, value);
}
void Logic::Temperature(uint16_t address, uint16_t value){
	printf("Temperature address %x change to value %x \n",address, value);
}
void Logic::FanSpeed(uint16_t address, uint16_t value){
	printf("FanSpeed address %x change to value %x \n",address, value);
}

