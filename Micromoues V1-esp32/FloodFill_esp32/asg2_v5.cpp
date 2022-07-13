#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// compile with gcc -std=c17 -pedantic -Werror ece2071_asg2.c -o ece2071_asg2 -lm
// run with command ece2071_asg2

struct cell
{
    char type;
    int cost;
    int x_coord;
    int y_coord;
    struct cell *nextPtr;
    struct cell *sourcePtr;
};

struct maze
{
    char type;
    int cost;
    int x_coord;
    int y_coord;
    struct cell *nextXPtr;
    struct cell *nextYPtr;
};

void enqueue(struct cell **startPtr, struct cell **prevTargetPtr, char value, int cellCost, int x, int y);
void dequeue(struct cell **startPtr);
void print_node(struct cell **startPtr);
int validCell(int x, int y);
void insertAdjacentCell(struct cell **currPtr, int currX, int currY, int cost);
char checkCellType(int x, int y);
int checkVisited(struct cell **headerPtr, int x, int y);

struct maze *mazePtr = NULL;
struct cell *headPtr = NULL; // pointer pointing to first node in queue
int size = 0;

int targetX = 0;
int targetY = 0;

int main()
{
    clock_t t;
    t = clock();
    struct cell *tailPtr = NULL; // pointer pointing to last node in queue
    struct cell *curPtr = NULL;  // pointer used to walk through queue and manipulate the queue
    int max_cost = -1;           // max cost of nodes in the queue
    FILE *fptr = fopen("maze1.txt", "r"); // open the text file containing maze
    // FILE *fptr = fopen("maze.txt", "r"); // open the text file containing maze
    // FILE *fptr = fopen("maze_83x83.txt", "r"); // open the text file containing maze
    // FILE *fptr = fopen("mazeHard.txt", "r"); // open the text file containing maze
    char c = '\0';
    int count = 0;
    if (fptr == NULL)
    {
        printf("File not found\n");
        return -1;
    }
    //----------------------------------------------------------------------------------------
    // Find the size of the maze (assuming a square maze)
    //----------------------------------------------------------------------------------------
    else
    {
        c = fgetc(fptr);
        while (c != '\n')
        {
            if (isspace(c))
            {
                c = fgetc(fptr);
                continue;
            }
            size++;
            c = fgetc(fptr);
        }
        printf("Assuming a square maze, the size of the maze is: %d x %d\n", size, size);
    }
    // fclose(fptr);
    //----------------------------------------------------------------------------------------
    // Add the starting point cell (labelled 'S') as the first node in the queue
    //----------------------------------------------------------------------------------------
    rewind(fptr); // rewind fptr to beginning of the text file
    while (!feof(fptr))
    {
        c = fgetc(fptr);
        if (isspace(c) || c == '\n')
        {
            c = fgetc(fptr);
            continue;
        }
        else if (c == 'S')
        {
            count++;
            headPtr = (struct cell *)malloc(sizeof(struct cell));
            headPtr->type = 'S';
            headPtr->y_coord = (count / size) + 1;
            headPtr->x_coord = (count % size);
            headPtr->cost = 0;
            headPtr->nextPtr = NULL;
            headPtr->sourcePtr = NULL;
            max_cost = 0;
            break;
        }
        else
        {
            c = fgetc(fptr);
            count++;
        }
    }
    fclose(fptr);

    // putting values into array and print map
    
    for (int i = 1; i <= size; i++)
    {
        for (int k = 1; k <= size; k++)
        {
            char value = checkCellType(k, i);
            printf("%c ", value);
            // maze[i - 1][k - 1] = value;
        }
        printf("\n");
    }
    /*
    printf("Details of node in the queue representing 'S' cell in the maze\n");
    printf("---------------------------------------------------------------------------\n");
    printf("Type: %c\n", headPtr->type);
    printf("Row-coordinate: %d\n", headPtr->y_coord);
    printf("Col-coordinate: %d\n", headPtr->x_coord);
    printf("Cost: %d\n", headPtr->cost);
    printf("---------------------------------------------------------------------------\n");
    */
    curPtr = headPtr;

    int currX = 0;
    int currY = 0;
    int cost = 0;

    struct cell *currPtr = headPtr;

    int length = 0;

    currX = currPtr->x_coord;
    currY = currPtr->y_coord;
    cost = currPtr->cost + 1;
    insertAdjacentCell(&currPtr, currX, currY, cost);

    // int counterCheck = 0;
    while (currPtr->type != 'T')
    {
        currPtr = currPtr->nextPtr;

        // print_node(&headPtr);
        currX = currPtr->x_coord;
        currY = currPtr->y_coord;
        cost = currPtr->cost + 1;
        insertAdjacentCell(&currPtr, currX, currY, cost);
        // counterCheck++;
        // if (counterCheck % 1000 == 0)
            // printf(".");
        if ((currPtr->nextPtr) == NULL)
        {
            if (checkCellType(currPtr->x_coord, currPtr->y_coord) != 'T')
            {
                // print_node(&headPtr);
                printf("no path found");
                exit(0);
            }
        }
    }
    // printf("\ntarget location x:%d y:%d", currPtr->x_coord, currPtr->y_coord);
    printf("Target Reached\n");

    print_node(&headPtr);

    int counter = 0;
    while (currPtr->sourcePtr != NULL)
    {
        // printf("\n %4.1d: (%d,%d)", counter, currPtr->x_coord, currPtr->y_coord);
        printf("(%2d,%2d) ", currPtr->y_coord, currPtr->x_coord);
        currPtr = currPtr->sourcePtr;
        counter++;
        if(counter%15==0)
            printf("\n");
    }

    printf("(%2d,%2d) ", currPtr->y_coord, currPtr->x_coord);
    // printf("\n %4.1d: (%d,%d)", counter, currPtr->x_coord, currPtr->y_coord);

    // obtain time taken
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("\n excetute time: %f \n", time_taken);
    return 0;
}

char checkCellType(int targetX, int targetY)
{
    // printf("%s", fileName);
    targetX -= 1;
    targetY -= 1;

    FILE *fptr = fopen("maze1.txt", "r"); // open the text file containing maze
    // FILE *fptr = fopen("maze.txt", "r"); // open the text file containing maze
    // FILE *fptr = fopen("maze_83x83.txt", "r"); // open the text file containing maze
    // FILE *fptr = fopen("mazeHard.txt", "r"); // open the text file containing maze
    int columns = 0;
    int rows = 0;
    char string_1[1024] = "\0";
    char targetValue;
    while (rows != targetY)
    {
        fgets(string_1, 1024, fptr);
        rows++;
    }
    fgets(string_1, 1024, fptr); // read next line of text file into string_1

    char *tokenPtr;
    tokenPtr = strtok(string_1, " ");
    columns = 0;

    while (tokenPtr != NULL)
    {
        if (columns == targetX && rows == targetY)
        {
            targetValue = *tokenPtr;
            break;
        }
        columns++;
        tokenPtr = strtok(NULL, " ");
    }
    rows++;
    fclose(fptr);

    // printf("rows %d\n", rows);
    return targetValue;
}

void print_node(struct cell **startPtr)
{
    struct cell *printPtr = *startPtr;
    printf("\n");

    // *printPtr = *startPtr;
    while (printPtr != NULL)
    { // print hte data in each node

        // print contents of printNode
        printf("type:%c cost:%d", printPtr->type, printPtr->cost);                                  // print type and cost
        printf(" x:%d y:%d ", printPtr->x_coord, printPtr->y_coord);                                // print coordinate
        printf(" source:%p current:%p next:%p ", printPtr->sourcePtr, printPtr, printPtr->nextPtr); // print momory location
        printPtr = printPtr->nextPtr;
        printf("\n"); // step to next node
    }
    printf("\nNULL");
}
void enqueue(struct cell **startPtr, struct cell **prevTargetPtr, char cellType, int cellCost, int x, int y)
{
    // maze[y - 1][x - 1] = cellCost + 48;

    struct cell *currPtr = *startPtr;
    struct cell *newPtr = NULL;
    newPtr = (struct cell *)malloc(sizeof(struct cell));
    newPtr->type = cellType;
    newPtr->cost = cellCost;
    newPtr->x_coord = x;
    newPtr->y_coord = y;
    newPtr->nextPtr = NULL;
    newPtr->sourcePtr = *prevTargetPtr;

    // add newPtr to the end of the queue
    while (currPtr->nextPtr != NULL)
    {
        currPtr = currPtr->nextPtr;
    }
    currPtr->nextPtr = newPtr;
}

void dequeue(struct cell **startPtr)
{
    struct cell *currPtr = *startPtr;
    *startPtr = (*startPtr)->nextPtr;
    free(currPtr);
}

int validCell(int x, int y)
{
    // printf("\n%d %d", x, y);
    if ((x > size || x < 1) || (y > size || y < 1))
    {
        return 0; // return value as invalid
    }
    else
    {
        char type = checkCellType(x, y);
        if (type == 'T')
        {
            // printf("x:%d y:%d ", x, y);
            targetX = x;
            targetY = y;
            return 1; // return value as valid
        }
        else if (checkVisited(&headPtr, x, y))
        {
            return 0; // return value as invalid
        }
        else if (type == '.')
        {
            return 1; // return value as valid
        }
        else
        {
            return 0;
        }
    }
}

void insertAdjacentCell(struct cell **currPtr, int currX, int currY, int cost)
{
    int nextX = 0;
    int nextY = 0;

    int topCell = validCell(currX, currY - 1);
    int bottomCell = validCell(currX, currY + 1);
    int leftCell = validCell(currX - 1, currY);
    int rightCell = validCell(currX + 1, currY);

    if (topCell) //check top cell 
    {   
        nextX = currX;
        nextY = currY - 1;
        // printf("%d %d\n", nextX, nextY);
        enqueue(&headPtr, currPtr, checkCellType(nextX, nextY), cost, nextX, nextY);
    }
    if (bottomCell) //check bottom cell 
    {
        nextX = currX;
        nextY = currY + 1;
        // printf("%d %d\n", nextX, nextY);
        enqueue(&headPtr, currPtr, checkCellType(nextX, nextY), cost, nextX, nextY);
    }
    if (leftCell) //check left cell 
    {
        nextX = currX - 1;
        nextY = currY;
        // printf("%d %d\n", nextX, nextY);
        enqueue(&headPtr, currPtr, checkCellType(nextX, nextY), cost, nextX, nextY);
    }
    if (rightCell) //check right cell 
    {
        nextX = currX + 1;
        nextY = currY;
        // printf("%d %d\n", nextX, nextY);
        enqueue(&headPtr, currPtr, checkCellType(nextX, nextY), cost, nextX, nextY);
    }
}

int checkVisited(struct cell **headerPtr, int x, int y) // check if that cell has been visited previously
{
    struct cell *currPtr = *headerPtr;

    int currX = 0;
    int currY = 0;
    if ((x > size || x < 1) || (y > size || y < 1))
    {
        return 0; // return value as invalid
    }
    else if ((*headerPtr)->nextPtr == NULL)
    {
        // printf("\nx:%d y:%d, end",(*headerPtr)->x_coord,(*headerPtr)->y_coord);
        return 0; // return value as invalid
    }
    else
    {
        do
        {
            currX = currPtr->x_coord;
            int currY = currPtr->y_coord;
            currPtr = currPtr->nextPtr;
            if (currX == x && currY == y)
            {
                // printf("visit!!! x:%d y:%d",x,y);
                return 1;
            }
        } while (currPtr->nextPtr != NULL);
        return 0;
    }
}