#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define _MSC_VER 1400
#define w(a,b) AddWall(game,a,b)
#define a(a,b) AddFood(game,a,b)
#define FOOD_SCORE 10
#define MAX_GHOSTS 30

typedef enum gameState{losing, onGoing, winning} GameState;
typedef enum direction{up, down, left, right, idle} Direction;


typedef struct {
    int pc,pr;
    int lazyfood;
    Direction dir;
}Ghost;

typedef struct game {
    char** grid;
    int columns;
    int rows;
    int foodCount;
    int score;
    int pr,pc;
    GameState state;
    Ghost g[MAX_GHOSTS];
    int cg;
} Game;


/* Creates a new game, with given rows and columns.
 * The left-upper corner is at row 0 and column 0.
 * Boundary is not included in either rows or columns.
 * You should dynamically allocate space for a Game pointer,
 * dynamically allocate a 2-dimensional char grid,
 * and initialize any other value in your Game structure.
 * Return that pointer to the game you created.
 */
Game* NewGame(int rows, int columns){
    char** grid=(char**)malloc(rows*sizeof(char*));
    memset(grid,0x00,sizeof(grid));
    for(int i=0;i<rows;i++)
        grid[i]=(char*)malloc(columns*sizeof(char));
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
            grid[i][j]=' ';
    Game* game=(Game*)malloc(sizeof(Game));
    game->columns=columns;
    game->rows=rows;
    game->grid=grid;
    game->foodCount=0;
    game->score=0;
    game->state=onGoing;
    game->pr=-1;
    game->cg=0;
    return game;
}

/* Ends your game by freeing any memory
 * you dynamically created.
 * After that, free the game pointer,
 * as it is also dynamically created.
 */
void EndGame(Game* game){
    for(int i=0;i<game->rows;i++){
        free(game->grid[i]);
    }
    free(game->grid);
    free(game);
    return;
}

/* Adds a wall to the game, at row = r, column = c.
 * Walls should be added only to an empty place.
 * After you successfully add a wall, 
 * you should modify the `grid' to represent
 * the wall by '#'. Then, return true.
 * Return false on failures.
 */
bool AddWall(Game* game, int r, int c){
    if(r>=game->rows || c>=game->columns || r<0 || c<0)return false;
    if(game->grid[r][c]!=' ')return false;
    game->grid[r][c]='#';
    return true;
}

/* Adds a food to the game, at row = r, column = c.
 * Foods should be added only to an empty place.
 * After you successfully add a food, 
 * you should modify the `grid' to represent
 * the food by '.', also update the `foodCount'
 * correctly. Then, return true.
 * Return false on failures.
 *
 * FOR PART 2:
 * It's not allowed to add a food on a ghost.
 * It's allowed, however, conversely.
 */
bool AddFood(Game* game, int r, int c){
    if(r>=game->rows || c>=game->columns || r<0 || c<0)return false;
    if(game->grid[r][c]!=' ')return false;
    game->grid[r][c]='.';
    game->foodCount++;
    return 1;
}


/* Adds a Pacman to the game! At row = r, column = c.
 * If there is already a Pacman, return false.
 * Pacman should be added only to an empty place.
 * After you successfully add a Pacman,
 * you should modify the `grid' to represent
 * the Pacman by 'C'. Then, return true.
 * Return false on failures.
 */
bool AddPacman(Game* game, int r, int c){
    if(r>=game->rows || c>=game->columns || r<0 || c<0)return false;
    if(game->pr!=-1)return false;
    if(game->grid[r][c]!=' ')return false;
    game->grid[r][c]='C';
    game->pr=r;
    game->pc=c;
    return true;
}

/* Moves Pacman in the given direction.
 * The direction will always be valid.
 * Pacman should stay still if this move
 * will let him hit a wall or boundaries.
 * No matter what move is performed, the
 * game score should decrease by 1.
 *
 * FOR PART 2:
 * Pacman is allowed to move onto a grid
 * with a ghost. In that case, Pacman loses,
 * and will not be able to eat the food
 * under that ghost, if any. Score should
 * still decrease by 1.
 */
void MovePacman(Game* game, Direction direction){
    if(game->pr==-1)return;
    int mr,mc;
    switch (direction) {
        case left:
            mr=0;
            mc=-1;
            break;
        case right:
            mr=0;
            mc=1;
            break;
        case up:
            mr=-1;
            mc=0;
            break;
        case down:
            mr=1;
            mc=0;
            break;
        case idle:
            game->score--;
            return;
    }
    if(game->pr+mr>=game->rows || game->pc+mc>=game->columns || game->pc+mc<0 || game->pr+mr<0){
        game->score--;
        return;
    }
    if(game->grid[game->pr+mr][game->pc+mc]=='#'){
        game->score--;
        return;
    }
    else if(game->grid[game->pr+mr][game->pc+mc]=='@'){
        game->grid[game->pr][game->pc]=' ';
        game->pr+=mr;
        game->pc+=mc;
        game->state=losing;
        game->score--;
        return;
    }
    else if(game->grid[game->pr+mr][game->pc+mc]=='.'){
        game->score+=FOOD_SCORE;
        game->foodCount--;
        if(game->foodCount==0){
            game->score--;
            game->grid[game->pr][game->pc]=' ';
            game->pr+=mr;
            game->pc+=mc;
            game->grid[game->pr][game->pc]='C';
            game->state=winning;
            return;
        }
    }
    game->grid[game->pr][game->pc]=' ';
    game->pr+=mr;
    game->pc+=mc;
    game->grid[game->pr][game->pc]='C';
    game->score--;
    return;
}

/* Adds a ghost to the game,
 * at row = r, column = c, with given initial direction.
 * you should modify the `grid' to represent the ghost by '@'.
 * Ghosts can be added to an empty place or on a food.
 * For the latter case, the ghost will cover that food on display,
 * represented also by an '@'. 
 * That food must still exist, and that grid should 
 * display '.' when the ghost leaves.
 */
bool AddGhost(Game* game, int r, int c, Direction direction){
    if(r>=game->rows || c>=game->columns || r<0 || c<0)return false;
    if(game->cg>=MAX_GHOSTS)return 0;
    if(game->grid[r][c]!='.' && game->grid[r][c]!=' ')return 0;
    Ghost gh={c,r,(game->grid[r][c]=='.'),direction};
    game->grid[r][c]='@';
    game->g[game->cg++]=gh;
    return true;
}

/* Moves all ghosts in their own directions.
 * Ghosts should be moved in the order they were added.
 * If a ghost will bump into a wall, another ghost, or a boundary,
 * Its direction will reverse, and it will try to move
 * in the new direction immediately this turn.
 * If it bumps into another wall/ghost/boundary,
 * it won't move for this turn.
 */
void MoveGhosts(Game* game){
    for(int i=0;i<game->cg;i++){
        int mr=0,mc=0;
        switch (game->g[i].dir) {
            case left:
                mr=0;
                mc=-1;
                break;
            case right:
                mr=0;
                mc=1;
                break;
            case up:
                mr=-1;
                mc=0;
                break;
            case down:
                mr=1;
                mc=0;
                break;
            case idle:
                continue;
        }
        if(game->g[i].pr+mr<game->rows && game->g[i].pr+mr>=0 && game->g[i].pc+mc<game->columns && game->g[i].pc+mc>=0 && game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='C'){
            if(game->g[i].lazyfood)game->grid[game->g[i].pr][game->g[i].pc]='.';
            else game->grid[game->g[i].pr][game->g[i].pc]=' ';
            game->g[i].lazyfood=0;
            game->grid[game->g[i].pr+mr][game->g[i].pc+mc]='@';
            game->g[i].pr+=mr;
            game->g[i].pc+=mc;
            game->state=losing;
            return;
        }
        if(game->g[i].pr+mr>=game->rows || game->g[i].pr+mr<0 || game->g[i].pc+mc>=game->columns || game->g[i].pc+mc<0 || game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='#' || game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='@'){
            switch (game->g[i].dir) {
                case left:
                    game->g[i].dir=right;
                    mr=0;
                    mc=1;
                    break;
                case right:
                    game->g[i].dir=left;
                    mr=0;
                    mc=-1;
                    break;
                case up:
                    game->g[i].dir=down;
                    mr=1;
                    mc=0;
                    break;
                case down:
                    game->g[i].dir=up;
                    mr=-1;
                    mc=0;
                    break;
            }
        }
        if(game->g[i].pr+mr>=game->rows || game->g[i].pr+mr<0 || game->g[i].pc+mc>=game->columns || game->g[i].pc+mc<0 || game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='#' || game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='@')continue;
       /* if(game->g[i].pr+mr>=game->rows || game->g[i].pr+mr<0 || game->g[i].pc+mc>=game->columns || game->g[i].pc+mc<0 || game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='#' || game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='@'){
            switch (game->g[i].dir) {
                case left:
                    game->g[i].dir=right;
                    break;
                case right:
                    game->g[i].dir=left;
                    break;
                case up:
                    game->g[i].dir=down;
                    break;
                case down:
                    game->g[i].dir=up;
                    break;
            }
            continue;
        }*/
        if(game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='C'){
            if(game->g[i].lazyfood)game->grid[game->g[i].pr][game->g[i].pc]='.';
            else game->grid[game->g[i].pr][game->g[i].pc]=' ';
            game->g[i].lazyfood=0;
            game->grid[game->g[i].pr+mr][game->g[i].pc+mc]='@';
            game->g[i].pr+=mr;
            game->g[i].pc+=mc;
            game->state=losing;
            return;
        }
        if(game->g[i].lazyfood)game->grid[game->g[i].pr][game->g[i].pc]='.';
        else game->grid[game->g[i].pr][game->g[i].pc]=' ';
        if(game->grid[game->g[i].pr+mr][game->g[i].pc+mc]=='.')game->g[i].lazyfood=1;
        else game->g[i].lazyfood=0;
        game->grid[game->g[i].pr+mr][game->g[i].pc+mc]='@';
        game->g[i].pr+=mr;
        game->g[i].pc+=mc;

    }
    return;
}


///////////////////////////////////////////////////////////////////////////////
/////////////////// Please submit all code above to OJ ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Declarations of provided functions
void PrintGame(Game* game);
void PlayGame(Game* game);

int main(){
    Game* game = NewGame(9, 18);
//    freopen("map.txt","r",stdin);
    // Add walls, foods, and pacman here.

    for(int i=0;i<9;i++)
        for(int j=0;j<18;j++){
            char c=getchar();
            while(c!='#' && c!='.' && c!=' ' && c!='C')c=getchar();
            if(c=='C')c=' ';
            game->grid[i][j]=c;
        }
//    fclose(stdin);
    AddPacman(game,8,8);
    AddGhost(game,2,3,right);
    AddGhost(game,4,5,down);
    PlayGame(game);

    EndGame(game);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */
#ifdef _MSC_VER

#include <windows.h>

#endif // _MSC_VER

void PrintGame(Game* game){
    if(!game || !game->grid) return;

// If visual C++, clear console.
#ifdef _MSC_VER 
    system("cls");
#else
// Clears terminal screen
#ifndef _ONLINE_JUDGE
    fflush(stdout);
    system("clear");
#endif

#endif
    
    // The game grid
    printf(" ");
    for(int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for(int i = 0; i < game->rows; i++){
        printf("|");
        for(int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for(int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");

    // Messages on different states
    switch(game->state){
    case losing:
        printf("Pacman died! Your score: %d\n", game->score);
        break;
    case onGoing:
        printf("Score: %d\n", game->score);
        printf("There are %d foods remaining!\n", game->foodCount);
        printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
        break;
    case winning:
        printf("Victory! Your score: %d\n", game->score);
        break;
    default:
        printf("ERROR: invalid game state!\n");
    }
}

void PlayGame(Game* game){
    if(!game) return;
    
    // Prints the initial grid
    PrintGame(game);

    // Main loop of game. Terminates when the game ends.
    while(true){
        // We only care about one charater, but should eat the whole line of input.
        char input[127];
        scanf("%s", input);
        Direction direction;
        switch(input[0]){
        case 'w':
        case 'W':
            direction = up; break;
        case 'a':
        case 'A':
            direction = left; break;
        case 's':
        case 'S':
            direction = down; break;
        case 'd':
        case 'D':
            direction = right; break;
        case 'i':
        case 'I':
            direction = idle; break;
        default:
            PrintGame(game);
            continue;
        }

        // Pacman moves first
        MovePacman(game, direction);

        // Loses if Pacman bumps into a ghost
        if(game->state != onGoing){
            break;
        }
        
        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);

        // Loses if a ghost kills Pacman
        if(game->state != onGoing){
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press any key to exit.\n");
    getchar();
    getchar();
}