#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10

typedef enum { FALSE = 0, TRUE = 1 } Boolean;
typedef int TYPE_ITEM;

typedef struct sparesMat {
    int row, col;
    TYPE_ITEM info;
    struct sparesMat* nextRow;
    struct sparesMat* nextCol;
} sparesMatNode;

sparesMatNode* init() 
{
    sparesMatNode* head = (sparesMatNode*)malloc(sizeof(sparesMatNode));
    if (!head) {
        printf("Memory allocation failed for head node.\n");
        return NULL;
    }

    head->row = 0;
    head->col = 0;
    head->info = 0;
    head->nextRow = head;
    head->nextCol = head;

    sparesMatNode* last = head;

    // Create row headers
    for (int i = 1; i <= ROWS; i++) {
        sparesMatNode* newRow = (sparesMatNode*)malloc(sizeof(sparesMatNode));
        if (!newRow) return NULL; 
        *newRow = (sparesMatNode){ .row = i, .col = 0, .info = 0, .nextRow = head, .nextCol = newRow };
        last->nextRow = newRow;
        last = newRow;
    }

    last = head;

    // Create column headers
    for (int i = 1; i <= COLS; i++) {
        sparesMatNode* newCol = (sparesMatNode*)malloc(sizeof(sparesMatNode));
        if (!newCol) return NULL; 
        *newCol = (sparesMatNode){ .row = 0, .col = i, .info = 0, .nextCol = head, .nextRow = newCol };
        last->nextCol = newCol;
        last = newCol;
    }

    return head;
}


Boolean isEmpty(sparesMatNode* mat)
{
    sparesMatNode* curr_row = mat->nextRow;
    sparesMatNode* curr_col = mat->nextCol;
    while (curr_row != mat)
    {
        if (curr_row->nextCol != curr_row)
            return FALSE;
        curr_row = curr_row->nextRow;
    }

    while (curr_col != mat)
    {
        if (curr_col->nextRow != curr_col)
            return FALSE;
        curr_col = curr_col->nextCol;
    }

    return TRUE;

}

void insertAfter(sparesMatNode* p, sparesMatNode* q, TYPE_ITEM x)
{
    sparesMatNode* tmp = (sparesMatNode*)malloc(sizeof(sparesMatNode));

    tmp->row = p->row + 1;
    tmp->col = p->col + 1;
    tmp->info = x;
    tmp->nextCol = q->nextCol;
    tmp->nextRow = p->nextRow;

    p->nextRow = tmp;
    q->nextCol = tmp;
}

int main() {
    sparesMatNode* matrixShell = init();
    printf("%d", isEmpty(matrixShell));
    return 0;
}


