/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    HwConfig.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "HwConfig.h"
//#include "SDCard.h"
//#include "Charger.h"

CONFIG_DATA configData;

CONFIG_DATA * configDataPtr = &configData;
char * configDataCharArrays[] = {
    configData.fwVersion,
    configData.bootloaderVersion,
    configData.rrId,
    configData.batteryReadinessTextYes,
    configData.batteryReadinessTextNo,
    configData.calibrationDate,
    configData.batteryReplacementDate,
    configData.modelNumber,
    configData.boardSerialNumber,
    configData.calibrationTechnician,
    configData.calibrationLocation,
    configData.batteryReplacementTechnician,
    configData.batteryReplacementLocation,
    configData.wifiPassword    
};
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
int global_data;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
void CFG_Initialize()
{
    
    CFG_SetEotPipeConfiguration(CFG_EOT_TYPE_SINGLE_PIPE);
    CFG_SetEotID((uint32_t)EOT_DEFAULT_ID);
    CFG_SetEotEnabled(true);
    CFG_SetRRID(RR_ID);
    CFG_SetBoardSerialNumber(DEFAULT_BOARD_SERIAL_NUMBER);
    CFG_SetModelNumber(DEFAULT_MODEL_NUMBER);
    CFG_SetFwVersion(FW_VERSION);
    CFG_SetBootloaderVersion();
    CFG_SetGnssTimeoutPeriod(GNSS_TIMEOUT_PERIOD);
    CFG_SetSocUpdatePeriod(CHARGER_SOC_UPDATE_PERIOD);
//    CFG_SetCallSpacingWakeTimeInMinutes(3);
//    CFG_SetCallSpacingSleepTimeInMinutes(1);
    CFG_SetCallSpacingWakeTimeInMinutes(CALL_SPACING_WAKE_IN_MIN);
    CFG_SetCallSpacingSleepTimeInMinutes(CALL_SPACING_SLEEP_IN_MIN);
    CFG_SetShowBatteryReadiness(ALPHA_SHOW_BATTERY_READINESS);
    CFG_SetBatteryReadinessTextYes(ALPHA_BATTERY_READINESS_TEXT_YES);
    CFG_SetBatteryReadinessTextNo(ALPHA_BATTERY_READINESS_TEXT_NO);
    CFG_SetCalibrationDate(DEFAULT_CALIBRATION_DATE);
    CFG_SetCalibrationTechnician(DEFAULT_CALIBRATION_TECHNICIAN);
    CFG_SetCalibrationLocation(DEFAULT_CALIBRATION_LOCATION);
    CFG_SetCalibrationEnabled(DEFAULT_CALIBRATION_ENABLED);
    CFG_SetBatteryReplacementDate(DEFAULT_BATTERY_REPLACEMENT_DATE);
    CFG_SetBatteryReplacementTechnician(DEFAULT_BATTERY_REPLACEMENT_TECHNICIAN);
    CFG_SetBatteryReplacementLocation(DEFAULT_BATTERY_REPLACEMENT_LOCATION);
    CFG_SetWifiPassword(DEFAULT_WIFI_PASSWORD);
    CFG_SetWifiEnabled(DEFAULT_WIFI_ENABLED);
    CFG_SetBatteryReadyThreshold(CHARGER_BATTERY_READY_THRESHOLD);
    CFG_SetDisplayOffTimeoutAfterMotion(EOT_DISPLAY_TIMEOUT_AFTER_MOTION_IN_SEC); 
    CFG_SetDisplayOffTimeout(EOT_DISPLAY_TIMEOUT_IN_SEC); 
//    CFG_SetDisplayOffTimeout(20); // use for debugging - fast blanking
    CFG_SetPrimaryPressureCalibrationValue(ADC_PRESSURE_COUNT_FOR_90);
    CFG_SetSecondaryPressureCalibrationValue(ADC_PRESSURE_COUNT_FOR_90);
    CFG_SetGnssRefreshTime(EOT_GNSS_REFRESH_TIME);
    CFG_SetGeneratorOvervoltageTimeout(EOT_GENERATOR_OVERVOLTAGE_TIMEOUT_SEC);
    CFG_SetGeneratorReenableTimeout(EOT_GENERATOR_REENABLE_TIMEOUT_SEC);
    CFG_SetGnssFixTimeout(GNSS_FIX_TIMEOUT);
    CFG_SetCellPowerupTimeout(CELL_POWERUP_TIMEOUT);
    CFG_SetContextActivationFailedTimeout(CELL_CONTEXT_ACTIVATION_FAILED_TIMEOUT);
    CFG_SetConnectToSlotFailedTimeout(CELL_CONNECT_TO_SLOT_FAILED_TIMEOUT);
    CFG_SetDaylightSensorCalibrationLightToDark(DLS_LIGHT_TO_DARK_THRESHOLD);
    CFG_SetDaylightSensorCalibrationDarkToLight(DLS_DARK_TO_LIGHT_THRESHOLD);
    CFG_SetGeneratorExists(DEFAULT_GENERATOR_EXISTS);
    CFG_SetGeneratorValveExists(DEFAULT_GENERATOR_VALVE_EXISTS);
    CFG_SetHvmExists(DEFAULT_HVM_EXISTS);
            
    // Use these values if no values exist
    float currentBatteryCapacity = ((float)CHARGER_DEFAULT_BATTERY_CHARGE * (float)CHARGER_DEFAULT_BATTERY_CAPACITY / 100.0); // (40.0 * 4500.0 / 100.0) = 1800
    configData.qcountMaximum = (uint32_t)(((float)CHARGER_DEFAULT_BATTERY_CAPACITY - currentBatteryCapacity)/(float)CHARGER_CAPACITY_PER_COUNT) + CHARGER_INITIAL_QCOUNT;  // ((4500 - 1800)/1.0667)+32768=35299 counts
    configData.qcountMinimum = (uint32_t)(CHARGER_INITIAL_QCOUNT - (uint32_t)(currentBatteryCapacity/(float)CHARGER_CAPACITY_PER_COUNT));  // (32768 - (1800/1.0667))=31081 counts





}
//
//SYS_FS_RESULT CFG_StoreConfig()
//{
//    char buffer[100];
//    
//    SYS_FS_RESULT result;
//    SYS_FS_HANDLE fileHandle;
//    float vbat = CHARGER_GetVbat();
//    SYS_PRINT("CFG_StoreConfig() vbat=%f", vbat);
//    
//    // Check that battery voltage is high enough to write to SD card
////    if(vbat > SDCARD_VBAT_LOCKOUT_VOLTAGE)
//        if(1)
//    {
//        SYS_PRINT("CFG_StoreConfig()\n\r");
//        fileHandle = SYS_FS_FileOpen("/mnt/myDrive/EotConfig.txt", (SYS_FS_FILE_OPEN_WRITE_PLUS));
//
//        if(fileHandle != SYS_FS_HANDLE_INVALID)
//        {
//            // File open is successful
//            result = SYS_FS_FileSeek(fileHandle, 0, SYS_FS_SEEK_SET);
//            result = SYS_FS_FileTruncate(fileHandle);
//
//            sprintf(buffer, "EOT_ID=%u\n\r", configData.idCode);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            if(configData.eotEnabled)
//            {
//                sprintf(buffer, "EOT_ENABLED=TRUE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            else
//            {
//                sprintf(buffer, "EOT_ENABLED=FALSE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "RR_ID=%s\n\r", configData.rrId);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "BOARD_SN=%s\n\r", configData.boardSerialNumber);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "MODEL_NUMBER=%s\n\r", configData.modelNumber);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "PIPE_CONFIG=%u\n\r", (uint16_t)configData.pipeConfiguration);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "SOC_UPDATE_PERIOD=%u\n\r", configData.socUpdatePeriod);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
////            sprintf(buffer, "BRAKING_EXT_TIME=%u\n\r", configData.eotBrakingExtensionTime);
////SYS_PRINT("%s", buffer);        
////            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "GNSS_TIMEOUT_PERIOD=%u\n\r", configData.gnssTimeoutPeriod);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "CALL_SPACING_WAKE_PERIOD=%u\n\r", CFG_GetCallSpacingWakeTimeInMinutes());
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "CALL_SPACING_SLEEP_PERIOD=%u\n\r", CFG_GetCallSpacingSleepTimeInMinutes());
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "SHOW_BATTERY_READINESS=%u\n\r", configData.showBatteryReadiness);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "BATTERY_READINESS_TEXT_YES=%s\n\r", configData.batteryReadinessTextYes);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "BATTERY_READINESS_TEXT_NO=%s\n\r", configData.batteryReadinessTextNo);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "CALIBRATION_DATE=%s\n\r", configData.calibrationDate);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            if(configData.calibrationEnabled)
//            {
//                sprintf(buffer, "CALIBRATION_ENABLED=TRUE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            else
//            {
//                sprintf(buffer, "CALIBRATION_ENABLED=FALSE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "CALIBRATION_TECHNICIAN=%s\n\r", configData.calibrationTechnician);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "CALIBRATION_LOCATION=%s\n\r", configData.calibrationLocation);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "BATTERY_REPLACEMENT_DATE=%s\n\r", configData.batteryReplacementDate);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "BATTERY_REPLACEMENT_TECHNICIAN=%s\n\r", configData.batteryReplacementTechnician);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "BATTERY_REPLACEMENT_LOCATION=%s\n\r", configData.batteryReplacementLocation);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "WIFI_PASSWORD=%s\n\r", configData.wifiPassword);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            if(configData.wifiEnabled)
//            {
//                sprintf(buffer, "WIFI_ENABLED=TRUE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            else
//            {
//                sprintf(buffer, "WIFI_ENABLED=FALSE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            sprintf(buffer, "PRIMARY_PRESSURE_CAL_VALUE=%d\n\r", configData.primaryPressureCalibrationValue);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "SECONDARY_PRESSURE_CAL_VALUE=%d\n\r", configData.secondaryPressureCalibrationValue);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "DLS_CAL_LIGHT_TO_DARK=%d\n\r", configData.daylightSensorCalibrationLightToDark);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            sprintf(buffer, "DLS_CAL_DARK_TO_LIGHT=%d\n\r", configData.daylightSensorCalibrationDarkToLight);
//SYS_PRINT("%s", buffer);        
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//            
//            if(configData.generatorExists)
//            {
//                sprintf(buffer, "GENERATOR_EXISTS=TRUE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            else
//            {
//                sprintf(buffer, "GENERATOR_EXISTS=FALSE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            if(configData.generatorValveExists)
//            {
//                sprintf(buffer, "GENERATOR_VALVE_EXISTS=TRUE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            else
//            {
//                sprintf(buffer, "GENERATOR_VALVE_EXISTS=FALSE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            if(configData.hvmExists)
//            {
//                sprintf(buffer, "HVM_EXISTS=TRUE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            else
//            {
//                sprintf(buffer, "HVM_EXISTS=FALSE\n\r");
//SYS_PRINT("%s", buffer);        
//            }
//            result = SYS_FS_FileWrite(fileHandle, (const void *)buffer, strlen(buffer));
//
//            
//        }
//        result = SYS_FS_FileClose(fileHandle);
//    }
//    else
//    {
//        result = SYS_FS_RES_FAILURE;
//    }
//    return result;
//}
//
//SYS_FS_RESULT CFG_ReadConfig()
//{
//#define READ_CONFIG_BUFFER_SIZE 100
//    SYS_FS_RESULT result;
//    char parameterBuffer[READ_CONFIG_BUFFER_SIZE];
//    char valueBuffer[READ_CONFIG_BUFFER_SIZE];
//    char readBuffer[2];
//    uint16_t index = 0;
//    SYS_FS_HANDLE fileHandle;
//    SDCARDReadState_t readState = SDCARD_READ_STATE_PARAMETER;
//    
//    fileHandle = SYS_FS_FileOpen("/mnt/myDrive/EotConfig.txt", (SYS_FS_FILE_OPEN_READ_PLUS));
//
//    if(fileHandle != SYS_FS_HANDLE_INVALID)
//    {
//        // File open is successful
//        while(SYS_FS_FileRead(fileHandle, readBuffer, 1))
//        {
//            // Safety check to avoid overflowing the buffer.
//            if(index < READ_CONFIG_BUFFER_SIZE)
//            {
//                if(readBuffer[0]=='=')
//                {
//                    if(readState == SDCARD_READ_STATE_PARAMETER)
//                    {
//                        // Consider the '=' to be a delimeter between the parameter
//                        // and the value.  Characters read in after '=' are part of the value.
//                        readState = SDCARD_READ_STATE_VALUE;
//                        parameterBuffer[index] = '\0';
//                        index = 0;
//                    }
//                    else // if(readState == SDCARD_READ_STATE_VALUE)
//                    {
//                        // If a value was being read and '=' appears, consider
//                        // it to be part of the value and not a delimeter.
//                        valueBuffer[index++] = readBuffer[0];
//                    }
//                }
//                else if(readBuffer[0]=='\r')
//                {
//                    // End of line
//                    // Look for parameter
//                    readState = SDCARD_READ_STATE_PARAMETER;
//                    valueBuffer[index++] = '\0';
//                    index = 0;
//                    CFG_ParseConfig(parameterBuffer, valueBuffer);
//                }
//                else if(readBuffer[0]=='\n')
//                {
//                    // Ignore line feeds
//                    //index = 0;
//                }
//                else
//                {
//                    switch(readState)
//                    {
//                        case SDCARD_READ_STATE_PARAMETER:
//                            parameterBuffer[index++] = readBuffer[0];
//                            break;
//
//                        case SDCARD_READ_STATE_VALUE:
//                            valueBuffer[index++] = readBuffer[0];
//                            break;
//
//                        default:
//                            readState = SDCARD_READ_STATE_PARAMETER;
//                            index = 0;
//                            break;
//                    }
//                }
//            }
//        }
//    }
//    result = SYS_FS_FileClose(fileHandle);
//    return result;
//}

void CFG_ParseConfig(char* parameterBuffer, char* valueBuffer)
{
    uint16_t value;
    SYS_PRINT("*****READ %s=%s\n\r", parameterBuffer, valueBuffer);        

    if(strcmp(parameterBuffer, "EOT_ID") == 0)
    {
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);
        CFG_SetEotID(value);
    }
    else if(strcmp(parameterBuffer, "EOT_ENABLED") == 0)
    {
        if(strcmp(valueBuffer, "TRUE") == 0)
        {
            SYS_PRINT("EOT_ENABLED=TRUE\n\r");
            CFG_SetEotEnabled(true);
        }
        else
        {
            SYS_PRINT("EOT_ENABLED=FALSE\n\r");
            CFG_SetEotEnabled(false);
        }
    }
    else if(strcmp(parameterBuffer, "RR_ID") == 0)
    {
        CFG_SetRRID(valueBuffer);
//        strcpy(configData.rrId, valueBuffer);
    }
//    else if(strcmp(parameterBuffer, "FW_VERSION") == 0)
//    {
//        CFG_SetFwVersion(valueBuffer);
////        strcpy(configData.fwVersion, valueBuffer);
//    }
    else if(strcmp(parameterBuffer, "MODEL_NUMBER") == 0)
    {
        CFG_SetModelNumber(valueBuffer);
//        strcpy(configData.modelNumber, valueBuffer);
    }
    else if(strcmp(parameterBuffer, "BOARD_SN") == 0)
    {
        CFG_SetBoardSerialNumber(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "PIPE_CONFIG") == 0)
    {
        // Parse the current count
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);
        if(value == 2)
        {
            CFG_SetEotPipeConfiguration(CFG_EOT_TYPE_DUAL_PIPE);
        }
        else
        {
            CFG_SetEotPipeConfiguration(CFG_EOT_TYPE_SINGLE_PIPE);
        }
    }
    else if(strcmp(parameterBuffer, "SOC_UPDATE_PERIOD") == 0)
    {
        // Parse the current count
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);
        if(value > 0)
        {
            CFG_SetSocUpdatePeriod(value);
        }
    }
//    else if(strcmp(parameterBuffer, "BRAKING_EXT_TIME") == 0)
//    {
//        // Parse the current count
//        value = (uint16_t)atoi(valueBuffer);
//        SYS_PRINT("value=%u\n\r", value);
//        CFG_SetBrakingExtensionTime(value);
//    }
    else if(strcmp(parameterBuffer, "GNSS_TIMEOUT_PERIOD") == 0)
    {
        // Parse the current count
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);
        if(value > 0)
        {
            CFG_SetSocUpdatePeriod(value);
        }
    }
    else if(strcmp(parameterBuffer, "CALL_SPACING_WAKE_PERIOD") == 0)
    {
        // Parse the current count
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);

        if(value > 0)
        {
            CFG_SetCallSpacingWakeTimeInMinutes(value);
        }
    }
    else if(strcmp(parameterBuffer, "CALL_SPACING_SLEEP_PERIOD") == 0)
    {
        // Parse the current count
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);

        if(value > 0)
        {
            CFG_SetCallSpacingSleepTimeInMinutes(value);
        }
    }
    else if(strcmp(parameterBuffer, "SHOW_BATTERY_READINESS") == 0)
    {
        // Parse the current count
        value = (uint16_t)atoi(valueBuffer);
        SYS_PRINT("value=%u\n\r", value);
        if(value > 0)
        {
            CFG_SetShowBatteryReadiness(1);
        }
        else if(value == 0)
        {
            CFG_SetShowBatteryReadiness(0);
        }
    }
    else if(strcmp(parameterBuffer, "BATTERY_READINESS_TEXT_YES") == 0)
    {
        CFG_SetBatteryReadinessTextYes(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "BATTERY_READINESS_TEXT_NO") == 0)
    {
        CFG_SetBatteryReadinessTextNo(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "CALIBRATION_DATE") == 0)
    {
        CFG_SetCalibrationDate(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "CALIBRATION_ENABLED") == 0)
    {
        if(strcmp(valueBuffer, "TRUE") == 0)
        {
            SYS_PRINT("CALIBRATION_ENABLED=TRUE\n\r");
            CFG_SetCalibrationEnabled(true);
        }
        else
        {
            SYS_PRINT("CALIBRATION_ENABLED=FALSE\n\r");
            CFG_SetCalibrationEnabled(false);
        }
    }
    else if(strcmp(parameterBuffer, "CALIBRATION_TECHNICIAN") == 0)
    {
        CFG_SetCalibrationTechnician(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "CALIBRATION_LOCATION") == 0)
    {
        CFG_SetCalibrationLocation(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "BATTERY_REPLACEMENT_DATE") == 0)
    {
        CFG_SetBatteryReplacementDate(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "BATTERY_REPLACEMENT_TECHNICIAN") == 0)
    {
        CFG_SetBatteryReplacementTechnician(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "BATTERY_REPLACEMENT_LOCATION") == 0)
    {
        CFG_SetBatteryReplacementLocation(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "WIFI_PASSWORD") == 0)
    {
        CFG_SetWifiPassword(valueBuffer);
    }
    else if(strcmp(parameterBuffer, "WIFI_ENABLED") == 0)
    {
        if(strcmp(valueBuffer, "TRUE") == 0)
        {
            SYS_PRINT("WIFI_ENABLED=TRUE\n\r");
            CFG_SetWifiEnabled(true);
        }
        else
        {
            SYS_PRINT("WIFI_ENABLED=FALSE\n\r");
            CFG_SetWifiEnabled(false);
        }
    }
    else if(strcmp(parameterBuffer, "PRIMARY_PRESSURE_CAL_VALUE") == 0)
    {
        value = (uint16_t)atoi(valueBuffer);
        CFG_SetPrimaryPressureCalibrationValue(value);
    }
    else if(strcmp(parameterBuffer, "SECONDARY_PRESSURE_CAL_VALUE") == 0)
    {
        value = (uint16_t)atoi(valueBuffer);
        CFG_SetSecondaryPressureCalibrationValue(value);
    }
    else if(strcmp(parameterBuffer, "DLS_CAL_LIGHT_TO_DARK") == 0)
    {
        value = (uint16_t)atoi(valueBuffer);
        CFG_SetDaylightSensorCalibrationLightToDark(value);
    }
    else if(strcmp(parameterBuffer, "DLS_CAL_DARK_TO_LIGHT") == 0)
    {
        value = (uint16_t)atoi(valueBuffer);
        CFG_SetDaylightSensorCalibrationDarkToLight(value);
    }
    else if(strcmp(parameterBuffer, "GENERATOR_EXISTS") == 0)
    {
        if(strcmp(valueBuffer, "TRUE") == 0)
        {
            SYS_PRINT("GENERATOR_EXISTS=TRUE\n\r");
            CFG_SetGeneratorExists(true);
        }
        else
        {
            SYS_PRINT("GENERATOR_EXISTS=FALSE\n\r");
            CFG_SetGeneratorExists(false);
        }
    }
    else if(strcmp(parameterBuffer, "GENERATOR_VALVE_EXISTS") == 0)
    {
        if(strcmp(valueBuffer, "TRUE") == 0)
        {
            SYS_PRINT("GENERATOR_VALVE_EXISTS=TRUE\n\r");
            CFG_SetGeneratorValveExists(true);
        }
        else
        {
            SYS_PRINT("GENERATOR_VALVE_EXISTS=FALSE\n\r");
            CFG_SetGeneratorValveExists(false);
        }
    }
    else if(strcmp(parameterBuffer, "HVM_EXISTS") == 0)
    {
        if(strcmp(valueBuffer, "TRUE") == 0)
        {
            SYS_PRINT("HVM_EXISTS=TRUE\n\r");
            CFG_SetHvmExists(true);
        }
        else
        {
            SYS_PRINT("HVM_EXISTS=FALSE\n\r");
            CFG_SetHvmExists(false);
        }
    }
    else
    {
        Nop();
        SYS_PRINT("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ UNEXPECTED PARAMETER\n\r");
        SYS_PRINT("String=%s\n\r", parameterBuffer);
    }
}

uint16_t CFG_GetQcountMinimum()
{
    return (configData.qcountMinimum);
}

uint16_t CFG_GetQcountMaximum()
{
    return (configData.qcountMaximum);
}

void CFG_SetQcountMinimum(uint16_t value)
{
    configData.qcountMinimum = value;
}

void CFG_SetQcountMaximum(uint16_t value)
{
    configData.qcountMaximum = value;
}

void CFG_SetStoredQcount(uint16_t value)
{
    configData.storedQcount = value;
}

uint16_t CFG_GetStoredQcount()
{
    return configData.storedQcount;
}

// Returns the first 32-bits of the serial number unique to the CPU.
uint32_t CFG_GetId1()
{
    // Return DEVSN0
    return (*(uint32_t *)0xBFC54020);
}

// Returns the second 32-bits of the serial number unique to the CPU.
uint32_t CFG_GetId2()
{
    // Return DEVSN1
    return (*(uint32_t *)0xBFC54024);
}

uint32_t CFG_GetDevId()
{
    // Return DEVID
    return (*(uint32_t *)0xBF800020);
}

// *** Pipe Configuration ***
EotPipeConfigurationType_e CFG_GetEotPipeConfiguration()
{
    return(configData.pipeConfiguration);
}

void CFG_SetEotPipeConfiguration(EotPipeConfigurationType_e pipeConfiguration)
{
    configData.pipeConfiguration = pipeConfiguration;
}

// *** EOT ID ***
uint32_t CFG_GetEotID()
{
    return (configData.idCode);
}

void CFG_SetEotID(uint32_t idCode)
{
    configData.idCode = idCode;
}

// *** EOT Enabled ***
bool CFG_GetEotEnabled()
{
    return (configData.eotEnabled);
}

void CFG_SetEotEnabled(bool eotEnabled)
{
    configData.eotEnabled = eotEnabled;
}

// *** RR ID ***
void CFG_GetRRID(char* string)
{
    strcpy(string, configData.rrId);
}

void CFG_SetRRID(char* string)
{
    // Copy the string but limit the string to 8 characters
//    strncpy(configData.rrId, string, 8);
//    configData.rrId[8] = '\0';
    
//    char newString[10];
//    CFG_FormatStringForAlphaDisplay(string, newString);
//    strcpy(configData.rrId, newString);
    strcpy(configData.rrId, string);
}

// *** Board Serial Number ***
void CFG_GetBoardSerialNumber(char* string)
{
    strcpy(string, configData.boardSerialNumber);
}

void CFG_SetBoardSerialNumber(char* string)
{
    int i;
    char newString[BOARD_SERIAL_NUMBER_LENGTH+2];
    
    // Copy the first 10 characters and insert a NULL at the end
    strncpy(newString, string, BOARD_SERIAL_NUMBER_LENGTH);
    newString[BOARD_SERIAL_NUMBER_LENGTH] = '\0';
    
    // if there are any unprintable characters, replace them with spaces.
    for(i = 0; i < BOARD_SERIAL_NUMBER_LENGTH; i++)
    {
        if((newString[i] < ' ') || (newString[i] > '~'))
        {
            newString[i] = ' ';
        }
    }

    strcpy(configData.boardSerialNumber, newString);
}

// *** Model Number ***
void CFG_GetModelNumber(char* string)
{
    strcpy(string, configData.modelNumber);
}

void CFG_SetModelNumber(char* string)
{
    int i;
    char newString[20];
    
    // Copy the first 10 characters and insert a NULL at the end
    strncpy(newString, string, 10);
    newString[10] = '\0';
    
    // if there are any unprintable characters, replace them with spaces.
    for(i = 0; i < 10; i++)
    {
        if((newString[i] < ' ') || (newString[i] > '~'))
        {
            newString[i] = ' ';
        }
    }

    strcpy(configData.modelNumber, newString);
}

// *** FW Version ***
void CFG_GetFwVersion(char* string)
{
    strcpy(string, configData.fwVersion);
}

void CFG_SetFwVersion(char* string)
{
    // Copy the string but limit the string to 8 characters
//    strncpy(configData.fwVersion, string, 8);
//    configData.fwVersion[8] = '\0';
    
    char newString[10];
    CFG_FormatStringForAlphaDisplay(string, newString);
    strcpy(configData.fwVersion, newString);
}

// *** Bootloader Version ***
void CFG_GetBootloaderVersion(char* string)
{
    strcpy(string, configData.bootloaderVersion);
}

void CFG_SetBootloaderVersion()
{
    // Most other "set" functions take in a value and store the value.
    // This function gets the bootloader version from a known memory
    // location in flash.
    
    // If the bootloader is not in flash, the values at this memory
    // location could be garbage.  Copy bytes instead a string.
    char newString[BOOTLOADER_VERSION_STRING_MAX_LENGTH+2];
    int count = 0;
    bool done = false;
    char* ptr = (char*)BOOTLOADER_VERSION_LOCATION;
    while((count < BOOTLOADER_VERSION_STRING_MAX_LENGTH) && !done)
    {
        if(*ptr == '\0')
        {
            done = true;
        }
        newString[count++] = *ptr++;
    }
    
    // Ensure that the string is null terminated
    newString[BOOTLOADER_VERSION_STRING_MAX_LENGTH] = '\0';
    
    // Check for NULL version.
    if((newString[0] == '\0') || (newString[0] == (char)0xFF))
    {
        strcpy(configData.bootloaderVersion, "NONE");
    }
    else
    {
        // Copy the string into memory
        memcpy(configData.bootloaderVersion, newString, (BOOTLOADER_VERSION_STRING_MAX_LENGTH+2));
    }
}

// *** GNSS Timeout Check Period
uint16_t CFG_GetGnssTimeoutPeriod()
{
    return configData.gnssTimeoutPeriod;
}

void CFG_SetGnssTimeoutPeriod(uint16_t timeout)
{
    configData.gnssTimeoutPeriod = timeout;
}

// *** SOC (State of Charge) Update Period ***
uint16_t CFG_GetSocUpdatePeriod()
{
    return configData.socUpdatePeriod;
}

void CFG_SetSocUpdatePeriod(uint16_t time)
{
    configData.socUpdatePeriod = time;
}

uint16_t CFG_GetCallSpacingWakeTimeInMinutes()
{
    return configData.callSpacingWakeTimeInMinutes;
}

void CFG_SetCallSpacingWakeTimeInMinutes(uint16_t timeInMinutes)
{
    configData.callSpacingWakeTimeInMinutes = timeInMinutes;
}

// *** Call Spacing - SLEEP ***
uint32_t CFG_GetCallSpacingSleepTimeInSeconds()
{
    return configData.callSpacingSleepTimeInSeconds;
}

uint32_t CFG_GetCallSpacingSleepTimeInMinutes()
{
    uint32_t retVal;
    retVal = configData.callSpacingSleepTimeInSeconds / 60;
    return retVal;
}

void CFG_SetCallSpacingSleepTimeInMinutes(uint16_t timeInMinutes)
{
    // Convert time to seconds
    configData.callSpacingSleepTimeInSeconds = timeInMinutes * 60;
}

// *** Show Battery Readiness ***
uint8_t CFG_GetShowBatteryReadiness()
{
    return configData.showBatteryReadiness;
}

void CFG_SetShowBatteryReadiness(uint8_t value)
{
    configData.showBatteryReadiness = value;
}

// *** Battery Readiness Text ***
void CFG_GetBatteryReadinessTextYes(char* string)
{
    strcpy(string, configData.batteryReadinessTextYes);
}

void CFG_SetBatteryReadinessTextYes(char* string)
{
    // Copy the string but limit the string to 8 characters
//    strncpy(configData.batteryReadinessTextYes, string, 8);
//    configData.batteryReadinessTextYes[8] = '\0';
    
    char newString[10];
    CFG_FormatStringForAlphaDisplay(string, newString);
    strcpy(configData.batteryReadinessTextYes, newString);
}

void CFG_GetBatteryReadinessTextNo(char* string)
{
    strcpy(string, configData.batteryReadinessTextNo);
}

void CFG_SetBatteryReadinessTextNo(char* string)
{
    // Copy the string but limit the string to 8 characters
//    strncpy(configData.batteryReadinessTextNo, string, 8);
//    configData.batteryReadinessTextNo[8] = '\0';
    
    char newString[10];
    CFG_FormatStringForAlphaDisplay(string, newString);
    strcpy(configData.batteryReadinessTextNo, newString);
}

void CFG_GetCalibrationDate(char* string)
{
    strcpy(string, configData.calibrationDate);
}

void CFG_SetCalibrationDate(char* string)
{
    strcpy(configData.calibrationDate, string);
}

void CFG_GetCalibrationTechnician(char* string)
{
    strcpy(string, configData.calibrationTechnician);
}

void CFG_SetCalibrationTechnician(char* string)
{
    strcpy(configData.calibrationTechnician, string);
}

void CFG_GetCalibrationLocation(char* string)
{
    strcpy(string, configData.calibrationLocation);
}

void CFG_SetCalibrationLocation(char* string)
{
    strcpy(configData.calibrationLocation, string);
}

bool CFG_GetCalibrationEnabled()
{
    return configData.calibrationEnabled;
}

void CFG_SetCalibrationEnabled(bool calibrationEnabled)
{
    configData.calibrationEnabled = calibrationEnabled;
}

void CFG_GetBatteryReplacementDate(char* string)
{
    strcpy(string, configData.batteryReplacementDate);
}

void CFG_SetBatteryReplacementDate(char* string)
{
    strcpy(configData.batteryReplacementDate, string);
}

void CFG_GetBatteryReplacementTechnician(char* string)
{
    strcpy(string, configData.batteryReplacementTechnician);
}

void CFG_SetBatteryReplacementTechnician(char* string)
{
    strcpy(configData.batteryReplacementTechnician, string);
}

void CFG_GetBatteryReplacementLocation(char* string)
{
    strcpy(string, configData.batteryReplacementLocation);
}

void CFG_SetBatteryReplacementLocation(char* string)
{
    strcpy(configData.batteryReplacementLocation, string);
}

void CFG_GetWifiPassword(char* string)
{
    strcpy(string, configData.wifiPassword);
}

void CFG_SetWifiPassword(char* string)
{
    strcpy(configData.wifiPassword, string);
}

bool CFG_GetWifiEnabled()
{
    return configData.wifiEnabled;
}

void CFG_SetWifiEnabled(bool wifiEnabled)
{
    configData.wifiEnabled = wifiEnabled;
}

// *** Battery Ready Threshold ***
uint8_t CFG_GetBatteryReadyThreshold()
{
    return configData.batteryReadyThreshold;
}

void CFG_SetBatteryReadyThreshold(uint8_t value)
{
    configData.batteryReadyThreshold = value;
}

bool CFG_GetGeneratorExists()
{
    return configData.generatorExists;
}

void CFG_SetGeneratorExists(bool generatorExists)
{
    configData.generatorExists = generatorExists;
}

bool CFG_GetGeneratorValveExists()
{
    return configData.generatorValveExists;
}

void CFG_SetGeneratorValveExists(bool generatorValveExists)
{
    configData.generatorValveExists = generatorValveExists;
}

bool CFG_GetHvmExists()
{
    return configData.hvmExists;
}

void CFG_SetHvmExists(bool hvmExists)
{
    configData.hvmExists = hvmExists;
}







void CFG_FormatStringForAlphaDisplay(char* inputBuffer, char* outputBuffer)
{
    int outputBufferIndex = 0;
    int inputBufferIndex = 0;
    bool endOfStringFound = false;
    const int MAXIMUM_CHARS_TO_CHECK = 20;
    
    // The Alphanumeric display can support 8 characters so ensure that there
    // are 8 displayable characters in the output string.
    do
    {
        if(endOfStringFound == false)
        {
            if(inputBuffer[inputBufferIndex] == '\"')
            {
                // Ignore quote characters.  Increment the input index.
                inputBufferIndex++;
            }
            else if(inputBuffer[inputBufferIndex] == '\0')
            {
                // If the string in inputBuffer is shorter than 8 characters,
                // pad the string with spaces.
                outputBuffer[outputBufferIndex] = ' ';
                endOfStringFound = true;
                outputBufferIndex++;
                inputBufferIndex++;
            }
            else
            {
                outputBuffer[outputBufferIndex++] = inputBuffer[inputBufferIndex++];
            }
        }
        else // if(endOfStringFound == true
        {
            // If the string in inputBuffer is shorter than 8 characters,
            // pad the string with spaces.
            outputBuffer[outputBufferIndex] = ' ';
            outputBufferIndex++;
            inputBufferIndex++;
        }
    }while((outputBufferIndex < 8) && (inputBufferIndex < MAXIMUM_CHARS_TO_CHECK));
    
    // Insert a NULL at the end of the string to ensure that it is no longer
    // than 8 characters.
    outputBuffer[8] = '\0';
    
    // Copy the string from outputBuffer to inputBuffer
//    memcpy(inputBuffer, outputBuffer, 9);
}

uint32_t CFG_GetDisplayOffTimeoutAfterMotion()
{
    return configData.displayOffTimeoutAfterMotion;
}

void CFG_SetDisplayOffTimeoutAfterMotion(uint32_t displayOffTimeoutAfterMotion)
{
    configData.displayOffTimeoutAfterMotion = displayOffTimeoutAfterMotion;
}

uint32_t CFG_GetDisplayOffTimeout()
{
    return configData.displayOffTimeout;
}

void CFG_SetDisplayOffTimeout(uint32_t displayOffTimeout)
{
    configData.displayOffTimeout = displayOffTimeout;    
}

int16_t CFG_GetPrimaryPressureCalibrationValue()
{
    return configData.primaryPressureCalibrationValue;
}

void CFG_SetPrimaryPressureCalibrationValue(int16_t pressureCalibrationValue)
{
    configData.primaryPressureCalibrationValue = pressureCalibrationValue;
}

int16_t CFG_GetSecondaryPressureCalibrationValue()
{
    return configData.secondaryPressureCalibrationValue;
}

void CFG_SetSecondaryPressureCalibrationValue(int16_t pressureCalibrationValue)
{
    configData.secondaryPressureCalibrationValue = pressureCalibrationValue;
}

uint32_t CFG_GetGnssRefreshTime()
{
    return configData.gnssRefreshTime;
}

void CFG_SetGnssRefreshTime(uint32_t gnssRefreshTime)
{
    configData.gnssRefreshTime = gnssRefreshTime;
}

uint32_t CFG_GetGeneratorOvervoltageTimeout()
{
    return configData.generatorOvervoltageTimeout;
}

void CFG_SetGeneratorOvervoltageTimeout(uint32_t generatorOvervoltageTimeout)
{
    configData.generatorOvervoltageTimeout = generatorOvervoltageTimeout;
}

uint32_t CFG_GetGeneratorReenableTimeout()
{
    return configData.generatorReenableTimeout;
}

void CFG_SetGeneratorReenableTimeout(uint32_t generatorReenableTimeout)
{
    configData.generatorReenableTimeout = generatorReenableTimeout;
}

uint32_t CFG_GetGnssFixTimeout()
{
    return configData.gnssFixTimeout;
}

void CFG_SetGnssFixTimeout(uint32_t gnssFixTimeout)
{
    configData.gnssFixTimeout = gnssFixTimeout;
}

uint32_t CFG_GetCellPowerupTimeout()
{
    return configData.cellPowerupTimeout;
}

void CFG_SetCellPowerupTimeout(uint32_t cellPowerupTimeout)
{
    configData.cellPowerupTimeout = cellPowerupTimeout;
}

uint32_t CFG_GetContextActivationFailedTimeout()
{
    return configData.contextActivationFailedTimeout;
}

void CFG_SetContextActivationFailedTimeout(uint32_t contextActivationFailedTimeout)
{
    configData.contextActivationFailedTimeout = contextActivationFailedTimeout;
}

uint32_t CFG_GetConnectToSlotFailedTimeout()
{
    return configData.connectToSlotFailedTimeout;
}

void CFG_SetConnectToSlotFailedTimeout(uint32_t connectToSlotFailedTimeout)
{
    configData.connectToSlotFailedTimeout = connectToSlotFailedTimeout;
}

uint16_t CFG_GetDaylightSensorCalibrationLightToDark()
{
    return configData.daylightSensorCalibrationLightToDark;
}

void CFG_SetDaylightSensorCalibrationLightToDark(uint16_t daylightSensorCalibrationLightToDark)
{
    configData.daylightSensorCalibrationLightToDark = daylightSensorCalibrationLightToDark;
}

uint16_t CFG_GetDaylightSensorCalibrationDarkToLight()
{
    return configData.daylightSensorCalibrationDarkToLight;
}

void CFG_SetDaylightSensorCalibrationDarkToLight(uint16_t daylightSensorCalibrationDarkToLight)
{
    configData.daylightSensorCalibrationDarkToLight = daylightSensorCalibrationDarkToLight;
}

uint16_t CFG_GetChargeRateInMaPerHour()
{
    return CHARGER_CHARGE_RATE;
}

// Some strings such as the model number need to be padded so that
// there are no unprintable characters.  This function replaces
// unprintable characters with a space.
void CFG_PadString(char* string, int numberOfCharacters)
{
    int i;
    int length = strlen(string);
    
    if(length < numberOfCharacters)
    {
        for(i = length; i < numberOfCharacters; i++)
        {
            string[i] = ' ';
        }
    }
    
    // if there are any unprintable characters, replace them with spaces.
    for(i = 0; i < numberOfCharacters; i++)
    {
        if((string[i] < ' ') || (string[i] > '~'))
        {
            string[i] = ' ';
        }
    }
}


#if 0
void CFG_FormatStringForAlphaDisplay(char* valueBuffer)
{
    int tempBufferIndex = 0;
    int valueBufferIndex = 0;
    char tempBuffer[10];
    bool endOfStringFound = false;
    const int MAXIMUM_CHARS_TO_CHECK = 20;
    
    // The Alphanumeric display can support 8 characters so ensure that there
    // are 8 displayable characters in the output string.
    do
    {
        if(endOfStringFound == false)
        {
            if(valueBuffer[valueBufferIndex] == '\"')
            {
                // Ignore quote characters.  Increment the input index.
                valueBufferIndex++;
            }
            else if(valueBuffer[valueBufferIndex] == '\0')
            {
                // If the string in valueBuffer is shorter than 8 characters,
                // pad the string with spaces.
                tempBuffer[tempBufferIndex] = ' ';
                endOfStringFound = true;
                tempBufferIndex++;
                valueBufferIndex++;
            }
            else
            {
                tempBuffer[tempBufferIndex++] = valueBuffer[valueBufferIndex++];
            }
        }
        else // if(endOfStringFound == true
        {
            // If the string in valueBuffer is shorter than 8 characters,
            // pad the string with spaces.
            tempBuffer[tempBufferIndex] = ' ';
            tempBufferIndex++;
            valueBufferIndex++;
        }
    }while((tempBufferIndex < 8) && (valueBufferIndex < MAXIMUM_CHARS_TO_CHECK));
    
    // Insert a NULL at the end of the string to ensure that it is no longer
    // than 8 characters.
    tempBuffer[8] = '\0';
    
    // Copy the string from tempBuffer to valueBuffer
    memcpy(valueBuffer, tempBuffer, 9);
}
#endif

/* *****************************************************************************
 End of File
 */
