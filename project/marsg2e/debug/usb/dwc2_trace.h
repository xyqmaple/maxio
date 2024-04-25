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
#include <asm/io.h>


DECLARE_EVENT_CLASS(dwc2_log_reg,
	TP_PROTO(dma_addr_t addr, u32 val, u8 flag),
	TP_ARGS(addr, val, write),
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
	TP_ARGS(addr, val, write)
);

DEFINE_EVENT(dwc2_log_reg, dwc2_writel, 
	TP_PROTO(dma_addr_t addr, u32 val, u8 flag),
	TP_ARGS(addr, val, write)
);

#endif /* __DWC2_TRACE_H */

/* this part must be outside header guard */

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .

#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE dwc2_trace

#include <trace/define_trace.h>
