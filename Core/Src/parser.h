/*
 * message.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Mustafa
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "stm32f4xx_hal.h"

void parserMessage(uint8_t buffer[15]);

typedef struct __Message
{
	char start;
	uint16_t emirno;
	uint8_t slaveno;
	uint32_t emiradres;
	uint8_t rorw;
	uint32_t datatype;
	uint32_t data_block;
	char end;
}Message;

typedef enum {
    HATA_BIR = 13,
    HATA_IKI,
    HATA_UC
} HataKodlari;

#endif /* SRC_PARSER_H_ */
