#include <linux/types.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int result = syscall(350);

  if (result == -1) {
    char *errorMessage = "Oh no! My kernel fails";
  }
  return result;
}
