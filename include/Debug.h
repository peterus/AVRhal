/*
 * Debug.h
 *
 * Created: 26.10.2014 20:01:06
 *  Author: Peter Buchegger
 */ 

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
//#define _DEBUG

#ifdef _DEBUG

	#include "COM/UART.h"
	#define DEBUG_OUT(format, args ...)	printf(format, ## args)

#else

	#define DEBUG_OUT(...)

#endif

#endif /* DEBUG_H_ */
