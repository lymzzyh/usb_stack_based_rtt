#ifndef __USB_COMMON_H__
#define __USB_COMMON_H__

#include <rtdevice.h>

#include <stdlib.h>

#define USB_DYNAMIC                     0x00

#define USB_CLASS_DEVICE                0x00
#define USB_CLASS_AUDIO                 0x01
#define USB_CLASS_CDC                   0x02
#define USB_CLASS_HID                   0x03
#define USB_CLASS_PHYSICAL              0x05
#define USB_CLASS_IMAGE                 0x06
#define USB_CLASS_PRINTER               0x07
#define USB_CLASS_MASS_STORAGE          0x08
#define USB_CLASS_HUB                   0x09
#define USB_CLASS_CDC_DATA              0x0a
#define USB_CLASS_SMART_CARD            0x0b
#define USB_CLASS_SECURITY              0x0d
#define USB_CLASS_VIDEO                 0x0e
#define USB_CLASS_HEALTHCARE            0x0f
#define USB_CLASS_DIAG_DEVICE           0xdc
#define USB_CLASS_WIRELESS              0xe0
#define USB_CLASS_MISC                  0xef
#define USB_CLASS_APP_SPECIFIC          0xfe
#define USB_CLASS_VEND_SPECIFIC         0xff

#define USB_DESC_TYPE_DEVICE            0x01
#define USB_DESC_TYPE_CONFIGURATION     0x02
#define USB_DESC_TYPE_STRING            0x03
#define USB_DESC_TYPE_INTERFACE         0x04
#define USB_DESC_TYPE_ENDPOINT          0x05
#define USB_DESC_TYPE_DEVICEQUALIFIER   0x06
#define USB_DESC_TYPE_OTHERSPEED        0x07
#define USB_DESC_TYPE_IAD               0x0b
#define USB_DESC_TYPE_HID               0x21
#define USB_DESC_TYPE_REPORT            0x22
#define USB_DESC_TYPE_PHYSICAL          0x23
#define USB_DESC_TYPE_HUB               0x29

#define USB_DESC_LENGTH_DEVICE          0x12
#define USB_DESC_LENGTH_CONFIG          0x9
#define USB_DESC_LENGTH_IAD             0x8
#define USB_DESC_LENGTH_STRING          0x4
#define USB_DESC_LENGTH_INTERFACE       0x9
#define USB_DESC_LENGTH_ENDPOINT        0x7

#define USB_REQ_TYPE_STANDARD           0x00
#define USB_REQ_TYPE_CLASS              0x20
#define USB_REQ_TYPE_VENDOR             0x40
#define USB_REQ_TYPE_MASK               0x60

#define USB_REQ_TYPE_DIR_OUT            0x00
#define USB_REQ_TYPE_DIR_IN             0x80

#define USB_REQ_TYPE_DEVICE             0x00
#define USB_REQ_TYPE_INTERFACE          0x01
#define USB_REQ_TYPE_ENDPOINT           0x02
#define USB_REQ_TYPE_OTHER              0x03
#define USB_REQ_TYPE_RECIPIENT_MASK     0x1f

#define USB_FEATURE_ENDPOINT_HALT       0x00
#define USB_FEATURE_DEV_REMOTE_WAKEUP   0x01
#define USB_FEATURE_TEST_MODE           0x02

#define USB_REQ_GET_STATUS              0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE             0x03
#define USB_REQ_SET_ADDRESS             0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B
#define USB_REQ_SYNCH_FRAME             0x0C
#define USB_REQ_SET_ENCRYPTION          0x0D
#define USB_REQ_GET_ENCRYPTION          0x0E
#define USB_REQ_RPIPE_ABORT             0x0E
#define USB_REQ_SET_HANDSHAKE           0x0F
#define USB_REQ_RPIPE_RESET             0x0F
#define USB_REQ_GET_HANDSHAKE           0x10
#define USB_REQ_SET_CONNECTION          0x11
#define USB_REQ_SET_SECURITY_DATA       0x12
#define USB_REQ_GET_SECURITY_DATA       0x13
#define USB_REQ_SET_WUSB_DATA           0x14
#define USB_REQ_LOOPBACK_DATA_WRITE     0x15
#define USB_REQ_LOOPBACK_DATA_READ      0x16
#define USB_REQ_SET_INTERFACE_DS        0x17

#define USB_STRING_LANGID_INDEX         0x00
#define USB_STRING_MANU_INDEX           0x01
#define USB_STRING_PRODUCT_INDEX        0x02
#define USB_STRING_SERIAL_INDEX         0x03
#define USB_STRING_CONFIG_INDEX         0x04
#define USB_STRING_INTERFACE_INDEX      0x05

#define USB_STRING_MAX                  0xff

#define USB_PID_OUT                     0x01
#define USB_PID_ACK                     0x02
#define USB_PID_DATA0                   0x03
#define USB_PID_SOF                     0x05
#define USB_PID_IN                      0x09
#define USB_PID_NACK                    0x0A
#define USB_PID_DATA1                   0x0B
#define USB_PID_PRE                     0x0C
#define USB_PID_SETUP                   0x0D
#define USB_PID_STALL                   0x0E

#define USB_EP_DESC_OUT                 0x00
#define USB_EP_DESC_IN                  0x80
#define USB_EP_DESC_NUM_MASK            0x0f

#define USB_EP_ATTR_CONTROL             0x00
#define USB_EP_ATTR_ISOC                0x01
#define USB_EP_ATTR_BULK                0x02
#define USB_EP_ATTR_INT                 0x03
#define USB_EP_ATTR_TYPE_MASK           0x03

#define USB_EPNO_MASK                   0x7f
#define USB_DIR_OUT                     0x00
#define USB_DIR_IN                      0x80
#define USB_DIR_INOUT                   0x40
#define USB_DIR_MASK                    0x80

#define ID_UNASSIGNED                   0
#define ID_ASSIGNED                     1

#define RH_GET_PORT_STATUS              0
#define RH_SET_PORT_STATUS              1
#define RH_CLEAR_PORT_FEATURE           2
#define RH_SET_PORT_FEATURE             3

#define USB_BUS_POWERED                 0
#define USB_SELF_POWERED                1
#define USB_REMOTE_WAKEUP               1
#define USB_EP_HALT                     0

/*----------------------------------------------------------------------------------*/
/*  USB standard descriptors                                                        */
/*----------------------------------------------------------------------------------*/

/* Descriptor header */
struct __attribute__((__packed__)) usb_descriptor_header
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
};

/*----------------------------------------------------------------------------------*/
/*  USB device descriptor                                                           */
/*----------------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) usb_device_descriptor  /*!< device descriptor structure        */
{
    uint8_t  bLength;                   /*!< Length of device descriptor            */
    uint8_t  bDescriptorType;           /*!< Device descriptor type                 */
    uint16_t bcdUSB;                    /*!< USB version number                     */
    uint8_t  bDeviceClass;              /*!< Device class code                      */
    uint8_t  bDeviceSubClass;           /*!< Device subclass code                   */
    uint8_t  bDeviceProtocol;           /*!< Device protocol code                   */
    uint8_t  bMaxPacketSize0;           /*!< Maximum packet size of control endpoint*/
    uint16_t idVendor;                  /*!< Vendor ID                              */
    uint16_t idProduct;                 /*!< Product ID                             */
    uint16_t bcdDevice;                 /*!< Device ID                              */
    uint8_t  iManufacturer;             /*!< Manufacture description string ID      */
    uint8_t  iProduct;                  /*!< Product description string ID          */
    uint8_t  iSerialNumber;             /*!< Serial number description string ID    */
    uint8_t  bNumConfigurations;        /*!< Total number of configurations         */
};                                      /*!< device descriptor structure            */

/*
 *  Configuration Descriptor
 */
typedef struct __attribute__((__packed__)) usb_config_descriptor    /*!< Configuration descriptor structure     */
{
    uint8_t   bLength;                  /*!< Length of configuration descriptor     */
    uint8_t   bDescriptorType;          /*!< Descriptor type                        */
    uint16_t  wTotalLength;             /*!< Total length of this configuration     */
    uint8_t   bNumInterfaces;           /*!< Total number of interfaces             */
    uint8_t   bConfigurationValue;      /*!< Configuration descriptor number        */
    uint8_t   iConfiguration;           /*!< String descriptor ID                   */
    uint8_t   bmAttributes;             /*!< Configuration characteristics          */
    uint8_t   MaxPower;                 /*!< Maximum power consumption              */
};                                      /*!< Configuration descriptor structure     */

/*
 *  Interface Descriptor
 */
typedef struct  __attribute__((__packed__)) usb_interface_descriptor   /*!< Interface descriptor structure       */
{
    uint8_t  bLength;                   /*!< Length of interface descriptor         */
    uint8_t  bDescriptorType;           /*!< Descriptor type                        */
    uint8_t  bInterfaceNumber;          /*!< Interface number                       */
    uint8_t  bAlternateSetting;         /*!< Alternate setting number               */
    uint8_t  bNumEndpoints;             /*!< Number of endpoints                    */
    uint8_t  bInterfaceClass;           /*!< Interface class code                   */
    uint8_t  bInterfaceSubClass;        /*!< Interface subclass code                */
    uint8_t  bInterfaceProtocol;        /*!< Interface protocol code                */
    uint8_t  iInterface;                /*!< Interface ID                           */
};                                      /*!< Interface descriptor structure         */

/*
 *  Endpoint Descriptor
 */
typedef struct __attribute__((__packed__)) usb_endpoint_descriptor   /*!< Endpoint descriptor structure         */
{
    uint8_t  bLength;                   /*!< Length of endpoint descriptor          */
    uint8_t  bDescriptorType;           /*!< Descriptor type                        */
    uint8_t  bEndpointAddress;          /*!< Endpoint address                       */
    uint8_t  bmAttributes;              /*!< Endpoint attribute                     */
    uint16_t wMaxPacketSize;            /*!< Maximum packet size                    */
    uint8_t  bInterval;                 /*!< Synchronous transfer interval          */

    /* NOTE:  these two are _only_ in audio endpoints. */
	/* use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. */
    uint8_t  bRefresh;                  /*!< Refresh                                */
    uint8_t  bSynchAddress;             /*!< Sync address                           */
};                                      /*!< Endpoint descriptor structure          */

enum usb_device_speed {
	USB_SPEED_UNKNOWN = 0,			/* enumerating */
	USB_SPEED_LOW, USB_SPEED_FULL,		/* usb 1.1 */
	USB_SPEED_HIGH,				/* usb 2.0 */

    /* not supported */
	USB_SPEED_WIRELESS,			/* wireless (usb 2.5) */
	USB_SPEED_SUPER,			/* usb 3.0 */
	USB_SPEED_SUPER_PLUS,			/* usb 3.1 */
};

enum usb_device_state {
	/* NOTATTACHED isn't in the USB spec, and this state acts
	 * the same as ATTACHED ... but it's clearer this way.
	 */
	USB_STATE_NOTATTACHED = 0,

	/* chapter 9 and authentication (wireless) device states */
	USB_STATE_ATTACHED,
	USB_STATE_POWERED,			/* wired */
	USB_STATE_RECONNECTING,			/* auth */
	USB_STATE_UNAUTHENTICATED,		/* auth */
	USB_STATE_DEFAULT,			/* limited function */
	USB_STATE_ADDRESS,
	USB_STATE_CONFIGURED,			/* most functions */

	USB_STATE_SUSPENDED

	/* NOTE:  there are actually four different SUSPENDED
	 * states, returning to POWERED, DEFAULT, ADDRESS, or
	 * CONFIGURED respectively when SOF tokens flow again.
	 * At this level there's no difference between L1 and L2
	 * suspend states.  (L2 being original USB 1.1 suspend.)
	 */
};

#endif /* __USB_COMMON_H__ */
