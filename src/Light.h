/*
 * Light.h
 *
 *  Created on: 28 Jan 2023
 *      Author: marwa
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_
#include <stdint.h>
#include <iostream>

class Light {
public:
	bool status ;
	Light();
	Light(bool value);
	virtual ~Light();
	void update (bool value);
};

#endif /* SRC_LIGHT_H_ */
