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
#include <beep/kernel.h>
#include <beep/export.h>
#include <sound/core.h>
#include <sound/control.h>

#define jack_detect_kctl_info	snd_ctl_boolean_mono_info

static int jack_detect_kctl_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	ucontrol->value.integer.value[0] = kcontrol->private_value;
	return 0;
}

static struct snd_kcontrol_new jack_detect_kctl = {
	/* name is filled later */
	.iface = SNDRV_CTL_ELEM_IFACE_CARD,
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = jack_detect_kctl_info,
	.get = jack_detect_kctl_get,
};

struct snd_kcontrol *
snd_kctl_jack_new(const char *name, int idx, void *private_data)
{
	struct snd_kcontrol *kctl;
	kctl = snd_ctl_new1(&jack_detect_kctl, private_data);
	if (!kctl)
		return NULL;
	snprintf(kctl->id.name, sizeof(kctl->id.name), "%s Jack", name);
	kctl->id.index = idx;
	kctl->private_value = 0;
	return kctl;
}
EXPORT_SYMBOL_GPL(snd_kctl_jack_new);

void snd_kctl_jack_report(struct snd_card *card,
			  struct snd_kcontrol *kctl, bool status)
{
	if (kctl->private_value == status)
		return;
	kctl->private_value = status;
	snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
}
EXPORT_SYMBOL_GPL(snd_kctl_jack_report);
