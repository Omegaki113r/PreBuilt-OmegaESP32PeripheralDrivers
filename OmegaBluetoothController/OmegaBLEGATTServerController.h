#ifndef __OMEGA_BLE_GATT_SERVER_CONTROLLER_H__
#define __OMEGA_BLE_GATT_SERVER_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if CONFIG_BT_ENABLED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <esp_log.h>
#include <esp_bt.h>
#include <esp_gap_ble_api.h>
#include <esp_gatts_api.h>
#include <esp_bt_defs.h>
#include <esp_bt_main.h>
#include <esp_gatt_common_api.h>

#include "OmegaBluetoothCommon.h"

#define GATTS_TAG "OmegaBLEGATTServerController"
#define MAX_GATT_SERVER_PROFILE_COUNT 100
#define adv_config_flag (1 << 0)
#define scan_rsp_config_flag (1 << 1)

    typedef struct
    {
        esp_gatts_cb_t gatts_cb;
        uint16_t gatts_if;
        uint16_t app_id;
        uint16_t conn_id;
        uint16_t service_handle;
        esp_gatt_srvc_id_t service_id;
        uint16_t char_handle;
        esp_bt_uuid_t char_uuid;
        esp_gatt_perm_t perm;
        esp_gatt_char_prop_t property;
        uint16_t descr_handle;
        esp_bt_uuid_t descr_uuid;
    } OmegaBLEGATTServer_profile_t;

    typedef struct
    {
        uint16_t _m_mtu;
        uint8_t _m_advertising_config_done;
        esp_ble_adv_params_t _m_advertising_parameters;
        OmegaBLEGATTServer_profile_t _m_gatts_profiles[MAX_GATT_SERVER_PROFILE_COUNT];
        esp_gatts_cb_t _m_gatts_profile_callback[MAX_GATT_SERVER_PROFILE_COUNT];
    } OmegaBLEGATTServerController_t;

    void OmegaBLEGATTServerController_reset_module(OmegaBLEGATTServerController_t *);
    void OmegaBLEGATTServerController_set_advertising_parameters(OmegaBLEGATTServerController_t *, uint16_t, uint16_t, esp_ble_adv_type_t, esp_ble_addr_type_t, esp_ble_adv_channel_t, esp_ble_adv_filter_t);
    void OmegaBLEGATTServerController_set_MTU(OmegaBLEGATTServerController_t *, uint16_t);
    void OmegaBLEGATTServerController_initialize(OmegaBLEGATTServerController_t *);

    void _OmegaBLEGATTServerController_gatts_event_handler(esp_gatts_cb_event_t, esp_gatt_if_t, esp_ble_gatts_cb_param_t *);
    void _OmegaBLEGATTServerController_gap_event_handler(esp_gap_ble_cb_event_t, esp_ble_gap_cb_param_t *);

#endif

#ifdef __cplusplus
}
#endif

#endif