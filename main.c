#include <stdio.h>
#include "dfa.h"
#include "nfa.h"

int main()
{
    printf("Testing DFA that recognizes exactly \"ullman\"...\n");
    DFA a = DFA_for_contains_ullman();
    DFA_repl(a);
    DFA_free(a);

    printf("Testing DFA that recognizes strings starting with \"com\"...\n");
    DFA b = DFA_for_startsWith_com();
    DFA_repl(b);
    DFA_free(b);

    printf("Testing DFA that recognizes strings with exactly three \"3\"...\n");
    DFA c = DFA_for_contains_threethrees();
    DFA_repl(c);
    DFA_free(c);

    printf("Testing DFA that recognizes binary strings with even 0's and odd 1's...\n");
    DFA d = DFA_for_contains_evenzeros_oddones();
    DFA_repl(d);
    DFA_free(d);

    printf("Testing NFA that recognizes strings ending with \"gs\"...\n");
    NFA e = NFA_for_endsWith_gs();
    NFA_repl(e);
    NFA_free(e);

    printf("Testing NFA that recognizes strings containing \"mas\"...\n");
    NFA f = NFA_for_contains_mas();
    NFA_repl(f);
    NFA_free(f);

    printf("Testing NFA that recognizes strings that are not anagrams of \"codebreaker\"...\n");
    NFA g = NFA_for_not_anagrams_codebreaker();
    NFA_repl(g);
    NFA_free(g);

    printf("Testing DFA on NFA that recognizes strings ending with \"gs\"...\n");
    DFA h = NFA_to_DFA(NFA_for_endsWith_gs());
    DFA_repl(h);
    DFA_free(h);

    printf("Testing DFA on NFA that recognizes strings containing \"mas\"...\n");
    DFA i = NFA_to_DFA(NFA_for_contains_mas());
    DFA_repl(i);
    DFA_free(i);

    printf("Testing DFA on NFA that recognizes strings that are not anagrams of \"codebreaker\"...\n");
    DFA j = NFA_to_DFA(NFA_for_not_anagrams_codebreaker());
    DFA_repl(j);
    DFA_free(j);
}