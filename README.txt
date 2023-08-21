Compile + Run instructions (on your terminal):
gcc -o main dfa.c nfa.c IntHashSet.c LinkedList.c main.c -Wall -Werror -std=c99 (add -lm if show "undefined reference to "pow"")
main

I combined every requirement into 1 single run so you can just call the main function. The order of run: DFA, NFA, NFA to DFA. 
I have also commented on the required functions for easier comprehension. 
My Valgrind report is clean for Part 1, Part 2 and the first 2 requirements of Part 3, but I couldn't check the last function because it took too long to execute on Valgrind.
*Note: For the last NFA to DFA, it may take longer (a few minutes) so please be patient.
