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

static const struct mtk_gate_regs vdo1_0_cg_regs = {
	.set_ofs = 0x104,
	.clr_ofs = 0x108,
	.sta_ofs = 0x100,
};

static const struct mtk_gate_regs vdo1_1_cg_regs = {
	.set_ofs = 0x124,
	.clr_ofs = 0x128,
	.sta_ofs = 0x120,
};

static const struct mtk_gate_regs vdo1_2_cg_regs = {
	.set_ofs = 0x134,
	.clr_ofs = 0x138,
	.sta_ofs = 0x130,
};

static const struct mtk_gate_regs vdo1_3_cg_regs = {
	.set_ofs = 0x144,
	.clr_ofs = 0x148,
	.sta_ofs = 0x140,
};

#define GATE_VDO1_0(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo1_0_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VDO1_1(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo1_1_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VDO1_2(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo1_2_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VDO1_3(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vdo1_3_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

static const struct mtk_gate vdo1_clks[] = {
	/* VDO1_0 */
	GATE_VDO1_0(CLK_VDO1_SMI_LARB2, CLK_TOP_VPP, 0),
	GATE_VDO1_0(CLK_VDO1_SMI_LARB3, CLK_TOP_VPP, 1),
	GATE_VDO1_0(CLK_VDO1_GALS, CLK_TOP_VPP, 2),
	GATE_VDO1_0(CLK_VDO1_FAKE_ENG0, CLK_TOP_VPP, 3),
	GATE_VDO1_0(CLK_VDO1_FAKE_ENG, CLK_TOP_VPP, 4),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA0, CLK_TOP_VPP, 5),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA1, CLK_TOP_VPP, 6),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA2, CLK_TOP_VPP, 7),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA3, CLK_TOP_VPP, 8),
	GATE_VDO1_0(CLK_VDO1_VPP_MERGE0, CLK_TOP_VPP, 9),
	GATE_VDO1_0(CLK_VDO1_VPP_MERGE1, CLK_TOP_VPP, 10),
	GATE_VDO1_0(CLK_VDO1_VPP_MERGE2, CLK_TOP_VPP, 11),
	GATE_VDO1_0(CLK_VDO1_VPP_MERGE3, CLK_TOP_VPP, 12),
	GATE_VDO1_0(CLK_VDO1_VPP_MERGE4, CLK_TOP_VPP, 13),
	GATE_VDO1_0(CLK_VDO1_VPP2_TO_VDO1_DL_ASYNC, CLK_TOP_VPP, 14),
	GATE_VDO1_0(CLK_VDO1_VPP3_TO_VDO1_DL_ASYNC, CLK_TOP_VPP, 15),
	GATE_VDO1_0(CLK_VDO1_DISP_MUTEX, CLK_TOP_VPP, 16),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA4, CLK_TOP_VPP, 17),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA5, CLK_TOP_VPP, 18),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA6, CLK_TOP_VPP, 19),
	GATE_VDO1_0(CLK_VDO1_MDP_RDMA7, CLK_TOP_VPP, 20),
	GATE_VDO1_0(CLK_VDO1_DP_INTF0_MM, CLK_TOP_VPP, 21),
	GATE_VDO1_0(CLK_VDO1_DPI0_MM, CLK_TOP_VPP, 22),
	GATE_VDO1_0(CLK_VDO1_DPI1_MM, CLK_TOP_VPP, 23),
	GATE_VDO1_0(CLK_VDO1_DISP_MONITOR, CLK_TOP_VPP, 24),
	GATE_VDO1_0(CLK_VDO1_MERGE0_DL_ASYNC, CLK_TOP_VPP, 25),
	GATE_VDO1_0(CLK_VDO1_MERGE1_DL_ASYNC, CLK_TOP_VPP, 26),
	GATE_VDO1_0(CLK_VDO1_MERGE2_DL_ASYNC, CLK_TOP_VPP, 27),
	GATE_VDO1_0(CLK_VDO1_MERGE3_DL_ASYNC, CLK_TOP_VPP, 28),
	GATE_VDO1_0(CLK_VDO1_MERGE4_DL_ASYNC, CLK_TOP_VPP, 29),
	GATE_VDO1_0(CLK_VDO1_VDO0_DSC_TO_VDO1_DL_ASYNC,
		    CLK_TOP_VPP, 30),
	GATE_VDO1_0(CLK_VDO1_VDO0_MERGE_TO_VDO1_DL_ASYNC,
		    CLK_TOP_VPP, 31),
	/* VDO1_1 */
	GATE_VDO1_1(CLK_VDO1_HDR_VDO_FE0, CLK_TOP_VPP, 0),
	GATE_VDO1_1(CLK_VDO1_HDR_GFX_FE0, CLK_TOP_VPP, 1),
	GATE_VDO1_1(CLK_VDO1_HDR_VDO_BE, CLK_TOP_VPP, 2),
	GATE_VDO1_1(CLK_VDO1_HDR_VDO_FE1, CLK_TOP_VPP, 16),
	GATE_VDO1_1(CLK_VDO1_HDR_GFX_FE1, CLK_TOP_VPP, 17),
	GATE_VDO1_1(CLK_VDO1_DISP_MIXER, CLK_TOP_VPP, 18),
	GATE_VDO1_1(CLK_VDO1_HDR_VDO_FE0_DL_ASYNC, CLK_TOP_VPP, 19),
	GATE_VDO1_1(CLK_VDO1_HDR_VDO_FE1_DL_ASYNC, CLK_TOP_VPP, 20),
	GATE_VDO1_1(CLK_VDO1_HDR_GFX_FE0_DL_ASYNC, CLK_TOP_VPP, 21),
	GATE_VDO1_1(CLK_VDO1_HDR_GFX_FE1_DL_ASYNC, CLK_TOP_VPP, 22),
	GATE_VDO1_1(CLK_VDO1_HDR_VDO_BE_DL_ASYNC, CLK_TOP_VPP, 23),
	/* VDO1_2 */
	GATE_VDO1_2(CLK_VDO1_DPI0, CLK_TOP_VPP, 0),
	GATE_VDO1_2(CLK_VDO1_DISP_MONITOR_DPI0, CLK_TOP_VPP, 1),
	GATE_VDO1_2(CLK_VDO1_DPI1, CLK_TOP_VPP, 8),
	GATE_VDO1_2(CLK_VDO1_DISP_MONITOR_DPI1, CLK_TOP_VPP, 9),
	GATE_VDO1_2(CLK_VDO1_DPINTF, CLK_TOP_VPP, 16),
	GATE_VDO1_2(CLK_VDO1_DISP_MONITOR_DPINTF, CLK_TOP_VPP, 17),

	/* VDO1_3 */
	GATE_VDO1_3(CLK_VDO1_26M_SLOW, CLK_TOP_CLK26M, 8),
};

extern const struct mtk_clk_tree mt8195_clk_tree;
static int mt8195_vdo1_probe(struct udevice *dev)
{
	return mtk_common_clk_gate_init(dev, &mt8195_clk_tree, vdo1_clks);
}

static const struct udevice_id of_match_clk_mt8195_vdo1[] = {
	{ .compatible = "mediatek,mt8195-vdo1", },
	{ }
};

U_BOOT_DRIVER(mtk_clk_vdo1) = {
	.name = "mt8195-vdo1",
	.id = UCLASS_CLK,
	.of_match = of_match_clk_mt8195_vdo1,
	.probe = mt8195_vdo1_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_gate_ops,
	.flags = DM_FLAG_PRE_RELOC,
};
