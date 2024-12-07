#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10

typedef enum { FALSE = 0, TRUE = 1 } Boolean;
typedef int TYPE_ITEM;

typedef struct sparesMat 
{
    int row, col;
    TYPE_ITEM info;
    struct sparesMat* nextRow;
    struct sparesMat* nextCol;
} sparesMatNode;

print_node(sparesMatNode* n)
{
    printf("(%d, %d) : %d\n", n->row, n->col, n->info);
    printf("col: (%d, %d) : %d\n", n->nextCol->row, n->nextCol->col, n->nextCol->info);
    printf("row: (%d, %d) : %d\n\n", n->nextRow->row, n->nextRow->col, n->nextRow->info);
    
}

void print_matrix(sparesMatNode* mat) {
    sparesMatNode* rowHeader = mat;
    sparesMatNode* currentRow;

    printf("(0, 0) ");
    sparesMatNode* colHeader = mat->nextCol;
    while (colHeader != mat) {
        printf("(%d, %d) ", colHeader->row, colHeader->col);
        colHeader = colHeader->nextCol;
    }
    printf("\n");

    rowHeader = rowHeader->nextRow;
    while (rowHeader != mat) {
        currentRow = rowHeader;
        printf("(%d, %d) ", currentRow->row, currentRow->col); 

        sparesMatNode* colNode = mat->nextCol; 
        while (colNode != mat) {
         
            sparesMatNode* temp = rowHeader->nextCol;
            Boolean found = FALSE;
            while (temp != rowHeader) {
                if (temp->col == colNode->col) {
                    printf("(%d, %d) ", temp->row, temp->col);
                    found = TRUE;
                    break;
                }
                temp = temp->nextCol;
            }
            if (!found) {
                printf("       "); 
            }
            colNode = colNode->nextCol;
        }
        printf("\n");
        rowHeader = rowHeader->nextRow;
    }
}


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
    if (p->nextCol == q->nextRow)
    {
        p->nextCol->info = x;
        return;
    }

    sparesMatNode* tmp = (sparesMatNode*)malloc(sizeof(sparesMatNode));
    if (!tmp) {
        printf("Memory allocation failed for head node.\n");
        return NULL;
    }

    tmp->info = x;
    tmp->row = p->row;
    tmp->col = q->col;
    tmp->nextCol = p->nextCol;
    tmp->nextRow = q->nextRow;

    p->nextCol = tmp;
    q->nextRow = tmp;

}


TYPE_ITEM deleteAfter(sparesMatNode* p, sparesMatNode* q)
{
    if (p->nextCol == NULL || q->nextRow == NULL || p->nextCol != q->nextRow) {
        printf("delete error: No valid node to delete.\n");
        return -1;
    }
    sparesMatNode* tmp = p->nextCol; 

    p->nextCol = tmp->nextCol;
    q->nextRow = tmp->nextRow;

    TYPE_ITEM val = tmp->info; 
    free(tmp);                 

    return val;
}


sparesMatNode* FindAbove(sparesMatNode* mat, int row, int col) {
    sparesMatNode* current = mat;

    
    for (int i = 0; i < col; i++)
    {
        current = current->nextCol;
    }


    sparesMatNode* tcol = current;
    
    for (int i = 1; i < row && current->nextRow != tcol; i++)
    {
        current = current->nextRow;
    }

    return current;
    
}


sparesMatNode* FindBefore(sparesMatNode* mat, int row, int col)
{
    sparesMatNode* current = mat;


    for (int i = 0; i < row; i++)
    {
        current = current->nextRow;
    }

    sparesMatNode* trol = current;

    for (int i = 1; i < col && current->nextCol != trol; i++)
    {
        current = current->nextCol;
    }

    return current;
}

void InsertToMatrix(sparesMatNode* mat, int row, int col, TYPE_ITEM x)
{
    sparesMatNode* prow = FindBefore(mat, row, col);
    sparesMatNode* pcol = FindAbove(mat, row, col);
    insertAfter(prow, pcol, x);
}

void printSparesMatrix(sparesMatNode* mat) {
    sparesMatNode* rowHeader = mat;
    sparesMatNode* currentRow;

    rowHeader = rowHeader->nextRow;
    while (rowHeader != mat) {
        currentRow = rowHeader;

        sparesMatNode* colNode = mat->nextCol;
        while (colNode != mat) {

            sparesMatNode* temp = rowHeader->nextCol;
            Boolean found = FALSE;
            while (temp != rowHeader) {
                if (temp->col == colNode->col) {
                    printf("%4d ", temp->info);
                    found = TRUE;
                    break;
                }
                temp = temp->nextCol;
            }
            if (!found) {
                printf("%4d ", 0);
            }
            colNode = colNode->nextCol;
        }
        printf("\n");
        rowHeader = rowHeader->nextRow;
    }
}

void freeMatrix(sparesMatNode* mat) {
    sparesMatNode* rowHeader = mat->nextRow;
    sparesMatNode* currentRow;
    sparesMatNode* temp;

    while (rowHeader != mat) {
        currentRow = rowHeader;
        sparesMatNode* colNode = rowHeader->nextCol;


        while (colNode != rowHeader) {
            temp = colNode;
            colNode = colNode->nextCol;
            free(temp);
        }

        temp = rowHeader;
        rowHeader = rowHeader->nextRow;
        free(temp);
    }

    rowHeader = mat->nextRow;
    sparesMatNode* colHeader = mat->nextCol;
    while (colHeader != mat) {
        temp = colHeader;
        colHeader = colHeader->nextCol;
        free(temp); 
    }

    free(mat);
}

void mulRow(sparesMatNode* mat, int row, int n)
{
    sparesMatNode* prow = mat;

    for (int i = 0; i < row; i++)
    {
        prow = prow->nextRow;
    }

    sparesMatNode* svaeRow = prow;
    prow = prow->nextCol;
    while (prow != svaeRow)
    {
        prow->info *= n;
        prow = prow->nextCol;
    }
}

sparesMatNode* retrieveSparesMatrix(sparesMatNode* mat, int row, int col)
{
    sparesMatNode* current = mat;


    for (int i = 0; i < row; i++)
    {
        current = current->nextRow;
    }


    for (int i = 0; i < col; i++)
    {
        current = current->nextCol;
    }

    return current;
}

int main() {
    sparesMatNode* matrix = init();
    if (matrix == NULL) {
        printf("Failed to initialize sparse matrix.\n");
        return 1;
    }

    
    int numEntries;
    int row = 0, col = 0, value = 0;

    printf("Enter number of non-zero entries: ");
    scanf_s("%d", &numEntries);

    for (int i = 0; i < numEntries; i++) {
        printf("Enter row, col, and value: ");
        scanf_s("%d %d %d", &row, &col, &value);

       
        InsertToMatrix(matrix, row, col, value);
    }


    printf("Sparse Matrix:\n");
    printSparesMatrix(matrix);
   
    print_node(retrieveSparesMatrix(matrix, 2, 2));

    mulRow(matrix, 2, 2);
    printSparesMatrix(matrix);
    freeMatrix(matrix);

    return 0;
}





