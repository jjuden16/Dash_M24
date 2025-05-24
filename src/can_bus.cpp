#include <FlexCAN_T4.h>
#include <string>
#include "constants.h"
#include "can_ids.h"
#include "can_bus.h"


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>  Can_Bus::flexcan_bus;
std::map<int, float> Can_Bus::msg_values;

// TODO: Does it make sense to initialize to 0 or should it be -1
Can_Bus::Can_Bus()
{
    msg_values.insert({CAN_FILTERED_SECONDARY_RPM, 0.0});
}

void Can_Bus::setup()
{
  flexcan_bus.begin();
  flexcan_bus.setBaudRate(FLEXCAN_BAUD_RATE);
  flexcan_bus.setMaxMB(FLEXCAN_MAX_MAILBOX);
  flexcan_bus.enableFIFO();
  flexcan_bus.enableFIFOInterrupt();
  flexcan_bus.onReceive(can_parse);
}

/**
 * @brief Send a command
 * @param cmd_id ODrive CAN command ID number
 * @param remote RTR bit for CAN message (typically 0 for setters and 1 for
 * requesters)
 * @param buf 8-wide array of command data bytes
 * @return Status code of command send
 */
u8 Can_Bus::send_command(u32 func_id, u32 node_id, bool remote, u8 buf[]) {
  // TODO: Fix error mwessages
  CAN_message_t msg;
  if (func_id < 0x00 || 0x1f < func_id) {
    return -1;
  }
  
    msg.id = (node_id << 5) | func_id;
  
  msg.len = 8;
  memcpy(&msg.buf, buf, 8);
  msg.flags.remote = remote;

  int write_code = flexcan_bus.write(msg);
 
  return write_code;
}

u8 Can_Bus::send_command(CAN_message_t msg) {
  return flexcan_bus.write(msg);
}

void Can_Bus::can_parse(const CAN_message_t &msg)
{
    u32 parsed_node_id = (msg.id >> 5) & 0x3F;
    u32 cmd_id = msg.id & 0x1F;
  
    if(parsed_node_id == RASP_NODE_ID)
        parse_message(msg);

}

void Can_Bus::parse_message(const CAN_message_t &msg) 
{
    u32 cmd_id = msg.id & 0x1F;

    switch (cmd_id) {
        case CAN_FILTERED_SECONDARY_RPM:
            u32 secondary_rpm; 
            memcpy(&secondary_rpm, msg.buf + 2, 4);
            msg_values.at(CAN_FILTERED_SECONDARY_RPM) = secondary_rpm;
            break;
    }

}