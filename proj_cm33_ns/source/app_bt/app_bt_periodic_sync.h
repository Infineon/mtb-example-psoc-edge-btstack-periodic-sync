/*******************************************************************************
* File Name: app_bt_periodic_sync.h
*
* Description: This file consists of the bt periodic sync function declarations
*
* Related Document: See README.md
*
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
#ifndef __APP_BT_PERIODIC_SYNC_H__
#define __APP_BT_PERIODIC_SYNC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * Header Files
 *******************************************************************************/
#include "wiced_bt_ble.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/
#define APP_BT_PERIODIC_ADV_HANDLE       (0x01U)
#define APP_BT_PERIODIC_ADV_SET_ID       (0x01U)
#define APP_BT_PERIODIC_ADV_SYNC_TIMEOUT (500U)
#define APP_BT_PERIODIC_ADV_INT_MIN      (0x00F0U)
#define APP_BT_PERIODIC_ADV_INT_MAX      (0x0190U)

/*******************************************************************************
 * FUNCTION DECLARATIONS
 ******************************************************************************/
void app_bt_periodic_sync_init(void);
void ext_scan_result_cback(wiced_ble_ext_scan_results_t *p_scan_result,
        uint16_t adv_data_len,
        uint8_t *p_adv_data);
void app_bt_start_periodic_sync(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __APP_BT_PERIODIC_SYNC_H__ */

/* [] END OF FILE */
