/**
 * @file OmegaWiFiController.h
 * @author Omegaki113r
 * @date Monday, 13th May 2024 4:07:25 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32PeripheralDrivers
 * File Name: OmegaWiFiController.h
 * File Created: Monday, 13th May 2024 4:07:25 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Friday, 31st May 2024 9:02:34 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 31-05-2024	0m3g4	complete implementation of OmegaWiFiController_manual_config, OmegaWiFiController_config and auto retry feature
 *
 * 31-05-2024	0m3g4	implementation of OmegaWiFiController_manual_config
 *
 * 31-05-2024	0m3g4	adding dual mode
 *
 * 30-05-2024	0m3g4	adding access point feature
 *
 * 30-05-2024	0m3g4	adding OmegaWiFiController_set_sta_provisioning,OmegaWiFiController_set_station_status_changed_callback APIs
 *
 * 29-05-2024	0m3g4	initial developemt started
 */

#ifndef __OMEGA_WIFI_CONTROLLER_H__
#define __OMEGA_WIFI_CONTROLLER_H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        WIFICTRL_SUCCESS,
        WIFICTRL_FAILED,
    } WiFiControllerStatus;

    typedef enum
    {
        STA_CONNECTED,
        STA_DISCONNECTED,
        STA_CONNECTION_FAILED,
        STA_GOT_IP,
    } StationStatus;

    typedef enum
    {
        AP_CONNECTED,
        AP_DISCONNECTED,
        AP_GOT_IP,
    } APStatus;

    typedef enum
    {
        Invalid,
        StationMode = (1 << 0),
        AccessPointMode = (1 << 1),
        DualMode = (StationMode | AccessPointMode),
    } WiFiControllerMode;

    typedef struct
    {
        char m_ssid[33];
        uint8_t m_mac_address[8];
    } AccessPoint_t;

    typedef uint64_t AccessPointHandle;
    typedef void (*sta_status_changed_cb_t)(StationStatus);
    typedef void (*ap_status_changed_cb_t)(APStatus);
    typedef void (*scan_result_cb_t)(AccessPoint_t *, size_t);

    WiFiControllerStatus OmegaWiFiController_manual_config(const char *in_json_str);
    WiFiControllerStatus OmegaWiFiController_config();
    WiFiControllerStatus OmegaWiFiController_initialize(WiFiControllerMode in_mode);
    WiFiControllerStatus OmegaWiFiController_deinitialize();
    WiFiControllerStatus OmegaWiFiController_set_sta_provisioning(const char *in_ssid, const char *in_password, uint16_t in_retry_count);
    WiFiControllerStatus OmegaWiFiController_set_ap_provisioning(const char *in_ssid, const char *in_password);
    WiFiControllerStatus OmegaWiFiController_start_scan();
    WiFiControllerStatus OmegaWiFiController_set_scan_result_callback(scan_result_cb_t in_scan_result_cb);
    WiFiControllerStatus OmegaWiFiController_set_station_status_changed_callback(sta_status_changed_cb_t in_station_status_cb);
    WiFiControllerStatus OmegaWiFiController_set_access_point_status_changed_callback(ap_status_changed_cb_t in_access_point_status_cb);

#ifdef __cplusplus
}
#endif

#endif