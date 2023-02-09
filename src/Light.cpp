/*
 * Light.cpp
 *
 *  Created on: 28 Jan 2023
 *      Author: marwa
 */

#include "Light.h"

Light::Light() {
	// TODO Auto-generated constructor stub

}
Light::Light(bool value) {
	this->status = value;

}

Light::~Light() {
	// TODO Auto-generated destructor stub
}
//callback function
void Light::update(bool value){

	this->status = value;

	if(this->status){
		printf("light is on\n");
	}
	else{
		printf("light is off\n");
	}

}

