#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// compile with gcc -std=c17 -pedantic -Werror ece2071_asg2.c -o ece2071_asg2 -lm
// run with command ece2071_asg2

struct cell
{
    int cost;
    bool bottomCell;
    bool leftCell;
    bool visitCell;
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
void print_node();

struct maze *mazePtr = NULL;
struct cell ***headPtr = NULL; // pointer pointing to first node in queue
// struct cell *headPtr = NULL; // pointer pointing to first node in queue
int size = 0;

int targetX = 0;
int targetY = 0;

    int mazeHeight = 3;
    int mazeWidth = 3;

int main()
{
    clock_t t;
    t = clock();
    struct cell *tailPtr = NULL;          // pointer pointing to last node in queue
    struct cell *curPtr = NULL;           // pointer used to walk through queue and manipulate the queue
    int max_cost = -1;                    // max cost of nodes in the queue
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
    // headPtr = (struct cell *)malloc(sizeof(struct cell));
    // headPtr ->cost = 5;
    headPtr = (struct cell ***)malloc(mazeHeight * mazeWidth * sizeof(struct cell));
    for (int x = 0; x < mazeWidth; x++)
    {
        headPtr[x] = (struct cell **)malloc(mazeHeight * sizeof(struct cell));
        for (int y = 0; y < mazeHeight; y++)
        {
            headPtr[x][y] = (struct cell *)malloc(sizeof(struct cell));
            headPtr[x][y]->cost = 0;
            headPtr[x][y]->leftCell = 0;
            headPtr[x][y]->bottomCell = 0;
            headPtr[x][y]->visitCell = 0;

        }
    }
    headPtr[2][2]->cost = 27;

    

    print_node();
    fclose(fptr);
    return 0;
}

void print_node()
{
    for (int x = 0; x < mazeWidth; x++)
    {
        for (int y = 0; y < mazeHeight; y++)
        {
            printf("%2d ", headPtr[x][y]->cost); // print type and cost
        }
        printf("\n"); // print type and cost
    }
}
