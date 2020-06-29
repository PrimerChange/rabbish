
#include "./dht11/bsp_dht11.h"

#include "delay.h"



uint8_t DH_11_init(void)
{
	uint8_t ret;
	DHT11_GPIO_Config ();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	return ret;
}

static void DHT11_GPIO_Config ( void )
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStruct; 

	
	/*开启DHT11_Dout_GPIO_PORT的外设时钟*/
  __HAL_RCC_GPIOC_CLK_ENABLE();
	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/															   
  	GPIO_InitStruct.Pin  = GPIO_PIN_13;

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

	/*设置引脚速率为50MHz */   
  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/*调用库函数，初始化DHT11_Dout_GPIO_PORT*/
  	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}

void DH11_GPIO_OUT_PP(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOC_CLK_ENABLE();
 GPIO_InitStruct.Pin  = GPIO_PIN_13;
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
 HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void DH11_GPIO_INPUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
 
 __HAL_RCC_GPIOC_CLK_ENABLE();
 GPIO_InitStruct.Pin  = GPIO_PIN_13;
 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
 HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

uint8_t Read_Byte(void)
{
	uint8_t i;
	uint8_t data = 0;
	DH11_GPIO_INPUT();//DAT设置为输入
 for(i=0; i<8; i++)
 {
  data <<= 1;
  while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET);//每一位数据前会有一个50us的低电平时间，等待该低电平结束
  //26-28us的高电平表示该位是0，70us高电平表示该位是1
  delay_us(30);//延时30us后检测电平状态
  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_SET)
  {
   data |= 0x01;
   while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET);
  }
 }
 return data;

}

void DHT_ReadData(uint8_t*DHT_data)
{
		 uint8_t i;
		 DH11_GPIO_OUT_PP();//DAT设置为输出
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);//低电平大于18ms发送开始信号
		 delay_ms(20);
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		 delay_us(40);//延时20-40us
		 DH11_GPIO_INPUT();//DAT设置为输入
		 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET)
		 {
			while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET);
		 }
		 while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_SET);
		 for(i=0; i<5; i++)
		 {
			DHT_data[i] =  Read_Byte();
		 }
		 delay_us(50);
}

void DHT_Reset(void)
{
	DH11_GPIO_OUT_PP();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

DHT11_Data_TypeDef DHT_ShowData(void)
{
	int i,j,k,p;
	uint8_t DHT_data[5];
	DHT11_Data_TypeDef DHT11_Data;
	DHT_ReadData(DHT_data);
	DHT_Reset();
	DHT11_Data.humi_int= DHT_data[0];

	DHT11_Data.humi_deci= DHT_data[1];

	DHT11_Data.temp_int= DHT_data[2];

	DHT11_Data.temp_deci= DHT_data[3];

	DHT11_Data.check_sum= DHT_data[4];
	
	DHT11_Data.dirty  = ((DHT11_Data.humi_int << 8) + DHT11_Data.humi_deci) / 10.0;
	
	DHT11_Data.temp = ((DHT11_Data.temp_int << 8) + DHT11_Data.temp_deci) / 10.0;
	
	return DHT11_Data;
}


/*************************************END OF FILE******************************/
