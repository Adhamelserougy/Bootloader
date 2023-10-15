#include "main.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"

#define MAX_Size 10000

uint8_t Code_hex[MAX_Size] = {0};
uint16_t Code_Size=0;
int main(void)
{
    /*************************** Initialization **************************/
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    can_init();
    EEPROM_init();


    /*********** Message object to be sent **************/
    tCANMsgObject sCANMessage;

    can_init();

    sCANMessage.ui32MsgID = 1;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
    sCANMessage.ui32MsgLen = 4;

    /*********************************************************/

    /*********** Message object to be recieved **************/

    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);
    /*********************************************************/

    /***********************************************************************/
    /*Send ACK*/

//    while(can_send(&sCANMessage_Tx, 2) != CAN_OK);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0U);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0U);

    can_receiveFile(&sCANMessage,Code_hex,&Code_Size);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0U);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_CAN0);
    Assign_Bank(1);
    Erase_Sector();
    Flash_New_Program((uint32_t *)Code_hex, Code_Size);
    Jump_To_New_Program();

    /*
    Assign_Bank(Bank); TODO: Choose either bank 1 or bank 2 to flash by reading the flag in EEPROM
    Erase_Sector(); TODO: Call Erase_Sector to clear bank before flashing new program
    Flash_New_Program(Code, Code_Size); TODO: Flash new program by giving it a uint32_t pointer to the array that contains code and the number of elements in array
    Jump_To_New_Program(); TODO: Call this to jump to new program
    */
}
