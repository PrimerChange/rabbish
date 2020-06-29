#ifndef __DHT11_H
#define	__DHT11_H

#include "main.h"



typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
	uint32_t dirty;
	uint32_t temp;
		                 
} DHT11_Data_TypeDef;
 

 uint8_t DH_11_init(void);
static void DHT11_GPIO_Config ( void );
void DH11_GPIO_OUT_PP(void);
void DH11_GPIO_INPUT(void);
uint8_t Read_Byte(void);
void DHT_ReadData(uint8_t*DHT_data);
void DHT_Reset(void);
DHT11_Data_TypeDef DHT_ShowData(void);


#endif /* __DHT11_H */







