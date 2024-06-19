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
 * Last Modified: Thursday, 20th June 2024 2:45:22 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 12-06-2024	0m3g4	adding OmegaWiFiController_reorder_stations
 *
 * 11-06-2024	0m3g4	added SavedStationList_t, OmegaWiFiController_get_saved_stations
 *
 * 11-06-2024	0m3g4	added StationStatusInformation_t
                        added station_state_changed
                        added OmegaWiFiController_get_current_connected_station
 *
 * 01-06-2024	0m3g4	build with __attribute__((weak)) for user callback for access points and scan results
 *
 * 01-06-2024	0m3g4	build with __attribute__((weak)) for user callback
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
        STA_CONNECTING,
        STA_CONNECTED,
        STA_DISCONNECTED,
        STA_AUTHENTICATION_FAILED,
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
        uint32_t ip_address;
        char ip_address_str[20 + 1];
    } IPData_t;

    typedef struct
    {
        char m_ssid[33 + 1];
        uint8_t m_mac_address[6];
    } AccessPoint_t;

    typedef struct
    {
        StationStatus status;
        union
        {
            char ssid[33 + 1];
            IPData_t ip_address;
        };
    } StationStatusInformation_t;

    typedef struct
    {
        char m_ssid[33 + 1];
        char m_password[64 + 1];
    } Station_t;

    typedef struct
    {
        Station_t stations[5];
        uint8_t station_count;
    } StationList_t;

    typedef uint64_t AccessPointHandle;
    typedef void (*sta_status_changed_cb_t)(StationStatus);
    typedef void (*ap_status_changed_cb_t)(APStatus);
    typedef void (*scan_result_cb_t)(AccessPoint_t *, size_t);

    __attribute__((weak)) void scan_result_callback(AccessPoint_t *, size_t);
    __attribute__((weak)) void station_state_changed(StationStatusInformation_t);
    __attribute__((weak)) void access_point_state_changed(APStatus);

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
    StationStatusInformation_t OmegaWiFiController_get_current_connected_station();
    StationList_t OmegaWiFiController_get_saved_stations();
    IPData_t OmegaWiFiController_get_ip_address();
    WiFiControllerStatus OmegaWiFiController_reorder_stations(const StationList_t in_new_stations);
    WiFiControllerStatus OmegaWiFiController_add_new_station(const Station_t in_new_station);

#ifdef __cplusplus
}
#endif

#endif