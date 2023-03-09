#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Grid.h"
using namespace std;

// public member functions
Grid::Grid() { // build 1 x 1 grid with mover in only square, facing east
    button = 1; // set button ON
    cout << "Constructing a 1x1 Stack..." << endl;
    for(i = 0; i < 3; i++){ // build blocks
        for(j = 0; j < 3; j++)
            grid[i][j] = '#';
    }
    row = 3, column = 3; // length of grid include blocks.

    // one random exit  
    srand((unsigned int)time(NULL)); // seed of time
    random = rand() % (2 *row + 2 * column - 8); // the quanlity of place that can be chosen as exit : 2 *row + 2 * column - 7
    if(random < column - 2)
        grid[0][random + 1] = '.';
    if(random >= column - 2 && random < 2 * column - 4) 
        grid[row - 1][random - column + 2 + 1] = '.';
    if(random >= 2 * column - 4 && random < 2 * column + row - 6)
        grid[random - 2 * column + 4 + 1][0] = '.';
    if(random >= 2 * column + row - 6)
        grid[random - 2 * column - row + 6 + 1][column - 1] = '.';

    grid[1][1] = '>';
    mover_r = 1, mover_c = 1, mover_d = 3;
}

Grid::Grid(int r, int c){ // build grid with r rows, c cols, blocks around edge with random exit and random mover position and direction
    
    button = 1; // set button ON

    // if r, c are not in range 3 ~ 40, set as the closest integer in the range
    if(r < 3) r = 3;
    if(r > 40) r = 40;
    if(c < 3) c = 3;
    if(c > 40) c = 40;
    row = r + 2, column = c + 2; // length of grid include blocks.
    cout << "Constructing a " << r << "x" << c << " Stack..." << endl;
    
    // build blocks
    for(i = 0; i < row; i ++){ 
        grid[i][0] = '#';
        grid[i][column - 1] = '#';
    }
    for(i = 0; i < column; i ++){
        grid[0][i] = '#';
        grid[row - 1][i] = '#';
    }

    for(i = 1; i < row - 1; i++){ // build grid (all '.');
        for(j = 1; j < column - 1 ; j++)
            grid[i][j] = '.';
    }

    // one random exit  
    srand((unsigned int)time(NULL)); // seed of time
    random = rand() % (2 *row + 2 * column - 8); // the quanlity of place that can be chosen as exit : 2 *row + 2 * column - 7
    if(random < column - 2)
        grid[0][random + 1] = '.';
    if(random >= column - 2 && random < 2 * column - 4) 
        grid[row - 1][random - column + 2 + 1] = '.';
    if(random >= 2 * column - 4 && random < 2 * column + row - 6)
        grid[random - 2 * column + 4 + 1][0] = '.';
    if(random >= 2 * column + row - 6)
        grid[random - 2 * column - row + 6 + 1][column - 1] = '.';

    // mover
    mover_r = (rand() % (row - 2)) + 1, mover_c = (rand() % (column - 2)) + 1, mover_d = rand() % 4;
    grid[mover_r][mover_c] =  direction[mover_d];
}

Grid::Grid(int r, int c, int mr, int mc, int d){ // build empty grid with r rows, c cols, and mover at row mr, col mc, and facing direction d
    
    if(d < 0 || d > 3) { // check if d is vaild
        cout << "The direction you set is invaild, help you set as EAST" <<endl;
        d = 3;
    }

    button = 1; // set button ON

    // if r, c are not in range 1 ~ 40, set as the closest integer in the range
    if(r < 1) r = 1;
    if(r > 40) r = 40;
    if(c < 1) c = 1;
    if(c > 40) c = 40;

    // if mr, mc is not in boundary of grid,  set as the closest integer in the grid
    if(mr < 0) mr = 0;
    if(mr >= r) mr = r - 1;
    if(mc < 0) mc = 0;
    if(mc >= c) mc = c - 1;
    row = r + 2, column = c + 2; // length of grid include blocks.
    cout << "Constructing a " << r << "x" << c << " Stack..." << endl;

    // build blocks
    for(i = 0; i < row; i ++){
        grid[i][0] = '#';
        grid[i][column - 1] = '#';
    }
    for(i = 0; i < column; i ++){
        grid[0][i] = '#';
        grid[row - 1][i] = '#';
    }

    for(i = 1; i < row - 1; i++){ // build grid (all '.');
        for(j = 1; j < column - 1 ; j++)
            grid[i][j] = '.';
    }

    // one random exit  
    srand((unsigned int)time(NULL)); // seed of time
    random = rand() % (2 *row + 2 * column - 8); // the quanlity of place that can be chosen as exit : 2 *row + 2 * column - 7
    if(random < column - 2)
        grid[0][random + 1] = '.';
    if(random >= column - 2 && random < 2 * column - 4) 
        grid[row - 1][random - column + 2 + 1] = '.';
    if(random >= 2 * column - 4 && random < 2 * column + row - 6)
        grid[random - 2 * column + 4 + 1][0] = '.';
    if(random >= 2 * column + row - 6)
        grid[random - 2 * column - row + 6 + 1][column - 1] = '.';

    // mover
    grid[mr + 1][mc + 1] =  direction[d];
    mover_r = mr + 1, mover_c = mc + 1, mover_d = d;
}

void Grid::Display() const { // display the grid on screen
    cout << "The Grid:" << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(button == 0 && grid[i][j] == ' ')
                cout << ".";
            else
                cout << grid[i][j];
            cout << " ";
        }
        cout << endl;
    }
} 

void Grid::TogglePath(){ // toggle whether or not moved path is shown
    if(button == 0)
        button = 1;
    else
        button = 0;
}

int Grid::GetRow() const{ // return row of the mover
    return mover_r - 1;
}
int Grid::GetCol() const{ // return column of the mover
    return mover_c - 1;
}
int Grid::GetNumRows() const{ // return number of rows in the grid
    return row - 2;
}
int Grid::GetNumCols() const{ // return number of columns in the grid
    return column - 2;
}

bool Grid::FrontIsClear() const{ // check to see if space in front of mover is clear
    if(mover_d == 0 && grid[mover_r - 1][mover_c] != '#')
        return true;
    else if(mover_d == 1 && grid[mover_r][mover_c - 1] != '#')
        return true;
    else if(mover_d == 2 && grid[mover_r + 1][mover_c] != '#')
        return true;
    else if(mover_d == 3 && grid[mover_r][mover_c + 1] != '#')
        return true;
    else
        return false;
}
bool Grid::RightIsClear() const{ // check to see if space to right of mover is clear
    if(mover_d == 0 && grid[mover_r][mover_c + 1] != '#')
        return true;
    else if(mover_d == 1 && grid[mover_r - 1][mover_c] != '#')
        return true;
    else if(mover_d == 2 && grid[mover_r][mover_c - 1] != '#')
        return true;
    else if(mover_d == 3 && grid[mover_r + 1][mover_c] != '#')
        return true;
    else
        return false;
}

void Grid::PutDown(){ // put down an item at the mover's position
    grid[mover_r][mover_c] = '@';
}
bool Grid::PutDown(int r, int c){ // put down an item at (r, c), if possible, if failed return false
    if(r < 0 || r > row - 2|| c < 0 || c > column - 2)
        return false;
    else if(grid[r + 1][c + 1] == '0' || grid[r + 1][c + 1] == '#' || grid[r + 1][c + 1] == '@')
        return false;
    else
        grid[r + 1][c + 1] = '0';
    return true;
}
bool Grid::PickUp(){ // pick up item at current position, if failed return false
    if(grid[mover_r][mover_c] == '@'){
        grid[mover_r][mover_c] = direction[mover_d];
        return true;
    }
    return false;
}
bool Grid::PlaceBlock(int r, int c){ // put a block at (r, c), if possible, if failed return false
    i = 0;
    if(r >= 0 && r <= row -2 && c >= 0 && c <= column - 2){ // put a block
        if(grid[r + 1][c + 1] == '.' || grid[r + 1][c + 1] == ' '){
            tmp = grid[r + 1][c + 1];
            grid[r + 1][c + 1] = '#';
            i = 1; // if it could => set i = 1;
        }
    }
    if(i == 0)
        return false;
    
    // check if the exit still alive
    for(i = 0; i < row; i ++){ 
        if(grid[i][0] != '#' || grid[i][column - 1] != '#')
            return true;
    }
    for(i = 0; i < column; i ++){
        if(grid[0][i] != '#' || grid[row - 1][i] != '#')
            return true;
    }
    grid[r + 1][c + 1] = tmp;
    return false;
}

bool Grid::Move(int s){ // move forward s spaces, if possible, if failed return false
    if(s <= 0 || s > 40) // check if step < 0 or > 40 (if step > 40, then it would absolutely out of grid after move)
        return false;

    // check if the move is vaild for four situation
    if(mover_d == 0){
        if(mover_r - s < 0) // if mover will be out of grid after move
            return false;
        for(i = 0; i <= s; i++){ // if there's '#' on the path
            if(grid[mover_r - i][mover_c] == '#')
                return false;
        }

        // move and change state on the path
        if(grid[mover_r][mover_c] == '@') // change the state of mover's location before move
            grid[mover_r][mover_c] = '0';
        for(i = 0; i <= s; i++){ // change the state of mover's location between move
            if(grid[mover_r - i][mover_c] != '0')
                grid[mover_r - i][mover_c] = ' ';
        }
        mover_r -= s;
    }
    if(mover_d == 1){
        if(mover_c - s < 0) // if mover will be out of grid after move
            return false;
        for(i = 0; i <= s; i++){ // if there's '#' on the path
            if(grid[mover_r][mover_c - i] == '#')
                return false;
        }
        
        // move and change state on the path
        if(grid[mover_r][mover_c] == '@') // change the state of mover's location before move
            grid[mover_r][mover_c] = '0';
        for(i = 0; i <= s; i++){ // change the state of mover's location between move
            if(grid[mover_r][mover_c - i] != '0')
                grid[mover_r][mover_c - i] = ' ';
        }
        mover_c -= s;
    }
    if(mover_d == 2){
        if(mover_r + s >= row) // if mover will be out of grid after move
            return false;
        for(i = 0; i <= s; i++){ // if there's '#' on the path
            if(grid[mover_r + i][mover_c] == '#')
                return false;
        }
        
        // move and change state on the path
        if(grid[mover_r][mover_c] == '@') // change the state of mover's location before move
            grid[mover_r][mover_c] = '0';
        for(i = 0; i <= s; i++){ // change the state of mover's location between move
            if(grid[mover_r + i][mover_c] != '0')
                grid[mover_r + i][mover_c] = ' ';
        }
        mover_r += s;
    }
    if(mover_d == 3){
        if(mover_r + s >= column) // if mover will be out of grid after move
            return false;
        for(i = 0; i <= s; i++){ // if there's '#' on the path
            if(grid[mover_r][mover_c + i] == '#')
                return false;
        }

        // move and change state on the path
        if(grid[mover_r][mover_c] == '@') // change the state of mover's location before move
            grid[mover_r][mover_c] = '0';
        for(i = 0; i <= s; i++){ // change the state of mover's location between move
            if(grid[mover_r][mover_c + i] != '0')
                grid[mover_r][mover_c + i] = ' ';
        }
        mover_c += s;
    }

    // change the state of mover's location after move
    if(grid[mover_r][mover_c] != '0'){
        grid[mover_r][mover_c] = direction[mover_d];
        return true;
    }
    grid[mover_r][mover_c] = '@';
    return true;
}

void Grid::TurnLeft(){ // turn the mover to the left
    if(mover_d == 3)
        mover_d = 0;
    else
        mover_d++;
    if(grid[mover_r][mover_c] != '@')
        grid[mover_r][mover_c] = direction[mover_d];
}

void Grid::Grow(int gr, int gc){ // grow the grid by gr rows, gc columns
    if(gr <= 0 || gc <= 0){ // check if gr, gc are vaild
        cout << "Grow means bigger, so your input should be bigger than 0" << endl;
        return;
    }
    
    if(row + gr - 2 > 40) // if row would we large than 40 after grow, set as 40
        gr -= (row + gr - 2 - 40);
    if(column + gc - 2 > 40) // if column would we large than 40 after grow, set as 40
        gc -= (column + gc - 2 - 40);

    cout << "Grow stack to a " << row + gr - 2 << "x" << column + gc - 2 << " stack" << endl;
    
    for(i = 0; i < row + gr; i++){ //build the grid
        for(j = 0; j < column + gc; j++){
            if(i == row - 1 && j < column && j > 0){ // if it's on the block of down side of original grid
                grid[row + gr - 1][j] = grid[i][j]; // put it's state to the block of new grid
                grid[i][j] = '.';
            }
            else if(j == column - 1 && i < row && i > 0){ // if it's on the block of right side of original grid
                grid[i][column + gc -1] = grid[i][j]; // put it's state to the block of new grid
                grid[i][j] = '.';
            }
            else if(i < row && j < column){ // if it's in the original grid or it's on the block of left/up side of original grid
                continue;
            }
            else if(i == row + gr - 1 || j == column + gc - 1 || i == 0 || j == 0){ // if it's on the block of new grid, and it's state hasn't been set
                if(grid[i][j] != '#' && grid[i][j] != '.')
                    grid[i][j] = '#';
            }
            else{ // if it's in the new grid but not in the original grid
                grid[i][j] = '.';
            }
        }
    }

    // set new state of grid
    row += gr;
    column += gc;
    grid[row - 1][column - 1] = '#';
}