// SPDX-License-Identifier: GPL-2.0
/*
 * MediaTek clock driver for MT8192 SoC
 *
 */

#include <dm.h>
#include <asm/io.h>
#include <dt-bindings/clock/mt8192-clk.h>

#include "clk-mtk.h"

#define MT8192_PLL_FMAX		(3800UL * MHZ)
#define MT8192_PLL_FMIN		(1500UL * MHZ)
#define MT8192_INTEGER_BITS 8

#define PLL(_id, _name, _reg, _pwr_reg, _en_mask, _flags,		\
	    _rst_bar_mask, _pcwbits, _pd_reg, _pd_shift,		\
	    _tuner_reg, _tuner_en_reg, _tuner_en_bit,			\
	    _pcw_reg, _pcw_shift, _pcw_chg_reg,				\
	    _en_reg, _pll_en_bit) {					\
		.id = _id,						\
		.reg = _reg,						\
		.pwr_reg = _pwr_reg,					\
		.en_mask = _en_mask,					\
		.rst_bar_mask = _rst_bar_mask,				\
		.fmax = MT8192_PLL_FMAX,				\
		.fmin = MT8192_PLL_FMIN,				\
		.flags = _flags,					\
		.pcwbits = _pcwbits,					\
		.pcwibits = MT8192_INTEGER_BITS,			\
		.pd_reg = _pd_reg,					\
		.pd_shift = _pd_shift,					\
		.pcw_reg = _pcw_reg,					\
		.pcw_shift = _pcw_shift,				\
		.pcw_chg_reg = _pcw_chg_reg,				\
	}

#define PLL_B(_id, _name, _reg, _pwr_reg, _en_mask, _flags,		\
			_rst_bar_mask, _pcwbits, _pd_reg, _pd_shift,	\
			_tuner_reg, _tuner_en_reg, _tuner_en_bit,	\
			_pcw_reg, _pcw_shift)				\
		PLL(_id, _name, _reg, _pwr_reg, _en_mask, _flags,	\
			_rst_bar_mask, _pcwbits, _pd_reg, _pd_shift,	\
			_tuner_reg, _tuner_en_reg, _tuner_en_bit,	\
			_pcw_reg, _pcw_shift, 0, 0, 0)

static const struct mtk_pll_data apmixed_plls[] = {
	PLL_B(CLK_APMIXED_MAINPLL, "mainpll", 0x0340, 0x034c, 0xff000000,
	      HAVE_RST_BAR, BIT(23), 22, 0x0344, 24, 0, 0, 0, 0x0344, 0),
};

static const struct mtk_fixed_clk top_fixed_clks[] = {
	FIXED_CLK(CLK_TOP_ULPOSC, 0, 260000000),
	FIXED_CLK(CLK_TOP_CLK26M, CLK_XTAL, 26000000),
};

static const struct mtk_fixed_factor top_fixed_divs[] = {
	FACTOR(CLK_TOP_MAINPLL_D3, CLK_APMIXED_MAINPLL, 1, 3, CLK_PARENT_APMIXED),
};

static const int axi_parents[] = {
	CLK_TOP_CLK26M,
};

static const struct mtk_composite top_muxes[] = {
	MUX_GATE(CLK_TOP_AXI_SEL, axi_parents, 0x010, 0, 3, 7),
};

const struct mtk_clk_tree mt8192_clk_tree = {
	.xtal_rate = 26 * MHZ,
	.xtal2_rate = 26 * MHZ,
	.fdivs_offs = CLK_TOP_MAINPLL_D3,
	.muxes_offs = CLK_TOP_AXI_SEL,
	.plls = apmixed_plls,
	.fclks = top_fixed_clks,
	.fdivs = top_fixed_divs,
	.muxes = top_muxes,
};

static const struct mtk_gate_regs infra0_cg_regs = {
	.set_ofs = 0x80,
	.clr_ofs = 0x84,
	.sta_ofs = 0x90,
};

static const struct mtk_gate_regs infra1_cg_regs = {
	.set_ofs = 0x88,
	.clr_ofs = 0x8c,
	.sta_ofs = 0x94,
};

static const struct mtk_gate_regs infra2_cg_regs = {
	.set_ofs = 0xa4,
	.clr_ofs = 0xa8,
	.sta_ofs = 0xac,
};

static const struct mtk_gate_regs infra3_cg_regs = {
	.set_ofs = 0xc0,
	.clr_ofs = 0xc4,
	.sta_ofs = 0xc8,
};

static const struct mtk_gate_regs infra4_cg_regs = {
	.set_ofs = 0xd0,
	.clr_ofs = 0xd4,
	.sta_ofs = 0xd8,
};

static const struct mtk_gate_regs infra5_cg_regs = {
	.set_ofs = 0xe0,
	.clr_ofs = 0xe4,
	.sta_ofs = 0xe8,
};

#define GATE_INFRA0(_id, _parent, _shift) {		\
		.id = _id,						\
		.parent = _parent,					\
		.regs = &infra0_cg_regs,				\
		.shift = _shift,					\
		.flags = CLK_GATE_SETCLR | CLK_PARENT_TOPCKGEN,		\
	}

static const struct mtk_gate infra_clks[] = {
	GATE_INFRA0(CLK_INFRA_PMIC_TMR, CLK_TOP_PWRAP_ULPOSC_SEL, 0),
};

static int mt8192_apmixedsys_probe(struct udevice *dev)
{
	return mtk_common_clk_init(dev, &mt8192_clk_tree);
}

static int mt8192_topckgen_probe(struct udevice *dev)
{
	return mtk_common_clk_init(dev, &mt8192_clk_tree);
}

static int mt8192_infracfg_probe(struct udevice *dev)
{
	return mtk_common_clk_gate_init(dev, &mt8192_clk_tree, infra_clks);
}

static const struct udevice_id mt8192_apmixed_compat[] = {
	{ .compatible = "mediatek,mt8192-apmixedsys", },
	{ }
};

static const struct udevice_id mt8192_topckgen_compat[] = {
	{ .compatible = "mediatek,mt8192-topckgen", },
	{ }
};

static const struct udevice_id mt8192_infracfg_compat[] = {
	{ .compatible = "mediatek,mt8192-infracfg", },
	{ }
};

U_BOOT_DRIVER(mtk_clk_apmixedsys) = {
	.name = "mt8192-apmixedsys",
	.id = UCLASS_CLK,
	.of_match = mt8192_apmixed_compat,
	.probe = mt8192_apmixedsys_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_apmixedsys_ops,
	.flags = DM_FLAG_PRE_RELOC,
};

U_BOOT_DRIVER(mtk_clk_topckgen) = {
	.name = "mt8192-topckgen",
  .id = UCLASS_CLK,
	.of_match = mt8192_topckgen_compat,
	.probe = mt8192_topckgen_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_topckgen_ops,
	.flags = DM_FLAG_PRE_RELOC,
};

U_BOOT_DRIVER(mtk_clk_infracfg) = {
	.name = "mt8192-infracfg",
	.id = UCLASS_CLK,
	.of_match = mt8192_infracfg_compat,
	.probe = mt8192_infracfg_probe,
	.priv_auto = sizeof(struct mtk_clk_priv),
	.ops = &mtk_clk_gate_ops,
	.flags = DM_FLAG_PRE_RELOC,
};
