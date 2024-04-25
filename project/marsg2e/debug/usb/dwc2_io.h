/**
 * @file dwc2_io.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2024-04-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _DWC2_IO_H_
#define _DWC2_IO_H_

#include <linux/types.h>
#include <asm/io.h>
#include "dwc2_trace.h"

#define DWC2_BASE_ADDR		0x2b000000

extern dma_addr_t reg_map_addr;

static inline u32 dwc2_readl(const void __iomem *addr)
{
	dma_addr_t phyaddr = (dma_addr_t)addr - reg_map_addr + DWC2_BASE_ADDR;
	u32 value;

	value = readl(addr);
	trace_dwc2_readl(phyaddr, value, 0);

	return value;
}

static inline void dwc2_writel(u32 value, void __iomem *addr)
{
	dma_addr_t phyaddr = (dma_addr_t)addr - reg_map_addr + DWC2_BASE_ADDR;

	writel(value, addr);
	trace_dwc2_writel(phyaddr, value, 1);
}

#endif /* !_DWC2_IO_H_ */
