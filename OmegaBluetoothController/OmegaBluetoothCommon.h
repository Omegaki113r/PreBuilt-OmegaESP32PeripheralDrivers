#ifndef __OMEGA_BLUETOOTH_COMMON_H__
#define __OMEGA_BLUETOOTH_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if CONFIG_BT_ENABLED

#include <esp_bt.h>
#include <esp_gap_ble_api.h>
#include <esp_gatts_api.h>
#include <esp_bt_defs.h>
#include <esp_bt_main.h>
#include <esp_gatt_common_api.h>

    void OmegaBluetoothController_common_initialize(esp_bt_mode_t);

#endif

#ifdef __cplusplus
}
#endif

#endif