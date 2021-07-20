#ifndef __USB_URB_H__
#define __USB_URB_H__

/*
 * urb->transfer_flags:
 *
 * Note: URB_DIR_IN/OUT is automatically set in usb_submit_urb().
 */
#define URB_SHORT_NOT_OK 0x0001   /* report short reads as errors */
#define URB_ISO_ASAP  0x0002            /* iso-only, urb->start_frame ignored */
#define URB_NO_TRANSFER_DMA_MAP 0x0004    /* urb->transfer_dma valid on submit */
#define URB_NO_SETUP_DMA_MAP 0x0008     /* urb->setup_dma valid on submit */
#define URB_NO_FSBR  0x0020      /* UHCI-specific */
#define URB_ZERO_PACKET  0x0040    /* Finish bulk OUT with short packet */
#define URB_NO_INTERRUPT 0x0080   /* HINT: no non-error interrupt  needed */
#define URB_FREE_BUFFER  0x0100   /* Free transfer buffer with the URB */

#define URB_DIR_IN  0x0200       /* Transfer from device to host */
#define URB_HCD_DRIVER_TEST 0xFFFF   /* Do NOT hand back or free this URB */
#define URB_DIR_OUT  0
#define URB_DIR_MASK  URB_DIR_IN


struct urb {
	/* private: usb core and host controller only fields in the urb */
	int unlinked;			/* unlink error code */
	void *hcpriv;			/* private data for host controller */
	atomic_t use_count;		/* concurrent submissions counter */
	atomic_t reject;		/* submissions will fail */

	/* public: documented fields in the urb that can be used by drivers */
	struct list_head urb_list;	/* list head for use by the urb's
					 * current owner */
	struct list_head anchor_list;	/* the URB may be anchored */
	struct usb_anchor *anchor;
	struct usb_device *dev;		/* (in) pointer to associated device */
	struct usb_host_endpoint *ep;	/* (internal) pointer to endpoint */
	unsigned int pipe;		/* (in) pipe information */
	unsigned int stream_id;		/* (in) stream ID */
	int status;			/* (return) non-ISO status */
    

	unsigned int transfer_flags;	/* (in) URB_SHORT_NOT_OK | ...*/
	void *transfer_buffer;		/* (in) associated data buffer */
	dma_addr_t transfer_dma;	/* (in) dma addr for transfer_buffer */
	struct scatterlist *sg;		/* (in) scatter gather buffer list */
	int num_mapped_sgs;		/* (internal) mapped sg entries */
	int num_sgs;			/* (in) number of entries in the sg list */
	u32 transfer_buffer_length;	/* (in) data buffer length */
	u32 actual_length;		/* (return) actual transfer length */
	unsigned char *setup_packet;	/* (in) setup packet (control only) */
	dma_addr_t setup_dma;		/* (in) dma addr for setup_packet */
	int start_frame;		/* (modify) start frame (ISO) */
	int number_of_packets;		/* (in) number of ISO packets */
	int interval;			/* (modify) transfer interval
					 * (INT/ISO) */
	int error_count;		/* (return) number of ISO errors */
	void *context;			/* (in) context for completion */
	usb_complete_t complete;	/* (in) completion routine */
	struct usb_iso_packet_descriptor iso_frame_desc[];
					/* (in) ISO ONLY */
};

#endif /* __USB_URB_H__ */
