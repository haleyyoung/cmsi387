CSI: Process
=======

**1.**

*Linux*

    hotMessLinux.png

*Mac OS X*

    hotMessMac.png

**2.**

*Linux*

    threadsLinux1.png, threadsLinux2.png, threadsLinux3.png, threadsLinux4.png

*Mac OS X*

    threadsMac1.png, threadsMac2.png, threadsMac3.png, threadsMac4.png, threadsMac5.png

    Each of these sets of pictures corresponds to running Sum.java once with large numbers
for input. The threadsLinux* images start with the maximum number of threads shown
with `ps -eLf`. The pictures were taken with successive calls to `ps -eLf` and
show that with 6 arguments, there are 20 threads of the Java process. This decreases
down to 15 threads when the last argument is being processed.

    The threadsMac* images show Sum.java being run as process 18753. The pictures were
taken one after another with Sum.java being run with 6 arguments. There are initially
30 threads of the Java process and this decreases down to 25 threads when the
last argument is being processed.

    The main difference between Mac and linux is that they visually display the threads
differently. Mac displays them all under one process ID on one line and the total
number of threads is displayed as a column in the window. Linux displays all the
threads as separate lines, but then still gives them the same process ID and
doesn't show an easy total number of threads. A similarity between the two is
that the number of threads is updated as the process is run, that is, as the
arguments are dealt with, their individual threads are deleted as necessary.
Neither operating system allows the threads to exist if they are no longer needed.
This can be seen in the multiple screenshots with decreasing numbers of threads
even though Sum.java isn't done running and hasn't been run again. The only difference
here is that on Mac, the display is a live display whereas on Linux the
command has to be run over again to see the update in the number of threads.
