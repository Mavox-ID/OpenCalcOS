/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
static pfm_reg_desc_t pfm_gen_pmc_desc[PMU_MAX_PMCS]={
/* pmc0  */ { PFM_REG_CONTROL , 0, 0x1UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc1  */ { PFM_REG_CONTROL , 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc2  */ { PFM_REG_CONTROL , 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc3  */ { PFM_REG_CONTROL , 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc4  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {RDEP(4),0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc5  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {RDEP(5),0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc6  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {RDEP(6),0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
/* pmc7  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {RDEP(7),0UL, 0UL, 0UL}, {0UL,0UL, 0UL, 0UL}},
	    { PFM_REG_END     , 0, 0x0UL, -1UL, NULL, NULL, {0,}, {0,}}, /* end marker */
};

static pfm_reg_desc_t pfm_gen_pmd_desc[PMU_MAX_PMDS]={
/* pmd0  */ { PFM_REG_NOTIMPL , 0, 0x0UL, -1UL, NULL, NULL, {0,}, {0,}},
/* pmd1  */ { PFM_REG_NOTIMPL , 0, 0x0UL, -1UL, NULL, NULL, {0,}, {0,}},
/* pmd2  */ { PFM_REG_NOTIMPL , 0, 0x0UL, -1UL, NULL, NULL, {0,}, {0,}},
/* pmd3  */ { PFM_REG_NOTIMPL , 0, 0x0UL, -1UL, NULL, NULL, {0,}, {0,}},
/* pmd4  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {RDEP(4),0UL, 0UL, 0UL}},
/* pmd5  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {RDEP(5),0UL, 0UL, 0UL}},
/* pmd6  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {RDEP(6),0UL, 0UL, 0UL}},
/* pmd7  */ { PFM_REG_COUNTING, 0, 0x0UL, -1UL, NULL, NULL, {0UL,0UL, 0UL, 0UL}, {RDEP(7),0UL, 0UL, 0UL}},
	    { PFM_REG_END     , 0, 0x0UL, -1UL, NULL, NULL, {0,}, {0,}}, /* end marker */
};

/*
 * impl_pmcs, impl_pmds are computed at runtime to minimize errors!
 */
static pmu_config_t pmu_conf_gen={
	.pmu_name   = "Generic",
	.pmu_family = 0xff, /* any */
	.ovfl_val   = (1UL << 32) - 1,
	.num_ibrs   = 0, /* does not use */
	.num_dbrs   = 0, /* does not use */
	.pmd_desc   = pfm_gen_pmd_desc,
	.pmc_desc   = pfm_gen_pmc_desc
};

