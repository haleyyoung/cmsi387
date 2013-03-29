Short-term Scheduling in Multiprogramming Systems
=================================================

ACM SIGOPS Operating Systems Review Homepage archive
Volume 6 Issue 1/2, June 1972
Pages 101 - 105

Per Brinch Hansen
Carnegie-Mellon University, Pittsburgh, Pennsylvania


*Connection*

This source is connected to the paper by Dijkstra because it directly references
that paper.

"At the short-term level of scheduling, a process is either running on a
processor or waiting in a queue. A process can wait for an idle processor or
for a timing signal from another process. In the former case, the process is
said to be ready, in the latter, it is blocked. The synchronizing primitives
for the latter case are the by now familiar P and V operations on semaphores
introduced by E. W. Dijkstra 2" (Hansen, 1972, p. 102).

"It can be done with the aid of a single binary semaphore, say 'free'. The value
of 'free' euqls the number of processes allowed to enter their ciritcal setion
now, or:

'free = 1' means: none of the processes is engaged in its critical section

'free = 0' means: one of the proecesses is engaged in its critical section"
(Dijkstra, 1965, p. 30).

*Difference*

"Preemption by means of the stop primitive makes
it useful to distinguish between semaphores used to
synchronize critical sections and input/output rela-
tionships. When a process enters a critical section,
its section depth must be increased by one to guaran-
tee that it will be able to complete that section,
and, when it leaves it again, the section depth must
be decreased by one" (Hansen, 1972, 104).

This is new in relation to the other papers because they mostly talk about how
to determine which process gets to come next, which Hansen does, but they also
describe the addition of some control signals which determine when a process can
enter the processor. These control signals are meant to help determine the exact
context of the process that is occuring and therefore help with the scheduling
of other processes.

*Quality*

The quality of this work is good because the author is associated with Carnegie-Mellon,
a prestigeous university in the computer science field. This article was also
found in the ACM which is a widely read Article Database. The thing I liked about
this article was that the author not only used snippets of code to get their
point accross, but they also drew diagrams of things that might be considered
confusing.

A simple solution to Lamport's concurrent programming problem with linear wait
==============================================================================

ICS '88 Proceedings of the 2nd international conference on Supercomputing
Pages 621 - 626

B. K. Szymanski Rensselear Polytechnic Institute, Troy, NY

*Connection*

This source is connected to the paper by Lamport beause it references the three
conditions that Lamport believes must be satisfied.

>1. Mutual exclusion: There will be at most one process executing the critical
>section at a time.
>
>2. Freedom from deadlock: The critical section will not become inaccessible to
>all processes. This means that if a number of processes attempts to execute their
>critical sections, then after finite amount of time some process will be allowed
>to do so.
>
>3. Fairness (freedom form starvation): No process will be denied entry to its
>critical section forever. Thus, a process requesting an entry to its critical
>section will enter it after waiting for a finite amount of time. The stronger
>fairness property requires that no process can enter its critical section twice
>while another process is waiting (linear wait).
>
>4. Robustness: The solution should be immune to the following two types of failures:
>
>(1) Process failure: a prooess may repeatedly fail and restart. However, process
>failing in the critical section, prologue or epilogue is assumed to leave the
>respective section of code and reset all its variables to their initial values.
>
>(2) Read errors during writes (flickering bits): when a process writes a new
>value to a shared variable, a sequence of reads may return any sequence of the
>old and new values.
(Szymanski, 1988, p. 622).

>1. At any time, at most one computer may be in its critical section.
>
>2. Each computer must eventually be able to enter its critical section (unless
>it halts)
>
>3. Any computer may halt in its noncritical section
(Lamport, 1974, p. 454).

*Difference*

"This algorithm uses just five distinct values of shared
memory per process. These values may be stored either in a
single variable or in three one-bit boolean variables per
process" (Szymanski, 1988, 626).

This is new in relation to Lamport's paper because she doesn't deal with the issue
of a process dying in the middle of its critical section. Also, when it comes to
the issue of reading and writing from/to a variable at the same time, Szymanski
deals with these issues. Szymanski proposes a 3 bit system in which more information
can be stored about the state of a certain process than just whether or not it's
in its critical section.

*Quality*

The quality of this work is good because the author is published in the ACM which
is a widely read Article Database. He also takes the time to set up the background
explaining what Lamport was dealing with as well as defines some possibly misunderstood
terms before diving into his new element of the algroithm.