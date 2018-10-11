//
// HwConfig.h
//

#ifndef HW_CONFIG_H_
#define HW_CONFIG_H_

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdio.h>
#include "system_definitions.h"
#include "system/debug/sys_debug.h"


#define CONFIG_ITEM_COUNT 44
#define LAST_BOOL_CONFIG_ITEM_INDEX 5
#define LAST_UINT8_CONFIG_ITEM_INDEX 7
#define LAST_UINT16_CONFIG_ITEM_INDEX 14
#define LAST_INT16_CONFIG_ITEM_INDEX 16
#define LAST_UINT32_CONFIG_ITEM_INDEX 28
#define LAST_ENUM_CONFIG_ITEM_INDEX 29
#define LAST_STRING_CONFIG_ITEM_INDEX CONFIG_ITEM_COUNT

// *** Global Defines ***
#define CHAR_LF                                         10
#define CHAR_CR                                         13
#define CHAR_GREATER_THAN                               '>'
#define ONE_MINUTE_IN_MS                                60000   // ms

#define BOUNDS_CHECK_MAX_EOT_ID_VALUE                   99999   // Max EOT ID
#define BOUNDS_CHECK_MAX_DLS_VALUE                      4095    // Max value
//#define BOUNDS_CHECK_MIN_WAKE_CALL_SPACING_IN_MINUTES   60      // minutes
#define BOUNDS_CHECK_MIN_WAKE_CALL_SPACING_IN_MINUTES   1      // minutes
#define BOUNDS_CHECK_MAX_WAKE_CALL_SPACING_IN_MINUTES   25200   // minutes
//#define BOUNDS_CHECK_MIN_SLEEP_CALL_SPACING_IN_MINUTES  60      // minutes
#define BOUNDS_CHECK_MIN_SLEEP_CALL_SPACING_IN_MINUTES  1      // minutes
#define BOUNDS_CHECK_MAX_SLEEP_CALL_SPACING_IN_MINUTES  25200   // minutes
#define BOUNDS_CHECK_MIN_READINESS_FLAG                 0       // 0=do not show
#define BOUNDS_CHECK_MAX_READINESS_FLAG                 1       // 1=show screen

// *** Daylight Sensor ***
#define DLS_LIGHT_TO_DARK_THRESHOLD                 40
#define DLS_DARK_TO_LIGHT_THRESHOLD                 45
//#define DLS_LIGHT_TO_DARK_THRESHOLD               90
//#define DLS_DARK_TO_LIGHT_THRESHOLD               110
//#define DLS_LIGHT_TO_DARK_THRESHOLD                 200         // count value
//#define DLS_DARK_TO_LIGHT_THRESHOLD                 300         // count value
#define DLS_LIGHT_TO_DARK_TRANSITION_TIME_IN_SECS   60          // seconds
#define DLS_DARK_TO_LIGHT_TRANSITION_TIME_IN_SECS   180         // seconds


// *** Valves ***
#define VALVE_POSITION_LIMIT                        500
#define VALVE_BRAKE_OPEN_TIME_MS                    20000       // msec
#define VALVE_BRAKE_OPEN_TIME_SEC                   20          // sec
//#define VALVE_BRAKE_RECHECK_TIME                    10000       // msec
//#define VALVE_BRAKE_MAX_TIME                        120000      // msec
#define EOT_MAXIMUM_EMERGENCY_PRESSURE_COUNT        6           // attempts

// *** Charger ***
#define CHARGER_QCOUNT_PRESCALE_FACTOR              0x0080
#if(CHARGER_QCOUNT_PRESCALE_FACTOR==0x0080)
#define CHARGER_CAPACITY_PER_COUNT                  1.0667f     // mAh
#elif(CHARGER_QCOUNT_PRESCALE_FACTOR==0x0200)
#define CHARGER_CAPACITY_PER_COUNT                  4.2666f     // mAh
#else
#error "CHARGER_QCOUNT_PRESCALE_FACTOR not defined"
#endif
#define CHARGER_DEFAULT_BATTERY_CHARGE              40          // percent
#define CHARGER_DEFAULT_BATTERY_CAPACITY            4500.0f     // mAh
#define CHARGER_COUNT_VALUE_ERROR                   0xFFFFFFFF
#define CHARGER_INITIAL_QCOUNT                      32768       // counts
#define CHARGER_SOC_UPDATE_PERIOD                   300         // seconds
#define CHARGER_BATTERY_LEVEL_LOW                   30          // percent
#define CHARGER_BATTERY_LEVEL_DEAD                  5           // percent
#define CHARGER_VOLTAGE_LEVEL_DEAD                  12.4f       // volts
#define CHARGER_VOLTAGE_LEVEL_MISSING               11.0f       // volts
#define CHARGER_BATTERY_READY_THRESHOLD             80          // percent
#define CHARGER_BATTERY_CAPACITY_IN_COUNTS          \
        (CHARGER_DEFAULT_BATTERY_CAPACITY/CHARGER_CAPACITY_PER_COUNT)+1
#define CHARGER_MINIMUM_VALID_QCOUNT                6000        // counts
#define CHARGER_MAXIMUM_VALID_QCOUNT                60000       // counts

// *** Button ***
#define BUTTON_DEBOUNCE_PERIOD_MS                   150         // msec
#define BUTTON_SECOND_DEBOUNCE_PERIOD_MS            200         // msec
#define BUTTON_POST_SECOND_DEBOUNCE_PERIOD_MS       1000        // msec
#define BUTTON_FIRST_RELEASE_PERIOD_MS              3000        // msec
#define BUTTON_SHUTDOWN_PERIOD_MS                   10000       // msec
#define BUTTON_SHUTDOWN_ABORTED_PERIOD_MS           13000       // msec
#define BUTTON_STUCK_PERIOD_MS                      60000       // msec

// *** Config ***
#define EOT_ENABLED                                 1
#define EOT_DISABLED                                0
#define EOT_DISABLED_TIMER_COUNT_IN_SEC             60          // sec
//#define EOT_ID                                      25
#define EOT_INVALID_ID                              0
#define EOT_DEFAULT_ID                              0
#define EOT_ID                                      26
//#define RR_ID                                       "INV"
#define RR_ID                                       "TST"
#define DEFAULT_MODEL_NUMBER                        "90385-0XXX"
#define DEFAULT_BOARD_SERIAL_NUMBER                 "NONE"
#define BOARD_SERIAL_NUMBER_LENGTH                  16
#define FW_VERSION                                  "9VD75-49"
#define BOOT_VERSION                                "9VA87-C"
#define MCM_SERIAL_NUMBER                           "NA"
#define PMM_FW_VERSION                              "NA"
#define PMM_BOOT_VERSION                            "NA"
#define PMM_SERIAL_NUMBER                           "NA"
#define CALL_SPACING_WAKE_IN_MIN                    120         // min
#define CALL_SPACING_SLEEP_IN_MIN                   120         // min
#define BOOTLOADER_IMAGE_FILE_NAME                  "image.hex"
#define USE_DEGREES_IN_LOG
#define BOOTLOADER_VERSION_LOCATION                 0x9fc2fe00
#define BOOTLOADER_VERSION_STRING_MAX_LENGTH        8

// *** Accelerometer ***
#define ACCEL_MAXIMUM_MOTION_COUNT                  20
//#define ACCEL_MOTION_THRESHOLD                      10
#define ACCEL_MOTION_THRESHOLD                      3
#define ACCEL_SAMPLE_PERIOD_MS                      1001
#define ACCEL_MOTION_DETECT_DEADBAND                250

// *** Alpha ***
// ALPHA_WAKE_DELAY is the amount of time that each startup message is displayed.
#define ALPHA_WAKE_DELAY                            3000        // msec
//#define ALPHA_BLANK_DELAY                           300000UL      // msec
#define ALPHA_BLANK_DELAY                           30000       // msec
#define ALPHA_CHARGING_DELAY                        5000        // msec
#define ALPHA_CHARGING_DONE_DELAY                   5000        // msec
#define ALPHA_BATTERY_MISSING_DELAY                 5000        // msec
#define ALPHA_BATTERY_SHORTED_DELAY                 5000        // msec
#define ALPHA_SHOW_BATTERY_READINESS                1
//#define ALPHA_BATTERY_READINESS_TEXT_YES            "BAT = SI"
//#define ALPHA_BATTERY_READINESS_TEXT_NO             "BAT = NO"
#define ALPHA_BATTERY_READINESS_TEXT_YES            "BAT = OK"
#define ALPHA_BATTERY_READINESS_TEXT_NO             "BAT=NOK "

// *** Digit ***
#define DIGIT_REMOVE_LEADING_ZEROES                             // define if used
#define DIGIT_BLANK_DELAY                           30000       // msec
#define DIGIT_WAKE_DELAY                            1000        // msec

// *** HVM ***
#define HVM_TEST_TIME                               30000       // msec
#define HVM_MOTION_TEST_TIME                        20000       // msec
#define HVM_ON_TIME                                 210         // msec
#define HVM_OFF_TIME                                1100        // msec
#define HVM_CONVERSION_TIME                         20          // msec
#ifdef USE_REV_B
#define HVM_VOLTAGE_VALID_THRESHOLD                 2.0f        // volts
#define HVM_CURRENT_VALID_THRESHOLD                 0.9f        // volts
#endif
#ifdef USE_REV_C
#define HVM_VOLTAGE_VALID_THRESHOLD                 0.70f       // volts
#define HVM_CURRENT_VALID_THRESHOLD                 0.20f       // volts
#endif

// *** EOT ***
#define EOT_DISPLAY_TIMEOUT_IN_SEC                  300         // sec
//#define EOT_TILT_TIME                             60000       // msec
#define EOT_GNSS_REFRESH_TIME                       1800000L    // msec
//#define EOT_DISPLAY_TIMEOUT_AFTER_MOTION            20000       // msec
#define EOT_DISPLAY_TIMEOUT_AFTER_MOTION_IN_SEC     20          // sec
#define EOT_GENERATOR_FAILURE_IN_SECONDS            10          // seconds
#define EOT_TRANSDUCER_FAILURE_IN_SECONDS           10          // seconds
#define EOT_ACCELEROMETER_FAILURE_IN_SECONDS        10          // seconds
#define EOT_PS_X_FAILURE_IN_SECONDS                 10          // seconds
#define EOT_PS_G_FAILURE_IN_SECONDS                 10          // seconds
#define EOT_RPM_FAILURE_IN_SECONDS                  10          // seconds
#define EOT_DLS_FAILURE_IN_SECONDS                  86400       // seconds
#define EOT_TSNS_FAILURE_IN_SECONDS                 86400       // seconds
#define EOT_CHARGER_FAILURE_IN_SECONDS              10          // seconds
#define EOT_HVM_FAILURE_IN_SECONDS                  10          // seconds
#define EOT_TEMP_FAILURE_IN_SECONDS                 10          // seconds
#define EOT_GVLV_FAILURE_IN_SECONDS                 10          // seconds
#define EOT_DVLV_FAILURE_IN_SECONDS                 10          // seconds


// *** FSK ***
#define FSK_HOT_MESSAGE_PERIOD                      60000       // msec

// *** GNSS ***
#define GNSS_TIMEOUT_PERIOD                         60000        // msec
//#define GNSS_MAXIMUM_MOTION_COUNT                   30          // (count)
//#define GNSS_MOTION_THRESHOLD                       10          // (count)
#define GNSS_MAXIMUM_MOTION_COUNT                   10          // (count)
#define GNSS_MAXIMUM_STOPPED_COUNT                  10          // (count)
#define GNSS_MINIMUM_SPEED_KPH                      3.5f        // kph
#define GNSS_FIX_TIMEOUT                            600         // seconds
#define GNSS_MAXIMUM_FAIL_COUNT                     5           // counts
#define GNSS_MAXIMUM_TRACK_COUNT                    4           // counts
#define GNSS_VALID_TRACK_DELTA                      10.0f       // degrees

// Other
#define EOT_GENERATOR_ENABLE_PRESSURE               5           // psi
//#define EOT_GENERATOR_OVERVOLTAGE_THRESHOLD         25.0f       // V
//#define EOT_GENERATOR_OVERVOLTAGE_THRESHOLD         32.0f       // V
#define EOT_GENERATOR_OVERVOLTAGE_THRESHOLD         34.0f       // V

// Re-enable generator after being manually disabled
#define EOT_GENERATOR_REENABLE_TIMEOUT_MS            300000      // msec
#define EOT_GENERATOR_REENABLE_TIMEOUT_SEC           300         // sec

// Re-enable generator after overvoltage condition
//#define EOT_GENERATOR_OVERVOLTAGE_TIMEOUT_MS         15000       // msec
#define EOT_GENERATOR_OVERVOLTAGE_TIMEOUT_SEC        900         // sec

// EOT tilt count
#define EOT_MAX_TILT_COUNT                          60          // sec

// System
#define EOT_NO_PRESSURE                             5           // psi
#define EOT_MINIMUM_PRESSURE_CHANGE                 2           // psi
#define EOT_MINIMUM_BRAKE_PRESSURE                  5           // psi
#define EOT_MINIMUM_OPERATIONAL_BRAKE_PRESSURE      45          // psi
//#define EOT_MINIMUM_AIRGEN_INPUT_VOLTAGE            10.0f       // volts       
//#define EOT_MAXIMUM_AIRGEN_INPUT_VOLTAGE            24.0f       // volts
#define EOT_MINIMUM_EXTERNAL_INPUT_VOLTAGE          10.0f       // volts       
#define EOT_MAXIMUM_EXTERNAL_INPUT_VOLTAGE          24.0f       // volts
#define EOT_MINIMUM_EXTERNAL_REGULATOR_VOLTAGE      14.0f       // volts
#define EOT_GENERATOR_STOPPED_RPMS                  500         // rpms
#define EOT_GENERATOR_RUNNING_RPMS                  8000        // rpms
#define EOT_GENERATOR_REGULATOR_LOW_VOLTAGE         5.0f        // volts
#define EOT_GENERATOR_REGULATOR_MINIMUM_VOLTAGE     13.0f       // volts
#define EOT_LOW_TRANSDUCER_PRESSURE                 20          // psi
#define EOT_MINIMUM_OPERATIONAL_BRAKE_PRESSURE      45          // psi
#define EOT_HIGH_TRANSDUCER_PRESSURE                70          // psi
#define EOT_EXTERNAL_CHARGER_PRESENT_VOLTAGE        9.0f        // volts       
#define EOT_16V_SWITCHER_OUTPUT_LOW                 9.0f        // volts       
#define EOT_GEN_REG_OUTPUT_GOOD                     13.0f       // volts       
#define EOT_16V_SWITCHER_OUTPUT_GOOD                15.0f       // volts       
#define EOT_GENERATOR_STOPPED_RPMS                  500         // rpms
#define EOT_GENERATOR_REGULATOR_14V                 14.0f       // volts
#define EOT_GENERATOR_VOLTAGE_LOW                   5.0f        // volts
#define VALVE_VOLTAGE_OPEN_CHECK_VOLTAGE            6.0f        // volts
#define VALVE_VOLTAGE_SHORTED_CHECK_VOLTAGE         6.0f        // volts
#define VALVE_COIL_NOT_SHORTED_CHECK_VOLTAGE        11.0f       // volts
#define VALVE_COIL_NOT_OPEN_CHECK_VOLTAGE           1.0f        // volts

// Temporarily reduced this setpoint until the charger uses MPPT.
//#define EOT_MINIMUM_AIRGEN_VOLTAGE                  14.0f       // volts
//#define EOT_MINIMUM_AIRGEN_VOLTAGE                  13.5f       // volts
#define EOT_MINIMUM_AIRGEN_VOLTAGE                  13.0f       // volts

#define EOT_MAXIMUM_TEMPERATURE                     70          // degrees C
#define ADC_PRESSURE_OFFSET                         310.3f      // counts
#define ADC_PRESSURE_SLOPE                          16.55f      // counts/psi
#define ADC_PRESSURE_COUNT_FOR_90                   1800.1f     // counts
#define ADC_PRESSURE_MAXIMUM                        125.0f      // psi
#define ADC_PRESSURE_MINIMUM                        0.0f        // psi
//#define ADC_PRESSURE_CALIBRATION_OFFSET_PRIMARY     0           // psi
//#define ADC_PRESSURE_CALIBRATION_OFFSET_SECONDARY   0           // psi
#define ADC_PRESSURE_CALIBRATION_PRESSURE           90.0f       // psi
#define ADC_PRESSURE_Y_INTERCEPT_DEFAULT            18.75f      // psi
// SD Card
#define SDCARD_VBAT_LOCKOUT_VOLTAGE                 12.2f       // volts
#define SDCARD_SOC_MAXIMUM_FAILURE_COUNT            100

// Serial
#define SERIAL_BUFFER_STRING_LENGTH                 80          // characters

// *** CHARGER ***
// Refer to the LTC4015 datasheet for details on the meanings of these values.
// For information on JEITA...


// Limit V6 and V5 to 14.0V
#define CHARGER_VCHARGE_JEITA_65                    0x00E7      // hex
// Limit V4 to 14.0V. Limit V3 and V2 to 14.4V.
#define CHARGER_VCHARGE_JEITA_432                   0x1DEF      // hex

// Calculations for current:
// There is a 5-bit register that controls the target voltage for each region.
//  The current is calculated in a range of 1mV-32mV divided by R_SNSB which
//  is 4 mohms in Rev B.  This converts to 250mA for a bit value of 00000 and 
//  1000mA for a bit value of 00011.  CHARGER_ICHARGE_JEITA_432 contains
//  5-bit registers for regions 4 and 3 and 2.  See the LTC4015 datasheet.
// Set I6 and I5 to 250 mA
//#define CHARGER_ICHARGE_JEITA_65                    0x0000      // hex

// Set I6 and I5 to 500 mA
#define CHARGER_ICHARGE_JEITA_65_500mA                0x0021      // hex

// Set I6 and I5 to 1000 mA
//#define CHARGER_ICHARGE_JEITA_65                    0x0063      // hex

// Set I6 and I5 to 1500 mA
#define CHARGER_ICHARGE_JEITA_65_1500mA               0x00A5      // hex

// Limit I4, I3 and I2 to 250mA
//#define CHARGER_ICHARGE_JEITA_432                   0x0000      // hex

// Limit I4, I3 and I2 to 500mA
#define CHARGER_ICHARGE_JEITA_432_500mA               0x0421      // hex

// Limit I4, I3 and I2 to 1000mA
//#define CHARGER_ICHARGE_JEITA_432                   0x0C63      // hex

// Limit I4, I3 and I2 to 1500mA
#define CHARGER_ICHARGE_JEITA_432_1500mA              0x14A5      // hex

// Charge rate constant equivalent to ICHARGE_JEITA
//#define CHARGER_CHARGE_RATE                         1000        // mA/hr
#define CHARGER_CHARGE_RATE                         1500        // mA/hr

// 
#define CHARGER_CONVERSION_COUNTS_TO_MA             1.0667f

// Defines temperature values for each region
#define CHARGER_JEITA_T1                            0x5230      // hex for -40C
//#define CHARGER_JEITA_T1                            0x4BDC      // hex for -20C
#define CHARGER_JEITA_T2                            0x377C      // hex for 10C
#define CHARGER_JEITA_T3                            0x1F02      // hex for 40C
#define CHARGER_JEITA_T4                            0x1BA3      // hex for 45C
#define CHARGER_JEITA_T5                            0x1891      // hex for 50C
#define CHARGER_JEITA_T6                            0x134A      // hex for 60C

// Set threshold to 13.20 Volts
#define CHARGER_RECHARGE_THRESHOLD                  0x430C      // hex

// Set the input current limit to 3 Amps
#define CHARGER_IIN_LIMIT_SETTING                   0x0011      // hex

// Set the input current limit to 167 mAmps
//#define CHARGER_IIN_LIMIT_SETTING                   0x0000      // hex

// Max CV Time in seconds
#define CHARGER_MAX_CV_TIME                         14400       // seconds

// Menu
#define MENU_FACTORY_CONFIGURATION_PASSWORD         "SiemensEOT"
#define MENU_CUSTOMER_CONFIGURATION_PASSWORD        "Customer"

// Set to 1 and use Siemens SIM card to access EOTPH or
// set to 0 and use AT&T SIM card to access httpbin.org and Internet.
#if 1
    #define APN_NAME                                "eotph01.com.attz"
    #define APN_USERNAME                            "User"
    #define APN_PASSWORD                            "Pass"
    #define WEBSERVER_ADDRESS                       "m2m.eotph.com"
    #define CM_SERVER_PATH                          "/cm"
#else
    #define APN_NAME                                "phone"
    #define APN_USERNAME                            ""
    #define APN_PASSWORD                            ""
    #define WEBSERVER_ADDRESS                       "httpbin.org"
    #define CM_SERVER_PATH                          "/post"
#endif
#define REMOTE_UDP_PORT                             10502
#define REMOTE_HTTP_PORT                            80
#define CELL_MSISDN                                 "1234567890"
#define HTTP_POST_PARAM                             "1"
#define CELL_MAX_NUMBER_OF_HEALTH_CHECKS            100
#define CELL_TEMPERATURE_OFFSET                     40          // degrees
#define CELL_POWERUP_TIMEOUT                        60          // seconds
#define CELL_CONTEXT_ACTIVATION_FAILED_TIMEOUT      60          // seconds
#define CELL_CONNECT_TO_SLOT_FAILED_TIMEOUT         60          // seconds
#define CELL_MAXIMUM_REGISTRATION_CHECKS            60         // number of fails

#define CELL_REPLY_MSG_ACK                          "OK"                // standard reply to a position message
#define CELL_REPLY_MSG_CMD                          "X-EOT-Cmd: "       // start of command sent in reply to position message
#define CELL_REPLY_MSG_CMD_AUTH                     "X-EOT-Cmd-Auth: "  // start of command authorization
#define CELL_REPLY_MSG_SET_CALL_SPACING             "call-spacing="     // command to set call spacing
#define CELL_REPLY_MSG_CM_REFRESH                   "cm-refresh"        // command to send configuration data
#define CELL_REPLY_MSG_DISABLE_EOT                  "disable-eot"       // command to disable EOT functions
#define CELL_REPLY_MSG_ENABLE_EOT                   "enable-eot"        // command to enable EOT functions
#define CELL_REPLY_MSG_CONTENT_LENGTH               "Content-Length: "  // length of download file
#define CELL_REPLY_MSG_UPLOAD                       "swu="              // command to upload new firmware

// *** Monitoring ***
#define EOT_MONITOR_INTERVAL                        1000        // seconds

// *** External ADC ***
#define EXT_ADC_BITS                                12
#define EXT_ADC_REFERENCE                           2.5f        // volts
#define EXT_ADC_STEP (EXT_ADC_REFERENCE/(1 << EXT_ADC_BITS))
#if (EXT_ADC_BITS == 10)
#define EXT_ADC_MASK                                0x03FF
#elif (EXT_ADC_BITS == 12)
#define EXT_ADC_MASK                                0x0FFF
#endif
    
#define V3P8_R1_VALUE 56000.0f
#define V3P8_R2_VALUE 84500.0f
#define V3P8_RATIO_RECIPROCAL ((V3P8_R2_VALUE+V3P8_R1_VALUE)/V3P8_R2_VALUE)

#define V5P0_R1_VALUE 84500.0f
#define V5P0_R2_VALUE 56000.0f
#define V5P0_RATIO_RECIPROCAL ((V5P0_R2_VALUE+V5P0_R1_VALUE)/V5P0_R2_VALUE)

#define V16P0_R1_VALUE 57600.0f       // RAD - Value on Rev B schematic
//#define V16P0_R1_VALUE 63400.0f         // RAD - Mod value for Rev B schematic
#define V16P0_R2_VALUE 10000.0f
#define V16P0_RATIO_RECIPROCAL ((V16P0_R2_VALUE+V16P0_R1_VALUE)/V16P0_R2_VALUE)

#define AIRGEN_R1_VALUE 110000.0f
#define AIRGEN_R2_VALUE 10000.0f
#define AIRGENREG_RATIO_RECIPROCAL ((AIRGEN_R2_VALUE+AIRGEN_R1_VALUE)/AIRGEN_R2_VALUE)

#define EXT_R1_VALUE 110000.0f
#define EXT_R2_VALUE 10000.0f
#define EXT_RATIO_RECIPROCAL ((EXT_R2_VALUE+EXT_R1_VALUE)/EXT_R2_VALUE)

#define V3P3_R1_VALUE 57600.0f
#define V3P3_R2_VALUE 100000.0f
#define V3P3_RATIO_RECIPROCAL ((V3P3_R2_VALUE+V3P3_R1_VALUE)/V3P3_R2_VALUE)

#define CELL_R1_VALUE 84500.0f
#define CELL_R2_VALUE 93100.0f
#define CELL_RATIO_RECIPROCAL ((CELL_R2_VALUE+CELL_R1_VALUE)/CELL_R2_VALUE)

#define GPS_R1_VALUE 41200.0f
#define GPS_R2_VALUE 100000.0f
#define GPS_RATIO_RECIPROCAL ((GPS_R2_VALUE+GPS_R1_VALUE)/GPS_R2_VALUE)

// There is no voltage divider for HVM voltage and current

#define UHF1_R1_VALUE 91000.0f
#define UHF1_R2_VALUE 15000.0f
#define UHF1_RATIO_RECIPROCAL ((UHF1_R2_VALUE+UHF1_R1_VALUE)/UHF1_R2_VALUE)

#define UHF2_R1_VALUE 91000.0f
#define UHF2_R2_VALUE 15000.0f
#define UHF2_RATIO_RECIPROCAL ((UHF2_R2_VALUE+UHF2_R1_VALUE)/UHF2_R2_VALUE)

#define V12P0_R1_VALUE 47000.0f
#define V12P0_R2_VALUE 10000.0f
#define V12P0_RATIO_RECIPROCAL ((V12P0_R2_VALUE+V12P0_R1_VALUE)/V12P0_R2_VALUE)

#ifdef USE_REV_B
// Measures voltage up to 32V
#define VR1_R1_VALUE 118000.0f
#endif
#ifdef USE_REV_C
// Measures voltage up to 42V
#define VR1_R1_VALUE 158000.0f
#endif

#define VR1_R2_VALUE 10000.0f
#define AIRGENINPUT_RATIO_RECIPROCAL ((VR1_R2_VALUE+VR1_R1_VALUE)/VR1_R2_VALUE)

// External ADC
#define ADC_EXT_NUMBER_OF_CHANNELS                       14
#define ADC_EXT_HVM_VOLTAGE_PIN                          9
#define ADC_EXT_HVM_CURRENT_PIN                          10

// Other parameters
#define DEFAULT_CALIBRATION_DATE                        "01-01-2018"
#define DEFAULT_CALIBRATION_ENABLED                     false
#define DEFAULT_BATTERY_REPLACEMENT_DATE                "01-01-2018"
#define DEFAULT_WIFI_PASSWORD                           "SiemensEOT"
#define DEFAULT_WIFI_ENABLED                            false
#define DEFAULT_CALIBRATION_TECHNICIAN                  "NA"
#define DEFAULT_CALIBRATION_LOCATION                    "NA"
#define DEFAULT_BATTERY_REPLACEMENT_TECHNICIAN          "NA"
#define DEFAULT_BATTERY_REPLACEMENT_LOCATION            "NA"
#define DEFAULT_GENERATOR_EXISTS                        true
#define DEFAULT_GENERATOR_VALVE_EXISTS                  true
#define DEFAULT_HVM_EXISTS                              true

// 338 days
#define CALIBRATION_SOON_TIME_IN_SECONDS                29203200

// 368 days
#define CALIBRATION_NOW_TIME_IN_SECONDS                 31795200

typedef enum
{
    CFG_EOT_TYPE_SINGLE_PIPE = 1,
    CFG_EOT_TYPE_DUAL_PIPE = 2
} EotPipeConfigurationType_e;

// Add new messages to the end of the list.  Leave obsolete messages in the list.
typedef enum
{
    LOG_MSG_MON_3V3,
    LOG_MSG_MON_3V8,
    LOG_MSG_MON_5V0,
    LOG_MSG_MON_12V0,
    LOG_MSG_MON_15V3,
    LOG_MSG_MON_16V0,
    LOG_MSG_MON_AIRGEN,
    LOG_MSG_MON_EXT,
    LOG_MSG_MON_CELL,
    LOG_MSG_MON_GPS,
    LOG_MSG_MON_UHF1,
    LOG_MSG_MON_UHF2,
    LOG_MSG_BRAKE_VALVE_HIGH_CHECK,
    LOG_MSG_BRAKE_VALVE_LOW_CHECK,
    LOG_MSG_GEN_VALVE_HIGH_CHECK,
    LOG_MSG_GEN_VALVE_LOW_CHECK,
    LOG_MSG_PRESSURE_REAR,
    LOG_MSG_PRESSURE_SECONDARY,
    LOG_MSG_TEMPERATURE,
    LOG_MSG_EOT_TO_HOT,             // RTF
    LOG_MSG_EOT_TO_HOT_SNIFFER,		// RTF
    LOG_MSG_HOT_TO_EOT,             // FTR
    LOG_MSG_HOT_TO_EOT_SNIFFER,		// FTR
    LOG_MSG_EOT_ID,
    LOG_MSG_HW_SERIAL_NUMBER,
    LOG_MSG_GNSS_LATITUDE,
    LOG_MSG_GNSS_LONGITUDE,
    LOG_MSG_GNSS_SPEED,
    LOG_MSG_CELL_MODEL,
    LOG_MSG_CELL_VERSION,
    LOG_MSG_CELL_MANUFACTURER,
    LOG_MSG_CELL_IMEI,
    LOG_MSG_CELL_IMSI,
    LOG_MSG_CELL_SIM_SERIAL_NUMBER,
    LOG_MSG_CELL_RSSI,
    LOG_MSG_CELL_REGISTERED,
    NUMBER_LOG_MESSAGES
} LogMessageType_e;

typedef enum
{
    LOG_FAULT_OVERTEMPERATURE,
    NUMBER_LOG_FAULTS
} LogFaultType_e;


const char * configItemsStrings[] = {
    "calibrationEnabled",
    "wifiEnabled",
    "eotEnabled",
    "generatorExists",
    "generatorValveExists",
    "hvmExists",
    "showBatteryReadiness",
    "batteryReadyThreshold",
    "qcountMinimum",
    "qcountMaximum",
    "storedQcount",
    "socUpdatePeriod",
    "gnssTimeoutPeriod",
    "daylightSensorCalibrationLightToDark",
    "daylightSensorCalibrationDarkToLight",
    "primaryPressureCalibrationValue",
    "secondaryPressureCalibrationValue",
    "idCode",
    "callSpacingWakeTimeInMinutes",
    "callSpacingSleepTimeInSeconds",
    "displayOffTimeoutAfterMotion",
    "displayOffTimeout",
    "gnssRefreshTime",
    "generatorOvervoltageTimeout",
    "generatorReenableTimeout",
    "gnssFixTimeout",
    "cellPowerupTimeout",
    "contextActivationFailedTimeout",
    "connectToSlotFailedTimeout",
    "pipeConfiguration",
    "fwVersion",
    "bootloaderVersion",
    "rrId",
    "batteryReadinessTextYes",
    "batteryReadinessTextNo",
    "calibrationDate",
    "batteryReplacementDate",
    "modelNumber",
    "boardSerialNumber",
    "calibrationTechnician",
    "calibrationLocation",
    "batteryReplacementTechnician",
    "batteryReplacementLocation",
    "wifiPassword"
};

typedef struct
{
    bool calibrationEnabled;
    bool wifiEnabled;
    bool eotEnabled;
    bool generatorExists;
    bool generatorValveExists;
    bool hvmExists;
    uint8_t showBatteryReadiness;
    uint8_t batteryReadyThreshold;
    uint16_t qcountMinimum;
    uint16_t qcountMaximum;
    uint16_t storedQcount;
    uint16_t socUpdatePeriod;
    uint16_t gnssTimeoutPeriod;
    uint16_t daylightSensorCalibrationLightToDark;
    uint16_t daylightSensorCalibrationDarkToLight;
    int16_t primaryPressureCalibrationValue;
    int16_t secondaryPressureCalibrationValue;
    uint32_t idCode;
    uint32_t callSpacingWakeTimeInMinutes;
    uint32_t callSpacingSleepTimeInSeconds;
    uint32_t displayOffTimeoutAfterMotion;
    uint32_t displayOffTimeout;
    uint32_t gnssRefreshTime;
    uint32_t generatorOvervoltageTimeout;
    uint32_t generatorReenableTimeout;
    uint32_t gnssFixTimeout;
    uint32_t cellPowerupTimeout;
    uint32_t contextActivationFailedTimeout;
    uint32_t connectToSlotFailedTimeout;
    EotPipeConfigurationType_e pipeConfiguration;
    char fwVersion[10];
    char bootloaderVersion[BOOTLOADER_VERSION_STRING_MAX_LENGTH+2];
    char rrId[10];
    char batteryReadinessTextYes[10];
    char batteryReadinessTextNo[10];
    char calibrationDate[12];
    char batteryReplacementDate[12];
    char modelNumber[20];
    char boardSerialNumber[20];
    char calibrationTechnician[21];
    char calibrationLocation[21];
    char batteryReplacementTechnician[21];
    char batteryReplacementLocation[21];
    char wifiPassword[31];
} CONFIG_DATA;

CONFIG_DATA configData;
CONFIG_DATA *configDataPtr;

char * configDataCharArrays[LAST_STRING_CONFIG_ITEM_INDEX - LAST_ENUM_CONFIG_ITEM_INDEX];

void CFG_Initialize();
void CFG_ParseConfig(char* parameterBuffer, char* valueBuffer);
void CFG_FormatStringForAlphaDisplay(char* inputBuffer, char* outputBuffer);
//SYS_FS_RESULT CFG_ReadConfig();
//SYS_FS_RESULT CFG_StoreConfig();
void CFG_PadString(char* string, int numberOfCharacters);

uint16_t CFG_GetQcountMinimum();
void CFG_SetQcountMinimum(uint16_t value);
uint16_t CFG_GetQcountMaximum();
void CFG_SetQcountMaximum(uint16_t value);
uint16_t CFG_GetStoredQcount();
void CFG_SetStoredQcount(uint16_t value);
uint32_t CFG_GetDevId();

// *** Serial Number ***
uint32_t CFG_GetId1();
uint32_t CFG_GetId2();


// *** Pipe Configuration ***
EotPipeConfigurationType_e CFG_GetEotPipeConfiguration();
void CFG_SetEotPipeConfiguration(EotPipeConfigurationType_e pipeConfiguration);

// *** EOT ID ***
uint32_t CFG_GetEotID();
void CFG_SetEotID(uint32_t idCode);

// *** EOT Enabled ***
bool CFG_GetEotEnabled();
void CFG_SetEotEnabled(bool eotEnabled);

// *** RR ID ***
void CFG_GetRRID(char* string);
void CFG_SetRRID(char* string);

// *** Board Serial Number ****
void CFG_GetBoardSerialNumber(char* string);
void CFG_SetBoardSerialNumber(char* string);

// *** Model Number ****
void CFG_GetModelNumber(char* string);
void CFG_SetModelNumber(char* string);

// *** FW Version ***
void CFG_GetFwVersion(char* string);
void CFG_SetFwVersion(char* string);

// *** Bootloader Version ***
void CFG_GetBootloaderVersion(char* string);
void CFG_SetBootloaderVersion();

// *** EOT Braking Extension Time ***
//uint16_t CFG_GetBrakingExtensionTime();
//void CFG_SetBrakingExtensionTime(uint16_t time);

// *** GNSS Timeout Period
uint16_t CFG_GetGnssTimeoutPeriod();
void CFG_SetGnssTimeoutPeriod(uint16_t timeout);

// *** SOC (State of Charge) Update Period ***
uint16_t CFG_GetSocUpdatePeriod();
void CFG_SetSocUpdatePeriod(uint16_t time);

// *** Call Spacing - WAKE ***
uint16_t CFG_GetCallSpacingWakeTimeInMinutes();
void CFG_SetCallSpacingWakeTimeInMinutes(uint16_t time);

// *** Call Spacing - SLEEP ***
uint32_t CFG_GetCallSpacingSleepTimeInMinutes();
uint32_t CFG_GetCallSpacingSleepTimeInSeconds();
void CFG_SetCallSpacingSleepTimeInMinutes(uint16_t time);

// *** Show Battery Readiness ***
uint8_t CFG_GetShowBatteryReadiness();
void CFG_SetShowBatteryReadiness(uint8_t value);

// *** Battery Readiness Text ***
void CFG_GetBatteryReadinessTextYes(char* string);
void CFG_SetBatteryReadinessTextYes(char* string);
void CFG_GetBatteryReadinessTextNo(char* string);
void CFG_SetBatteryReadinessTextNo(char* string);

// *** Configuration Date ***
void CFG_GetCalibrationDate(char* string);
void CFG_SetCalibrationDate(char* string);

// *** Configuration Technician ***
void CFG_GetCalibrationTechnician(char* string);
void CFG_SetCalibrationTechnician(char* string);

// *** Configuration Location ***
void CFG_GetCalibrationLocation(char* string);
void CFG_SetCalibrationLocation(char* string);

// *** Calibration Enabled ***
bool CFG_GetCalibrationEnabled();
void CFG_SetCalibrationEnabled(bool calibrationEnabled);

// *** Battery Replacement Date ***
void CFG_GetBatteryReplacementDate(char* string);
void CFG_SetBatteryReplacementDate(char* string);

// *** Battery Replacement Technician ***
void CFG_GetBatteryReplacementTechnician(char* string);
void CFG_SetBatteryReplacementTechnician(char* string);

// *** Battery Replacement Location ***
void CFG_GetBatteryReplacementLocation(char* string);
void CFG_SetBatteryReplacementLocation(char* string);

// *** Wifi Password ***
void CFG_GetWifiPassword(char* string);
void CFG_SetWifiPassword(char* string);

// *** Wifi Enabled ***
bool CFG_GetWifiEnabled();
void CFG_SetWifiEnabled(bool calibrationEnabled);

// *** Battery Ready Threshold ***
uint8_t CFG_GetBatteryReadyThreshold();
void CFG_SetBatteryReadyThreshold(uint8_t value);

// *** Display Off Timeout After Motion ***
uint32_t CFG_GetDisplayOffTimeoutAfterMotion();
void CFG_SetDisplayOffTimeoutAfterMotion(uint32_t displayOffTimeoutAfterMotion);

// *** Display Off Timeout ***
uint32_t CFG_GetDisplayOffTimeout();
void CFG_SetDisplayOffTimeout(uint32_t displayOffTimeout);

// *** Primary Pressure Calibration Offset ***
int16_t CFG_GetPrimaryPressureCalibrationValue();
void CFG_SetPrimaryPressureCalibrationValue(int16_t pressureCalibrationValue);

// *** Secondary Pressure Calibration Offset ***
int16_t CFG_GetSecondaryPressureCalibrationValue();
void CFG_SetSecondaryPressureCalibrationValue(int16_t pressureCalibrationValue);

// *** GNSS Refresh Time
uint32_t CFG_GetGnssRefreshTime();
void CFG_SetGnssRefreshTime(uint32_t gnssRefreshTime);

// *** Generator Overvoltage Timeout ***
uint32_t CFG_GetGeneratorOvervoltageTimeout();
void CFG_SetGeneratorOvervoltageTimeout(uint32_t generatorRefreshTime);

// *** Generator Re-enable Timeout ***
uint32_t CFG_GetGeneratorReenableTimeout();
void CFG_SetGeneratorReenableTimeout(uint32_t generatorReenableTimeout);

// *** GNSS Fix Timeout ***
uint32_t CFG_GetGnssFixTimeout();
void CFG_SetGnssFixTimeout(uint32_t gnssFixTimeout);

// *** Cell Powerup Timeout ***
uint32_t CFG_GetCellPowerupTimeout();
void CFG_SetCellPowerupTimeout(uint32_t cellPowerupTimeout);

// *** Context Activation Failed Timeout ***
uint32_t CFG_GetContextActivationFailedTimeout();
void CFG_SetContextActivationFailedTimeout(uint32_t contextActivationFailedTimeout);

// *** Connect To Slot Failed Timeout ***
uint32_t CFG_GetConnectToSlotFailedTimeout();
void CFG_SetConnectToSlotFailedTimeout(uint32_t connectedToSlotFailedTimeout);

uint16_t CFG_GetDaylightSensorCalibrationLightToDark();
void CFG_SetDaylightSensorCalibrationLightToDark(uint16_t daylightSensorCalibrationLightToDark);

uint16_t CFG_GetDaylightSensorCalibrationDarkToLight();
void CFG_SetDaylightSensorCalibrationDarkToLight(uint16_t daylightSensorCalibrationDarkToLight);

bool CFG_GetGeneratorExists();
void CFG_SetGeneratorExists(bool generatorExists);

bool CFG_GetGeneratorValveExists();
void CFG_SetGeneratorValveExists(bool generatorValveExists);

bool CFG_GetHvmExists();
void CFG_SetHvmExists(bool hvmExists);

// TODO: find a better place for the bit definitions
#define BIT0                                        0x0001
#define BIT1                                        0x0002
#define BIT2                                        0x0004
#define BIT3                                        0x0008
#define BIT4                                        0x0010
#define BIT5                                        0x0020
#define BIT6                                        0x0040
#define BIT7                                        0x0080
#define BIT8                                        0x0100
#define BIT9                                        0x0200
#define BIT10                                       0x0400
#define BIT11                                       0x0800
#define BIT12                                       0x1000
#define BIT13                                       0x2000
#define BIT14                                       0x4000
#define BIT15                                       0x8000



/* *****************************************************************************
 End of File
 */


#endif // HW_CONFIG_H_



