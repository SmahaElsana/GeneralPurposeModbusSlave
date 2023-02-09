/*
 * DiscreteRegsTable.h
 *
 *  Created on: 30 Dec 2022
 *      Author: smaha
 */

#ifndef DISCRETEREGSTABLE_H_
#define DISCRETEREGSTABLE_H_
#include "RegsTable.h"
class DiscreteRegsTable : public RegsTable<int>{
public:
	DiscreteRegsTable();
	virtual ~DiscreteRegsTable();
};

#endif /* DISCRETEREGSTABLE_H_ */
