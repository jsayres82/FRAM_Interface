/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "system_config.h"
#include "system_definitions.h"
#include "HwConfig.h"
#include "SPI_FRAM.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_BUTTON_0   (GUI_ID_USER + 0x01)
#define ID_DROPDOWN_0   (GUI_ID_USER + 0x02)
#define ID_EDIT_0   (GUI_ID_USER + 0x03)
#define ID_TEXT_0   (GUI_ID_USER + 0x04)
#define ID_BUTTON_1   (GUI_ID_USER + 0x05)
#define ID_TEXT_1   (GUI_ID_USER + 0x06)
#define ID_TEXT_2   (GUI_ID_USER + 0x07)
#define ID_TEXT_3   (GUI_ID_USER + 0x08)
#define ID_TEXT_4   (GUI_ID_USER + 0x09)
#define ID_RADIO_0   (GUI_ID_USER + 0x0A)
#define ID_SPINBOX_0   (GUI_ID_USER + 0x0B)
#define ID_RADIO_1   (GUI_ID_USER + 0x0C)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
void reverse(char *x, int begin, int end);
char* strrev(char*);
  uint32_t address;
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "ConfigurationUpdate", ID_FRAMEWIN_0, 0, 0, 480, 272, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "TABack", ID_BUTTON_0, 396, 189, 60, 43, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "configItemsDropdown", ID_DROPDOWN_0, 84, 58, 300, 25, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 89, 88, 293, 29, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 158, 31, 153, 20, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "updateItemValueButton", ID_BUTTON_1, 163, 133, 140, 35, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "rwCountText", ID_TEXT_1, 219, 215, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 13, 215, 167, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 12, 190, 190, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 222, 190, 80, 20, 0, 0x64, 0 },
  { RADIO_CreateIndirect, "booleanRadio", ID_RADIO_0, 202, 86, 80, 39, 0, 0x1402, 0 },
  { SPINBOX_CreateIndirect, "numberSpinbox", ID_SPINBOX_0, 119, 88, 240, 38, 0, 0x0, 0 },
  { RADIO_CreateIndirect, "Radio", ID_RADIO_1, 204, 86, 80, 44, 0, 0x1402, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  static uint16_t selectedItem = 0;
  char tempBuffer[100];
  static WM_HWIN lastWinItem;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'ConfigurationUpdate'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetFont(hItem, GUI_FONT_20_ASCII);
    FRAMEWIN_SetText(hItem, "Configuration Settings Update");
    //
    // Initialization of 'TABack'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Home");
    BUTTON_SetFont(hItem, GUI_FONT_13B_1);
    //
    // Initialization of 'configItemsDropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    DROPDOWN_SetListHeight(hItem, 100);
    DROPDOWN_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "Value");
    EDIT_SetFont(hItem, GUI_FONT_20_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    TEXT_SetText(hItem, "Configuration Item:");
    //
    // Initialization of 'updateItemValueButton'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_20_ASCII);
    BUTTON_SetText(hItem, "Submit Change");
    //
    // Initialization of 'rwCountText'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    TEXT_SetText(hItem, "0");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_20B_ASCII);
    TEXT_SetText(hItem, "Read/Write Count");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_20B_ASCII);
    TEXT_SetText(hItem, "Config Data Address");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    TEXT_SetText(hItem, "0x0000");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'booleanRadio'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
    RADIO_SetText(hItem, "True", 0);
    RADIO_SetText(hItem, "False", 1);
    RADIO_SetFont(hItem, GUI_FONT_20_ASCII);
    //
    // Initialization of 'numberSpinbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
    SPINBOX_SetFont(hItem, GUI_FONT_20_ASCII);
    //
    // Initialization of 'Radio'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_1);
    RADIO_SetText(hItem, "Single", 0);
    RADIO_SetText(hItem, "Dual", 1);
    RADIO_SetFont(hItem, GUI_FONT_20_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
    uint8_t i;    
        
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    sprintf(tempBuffer, "0x%04X", rwCountAddr);
    TEXT_SetText(hItem, tempBuffer);
    memset(tempBuffer, 0, 100);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    sprintf(tempBuffer, "%02u / %u", rwCycles, MAX_RW_COUNT);
    TEXT_SetText(hItem, tempBuffer);
    memset(tempBuffer, 0, 100);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_1);
    WM_HideWindow(hItem);
        
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
    WM_HideWindow(hItem);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
    WM_HideWindow(hItem);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);    
    WM_HideWindow(hItem);
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    for(i = 0; i < CONFIG_ITEM_COUNT; i++)
        DROPDOWN_AddString(hItem, configItemsStrings[i]);
    DROPDOWN_SetAutoScroll(hItem, 1);
    DROPDOWN_SetScrollbarWidth(hItem, 30);
    
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
    if(configDataPtr->calibrationEnabled) 
        RADIO_SetValue(hItem, 0);
    else
        RADIO_SetValue(hItem, 1);
    WM_ShowWindow(hItem);
    
       
    lastWinItem = hItem;
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'TABack'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
          emWin_GuiScreenChange(EMWIN_APP_SCREEN_HOME_PAGE);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_DROPDOWN_0: // Notifications sent by 'configItemsDropdown'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
          hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
          selectedItem = DROPDOWN_GetSel(hItem);
          WM_HideWindow(lastWinItem);
          if(selectedItem <= LAST_BOOL_CONFIG_ITEM_INDEX)
          {
              hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
              WM_ShowWindow(hItem);
              
              address = (uint32_t)(&configData.calibrationEnabled + selectedItem);
              if(*(&configData.calibrationEnabled + selectedItem) == false)
                  RADIO_SetValue(hItem, 1);
              else
                  RADIO_SetValue(hItem, 0);
          }else if(selectedItem <= LAST_UINT8_CONFIG_ITEM_INDEX)
          {
              hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
              WM_ShowWindow(hItem);
    
              SPINBOX_SetRange(hItem, 0, 255);
              address = *(&configData.showBatteryReadiness + selectedItem - 1 - LAST_BOOL_CONFIG_ITEM_INDEX);
              
              sprintf(tempBuffer, "%u", address);
              SPINBOX_SetValue(hItem, address);
          }else if(selectedItem <= LAST_UINT16_CONFIG_ITEM_INDEX)
          {
              hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
              WM_ShowWindow(hItem);
              SPINBOX_SetRange(hItem, 0, 65535);
              address = *(&configData.qcountMinimum + ((selectedItem - 1 - LAST_UINT8_CONFIG_ITEM_INDEX)));
              sprintf(tempBuffer, "%u", address);
              SPINBOX_SetValue(hItem, address);
          }else if(selectedItem <= LAST_INT16_CONFIG_ITEM_INDEX)
          {        
              hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
              WM_ShowWindow(hItem);
               
              SPINBOX_SetRange(hItem, -32768, 32767);
              address = *(&configData.primaryPressureCalibrationValue + ((selectedItem - 1 - LAST_UINT16_CONFIG_ITEM_INDEX)));
              sprintf(tempBuffer, "%i", address);
              SPINBOX_SetValue(hItem, address);
          }else if(selectedItem <= LAST_UINT32_CONFIG_ITEM_INDEX)
          {             
              hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
              WM_ShowWindow(hItem);
              
              SPINBOX_SetRange(hItem, 0, 429496729);
              address = *(&configData.idCode + ((selectedItem - 1 -LAST_INT16_CONFIG_ITEM_INDEX)));
              sprintf(tempBuffer, "%u", address);
              SPINBOX_SetValue(hItem, address);
          }else if(selectedItem <= LAST_ENUM_CONFIG_ITEM_INDEX)
          {
              hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_1);
              WM_ShowWindow(hItem);
              
              if(configDataPtr->pipeConfiguration == CFG_EOT_TYPE_SINGLE_PIPE)
                  RADIO_SetValue(hItem, 0);
              else
                  RADIO_SetValue(hItem, 1);
          }
          else //selectedItem <= LAST_STRING_CONFIG_ITEM_INDEX
          {
              hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);   
              WM_ShowWindow(hItem);
    
              sprintf(tempBuffer, configDataCharArrays[selectedItem - LAST_ENUM_CONFIG_ITEM_INDEX - 1]);              
              hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);          
              EDIT_SetText(hItem, tempBuffer);
          }
          
          lastWinItem = hItem;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'updateItemValueButton'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
          
        if(selectedItem <= LAST_BOOL_CONFIG_ITEM_INDEX)
        {
            address = (uint32_t)(&configData.calibrationEnabled + selectedItem);
            if(RADIO_GetValue(lastWinItem) == 0)
                *(&configData.calibrationEnabled + selectedItem) = true;          
            else
                *(&configData.calibrationEnabled + selectedItem) = false;                
        }else if(selectedItem <= LAST_UINT8_CONFIG_ITEM_INDEX)
        {            
            address = *(&configData.showBatteryReadiness + selectedItem - 1 - LAST_BOOL_CONFIG_ITEM_INDEX);
            *(&configData.showBatteryReadiness + selectedItem - 1 - LAST_BOOL_CONFIG_ITEM_INDEX) = (uint8_t)SPINBOX_GetValue(lastWinItem);
        }else if(selectedItem <= LAST_UINT16_CONFIG_ITEM_INDEX)
        {
            address = *(&configData.qcountMinimum + ((selectedItem - 1 - LAST_UINT8_CONFIG_ITEM_INDEX)));
            *(&configData.qcountMinimum + ((selectedItem - 1 - LAST_UINT8_CONFIG_ITEM_INDEX))) = (uint16_t)SPINBOX_GetValue(lastWinItem);
        }else if(selectedItem <= LAST_INT16_CONFIG_ITEM_INDEX)
        {                   
            address = *(&configData.primaryPressureCalibrationValue + ((selectedItem - 1 - LAST_UINT16_CONFIG_ITEM_INDEX)));
            *(&configData.primaryPressureCalibrationValue + ((selectedItem - 1 - LAST_UINT16_CONFIG_ITEM_INDEX))) = (int16_t)SPINBOX_GetValue(lastWinItem);
        }else if(selectedItem <= LAST_UINT32_CONFIG_ITEM_INDEX)
        {              
            address = *(&configData.idCode + ((selectedItem - 1 -LAST_INT16_CONFIG_ITEM_INDEX)));
            *(&configData.idCode + ((selectedItem - 1 -LAST_INT16_CONFIG_ITEM_INDEX))) = (uint32_t)SPINBOX_GetValue(lastWinItem);
        }else if(selectedItem <= LAST_ENUM_CONFIG_ITEM_INDEX)
        {
            if(RADIO_GetValue(lastWinItem) == 0)
                configDataPtr->pipeConfiguration = CFG_EOT_TYPE_SINGLE_PIPE;
            else
                configDataPtr->pipeConfiguration = CFG_EOT_TYPE_DUAL_PIPE;
                
        }
        else //selectedItem <= LAST_STRING_CONFIG_ITEM_INDEX
        {
            sprintf(tempBuffer, strrev(configDataCharArrays[selectedItem - LAST_ENUM_CONFIG_ITEM_INDEX - 1]));
            sprintf(configDataCharArrays[selectedItem - LAST_ENUM_CONFIG_ITEM_INDEX - 1],  tempBuffer);  
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
            EDIT_SetText(hItem, configDataCharArrays[selectedItem - LAST_ENUM_CONFIG_ITEM_INDEX - 1]);
    
        }
        saveConfigRequired = true;
          
        uint8_t i;
        char tempBuffer[200];
        hItem = WM_GetDialogItem(emWin_GuiScreenGet(EMWIN_APP_SCREEN_NUMBER_CHURNING), 0x803);
        for(i = 0; i < CONFIG_ITEM_COUNT; i++)
        {
            LISTVIEW_SetItemText(hItem, 0, i, configItemsStrings[i]);
            if(i <= LAST_BOOL_CONFIG_ITEM_INDEX)
            {
                address = (uint32_t)(&configData.calibrationEnabled + i);
                if(*(&configData.calibrationEnabled + i) == false)
                    sprintf(tempBuffer, "False");
                else
                    sprintf(tempBuffer, "True");
            }else if(i <= LAST_UINT8_CONFIG_ITEM_INDEX)
            {
                address = *(&configData.showBatteryReadiness + i - 1 - LAST_BOOL_CONFIG_ITEM_INDEX);
                sprintf(tempBuffer, "%u", address);
            }else if(i <= LAST_UINT16_CONFIG_ITEM_INDEX)
            {
                address = *(&configData.qcountMinimum + ((i - 1 - LAST_UINT8_CONFIG_ITEM_INDEX)));
                sprintf(tempBuffer, "%u", address);
            }else if(i <= LAST_INT16_CONFIG_ITEM_INDEX)
            {                   
                address = *(&configData.primaryPressureCalibrationValue + ((i - 1 - LAST_UINT16_CONFIG_ITEM_INDEX)));
                sprintf(tempBuffer, "%i", address);
            }else if(i <= LAST_UINT32_CONFIG_ITEM_INDEX)
            {              
                address = *(&configData.idCode + ((i - 1 -LAST_INT16_CONFIG_ITEM_INDEX)));
                sprintf(tempBuffer, "%u", address);
            }else if(i <= LAST_ENUM_CONFIG_ITEM_INDEX)
            {
                if(configDataPtr->pipeConfiguration == CFG_EOT_TYPE_SINGLE_PIPE)
                    sprintf(tempBuffer, "SINGLE PIPE");
                else
                    sprintf(tempBuffer, "DUAL PIPE");
            }
            else //selectedItem <= LAST_STRING_CONFIG_ITEM_INDEX
            {
                sprintf(tempBuffer, configDataCharArrays[i - LAST_ENUM_CONFIG_ITEM_INDEX - 1]);   
            }
            LISTVIEW_SetItemText(hItem, 1, i, tempBuffer);
            if( i < CONFIG_ITEM_COUNT - 1)
                LISTVIEW_AddRow(hItem, NULL);
        }
        LISTVIEW_SetAutoScrollV(hItem, 1);
        
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_RADIO_0: // Notifications sent by 'booleanRadio'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SPINBOX_0: // Notifications sent by 'numberSpinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_RADIO_1: // Notifications sent by 'Radio'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateConfigurationUpdate
*/
WM_HWIN CreateConfigurationUpdate(void);
WM_HWIN CreateConfigurationUpdate(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
void reverse(char *x, int begin, int end)
{
   char c;
 
   if (begin >= end)
      return;
 
   c          = *(x+begin);
   *(x+begin) = *(x+end);
   *(x+end)   = c;
 
   reverse(x, ++begin, --end);
}

char* strrev(char* inString)
{
   reverse(inString, 0, strlen(inString)-1);
   return inString;
}
// USER END

/*************************** End of file ****************************/