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
    typedef void (*sta_connected_cb_t)(void);
    typedef void (*sta_disconnected_cb_t)(void);
    typedef void (*sta_got_ip_cb_t)(void);
    typedef void (*ap_assigned_ip_cb_t)(void);
    typedef void (*scan_result_cb_t)(AccessPoint_t *, size_t);

    WiFiControllerStatus OmegaWiFiController_initialize(WiFiControllerMode in_mode);
    WiFiControllerStatus OmegaWiFiController_deinitialize();
    WiFiControllerStatus OmegaWiFiController_set_sta_provisioning(const char *in_ssid, const char *in_password);
    WiFiControllerStatus OmegaWiFiController_set_ap_provisioning(const char *in_ssid, const char *in_password);
    WiFiControllerStatus OmegaWiFiController_start();
    WiFiControllerStatus OmegaWiFiController_start_scan();
    WiFiControllerStatus OmegaWiFiController_set_scan_result_callback(scan_result_cb_t in_scan_result_cb);

#ifdef __cplusplus
}
#endif

#endif