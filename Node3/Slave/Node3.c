/*
 * Master.c
 *
 * Created: 2/2/2019 5:04:06 PM
 * Author : ebrah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\comm_stack.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\gpio\GPIO.h"

void transmission_complete()
{		
}
void Receive_Complete(uint8* RX_data,uint16 num)
{
	gpio_uart_cng();
	CommTx_DataCfgType Data_toTransmit={transmission_complete,(RX_data+1),num,UART0_CHANNEL};
	comm_TxInit(&Data_toTransmit);
	RX_CommFree();
}
int main(void)
{
   sei();
      
   RX_cfg_t message1={Receive_Complete,I2C0,'*'};	   
   Comm_RxInit(&message1);
   
    while (1) 
    {
		RX_com_dispatch();
		
    }
}

