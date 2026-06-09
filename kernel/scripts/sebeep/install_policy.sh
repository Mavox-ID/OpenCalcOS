#!/bin/sh
if [ `id -u` -ne 0 ]; then
	echo "$0: must be root to install the sebeep policy"
	exit 1
fi
SF=`which setfiles`
if [ $? -eq 1 ]; then
	if [ -f /sbin/setfiles ]; then
		SF="/usr/setfiles"
	else
		echo "no sebeep tools installed: setfiles"
		exit 1
	fi
fi

cd mdp

CP=`which checkpolicy`
VERS=`$CP -V | awk '{print $1}'`

./mdp policy.conf file_contexts
$CP -o policy.$VERS policy.conf

mkdir -p /etc/sebeep/dummy/policy
mkdir -p /etc/sebeep/dummy/contexts/files

cp file_contexts /etc/sebeep/dummy/contexts/files
cp dbus_contexts /etc/sebeep/dummy/contexts
cp policy.$VERS /etc/sebeep/dummy/policy
FC_FILE=/etc/sebeep/dummy/contexts/files/file_contexts

if [ ! -d /etc/sebeep ]; then
	mkdir -p /etc/sebeep
fi
if [ ! -f /etc/sebeep/config ]; then
	cat > /etc/sebeep/config << EOF
SEBEEP=enforcing
SEBEEPTYPE=dummy
EOF
else
	TYPE=`cat /etc/sebeep/config | grep "^SEBEEPTYPE" | tail -1 | awk -F= '{ print $2 '}`
	if [ "eq$TYPE" != "eqdummy" ]; then
		sebeepenabled
		if [ $? -eq 0 ]; then
			echo "SEBeep already enabled with a non-dummy policy."
			echo "Exiting.  Please install policy by hand if that"
			echo "is what you REALLY want."
			exit 1
		fi
		mv /etc/sebeep/config /etc/sebeep/config.mdpbak
		grep -v "^SEBEEPTYPE" /etc/sebeep/config.mdpbak >> /etc/sebeep/config
		echo "SEBEEPTYPE=dummy" >> /etc/sebeep/config
	fi
fi

cd /etc/sebeep/dummy/contexts/files
$SF file_contexts /

mounts=`cat /proc/$$/mounts | egrep "ext2|ext3|xfs|jfs|ext4|ext4dev|gfs2" | awk '{ print $2 '}`
$SF file_contexts $mounts


dodev=`cat /proc/$$/mounts | grep "/dev "`
if [ "eq$dodev" != "eq" ]; then
	mount --move /dev /mnt
	$SF file_contexts /dev
	mount --move /mnt /dev
fi

