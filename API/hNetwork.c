/*
 * hNetwork.c
 *
 *  Created on: 11 de out. de 2024
 *      Author: diego.marinho
 */

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "hNetwork.h"



// -----------------------------------------------------------------------------
//                          Variables Definitions
// -----------------------------------------------------------------------------
int16_t tx_powerx = SL_SENSOR_SINK_TX_POWER;


// -----------------------------------------------------------------------------
//                          Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Checks if the current channel is valid for the selected PHY.
 * If the channel is invalid, it recommends the first available channel.
 * Returns false if the given channel is below the first allowed channel
 * or true otherwise.
 *****************************************************************************/
bool hcheck_channel(uint16_t channel)
{
  bool channel_ok = true;
  uint16_t default_channel = emberGetDefaultChannel();

  if (channel < default_channel) {
    //app_log_info("Channel %d is invalid, the first valid channel is %d!\n", channel, default_channel);
    channel_ok = false;
  }
  return (channel_ok);
}

/******************************************************************************
 * CLI - Join as Sleepy End Device
 * Joins the network on the specified channel.
 *****************************************************************************/
void join_sleepy(uint16_t channel)
{
  EmberNetworkParameters parameters;
  //uint16_t channel = sl_cli_get_argument_uint8(arguments, 0);
  // Abort if the channel is invalid for this PHY
  if (hcheck_channel(channel) == false) {
    return;
  }

  memset(&parameters, 0, sizeof(EmberNetworkParameters));
  parameters.radioTxPower = tx_powerx;
  parameters.radioChannel = channel;

  // set default PAN ID or the one passed as parameter
  parameters.panId = SL_SENSOR_SINK_PAN_ID;

  emberJoinNetwork(EMBER_STAR_SLEEPY_END_DEVICE, &parameters);
  //app_log_info("join sleepy 0x%02X\n", status);
}

void leave(void)
{
  emberNetworkLeave();
  emberResetNetworkState();
}

void set_tx(uint16_t power){
  emberSetRadioPower(power, 1);
}
