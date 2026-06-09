#ifndef __BEEP_IIO_KFIFO_BUF_H__
#define __BEEP_IIO_KFIFO_BUF_H__

#include <beep/kfifo.h>
#include <beep/iio/iio.h>
#include <beep/iio/buffer.h>

struct iio_buffer *iio_kfifo_allocate(struct iio_dev *indio_dev);
void iio_kfifo_free(struct iio_buffer *r);

#endif
