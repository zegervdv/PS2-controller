/**
  ******************************************************************************
  * @file    usbd_hid_core.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Custom
  *             - Collection : Application 
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/ 
uint8_t  USBD_HID_Init (void  *pdev, 
                               uint8_t cfgidx);

uint8_t  USBD_HID_DeInit (void  *pdev, 
                                 uint8_t cfgidx);

uint8_t  USBD_HID_Setup (void  *pdev, 
                                USB_SETUP_REQ *req);

uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length);


uint8_t  USBD_HID_DataIn (void  *pdev, uint8_t epnum);


uint8_t  USBD_HID_DataOut (void  *pdev, uint8_t epnum);


uint8_t  USBD_HID_EP0_RxReady (void  *pdev);

USBD_Class_cb_TypeDef  USBD_HID_cb = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/  
  USBD_HID_EP0_RxReady, /*EP0_RxReady*/ /* STATUS STAGE IN */
  USBD_HID_DataIn, /*DataIn*/
  USBD_HID_DataOut, /*DataOut*/
  NULL, /*SOF */    
  USBD_HID_GetCfgDesc, 
};
  


uint8_t Report_buf[2];
uint8_t USBD_HID_Report_ID=0;
uint8_t flag = 0;
extern uint8_t PrevXferDone;

static uint32_t  USBD_HID_AltSet = 0;
    
static uint32_t  USBD_HID_Protocol = 0;
 
static uint32_t  USBD_HID_IdleState = 0;

/* USB HID device Configuration Descriptor */
const uint8_t USBD_HID_CfgDesc[CUSTOMHID_SIZ_CONFIG_DESC] =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
  CUSTOMHID_SIZ_CONFIG_DESC,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xC0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  
  /************** Descriptor of Custom HID interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x02,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Custom HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  CUSTOMHID_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Custom HID endpoints ***********/
  /* 27 */
  0x07,          /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */
  
  HID_IN_EP,     /* bEndpointAddress: Endpoint Address (IN) */
  0x03,          /* bmAttributes: Interrupt endpoint */
  HID_IN_PACKET, /* wMaxPacketSize: 2 Bytes max */
  0x00,
  0x20,          /* bInterval: Polling Interval (32 ms) */
  /* 34 */
  
  0x07,	         /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
  /*	Endpoint descriptor type */
  HID_OUT_EP,	/* bEndpointAddress: */
  /*	Endpoint Address (OUT) */
  0x03,	/* bmAttributes: Interrupt endpoint */
  HID_OUT_PACKET,	/* wMaxPacketSize: 2 Bytes max  */
  0x00,
  0x20,	/* bInterval: Polling Interval (20 ms) */
  /* 41 */
} ;

const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] =
{
  0x05, 0x01,   //Usage Page (Generic Desktop)
  0x09, 0x05,   //Usage (Game Pad)
  0xA1, 0x01,   //Collection (Application)
  0x05, 0x01,   //Usage Page (Generic Desktop)
  0x09, 0x01,   //Usage (Pointer)
  0xA0,         //Collection (Physical)
  0x14,         //Logical Minimum (0)
  0x25, 0xFF,   //Logical Maximum (255)
  0x75, 0x0C,   //Report Size (12)
  0x95, 0x04,   //Report Count (4)
  0x09, 0x34,   //Usage (Ry)
  0x09, 0x33,   //Usage (Rx)
  0x09, 0x31,   //Usage (Y)
  0x09, 0x30,   //Usage (X)
  0x81, 0x02,   //Input (Data, Variable, Absolute)
  0x14,         //Logical Minimum (0)
  0x25, 0x01,   //Logical Maximum (1)
  0x75, 0x01,   //Report Size (1)
  0x95, 0x02,   //Report Count (2)
  0x05, 0x09,   //Usage Page (Button)
  0x19, 0x01,   //Usage Minimum (Button 1)
  0x29, 0x02,   //Usage Maximum (Button 2)
  0x81, 0x02,   //Input (Data, Variable, Absolute)
  0x75, 0x06,   //Report Size (6)
  0x95, 0x01,   //Report Count (1)
  0x81, 0x03,   //Input (Constant, Variable, Absolute)
  0xC0,         //END Collection
  0xC0,         //END Collection   END_COLLECTION	             */
}; /* CustomHID_ReportDescriptor */

/* Private function ----------------------------------------------------------*/ 
/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
uint8_t  USBD_HID_Init (void  *pdev, 
                               uint8_t cfgidx)
{
  DCD_PMA_Config(pdev , HID_IN_EP,USB_SNG_BUF,HID_IN_TX_ADDRESS);
  DCD_PMA_Config(pdev , HID_OUT_EP,USB_SNG_BUF,HID_OUT_RX_ADDRESS);

  /* Open EP IN */
  DCD_EP_Open(pdev,
              HID_IN_EP,
              HID_IN_PACKET,
              USB_EP_INT);
  
  /* Open EP OUT */
  DCD_EP_Open(pdev,
              HID_OUT_EP,
              HID_OUT_PACKET,
              USB_EP_INT);
 
  /*Receive Data*/
  DCD_EP_PrepareRx(pdev,HID_OUT_EP,Report_buf,2);
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
uint8_t  USBD_HID_DeInit (void  *pdev, 
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  DCD_EP_Close (pdev , HID_IN_EP);
  DCD_EP_Close (pdev , HID_OUT_EP);
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
uint8_t  USBD_HID_Setup (void  *pdev, 
                                USB_SETUP_REQ *req)
{
  uint8_t USBD_HID_Report_LENGTH=0;
  uint16_t len = 0;
  uint8_t  *pbuf = NULL;

  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
    case HID_REQ_SET_PROTOCOL:
      USBD_HID_Protocol = (uint8_t)(req->wValue);
      break;
      
    case HID_REQ_GET_PROTOCOL:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&USBD_HID_Protocol,
                        1);    
      break;
      
    case HID_REQ_SET_IDLE:
      USBD_HID_IdleState = (uint8_t)(req->wValue >> 8);
      break;
      
    case HID_REQ_GET_IDLE:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&USBD_HID_IdleState,
                        1);        
      break;
      
    case HID_REQ_SET_REPORT:
      flag = 1;
      USBD_HID_Report_ID = (uint8_t)(req->wValue);
      USBD_HID_Report_LENGTH = (uint8_t)(req->wLength);
      USBD_CtlPrepareRx (pdev, Report_buf, USBD_HID_Report_LENGTH);
      
      break;
   
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 
      if( req->wValue >> 8 == HID_REPORT_DESC)
      {
        len = MIN(CUSTOMHID_SIZ_REPORT_DESC , req->wLength);
        pbuf = (uint8_t*)CustomHID_ReportDescriptor;
      }
      else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
        pbuf = (uint8_t*)USBD_HID_CfgDesc + 0x12;
        len = MIN(USB_HID_DESC_SIZ , req->wLength);
      }
      
      USBD_CtlSendData (pdev, 
                        pbuf,
                        len);
      
      break;
      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&USBD_HID_AltSet,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      USBD_HID_AltSet = (uint8_t)(req->wValue);
      break;
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USB_CORE_HANDLE  *pdev, 
                                 uint8_t *report,
                                 uint16_t len)
{
  /* Check if USB is configured */
  if (pdev->dev.device_status == USB_CONFIGURED )
  {
    DCD_EP_Tx (pdev, HID_IN_EP, report, len);
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return (uint8_t*)USBD_HID_CfgDesc;
}

/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
uint8_t  USBD_HID_DataIn (void  *pdev, 
                                 uint8_t epnum)
{
  if (epnum == 1) PrevXferDone = 1;

  return USBD_OK;
}

/**
  * @brief  USBD_HID_DataOut
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
uint8_t  USBD_HID_DataOut (void  *pdev, 
                                  uint8_t epnum)
{
  
  BitAction Led_State;
  if (epnum == 1) 
  {
    if (Report_buf[1] == 0)
    {
      Led_State = Bit_RESET;
    }
    else 
    {
      Led_State = Bit_SET;
    }
    
    switch (Report_buf[0])
    {
    case 1: /* Led 3 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED3);
      }
      else
      {
        STM_EVAL_LEDOff(LED3);
      }
      break;
      
    case 2: /* Led 4 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED4);
      }
      else
      {
        STM_EVAL_LEDOff(LED4);
      }
      break;
    case 3: /* Led 5 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED5);
      }
      else
      {
        STM_EVAL_LEDOff(LED5);
      }
      break;
    case 4: /* Led 6 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED6);
      }
      else
      {
        STM_EVAL_LEDOff(LED6);
      }
      break;
    default:
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOff(LED4);
      STM_EVAL_LEDOff(LED5);
      STM_EVAL_LEDOff(LED6); 
      break;
    }
  }
  
  DCD_EP_PrepareRx(pdev,HID_IN_EP,Report_buf,2);
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_EP0_RxReady
  *         Handles control request data.
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */

uint8_t USBD_HID_EP0_RxReady(void *pdev)
{
  BitAction Led_State;
  
  if (flag == 1)
  {
    flag = 0;
    if (Report_buf[1] == 0)
    {
      Led_State = Bit_RESET;
    }
    else 
    {
      Led_State = Bit_SET;
    }
    
    switch (Report_buf[0])
    {
    case 1: /* Led 3 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED3);
      }
      else
      {
        STM_EVAL_LEDOff(LED3);
      }
      break;
      
    case 2: /* Led 4 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED4);
      }
      else
      {
        STM_EVAL_LEDOff(LED4);
      }
      break;
    case 3: /* Led 5 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED5);
      }
      else
      {
        STM_EVAL_LEDOff(LED5);
      }
      break;
    case 4: /* Led 6 */
      if (Led_State != Bit_RESET)
      {
        STM_EVAL_LEDOn(LED6);
      }
      else
      {
        STM_EVAL_LEDOff(LED6);
      }
      break;
    default:
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOff(LED4);
      STM_EVAL_LEDOff(LED5);
      STM_EVAL_LEDOff(LED6); 
      break;
    }
  }
  return USBD_OK;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
