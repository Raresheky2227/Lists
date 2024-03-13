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

void removeElem(List *L, Elem *e) {
    // Check if the list is empty
    if (L->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Special case: removing the head element
    if (L->head == e) {
        L->head = e->next;
        // If the element to remove is also the tail, update the tail pointer
        if (L->tail == e) {
            L->tail = NULL;
        }
        L->size--;
        return;
    }

    // General case: find the element before e and update its next pointer
    Elem *prev = L->head;
    while (prev != NULL && prev->next != e) {
        prev = prev->next;
    }

    // If e is not found in the list
    if (prev == NULL) {
        printf("Element not found in the list.\n");
        return;
    }

    // Update the next pointer of the element before e
    prev->next = e->next;

    // If e is the tail, update the tail pointer
    if (L->tail == e) {
        L->tail = prev;
    }

    L->size--;
}

void stealFirstElem(List *src, List *dest) {
    // Ensure src list is not empty
    if (src->head == NULL) {
        printf("Source list is empty.\n");
        return;
    }

    // Get the first element from src
    Elem *firstElem = src->head;

    // Update src list's head to the next element
    src->head = src->head->next;

    // If src list becomes empty, update tail as well
    if (src->head == NULL) {
        src->tail = NULL;
    }

    // Update next pointer of firstElem to NULL (as it's being moved)
    firstElem->next = NULL;

    // If dest list is empty, update both head and tail
    if (dest->head == NULL) {
        dest->head = firstElem;
        dest->tail = firstElem;
    } else {
        // Otherwise, add firstElem at the end of dest list
        dest->tail->next = firstElem;
        dest->tail = firstElem;
    }

    // Update size of src and dest lists
    src->size--;
    dest->size++;
}

void appendList(List *src, List *dest) {
    // If src is empty, there's nothing to append
    if (src->size == 0) {
        return;
    }
    
    // If dest is empty, simply assign dest to src
    if (dest->size == 0) {
        dest->head = src->head;
        dest->tail = src->tail;
    } else {
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


List *mergeLists(List *L1, List *L2)
{
    List *L = createList();
    while (L1->head != NULL && L2->head != NULL)
    {
        if (L1->tail->v <= L2->head->v) {
            appendList(L1, L);
            appendList(L2, L);
            destroyList(L1);
            destroyList(L2);
            return L;
        }
        if (L2->tail->v <= L1->head->v) {
            appendList(L2, L);
            appendList(L1, L);
            destroyList(L1);
            destroyList(L2);
            return L;
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
    appendList(L1, L);
    appendList(L2, L);

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

List *deepCopy(List *original) {
    List *newList = createList();
    Elem *current = original->head;
    while (current != NULL) {
        Elem *newElem = malloc(sizeof(Elem));
        if (newElem == NULL) {
            // Handle memory allocation failure
            destroyList(newList);
            return NULL;
        }
        // Copy the contents of the original element to the new element
        newElem->v = current->v; // Assuming 'v' is a simple data type
        
        // Add the new element to the new list
        addElemLast(newList, newElem);
        
        // Move to the next element in the original list
        current = current->next;
    }
    return newList;
}


List *sortList(List *L)
{
    int done = 1;
    List *newList = createList();
    List *result = createList();
    if (L->size < 2)
    {
        return L;
    }
    Elem *curr = L->head;
    while (done)
    {
        done = 0;
        while (curr->next != NULL)
        {
            if (curr->next->v < curr->v)
            {
                Elem *temp = curr->next;
                curr->next = temp->next;
                L->size--;
                addElemLast(newList, temp);
                done = 1;
            }
            else
            {
                //bagi in newlist daca curr->v >= newlist->tail->v sau curr->v <= newlist->head->v si faci merge cu newlist si result
                curr = curr->next;
            }
        }
        sum += L->size;
        result = mergeLists(L, result);
        L = cutList(newList);
        curr = L->head;
        iterations++;
    }
    
    destroyList(newList);
    destroyList(L);
    return result;
}

int isListSorted(List *L) {
    Elem *curr = L->head;
    if (curr == NULL)
    {
        return 1;
    }
    while (curr->next!= NULL)
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
    if (argc != 3) {
        printf("Usage: %s 2^^<n> size list and <m> the range elements can be in(0 to m-1)\n", argv[0]);
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    N = 1<<n;
    List *L = createList();
    randomList(L, m, N);
    //printList(L);
    clock_t start = clock();
    L = sortList(L);
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Average merging was done with %f elements\n", (float)(sum) / iterations);
    printf("Time elapsed in ms: %f\n", elapsed);
    printf("Sorted?: %s\n", isListSorted(L) ? "Yes" : "No");
    printf("Number of loops when sorting: %d\n", iterations);
    printf("Size of list/iterations: %f\n", (float)((L->size * 1.0)/ iterations));
    destroyList(L);
    return 0;
}