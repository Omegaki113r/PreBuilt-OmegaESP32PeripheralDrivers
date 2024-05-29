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
 * Last Modified: Thursday, 30th May 2024 3:39:22 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
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
        StationMode,
        AccessPointMode,
        DualMode,
    } WiFiControllerMode;

    typedef struct
    {
        char m_ssid[33];
        uint8_t m_mac_address[8];
    } AccessPoint_t;

    typedef uint64_t AccessPointHandle;
    typedef void (*sta_status_changed_cb_t)(StationStatus);
    typedef void (*ap_assigned_ip_cb_t)(void);
    typedef void (*scan_result_cb_t)(AccessPoint_t *, size_t);

    WiFiControllerStatus OmegaWiFiController_initialize(WiFiControllerMode in_mode);
    WiFiControllerStatus OmegaWiFiController_deinitialize();
    WiFiControllerStatus OmegaWiFiController_set_sta_provisioning(const char *in_ssid, const char *in_password, uint16_t in_retry_count);
    WiFiControllerStatus OmegaWiFiController_set_ap_provisioning(const char *in_ssid, const char *in_password);
    WiFiControllerStatus OmegaWiFiController_start();
    WiFiControllerStatus OmegaWiFiController_start_scan();
    WiFiControllerStatus OmegaWiFiController_set_scan_result_callback(scan_result_cb_t in_scan_result_cb);
    WiFiControllerStatus OmegaWiFiController_set_station_status_changed_callback(sta_status_changed_cb_t in_station_status_cb);

#ifdef __cplusplus
}
#endif

#endif