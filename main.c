#include <stdio.h>

#define SIZE 5
#define TILES_NEEDED_TO_WIN 3
int game_grid[SIZE][SIZE];
//int tilesNeededToWin = 3;
int const players[2] = {'X', 'O'};
int current_player = 0;

void setup(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            game_grid[i][j] = '-';
        }
    }
}

int get_info(char info[]){
    int answer;
    int pocetZnaku;
    do{
        printf("Enter %s: ", info);
        scanf("%d", &answer);
        pocetZnaku = 0;
        while(getchar() != '\n'){
            pocetZnaku++;
        }
        if(pocetZnaku > 0){
            printf("You didn't enter a number!\n");
        }else if(answer < 0 || answer >= SIZE){
            printf("You entered a number out of range!\n");
        }else if(game_grid[answer][answer] != '-'){
            printf("This field is already taken!\n");
        }
    }while(pocetZnaku > 0 || answer < 0 || answer >= SIZE || game_grid[answer][answer] != '-');
    return answer;
}

void line(){
    printf("-------------------------\n");
}

void printGrid(){
    line();
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%c ", game_grid[i][j]);
        }
        printf("\n");
    }
    line();
    printf("Current player: %c\n", players[current_player]);
}

int checkWinner(int row, int column){
    int numInLine = 1;
    int checked = 1;
    //printf("grid: %c\n", game_grid[row][column]);
    /*int testGrid[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            testGrid[i][j] = 0;
        }
    } */
    // kontrola radku doleva a doprava
    while(numInLine < TILES_NEEDED_TO_WIN && checked < TILES_NEEDED_TO_WIN){
        if(game_grid[row][column] == game_grid[row][column - checked]){
            numInLine++;
            //printf("added\n");
            //testGrid[row][column - checked] = 1;
        } else {
            numInLine = 0;
            break;
        }
        checked++;
    }
    checked = 1;
    while(numInLine < TILES_NEEDED_TO_WIN && checked < TILES_NEEDED_TO_WIN){
        if(game_grid[row][column] == game_grid[row][column + checked]){
            numInLine++;
            //printf("added here\n");
            //testGrid[row][column + checked] = 1;
        } else {
            numInLine = 0;
            break;
        }
    }
    checked = 0;
    //printf("numInLine: %d\n", numInLine);
    /*for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%d ", testGrid[i][j]);
        }
        printf("\n");
    } */
    // kontrola jestli je nekdo vitez
    if(numInLine >= TILES_NEEDED_TO_WIN){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    setup();
    int running = 1;
    int row, column;
    printf("Current player: %c\n", players[current_player]);
    while(running){
        // ziskani souradnic
        row = get_info("row");
        column = get_info("column");
        game_grid[row][column] = players[current_player];
        // vypis gridu
        printGrid();
        // kontrola jestli je nekdo vitez
        if (checkWinner(row, column)==1){
            printf("Player %c wins!\n", players[current_player]);
            running = 0;
        }
        if (current_player == 0){
            current_player = 1;
        } else {
            current_player = 0;
        }
    }
}