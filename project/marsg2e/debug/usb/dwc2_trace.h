/**
 * @file dwc2_trace.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2024-04-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#undef TRACE_SYSTEM
#define TRACE_SYSTEM dwc2

#if !defined(__DWC2_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define __DWC2_TRACE_H

#include <linux/tracepoint.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/usb.h>
#include <asm/io.h>
#include "hcd.h"

DECLARE_EVENT_CLASS(dwc2_log_urb,
	TP_PROTO(struct urb *urb),
	TP_ARGS(urb),
	TP_STRUCT__entry(
		__field(dma_addr_t, urb_virt)
		__field(u32, pipe)
		__field(dma_addr_t, transfer_dma)
		__field(u32, transfer_buffer_length)
		__field(u32, actual_length)
		__field(int, num_sgs)
	),
	TP_fast_assign(
		__entry->urb_virt = (dma_addr_t)urb;
		__entry->pipe = urb->pipe;
		__entry->transfer_dma = urb->transfer_dma;
		__entry->transfer_buffer_length = urb->transfer_buffer_length;
		__entry->actual_length = urb->actual_length;
		__entry->num_sgs = urb->num_sgs;
	),
	TP_printk("urb:0x%08x => devaddr:%u, ep%u-%s, type:%u, xfer_dma:0x%08x, "
		"len:0x%x, actual:0x%x, nr_sg:%d", 
		__entry->urb_virt,
		usb_pipedevice(__entry->pipe), 
		usb_pipeendpoint(__entry->pipe),
		usb_pipein(__entry->pipe) ? "in" : "out", 
		usb_pipetype(__entry->pipe),
		__entry->transfer_dma, __entry->transfer_buffer_length,
		__entry->actual_length, __entry->num_sgs)
);

DEFINE_EVENT(dwc2_log_urb, _dwc2_hcd_urb_enqueue,
	TP_PROTO(struct urb *urb),
	TP_ARGS(urb)
);

DEFINE_EVENT(dwc2_log_urb, _dwc2_hcd_urb_dequeue,
	TP_PROTO(struct urb *urb),
	TP_ARGS(urb)
);

DEFINE_EVENT(dwc2_log_urb, dwc2_host_complete,
	TP_PROTO(struct urb *urb),
	TP_ARGS(urb)
);

DECLARE_EVENT_CLASS(dwc2_log_channel,
	TP_PROTO(struct dwc2_host_chan *chan),
	TP_ARGS(chan),
	TP_STRUCT__entry(
		__field(u8, hc_num)
		__field(u8, dev_addr)
		__field(u8, ep_num)
		__field(u8, ep_is_in)
		__field(u8, speed)
		__field(u8, ep_type)
		__field(dma_addr_t, xfer_dma)
		__field(u32, xfer_len) /* Total number of bytes to transfer */
		__field(u32, xfer_count) /* Number of bytes transferred so far */
	),
	TP_fast_assign(
		__entry->hc_num = chan->hc_num;
		__entry->dev_addr = chan->dev_addr;
		__entry->ep_num = chan->ep_num;
		__entry->ep_is_in = chan->ep_is_in;
		__entry->speed = chan->speed;
		__entry->ep_type = chan->ep_type;
		__entry->xfer_dma = chan->xfer_dma;
		__entry->xfer_len = chan->xfer_len;
		__entry->xfer_count = chan->xfer_count;
	),
	TP_printk("devaddr:%u, ep%u-%s, type:%u, dma:0x%08x, len:0x%x, "
		"actual:0x%x, chan:%u",
		__entry->dev_addr, __entry->ep_num,
		__entry->ep_is_in ? "in" : "out", __entry->ep_type,
		__entry->xfer_dma, __entry->xfer_len, __entry->xfer_count,
		__entry->hc_num)
);

DEFINE_EVENT(dwc2_log_channel, dwc2_hc_chhltd_intr_dma,
	TP_PROTO(struct dwc2_host_chan *chan),
	TP_ARGS(chan)
);

DECLARE_EVENT_CLASS(dwc2_log_reg,
	TP_PROTO(dma_addr_t addr, u32 val, u8 flag),
	TP_ARGS(addr, val, flag),
	TP_STRUCT__entry(
		__field(dma_addr_t, addr)
		__field(u32, val)
		__field(u8, flag)
	),
	TP_fast_assign(
		__entry->addr = addr;
		__entry->val = val;
		__entry->flag = flag; /* 0: read, 1: write */
	),
	TP_printk("%s: %08x %s %08lx", 
		__entry->flag ? "W" : "R", __entry->val, 
		__entry->flag ? "=>": "<=", __entry->addr)
);

DEFINE_EVENT(dwc2_log_reg, dwc2_readl, 
	TP_PROTO(dma_addr_t addr, u32 val, u8 flag),
	TP_ARGS(addr, val, flag)
);

DEFINE_EVENT(dwc2_log_reg, dwc2_writel, 
	TP_PROTO(dma_addr_t addr, u32 val, u8 flag),
	TP_ARGS(addr, val, flag)
);

#endif /* __DWC2_TRACE_H */

/* this part must be outside header guard */

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .

#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE dwc2_trace

#include <trace/define_trace.h>
