/*
 * Message.cpp
 *
 *  Created on: 31 Dec 2022
 *      Author: smaha
 */

#include "Message.h"
#include <stdio.h>

Message::Message() {
	// TODO Auto-generated constructor stub

}
Message::Message(uint8_t funCode,uint8_t* data,uint8_t* tx,int len){
	printf("Message consructor data pointer0 %x \n", data[0]);
	printf("Message consructor data pointer1 %x \n", data[1]);
	printf("Message consructor data pointer2 %x \n", data[2]);
	printf("Message consructor data pointer3 %x \n", data[3]);
	function_code = funCode;
	/*for(int i=0; i<len-8;i++){
		this->data.push_back(data[i]);
	}*/
	this->data = new uint8_t(len-8);
	for(int i=0; i<len-8;i++){
			this->data[i]=data[i];
			printf("Message consructor data pointer%d %x \n",i, data[i]);
		}
//	this->data = data;
	this->tx = tx;
	this->len = len;

}



Message::~Message() {
	// TODO Auto-generated destructor stub
}

uint8_t Message:: getFunctionCode(){
	return function_code;
}

uint8_t* Message:: getData(){
	return data;
}

uint8_t* Message:: getTx(){
	return tx;
}

int Message::getLen(){
	return this->len;
}

void Message::setTx(uint8_t* tx){
	this->tx = tx;
}

void Message::setLen(int len){
	this->len = len;
}

void Message::setTxfunctionCode(uint8_t functionCode){
	(this->tx)[7]= functionCode;

}

void Message::setTxError(uint8_t error){
	(this->tx)[7]= this->function_code|0x80;
	(this->tx)[8]= error;
	this->len = 9;


}
