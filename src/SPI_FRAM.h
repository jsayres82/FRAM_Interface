/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef SPI_FRAM_H    /* Guard against multiple inclusion */
#define SPI_FRAM_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <stdint.h>
#include "HwConfig.h"
#include "peripheral/spi/plib_spi.h"
/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */

uint16_t rwCountAddr;
uint16_t configDataAddr;
uint32_t rwCycles;

    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */

// IO Assignment for SPI
#define SI      11 //MOSI
#define SO      12 //MISO
#define SCK     13 //sck
#define CS      10 //ss


// SPI F-RAM Opcodes
#define WREN  0x06   // Write Enable Opcode
#define WRDI  0x04   // Write Disable Opcode
#define RDSR  0x05   // Read Status Register Opcode
#define WRSR  0x01   // Write Status Register Opcode
#define READ  0x03   // Read Opcode
#define WRITE 0x02   // Write Opcode

// address masks
#define ADDR_MSB_MASK   (uint16_t)0xFF00
#define ADDR_LSB_MASK   (uint16_t)0x00FF
#define MSB_ADDR_BYTE(addr)   ((uint8_t)((addr & ADDR_MSB_MASK)>>8))
#define LSB_ADDR_BYTE(addr)   ((uint8_t)(addr & ADDR_LSB_MASK))
    
// Count masks
#define RW_COUNT_MSB_MASK   (uint32_t)0xFF000000
#define RW_COUNT_MSB2_MASK   (uint32_t)0x00FF0000
#define RW_COUNT_LSB2_MASK   (uint32_t)0x0000FF00
#define RW_COUNT_LSB_MASK   (uint32_t)0x000000FF
#define MSB_RW_COUNT_BYTE(count)    ((uint8_t)((count & RW_COUNT_MSB_MASK)>>24))
#define MSB2_RW_COUNT_BYTE(count)   ((uint8_t)((count & RW_COUNT_MSB2_MASK)>>16))
#define LSB2_RW_COUNT_BYTE(count)   ((uint8_t)((count & RW_COUNT_LSB2_MASK)>>8))
#define LSB_RW_COUNT_BYTE(count)    ((uint8_t)(count & RW_COUNT_LSB_MASK))
    
#define NULL_PTR         ((uint8_t*) 0u)

#define FRAM_CHIP_SELECT_ENABLE() FRAM_CSOff()
#define FRAM_CHIP_SELECT_DISABLE() FRAM_CSOn()
    
#define NUMBER_OF_STORAGE_LOCATIONS         (0x8000)
#define LAST_STORAGE_LOCATION               (0x7FFF)
// Example F-RAM Address
#define FIRST_CONFIG_DATA_ADDR              (0x0130)
// RW Count F-RAM Address
#define FIRST_RW_COUNT_ADDR                 (0x012C)
// Config Data F-RAM Address
#define STORAGE_ADDR                        (0x0000)
// Number of Read/Writes before updating storage address
#define MAX_RW_COUNT                        (0x0000000F)
// Number of Read/Writes before updating storage address
#define ROW_BYTE_COUNT                        (0x08)
    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    typedef enum
    {
        CONFIG_DATA_FOUND,
                
        CONFIG_DATA_CORRUPTED,                
                
        NO_CONFIG_DATA_STORAGE_ADDRESS,
                
        CONFIG_DATA_LOADED_FROM_DEFAULT,
                
        ERROR,
    }CONFIG_DATA_RESULT;
    
    typedef union
    {
        /* Byte-wise access */
        uint8_t byte;

        /* This structure allows bitwise access of the response */
        struct
        {
            /* Unused bit 0 */
            unsigned unusedB0:1;

            /* Write Enable Latch */
            unsigned wel:1;

            /* Block Protect Enable Bit0 */
            unsigned bp0:1;

            /* Block Protect Enable Bit1 */
            unsigned bp1:1;

            /* Unused bit 4 */
            unsigned unusedB4:1;
            
            /* Unused bit 5 */
            unsigned unusedB5:1;
            
            /* Unused bit 6 */
            unsigned unusedB6:1;
            
            /* Write Protect Bet*/
            unsigned wpen:1;
        };

    } FRAM_STATUS_REG_RESP;

    typedef struct
    {
        /* Flag to indicate that the driver object is in use  */
        bool                            inUse;
        
        /* Write protect state */
        uint8_t                         isWriteProtected;
        
        /* Pointer to the buffer used during sending commands and receiving responses
        on the SPI bus */
        uint8_t                        *pCmdResp;
        
        /* Pointer to the buffer used to send dummy clock pulses on the SPI bus */
        uint8_t                        *pClkPulseData;
        
        /* Pointer to the CSD data of the SD Card */
        uint8_t                        *pCsdData;

        /* Index of the SPI driver */
        SYS_MODULE_INDEX                spiIndex;

        /* SPI client handle */
        DRV_HANDLE                      spiClientHandle;

        /* This is needed t keep track of the transfers */
        DRV_SPI_BUFFER_HANDLE           spiBufferHandle;

        DRV_SPI_CLIENT_DATA             spiClientData;

        /* Hold transfer pin setting */
        PORTS_CHANNEL                   transferHoldPort;

        /* Position of the bit in the port selected for Hold Transfer */
        PORTS_BIT_POS                   transferHoldBitPosition;

        /* Write protect pin setting */
        PORTS_CHANNEL                   writeProtectPort;

        /* Position of the bit in the port selected for Write protection */
        PORTS_BIT_POS                   writeProtectBitPosition;

        /* Chip select pin setting */
        PORTS_CHANNEL                   chipSelectPort;

        /* Position of the bit in the port selected for chip selection */
        PORTS_BIT_POS                   chipSelectBitPosition;
        
        FRAM_STATUS_REG_RESP            statusRegister;

        } DRV_FRAM_OBJ;
        
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Precondition
        List and describe any required preconditions. If there are no preconditions,
        enter "None."

      @Parameters
        @param param1 Describe the first parameter to the function.
    
        @param param2 Describe the second parameter to the function.

      @Returns
        List (if feasible) and describe the return values of the function.
        <ul>
          <li>1   Indicates an error occurred
          <li>0   Indicates an error did not occur
        </ul>

      @Remarks
        Describe any special behavior not described above.
        <p>
        Any additional remarks.

      @Example
        @code
        if(ExampleFunctionName(1, 2) == 0)
        {
            return 3;
        }
     */
// API decaration
void FRAM_Save_Configuration_Data();
void FRAM_Get_Config_Data();

// API decaration
uint16_t FRAM_Get_Storage_Address();

// API decaration
uint32_t FRAM_Get_RW_Count();

// SPI F-RAM Initialization
CONFIG_DATA_RESULT  FRAM_SPI_Init  ( DRV_HANDLE , SPI_MODULE_ID  );

// F-RAM Write function
void  FRAM_SPI_Write ( uint32_t , uint8_t );

// F-RAM read function
uint8_t  FRAM_SPI_Read  ( uint32_t );

// F-RAM BurstWrite function
void  FRAM_SPI_BurstWrite ( uint32_t , uint8_t * , uint32_t );

// F-RAM BurstRead function
void  FRAM_SPI_BurstRead  ( uint32_t , uint8_t * , uint32_t );

// Status register write function
void  FRAM_SPI_Status_Reg_Write( FRAM_STATUS_REG_RESP  );

// Status register read function
FRAM_STATUS_REG_RESP  FRAM_SPI_Status_Reg_Read ( void   );

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
