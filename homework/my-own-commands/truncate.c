/**
 * This program demonstrates invocation of the truncate
 * system call (92) using the syscall function.
 *
 * The commandline arguments for this function are assumed
 * to be a file name and then a length (in bytes).
 * If the file is longer than the length provided, the extra
 * bytes are deleted.  If the file is shorter, null bytes are
 * concatenated onto the end of the file.
 */
#include <linux/types.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *path = argv[1];
  off_t length = atoi(argv[2]);
  int result = syscall(92, path, length);

  if (result == -1) {
    char *errorMessage = "Oh no! Your file was not truncated. Check your parameters\n";
    syscall(4, 2, errorMessage, strlen(errorMessage));
  }
  return result;
}
