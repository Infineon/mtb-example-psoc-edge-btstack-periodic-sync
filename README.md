# PSOC&trade; Edge MCU:  Bluetooth&reg; LE periodic sync

This code example demonstrates the implementation of a Bluetooth&reg; LE periodic advertiser sync functionality using an Arm&reg; Cortex&reg;-M33 CPU on PSOC&trade; Edge MCU coupled with AIROC&trade; CYW55513 Wi-Fi & Bluetooth&reg; combo chip in the ModusToolbox&trade; software environment.

This code example has a three project structure: CM33 secure, CM33 non-secure, and CM55 projects. All three projects are programmed to the external QSPI flash and executed in Execute in Place (XIP) mode. Extended boot launches the CM33 secure project from a fixed location in the external flash, which then configures the protection settings and launches the CM33 non-secure application. Additionally, CM33 non-secure application enables CM55 CPU and launches the CM55 application.

[View this README on GitHub.](https://github.com/Infineon/mtb-example-psoc-edge-btstack-periodic-sync)

[Provide feedback on this code example.](https://yourvoice.infineon.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyNDE4NjUiLCJTcGVjIE51bWJlciI6IjAwMi00MTg2NSIsIkRvYyBUaXRsZSI6IlBTT0MmdHJhZGU7IEVkZ2UgTUNVOiAgQmx1ZXRvb3RoJnJlZzsgTEUgcGVyaW9kaWMgc3luYyIsInJpZCI6ImFydmluZGt1bWFyLnN1cmVzaGt1bWFyQGluZmluZW9uLmNvbSIsIkRvYyB2ZXJzaW9uIjoiMi4xLjAiLCJEb2MgTGFuZ3VhZ2UiOiJFbmdsaXNoIiwiRG9jIERpdmlzaW9uIjoiTUNEIiwiRG9jIEJVIjoiSUNXIiwiRG9jIEZhbWlseSI6IlBTT0MifQ==)

See the [Design and implementation](docs/design_and_implementation.md) for the functional description of this code example.


## Requirements

- [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) v3.7 or later (tested with v3.9)
- Board support package (BSP) minimum required version: 1.4.0
- Programming language: C
- Associated parts: All [PSOC&trade; Edge MCU](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm) parts


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v14.2.1 (`GCC_ARM`) – Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.22 (`ARM`)
- IAR C/C++ Compiler v9.70.4 (`IAR`)
- LLVM Embedded Toolchain for Arm&reg; v19.1.5 (`LLVM_ARM`)


## Supported kits (make variable 'TARGET')

- [PSOC&trade; Edge E84 Evaluation Kit](https://www.infineon.com/KIT_PSE84_EVAL) (`KIT_PSE84_EVAL_EPC2`) – Default value of `TARGET`
- [PSOC&trade; Edge E84 Evaluation Kit](https://www.infineon.com/KIT_PSE84_EVAL) (`KIT_PSE84_EVAL_EPC4`)


## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

Ensure the following jumper and pin configuration on board.
- BOOT SW must be in the HIGH/ON position
- J20 and J21 must be in the tristate/not connected (NC) position

To verify the output, two PSOC&trade; Edge E84 Evaluation Kits are required: One for Bluetooth&reg; LE periodic advertisement and the other for Bluetooth&reg; LE periodic sync.

Program the [PSOC&trade; Edge MCU: Bluetooth&reg; LE periodic advertisement](https://github.com/Infineon/mtb-example-psoc-edge-btstack-periodic-adv) code example to run as Bluetooth&reg; LE periodic advertisement on the second kit.


## Software setup

See the [ModusToolbox&trade; tools package installation guide](https://www.infineon.com/ModusToolboxInstallguide) for information about installing and configuring the tools package.

Install a terminal emulator if you do not have one. Instructions in this document use [Tera Term](https://teratermproject.github.io/index-en.html).

This example requires no additional software or tools.


## Operation

See [Using the code example](docs/using_the_code_example.md) for instructions on creating a project, opening it in various supported IDEs, and performing tasks, such as building, programming, and debugging the application within the respective IDEs.

This code example requires to program the [PSOC&trade; Edge MCU: Bluetooth&reg; LE periodic advertisement](https://github.com/Infineon/mtb-example-psoc-edge-btstack-periodic-adv) application on another PSOC&trade; Edge E84 Evaluation Kit.

1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector

2. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud

3. After programming, the application starts automatically. Observe the messages on the UART terminal and wait for the device to be synced with the peer advertiser [PSOC&trade; Edge MCU: Bluetooth&reg; LE periodic advertisement](https://github.com/Infineon/mtb-example-psoc-edge-btstack-periodic-adv). Use the KitProg3 COM port to view the Bluetooth&reg; stack and application trace messages in the terminal window:

   **Figure 1. Log messages on KitProg3 COM port**

   ![](images/terminal-le-periodic-sync.png)

   The sync device prints the simulated data synced with the advertiser with an interval of 500 milliseconds

   **Figure 2. Sync side receive the peer periodic advertisement data log message**

   ![](images/terminal-le-periodic-sync-receive-log-message.png)


## Enable BTSpy logs

1. **airoc-hci-transport** library is required to enable BTSpy logs. Open Library Manager from Quick Panel, click on Add Library, and add **airoc-hci-transport** under **proj_cm33_ns** as shown in **Figure 3** and click **OK** to update

   **Figure 3. Add hci-airoc-transport library**

   ![](./images/airoc-hci-transport.png)

2. Delete **retarget_io** library from the mtb-shared folder using Library Manager tool.

3. Navigate to the application *Makefile* inside the *proj_cm33_ns*. Find the *Makefile* variable `ENABLE_SPY_TRACES` and set it to the value *1* as shown:
```
ENABLE_SPY_TRACES = 1
```
4. Open Device Configurator from the Quick Panel and make the following modifications for **Serial Communication Block (SCB) 2** (under **Peripheral** section) as shown in **Figure 4**
   - Change the **Oversample** value to '8'
   - Select **Enable flow control** to turn on flow control
   - Select the **Clock** as "16.5 bit Divider 0 clk (CYBSP_BT_UART_CLK_DIV)"
   - Select appropriate CTS and RTS pins

   **Figure 4. Enable Flow Control in Debug UART**

   ![](./images/airoc-hci-transport1.png)

5. Save the *Makefile* and Device Configurator. Then build and program the application to the board

6. Download and launch the [BTSpy](https://github.com/Infineon/btsdk-utils/tree/master/BTSpy) tool

7. Click on serial port setup and select **Enable Serial Port**. Then select the correct baudrate, port number, and enable hardware flow control as shown in **Figure 5**

   **Figure 5. Enable BTSpy logs**

   ![](./images/btspy.png)

8. Press and release the reset button (XRES) on the board to get the BTSpy logs on the BTSpy tool

   **Figure 6. BTSpy logs**

   ![](./images/btspy-logs.png)

9. For more traces, call the following function in `application main()`

```
cybt_platform_set_trace_level(CYBT_TRACE_ID_STACK,CYBT_TRACE_LEVEL_DEBUG);
```
This function is defined in *cybt_platform_trace.c* in [btstack-integration](https://github.com/Infineon/btstack-integration) <br>
Set the trace category ID and trace level as per the requirement

> **Note:** Revert back the changes done in **Step 2** , **Step3** (add retarget_io library back using Library Manager tool) and **Step 4** and delete the **airoc-hci-transport** library using the Library Manager tool to switch back to Debug UART logs from BTSpy logs

### Additional steps for other Bluetooth&reg; Low Energy applications 

Perform the below steps additionally for other code examples. This is already implemented in this (BLE Hello Sensor) code example.

1. Make sure to remove retarget_io related files and header informations from your application

2. Add the below code in the main.c file of CM33_NS project by replacing the existing retarget_io initialization.

``` 
#ifdef ENABLE_BT_SPY_LOG
#include "cybt_debug_uart.h"
#endif 

#ifdef ENABLE_BT_SPY_LOG
cybt_debug_uart_config_t config =
{
   .baud_rate = DEBUG_UART_BAUDRATE,
   .flow_control = TRUE
};
cybt_debug_uart_init(&config, NULL);
#else
/* Initialize retarget-io middleware */
init_retarget_io();
#endif
```
 
3. Add the below code in event_handler implementation file. In this case it is app_bt_event_handler.c file

```
#ifdef ENABLE_BT_SPY_LOG
#include "cybt_debug_uart.h"
#endif

#ifdef ENABLE_BT_SPY_LOG
void hci_trace_cback(wiced_bt_hci_trace_type_t type, uint16_t length, 
uint8_t* p_data)
{
   cybt_debug_uart_send_hci_trace(type, length, p_data);
}
#endif

/* place the below code inside app_bt_application_init()   
   or similar function */

#ifdef ENABLE_BT_SPY_LOG
wiced_bt_dev_register_hci_trace(hci_trace_cback);
#endif
```
4. Add the below define in the makefile of CM33_NS project. 

```
# Optionally enable app and Bluetooth protocol traces and route to BTSpy
ENABLE_SPY_TRACES = 1
ifeq ($(ENABLE_SPY_TRACES),1)
DEFINES+=ENABLE_BT_SPY_LOG DEBUG_UART_BAUDRATE=3000000
else
DEFINES+=ENABLE_AIROC_HCI_TRANSPORT_PRINTF=0
endif
```

   
## Resources and settings

This section explains the ModusToolbox&trade; software resources and their configurations as used in this code example. Note that all the configuration explained in this section has already been implemented in the code example.

- **Bluetooth&reg; Configurator:** The Bluetooth&reg; peripheral has a configurator called the “Bluetooth&reg; Configurator” that is used to generate the Bluetooth&reg; LE GATT database and various Bluetooth&reg; settings for the application. These settings are stored in the file named *design.cybt*.

See the [Bluetooth&reg; Configurator guide](https://www.infineon.com/ModusToolboxBLEConfig) for more details.


## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN235935](https://www.infineon.com/AN235935) – Getting started with PSOC&trade; Edge E8 MCU on ModusToolbox&trade; software <br> [AN236697](https://www.infineon.com/AN236697) – Getting started with PSOC&trade; MCU and AIROC&trade; Connectivity devices <br>
Code examples  | [Using ModusToolbox&trade;](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [PSOC&trade; Edge MCU datasheets](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm#documents) <br> [PSOC&trade; Edge MCU reference manuals](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm#documents)
Development kits | Select your kits from the [Evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board)
Libraries  | [mtb-dsl-pse8xxgp](https://github.com/Infineon/mtb-dsl-pse8xxgp) – Device support library for PSE8XXGP <br> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port <br> [btstack-integration](https://github.com/Infineon/btstack-integration) - The btstack-integration hosts platform adaptation layer (porting layer) between AIROC&trade; BTSTACK and Infineon's different hardware platforms
Tools  | [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use libraries and tools enabling rapid development with Infineon MCUs for applications ranging from wireless and cloud-connected systems, edge AI/ML, embedded sense and control, to wired USB connectivity using PSOC&trade; Industrial/IoT MCUs, AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices, XMC&trade; Industrial MCUs, and EZ-USB&trade;/EZ-PD&trade; wired connectivity controllers. ModusToolbox&trade; incorporates a comprehensive set of BSPs, HAL, libraries, configuration tools, and provides support for industry-standard IDEs to fast-track your embedded application development

<br>


## Other resources

Infineon provides a wealth of data at [www.infineon.com](https://www.infineon.com) to help you select the right device, and quickly and effectively integrate it into your design.


## Document history

Document title: *CE241865* – *PSOC&trade; Edge MCU: Bluetooth&reg; LE periodic sync*

 Version | Description of change
 ------- | ---------------------
 1.x.0   | New code example <br> Early access release
 2.0.0   | GitHub release
 2.0.1   | Updated README.md file
 2.1.0   | Updated to support btstack-integration v7.X
<br>


All referenced product or service names and trademarks are the property of their respective owners.

The Bluetooth&reg; word mark and logos are registered trademarks owned by Bluetooth SIG, Inc., and any use of such marks by Infineon is under license.

PSOC&trade;, formerly known as PSoC&trade;, is a trademark of Infineon Technologies. Any references to PSoC&trade; in this document or others shall be deemed to refer to PSOC&trade;.

---------------------------------------------------------

© Cypress Semiconductor Corporation, 2023-2025. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress's patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress's published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, ModusToolbox, PSoC, CAPSENSE, EZ-USB, F-RAM, and TRAVEO are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit www.infineon.com. Other names and brands may be claimed as property of their respective owners.
