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
#ifndef S5P_MFC_DEC_H_
#define S5P_MFC_DEC_H_

struct s5p_mfc_codec_ops *get_dec_codec_ops(void);
struct vb2_ops *get_dec_queue_ops(void);
const struct v4l2_ioctl_ops *get_dec_v4l2_ioctl_ops(void);
struct s5p_mfc_fmt *get_dec_def_fmt(bool src);
int s5p_mfc_dec_ctrls_setup(struct s5p_mfc_ctx *ctx);
void s5p_mfc_dec_ctrls_delete(struct s5p_mfc_ctx *ctx);
void s5p_mfc_dec_init(struct s5p_mfc_ctx *ctx);

#endif /* S5P_MFC_DEC_H_ */
