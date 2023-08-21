#include "Set.h"
#include "nfa.h"
#include "IntHashSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * The data structure used to represent a nondeterministic finite automaton.
 * @see FOCS Section 10.3
 * @see Comments for NFA in NFA.h
 */
typedef struct NFA *NFA;
struct NFA
{
    int numStates;
    IntHashSet **transitionFunc;
    int *acceptingStates;
};

/**
 * Allocate and return a new NFA containing the given number of states.
 */
NFA new_NFA(int nstates)
{
    NFA nfa = (NFA)malloc(sizeof(struct NFA));
    nfa->numStates = nstates;
    nfa->transitionFunc = (IntHashSet **)malloc(nstates * sizeof(IntHashSet *));
    nfa->acceptingStates = (int *)malloc(nstates * sizeof(int));
    for (int i = 0; i < nfa->numStates; i++)
    {
        nfa->transitionFunc[i] = (IntHashSet *)malloc(128 * sizeof(IntHashSet));
        for (int j = 0; j < 128; j++)
        {
            nfa->transitionFunc[i][j] = new_IntHashSet(nstates);
        }
    }

    for (int i = 0; i < nstates; i++)
    {
        nfa->acceptingStates[i] = false;
    }
    return nfa;
}
/**
 * Free the given NFA.
 */
void NFA_free(NFA nfa)
{
    if (nfa == NULL)
    {
        return;
    }
    for (int i = 0; i < nfa->numStates; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            IntHashSet_free(nfa->transitionFunc[i][j]);
        }
        free(nfa->transitionFunc[i]);
    }
    free(nfa->transitionFunc);
    free(nfa->acceptingStates);
    free(nfa);
}

/**
 * Return the number of states in the given NFA.
 */
int NFA_get_size(NFA nfa)
{
    return nfa->numStates;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
Set NFA_get_transitions(NFA nfa, int state, char sym)
{
    unsigned char temp = sym;
    return nfa->transitionFunc[state][temp];
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
void NFA_add_transition(NFA nfa, int src, char sym, int dst)
{
    unsigned char temp = sym;
    IntHashSet_insert(nfa->transitionFunc[src][temp], dst);
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst)
{
    int len = (int)strlen(str);
    for (int i = 0; i < len; i++)
    {
        unsigned char temp = str[i];
        IntHashSet_insert(nfa->transitionFunc[src][temp], dst);
    }
}

/**
 * Add a transition for the given NFA for each input symbol.
 */
void NFA_add_transition_all(NFA nfa, int src, int dst)
{
    for (int i = 0; i < 128; i++)
    {
        IntHashSet_insert(nfa->transitionFunc[src][i], dst);
    }
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
void NFA_set_accepting(NFA nfa, int state, bool value)
{
    if (value == false)
    {
        return;
    }
    if (state < 0 || state > nfa->numStates)
    {
        return;
    }
    nfa->acceptingStates[state] = value;
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
bool NFA_get_accepting(NFA nfa, int state)
{
    return nfa->acceptingStates[state];
}

/**
 * NFA for part 2A
 */
NFA NFA_for_endsWith_gs()
{
    NFA nfa = new_NFA(3);
    NFA_set_accepting(nfa, 2, true);

    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'g', 1);
    NFA_add_transition(nfa, 1, 's', 2);

    return nfa;
}

/**
 * NFA for part 2B
 */
NFA NFA_for_contains_mas()
{
    NFA nfa = new_NFA(4);

    NFA_set_accepting(nfa, 3, true);

    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'm', 1);
    NFA_add_transition(nfa, 1, 'a', 2);
    NFA_add_transition(nfa, 2, 's', 3);
    NFA_add_transition_all(nfa, 3, 3);

    return nfa;
}

/**
 * NFA for part 2C
 */
NFA NFA_for_not_anagrams_codebreaker()
{
    NFA nfa = new_NFA(18);

    NFA_set_accepting(nfa, 2, true);
    NFA_set_accepting(nfa, 4, true);
    NFA_set_accepting(nfa, 6, true);
    NFA_set_accepting(nfa, 8, true);
    NFA_set_accepting(nfa, 10, true);
    NFA_set_accepting(nfa, 13, true);
    NFA_set_accepting(nfa, 17, true);

    for (int i = 0; i < 18; i++)
    {
        NFA_add_transition_all(nfa, i, i);
    }

    NFA_add_transition(nfa, 0, 'a', 1);
    NFA_add_transition(nfa, 1, 'a', 2);
    NFA_add_transition(nfa, 0, 'b', 3);
    NFA_add_transition(nfa, 3, 'b', 4);
    NFA_add_transition(nfa, 0, 'c', 5);
    NFA_add_transition(nfa, 5, 'c', 6);
    NFA_add_transition(nfa, 0, 'd', 7);
    NFA_add_transition(nfa, 7, 'd', 8);
    NFA_add_transition(nfa, 0, 'k', 9);
    NFA_add_transition(nfa, 9, 'k', 10);
    NFA_add_transition(nfa, 0, 'r', 11);
    NFA_add_transition(nfa, 11, 'r', 12);
    NFA_add_transition(nfa, 12, 'r', 13);
    NFA_add_transition(nfa, 0, 'e', 14);
    NFA_add_transition(nfa, 14, 'e', 15);
    NFA_add_transition(nfa, 15, 'e', 16);
    NFA_add_transition(nfa, 16, 'e', 17);

    return nfa;
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool NFA_execute(NFA nfa, char *input)
{
    IntHashSet finalState = new_IntHashSet(NFA_get_size(nfa));
    IntHashSet_insert(finalState, 0);

    int len = (int)strlen(input);
    for (int i = 0; i < len; i++)
    {
        IntHashSet temp = new_IntHashSet(NFA_get_size(nfa));
        IntHashSetIterator iterator = IntHashSet_iterator(finalState);
        while (IntHashSetIterator_hasNext(iterator))
        {
            int state = IntHashSetIterator_next(iterator);
            IntHashSet_union(temp, NFA_get_transitions(nfa, state, input[i]));
        }
        finalState = temp;
    }

    IntHashSetIterator iterator = IntHashSet_iterator(finalState);
    while (IntHashSetIterator_hasNext(iterator))
    {
        int state = IntHashSetIterator_next(iterator);
        if (NFA_get_accepting(nfa, state))
        {
            return true;
        }
    }

    return false;
}

/**
 * Print the given NFA to System.out.
 */
void NFA_print(NFA nfa)
{
    printf("NFA has %d states\n", nfa->numStates);
    printf("Accepting state(s): ");
    for (int i = 0; i < nfa->numStates; i++)
    {
        if (nfa->acceptingStates[i] == true)
        {
            printf("%d", i);
        }
    }
    printf("\n");

    printf("Transition table:\n");
    for (int i = 0; i < nfa->numStates; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            printf("State %d + input: %c -> State %s\n", i, j, IntHashSet_toString(nfa->transitionFunc[i][j]));
        }
    }
}

void NFA_repl(NFA nfa)
{
    printf("Enter an input (\"quit\" to quit): ");
    char str[255];
    fgets(str, 255, stdin);
    str[strcspn(str, "\n")] = 0;
    while (strcmp(str, "quit") != 0)
    {
        printf("Result for input \"%s\": ", str);
        bool check = NFA_execute(nfa, str);
        if (check)
        {
            printf("True \n");
        }
        else
        {
            printf("False \n");
        }
        printf("Enter an input (\"quit\" to quit): ");
        fgets(str, 255, stdin);
        str[strcspn(str, "\n")] = 0;
    }
}
