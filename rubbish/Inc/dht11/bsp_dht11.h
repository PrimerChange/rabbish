#ifndef __DHT11_H
#define	__DHT11_H

#include "main.h"



typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
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







