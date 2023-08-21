#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dfa.h"
#include "nfa.h"
#include "IntHashSet.h"
#include "Set.h"
#include "LinkedList.h"

/**
 * The data structure used to represent a deterministic finite automaton.
 * @see FOCS Section 10.2
 * Note that YOU must specify this data structure, although you can hide
 * (encapsulate) its implementation behind the declared API functions and
 * only provide a partial declaration in the header file.
 */

typedef struct DFA *DFA;
struct DFA
{
    int numStates;
    int **transitionFunc;
    int *acceptingStates;
};

/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA new_DFA(int nstates)
{
    // printf("%d\n", sizeof(struct DFA));
    DFA dfa = (DFA)malloc(sizeof(struct DFA));
    dfa->numStates = nstates;
    dfa->transitionFunc = (int **)malloc(nstates * sizeof(int *));
    dfa->acceptingStates = (int *)malloc(nstates * sizeof(int));

    for (int i = 0; i < dfa->numStates; i++)
    {
        dfa->transitionFunc[i] = (int *)malloc(128 * sizeof(int));
        for (int j = 0; j < 128; j++)
        {
            dfa->transitionFunc[i][j] = -1;
        }
    }

    for (int i = 0; i < nstates; i++)
    {
        dfa->acceptingStates[i] = false;
    }
    return dfa;
};

/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa)
{
    if (dfa == NULL)
    {
        return;
    }
    for (int i = 0; i < dfa->numStates; i++)
    {
        free(dfa->transitionFunc[i]);
    }
    free(dfa->transitionFunc);
    free(dfa->acceptingStates);
    free(dfa);
};

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa)
{
    return dfa->numStates;
};

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym)
{
    unsigned char temp = sym;
    return dfa->transitionFunc[src][temp];
};

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst)
{
    unsigned char temp = sym;
    dfa->transitionFunc[src][temp] = dst;
};

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst)
{
    int len = (int)strlen(str);
    for (int i = 0; i < len; i++)
    {
        unsigned char temp = str[i];
        dfa->transitionFunc[src][temp] = dst;
    }
};

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst)
{
    for (int i = 0; i < 128; i++)
    {
        dfa->transitionFunc[src][i] = dst;
    }
};

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value)
{
    if (value == false)
    {
        return;
    }
    if (state < 0 || state > dfa->numStates)
    {
        return;
    }
    dfa->acceptingStates[state] = value;
};

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state)
{
    return dfa->acceptingStates[state];
};

/**
 * Set DFA for part 1A
 */
DFA DFA_for_contains_ullman()
{
    DFA dfa = new_DFA(8);
    DFA_set_accepting(dfa, 6, true);

    DFA_set_transition_all(dfa, 0, 7);
    DFA_set_transition(dfa, 0, 'u', 1);

    DFA_set_transition_all(dfa, 1, 7);
    DFA_set_transition(dfa, 1, 'l', 2);

    DFA_set_transition_all(dfa, 2, 7);
    DFA_set_transition(dfa, 2, 'l', 3);

    DFA_set_transition_all(dfa, 3, 7);
    DFA_set_transition(dfa, 3, 'm', 4);

    DFA_set_transition_all(dfa, 4, 7);
    DFA_set_transition(dfa, 4, 'a', 5);

    DFA_set_transition_all(dfa, 5, 7);
    DFA_set_transition(dfa, 5, 'n', 6);

    DFA_set_transition_all(dfa, 6, 7);

    return dfa;
};

/**
 * Set DFA for part 1B
 */
DFA DFA_for_startsWith_com()
{
    DFA dfa = new_DFA(5);
    DFA_set_accepting(dfa, 3, true);

    DFA_set_transition_all(dfa, 0, 4);
    DFA_set_transition(dfa, 0, 'c', 1);

    DFA_set_transition_all(dfa, 1, 4);
    DFA_set_transition(dfa, 1, 'o', 2);

    DFA_set_transition_all(dfa, 2, 4);
    DFA_set_transition(dfa, 2, 'm', 3);

    DFA_set_transition_all(dfa, 3, 3);
    DFA_set_transition_all(dfa, 4, 4);

    return dfa;
};

/**
 * Set DFA for part 1C
 */
DFA DFA_for_contains_threethrees()
{
    DFA dfa = new_DFA(5);
    DFA_set_accepting(dfa, 3, true);

    DFA_set_transition_all(dfa, 0, 0);
    DFA_set_transition(dfa, 0, '3', 1);

    DFA_set_transition_all(dfa, 1, 1);
    DFA_set_transition(dfa, 1, '3', 2);

    DFA_set_transition_all(dfa, 2, 2);
    DFA_set_transition(dfa, 2, '3', 3);

    DFA_set_transition_all(dfa, 3, 3);
    DFA_set_transition(dfa, 3, '3', 4);

    DFA_set_transition_all(dfa, 4, 4);

    return dfa;
};

/**
 * Set DFA for part 1D
 */
DFA DFA_for_contains_evenzeros_oddones()
{

    DFA dfa = new_DFA(5);
    DFA_set_accepting(dfa, 2, true);

    DFA_set_transition_all(dfa, 0, 4);
    DFA_set_transition(dfa, 0, '0', 1);
    DFA_set_transition(dfa, 0, '1', 2);

    DFA_set_transition_all(dfa, 1, 4);
    DFA_set_transition(dfa, 1, '0', 0);
    DFA_set_transition(dfa, 1, '1', 3);

    DFA_set_transition_all(dfa, 2, 4);
    DFA_set_transition(dfa, 2, '0', 3);
    DFA_set_transition(dfa, 2, '1', 0);

    DFA_set_transition_all(dfa, 3, 4);
    DFA_set_transition(dfa, 3, '0', 2);
    DFA_set_transition(dfa, 3, '1', 1);
    DFA_set_transition_all(dfa, 4, 4);

    return dfa;
};

int getIndex(LinkedList list, IntHashSet set)
{
    LinkedListIterator it = LinkedList_iterator(list);
    int curr = 0;
    while (LinkedListIterator_hasNext(it))
    {
        if (IntHashSet_equals(LinkedListIterator_next(it), set))
        {
            free(it);
            return curr;
        }
        curr++;
    }
    free(it);
    return -1;
}

DFA NFA_to_DFA(NFA nfa)
{
    DFA dfa = new_DFA((int)pow(2, NFA_get_size(nfa)));

    LinkedList cont1 = new_LinkedList();
    LinkedList cont2 = new_LinkedList();
    IntHashSet set = new_IntHashSet(NFA_get_size(nfa));
    IntHashSet_insert(set, 0);
    LinkedList_add_at_end(cont1, set);
    int state = 0;

    while (!LinkedList_isEmpty(cont1))
    {
        IntHashSet pop = LinkedList_pop(cont1);
        for (int i = 0; i < 128; i++)
        {
            IntHashSetIterator popIt = IntHashSet_iterator(pop);
            IntHashSet visited = new_IntHashSet(5);
            while (IntHashSetIterator_hasNext(popIt))
            {
                int src = IntHashSetIterator_next(popIt);
                IntHashSet_union(visited, NFA_get_transitions(nfa, src, i));
                if (NFA_get_accepting(nfa, src))
                    DFA_set_accepting(dfa, state - 1, true);
            }
            int dst = getIndex(cont2, visited);

            if (dst == -1)
            {
                LinkedList_add_at_end(cont1, visited);
                LinkedList_add_at_end(cont2, visited);
            }

            dst = getIndex(cont2, visited);
            DFA_set_transition(dfa, getIndex(cont2, pop), i, dst);
            free(popIt);
        }
        state++;
    }

    IntHashSet_free(set);
    LinkedList_free(cont1, true);
    LinkedList_free(cont2, true);

    return dfa;
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input)
{
    int finalState = 0;
    int len = (int)strlen(input);
    for (int i = 0; i < len; i++)
    {
        finalState = DFA_get_transition(dfa, finalState, input[i]);
    }
    return DFA_get_accepting(dfa, finalState);
};

/**
 * Print the given DFA to System.out.
 */
void DFA_print(DFA dfa)
{
    printf("DFA has %d states\n", dfa->numStates);
    printf("Accepting state(s): ");
    for (int i = 0; i < dfa->numStates; i++)
    {
        if (dfa->acceptingStates[i] == true)
        {
            printf("%d", i);
        }
    }
    printf("\n");

    printf("Transition table:\n");
    for (int i = 0; i < dfa->numStates; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            printf("State %d + input: %c -> State %d\n", i, j, dfa->transitionFunc[i][j]);
        }
    }
};

void DFA_repl(DFA dfa)
{
    printf("Enter an input (\"quit\" to quit): ");
    char str[255];
    fgets(str, 255, stdin);
    str[strcspn(str, "\n")] = 0;
    while (strcmp(str, "quit") != 0)
    {
        printf("Result for input \"%s\": ", str);
        bool check = DFA_execute(dfa, str);
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
