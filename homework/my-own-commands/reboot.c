/**
 * This program demonstrates invocation of the sysinfo
 * system call (142) using the syscall function.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/reboot.h>

// For convenience, we just use the stdio functions to display
// the output for this one.
#include <stdio.h>

int main(int argc, char *argv[]) {
  int what = 0;
    printf("%d\n", what);
  what = syscall(88,  LINUX_REBOOT_MAGIC1,  LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART);
    printf("%d\n", what);
  return what;
}
