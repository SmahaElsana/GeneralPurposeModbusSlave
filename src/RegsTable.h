/*
 * RegsTable.h
 *
 *  Created on: 29 Dec 2022
 *      Author: smaha
 */

#ifndef REGSTABLE_H_
#define REGSTABLE_H_
#include <stdint.h>
#include <map>
#include"Message.h"
#include <utility>
#include <functional>

typedef void (*OnRegisterChange)(uint16_t address, uint16_t value);


template <typename T>
class RegsTable {
protected:
	// class variables should be private for security ENCAPCULATION
	//	std::map <uint16_t, T> regTable ;
public:
	std::map <uint16_t, T> regTable ;
	std::map <uint16_t, std::function<void(uint16_t address, uint16_t value)>> cbTable ;
	uint16_t lowerAddress = 0x0;
	uint16_t upperAddress= 0xFFFF;

	RegsTable() {
		// TODO Auto-generated constructor stub

	}

	~RegsTable() {
		// TODO Auto-generated destructor stub
	}
	//map<uint16_t,T>;
	/*RegsTable();
	virtual ~RegsTable();*/
};

#endif /* REGSTABLE_H_ */
