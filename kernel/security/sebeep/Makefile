#
# Makefile for building the SEBeep module as part of the kernel tree.
#

obj-$(CONFIG_SECURITY_SEBEEP) := sebeep.o

sebeep-y := avc.o hooks.o sebeepfs.o netlink.o nlmsgtab.o netif.o \
	     netnode.o netport.o exports.o \
	     ss/ebitmap.o ss/hashtab.o ss/symtab.o ss/sidtab.o ss/avtab.o \
	     ss/policydb.o ss/services.o ss/conditional.o ss/mls.o ss/status.o

sebeep-$(CONFIG_SECURITY_NETWORK_XFRM) += xfrm.o

sebeep-$(CONFIG_NETLABEL) += netlabel.o

ccflags-y := -Isecurity/sebeep -Isecurity/sebeep/include

$(addprefix $(obj)/,$(sebeep-y)): $(obj)/flask.h

quiet_cmd_flask = GEN     $(obj)/flask.h $(obj)/av_permissions.h
      cmd_flask = scripts/sebeep/genheaders/genheaders $(obj)/flask.h $(obj)/av_permissions.h

targets += flask.h av_permissions.h
$(obj)/flask.h: $(src)/include/classmap.h FORCE
	$(call if_changed,flask)
