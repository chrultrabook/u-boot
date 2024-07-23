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

static const struct mtk_gate_regs vpp0_0_cg_regs = {
	.set_ofs = 0x24,
	.clr_ofs = 0x28,
	.sta_ofs = 0x20,
};

static const struct mtk_gate_regs vpp0_1_cg_regs = {
	.set_ofs = 0x30,
	.clr_ofs = 0x34,
	.sta_ofs = 0x2c,
};

static const struct mtk_gate_regs vpp0_2_cg_regs = {
	.set_ofs = 0x3c,
	.clr_ofs = 0x40,
	.sta_ofs = 0x38,
};

#define GATE_VPP0_0(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vpp0_0_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VPP0_1(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vpp0_1_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

#define GATE_VPP0_2(_id, _parent, _shift)			\
	GATE_MTK_FLAGS(_id, _parent, &vpp0_2_cg_regs, _shift,\
		CLK_PARENT_TOPCKGEN | CLK_GATE_SETCLR)

static const struct mtk_gate vpp0_clks[] = {
	/* VPP0_0 */
	GATE_VPP0_0(CLK_VPP0_MDP_FG, CLK_TOP_VPP, 1),
	GATE_VPP0_0(CLK_VPP0_STITCH, CLK_TOP_VPP, 2),
	GATE_VPP0_0(CLK_VPP0_PADDING, CLK_TOP_VPP, 7),
	GATE_VPP0_0(CLK_VPP0_MDP_TCC, CLK_TOP_VPP, 8),
	GATE_VPP0_0(CLK_VPP0_WARP0_ASYNC_TX, CLK_TOP_VPP, 10),
	GATE_VPP0_0(CLK_VPP0_WARP1_ASYNC_TX, CLK_TOP_VPP, 11),
	GATE_VPP0_0(CLK_VPP0_MUTEX, CLK_TOP_VPP, 13),
	GATE_VPP0_0(CLK_VPP0_VPP02VPP1_RELAY, CLK_TOP_VPP, 14),
	GATE_VPP0_0(CLK_VPP0_VPP12VPP0_ASYNC, CLK_TOP_VPP, 15),
	GATE_VPP0_0(CLK_VPP0_MMSYSRAM_TOP, CLK_TOP_VPP, 16),
	GATE_VPP0_0(CLK_VPP0_MDP_AAL, CLK_TOP_VPP, 17),
	GATE_VPP0_0(CLK_VPP0_MDP_RSZ, CLK_TOP_VPP, 18),
	/* VPP0_1 */
	GATE_VPP0_1(CLK_VPP0_SMI_COMMON, CLK_TOP_VPP, 0),
	GATE_VPP0_1(CLK_VPP0_GALS_VDO0_LARB0, CLK_TOP_VPP, 1),
	GATE_VPP0_1(CLK_VPP0_GALS_VDO0_LARB1, CLK_TOP_VPP, 2),
	GATE_VPP0_1(CLK_VPP0_GALS_VENCSYS, CLK_TOP_VPP, 3),
	GATE_VPP0_1(CLK_VPP0_GALS_VENCSYS_CORE1, CLK_TOP_VPP, 4),
	GATE_VPP0_1(CLK_VPP0_GALS_INFRA, CLK_TOP_VPP, 5),
	GATE_VPP0_1(CLK_VPP0_GALS_CAMSYS, CLK_TOP_VPP, 6),
	GATE_VPP0_1(CLK_VPP0_GALS_VPP1_LARB5, CLK_TOP_VPP, 7),
	GATE_VPP0_1(CLK_VPP0_GALS_VPP1_LARB6, CLK_TOP_VPP, 8),
	GATE_VPP0_1(CLK_VPP0_SMI_REORDER, CLK_TOP_VPP, 9),
	GATE_VPP0_1(CLK_VPP0_SMI_IOMMU, CLK_TOP_VPP, 10),
	GATE_VPP0_1(CLK_VPP0_GALS_IMGSYS_CAMSYS, CLK_TOP_VPP, 11),
	GATE_VPP0_1(CLK_VPP0_MDP_RDMA, CLK_TOP_VPP, 12),
	GATE_VPP0_1(CLK_VPP0_MDP_WROT, CLK_TOP_VPP, 13),
	GATE_VPP0_1(CLK_VPP0_GALS_EMI0_EMI1, CLK_TOP_VPP, 16),
	GATE_VPP0_1(CLK_VPP0_SMI_SUB_COMMON_REORDER, CLK_TOP_VPP, 17),
	GATE_VPP0_1(CLK_VPP0_SMI_RSI, CLK_TOP_VPP, 18),
	GATE_VPP0_1(CLK_VPP0_SMI_COMMON_LARB4, CLK_TOP_VPP, 19),
	GATE_VPP0_1(CLK_VPP0_GALS_VDEC_VDEC_CORE1, CLK_TOP_VPP, 20),
	GATE_VPP0_1(CLK_VPP0_GALS_VPP1_WPE, CLK_TOP_VPP, 21),
	GATE_VPP0_1(CLK_VPP0_GALS_VDO0_VDO1_VENCSYS_CORE1, CLK_TOP_VPP, 22),
	GATE_VPP0_1(CLK_VPP0_FAKE_ENG, CLK_TOP_VPP, 23),
	GATE_VPP0_1(CLK_VPP0_MDP_HDR, CLK_TOP_VPP, 24),
	GATE_VPP0_1(CLK_VPP0_MDP_TDSHP, CLK_TOP_VPP, 25),
	GATE_VPP0_1(CLK_VPP0_MDP_COLOR, CLK_TOP_VPP, 26),
	GATE_VPP0_1(CLK_VPP0_MDP_OVL, CLK_TOP_VPP, 27),
	/* VPP0_2 */
	GATE_VPP0_2(CLK_VPP0_WARP0_RELAY, CLK_TOP_WPE_VPP, 0),
	GATE_VPP0_2(CLK_VPP0_WARP0_MDP_DL_ASYNC, CLK_TOP_WPE_VPP, 1),
	GATE_VPP0_2(CLK_VPP0_WARP1_RELAY, CLK_TOP_WPE_VPP, 2),
	GATE_VPP0_2(CLK_VPP0_WARP1_MDP_DL_ASYNC, CLK_TOP_WPE_VPP, 3),
};

extern const struct mtk_clk_tree mt8195_clk_tree;
static int mt8195_vpp0_probe(struct udevice *dev)
{
	return mtk_common_clk_gate_init(dev, &mt8195_clk_tree, vpp0_clks);
}

static const struct udevice_id of_match_clk_mt8195_vpp0[] = {
	{ .compatible = "mediatek,mt8195-vpp0", },
	{ }
};

U_BOOT_DRIVER(mtk_clk_vpp0) = {
	.name = "mt8195-vpp0",
	.id = UCLASS_CLK,
	.of_match = of_match_clk_mt8195_vpp0,
	.probe = mt8195_vpp0_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_gate_ops,
	.flags = DM_FLAG_PRE_RELOC,
};
