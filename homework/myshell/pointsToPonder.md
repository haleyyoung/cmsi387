Points To Ponder:
=================

1. The `cd` command got special mention because `exec()` and all of its relatives
look for an executable file to run under the name of the command passed in. `cd`
is different from most bash commands in that it doesn't have an executable file,
the pointer to which directory the shell is in is just updated to the first
argument after `cd`. Because of this, `exec()` can't handle the `cd` command because
it doesn't fit the qualities necessary for `exec()` to run it.

Source: http://stackoverflow.com/questions/9859903/using-the-exec-family-to-run-the-cd-command?rq=1

2. My shell cannot run scripts because it only knows how to handle specific commands.
That is, it only knows how to pass things to `execvp()`, `chdir()`, or call a specific
system call. Scripts are different in that they have the elements of a regular
language such as if statements and for loops and such. My shell can only handle a
list of commands and their corresponding arguments. I guess if a script consisted
of a list of commands and their corresponding arguments, then my shell could run
it, but aside from that, it couldn't.

3. Yes `Ctrl-D` exits my shell because the while loop keeps going until an `EOF`
character is found.
