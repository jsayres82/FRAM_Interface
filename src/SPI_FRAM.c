/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
/*
 * Copyright (c) 2014 by Cypress Semiconductor Technology Pvt Ltd. <medu@cypress.com>
 * SPI F-RAM Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
#include "SPI_FRAM.h"
#include "HwConfig.h"
static DRV_FRAM_OBJ framObj;

uint8_t scratchBuffer[0x100];
#define GetSystemClock() (200000000UL)/* Fcy = 80MHz */
#define us_SCALE   (GetSystemClock()/2000000)
#define ms_SCALE   (GetSystemClock()/2000)

static uint32_t ReadCoreTimer(void);

static uint32_t ReadCoreTimer()
{
    volatile uint32_t timer;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return(timer);
}
void DelayMs(unsigned long int msDelay )
{
      register unsigned int startCntms = ReadCoreTimer();
      register unsigned int waitCntms = msDelay * ms_SCALE;
 
      while( ReadCoreTimer() - startCntms < waitCntms );
}

void FRAM_Write_Enable();
void FRAM_Update_RW_Count();
void FRAM_Set_Storage_Address();
//void FRAM_Get_Config_Data();
void FRAM_Set_Config_Data();
void FRAM_Write_Single_Row(uint16_t row, uint8_t val);
uint16_t FRAM_Read_Single_Row(uint16_t row);
void FRAM_Write_All_Locations(uint8_t val);
uint32_t FRAM_Read_All_Locations();
void uitoa(uint16_t Value, uint8_t* Buffer);
// This callback is executed after the Conversion command has been sent
void FRAM_CommandComplete()
{
    framObj.inUse = false;
    
    // Clear Chip Select
     FRAM_CHIP_SELECT_DISABLE(); //release chip, signal end transfer
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Init
// Purpose   : API to initialize the SPI F-RAM
// Arguments : None
// Return    : None
// Usage     : Eg: FRAM_SPI_Init();
//--------------------------------------------------------------------------------------
CONFIG_DATA_RESULT FRAM_SPI_Init(DRV_HANDLE drvSPIHandle, SPI_MODULE_ID spiId)
{
    CONFIG_DATA_RESULT result;
    uint32_t sum = 0;    
    uint8_t val = 1;
    uint8_t tempByte;
    // Initialize SPI
    framObj.spiClientHandle = drvSPIHandle;
    framObj.spiIndex = spiId;
    DelayMs(1000);
    
    FRAM_CHIP_SELECT_DISABLE(); //Disable Chip Select
    
    // Check Status Register
    framObj.statusRegister = FRAM_SPI_Status_Reg_Read();                
    tempByte = framObj.statusRegister.byte;
    if(framObj.statusRegister.byte != 0)
    {
        framObj.statusRegister.byte = 0;
        FRAM_SPI_Status_Reg_Write(framObj.statusRegister);
        if(framObj.statusRegister.byte != FRAM_SPI_Status_Reg_Read().byte)
        {
            if(tempByte == FRAM_SPI_Status_Reg_Read().byte)
                result = ERROR;                                     // Cant write to status reg
            else                
                result = ERROR;                                     // Write data was corrupt
        }
    }
    // for debugging
//    FRAM_Write_All_Locations(0);
    
    // Test write/read
    FRAM_Write_Single_Row(2, val);
    sum = FRAM_Read_Single_Row(2);    
    if(sum != val*ROW_BYTE_COUNT)
         result = ERROR;                                            // Error during test write/read
    
    // Get the config Data
    rwCountAddr = FRAM_Get_Storage_Address();
    if(rwCountAddr != 0x0000)
    {
        rwCycles = FRAM_Get_RW_Count();
        if(rwCycles != 0)
        {
            configDataAddr = rwCountAddr + 4;
            FRAM_Get_Config_Data();
            if(strlen(configData.fwVersion) == 0)
            {
                FRAM_Set_Config_Data();
                result = CONFIG_DATA_CORRUPTED;
            }
            else
            {
                result = CONFIG_DATA_FOUND;
            }
        }
        else
        {
            FRAM_Set_Config_Data();
            result = CONFIG_DATA_CORRUPTED;
        }
    }
    else
    {
        rwCountAddr = FIRST_RW_COUNT_ADDR;
        configDataAddr = FIRST_CONFIG_DATA_ADDR;
        FRAM_Set_Storage_Address();
        FRAM_Set_Config_Data();
        result = CONFIG_DATA_LOADED_FROM_DEFAULT;
    }
    return result;    
}


//--------------------------------------------------------------------------------------
// FRAM_SPI_Write_Config
// Purpose   : API to write to SPI F-RAM
// Arguments : None
// Return    : true if successful
// Usage     : Eg: FRAM_SPI_Write_Config(); Writes 
//--------------------------------------------------------------------------------------
void FRAM_Save_Configuration_Data()
{
    WM_HWIN hItem;
    char tempBuffer[10];
    FRAM_Set_Config_Data();
    
    hItem = WM_GetDialogItem(emWin_GuiScreenGet(EMWIN_APP_SCREEN_TEXT_ALIGNMENT), 0x809);
    sprintf(tempBuffer, "0x%04X", rwCountAddr);
    TEXT_SetText(hItem, tempBuffer);
    memset(tempBuffer, 0, 10);
    
    hItem = WM_GetDialogItem(emWin_GuiScreenGet(EMWIN_APP_SCREEN_TEXT_ALIGNMENT), 0x806);
    sprintf(tempBuffer, "%02u / %u", rwCycles, MAX_RW_COUNT);
    TEXT_SetText(hItem, tempBuffer);
    memset(tempBuffer, 0, 10);

}

//--------------------------------------------------------------------------------------
// FRAM_Save_Config_Data
// Purpose   : API to write to SPI F-RAM
// Arguments : None
// Return    : None
// Usage     : Eg: FRAM_SPI_Write(0x0000, 0x55); Writes data byte 0x55 to F-RAM address 0x0000
//--------------------------------------------------------------------------------------
void FRAM_Set_Config_Data()
{
    FRAM_Write_Enable();
  
    // F-RAM WRITE OPERATION
    FRAM_CHIP_SELECT_ENABLE();                                                //chip select
    drvSPI1TXbuffer[0] = WRITE;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(rwCountAddr);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(rwCountAddr);
    rwCycles++;
    if(rwCycles > MAX_RW_COUNT)
    {
        //update address 
        rwCountAddr += sizeof(configData) + 4;
        configDataAddr += sizeof(configData) + 4;
        rwCycles = 0;
        FRAM_Set_Storage_Address();
        FRAM_Set_Config_Data();
        return;
    }
  
    drvSPI1TXbuffer[3] = MSB_RW_COUNT_BYTE(rwCycles);
    drvSPI1TXbuffer[4] = MSB2_RW_COUNT_BYTE(rwCycles);
    drvSPI1TXbuffer[5] = LSB2_RW_COUNT_BYTE(rwCycles);
    drvSPI1TXbuffer[6] = LSB_RW_COUNT_BYTE(rwCycles);
  
    memcpy(&drvSPI1TXbuffer[7], &configData, sizeof(configData));
  
    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(framObj.spiClientHandle,
                                            &drvSPI1TXbuffer[0], sizeof(configData) + 8,        // Bytes to send
                                            &drvSPI1RXbuffer[0], 0,                             // Bytes to receive
                                            (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                                            NULL);     // context 
  
    while(framObj.inUse);
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Write
// Purpose   : API to write to SPI F-RAM
// Arguments : None
// Return    : None
// Usage     : Eg: FRAM_SPI_Write(0x0000, 0x55); Writes data byte 0x55 to F-RAM address 0x0000
//--------------------------------------------------------------------------------------
void FRAM_Get_Config_Data()
{
    FRAM_CHIP_SELECT_ENABLE();                   //chip select
    drvSPI1TXbuffer[0] = READ;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(configDataAddr);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(configDataAddr);

    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 3,                             // Bytes to send
                              &drvSPI1RXbuffer[0], sizeof(configData)+3,          // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    while(framObj.inUse);

    memcpy(&configData, &drvSPI1RXbuffer[3], sizeof(configData));

    FRAM_Update_RW_Count();
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
uint16_t FRAM_Get_Storage_Address()
{
    uint16_t data;

    //FRAM READ OPERATION

    FRAM_CHIP_SELECT_ENABLE();                   //chip select
    drvSPI1TXbuffer[0] = READ;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(STORAGE_ADDR);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(STORAGE_ADDR);
    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 3,                          // Bytes to send
                              &drvSPI1RXbuffer[0], 5,                          // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    while(framObj.inUse);

    data = (((uint16_t)drvSPI1RXbuffer[3]<<8) | (uint16_t)drvSPI1RXbuffer[4]);
    return data;   // Return data byte
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
void FRAM_Set_Storage_Address()
{
    FRAM_Write_Enable();

    // F-RAM WRITE OPERATION
    FRAM_CHIP_SELECT_ENABLE();                                                //chip select
    drvSPI1TXbuffer[0] = WRITE;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(STORAGE_ADDR);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(STORAGE_ADDR);
    drvSPI1TXbuffer[3] = MSB_ADDR_BYTE(rwCountAddr);
    drvSPI1TXbuffer[4] = LSB_ADDR_BYTE(rwCountAddr);

    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 5,                          // Bytes to send
                              &drvSPI1RXbuffer[0], 0,                          // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    while(framObj.inUse);
  
}


//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
uint32_t FRAM_Get_RW_Count()
{
    uint32_t data;

    FRAM_SPI_BurstRead(rwCountAddr, scratchBuffer, 4);
    data = ((((uint32_t)scratchBuffer[0])<<24) | ((uint32_t)scratchBuffer[1])<<16 | ((uint32_t)scratchBuffer[2])<<8 |  (uint32_t)scratchBuffer[3]);

    return data;   // Return data byte
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
void FRAM_Update_RW_Count()
{
    rwCycles++;
    if(rwCycles > MAX_RW_COUNT)
    {
        //update address 
        rwCountAddr += sizeof(configData) + 4;
        configDataAddr += sizeof(configData) + 4;
        rwCycles = 0;
        FRAM_Set_Storage_Address();
        FRAM_Set_Config_Data();
        return;
    }

    scratchBuffer[0] = MSB_RW_COUNT_BYTE(rwCycles);
    scratchBuffer[1] = MSB2_RW_COUNT_BYTE(rwCycles);
    scratchBuffer[2] = LSB2_RW_COUNT_BYTE(rwCycles);
    scratchBuffer[3] = LSB_RW_COUNT_BYTE(rwCycles);

    FRAM_SPI_BurstWrite(rwCountAddr, scratchBuffer, 4);
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
void FRAM_Write_Single_Row(uint16_t row, uint8_t val)
{
    uint8_t buf[ROW_BYTE_COUNT];
    uint16_t i;
    for(i=0; i < ROW_BYTE_COUNT; i++)
        buf[i] = val;
    FRAM_SPI_BurstWrite((row-1)*ROW_BYTE_COUNT, buf, ROW_BYTE_COUNT);
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
uint16_t FRAM_Read_Single_Row(uint16_t row)
{
    uint8_t i;
    uint16_t sum = 0;
    uint8_t buf[ROW_BYTE_COUNT];
    
    FRAM_SPI_BurstRead((row-1)*ROW_BYTE_COUNT, buf, ROW_BYTE_COUNT);
    for(i=0; i<ROW_BYTE_COUNT; i++)
        sum += buf[i];
    
    return sum;
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
void FRAM_Write_All_Locations(uint8_t val)
{
    uint8_t buf[MAX_NUM_OF_BYTES];
    uint16_t bytesRemaining = NUMBER_OF_STORAGE_LOCATIONS;
    memset(buf, val, MAX_NUM_OF_BYTES);
    while(bytesRemaining)
    {
        FRAM_SPI_BurstWrite(NUMBER_OF_STORAGE_LOCATIONS - bytesRemaining, buf, MAX_NUM_OF_BYTES);    
        bytesRemaining -= MAX_NUM_OF_BYTES;
    }    
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
uint32_t FRAM_Read_All_Locations()
{    
    uint8_t buf[MAX_NUM_OF_BYTES];
    uint16_t i;
    uint32_t sum = 0;
    uint16_t bytesRemaining = NUMBER_OF_STORAGE_LOCATIONS;
    
    while(bytesRemaining)
    {
        FRAM_SPI_BurstRead(NUMBER_OF_STORAGE_LOCATIONS-bytesRemaining, buf, MAX_NUM_OF_BYTES);
        for(i=0; i < MAX_NUM_OF_BYTES; i++)
            sum += buf[i];
        bytesRemaining -= MAX_NUM_OF_BYTES;
    }
    return sum;
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Write_Enable
// Purpose   : API to write to SPI F-RAM
// Arguments : None
// Return    : None
// Usage     : Eg: FRAM_SPI_Write(0x0000, 0x55); Writes data byte 0x55 to F-RAM address 0x0000
//--------------------------------------------------------------------------------------
void FRAM_Write_Enable()
{
    // F-RAM WRITE ENABLE COMMAND
    FRAM_CHIP_SELECT_ENABLE();  //chip select
    drvSPI1TXbuffer[0] = WREN;
    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 1,         // Bytes to send
                              &drvSPI1RXbuffer[0], 0,         // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    framObj.inUse = true;
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Write
// Purpose   : API to write to SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
//             FRAM_data    -> 1 byte data
// Return    : None
// Usage     : Eg: FRAM_SPI_Write(0x0000, 0x55); Writes data byte 0x55 to F-RAM address 0x0000
//--------------------------------------------------------------------------------------
void FRAM_SPI_Write(uint32_t FRAM_address, uint8_t FRAM_data)
{
    FRAM_Write_Enable();
    
    FRAM_CHIP_SELECT_ENABLE();                                                //chip select
    drvSPI1TXbuffer[0] = WRITE;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(FRAM_address);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(FRAM_address);
    drvSPI1TXbuffer[3] = (uint8_t)(FRAM_data);
    framObj.inUse = true;
    
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(framObj.spiClientHandle,
                                    &drvSPI1TXbuffer[0], 4,                          // Bytes to send
                                    &drvSPI1RXbuffer[0], 0,                          // Bytes to receive
                                    (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                                    NULL);     // context 
  
    while(framObj.inUse);  
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Read
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
// Return    : 1 byte data read from F-RAM
// Usage     : Eg: value = FRAM_SPI_Read(0x0000); Reads 1-byte data from F-RAM and assigns to
//           : variable 'value'
//--------------------------------------------------------------------------------------
uint8_t FRAM_SPI_Read(uint32_t FRAM_address)
{
  uint8_t data;

  //FRAM READ OPERATION

  FRAM_CHIP_SELECT_ENABLE();                   //chip select
  drvSPI1TXbuffer[0] = READ;
  drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(FRAM_address);
  drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(FRAM_address);
  framObj.inUse = true;
  framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                            framObj.spiClientHandle,
                            &drvSPI1TXbuffer[0], 3,                          // Bytes to send
                            &drvSPI1RXbuffer[0], 4,                          // Bytes to receive
                            (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                            NULL);     // context 
  while(framObj.inUse);
  
  data = drvSPI1RXbuffer[3];
  return data;   // Return data byte
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Status_Reg_Write
// Purpose   : API to write to SPI F-RAM
// Arguments : FRAM_data    -> 1 byte status data
// Return    : None
// Usage     : Eg: FRAM_SPI_Status_Reg_Write(0x00); Writes data byte 0x00 to F-RAM status register
//--------------------------------------------------------------------------------------
void FRAM_SPI_Status_Reg_Write(FRAM_STATUS_REG_RESP FRAM_data)
{
    FRAM_Write_Enable();
    
    // F-RAM WRITE OPERATION
    FRAM_CHIP_SELECT_ENABLE();                                                //chip select
    drvSPI1TXbuffer[0] = WRSR;
    drvSPI1TXbuffer[1] = (uint8_t)(FRAM_data.byte);
    // F-RAM STATUS WRITE OPERATION
    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 2,                          // Bytes to send
                              &drvSPI1RXbuffer[0], 0,                          // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    while(framObj.inUse);
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_Status_Reg_Read
// Purpose   : API to read status byte from SPI F-RAM
// Arguments : None
// Return    : 1 byte status data read from F-RAM
// Usage     : Eg: status = FRAM_SPI_Status_Reg_Read(); Reads 1-byte status data from F-RAM and assigns to
//           : variable 'status'
//--------------------------------------------------------------------------------------
FRAM_STATUS_REG_RESP FRAM_SPI_Status_Reg_Read(void)
{
    FRAM_STATUS_REG_RESP data;

    //FRAM STATUS READ OPERATION

    FRAM_CHIP_SELECT_ENABLE();                   //chip select
    drvSPI1TXbuffer[0] = RDSR;
    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 1,                          // Bytes to send
                              &drvSPI1RXbuffer[0], 2,                          // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
      //                        &(drvSPI1TXbuffer[0]));     // context 
                              NULL);     // context 
    while(framObj.inUse);
    data.byte = drvSPI1RXbuffer[1]; //get status data byte from F-RAM

    return data;
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_BurstWrite
// Purpose   : API to write to SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
//           : FRAM_wr_data_ptr -> Data Buffer which needs to be written into FRAM
//           : total_count  -> Total number of bytes to write
// Return    : None
// Usage     : Eg: FRAM_SPI_BurstWrite(0x0000, wr_buf,16); Writes 16 bytes of data from wr_buf to F-RAM at address 0x0000
//--------------------------------------------------------------------------------------
void FRAM_SPI_BurstWrite(uint32_t FRAM_address, uint8_t * FRAM_wr_data_ptr, uint32_t total_count)
{
    // If write pointer is NULL, return
    if(FRAM_wr_data_ptr == NULL_PTR)
        return;

    FRAM_Write_Enable();

    // F-RAM WRITE OPERATION
    FRAM_CHIP_SELECT_ENABLE();                                                //chip select
    drvSPI1TXbuffer[0] = WRITE;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(FRAM_address);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(FRAM_address);

    memcpy(&drvSPI1TXbuffer[3], FRAM_wr_data_ptr, total_count+3);

    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], total_count + 3,                          // Bytes to send
                              &drvSPI1RXbuffer[0], 0,                             // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    while(framObj.inUse);  
}

//--------------------------------------------------------------------------------------
// FRAM_SPI_BurstRead
// Purpose   : API to read from SPI F-RAM
// Arguments : FRAM_address -> 2 byte F-RAM address
//           : FRAM_rd_data_ptr -> Buffer to hold the data being read
//           : total_count  -> Total number of bytes to read
// Return    : None
// Usage     : Eg: value = FRAM_SPI_BurstRead(0x0000, rd_buf, 16); Reads 16-bytes of data from F-RAM starting
//           : at address 0x0000 and stores into rd_buf
//--------------------------------------------------------------------------------------
void FRAM_SPI_BurstRead(uint32_t FRAM_address, uint8_t * FRAM_rd_data_ptr, uint32_t total_count)
{
    // If read pointer is NULL, return
    if(FRAM_rd_data_ptr == NULL_PTR)
        return;

    //FRAM READ OPERATION
    FRAM_CHIP_SELECT_ENABLE();                   //chip select
    drvSPI1TXbuffer[0] = READ;
    drvSPI1TXbuffer[1] = MSB_ADDR_BYTE(FRAM_address);
    drvSPI1TXbuffer[2] = LSB_ADDR_BYTE(FRAM_address);

    framObj.inUse = true;
    framObj.spiBufferHandle = DRV_SPI_BufferAddWriteRead(
                              framObj.spiClientHandle,
                              &drvSPI1TXbuffer[0], 3,                          // Bytes to send
                              &drvSPI1RXbuffer[0], total_count+3,                          // Bytes to receive
                              (DRV_SPI_BUFFER_EVENT_HANDLER)FRAM_CommandComplete, // DRV_SPI_BUFFER_EVENT_HANDLER
                              NULL);     // context 
    while(framObj.inUse);

    memcpy(FRAM_rd_data_ptr, &drvSPI1RXbuffer[3], total_count);  
}

/*****************************************************************************
  Function:
	void uitoa(uint16_t Value, uint8_t* Buffer)

  Summary:
	Converts an unsigned integer to a decimal string.
	
  Description:
	Converts a 16-bit unsigned integer to a null-terminated decimal string.
	
  Precondition:
	None

  Parameters:
	Value	- The number to be converted
	Buffer	- Pointer in which to store the converted string

  Returns:
  	None
  ***************************************************************************/
void uitoa(uint16_t Value, uint8_t* Buffer)
{
	uint8_t i;
	uint16_t Digit;
	uint16_t Divisor;
	bool Printed = false;

	if(Value)
	{
		for(i = 0, Divisor = 10000; i < 5u; i++)
		{
			Digit = Value/Divisor;
			if(Digit || Printed)
			{
				*Buffer++ = '0' + Digit;
				Value -= Digit*Divisor;
				Printed = true;
			}
			Divisor /= 10;
		}
	}
	else
	{
		*Buffer++ = '0';
	}

	*Buffer = '\0';
}			    

/* *****************************************************************************
 End of File
 */
