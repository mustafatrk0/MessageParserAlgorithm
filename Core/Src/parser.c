/*
 * parser.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Mustafa ERGÜL
 */

#include "parser.h"
#include "stm32f4xx_hal.h"
#include "stdlib.h"

extern Message parser;
extern HataKodlari HATA;
extern UART_HandleTypeDef huart2;

Message parser;

uint32_t read_value = 0;

void hataMesajiYaz(HataKodlari hataKodu, const char* hataMesaji){
    char hata[50];
    sprintf(hata, "\t HATA: %d %s\n", hataKodu, hataMesaji);
    HAL_UART_Transmit(&huart2, (uint8_t*)hata, strlen(hata), 500);
}
void parserMessage(uint8_t buffer[15])
{
	parser.start = buffer[0]; // '£' Ascii value 0xA3

	parser.emirno = ((uint16_t)buffer[1] << 8 ) | buffer[2];

	parser.slaveno = buffer[3];

	parser.emiradres = (buffer[4] << 24) |(buffer[5] << 16) | (buffer[6] << 8) | buffer[7];

	parser.rorw = buffer[8];

	parser.datatype = buffer[9];

	parser.data_block = (buffer[10] << 24 ) | (buffer[11] << 16) | (buffer[12] << 8) | buffer[13];

	parser.end = buffer[14]; // '%' Ascii value 0x25


	if(parser.start == 0xA3 && parser.end == 0x25){

		HAL_UART_Transmit(&huart2, (uint8_t*)"\t Emir alindi\n",strlen("\t Emir Alindi\n"),500);
		HAL_Delay(100);

		uint8_t readorwrite = (uint8_t*)&parser.rorw;

		if(readorwrite == 0x00) // If reading is to be done
		{
			HAL_UART_Transmit(&huart2, (uint8_t*)"Okuma islemi yapilacak\n",strlen("Okuma islemi yapilacak\n"),500);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)"Emir No: \n",strlen("Emir No: \n"),500);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)&parser.emirno, strlen(parser.emirno), 500);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)"\nSlave No: \n",strlen("\nSlave No: \n"),500);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)&parser.slaveno, strlen(parser.slaveno), 500);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)"\nEmir Adresi: \n",strlen("\nEmir Adresi: \n"),500);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)&parser.emiradres, strlen(parser.emiradres), 500);
			HAL_Delay(100);

			volatile uint32_t *adres = (uint32_t*)parser.emiradres;
			read_value = *adres;
		}
		else if(readorwrite == 0x01){
			HAL_UART_Transmit(&huart2, (uint8_t*) "Yazma islemi yapilacak\n", strlen("Yazma islemi yapilacak\n"),500);
			uint32_t *adres = (uint32_t*)parser.emiradres; //address assignment
			*adres = parser.data_block;

			if(*adres != parser.data_block){
				HataKodlari hata = HATA_IKI;
				char* hataMesaji = "Yazma hatası. Bu bitleri değiştiremezsiniz\n";
				hataMesajiYaz(hata, hataMesaji);
				*adres = 0x00;
			}
		}
	}
	else{
		HataKodlari hata = HATA_BIR;
		char* hataMesaji = "Hatali emir\n";
		hataMesajiYaz(hata, hataMesaji);
	}
}

