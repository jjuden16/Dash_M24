#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <macros.h>
#include <math.h>
#include <stddef.h>
#include <types.h>

#define dancing 13

// Units
constexpr float MINUTES_PER_HOUR = 60.0;
constexpr float SECONDS_PER_MINUTE = 60.0; // s / min
constexpr float MS_PER_SECOND = 1.0e3;     // ms / s
constexpr float US_PER_SECOND = 1.0e6;     // us / s
constexpr float SECONDS_PER_MS = 1.0e-3;   // s / ms
constexpr float SECONDS_PER_US = 1.0e-6;   // s / us

constexpr float MM_PER_INCH = 25.4;              // mm / inch
constexpr float INCHES_PER_MM = 1 / MM_PER_INCH; // inch / mm

constexpr float FEET_PER_MILE = 5280.0; // feet / mile
constexpr float INCH_PER_FEET = 12.0;   // inch / feet

constexpr float ENGINE_COUNTS_PER_ROT = 32; // count / rot
constexpr float GEAR_COUNTS_PER_ROT = 50;   // count / rot

constexpr float WHEEL_GEAR_COUNTS_PER_ROT = 8; // count / rot

// NOTE: x_to_y ratio is how many rotations of x for 1 rotation of y
constexpr float GEAR_TO_WHEEL_RATIO = 58.0 / 19.0;                
constexpr float GEAR_TO_SECONDARY_RATIO = 17.0 / 50.0;             
 
constexpr float SECONDARY_TO_WHEEL_RATIO =                    
    ((50.0 / 17.0) * (58.0 / 19.0)); // ~8.978

    // 1: 17, 2:50, 3: 19, 4: 58
constexpr float WHEEL_TO_SECONDARY_RATIO =
    (1.0 / SECONDARY_TO_WHEEL_RATIO); // ~0.111                  

constexpr float WHEEL_DIAMETER_INCH = 23.0; // inch                     
constexpr float WHEEL_MPH_PER_RPM = (WHEEL_DIAMETER_INCH * M_PI) /       
                                    (FEET_PER_MILE * INCH_PER_FEET) *    
                                    MINUTES_PER_HOUR; // mph / rpm       

constexpr u32 ENGINE_SAMPLE_WINDOW = 4;
constexpr u32 GEAR_SAMPLE_WINDOW = 10;
constexpr u32 L_WHEEL_GEAR_SAMPLE_WINDOW = 1; 
constexpr u32 R_WHEEL_GEAR_SAMPLE_WINDOW = 1;
 
// ODrive
constexpr u8 ODRIVE_NODE_ID = 0x3;
constexpr u8 RASP_NODE_ID = 0x4; 

constexpr float ODRIVE_VEL_LIMIT = 20.0;        // rot / s    //TODO: Change this to reasonable value
constexpr float ODRIVE_CURRENT_SOFT_MAX = 10.0; // A          // TODO: Check if this is the right value 

// Flexcan
constexpr u32 FLEXCAN_BAUD_RATE = 250000;  
constexpr u32 FLEXCAN_MAX_MAILBOX = 63;     
// Logging
// bytes_per_cycle * cycle_freq * time_to_flush_sd * safety_factor
// 100 * 100 * 0.4 * 2 = 8000
constexpr size_t LOG_BUFFER_SIZE = 65536;

constexpr u8 PROTO_HEADER_MESSAGE_ID = 0x00;
constexpr u8 PROTO_CONTROL_FUNCTION_MESSAGE_ID = 0x01;

constexpr size_t MESSAGE_BUFFER_SIZE = 512;
constexpr size_t PROTO_DELIMITER_LENGTH = 5;

// Teensy 
#define Button_1 38
#define Button_2 37
#define Button_3 36
#define Button_4 35
#define Switch 34

#define LED_1 0
#define LED_2 1
#define LED_3 2
#define LED_4 3
#define LED_5 4
#define LED_6 5

#define Display_SCL 24
#define Display_SDA 25

#define CAN_RX 21
#define CAN_TX 20

#endif