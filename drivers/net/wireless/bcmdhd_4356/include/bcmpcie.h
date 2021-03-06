/*
 * Broadcom PCIE
 * Software-specific definitions shared between device and host side
 * Explains the shared area between host and dongle
 * Copyright (C) 1999-2015, Broadcom Corporation
 * 
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 * $Id: bcmpcie.h 546977 2015-04-07 06:34:52Z $
 */

#ifndef	_bcmpcie_h_
#define	_bcmpcie_h_

#include <bcmutils.h>

#define ADDR_64(x)			(x.addr)
#define HIGH_ADDR_32(x)     ((uint32) (((sh_addr_t) x).high_addr))
#define LOW_ADDR_32(x)      ((uint32) (((sh_addr_t) x).low_addr))

typedef struct {
	uint32 low_addr;
	uint32 high_addr;
} sh_addr_t;



#ifdef BCMPCIE_SUPPORT_TX_PUSH_RING
#define BCMPCIE_PUSH_TX_RING	1
#else
#define BCMPCIE_PUSH_TX_RING	0
#endif 

#if !defined(BCMPCIE_MAX_TX_FLOWS)
#define BCMPCIE_MAX_TX_FLOWS	40
#endif 

#define PCIE_SHARED_VERSION		0x00005
#define PCIE_SHARED_VERSION_MASK	0x000FF
#define PCIE_SHARED_ASSERT_BUILT	0x00100
#define PCIE_SHARED_ASSERT		0x00200
#define PCIE_SHARED_TRAP		0x00400
#define PCIE_SHARED_IN_BRPT		0x00800
#define PCIE_SHARED_SET_BRPT		0x01000
#define PCIE_SHARED_PENDING_BRPT	0x02000
#define PCIE_SHARED_TXPUSH_SPRT		0x04000
#define PCIE_SHARED_EVT_SEQNUM		0x08000
#define PCIE_SHARED_DMA_INDEX		0x10000

#define PCIE_SHARED_D2H_SYNC_SEQNUM		0x20000
#define PCIE_SHARED_D2H_SYNC_XORCSUM		0x40000
#define PCIE_SHARED_D2H_SYNC_MODE_MASK \
	(PCIE_SHARED_D2H_SYNC_SEQNUM | PCIE_SHARED_D2H_SYNC_XORCSUM)

#define BCMPCIE_H2D_MSGRING_CONTROL_SUBMIT		0
#define BCMPCIE_H2D_MSGRING_RXPOST_SUBMIT		1
#define BCMPCIE_D2H_MSGRING_CONTROL_COMPLETE		2
#define BCMPCIE_D2H_MSGRING_TX_COMPLETE			3
#define BCMPCIE_D2H_MSGRING_RX_COMPLETE			4
#define BCMPCIE_COMMON_MSGRING_MAX_ID			4

#define BCMPCIE_H2D_TXFLOWRINGID			5

#define BCMPCIE_H2D_COMMON_MSGRINGS			2
#define BCMPCIE_D2H_COMMON_MSGRINGS			3
#define BCMPCIE_COMMON_MSGRINGS				5

enum h2dring_idx {
	BCMPCIE_H2D_MSGRING_CONTROL_SUBMIT_IDX = 0,
	BCMPCIE_H2D_MSGRING_RXPOST_SUBMIT_IDX =	1,
	BCMPCIE_H2D_MSGRING_TXFLOW_IDX_START = 2
};

enum d2hring_idx {
	BCMPCIE_D2H_MSGRING_CONTROL_COMPLETE_IDX = 0,
	BCMPCIE_D2H_MSGRING_TX_COMPLETE_IDX = 1,
	BCMPCIE_D2H_MSGRING_RX_COMPLETE_IDX = 2
};

typedef struct ring_mem {
	uint16		idx;
	uint8		type;
	uint8		rsvd;
	uint16		max_item;
	uint16		len_items;
	sh_addr_t	base_addr;
} ring_mem_t;

#define RINGSTATE_INITED	1

typedef struct ring_state {
	uint8 idx;
	uint8 state;
	uint16 r_offset;
	uint16 w_offset;
	uint16 e_offset;
} ring_state_t;



typedef struct ring_info {
	
	uint32		ringmem_ptr;	
	uint32		h2d_w_idx_ptr;

	uint32		h2d_r_idx_ptr;
	uint32		d2h_w_idx_ptr;

	uint32		d2h_r_idx_ptr;
	
	sh_addr_t	h2d_w_idx_hostaddr;
	sh_addr_t	h2d_r_idx_hostaddr;
	sh_addr_t	d2h_w_idx_hostaddr;
	sh_addr_t	d2h_r_idx_hostaddr;
	uint16		max_sub_queues;
	uint16		rsvd;
} ring_info_t;

typedef struct {
	
	uint32	flags;

	uint32  trap_addr;
	uint32  assert_exp_addr;
	uint32  assert_file_addr;
	uint32  assert_line;
	uint32	console_addr;		

	uint32  msgtrace_addr;

	uint32  fwid;

	
	uint16  total_lfrag_pkt_cnt;
	uint16  max_host_rxbufs; 

	uint32 dma_rxoffset; 

	
	uint32  h2d_mb_data_ptr;
	uint32  d2h_mb_data_ptr;

	
	
	uint32	rings_info_ptr;

	
	uint32		host_dma_scratch_buffer_len;
	sh_addr_t	host_dma_scratch_buffer;

	
	uint32		device_rings_stsblk_len;
	sh_addr_t	device_rings_stsblk;
#ifdef BCM_BUZZZ
	uint32	buzzz;	
#endif
} pciedev_shared_t;


#define H2D_HOST_D3_INFORM	0x00000001
#define H2D_HOST_DS_ACK		0x00000002
#define H2D_HOST_CONS_INT	0x80000000	

#define H2D_HOST_D0_INFORM_IN_USE	0x00000008
#define H2D_HOST_D0_INFORM		0x00000010

#define D2H_DEV_D3_ACK		0x00000001
#define D2H_DEV_DS_ENTER_REQ	0x00000002
#define D2H_DEV_DS_EXIT_NOTE	0x00000004
#define D2H_DEV_FWHALT		0x10000000


extern pciedev_shared_t pciedev_shared;
#define NEXTTXP(i, d)           ((((i)+1) >= (d)) ? 0 : ((i)+1))
#define NTXPACTIVE(r, w, d)     (((r) <= (w)) ? ((w)-(r)) : ((d)-(r)+(w)))
#define NTXPAVAIL(r, w, d)      (((d) - NTXPACTIVE((r), (w), (d))) > 1)

#define READ_AVAIL_SPACE(w, r, d)		\
			((w >= r) ? (w - r) : (d - r))

#define WRT_PEND(x)	((x)->wr_pending)
#define DNGL_RING_WPTR(msgbuf)		(*((msgbuf)->tcm_rs_w_ptr))
#define BCMMSGBUF_RING_SET_W_PTR(msgbuf, a)	(DNGL_RING_WPTR(msgbuf) = (a))

#define DNGL_RING_RPTR(msgbuf)		(*((msgbuf)->tcm_rs_r_ptr))
#define BCMMSGBUF_RING_SET_R_PTR(msgbuf, a)	(DNGL_RING_RPTR(msgbuf) = (a))

#define  RING_READ_PTR(x)	((x)->ringstate->r_offset)
#define  RING_WRITE_PTR(x)	((x)->ringstate->w_offset)
#define  RING_START_PTR(x)	((x)->ringmem->base_addr.low_addr)
#define  RING_MAX_ITEM(x)	((x)->ringmem->max_item)
#define  RING_LEN_ITEMS(x)	((x)->ringmem->len_items)
#define	 HOST_RING_BASE(x)	((x)->ring_base.va)
#define	 HOST_RING_END(x)	((uint8 *)HOST_RING_BASE((x)) + \
			 ((RING_MAX_ITEM((x))-1)*RING_LEN_ITEMS((x))))

#define WRITE_SPACE_AVAIL_CONTINUOUS(r, w, d)		((w >= r) ? (d - w) : (r - w))
#define WRITE_SPACE_AVAIL(r, w, d)	(d - (NTXPACTIVE(r, w, d)) - 1)
#define CHECK_WRITE_SPACE(r, w, d)	\
	MIN(WRITE_SPACE_AVAIL(r, w, d), WRITE_SPACE_AVAIL_CONTINUOUS(r, w, d))

#endif	
