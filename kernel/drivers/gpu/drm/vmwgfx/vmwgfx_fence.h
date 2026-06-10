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
#ifndef _VMWGFX_FENCE_H_

#define VMW_FENCE_WAIT_TIMEOUT (5*HZ)

struct vmw_private;

struct vmw_fence_manager;

/**
 *
 *
 */
enum vmw_action_type {
	VMW_ACTION_EVENT = 0,
	VMW_ACTION_MAX
};

struct vmw_fence_action {
	struct list_head head;
	enum vmw_action_type type;
	void (*seq_passed) (struct vmw_fence_action *action);
	void (*cleanup) (struct vmw_fence_action *action);
};

struct vmw_fence_obj {
	struct kref kref;
	u32 seqno;

	struct vmw_fence_manager *fman;
	struct list_head head;
	uint32_t signaled;
	uint32_t signal_mask;
	struct list_head seq_passed_actions;
	void (*destroy)(struct vmw_fence_obj *fence);
	wait_queue_head_t queue;
};

extern struct vmw_fence_manager *
vmw_fence_manager_init(struct vmw_private *dev_priv);

extern void vmw_fence_manager_takedown(struct vmw_fence_manager *fman);

extern void vmw_fence_obj_unreference(struct vmw_fence_obj **fence_p);

extern struct vmw_fence_obj *
vmw_fence_obj_reference(struct vmw_fence_obj *fence);

extern void vmw_fences_update(struct vmw_fence_manager *fman);

extern bool vmw_fence_obj_signaled(struct vmw_fence_obj *fence,
				   uint32_t flags);

extern int vmw_fence_obj_wait(struct vmw_fence_obj *fence, uint32_t flags,
			      bool lazy,
			      bool interruptible, unsigned long timeout);

extern void vmw_fence_obj_flush(struct vmw_fence_obj *fence);

extern int vmw_fence_create(struct vmw_fence_manager *fman,
			    uint32_t seqno,
			    uint32_t mask,
			    struct vmw_fence_obj **p_fence);

extern int vmw_user_fence_create(struct drm_file *file_priv,
				 struct vmw_fence_manager *fman,
				 uint32_t sequence,
				 uint32_t mask,
				 struct vmw_fence_obj **p_fence,
				 uint32_t *p_handle);

extern void vmw_fence_fifo_up(struct vmw_fence_manager *fman);

extern void vmw_fence_fifo_down(struct vmw_fence_manager *fman);

extern int vmw_fence_obj_wait_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv);

extern int vmw_fence_obj_signaled_ioctl(struct drm_device *dev, void *data,
					struct drm_file *file_priv);

extern int vmw_fence_obj_unref_ioctl(struct drm_device *dev, void *data,
				     struct drm_file *file_priv);
extern int vmw_fence_event_ioctl(struct drm_device *dev, void *data,
				 struct drm_file *file_priv);
extern void vmw_event_fence_fpriv_gone(struct vmw_fence_manager *fman,
				       struct list_head *event_list);
extern int vmw_event_fence_action_queue(struct drm_file *filee_priv,
					struct vmw_fence_obj *fence,
					struct drm_pending_event *event,
					uint32_t *tv_sec,
					uint32_t *tv_usec,
					bool interruptible);
#endif /* _VMWGFX_FENCE_H_ */
