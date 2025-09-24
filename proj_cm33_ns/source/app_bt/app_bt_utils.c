/*******************************************************************************
* File Name: app_bt_utils.c
*
* Description: This file consists of the utility function definitions that will
*              help debugging and developing the applications easier with much
*              more meaningful information.
*
********************************************************************************
* Copyright 2024-2025, Cypress Semiconductor Corporation (an Infineon company) or
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
* Header Files
*******************************************************************************/
#include "app_bt_utils.h"
#include "wiced_bt_dev.h"
#include "cybt_platform_trace.h"
#include "cycfg_gap.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define COUNTER_INIT_VAL (0U)
#define BD_ADDR_INDEX_0  (0U)
#define BD_ADDR_INDEX_1  (1U)
#define BD_ADDR_INDEX_2  (2U)
#define BD_ADDR_INDEX_3  (3U)
#define BD_ADDR_INDEX_4  (4U)
#define BD_ADDR_INDEX_5  (5U)
#define BD_ADDR_INDEX_6  (6U)
#define BD_ADDR_INDEX_7  (7U)

#define CASE_DEFAULT_STR default:  \
    printf( "%s: defalut case\n", __FUNCTION__ ); break;

/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name: app_bt_util_print_bd_address
********************************************************************************
* Summary:
*  This is the utility function that prints the address of the
*  Bluetooth device
*
* Parameters:
*  wiced_bt_device_address_t bdadr: Bluetooth address
*
* Return:
*  None
*
*******************************************************************************/
void app_bt_util_print_bd_address(const wiced_bt_device_address_t bdadr)
{
    printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", bdadr[BD_ADDR_INDEX_0],
                                                bdadr[BD_ADDR_INDEX_1],
                                                bdadr[BD_ADDR_INDEX_2],
                                                bdadr[BD_ADDR_INDEX_3],
                                                bdadr[BD_ADDR_INDEX_4],
                                                bdadr[BD_ADDR_INDEX_5]);
}

/*******************************************************************************
* Function Name: app_bt_util_print_byte_array
********************************************************************************
* Summary:
*  This is a utility function that prints the specified number of
*  values from memory
*
* Parameters:
*  void* to_print       : Pointer to the location to print
*  uint16_t             : Number of bytes to print
*
* Return:
*  void
*
*******************************************************************************/
void app_bt_util_print_byte_array(void *to_print, uint16_t len)
{
    uint16_t counter;

    for (counter = COUNTER_INIT_VAL; counter < len; counter++)
    {
        if (COUNTER_INIT_VAL == counter % NUM_BYTES_PER_LINE)
        {
            printf("\n");
        }
        printf("%02X ", *(((uint8_t *)(to_print)) + counter));
    }
    printf("\n");
}

/*******************************************************************************
* Function Name: app_bt_util_get_btm_event_name
********************************************************************************
* Summary:
*  The function converts the wiced_bt_management_evt_t enum value to its
*  corresponding string literal. This will help the programmer to debug easily
*  with log traces without navigating through the source code.
*
* Parameters:
*  wiced_bt_management_evt_t event: Bluetooth management event type
*
* Return:
*  wiced_bt_management_evt_t
*
*******************************************************************************/
const char *app_bt_util_get_btm_event_name(wiced_bt_management_evt_t event)
{
    switch ((int)event)
    {
        CASE_RETURN_STR(BTM_ENABLED_EVT)
        CASE_RETURN_STR(BTM_DISABLED_EVT)
        CASE_RETURN_STR(BTM_POWER_MANAGEMENT_STATUS_EVT)
        CASE_RETURN_STR(BTM_PIN_REQUEST_EVT)
        CASE_RETURN_STR(BTM_USER_CONFIRMATION_REQUEST_EVT)
        CASE_RETURN_STR(BTM_PASSKEY_NOTIFICATION_EVT)
        CASE_RETURN_STR(BTM_PASSKEY_REQUEST_EVT)
        CASE_RETURN_STR(BTM_KEYPRESS_NOTIFICATION_EVT)
        CASE_RETURN_STR(BTM_PAIRING_IO_CAPABILITIES_BR_EDR_REQUEST_EVT)
        CASE_RETURN_STR(BTM_PAIRING_IO_CAPABILITIES_BR_EDR_RESPONSE_EVT)
        CASE_RETURN_STR(BTM_PAIRING_IO_CAPABILITIES_BLE_REQUEST_EVT)
        CASE_RETURN_STR(BTM_PAIRING_COMPLETE_EVT)
        CASE_RETURN_STR(BTM_ENCRYPTION_STATUS_EVT)
        CASE_RETURN_STR(BTM_SECURITY_REQUEST_EVT)
        CASE_RETURN_STR(BTM_SECURITY_FAILED_EVT)
        CASE_RETURN_STR(BTM_SECURITY_ABORTED_EVT)
        CASE_RETURN_STR(BTM_READ_LOCAL_OOB_DATA_COMPLETE_EVT)
        CASE_RETURN_STR(BTM_REMOTE_OOB_DATA_REQUEST_EVT)
        CASE_RETURN_STR(BTM_PAIRED_DEVICE_LINK_KEYS_UPDATE_EVT)
        CASE_RETURN_STR(BTM_PAIRED_DEVICE_LINK_KEYS_REQUEST_EVT)
        CASE_RETURN_STR(BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT)
        CASE_RETURN_STR(BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT)
        CASE_RETURN_STR(BTM_BLE_SCAN_STATE_CHANGED_EVT)
        CASE_RETURN_STR(BTM_BLE_ADVERT_STATE_CHANGED_EVT)
        CASE_RETURN_STR(BTM_SMP_REMOTE_OOB_DATA_REQUEST_EVT)
        CASE_RETURN_STR(BTM_SMP_SC_REMOTE_OOB_DATA_REQUEST_EVT)
        CASE_RETURN_STR(BTM_SMP_SC_LOCAL_OOB_DATA_NOTIFICATION_EVT)
        CASE_RETURN_STR(BTM_SCO_CONNECTED_EVT)
        CASE_RETURN_STR(BTM_SCO_DISCONNECTED_EVT)
        CASE_RETURN_STR(BTM_SCO_CONNECTION_REQUEST_EVT)
        CASE_RETURN_STR(BTM_SCO_CONNECTION_CHANGE_EVT)
        CASE_RETURN_STR(BTM_BLE_CONNECTION_PARAM_UPDATE)
        CASE_RETURN_STR(BTM_BLE_PHY_UPDATE_EVT)
        CASE_RETURN_STR(BTM_BLE_DATA_LENGTH_UPDATE_EVENT)
        CASE_DEFAULT_STR
    }
    return "UNKNOWN_EVENT";
}

/*******************************************************************************
 * Function Name: app_bt_util_get_ext_adv_event_name
 *******************************************************************************
 *
 * Summary:
 *         The function converts the wiced_bt_ble_adv_ext_event_t enum value to its
 *         corresponding string literal. This will help the programmer to debug
 *         easily with log traces without navigating through the source code.
 *
 * Parameters:
 * event: extern adv event type
 *
 * Return:
 * char*: String corresponding to the wiced_bt_ble_adv_ext_event_t event
 ******************************************************************************/
const char *app_bt_util_get_ext_adv_event_name(wiced_ble_ext_adv_event_t event)
{
    switch ((int)event)
    {
        CASE_RETURN_STR(WICED_BLE_PERIODIC_ADV_SYNC_ESTABLISHED_EVENT)
        CASE_RETURN_STR(WICED_BLE_PERIODIC_ADV_REPORT_EVENT)
        CASE_RETURN_STR(WICED_BLE_PERIODIC_ADV_SYNC_LOST_EVENT)
        CASE_RETURN_STR(WICED_BT_BLE_ADV_SET_TERMINATED_EVENT)
        CASE_RETURN_STR(WICED_BT_BLE_SCAN_REQUEST_RECEIVED_EVENT)
        CASE_RETURN_STR(BTM_BLE_CHANNEL_SELECTION_ALGO_EVENT)
        CASE_RETURN_STR(WICED_BT_BLE_BIGINFO_ADV_REPORT_EVENT)
        CASE_RETURN_STR(WICED_BLE_PERIODIC_ADV_SYNC_TRANSFER_EVENT)
        CASE_RETURN_STR(HCI_BLE_PAWR_SYNC_ESTABLISHED_EVT)
        CASE_RETURN_STR(WICED_BT_BLE_PAWR_SUBEVENT_DATA_REQ_EVENT)
        CASE_RETURN_STR(HCI_BLE_PAWR_IND_REPORT_EVT)
        CASE_RETURN_STR(WICED_BT_BLE_PAWR_RSP_REPORT_EVENT)
        CASE_DEFAULT_STR
    }
    return "UNKNOWN_EVENT";
}

/*******************************************************************************
* Function Name: app_bt_util_get_btm_advert_mode_name
********************************************************************************
* Summary:
*  The function converts the wiced_bt_ble_advert_mode_t enum value
*  to its corresponding string literal. This will help the programmer
*  to debug easily with log traces without navigating through the
*  source code.
*
* Parameters:
*  wiced_bt_ble_advert_mode_t mode: Bluetooth advertisement mode type
*
* Return:
*  wiced_bt_ble_advert_mode_t
*
*******************************************************************************/
const char *app_bt_util_get_btm_advert_mode_name(wiced_bt_ble_advert_mode_t mode)
{
    switch ((int)mode)
    {
        CASE_RETURN_STR(BTM_BLE_ADVERT_OFF)
        CASE_RETURN_STR(BTM_BLE_ADVERT_DIRECTED_HIGH)
        CASE_RETURN_STR(BTM_BLE_ADVERT_DIRECTED_LOW)
        CASE_RETURN_STR(BTM_BLE_ADVERT_UNDIRECTED_HIGH)
        CASE_RETURN_STR(BTM_BLE_ADVERT_UNDIRECTED_LOW)
        CASE_RETURN_STR(BTM_BLE_ADVERT_NONCONN_HIGH)
        CASE_RETURN_STR(BTM_BLE_ADVERT_NONCONN_LOW)
        CASE_RETURN_STR(BTM_BLE_ADVERT_DISCOVERABLE_HIGH)
        CASE_RETURN_STR(BTM_BLE_ADVERT_DISCOVERABLE_LOW)
        CASE_DEFAULT_STR
    }
    return "UNKNOWN_MODE";
}

/*******************************************************************************
* Function Name: app_bt_util_get_gatt_disconn_reason_name
********************************************************************************
* Summary:
*  The function converts the wiced_bt_gatt_disconn_reason_t enum value
*  to its corresponding string literal. This will help the programmer
*  to debug easily with log traces without navigating through the
*  source code.
*
* Parameters:
*  wiced_bt_gatt_disconn_reason_t reason: GATT Disconnection reason
*
* Return:
*  wiced_bt_gatt_disconn_reason_t
*
*******************************************************************************/
const char *app_bt_util_get_gatt_disconn_reason_name
                     (wiced_bt_gatt_disconn_reason_t reason)
{
    switch ((int)reason)
    {
        CASE_RETURN_STR(GATT_CONN_UNKNOWN)
        CASE_RETURN_STR(GATT_CONN_L2C_FAILURE)
        CASE_RETURN_STR(GATT_CONN_TIMEOUT)
        CASE_RETURN_STR(GATT_CONN_TERMINATE_PEER_USER)
        CASE_RETURN_STR(GATT_CONN_TERMINATE_LOCAL_HOST)
        CASE_RETURN_STR(GATT_CONN_FAIL_ESTABLISH)
        CASE_RETURN_STR(GATT_CONN_LMP_TIMEOUT)
        CASE_RETURN_STR(GATT_CONN_CANCEL)
        CASE_DEFAULT_STR
    }
    printf("Unknown Reason\r\n");
    return "UNKNOWN_REASON";
}

/*******************************************************************************
* Function Name: app_bt_util_get_gatt_status_name
********************************************************************************
* Summary:
*  The function converts the wiced_bt_gatt_status_t enum value
*  to its corresponding string literal. This will help the programmer to debug
*  easily with log traces without navigating through the source code.
*
* Parameters:
*  wiced_bt_gatt_status_t status: GATT status
*
* Return:
*  wiced_bt_gatt_status_t
*
*******************************************************************************/
const char *app_bt_util_get_gatt_status_name(wiced_bt_gatt_status_t status)
{
    switch ((int)status)
    {
        CASE_RETURN_STR(WICED_BT_GATT_SUCCESS || WICED_BT_GATT_ENCRYPTED_MITM)
        CASE_RETURN_STR(WICED_BT_GATT_INVALID_HANDLE)
        CASE_RETURN_STR(WICED_BT_GATT_READ_NOT_PERMIT)
        CASE_RETURN_STR(WICED_BT_GATT_WRITE_NOT_PERMIT)
        CASE_RETURN_STR(WICED_BT_GATT_INVALID_PDU)
        CASE_RETURN_STR(WICED_BT_GATT_INSUF_AUTHENTICATION)
        CASE_RETURN_STR(WICED_BT_GATT_REQ_NOT_SUPPORTED)
        CASE_RETURN_STR(WICED_BT_GATT_INVALID_OFFSET)
        CASE_RETURN_STR(WICED_BT_GATT_INSUF_AUTHORIZATION)
        CASE_RETURN_STR(WICED_BT_GATT_PREPARE_Q_FULL)
        CASE_RETURN_STR(WICED_BT_GATT_ATTRIBUTE_NOT_FOUND)
        CASE_RETURN_STR(WICED_BT_GATT_NOT_LONG)
        CASE_RETURN_STR(WICED_BT_GATT_INSUF_KEY_SIZE)
        CASE_RETURN_STR(WICED_BT_GATT_INVALID_ATTR_LEN)
        CASE_RETURN_STR(WICED_BT_GATT_ERR_UNLIKELY)
        CASE_RETURN_STR(WICED_BT_GATT_INSUF_ENCRYPTION)
        CASE_RETURN_STR(WICED_BT_GATT_UNSUPPORT_GRP_TYPE)
        CASE_RETURN_STR(WICED_BT_GATT_INSUF_RESOURCE)
        CASE_RETURN_STR(WICED_BT_GATT_ILLEGAL_PARAMETER)
        CASE_RETURN_STR(WICED_BT_GATT_NO_RESOURCES)
        CASE_RETURN_STR(WICED_BT_GATT_INTERNAL_ERROR)
        CASE_RETURN_STR(WICED_BT_GATT_WRONG_STATE)
        CASE_RETURN_STR(WICED_BT_GATT_DB_FULL)
        CASE_RETURN_STR(WICED_BT_GATT_BUSY)
        CASE_RETURN_STR(WICED_BT_GATT_ERROR)
        CASE_RETURN_STR(WICED_BT_GATT_CMD_STARTED)
        CASE_RETURN_STR(WICED_BT_GATT_PENDING)
        CASE_RETURN_STR(WICED_BT_GATT_AUTH_FAIL)
        CASE_RETURN_STR(WICED_BT_GATT_MORE)
        CASE_RETURN_STR(WICED_BT_GATT_INVALID_CFG)
        CASE_RETURN_STR(WICED_BT_GATT_SERVICE_STARTED)
        CASE_RETURN_STR(WICED_BT_GATT_ENCRYPTED_NO_MITM)
        CASE_RETURN_STR(WICED_BT_GATT_NOT_ENCRYPTED)
        CASE_RETURN_STR(WICED_BT_GATT_CONGESTED)
        CASE_RETURN_STR(WICED_BT_GATT_WRITE_REQ_REJECTED)
        CASE_RETURN_STR(WICED_BT_GATT_CCC_CFG_ERR)
        CASE_RETURN_STR(WICED_BT_GATT_PRC_IN_PROGRESS)
        CASE_RETURN_STR(WICED_BT_GATT_OUT_OF_RANGE)
        CASE_DEFAULT_STR
    }
    return "UNKNOWN_STATUS";
}

/*******************************************************************************
* Function Name: app_bt_util_get_pairing_status_name
********************************************************************************
* Summary:
*  The function converts the wiced_bt_smp_status_t enum value to its
*  corresponding string literal. This will help the programmer to debug easily
*  with log traces without navigating through the source code.
*
* Parameters:
*  wiced_bt_smp_status_t status: GATT status
*
* Return:
*  wiced_bt_smp_status_t
*
*******************************************************************************/
const char *app_bt_util_get_pairing_status_name(wiced_bt_smp_status_t status)
{
    switch ((int)status)
    {
        CASE_RETURN_STR(SMP_SUCCESS)                 /* Success */
        CASE_RETURN_STR(SMP_PASSKEY_ENTRY_FAIL)      /* Passkey entry failed */
        CASE_RETURN_STR(SMP_OOB_FAIL)                /* OOB failed */
        CASE_RETURN_STR(SMP_PAIR_AUTH_FAIL)          /* Authentication failed */
        CASE_RETURN_STR(SMP_CONFIRM_VALUE_ERR)       /* Value confirmation failed */
        CASE_RETURN_STR(SMP_PAIR_NOT_SUPPORT)        /* Not supported */
        CASE_RETURN_STR(SMP_ENC_KEY_SIZE)            /* Encryption key size
                                                      * failure */
        CASE_RETURN_STR(SMP_INVALID_CMD)             /* Invalid command */
        CASE_RETURN_STR(SMP_PAIR_FAIL_UNKNOWN)       /* Unknown failure */
        CASE_RETURN_STR(SMP_REPEATED_ATTEMPTS)       /* Repeated attempts */
        CASE_RETURN_STR(SMP_INVALID_PARAMETERS)      /* Invalid parameters  */
        CASE_RETURN_STR(SMP_DHKEY_CHK_FAIL)          /* DH Key check failed */
        CASE_RETURN_STR(SMP_NUMERIC_COMPAR_FAIL)     /* Numeric comparison failed */
        CASE_RETURN_STR(SMP_BR_PAIRING_IN_PROGR)     /* BR paIring in progress */
        CASE_RETURN_STR(SMP_XTRANS_DERIVE_NOT_ALLOW) /* Cross transport key
                                                      * derivation not allowed */
        /* bte smp status codes */
        CASE_RETURN_STR(SMP_PAIR_INTERNAL_ERR)       /* Internal error */
        CASE_RETURN_STR(SMP_UNKNOWN_IO_CAP)          /* unknown IO capability,
                                                      * unable to decide
                                                      * association model */
        CASE_RETURN_STR(SMP_INIT_FAIL)               /* Initialization failed */
        CASE_RETURN_STR(SMP_CONFIRM_FAIL)            /* Confirmation failed */
        CASE_RETURN_STR(SMP_BUSY)                    /* Busy */
        CASE_RETURN_STR(SMP_ENC_FAIL)                /* Encryption failed */
        CASE_RETURN_STR(SMP_STARTED)                 /* Started */
        CASE_RETURN_STR(SMP_RSP_TIMEOUT)             /* Response timeout */
        CASE_RETURN_STR(SMP_FAIL)                    /* Generic failure */
        CASE_RETURN_STR(SMP_CONN_TOUT)               /* Connection timeout */
        CASE_DEFAULT_STR
    }
    return "UNKNOWN_STATUS";
}

/*******************************************************************************
* Function Name: app_bt_util_print_local_identity_key
********************************************************************************
* Summary:
*  Prints the given identity key
*
* Parameters:
*  st: Address of the location to print from
*  p_identity_key: pointer to identity key
*
* Return:
*  void
*
*******************************************************************************/
void app_bt_util_print_local_identity_key(char *st,
        wiced_bt_local_identity_keys_t *p_identity_key)
{
    printf("%s local identity key\n", st);
    if (p_identity_key->key_type_mask == BTM_BLE_KEY_TYPE_ID)
    {
        printf("key type: %d (Identity resolving key)\n", p_identity_key
                ->key_type_mask);
    }
    else if (p_identity_key->key_type_mask == BTM_BLE_KEY_TYPE_ER)
    {
        printf("key type: %d (Encryption root key)\n", p_identity_key
                ->key_type_mask);
    }
    else
    {
        printf("key type: %d (unknown)\n", p_identity_key->key_type_mask);
    }
    printf("   ir: ");
    app_bt_util_print_byte_array(p_identity_key->id_keys.ir, LINK_KEY_LEN);
    printf("  irk: ");
    app_bt_util_print_byte_array(p_identity_key->id_keys.irk, LINK_KEY_LEN);
    printf("  dhk: ");
    app_bt_util_print_byte_array(p_identity_key->id_keys.dhk, LINK_KEY_LEN);
    printf("   er: ");
    app_bt_util_print_byte_array(p_identity_key->er, LINK_KEY_LEN);
}

/*******************************************************************************
* Function Name: app_bt_util_print_link_key_data
********************************************************************************
* Summary:
*  Prints the given link key data
*
* Parameters:
*  p_key: pointer to link key
*
* Return:
*  void
*
*******************************************************************************/
void app_bt_util_print_link_key_data(wiced_bt_device_sec_keys_t *p_key)
{
    printf("key mask: %02X\n", p_key->le_keys_available_mask);
    printf("add type: %d\n", p_key->ble_addr_type);
    printf("     irk: ");
    app_bt_util_print_byte_array(p_key->le_keys.irk, LINK_KEY_LEN);
    printf("    pltk: ");
    app_bt_util_print_byte_array(p_key->le_keys.pltk, LINK_KEY_LEN);
    printf("   pcsrk: ");
    app_bt_util_print_byte_array(p_key->le_keys.pcsrk, LINK_KEY_LEN);
    printf("    lltk: ");
    app_bt_util_print_byte_array(p_key->le_keys.lltk, LINK_KEY_LEN);
    printf("   lcsrk: ");
    app_bt_util_print_byte_array(p_key->le_keys.lcsrk, LINK_KEY_LEN);
}

/*******************************************************************************
* Function Name: app_bt_util_generate_bd_address
********************************************************************************
* Summary:
*  Function used to generate unique BD Address for the device
*
* Parameters:
*  device_addr: pointer to read device address structure
*
* Return:
*  void
*
*******************************************************************************/
void app_bt_util_generate_bd_address(const uint8_t *device_addr)
{
    printf("BD Address 0x%x%x%x%x%x%x%x%x \r\n",
           device_addr[BD_ADDR_INDEX_0], device_addr[BD_ADDR_INDEX_1],
           device_addr[BD_ADDR_INDEX_2], device_addr[BD_ADDR_INDEX_3],
           device_addr[BD_ADDR_INDEX_4], device_addr[BD_ADDR_INDEX_5],
           device_addr[BD_ADDR_INDEX_6], device_addr[BD_ADDR_INDEX_7]);
}

/* [] END OF FILE */
