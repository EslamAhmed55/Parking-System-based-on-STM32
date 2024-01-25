

#include "MCAL/Stm32_F103C6_USART.h"
#include <stdint.h>


#define RFID_ENTRY USART1
#define RFID_EXIT USART2

void RFID_init(void)
{
	USART_Config_t USART_EntryConfig;
	USART_EntryConfig.BaudRate = UART_BaudRate_115200;
	USART_EntryConfig.HwFlowCtl = UART_HwFlowCtl_NONE;
	USART_EntryConfig.IRQ_Enable = UART_IRQ_Enable_NONE;
	USART_EntryConfig.Parity = UART_Parity_NONE;
	USART_EntryConfig.Payload_Length = UART_Payload_Length_8B;
	USART_EntryConfig.StopBits = UART_StopBits_1;
	USART_EntryConfig.USART_Mode = UART_Mode_TX_RX;
	MCAL_UART_Init(RFID_ENTRY, &USART_EntryConfig);
	MCAL_UART_GPIO_Set_Pins(RFID_ENTRY);


	USART_Config_t USART_ExitConfig;

	USART_ExitConfig.BaudRate = UART_BaudRate_115200;
	USART_ExitConfig.HwFlowCtl = UART_HwFlowCtl_NONE;
	USART_ExitConfig.IRQ_Enable = UART_IRQ_Enable_NONE;
	USART_ExitConfig.Parity = UART_Parity_NONE;
	USART_ExitConfig.Payload_Length = UART_Payload_Length_8B;
	USART_ExitConfig.StopBits = UART_StopBits_1;
	USART_ExitConfig.USART_Mode = UART_Mode_TX_RX;
	MCAL_UART_Init(RFID_EXIT, &USART_ExitConfig);
	MCAL_UART_GPIO_Set_Pins(RFID_EXIT);
}

uint16_t RFID_entry_Read(void)
{
	uint16_t entryId = 0;
	MCAL_UART_ReceiveData(RFID_ENTRY, &entryId, enable);

	return entryId;
}

uint8_t RFID_entry_isavailable(void)
{
	return MCAL_UART_IsDataAvailable(RFID_ENTRY);
}

uint16_t RFID_exit_Read(void)
{
	uint16_t exitId = 0;
	MCAL_UART_ReceiveData(RFID_EXIT, &exitId, enable);

	return exitId;
}

uint8_t RFID_exit_isavailable(void)
{
	return MCAL_UART_IsDataAvailable(RFID_EXIT);
}

