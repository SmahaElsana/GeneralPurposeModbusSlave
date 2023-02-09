/*
 * Message.h
 *
 *  Created on: 31 Dec 2022
 *      Author: smaha
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <stdint.h>
#include <vector>


class Message {


private:
	uint8_t function_code;

	//std::vector<uint8_t> data;
	uint8_t* data;
	uint8_t* tx;
	int len;

public:
	Message();
	Message(uint8_t funCode,uint8_t* data,uint8_t* tx, int length);
	virtual ~Message();

	uint8_t getFunctionCode();
	uint8_t* getData();
	uint8_t* getTx();
	int getLen();
	void setTx(uint8_t* tx);
	void setLen(int len);
	void setTxfunctionCode(uint8_t functionCode);
	void setTxError(uint8_t functionCode);







};

#endif /* MESSAGE_H_ */
