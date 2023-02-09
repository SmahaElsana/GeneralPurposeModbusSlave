/*
 * InputRegsTable.h
 *
 *  Created on: 29 Dec 2022
 *      Author: smaha
 */

#ifndef INPUTREGSTABLE_H_
#define INPUTREGSTABLE_H_
#include "RegsTable.h"

class InputRegsTable: public RegsTable<int>{
public:
	InputRegsTable();
	virtual ~InputRegsTable();
};

#endif /* INPUTREGSTABLE_H_ */
