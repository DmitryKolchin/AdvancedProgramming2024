

#include "raylib.h"
#include <time.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const int ENTITIES_MAX = 5;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

const int CELLS_ROWS_MAX = 80;
const int CELLS_COLUMNS_MAX = 45;

// Struct for entity data (position and velocity)
struct EntityData
{
    float positionX;
    float positionY;
    float positionZ;
    float velocityX;
    float velocityY;
    float velocityZ;
};


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

struct EntityData* CreateEntities(int EntitiesNum)
{
    struct EntityData* Entities;
    Entities = (struct EntityData*)malloc(EntitiesNum * sizeof(struct EntityData));
    for (int i = 0; i < EntitiesNum; ++i){
        struct EntityData Entity;
        Entity.positionX = rand() % SCREEN_WIDTH;
        Entity.positionY = rand() % SCREEN_HEIGHT;
        Entity.positionZ = 0;
        Entity.velocityX = rand() % 10 - 20;
        Entity.velocityY = rand() % 10 - 20;
        Entity.velocityZ = 0.1;
        
        Entities[i] = Entity;
        
    }
    
    return Entities;
};

void DrawEntities(struct EntityData* Entities, int EntitiesNum){
    for (int i = 0; i < EntitiesNum; ++i)
    {
        DrawCircle(Entities[i].positionX, Entities[i].positionY, 10, RED );
    }
}


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

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    struct EntityData* Entities = CreateEntities(ENTITIES_MAX);
    struct Cell* Cells = CreateCellsGrid(CELLS_ROWS_MAX, CELLS_COLUMNS_MAX);
    
    
    const int CellSizeX = SCREEN_WIDTH / CELLS_ROWS_MAX;
    const int CellSizeY = SCREEN_HEIGHT / CELLS_COLUMNS_MAX;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        UpdatePositions(Entities, ENTITIES_MAX, 0.016);
        UpdateCells(Cells, CELLS_ROWS_MAX, CELLS_COLUMNS_MAX);
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawEntities(Entities, ENTITIES_MAX);
        DrawCells(Cells, CELLS_ROWS_MAX * CELLS_COLUMNS_MAX, CellSizeX, CellSizeY);
        

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            
            
           

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