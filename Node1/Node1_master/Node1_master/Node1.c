/*
 * Node1_master.c
 *
 * Created: 1/26/2019 3:47:59 PM
 * Author : ebrah
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\comm_stack.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\gpio\GPIO.h"

void transmission_complete()
{
	digitalWrite(A0,PORT_PIN_LEVEL_HIGH);
}

void Receive_Complete(uint8* RX_data,uint16 num)
{
	CommTx_DataCfgType Data_toTransmit={transmission_complete,RX_data,num,SPI0_CHANNEL};
	comm_TxInit(&Data_toTransmit);
	RX_CommFree();
}



int main(void)
{
	sei(); // enable global interrupt

	SetPinDirection(A0,PORT_PIN_OUT);// test 
	digitalWrite(A0,PORT_PIN_LEVEL_LOW);
	
	gpio_uart_cng();
	gpio_spi_cng_master();
	
	RX_cfg_t message1 ={Receive_Complete,UART0,'*'}; // call back fun when recieve complet , channel, confirmation litter
    Comm_RxInit(&message1);
	
    while (1) 
    {
		RX_com_dispatch();
		comm_TxDisspatcher();
    }
}
