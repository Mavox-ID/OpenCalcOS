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
#ifndef __ASM_KVM_BOOKE_H__
#define __ASM_KVM_BOOKE_H__

#include <beep/types.h>
#include <beep/kvm_host.h>

/* LPIDs we support with this build -- runtime limit may be lower */
#define KVMPPC_NR_LPIDS                        64

static inline void kvmppc_set_gpr(struct kvm_vcpu *vcpu, int num, ulong val)
{
	vcpu->arch.gpr[num] = val;
}

static inline ulong kvmppc_get_gpr(struct kvm_vcpu *vcpu, int num)
{
	return vcpu->arch.gpr[num];
}

static inline void kvmppc_set_cr(struct kvm_vcpu *vcpu, u32 val)
{
	vcpu->arch.cr = val;
}

static inline u32 kvmppc_get_cr(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.cr;
}

static inline void kvmppc_set_xer(struct kvm_vcpu *vcpu, u32 val)
{
	vcpu->arch.xer = val;
}

static inline u32 kvmppc_get_xer(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.xer;
}

static inline u32 kvmppc_get_last_inst(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.last_inst;
}

static inline void kvmppc_set_ctr(struct kvm_vcpu *vcpu, ulong val)
{
	vcpu->arch.ctr = val;
}

static inline ulong kvmppc_get_ctr(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.ctr;
}

static inline void kvmppc_set_lr(struct kvm_vcpu *vcpu, ulong val)
{
	vcpu->arch.lr = val;
}

static inline ulong kvmppc_get_lr(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.lr;
}

static inline void kvmppc_set_pc(struct kvm_vcpu *vcpu, ulong val)
{
	vcpu->arch.pc = val;
}

static inline ulong kvmppc_get_pc(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.pc;
}

static inline ulong kvmppc_get_fault_dar(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.fault_dear;
}

static inline ulong kvmppc_get_msr(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.shared->msr;
}
#endif /* __ASM_KVM_BOOKE_H__ */
