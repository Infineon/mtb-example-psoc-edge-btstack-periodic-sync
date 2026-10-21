/*******************************************************************************
* File Name: app_bt_event_handler.h
*
* Description:
* This file contains the interfaces for application procedure to handle the
* Bluetooth events in Bluetooth Management callback. The Bluetooth Management
* callback acts like a Finite State Machine (FSM) for the SoC.
*
* Related Document: See README.md
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
#ifndef __APP_BT_TASK_H__
#define __APP_BT_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "cycfg_gatt_db.h"
#include "cycfg_gap.h"
#include "cycfg_bt_settings.h"
#include "cyabs_rtos.h"
#include "app_bt_utils.h"
#include "wiced_bt_ble.h"
#include "wiced_bt_uuid.h"
#include "wiced_memory.h"
#include "wiced_bt_stack.h"
#include "wiced_bt_dev.h"
#include "wiced_bt_l2c.h"
#include <task.h>
#include "timers.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
/* Status variable for connection ID */
extern uint16_t app_bt_conn_id;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
/* Callback function for Bluetooth stack management type events */
wiced_bt_dev_status_t
app_bt_event_management_callback(wiced_bt_management_evt_t event,
                                 wiced_bt_management_evt_data_t *p_event_data);
void hci_trace_cback(wiced_bt_hci_trace_type_t type, uint16_t length,
        uint8_t *p_data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __APP_BT_TASK_H__ */
