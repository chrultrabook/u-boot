// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2024 MediaTek Inc.
 * Author: Chris-qj Chen <chris-qj.chen@mediatek.com>
 */

#include <common.h>
#include <dm.h>
#include <asm/io.h>
#include <dt-bindings/clock/mt8195-clk.h>
#include <linux/bitops.h>

#include "clk-mtk.h"

static const struct mtk_gate_regs vdo0_0_cg_regs = {
	.set_ofs = 0x104,
	.clr_ofs = 0x108,
	.sta_ofs = 0x100,
};

static const struct mtk_gate_regs vdo0_1_cg_regs = {
	.set_ofs = 0x114,
	.clr_ofs = 0x118,
	.sta_ofs = 0x110,
};

static const struct mtk_gate_regs vdo0_2_cg_regs = {
	.set_ofs = 0x124,
	.clr_ofs = 0x128,
	.sta_ofs = 0x120,
};

#define GATE_VDO0_0(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo0_0_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VDO0_1(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo0_1_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VDO0_2(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo0_2_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

static const struct mtk_gate vdo0_clks[] = {
	/* VDO0_0 */
	GATE_VDO0_0(CLK_VDO0_DISP_OVL0, CLK_TOP_VPP, 0),
	GATE_VDO0_0(CLK_VDO0_DISP_COLOR0, CLK_TOP_VPP, 2),
	GATE_VDO0_0(CLK_VDO0_DISP_COLOR1, CLK_TOP_VPP, 3),
	GATE_VDO0_0(CLK_VDO0_DISP_CCORR0, CLK_TOP_VPP, 4),
	GATE_VDO0_0(CLK_VDO0_DISP_CCORR1, CLK_TOP_VPP, 5),
	GATE_VDO0_0(CLK_VDO0_DISP_AAL0, CLK_TOP_VPP, 6),
	GATE_VDO0_0(CLK_VDO0_DISP_AAL1, CLK_TOP_VPP, 7),
	GATE_VDO0_0(CLK_VDO0_DISP_GAMMA0, CLK_TOP_VPP, 8),
	GATE_VDO0_0(CLK_VDO0_DISP_GAMMA1, CLK_TOP_VPP, 9),
	GATE_VDO0_0(CLK_VDO0_DISP_DITHER0, CLK_TOP_VPP, 10),
	GATE_VDO0_0(CLK_VDO0_DISP_DITHER1, CLK_TOP_VPP, 11),
	GATE_VDO0_0(CLK_VDO0_DISP_OVL1, CLK_TOP_VPP, 16),
	GATE_VDO0_0(CLK_VDO0_DISP_WDMA0, CLK_TOP_VPP, 17),
	GATE_VDO0_0(CLK_VDO0_DISP_WDMA1, CLK_TOP_VPP, 18),
	GATE_VDO0_0(CLK_VDO0_DISP_RDMA0, CLK_TOP_VPP, 19),
	GATE_VDO0_0(CLK_VDO0_DISP_RDMA1, CLK_TOP_VPP, 20),
	GATE_VDO0_0(CLK_VDO0_DSI0, CLK_TOP_VPP, 21),
	GATE_VDO0_0(CLK_VDO0_DSI1, CLK_TOP_VPP, 22),
	GATE_VDO0_0(CLK_VDO0_DSC_WRAP0, CLK_TOP_VPP, 23),
	GATE_VDO0_0(CLK_VDO0_VPP_MERGE0, CLK_TOP_VPP, 24),
	GATE_VDO0_0(CLK_VDO0_DP_INTF0, CLK_TOP_VPP, 25),
	GATE_VDO0_0(CLK_VDO0_DISP_MUTEX0, CLK_TOP_VPP, 26),
	GATE_VDO0_0(CLK_VDO0_DISP_IL_ROT0, CLK_TOP_VPP, 27),
	GATE_VDO0_0(CLK_VDO0_APB_BUS, CLK_TOP_VPP, 28),
	GATE_VDO0_0(CLK_VDO0_FAKE_ENG0, CLK_TOP_VPP, 29),
	GATE_VDO0_0(CLK_VDO0_FAKE_ENG1, CLK_TOP_VPP, 30),
	/* VDO0_1 */
	GATE_VDO0_1(CLK_VDO0_DL_ASYNC0, CLK_TOP_VPP, 0),
	GATE_VDO0_1(CLK_VDO0_DL_ASYNC1, CLK_TOP_VPP, 1),
	GATE_VDO0_1(CLK_VDO0_DL_ASYNC2, CLK_TOP_VPP, 2),
	GATE_VDO0_1(CLK_VDO0_DL_ASYNC3, CLK_TOP_VPP, 3),
	GATE_VDO0_1(CLK_VDO0_DL_ASYNC4, CLK_TOP_VPP, 4),
	GATE_VDO0_1(CLK_VDO0_DISP_MONITOR0, CLK_TOP_VPP, 5),
	GATE_VDO0_1(CLK_VDO0_DISP_MONITOR1, CLK_TOP_VPP, 6),
	GATE_VDO0_1(CLK_VDO0_DISP_MONITOR2, CLK_TOP_VPP, 7),
	GATE_VDO0_1(CLK_VDO0_DISP_MONITOR3, CLK_TOP_VPP, 8),
	GATE_VDO0_1(CLK_VDO0_DISP_MONITOR4, CLK_TOP_VPP, 9),
	GATE_VDO0_1(CLK_VDO0_SMI_GALS, CLK_TOP_VPP, 10),
	GATE_VDO0_1(CLK_VDO0_SMI_COMMON, CLK_TOP_VPP, 11),
	GATE_VDO0_1(CLK_VDO0_SMI_EMI, CLK_TOP_VPP, 12),
	GATE_VDO0_1(CLK_VDO0_SMI_IOMMU, CLK_TOP_VPP, 13),
	GATE_VDO0_1(CLK_VDO0_SMI_LARB, CLK_TOP_VPP, 14),
	GATE_VDO0_1(CLK_VDO0_SMI_RSI, CLK_TOP_VPP, 15),
	/* VDO0_2 */
	GATE_VDO0_2(CLK_VDO0_DSI0_DSI, CLK_TOP_DSI_OCC, 0),
	GATE_VDO0_2(CLK_VDO0_DSI1_DSI, CLK_TOP_DSI_OCC, 8),
	GATE_VDO0_2(CLK_VDO0_DP_INTF0_DP_INTF, CLK_TOP_EDP, 16),
};

extern const struct mtk_clk_tree mt8195_clk_tree;
static int mt8195_vdo0_probe(struct udevice *dev)
{
	return mtk_common_clk_gate_init(dev, &mt8195_clk_tree, vdo0_clks);
}

static const struct udevice_id of_match_clk_mt8195_vdo0[] = {
	{ .compatible = "mediatek,mt8195-vdo0", },
	{ }
};

U_BOOT_DRIVER(mtk_clk_vdo0) = {
	.name = "mt8195-vdo0",
	.id = UCLASS_CLK,
	.of_match = of_match_clk_mt8195_vdo0,
	.probe = mt8195_vdo0_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_gate_ops,
	.flags = DM_FLAG_PRE_RELOC,
};
