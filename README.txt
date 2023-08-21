Compile + Run instructions (on your terminal):
gcc -o main dfa.c nfa.c IntHashSet.c LinkedList.c main.c -Wall -Werror -std=c99 (add -lm if show "undefined reference to "pow"")
main

I combined every requirement into 1 single run so you can just call the main function. The order of run: DFA, NFA, NFA to DFA. 
I have also commented on the required functions for easier comprehension. 

*Note: For the last NFA to DFA, it may take longer (a few minutes) so please be patient.
