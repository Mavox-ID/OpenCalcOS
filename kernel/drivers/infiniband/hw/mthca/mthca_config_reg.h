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
#ifndef MTHCA_CONFIG_REG_H
#define MTHCA_CONFIG_REG_H

#define MTHCA_HCR_BASE         0x80680
#define MTHCA_HCR_SIZE         0x0001c
#define MTHCA_ECR_BASE         0x80700
#define MTHCA_ECR_SIZE         0x00008
#define MTHCA_ECR_CLR_BASE     0x80708
#define MTHCA_ECR_CLR_SIZE     0x00008
#define MTHCA_MAP_ECR_SIZE     (MTHCA_ECR_SIZE + MTHCA_ECR_CLR_SIZE)
#define MTHCA_CLR_INT_BASE     0xf00d8
#define MTHCA_CLR_INT_SIZE     0x00008
#define MTHCA_EQ_SET_CI_SIZE   (8 * 32)

#endif /* MTHCA_CONFIG_REG_H */
