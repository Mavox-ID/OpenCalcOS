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
#ifdef CONFIG_DRM_EXYNOS_G2D
extern int exynos_g2d_get_ver_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv);
extern int exynos_g2d_set_cmdlist_ioctl(struct drm_device *dev, void *data,
					struct drm_file *file_priv);
extern int exynos_g2d_exec_ioctl(struct drm_device *dev, void *data,
				 struct drm_file *file_priv);
#else
static inline int exynos_g2d_get_ver_ioctl(struct drm_device *dev, void *data,
					   struct drm_file *file_priv)
{
	return -ENODEV;
}

static inline int exynos_g2d_set_cmdlist_ioctl(struct drm_device *dev,
					       void *data,
					       struct drm_file *file_priv)
{
	return -ENODEV;
}

static inline int exynos_g2d_exec_ioctl(struct drm_device *dev, void *data,
					struct drm_file *file_priv)
{
	return -ENODEV;
}
#endif
