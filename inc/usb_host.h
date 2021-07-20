#ifndef __USB_HOST_H__
#define __USB_HOST_H__

#include "usb_common.h"

struct usb_device;
struct usb_bus;

/* USB device number allocation bitmap */
struct usb_devmap {
	unsigned long devicemap[128 / (8*sizeof(unsigned long))];
};

/*
 * Allocated per bus (tree of devices) we have:
 */
struct usb_bus {
	struct rt_device parent;	/* host side hardware */
	int busnum;			/* Bus number (in order of reg) */
	uint8_t otg_port;			/* 0, or number of OTG/HNP port */
	unsigned is_b_host:1;		/* true during some HNP roleswitches */

	int devnum_next;		/* Next open device number in
					 * round-robin allocation */
	struct rt_mutex devnum_next_mutex; /* devnum_next mutex */

	struct usb_devmap devmap;	/* device address allocation map */
	struct usb_device *root_hub;	/* Root hub */
	struct usb_bus *hs_companion;	/* Companion EHCI bus, if any */

	int bandwidth_allocated;	/* on this bus: how much of the time
					 * reserved for periodic (intr/iso)
					 * requests is used, on average?
					 * Units: microseconds/frame.
					 * Limits: Full/low speed reserve 90%,
					 * while high speed reserves 80%.
					 */
	int bandwidth_int_reqs;		/* number of Interrupt requests */
	int bandwidth_isoc_reqs;	/* number of Isoc. requests */

	unsigned resuming_ports;	/* bit array: resuming root-hub ports */

};

struct usb_device {
	struct rt_device dev;
	int		devnum;
	/*
	char		devpath[16];
	uint32_t		route;
	*/
	enum usb_device_state	state;
	enum usb_device_speed	speed;

	/* for ohci ehci */
	/* reserved 
	struct usb_tt	*tt;
	int		ttport;
	*/

	/* toggle D0/D1 bit */
	unsigned int toggle[2];

	struct usb_device *parent;
	struct usb_bus *bus;
	struct usb_host_endpoint ep0;

	struct usb_device_descriptor descriptor;
	struct usb_host_bos *bos;
	struct usb_host_config *config;

	struct usb_host_config *actconfig;
	struct usb_host_endpoint *ep_in[16];
	struct usb_host_endpoint *ep_out[16];

	char **rawdescriptors;

	unsigned short bus_mA;
	/* for hub */
	uint8_t portnum;
	/* roothub is 0 etc. */
	uint8_t level;
	uint8_t devaddr;

	unsigned can_submit:1;
	unsigned persist_enabled:1;
	unsigned have_langid:1;
	/* not support authorized usb */
	/* reserved
	unsigned authorized:1;
	unsigned authenticated:1;
	*/
	/* not support wireless usb */
	/* reserved
	unsigned wusb:1;
	*/
	/* not support lpm */
	/*
	unsigned lpm_capable:1;
	unsigned usb2_hw_lpm_capable:1;
	unsigned usb2_hw_lpm_besl_capable:1;
	unsigned usb2_hw_lpm_enabled:1;
	unsigned usb2_hw_lpm_allowed:1;
	unsigned usb3_lpm_u1_enabled:1;
	unsigned usb3_lpm_u2_enabled:1;
	*/
	int string_langid;

	/* static strings from the device */
	char *product;
	char *manufacturer;
	char *serial;

	rt_list_t children;

	int maxchild;

	uint32_t quirks;//?
	int urbnum;//需要原子操作
	/* not support lpm
	unsigned long active_duration;

#ifdef CONFIG_PM
	unsigned long connect_time;

	unsigned do_remote_wakeup:1;
	unsigned reset_resume:1;
	unsigned port_is_suspended:1;
#endif
	struct wusb_dev *wusb_dev;
	int slot_id;
	struct usb2_lpm_parameters l1_params;
	struct usb3_lpm_parameters u1_params;
	struct usb3_lpm_parameters u2_params;
	unsigned lpm_disable_count;
	*/
	uint16_t hub_delay;
	unsigned use_generic_driver:1;
};

struct usb_host_endpoint {
	struct usb_endpoint_descriptor		desc;
	/* This is for Super Speed USB */
	/* reserved
	struct usb_ss_ep_comp_descriptor	ss_ep_comp;
	struct usb_ssp_isoc_ep_comp_descriptor	ssp_isoc_ep_comp;
	*/
	rt_list_t							urb_list;

	struct usb_device 					*udev;

	/* hcd drivers */
	void								*hcpriv;

	/* for uvc devices */
	unsigned char 						*extra;   /* Extra descriptors */
	int 								extralen;
	
	int 								enabled;

	/* reserved */
	int 								streams;
};




#endif /* __USB_HOST_H__ */
