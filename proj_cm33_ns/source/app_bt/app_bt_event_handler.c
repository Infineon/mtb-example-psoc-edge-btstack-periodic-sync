/*******************************************************************************
* File Name: app_bt_event_handler.c
*
* Description:
* This file contains the starting point of Bluetooth LE Periodic Sync application.
* The wiced_bt_stack_init() registers for Bluetooth events in this main function.
* The Bluetooth Management callback manages the Bluetooth events and the
* application developer can customize the functionality and behavior depending on
* the Bluetooth events. The Bluetooth Management callback acts like a
* Finite State Machine (FSM) for the SoC.
*
* Related Document: See README.md
*
********************************************************************************
* Copyright 2023-2025, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/
#include "stdio.h"
#include "app_bt_event_handler.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_ble.h"
#include "app_bt_periodic_sync.h"
#ifdef ENABLE_BT_SPY_LOG
#include "cybt_debug_uart.h"
#endif

/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name: app_bt_event_management_callback
********************************************************************************
* Summary:
*  This is a Bluetooth stack event handler function to receive
*  management events from the LE stack and process as per the application.
*
* Parameters:
*  wiced_bt_management_evt_t event             : LE event code of
*                                                one byte length
*  wiced_bt_management_evt_data_t *p_event_data: Pointer to LE
*                                                management event structures
*
* Return:
*  wiced_result_t                          : Error code from
*                                          WICED_RESULT_LIST or BT_RESULT_LIST
*
*******************************************************************************/
wiced_result_t
app_bt_event_management_callback(wiced_bt_management_evt_t event,
                                 wiced_bt_management_evt_data_t *p_event_data)
{
    wiced_bt_dev_status_t bt_dev_status = WICED_SUCCESS;
    printf("\nBluetooth Management Event: %d,\t:%s\r\n", event,
            app_bt_util_get_btm_event_name(event));
    switch (event)
    {
    case BTM_ENABLED_EVT:

        /* Perform application-specific initialization */
#ifdef ENABLE_BT_SPY_LOG
        wiced_bt_dev_register_hci_trace(hci_trace_cback);
#endif
        /* Sync to Periodic Advertisement Init */
        app_bt_periodic_sync_init();

        break;

    case BTM_BLE_ADVERT_STATE_CHANGED_EVT:
        break;

    case BTM_SECURITY_REQUEST_EVT:
        /* Need to compare with BT-SDK remote here for this event */
        wiced_bt_ble_security_grant(p_event_data->security_request.bd_addr,
                WICED_BT_SUCCESS);
        break;

    case BTM_PAIRING_IO_CAPABILITIES_BLE_REQUEST_EVT:
        break;

    case BTM_PIN_REQUEST_EVT:
        break;

    case BTM_PASSKEY_REQUEST_EVT:
        break;

    case BTM_PAIRED_DEVICE_LINK_KEYS_REQUEST_EVT:
        break;

    case BTM_PAIRED_DEVICE_LINK_KEYS_UPDATE_EVT:
        break;

    case BTM_PAIRING_COMPLETE_EVT:
        break;

    case BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT:
        printf("Local Identity Key Update\n");
        break;

    case BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT:
        break;

    case BTM_ENCRYPTION_STATUS_EVT:
        break;

    case BTM_BLE_CONNECTION_PARAM_UPDATE:

        break;

    case BTM_SECURITY_FAILED_EVT:
        /* Handle pairing Failure */
        printf("Pairing Failed\r\n");
        break;

    case BTM_BLE_PHY_UPDATE_EVT:
        printf("BTM_BLE_PHY_UPDATE_EVT,\r\n "
               "PHY Tx value is: %d, \r\n"
               "PHY Rx value is: %d \r\n",
               p_event_data->ble_phy_update_event.tx_phy,
               p_event_data->ble_phy_update_event.rx_phy);
        break;

    case BTM_DISABLED_EVT:
        /* Bluetooth Controller and Host Stack Disabled */
        printf("BTM_DISABLED_EVT\r\n");
        break;

    case BTM_BLE_DATA_LENGTH_UPDATE_EVENT:
        printf("BTM_BLE_DATA_LENGTH_UPDATE_EVENT, \r\n"
               "Max tx octets is :%d ,\r\n"
               "Max rx octets is :%d \r\n",
               p_event_data->ble_data_length_update_event.max_tx_octets,
               p_event_data->ble_data_length_update_event.max_rx_octets);
        break;

    default:
        printf("\nUnhandled Bluetooth Management Event: %d\r\n", event);
        break;
    }
    return (bt_dev_status);
}

/*******************************************************************************
* Function Name: hci_trace_cback
********************************************************************************
* Summary:
*  This callback routes HCI packets to debug uart.
*
* Parameters:
*  wiced_bt_hci_trace_type_t type : HCI trace type
*  uint16_t length : length of p_data
*  uint8_t* p_data : pointer to data
*
* Return:
*  None
*
*******************************************************************************/
#ifdef ENABLE_BT_SPY_LOG
void hci_trace_cback(wiced_bt_hci_trace_type_t type,
                     uint16_t length, uint8_t *p_data)
{
    cybt_debug_uart_send_hci_trace(type, length, p_data);
}
#endif

/* END OF FILE [] */
