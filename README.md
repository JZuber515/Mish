# Mish

An interactive shell program.
Takes input, tokenizes it, then forks and executes a process based on the input.

Design:
For my design, I did more of a top-down design. I started with getting the
loop to work and retrieving input. After that, I tokenized the input, just
looking for spaces. Then I got all of the internal commands working. I
would test everything along the way to make sure that all of this worked.
After that, I attempted to get the execvp calls working with the switch
statement. Obviously the internal command verbose could not be
completely finished because some of this information needed to be
printed out here. But I mainly focused on the switch of turning verbose
on and off in a boolean and then printing that information was easy.
The main thing that was hard was grouping quoted text together. I saved
this for the end. As long as the quote is closed, then mine works fine.
After that it was just working on cleaning up the memory.

Problems:
I tested every process and sometimes memory would leak, but it would not
crash the program. Also, I believe that if quoted text is put in the
middle of a command, then my mish will crash. I could not figure out why though.
Separating the input was one of the most challenging parts of this project.
