/*
 * tcp.h
 *
 *  Created on: 21 Dec 2022
 *      Author: marwa
 */

#ifndef TCP_H_
#define TCP_H_
#include "Message.h"
#include <cstdint>
#include <cstring>
#include "SlaveManager.h"




class tcp {
public:
	SlaveManager* sm;
	int port;
	tcp();
	tcp(int port);
	tcp(int port,SlaveManager* sm);
	virtual ~tcp();
	void start();
};

#endif /* TCP_H_ */
