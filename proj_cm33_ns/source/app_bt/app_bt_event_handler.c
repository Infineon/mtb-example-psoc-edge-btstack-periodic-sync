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
* (c) 2023-2025, Infineon Technologies AG, or an affiliate of Infineon Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is owned by
* Infineon Technologies AG or one of its affiliates ("Infineon") and is protected
* by and subject to worldwide patent protection, worldwide copyright laws, and
* international treaty provisions. Therefore, you may use this Software only as
* provided in the license agreement accompanying the software package from which
* you obtained this Software. If no license agreement applies, then any use,
* reproduction, modification, translation, or compilation of this Software is
* prohibited without the express written permission of Infineon.
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF THIRD-PARTY RIGHTS AND
* IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A SPECIFIC USE/PURPOSE OR
* MERCHANTABILITY. Infineon reserves the right to make changes to the Software
* without notice. You are responsible for properly designing, programming, and
* testing the functionality and safety of your intended application of the
* Software, as well as complying with any legal requirements related to its
* use. Infineon does not guarantee that the Software will be free from intrusion,
* data theft or loss, or other breaches ("Security Breaches"), and Infineon
* shall have no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any application
* where a failure of the Product or any consequences of the use thereof can
* reasonably be expected to result in personal injury.
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
