/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "HwConfig.h"
#include "SPI_FRAM.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
  bool saveConfigRequired = false;
  bool getConfigRequired = false;
  uint8_t data_bytes[BUFFER_SIZE];
  uint8_t fram_rd_data[BUFFER_SIZE];
  uint8_t fram_rd_byte;
  uint8_t status_reg = 0;
  uint8_t result;
  bool moduleInitSuccess = false;
  bool moduleBurstWriteReadSuccess = false;
  bool moduleStatusRegWriteReadSuccess = false;
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/
APP_DATA appData;

// EMWIN USER START (Mandatory add screens here)

EMWIN_GUI_SCREEN_CREATE emWinScreenCreate[ EMWIN_GUI_NUM_SCREENS ]
                                         = { CreateHomePage,
                                             CreateConfigurationSettings,
                                             CreateConfigurationUpdate };

// EMWIN USER END

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
 
#define GetSystemClock() (200000000UL)/* Fcy = 80MHz */
#define us_SCALE   (GetSystemClock()/2000000)
#define ms_SCALE   (GetSystemClock()/2000)

static uint32_t ReadCoreTimer(void);
//static uint16_t lastAddr = 0;
//static uint32_t lastCount = 0;
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


void APP_ScreenInitialize ( void )
{   
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************
void setupFRAM()
{  
    CONFIG_DATA_RESULT res;
    appData.drvSPIindex0Handle = DRV_SPI_Open( DRV_SPI_INDEX_0, DRV_IO_INTENT_WRITE );            
    if( DRV_HANDLE_INVALID != appData.drvSPIindex0Handle )
    {
        res = FRAM_SPI_Init( appData.drvSPIindex0Handle, DRV_SPI_SPI_ID_IDX0 );
        if(res == ERROR)
            res = FRAM_SPI_Init( appData.drvSPIindex0Handle, DRV_SPI_SPI_ID_IDX0 );
    }
        
}

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    int32_t screenCount = 0;
    
    CFG_Initialize();
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    // EMWIN USER START (Mandatory)
    
    setupFRAM();
    /* Register Screen Initialization */
    emWin_GuiScreenInitializeRegister( APP_ScreenInitialize );
            
    /* Register Screens */
    for( screenCount = 0; screenCount < EMWIN_GUI_NUM_SCREENS; screenCount++ )
    {
        emWin_GuiScreenRegister( screenCount, emWinScreenCreate[screenCount]);
    }
    
    /* set the start screen */
    emWin_GuiStartScreenSet( EMWIN_APP_SCREEN_HOME_PAGE );
    
// EMWIN USER END
    
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
       
            if(appInitialized)
                appData.state = APP_STATE_SERVICE_TASKS;
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            if(saveConfigRequired)
            {
                FRAM_Save_Configuration_Data();
                saveConfigRequired = false;    
            }
            if(getConfigRequired)
            {
                FRAM_Get_Config_Data();
                getConfigRequired = false;
            }
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
