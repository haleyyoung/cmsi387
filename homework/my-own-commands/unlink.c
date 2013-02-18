/**
 * This program demonstrates invocation of the truncate
 * system call (10) using the syscall function.
 *
 * The commandline arguments for this function are assumed
 * to be a file name and then a length (in bytes).
 *
 * This function "deletes a name from the filesystem. If that name was the last
 * link to a file and no processes have the file open the file is deleted and the
 * space it was using is made available for reuse.
 * If the name was the last link to a file but any processes still have the file
 * open the file will remain in existence until the last file descriptor referring
 * to it is closed.
 * If the name referred to a symbolic link the link is removed. If the name
 * referred to a socket, fifo or device the name for it is removed but processes
 * which have the object open may continue to use it."
 * http://www.tutorialspoint.com/unix_system_calls/unlink.htm
 */
#include <linux/types.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *path = argv[1];
  int result = syscall(10, path);

  if (result == -1) {
    char *errorMessage = "Oh no! Your file was deleted(unlinked). Check your path name\n";
    syscall(4, 2, errorMessage, strlen(errorMessage));
  }
  return result;
}
