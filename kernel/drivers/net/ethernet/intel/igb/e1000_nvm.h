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
#ifndef _E1000_NVM_H_
#define _E1000_NVM_H_

s32  igb_acquire_nvm(struct e1000_hw *hw);
void igb_release_nvm(struct e1000_hw *hw);
s32  igb_read_mac_addr(struct e1000_hw *hw);
s32  igb_read_part_num(struct e1000_hw *hw, u32 *part_num);
s32  igb_read_part_string(struct e1000_hw *hw, u8 *part_num,
                          u32 part_num_size);
s32  igb_read_nvm_eerd(struct e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32  igb_read_nvm_spi(struct e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32  igb_write_nvm_spi(struct e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32  igb_validate_nvm_checksum(struct e1000_hw *hw);
s32  igb_update_nvm_checksum(struct e1000_hw *hw);

struct e1000_fw_version {
	u32 etrack_id;
	u16 eep_major;
	u16 eep_minor;

	u8 invm_major;
	u8 invm_minor;
	u8 invm_img_type;

	bool or_valid;
	u16 or_major;
	u16 or_build;
	u16 or_patch;
};
void igb_get_fw_version(struct e1000_hw *hw, struct e1000_fw_version *fw_vers);

#endif
