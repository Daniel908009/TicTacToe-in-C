#include <stdio.h>

#define SIZE 5
#define TILES_NEEDED_TO_WIN 3
int game_grid[SIZE][SIZE];
int const players[2] = {'X', 'O'};
int current_player = 0;

// funkce pro vyplneni gridu pomlckami
void setup(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            game_grid[i][j] = '-';
        }
    }
}

// kontrola jestli je nekdo vitez
int isWinner(int numInLine){
    printf("numInLine: %d\n", numInLine);
    if(numInLine >= TILES_NEEDED_TO_WIN){
        return 1;
    }else{
        return 0;
    }
}

// funkce pro ziskavani informaci od uzivatele
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
        }
    }while(pocetZnaku > 0 || answer < 0 || answer >= SIZE);
    return answer;
}

// funkce pro vypis cary
void line(){
    printf("//////////////////////////////////////////////\n");
}

// funkce pro vypis vnitrni vodorovne cary gridu
void gridLine(){
    printf("|");
    for(int i = 0; i < SIZE; i++){
        printf("----");
    }
    printf("|\n");
}

// funkce pro vypis gridu
void printGrid(){
    line();
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("| ");
            printf("%c ", game_grid[i][j]);
        }
        printf(" |\n");
        if (i < SIZE - 1){ // tohle zabranuje vytvareni cary pod poslednim radkem
            gridLine();
        }
    }
    line();
}

// funkce pro kontrolu jestli je nekdo vitez
int checkWinner(int row, int column){
    int numInLine = 1;
    int checked = 1;
    // kontrola radku doleva a doprava
    while(numInLine < TILES_NEEDED_TO_WIN && checked < TILES_NEEDED_TO_WIN && column - checked >= 0){
        if(game_grid[row][column] == game_grid[row][column - checked]){
            numInLine++;
        } else {
            break;
        }
        checked++;
    }
    checked = 1;
    while(numInLine < TILES_NEEDED_TO_WIN && checked < TILES_NEEDED_TO_WIN && column + checked < SIZE){
        if(game_grid[row][column] == game_grid[row][column + checked]){
            numInLine++;
        } else {
            break;
        }
    }
    checked = 1;
    if (isWinner(numInLine) == 1){
        return 1;
    }else{
        numInLine = 1;
    }
    // kontrola sloupce nahoru a dolu
    while(numInLine < TILES_NEEDED_TO_WIN && checked < TILES_NEEDED_TO_WIN && row - checked >= 0){
        if(game_grid[row][column] == game_grid[row - checked][column]){
            numInLine++;
            printf("added from first if\n");
        } else {
            break;
        }
    }
    checked = 1;
    while(numInLine < TILES_NEEDED_TO_WIN && checked < TILES_NEEDED_TO_WIN && row + checked < SIZE){
        if(game_grid[row][column] == game_grid[row + checked][column]){
            numInLine++;
            printf("added from second if\n");
        } else {
            break;
        }
    }
    if (isWinner(numInLine) == 1){
        return 1;
    }else{
        numInLine = 1;
    }
}

int main(){
    setup();
    int running = 1;
    int row, column = -1;
    printf("Current player: %c\n", players[current_player]);
    while(running){
        // ziskani souradnic
        do{
            row = get_info("row");
            column = get_info("column");
            if (game_grid[row][column] != '-' && row >= 0 && column >= 0){
                printf("This field is already taken!\n");
            }
            printf("row: %d, column: %d\n", row, column);
        }while (game_grid[row][column] != '-');
        
        game_grid[row][column] = players[current_player];
        // vypis gridu
        printGrid();
        // kontrola jestli je nekdo vitez
        if (checkWinner(row, column)==1){
            printf("Player %c wins!\n", players[current_player]);
            running = 0;
            break;
        }
        if (current_player == 0){
            current_player = 1;
        } else {
            current_player = 0;
        }
        row = -1;
        column = -1;
        printf("Current player: %c\n", players[current_player]);
    }
}