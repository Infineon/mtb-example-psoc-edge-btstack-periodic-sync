/*******************************************************************************
* File Name: app_bt_periodic_sync.c
*
* Description: This file consists of the bt periodic advertise sync function
*              definitions
*
* Related Document: See README.md
*
*
********************************************************************************
* (c) 2023-2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
/* FreeRTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "timers.h"
#include "stdio.h"
#include "app_bt_periodic_sync.h"
#include "cy_syslib.h"
#include "app_bt_utils.h"
#include "wiced_bt_adv_scan_extended.h"
#include "wiced_bt_adv_scan_periodic.h"
#include "wiced_bt_types.h"
#include "retarget_io_init.h"

/*******************************************************************************
* Defines
*******************************************************************************/
#define HCI_BLE_EVENT_MASK_DEF_NEW "\x00\x00\x00\x00\x7F\xff\xff\xff"
#define PERIODIC_SYNC_START_TIME_VALUE (2000U)
#define TIMER_TICKS_TO_WAIT            (10U)
#define MAX_EXT_ADV_LEN                (300U)
#define MAX_PER_ADV_LEN                (300U)
#define MAX_EXT_SCAN_LEN               (300U)
#define SCAN_DURATION                  (0U)
#define SCAN_PERIOD                    (0U)
#define SYNC_TYPE                      (0U)
#define EVENTS_SKIP                    (0U)
#define ADV_ADDR_0                     (0x20U)
#define ADV_ADDR_1                     (0x82U)
#define ADV_ADDR_2                     (0x9BU)
#define ADV_ADDR_3                     (0x1U)
#define ADV_ADDR_4                     (0x22U)
#define ADV_ADDR_5                     (0x33U)
#define DATA_LENGTH_INIT_VAL           (0U)
#define SCAN_ENABLE                    (1U)
#define SCAN_DISABLE                   (0U)
#define DATA_INDEX                     (0U)

/******************************************************************************
 * Global Variables
 ******************************************************************************/
static TimerHandle_t periodic_sync_start_timer = NULL;
wiced_bt_device_address_t peer_bda = {ADV_ADDR_0, ADV_ADDR_1, ADV_ADDR_2,
        ADV_ADDR_3, ADV_ADDR_4,ADV_ADDR_5};
wiced_ble_ext_scan_params_t scan_params =
{
    .own_addr_type = BLE_ADDR_PUBLIC,
    .scanning_phys = WICED_BLE_EXT_ADV_PHY_1M_BIT,
    .scan_filter_policy = WICED_BLE_SCAN_BASIC_UNFILTERED_SP,
    .sp_1m.scan_type = BTM_BLE_SCAN_MODE_PASSIVE,
    .sp_1m.scan_interval = WICED_BT_CFG_DEFAULT_HIGH_DUTY_SCAN_INTERVAL,
    .sp_1m.scan_window = WICED_BT_CFG_DEFAULT_HIGH_DUTY_SCAN_WINDOW
};
wiced_ble_ext_scan_enable_params_t scan_enable =
{
    .scan_duration =SCAN_DURATION,
    .scan_period = SCAN_PERIOD
};
wiced_ble_padv_create_sync_params_t sync_par =
{
    .options = WICED_BLE_PADV_CREATE_SYNC_OPTION_IGNORE_PA_LIST,
    .adv_sid = APP_BT_PERIODIC_ADV_SET_ID,
    .adv_addr_type = BLE_ADDR_PUBLIC,
    .adv_addr= {ADV_ADDR_0, ADV_ADDR_1, ADV_ADDR_2, ADV_ADDR_3, ADV_ADDR_4,
                ADV_ADDR_5},
    .skip= EVENTS_SKIP,
    .sync_timeout = APP_BT_PERIODIC_ADV_SYNC_TIMEOUT,
    .sync_cte_type = SYNC_TYPE,
};

/*******************************************************************************
* Function Definitions
*******************************************************************************/
/*******************************************************************************
* Function Name: ext_scan_result_cback
********************************************************************************
* Summary:
* This function is called when an ADV is received. This will typically
* only sync with periodic adv
*
* Parameters:
* p_scan_result  scan result
* adv_data_len   Adv data length
* p_adv_data     Extra adv data
*
* Return:
* void
*******************************************************************************/
void ext_scan_result_cback(wiced_ble_ext_scan_results_t *p_scan_result,
        uint16_t adv_data_len,
        uint8_t *p_adv_data)
{
    if (p_scan_result != NULL)
    {
        printf("[%s]  rssi:%i\n", __FUNCTION__, p_scan_result->rssi);
    }
}

/*******************************************************************************
* Function Name: ext_adv_callback
********************************************************************************
* Summary:
*  Process Extended ADV events
*
* Parameters:
*  event      The event code
*  p_data     Event-specific supporting data
*
* Return:
*  void
*******************************************************************************/
static void ext_adv_callback(wiced_ble_ext_adv_event_t event,
        wiced_ble_ext_adv_event_data_t *p_data)
{
    uint8_t data_len = DATA_LENGTH_INIT_VAL;
    printf("[%s]  event: %s\n", __FUNCTION__,
            app_bt_util_get_ext_adv_event_name(event));
    switch (event)
    {
    case WICED_BLE_PERIODIC_ADV_SYNC_ESTABLISHED_EVENT:
        printf("[%s] PERIODIC_ADV_SYNC_ESTABLISHED_EVENT\n", __FUNCTION__);
        wiced_ble_ext_scan_enable(SCAN_DISABLE,&scan_enable);
        break;

    case WICED_BLE_PERIODIC_ADV_REPORT_EVENT:
        data_len = p_data->periodic_adv_report.data_length;
        if (DATA_LENGTH_INIT_VAL < data_len )
        {
            printf("[%s] PERIODIC_ADV_REPORT_EVENT, len:%d, "
                    "rssi:%i, content:%d...\n", __FUNCTION__, data_len,
                    p_data->periodic_adv_report.rssi, p_data->
                    periodic_adv_report.p_data[DATA_INDEX]);
        }
        else
        {
            printf("[%s] PERIODIC_ADV_REPORT_EVENT, len:%d, rssi:%i\n"
                    , __FUNCTION__, data_len,
                    p_data->periodic_adv_report.rssi);
        }
        break;

    case WICED_BLE_PERIODIC_ADV_SYNC_LOST_EVENT:
        printf("[%s] PERIODIC_ADV_SYNC_LOST_EVENT, re-sync again\n"
               , __FUNCTION__);
        memcpy(sync_par.adv_addr, peer_bda, BD_ADDR_LEN);
        wiced_ble_padv_create_sync (&sync_par);
        wiced_ble_ext_scan_enable(SCAN_ENABLE,&scan_enable);
        break;

    case WICED_BT_BLE_PAWR_SUBEVENT_DATA_REQ_EVENT:
        printf("[%s] PAWR_SYNC_ESTABLISHED_EVENT\n", __FUNCTION__);
        wiced_ble_ext_scan_enable(SCAN_DISABLE,&scan_enable);
        break;

    case WICED_BT_BLE_PAWR_RSP_REPORT_EVENT:
        data_len = p_data->pawr_rsp_report.data_length;
        if (DATA_LENGTH_INIT_VAL < data_len )
        {
            printf("[%s] PAWR_IND_REPORT_EVENT, len:%d, rssi:%i, "
             "content:%d...\n", __FUNCTION__, p_data->pawr_rsp_report.data_length,
             p_data->pawr_rsp_report.rssi, p_data->periodic_adv_report.
             p_data[DATA_INDEX]);
        }
        else
        {
            printf("[%s] PAWR_IND_REPORT_EVENT, len:%d, rssi:%i\n",
                    __FUNCTION__, p_data->pawr_rsp_report.data_length,
                    p_data->pawr_rsp_report.rssi);
        }
        break;

    default:
        break;
    }
}

/*******************************************************************************
* Function Name: app_bt_periodic_sync_start_cb
********************************************************************************
* Summary:
*  Callback to set parameters for the periodic synchronizer
*
* Parameters:
*  TimerHandle_t : Timer handle parameters
*
* Return:
*  void
******************************************************************************/
void app_bt_periodic_sync_start_cb(TimerHandle_t cb_params)
{
    wiced_bt_dev_status_t status;

    /* Set extended scan configuration */
    status = wiced_ble_ext_scan_register_cb(ext_scan_result_cback);
    if (WICED_SUCCESS != status)
    {
        printf("Error configuring extended scan\n");
        handle_app_error();
    }

    /* Register for extended ADV events */
    wiced_ble_ext_adv_register_cback(ext_adv_callback);

    /* set extended scan parameters */
    status = wiced_ble_ext_scan_set_params(&scan_params);
    if (WICED_SUCCESS != status)
    {
        printf("Error setting extended scan parameters\n");
        handle_app_error();
    }

    /* Disable extended scan */
    status = wiced_ble_ext_scan_enable(SCAN_DISABLE,&scan_enable);
    if (WICED_SUCCESS != status)
    {
        printf("Error disabling extended scan\n");
        handle_app_error();
    }

    /* Start periodic sync */
    app_bt_start_periodic_sync();
    app_bt_util_print_bd_address(peer_bda);

    /* set extended scan enable */
    status = wiced_ble_ext_scan_enable(SCAN_ENABLE,&scan_enable);
    if (WICED_SUCCESS == status)
    {
        printf("[%s] wiced_ble_ext_scan_enable status:"
            "%d\n", __FUNCTION__, status);
    }
    else
    {
        printf("[%s] wiced_ble_ext_scan_enable status:"
            "%d\n", __FUNCTION__, status);
        handle_app_error();
    }
}

/*******************************************************************************
* Function Name:   app_bt_periodic_sync_init
********************************************************************************
* Summary:
*  Creare and start periodic sync.
*******************************************************************************/
void app_bt_start_periodic_sync(void)
{
    wiced_bt_dev_status_t status;
    memcpy(sync_par.adv_addr, peer_bda, BD_ADDR_LEN);
    status = wiced_ble_padv_add_device_to_list(BLE_ADDR_PUBLIC, peer_bda,
           APP_BT_PERIODIC_ADV_SET_ID);
    if (WICED_SUCCESS != status)
    {
        printf("Error adding device to Periodic Advertiser list\n");
        handle_app_error();
    }
    status = wiced_ble_padv_create_sync (&sync_par);
    if (WICED_SUCCESS == status)
    {
        printf("[%s] wiced_ble_padv_create_sync Result: %d BDA: \n",
            __FUNCTION__, status);
    }
    else
    {
        printf("[%s] wiced_ble_padv_create_sync Result: %d BDA: \n",
            __FUNCTION__, status);
        handle_app_error();
    }
}

/*******************************************************************************
* Function Name:   app_bt_periodic_sync_init
********************************************************************************
* Summary:
*  Initialize ble periodic sync, fire a 2s timer to start the periodic sync.
*******************************************************************************/
void app_bt_periodic_sync_init(void)
{
    periodic_sync_start_timer = xTimerCreate("Simulate Sensor Timer",
                                             PERIODIC_SYNC_START_TIME_VALUE,
                                             pdFALSE,
                                             NULL,
                                             app_bt_periodic_sync_start_cb);

    if (periodic_sync_start_timer != NULL && pdPASS !=
            xTimerStart(periodic_sync_start_timer, TIMER_TICKS_TO_WAIT))
    {
        printf("Failed to start periodic_sync_start_timer!\n");
        handle_app_error();
    }
}

/* END OF FILE [] */
