#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Elem
{
    int v;
    struct Elem *next;
} Elem;

typedef struct List
{
    int size;
    Elem *head;
    Elem *tail;
} List;

int iterations = 0;
int N = 0;
int sum = 0;
int m = 0;

int power(int base, int exponent)
{
    if (base == 0 && exponent == 0)
    {
        perror("Undefined");
        return 0;
    }
    if (base == 0)
        return 0;
    if (exponent == 0)
        return 1;
    if (base == 1)
        return 1;

    if (exponent % 2 == 0)
    {
        return power(base, exponent / 2) * power(base, exponent / 2);
    }
    else
    {
        return power(base, exponent / 2) * power(base, exponent / 2) * base;
    }
}

List *createList()
{
    List *L = malloc(sizeof(List));
    L->size = 0;
    L->head = NULL;
    L->tail = NULL;
    return L;
}

void printList(List *L)
{
    Elem *curr = L->head;
    if (curr == NULL)
    {
        printf("List is empty.\n\n");
        return;
    }
    while (curr != NULL)
    {
        printf("%d, ", curr->v);
        curr = curr->next;
    }
    printf("\n\n");
}

void addNumber(List *L, int v)
{
    Elem *newElem = malloc(sizeof(Elem));
    newElem->v = v;
    newElem->next = NULL;
    if (L->size == 0)
    {
        L->head = newElem;
        L->tail = newElem;
    }
    else
    {
        L->tail->next = newElem;
        L->tail = newElem;
    }
    L->size++;
}

void addElemLast(List *L, Elem *e)
{
    e->next = NULL;
    if (L->size == 0)
    {
        L->head = e;
        L->tail = e;
    }
    else
    {
        L->tail->next = e;
        L->tail = e;
    }
    L->size++;
}

void addElemFirst(List *L, Elem *e)
{
    if (L->size == 0)
    {
        L->head = e;
        L->tail = e;
    }
    else
    {
        Elem *temp = L->head;
        L->head = e;
        e->next = temp;
    }
    L->size++;
}

void destroyList(List *L)
{
    Elem *curr = L->head;
    while (curr != NULL)
    {
        Elem *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(L);
}

void randomList(List *L, int m, int n)
{
    while (L->size < n)
    {
        addNumber(L, rand() % m);
    }
}

void removeElem(List *L, Elem *prev, Elem *e)
{
    // Check if the list is empty
    if (L->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // Special case: removing the head element
    if (prev == NULL)
    {
        L->head = e->next;
        // If the element to remove is also the tail, update the tail pointer
        if (L->tail == e)
        {
            L->tail = NULL;
        }
        L->size--;
        return;
    }

    // Update the next pointer of the element before e
    prev->next = e->next;

    // If e is the tail, update the tail pointer
    if (L->tail == e)
    {
        L->tail = prev;
    }

    L->size--;
}

void stealFirstElem(List *src, List *dest)
{
    // Ensure src list is not empty
    if (src->head == NULL)
    {
        printf("Source list is empty.\n");
        return;
    }

    // Get the first element from src
    Elem *firstElem = src->head;

    // Update src list's head to the next element
    src->head = src->head->next;

    // If src list becomes empty, update tail as well
    if (src->head == NULL)
    {
        src->tail = NULL;
    }

    // Update next pointer of firstElem to NULL (as it's being moved)
    firstElem->next = NULL;

    // If dest list is empty, update both head and tail
    if (dest->head == NULL)
    {
        dest->head = firstElem;
        dest->tail = firstElem;
    }
    else
    {
        // Otherwise, add firstElem at the end of dest list
        dest->tail->next = firstElem;
        dest->tail = firstElem;
    }

    // Update size of src and dest lists
    src->size--;
    dest->size++;
}

void appendList(List *src, List *dest)
{
    if (src == NULL)
    {
        return;
    }
    if (dest == NULL)
    {
        dest = src;
        return;
    }
    // If src is empty, there's nothing to append
    if (src->size == 0)
    {
        return;
    }

    // If dest is empty, simply assign dest to src

    if (dest->size == 0)
    {
        dest->head = src->head;
        dest->tail = src->tail;
    }
    else
    {
        // If dest is not empty, append src to dest
        dest->tail->next = src->head;
        dest->tail = src->tail;
    }

    // Update the size of dest
    dest->size += src->size;

    // Clear src to avoid memory leaks
    src->head = NULL;
    src->tail = NULL;
    src->size = 0;
}

int elems = 0;
List *mergeLists(List *L1, List *L2)
{
    List *L = createList();
    while (L1->head != NULL && L2->head != NULL)
    {
        if (L1->head->v >= L2->tail->v)
        {
            // elems += L2->size;
            appendList(L1, L2);
            break;
        }
        if (L1->tail->v <= L2->head->v)
        {
            // elems += L1->size;
            appendList(L2, L1);
            break;
        }
        if (L1->head->v < L2->head->v)
        {
            stealFirstElem(L1, L);
        }
        else
        {
            stealFirstElem(L2, L);
        }
    }
    if (L1->head != NULL)
    {
        elems += L1->size;
        appendList(L1, L);
    }
    if (L2->head != NULL)
    {
        elems += L2->size;
        appendList(L2, L);
    }

    destroyList(L1);
    destroyList(L2);
    return L;
}

List *cutList(List *L)
{
    List *L1 = createList();
    L1->size = L->size;
    L->size = 0;
    L1->head = L->head;
    L->head = NULL;
    L1->tail = L->tail;
    L->tail = NULL;
    return L1;
}

List *betterStalinUpward(List *L)
{
    List *S = createList();
    Elem *curr = L->head;
    Elem *prev = NULL;
    Elem *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        if (S->size == 0)
        {
            curr = next;
            stealFirstElem(L, S);
        }
        else if (curr->v >= S->tail->v)
        {
            addElemLast(S, curr);
            if (prev != NULL)
            {
                prev->next = next;
            }
            else
            {
                L->head = next;
            }
            if (curr == L->tail)
            {
                L->tail = prev;
            }
            L->size--;
            curr = next;
        }
        // else if (curr->v <= S->head->v) {
        //     addElemFirst(S, curr);
        //     if (prev != NULL) {
        //         prev->next = next;
        //     }
        //     else {
        //         L->head = next;
        //     }
        //         if (curr == L->tail)
        //         {
        //             L->tail = prev;
        //         }
        //         L->size--;
        //     curr = next;
        // }
        else
        {
            prev = curr;
            curr = next;
        }
    }
    return S;
}

List *betterStalinDownward(List *L)
{
    List *S = createList();
    Elem *curr = L->head;
    Elem *prev = NULL;
    Elem *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        if (S->size == 0)
        {
            curr = next;
            stealFirstElem(L, S);
        }
        // else if (curr->v >= S->tail->v)
        // {
        //     addElemLast(S, curr);
        //     if (prev != NULL)
        //     {
        //         prev->next = next;
        //     }
        //     else
        //     {
        //         L->head = next;
        //     }
        //     if (curr == L->tail)
        //     {
        //         L->tail = prev;
        //     }
        //     L->size--;
        //     curr = next;
        // }
        else if (curr->v <= S->head->v)
        {
            addElemFirst(S, curr);
            if (prev != NULL)
            {
                prev->next = next;
            }
            else
            {
                L->head = next;
            }
            if (curr == L->tail)
            {
                L->tail = prev;
            }
            L->size--;
            curr = next;
        }
        else
        {
            prev = curr;
            curr = next;
        }
    }
    return S;
}

void betterStalinGen(List *L, List *V1, List *V2)
{
    if (L == NULL)
    {
        return;
    }
    if (L->size == 0) {
        return;
    }
    if (L->size == 1) {
        stealFirstElem(L, V1);
        return;
    }
    Elem *curr = L->head;
    Elem *prev = NULL;
    Elem *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        if (V1->size == 0 && V2->size == 0)
        {
            if (next->v <= curr->v) {
                next = next->next;
                curr = next;
                stealFirstElem(L, V1);
                stealFirstElem(L, V2);
            }
            else {
                next = next->next;
                curr = next;
                stealFirstElem(L, V2);
                stealFirstElem(L, V1);
            }
        }
        else if (curr->v >= V2->tail->v)
        {
            addElemLast(V2, curr);
            if (prev != NULL)
            {
                prev->next = next;
            }
            else
            {
                L->head = next;
            }
            if (curr == L->tail)
            {
                L->tail = prev;
            }
            L->size--;
            curr = next;
        }
        else if (curr->v <= V1->head->v)
        {
            addElemFirst(V1, curr);
            if (prev != NULL)
            {
                prev->next = next;
            }
            else
            {
                L->head = next;
            }
            if (curr == L->tail)
            {
                L->tail = prev;
            }
            L->size--;
            curr = next;
        }
        else
        {
            prev = curr;
            curr = next;
        }
    }
    return;
}

List *sortList(List *L)
{
    List *big;
    List *resultbig = createList();
    List *small;
    List *resultsmall = createList();
    if (L->size < 2)
    {
        return L;
    }
    while (L->size > 0)
    {
        // big = betterStalinUpward(L);
        big = createList();
        small = createList();
        betterStalinGen(L, small, big);
        resultsmall = mergeLists(resultsmall, small);
        resultbig = mergeLists(resultbig, big);
        iterations++;
    }

    destroyList(L);
    //printList(resultbig);
    //printList(resultsmall);
    return mergeLists(resultsmall, resultbig);
}

int isListSorted(List *L)
{
    Elem *curr = L->head;
    if (curr == NULL)
    {
        return 1;
    }
    while (curr->next != NULL)
    {
        if (curr->next->v < curr->v)
        {
            return 0;
        }
        curr = curr->next;
    }
    return 1;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc != 3)
    {
        printf("Usage: %s 2^^<n> size list and <m> the range elements can be in(0 to m-1)\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    int n = atoi(argv[2]);
    N = 1 << n;
    List *L = createList();
    randomList(L, m, N);
    // printList(L);
    clock_t start = clock();
    L = sortList(L);
    clock_t stop = clock();
    // printList(L);
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f\n", elapsed);
    printf("Sorted?: %s\n", isListSorted(L) ? "Yes" : "No");
    printf("Number of loops when sorting: %d\n", iterations);
    printf("Size of list/iterations: %f\n", (float)((L->size * 1.0) / iterations));
    printf("Number of elems appended: %d\n", elems);
    destroyList(L);
    return 0;
}