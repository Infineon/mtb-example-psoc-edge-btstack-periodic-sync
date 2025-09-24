/*******************************************************************************
* File Name: app_bt_periodic_sync.h
*
* Description: This file consists of the bt periodic sync function declarations
*
* Related Document: See README.md
*
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
