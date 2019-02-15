/*
 * Node2_slave.c
 *
 * Created: 1/26/2019 3:49:24 PM
 * Author : ebrah
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\comm_stack.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\gpio\GPIO.h"


/*

* Recieve from spi 
* transmit through I2c
*/
	
void transmission_complete()
{
	
}

void Receive_Complete(uint8* RX_data,uint16 num)
{
	digitalWrite(A0,PORT_PIN_LEVEL_HIGH);
	CommTx_DataCfgType Data_toTransmit={transmission_complete,RX_data,num,I2C0};
	comm_TxInit(&Data_toTransmit);
	RX_CommFree();
}

int main(void)
{
	sei(); // enable global interrupt
	
	gpio_uart_cng();
	gpio_spi_cng_slave();
	
	RX_cfg_t message1 ={Receive_Complete,SPI0_CHANNEL,'*'}; // call back fun when recieve complet , channel, confirmation litter
	Comm_RxInit(&message1);
	
	while (1)
	{
		RX_com_dispatch();
		comm_TxDisspatcher();
	}
}
