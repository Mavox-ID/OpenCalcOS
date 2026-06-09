#ifndef _BEEP_VIRTIO_RING_H
#define _BEEP_VIRTIO_RING_H

#include <beep/irqreturn.h>
#include <uapi/beep/virtio_ring.h>

struct virtio_device;
struct virtqueue;

struct virtqueue *vring_new_virtqueue(unsigned int index,
				      unsigned int num,
				      unsigned int vring_align,
				      struct virtio_device *vdev,
				      bool weak_barriers,
				      void *pages,
				      void (*notify)(struct virtqueue *vq),
				      void (*callback)(struct virtqueue *vq),
				      const char *name);
void vring_del_virtqueue(struct virtqueue *vq);
/* Filter out transport-specific feature bits. */
void vring_transport_features(struct virtio_device *vdev);

irqreturn_t vring_interrupt(int irq, void *_vq);
#endif /* _BEEP_VIRTIO_RING_H */
