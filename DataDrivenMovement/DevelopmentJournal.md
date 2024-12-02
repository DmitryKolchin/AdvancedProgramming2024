# Data Driven Movement System



**Advanced Programming**

**Dmitrii Kolchin**  
**2220982**

---
## Research  

For this task, I aimed to develop two distinct implementations:  
1. A movement system written in plain C, visualised using raylib.  
2. Conway's Game of Life [(Conway’s Game of Life, 2024)](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), implemented with a data-driven design paradigm and showcased via raylib.  

These implementations not only allowed me to experiment with different programming concepts but also provided a platform to explore raylib and gain familiarity with C programming.  

---

## Implementation  

### Data-Driven Moving Circles  

To create a dynamic system for moving circles, the first step was to generate an array of entities, each representing a circle with position and velocity attributes.  

```c  
struct EntityData* CreateEntities(int EntitiesNum)
{
    struct EntityData* Entities;
    Entities = (struct EntityData*)malloc(EntitiesNum * sizeof(struct EntityData));
    for (int i = 0; i < EntitiesNum; ++i){
        struct EntityData Entity;
        Entity.positionX = rand() % SCREEN_WIDTH;
        Entity.positionY = rand() % SCREEN_HEIGHT;
        Entity.positionZ = 0;
        Entity.velocityX = 100 - rand() % 200;
        Entity.velocityY = 100 - rand() % 200;
        Entity.velocityZ = 0.1;
        
        Entities[i] = Entity;
    }
    
    return Entities;
};
```  

The `velocityZ` parameter is included for completeness but does not influence the current implementation, as all entities exist in a 2D space.  

Next, I implemented a function to update the entities' positions:  

```c  
void UpdatePositions(struct EntityData* Entities, int EntitiesNum, float DeltaTime)
{
    for (int i = 0; i < EntitiesNum; ++i){
        Entities[i].positionX += Entities[i].velocityX * DeltaTime;
        if (Entities[i].positionX < 0 || SCREEN_WIDTH < Entities[i].positionX){
            Entities[i].velocityX *= -1;
        }
        Entities[i].positionY += Entities[i].velocityY * DeltaTime;
        if (Entities[i].positionY < 0 || SCREEN_HEIGHT < Entities[i].positionY){
            Entities[i].velocityY *= -1;
        }
        Entities[i].positionZ += Entities[i].velocityZ * DeltaTime;
    }
}
```  

This update ensures the circles bounce off the screen edges, creating a dynamic effect. Drawing the circles is handled using raylib's `DrawCircle` function [(raylib - cheatsheet, s.d.)](https://www.raylib.com/cheatsheet/cheatsheet.html):  

```c  
void DrawEntities(struct EntityData* Entities, int EntitiesNum){
    for (int i = 0; i < EntitiesNum; ++i)
    {
        DrawCircle(Entities[i].positionX, Entities[i].positionY, 10, RED );
    }
} 
```  

Finally, I integrated these components into raylib's main function:  

```c  
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------
    struct EntityData* Entities = CreateEntities(ENTITIES_MAX);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdatePositions(Entities, ENTITIES_MAX, 0.016);        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawEntities(Entities, ENTITIES_MAX);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free(Entities);
    return 0;
} 
```  

The result is a visually dynamic system of bouncing circles, as demonstrated below:  

![](./Resources/Balls.gif)  

---

### Conway's Game of Life  

Conway's Game of Life, a cellular automaton, was implemented using a data-driven approach. The first step was to define the necessary data structures:  

```c  
enum CellState 
{
    ALIVE,
    DEAD
};

//struct for cells 
struct Cell
{
    int Row;
    int Column;
    enum CellState State;
}; 
```  

To initialise the grid, I created the following function:  

```c  
struct Cell* CreateCellsGrid(int Rows, int Columns)
{
    struct Cell* Cells;
    Cells = (struct Cell*)malloc(Rows * Columns * sizeof(struct Cell));
    for (int i = 0; i < Rows; ++i){
        for (int j = 0; j < Columns; ++j){
            struct Cell NewCell;
            NewCell.Row = i;
            NewCell.Column = j;
            NewCell.State = rand() % 2;
            Cells[i * Columns + j] = NewCell;
        }
    }
    
    return Cells;
} 
```  

The grid is updated based on two rules:  
1. Alive cells with fewer than two or more than three neighbours die.  
2. Dead cells with exactly three alive neighbours become alive.  

To implement this, I first wrote a helper function to calculate the number of alive neighbours:  

```c  
int GetCellAliveNeighborsNum(struct Cell* Cells, int CellIndex, int CellRowsNum, int CellsColumnNum)
{
    struct Cell TargetCell = Cells[CellIndex];
    int AliveNeighborsNum = 0;
    for (int i = TargetCell.Row - 1; i <= TargetCell.Row + 1; ++i)
    {
        if (i < 0 || CellRowsNum <= i)
        {
            continue;
        }
        for (int j = TargetCell.Column - 1; j <= TargetCell.Column + 1; ++j)
        {
            if (j < 0 || CellsColumnNum <= j)
            {
                continue;
            }
            if (i == TargetCell.Row && j == TargetCell.Column)
            {
                continue;
            }
            if (Cells[i * CellsColumnNum + j].State == ALIVE)
            {
                ++AliveNeighborsNum;
            }
        }
    }
    
    return AliveNeighborsNum;
}
```  

Next, I implemented the grid update logic:  

```c  
void UpdateCells(struct Cell* Cells, int CellsRowNum, int CellsColumnNum)
{
    struct Cell* UpdatedCells = (struct Cell*)malloc(CellsColumnNum * CellsRowNum * sizeof(struct Cell));
    
    for (int i = 0; i < CellsRowNum; ++i)
    {
        for (int j = 0; j < CellsColumnNum; ++j)
        {
            UpdatedCells[i * CellsColumnNum + j] = Cells[i * CellsColumnNum + j];
            int AliveNeighborsNum = GetCellAliveNeighborsNum(Cells, i * CellsColumnNum + j, CellsRowNum, CellsColumnNum);
            if (UpdatedCells[i * CellsColumnNum + j].State == ALIVE){
                if (AliveNeighborsNum < 2 || 3 < AliveNeighborsNum )
                {
                    UpdatedCells[i * CellsColumnNum + j].State = DEAD;
                }
            }
            
            else if (AliveNeighborsNum == 3){
                UpdatedCells[i * CellsColumnNum + j].State = ALIVE;
            }
        }
    }
    for (int i = 0; i < CellsRowNum; ++i)
    {
        for (int j = 0; j < CellsColumnNum; ++j)
        {
            Cells[i * CellsColumnNum + j].State = UpdatedCells[i * CellsColumnNum + j].State;
        }
    }
    
    free(UpdatedCells);
}
```  

Finally, I implemented a function to render the cells:  

```c  
void DrawCells(struct Cell* Cells, int CellsNum, int CellSizeX, int CellSizeY)
{
    for (int i = 0; i < CellsNum; ++i)
    {
        if (Cells[i].State == DEAD)
        {
            continue;
        }
        int X_Coordinate = Cells[i].Row * CellSizeX + CellSizeX / 2;
        int Y_Coordinate = Cells[i].Column * CellSizeY + CellSizeY / 2;
        DrawRectangle(X_Coordinate, Y_Coordinate, CellSizeX, CellSizeY, BLACK);
    }
}
```  

The result is a visually dynamic simulation at 30 frames per second:  

![](./Resources/GameOfLife.gif)  


All the source files could be found [here](https://github.com/DmitryKolchin/AdvancedProgramming2024/tree/main/DataDrivenMovement)

---

## Critical Reflection  

### What Went Well  

- Successfully implemented functionality in C, a language I explored for the first time.  
- Gained familiarity with raylib and its rendering capabilities.  
- Successfully applied data-driven design principles.  

### Areas for Improvement  

- Deepen my understanding of raylib's capabilities to implement more complex visualisations.  
- Develop greater proficiency in C programming for efficient and elegant code design.  

## Bibliography
- C Enum (Enumeration) (s.d.) At: https://www.w3schools.com/c/c_enums.php (Accessed  02/12/2024).
- Conway’s Game of Life (2024) In: Wikipedia. At: https://en.wikipedia.org/w/index.php?title=Conway%27s_Game_of_Life&oldid=1259378461 (Accessed  02/12/2024).
- Dynamic Array in C (2023) At: https://www.geeksforgeeks.org/dynamic-array-in-c/ (Accessed  30/11/2024).
- How to Release Memory in C? (2024) At: https://www.geeksforgeeks.org/how-to-release-memory-in-c/ (Accessed  02/12/2024).
- Lew, Ł. (2009) Answer to ‘How to generate a random int in C?’ At: https://stackoverflow.com/a/822368 (Accessed  30/11/2024).
- raylib (s.d.) At: https://www.raylib.com (Accessed  02/12/2024).
- raylib - cheatsheet (s.d.) At: https://www.raylib.com (Accessed  02/12/2024).

## Declared Assets

The following assets were created or modified with the use of GPT 4o:
```md 
- DevelopmentJournal.md
```