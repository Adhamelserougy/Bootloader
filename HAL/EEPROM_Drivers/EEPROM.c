#include "HAL/EEPROM_Drivers/EEPROM.h"

void EEPROM_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)){}
}

void EEPROM_Write(uint32_t *data,uint32_t address,uint8_t size)
{
    EEPROMProgram(data,address,size);
}

void EEPROM_Read(uint32_t *data,uint32_t address,uint8_t size)
{
    EEPROMRead(data, address, size);
}


