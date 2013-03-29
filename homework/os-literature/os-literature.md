Short-term scheduling in multiprogramming systems
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