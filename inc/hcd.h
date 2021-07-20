#ifndef __USB_HCD_H__
#define __USB_HCD_H__

#include "usb_host.h"

struct usb_hcd {

	/*
	 * housekeeping
	 */
	struct usb_bus		self;		/* hcd is-a bus */

	const char		*product_desc;	/* product/vendor string */
	int			speed;		/* Speed for this roothub.
						 * May be different from
						 * hcd->driver->flags & HCD_MASK
						 */

	struct timer_list	rh_timer;	/* drives root-hub polling */
	struct urb		*status_urb;	/* the current status urb */
#ifdef CONFIG_PM
	struct work_struct	wakeup_work;	/* for remote wakeup */
#endif
	struct work_struct	died_work;	/* for when the device dies */

	/*
	 * hardware info/state
	 */
	const struct hc_driver	*driver;	/* hw-specific hooks */

	/*
	 * OTG and some Host controllers need software interaction with phys;
	 * other external phys should be software-transparent
	 */
	struct usb_phy		*usb_phy;
	struct usb_phy_roothub	*phy_roothub;

	/* Flags that need to be manipulated atomically because they can
	 * change while the host controller is running.  Always use
	 * set_bit() or clear_bit() to change their values.
	 */
	unsigned long		flags;
#define HCD_FLAG_HW_ACCESSIBLE		0	/* at full power */
#define HCD_FLAG_POLL_RH		2	/* poll for rh status? */
#define HCD_FLAG_POLL_PENDING		3	/* status has changed? */
#define HCD_FLAG_WAKEUP_PENDING		4	/* root hub is resuming? */
#define HCD_FLAG_RH_RUNNING		5	/* root hub is running? */
#define HCD_FLAG_DEAD			6	/* controller has died? */
#define HCD_FLAG_INTF_AUTHORIZED	7	/* authorize interfaces? */

	/* The flags can be tested using these macros; they are likely to
	 * be slightly faster than test_bit().
	 */
#define HCD_HW_ACCESSIBLE(hcd)	((hcd)->flags & (1U << HCD_FLAG_HW_ACCESSIBLE))
#define HCD_POLL_RH(hcd)	((hcd)->flags & (1U << HCD_FLAG_POLL_RH))
#define HCD_POLL_PENDING(hcd)	((hcd)->flags & (1U << HCD_FLAG_POLL_PENDING))
#define HCD_WAKEUP_PENDING(hcd)	((hcd)->flags & (1U << HCD_FLAG_WAKEUP_PENDING))
#define HCD_RH_RUNNING(hcd)	((hcd)->flags & (1U << HCD_FLAG_RH_RUNNING))
#define HCD_DEAD(hcd)		((hcd)->flags & (1U << HCD_FLAG_DEAD))

	/*
	 * Specifies if interfaces are authorized by default
	 * or they require explicit user space authorization; this bit is
	 * settable through /sys/class/usb_host/X/interface_authorized_default
	 */
#define HCD_INTF_AUTHORIZED(hcd) \
	((hcd)->flags & (1U << HCD_FLAG_INTF_AUTHORIZED))

	/*
	 * Specifies if devices are authorized by default
	 * or they require explicit user space authorization; this bit is
	 * settable through /sys/class/usb_host/X/authorized_default
	 */
	enum usb_dev_authorize_policy dev_policy;

	/* Flags that get set only during HCD registration or removal. */
	unsigned		rh_registered:1;/* is root hub registered? */
	unsigned		rh_pollable:1;	/* may we poll the root hub? */
	unsigned		msix_enabled:1;	/* driver has MSI-X enabled? */
	unsigned		msi_enabled:1;	/* driver has MSI enabled? */
	/*
	 * do not manage the PHY state in the HCD core, instead let the driver
	 * handle this (for example if the PHY can only be turned on after a
	 * specific event)
	 */
	unsigned		skip_phy_initialization:1;

	/* The next flag is a stopgap, to be removed when all the HCDs
	 * support the new root-hub polling mechanism. */
	unsigned		uses_new_polling:1;
	unsigned		wireless:1;	/* Wireless USB HCD */
	unsigned		has_tt:1;	/* Integrated TT in root hub */
	unsigned		amd_resume_bug:1; /* AMD remote wakeup quirk */
	unsigned		can_do_streams:1; /* HC supports streams */
	unsigned		tpl_support:1; /* OTG & EH TPL support */
	unsigned		cant_recv_wakeups:1;
			/* wakeup requests from downstream aren't received */

	unsigned int		irq;		/* irq allocated */
	void __iomem		*regs;		/* device memory/io */
	resource_size_t		rsrc_start;	/* memory/io resource start */
	resource_size_t		rsrc_len;	/* memory/io resource length */
	unsigned		power_budget;	/* in mA, 0 = no limit */

	struct giveback_urb_bh  high_prio_bh;
	struct giveback_urb_bh  low_prio_bh;

	/* bandwidth_mutex should be taken before adding or removing
	 * any new bus bandwidth constraints:
	 *   1. Before adding a configuration for a new device.
	 *   2. Before removing the configuration to put the device into
	 *      the addressed state.
	 *   3. Before selecting a different configuration.
	 *   4. Before selecting an alternate interface setting.
	 *
	 * bandwidth_mutex should be dropped after a successful control message
	 * to the device, or resetting the bandwidth after a failed attempt.
	 */
	struct mutex		*address0_mutex;
	struct mutex		*bandwidth_mutex;
	struct usb_hcd		*shared_hcd;
	struct usb_hcd		*primary_hcd;


#define HCD_BUFFER_POOLS	4
	struct dma_pool		*pool[HCD_BUFFER_POOLS];

	int			state;
#	define	__ACTIVE		0x01
#	define	__SUSPEND		0x04
#	define	__TRANSIENT		0x80

#	define	HC_STATE_HALT		0
#	define	HC_STATE_RUNNING	(__ACTIVE)
#	define	HC_STATE_QUIESCING	(__SUSPEND|__TRANSIENT|__ACTIVE)
#	define	HC_STATE_RESUMING	(__SUSPEND|__TRANSIENT)
#	define	HC_STATE_SUSPENDED	(__SUSPEND)

#define	HC_IS_RUNNING(state) ((state) & __ACTIVE)
#define	HC_IS_SUSPENDED(state) ((state) & __SUSPEND)

	/* memory pool for HCs having local memory, or %NULL */
	struct gen_pool         *localmem_pool;

	/* more shared queuing code would be good; it should support
	 * smarter scheduling, handle transaction translators, etc;
	 * input size of periodic table to an interrupt scheduler.
	 * (ohci 32, uhci 1024, ehci 256/512/1024).
	 */

	/* The HC driver's private data is stored at the end of
	 * this structure.
	 */
	unsigned long hcd_priv[]
			__attribute__ ((aligned(sizeof(s64))));
};

#endif /* __USB_HCD_H__ */
