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
extern void simtec_audio_init(struct snd_soc_pcm_runtime *rtd);

extern int simtec_audio_core_probe(struct platform_device *pdev,
				   struct snd_soc_card *card);

extern int simtec_audio_remove(struct platform_device *pdev);

#ifdef CONFIG_PM
extern const struct dev_pm_ops simtec_audio_pmops;
#define simtec_audio_pm &simtec_audio_pmops
#else
#define simtec_audio_pm NULL
#endif
