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
#ifndef CALLBACKS_H
#define CALLBACKS_H


extern void cb_out_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		     struct callb_data *data);

extern void cb_out_2(struct pcbit_dev *dev, struct pcbit_chan *chan,
		     struct callb_data *data);

extern void cb_in_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);
extern void cb_in_2(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);
extern void cb_in_3(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);

extern void cb_disc_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);
extern void cb_disc_2(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);
extern void cb_disc_3(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);

extern void cb_notdone(struct pcbit_dev *dev, struct pcbit_chan *chan,
		       struct callb_data *data);

extern void cb_selp_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);
extern void cb_open(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);

#endif
