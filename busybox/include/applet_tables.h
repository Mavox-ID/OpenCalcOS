/* This is a generated file, don't edit */

#define NUM_APPLETS 56
#define KNOWN_APPNAME_OFFSETS 4

const uint16_t applet_nameofs[] ALIGN2 = {
70,
162,
247,
};

const char applet_names[] ALIGN1 = ""
"[" "\0"
"[[" "\0"
"basename" "\0"
"bash" "\0"
"cat" "\0"
"chmod" "\0"
"clear" "\0"
"cp" "\0"
"dd" "\0"
"dirname" "\0"
"dmesg" "\0"
"echo" "\0"
"find" "\0"
"free" "\0"
"hd" "\0"
"hexdump" "\0"
"hexedit" "\0"
"hush" "\0"
"i2cdetect" "\0"
"i2cdump" "\0"
"i2cget" "\0"
"i2cset" "\0"
"i2ctransfer" "\0"
"init" "\0"
"kill" "\0"
"linuxrc" "\0"
"ln" "\0"
"ls" "\0"
"mkdir" "\0"
"mount" "\0"
"mountpoint" "\0"
"mv" "\0"
"poweroff" "\0"
"printf" "\0"
"ps" "\0"
"pwd" "\0"
"reboot" "\0"
"rm" "\0"
"rmdir" "\0"
"setsid" "\0"
"sh" "\0"
"sha256sum" "\0"
"sleep" "\0"
"su" "\0"
"test" "\0"
"top" "\0"
"touch" "\0"
"true" "\0"
"umount" "\0"
"uname" "\0"
"uptime" "\0"
"vi" "\0"
"watch" "\0"
"which" "\0"
"xxd" "\0"
"yes" "\0"
;

#define APPLET_NO_basename 2
#define APPLET_NO_bash 3
#define APPLET_NO_cat 4
#define APPLET_NO_chmod 5
#define APPLET_NO_clear 6
#define APPLET_NO_cp 7
#define APPLET_NO_dd 8
#define APPLET_NO_dirname 9
#define APPLET_NO_dmesg 10
#define APPLET_NO_echo 11
#define APPLET_NO_find 12
#define APPLET_NO_free 13
#define APPLET_NO_hd 14
#define APPLET_NO_hexdump 15
#define APPLET_NO_hexedit 16
#define APPLET_NO_hush 17
#define APPLET_NO_i2cdetect 18
#define APPLET_NO_i2cdump 19
#define APPLET_NO_i2cget 20
#define APPLET_NO_i2cset 21
#define APPLET_NO_i2ctransfer 22
#define APPLET_NO_init 23
#define APPLET_NO_kill 24
#define APPLET_NO_linuxrc 25
#define APPLET_NO_ln 26
#define APPLET_NO_ls 27
#define APPLET_NO_mkdir 28
#define APPLET_NO_mount 29
#define APPLET_NO_mountpoint 30
#define APPLET_NO_mv 31
#define APPLET_NO_poweroff 32
#define APPLET_NO_printf 33
#define APPLET_NO_ps 34
#define APPLET_NO_pwd 35
#define APPLET_NO_reboot 36
#define APPLET_NO_rm 37
#define APPLET_NO_rmdir 38
#define APPLET_NO_setsid 39
#define APPLET_NO_sh 40
#define APPLET_NO_sha256sum 41
#define APPLET_NO_sleep 42
#define APPLET_NO_su 43
#define APPLET_NO_test 44
#define APPLET_NO_top 45
#define APPLET_NO_touch 46
#define APPLET_NO_true 47
#define APPLET_NO_umount 48
#define APPLET_NO_uname 49
#define APPLET_NO_uptime 50
#define APPLET_NO_vi 51
#define APPLET_NO_watch 52
#define APPLET_NO_which 53
#define APPLET_NO_xxd 54
#define APPLET_NO_yes 55

#ifndef SKIP_applet_main
int (*const applet_main[])(int argc, char **argv) = {
test_main,
test_main,
basename_main,
hush_main,
cat_main,
chmod_main,
clear_main,
cp_main,
dd_main,
dirname_main,
dmesg_main,
echo_main,
find_main,
free_main,
hexdump_main,
hexdump_main,
hexedit_main,
hush_main,
i2cdetect_main,
i2cdump_main,
i2cget_main,
i2cset_main,
i2ctransfer_main,
init_main,
kill_main,
init_main,
ln_main,
ls_main,
mkdir_main,
mount_main,
mountpoint_main,
mv_main,
halt_main,
printf_main,
ps_main,
pwd_main,
halt_main,
rm_main,
rmdir_main,
setsid_main,
hush_main,
md5_sha1_sum_main,
sleep_main,
su_main,
test_main,
top_main,
touch_main,
true_main,
umount_main,
uname_main,
uptime_main,
vi_main,
watch_main,
which_main,
xxd_main,
yes_main,
};
#endif

const uint8_t applet_suid[] ALIGN1 = {
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x80,
0x00,
0x00,
0x00,
};

const uint8_t applet_install_loc[] ALIGN1 = {
0x33,
0x13,
0x11,
0x13,
0x31,
0x11,
0x33,
0x33,
0x13,
0x44,
0x44,
0x24,
0x01,
0x11,
0x11,
0x11,
0x32,
0x11,
0x12,
0x31,
0x31,
0x11,
0x33,
0x11,
0x11,
0x13,
0x31,
0x33,
};
