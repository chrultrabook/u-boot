// SPDX-License-Identifier: GPL-2.0-only
/*
 */

#include <dm.h>
#include <asm/io.h>
#include <dt-bindings/clock/mt8192-clk.h>
#include <linux/bitops.h>
#include <stdio.h>

#include "clk-mtk.h"

static const struct mtk_gate_regs msdc_top_cg_regs = {
	.set_ofs = 0x0,
	.clr_ofs = 0x0,
	.sta_ofs = 0x0,
};

#define GATE_MSDC_TOP(_id, _parent, _shift) {		\
		.id = _id,						\
		.parent = _parent,					\
		.regs = &msdc_top_cg_regs,				\
		.shift = _shift,					\
		.flags = CLK_GATE_SETCLR | CLK_PARENT_TOPCKGEN,		\
	}

static const struct mtk_gate msdc_top_clks[] = {
	GATE_MSDC_TOP(CLK_MSDC_TOP_AES_0P, CLK_TOP_AES_MSDCFDE_SEL, 0),
	GATE_MSDC_TOP(CLK_MSDC_TOP_SRC_0P, CLK_INFRA_MSDC0_SRC, 1),
	GATE_MSDC_TOP(CLK_MSDC_TOP_SRC_1P, CLK_INFRA_MSDC1_SRC, 2),
	GATE_MSDC_TOP(CLK_MSDC_TOP_SRC_2P, CLK_INFRA_MSDC2_SRC, 3),
	GATE_MSDC_TOP(CLK_MSDC_TOP_P_MSDC0, CLK_TOP_AXI_SEL, 4),
	GATE_MSDC_TOP(CLK_MSDC_TOP_P_MSDC1, CLK_TOP_AXI_SEL, 5),
	GATE_MSDC_TOP(CLK_MSDC_TOP_P_MSDC2, CLK_TOP_AXI_SEL, 6),
	GATE_MSDC_TOP(CLK_MSDC_TOP_P_CFG, CLK_TOP_AXI_SEL, 7),
	GATE_MSDC_TOP(CLK_MSDC_TOP_AXI, CLK_TOP_AXI_SEL, 8),
	GATE_MSDC_TOP(CLK_MSDC_TOP_H_MST_0P, CLK_INFRA_MSDC0, 9),
	GATE_MSDC_TOP(CLK_MSDC_TOP_H_MST_1P, CLK_INFRA_MSDC1, 10),
	GATE_MSDC_TOP(CLK_MSDC_TOP_H_MST_2P, CLK_INFRA_MSDC2, 11),
	GATE_MSDC_TOP(CLK_MSDC_TOP_MEM_OFF_DLY_26M, CLK_TOP_CLK26M, 12),
	GATE_MSDC_TOP(CLK_MSDC_TOP_32K, CLK_TOP_CLK32K, 13),
	GATE_MSDC_TOP(CLK_MSDC_TOP_AHB2AXI_BRG_AXI, CLK_TOP_AXI_SEL, 14),
};

extern const struct mtk_clk_tree mt8192_clk_tree;
static int mt8192_msdc_top(struct udevice *dev)
{
	printf("msdc clock init\n");
	return mtk_common_clk_gate_init(dev, &mt8192_clk_tree, msdc_top_clks);
}

static const struct udevice_id of_match_clk_mt8192_msdc_top[] = {
	{ .compatible = "mediatek,mt8192-msdc_top", },
	{ }
};

U_BOOT_DRIVER(mtk_clk_msdc_top) = {
	.name = "mt8192-msdc_top",
	.id = UCLASS_CLK,
	.of_match = of_match_clk_mt8192_msdc_top,
	.probe = mt8192_msdc_top,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_gate_ops,
	.flags = DM_FLAG_PRE_RELOC,
};
