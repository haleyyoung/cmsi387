*Note that this howto page is specifically for the Ubuntu 3.5.0-25-generic kernel*

General Building Steps
======================

From Dr. Dionisio's "Linux Kernel Building and Modification -- A Conceptual Guide" handout:

>  * Acquire the kernel source code
>  * Acquire prerequisite software
>  * Linux kernel code supports multiple architectures--be aware that not all source files will apply to your build
>  * Configure the kernel (for your architecture)
>  * Start the actual build sequence
>  * Install the build products

Modification Steps
==================

The first thing you need to do is add your new syscall to the syscall table.
Depending on the kernel you've obtained, the location of this file may be
different from that described here, but in general, you're looking for a file
with a name close to "syscall_32.tbl". In my case, the file is located in

    ubuntu-quantal/arch/x86/syscalls/syscall_32.tbl

Once you locate this file, you will want to add the following line to the end of
the list of syscalls. Note that the first number is the hardcoded number that
can be used to directly call our new helloworld syscall. The second number
denotes the type of system we're working with. The third element of the line is
the name of the syscall if one wanted to call it on the commandline. The fourth
element of this line of code is the name of the function that will be called
when the system call is called.

~~~
350 i386    helloworld      sys_helloworld
~~~


Add your syscall to the syscall table - add your syscall to the file:

""

ubuntu-quantal/arch/m32r/kernel/syscall_table.S 
"    .long sys_helloworld"

ubuntu-quantal/arch/sh/kernel/syscalls_32.S
"    .long sys_helloworld"

ubuntu-quantal/arch/sh/include/asm/unistd_32.h

add: "#define __NR_helloworld     367"

add one more to the number: "#define NR_syscalls 368"

ubuntu-quantal/include/linux/syscalls.h
"asmlinkage long sys_helloworld(void);"


in the root directory of the operating system add a folder called "test"
then add a file called "sys_helloworld.c" with the following code in it:

"#include <linux/kernel.h>

asmlinkage long sys_helloworld(void) {
    printk("Hello world! This freaking rocks!\n");
    return 0;
}"

add a file called "Makefile" to the test directory and add this line to it:
"obj-y := sys_helloworld.o"

in ubuntu-quantal/Makfile add "test/" to the end of the line that says:
"core-y		+= kernel/ mm/ fs/ ipc/ security/ crypto/ block/"

build your kernel using these two commands at the root directory of your operating system (this takes me 2 hours):

fakeroot debian/rules clean
fakeroot debian/rules binary-headers binary-generic

then go up one directory and use these two commands:

sudo dpkg -i linux*2.6.38-7.37*.deb
sudo reboot

once your system has rebooted, create a c program which calls your newly built system call:

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


to check to see if your syscall worked, check your kernel log:

use this command "tail -f /var/log/kern.log" to see the kernel log and wait to see your hello-world output at the end of the list!




Used this webpage for guidance:
http://arvindsraj.wordpress.com/2012/10/05/adding-hello-world-system-call-to-linux/
http://stackoverflow.com/questions/12469836/how-to-write-system-calls-on-debian-ubuntu
https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel
