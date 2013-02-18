/**
 * This program demonstrates invocation of the reboot
 * system call (88) using the syscall function.
 *
 * Note this system call must be run as sudo.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/reboot.h>

int main(int argc, char *argv[]) {
    syscall(88,  LINUX_REBOOT_MAGIC1,  LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART);
    return 0;
}
