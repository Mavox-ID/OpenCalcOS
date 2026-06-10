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
#ifndef __KVM_ASYNC_PF_H__
#define __KVM_ASYNC_PF_H__

#ifdef CONFIG_KVM_ASYNC_PF
int kvm_async_pf_init(void);
void kvm_async_pf_deinit(void);
void kvm_async_pf_vcpu_init(struct kvm_vcpu *vcpu);
#else
#define kvm_async_pf_init() (0)
#define kvm_async_pf_deinit() do{}while(0)
#define kvm_async_pf_vcpu_init(C) do{}while(0)
#endif

#endif
