#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;
const int UNASSIGNED = 0;
const int grid_size = 9;
int level = 0;
int Solution_Grid[grid_size][grid_size] = { 0 };
// Color of the console
HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

//print title
void print_title()
{
    int k = 48;
    cout << endl << endl << endl << endl;
    cout << string(k, ' ') << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$      " << endl;
    cout << string(k, ' ') << "$$                                                                   $$      " << endl;
    cout << string(k, ' ') << "$$    $$$$$$   $$    $$   $$$$$$      $$$$$$    $$   $$   $$    $$   $$      " << endl;
    cout << string(k, ' ') << "$$   $$        $$    $$   $$   $$    $$    $$   $$  $$    $$    $$   $$      " << endl;
    cout << string(k, ' ') << "$$   $$        $$    $$   $$    $$   $$    $$   $$ $$     $$    $$   $$      " << endl;
    cout << string(k, ' ') << "$$    $$$$$    $$    $$   $$    $$   $$    $$   $$$$      $$    $$   $$      " << endl;
    cout << string(k, ' ') << "$$        $$   $$    $$   $$    $$   $$    $$   $$ $$     $$    $$   $$      " << endl;
    cout << string(k, ' ') << "$$        $$   $$    $$   $$   $$    $$    $$   $$  $$    $$    $$   $$      " << endl;
    cout << string(k, ' ') << "$$   $$$$$$     $$$$$$    $$$$$$      $$$$$$    $$   $$    $$$$$$    $$      " << endl;
    cout << string(k, ' ') << "$$                                                                   $$      " << endl;
    cout << string(k, ' ') << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$      " << endl;
    cout << endl << endl << endl << endl << endl << endl;
}

//FileHandling
/*void File()
{
    ofstream file{ "Game1.txt" };
    if (!file.is_open()) return -1;

    for (int row = 0; row < grid_size; row++)
        for (int col = 0; col < grid_size; col++)
            file << grid[row][col];
}*/

//Menu Page
char Menu()
{
    char ch;
    int k = 75;
    system("Color F5");
    cout << string(k, ' ') << "    START GAME-S    " << endl;
    cout << string(k, ' ') << "    LOAD GAME-L     " << endl;
    cout << string(k, ' ') << "INSTRUCTION MANUAL-I" << endl;
    cout << string(k, ' ') << "    QUIT GAME-Q     " << endl;
    cout << string(k, ' ') << "   ENTER CHOICE : ";
    cin.clear();
    cin >> ch;
    return ch;
}

// Check for empty cell location
bool checkEmptyCell(int grid[grid_size][grid_size], int& row, int& col)
{
    for (row = 0; row <grid_size; row++)
        for (col = 0; col <grid_size; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

// Check if num exists in row or column
bool usedInRowOrCol(int grid[grid_size][grid_size], int row, int col, int num)
{
    for (int idx = 0; idx <grid_size; idx++)
        if (grid[row][idx] == num || grid[idx][col] == num)
            return true;
    return false;
}

// Check if num exists in 3 x 3 box
bool usedInBox(int grid[grid_size][grid_size], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

// Check if it is allowed to assign number in location 
bool isSafe(int grid[grid_size][grid_size], int row, int col, int num)
{
    return !usedInRowOrCol(grid, row, col, num) && !usedInBox(grid, row - row % 3, col - col % 3, num);
}

// Creating Sudoku Board
bool createSudokuBoard(int grid[grid_size][grid_size])
{
    int row, col;
    if (!checkEmptyCell(grid, row, col))
        return true;
    for (int nu = 0; nu < 9; nu++)
    {
        int num = rand() % 9 + 1;
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (createSudokuBoard(grid))
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

//Copy sodoku board
void Save_Solution(int grid[grid_size][grid_size])
{
    for (int row = 0; row < grid_size; row++)
    {
        for (int col = 0; col < grid_size; col++)
        {
            Solution_Grid[row][col] = grid[row][col];
        }
    }
}

//assigning empty cells in grid randomly
void emptyRandomGridCells(int grid[grid_size][grid_size], int total_cells)
{
    for (int i = 0; i < total_cells; i++)
    {
        while (true)
        {
            int row_num = rand() % grid_size - 1;
            int col_num = rand() % grid_size - 1;

            if (grid[row_num][col_num] != UNASSIGNED)
            {
                grid[row_num][col_num] = UNASSIGNED;
                break;
            }
        }

    }
}

// print grid  
void printGrid(int grid[grid_size][grid_size])
{
    system("cls");
    cout << endl << endl << endl;
    int sp = 61;
    //level number tag
    {
        int space = sp + 15;
        cout << string(space, ' ') << string(13, '@') << endl;
        cout << string(space, ' ') << "@" << string(11, ' ') << "@" << endl;
        if (level > 9)
            cout << string(space, ' ') << "@ LEVEL " << level << "  @";
        else
            cout << string(space, ' ') << "@  LEVEL " << level << "  @";
        cout << endl;
        cout << string(space, ' ') << "@" << string(11, ' ') << "@" << endl;
        cout << string(space, ' ') << string(13, '@') << endl;
        cout << endl << endl << endl << endl;
    }
    //upper horizontal co-ordinates
    cout << string(sp + 3, ' ');
    cout << "1   2   3     4   5   6     7   8   9" << endl;

    for (int row = 0; row <grid_size; row++)
    {
        if ((row + 3) % 3 == 0)
            cout << string(sp, ' ') << string(43, '$');
        else
        {
            cout << string(sp - 1, ' ');
            for (int count = 0; count < 3; count++)
                cout << " $ " << "---+---+---";
            cout << " $";
        }
        cout << endl;
        cout << string(sp - 2, ' ');
        for (int col = 0; col < grid_size; col++)
        {
            if (col == 0)
                cout << row+1 << " $ ";
            else if (col % 3 == 0)
                cout << " $ ";
            else
                cout << "|";
            if (grid[row][col] == 0)
                cout << " " << " " << " ";
            else
            {
                //SetConsoleTextAttribute(console_color, 6);
                cout << " " << grid[row][col] << " ";
            }
            if (col == grid_size - 1)
                cout << " $ " << row + 1;
        }
        cout << endl;
    }
    cout << string(sp, ' ') << string(43, '$') << endl;
    //lower horizontal co-ordinates
    cout << string(sp + 3, ' ');
    cout << "1   2   3     4   5   6     7   8   9" << endl << endl << endl;
}

//Comparing Grids
bool comparison(int grid[grid_size][grid_size])
{
    for (int row = 0; row < grid_size; row++)
        for (int col = 0; col < grid_size; col++)
            if (Solution_Grid[row][col] != grid[row][col])
                return false;
    return true;
}

//CONGRATULATIONS    
void CONGRATS()
{
    system("cls");
    char nums;
    int sp = 40;
    cout << endl << endl << endl;
    cout << string(sp, ' ') << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;
    cout << string(sp, ' ') << "@@@@@@@   @@@@@@@@@   @@@@@     @@@   @@@@@@@   @@@@@@@     @@@@@@@    @@@@@@@@@   @@@@@@@@@" << endl;
    cout << string(sp, ' ') << "@@@@@@@   @@@@@@@@@   @@@@@@    @@@   @@@@@@@   @@@@@@@@   @@@@@@@@@   @@@@@@@@@   @@@@@@@@@" << endl;
    cout << string(sp, ' ') << "@@@       @@@   @@@   @@@ @@@   @@@   @@@       @@@  @@@   @@@   @@@      @@@      @@@      " << endl;
    cout << string(sp, ' ') << "@@@       @@@   @@@   @@@  @@@  @@@   @@@       @@@@@@@@   @@@@@@@@@      @@@      @@@@@@@@@" << endl;
    cout << string(sp, ' ') << "@@@       @@@   @@@   @@@   @@@ @@@   @@@  @@   @@@@@@     @@@@@@@@@      @@@            @@@" << endl;
    cout << string(sp, ' ') << "@@@@@@@   @@@@@@@@@   @@@    @@@@@@   @@@@@@@   @@@ @@@    @@@   @@@      @@@      @@@@@@@@@" << endl;
    cout << string(sp, ' ') << "@@@@@@@   @@@@@@@@@   @@@     @@@@@   @@@@@@@   @@@  @@@   @@@   @@@      @@@      @@@@@@@@@" << endl << endl;
    cout << string(sp, ' ') << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl << endl;
    cout << "Press any key to go back to main menu...." << endl;
    cin >> nums;
}

void saveGame(int grid[grid_size][grid_size], int sol_grid[grid_size][grid_size])
{
    char num;
    ofstream file{ "load_game.txt" };
    for (int row = 0; row < grid_size; row++, file << endl)
        for (int col = 0; col < grid_size; col++)
            file << grid[row][col] << " ";

    for (int row = 0; row < grid_size; row++, file << endl)
        for (int col = 0; col < grid_size; col++)
            file << Solution_Grid[row][col] << " ";

    file.close();
    cout << "Game saved. Press any key to conitune." << endl;
    cin >> num;
}

//Ask user for co-ordinates
void AskUserCordinates(int grid[grid_size][grid_size])
{
    int num, x, y;
    char save_option;
    while (true) 
    {
        cout << "Please select (s) to save the game or (c) to continue: ";
        cin >> save_option;
        if (save_option == 's')
        {
            saveGame(grid, Solution_Grid);
        }
        x = 0, y = 0;
        cout << "CO-ORDINATES:" << endl;
        while (x < 1 || x > 9)
        {
            cout << "Enter the X co-ordinate : ";
            cin >> x;
        }

        while (y < 1 || y > 9)
        {
            cout << "Enter the Y co-ordinate : ";
            cin >> y;
        }

        if (grid[x - 1][y - 1] != 0)
            cout << "Sorry the chosen cell is fixed" << endl << "Try Again" << endl;
        else
        {
            num = 0;
            while (num < 1 || num > 9)
            {
                cout << "Enter your value : ";
                cin >> num;
            }
            if (isSafe(grid, x - 1, y - 1, num))
            {
                grid[x - 1][y - 1] = num;
                system("cls");
                printGrid(grid);
            }
            else
            {
                cout << "WRONG ANSWER! Please Try Again." << endl;
            }
            if (comparison(grid))
                break;
        }
    }
    CONGRATS();
}

//choosing level of complexity from range of 1-20
int Level(int grid[grid_size][grid_size])
{
    system("cls");
    int lev = 1;
    //printing page layout
    for (int j = 1; j <= 4; j++)
    {
        cout << endl << endl << endl;
        for (int i = 0; i < 5; i++)
            cout << string(5, ' ') << string(13, '@') << string(5, ' ');
        cout << endl;
        for (int i = 0; i < 5; i++)
            cout << string(5, ' ') << "@" << string(11, ' ') << "@" << string(5, ' ');
        cout << endl;
        for (int l = 1; l < 6; l++)
        {
            if (lev > 9)
                cout << string(5, ' ') << "@ LEVEL " << lev++ << "  @" << string(5, ' ');
            else
                cout << string(5, ' ') << "@  LEVEL " << lev++ << "  @" << string(5, ' ');
        }
        cout << endl;
        for (int i = 0; i < 5; i++)
            cout << string(5, ' ') << "@" << string(11, ' ') << "@" << string(5, ' ');
        cout << endl;
        for (int i = 0; i < 5; i++)
            cout << string(5, ' ') << string(13, '@') << string(5, ' ');
    }
    cout << endl << endl << endl;
    int l;
    cout << " Choose Level Number : ";
    cin >> l;
    emptyRandomGridCells(grid, (10 + (2 * (l - 1))));
    return l;
}

//Instruction manual
void instuctions()
{
    system("cls");
    cout << endl << endl << endl << endl;
    cout << " $$ $$  $$$$$  $$  $$  $$    $$$$$$  $$$$$    $$$$$  $$    $$$$$  $$  $$" << endl;
    cout << " $$$$$  $$ $$  $$  $$  $$      $$    $$ $$    $$ $$  $$    $$ $$   $$$$ " << endl;
    cout << " $$ $$  $$ $$   $$$  $$$       $$    $$ $$    $$$$$  $$    $$$$$    $$  " << endl ;
    cout << " $$ $$  $$$$$    $$  $$        $$    $$$$$    $$     $$$$  $$ $$    $$  " << endl << endl;
    cout << " ######################################################################" << endl;
    cout << " ######################################################################" << endl << endl << endl;
    cout << "Sudoku is one of the most popular classic games. The playing grid of sudoku consists of the 9 * 9 squares space.The game initially has 9 squares" << endl;
    cout << "combining rows and columns.Out of these 9 squares, every square is a separate grid of 3 * 3 square spaces.Every rowand column consist of 9 squares." << endl;
    cout << "The game’s primary purpose is to fill boxes in every square with numbers ranging from 1 to 9.The exciting thing about the Sudoku game is that no"<< endl;
    cout << "column, row, or square allows repeating a number.Moreover, the game initially fills some of the squares with random numbers from 1 to 9.The rest " << endl;
    cout << "of the boxes or squares are left empty for the player to fill.The number of already filled boxes determines the complexity of the game." << endl << endl;
    cout << "After starting the game, choose the level of complexity you want to play. When you choose the level, partially empty sudoku board will appear." << endl;
    cout << " You can fill the empty cells in the board by entering the co-ordiates of those cells. Once all the cells are filled with correct values, the " << endl;
    cout << "level will end.";
}

void loadGame(int grid[grid_size][grid_size])
{
    int num;
    ifstream file{ "load_game.txt" };
    if (!file.is_open())
    {
        cout << "No save game exist...  Press any key to continue" << endl;
        cin >> num;
    }
    else
        for (int row = 0; row < grid_size; row++)
            for (int col = 0; col < grid_size; col++)
                file >> grid[row][col];

    file.close();
}

// Main 
int main()
{
    srand((unsigned)time(NULL));
    int grid[grid_size][grid_size] = { 0 };
    while (true)
    {
        system("cls");
        print_title();
        char option = Menu();
        if (option == 's' || option == 'S')
        {
            //system("cls");
            //to check solution board remove comment bar below;
            //printGrid(grid);
            print_title();
            createSudokuBoard(grid);
            Save_Solution(grid);
            level = Level(grid);
            printGrid(grid);
            AskUserCordinates(grid);

        }
        else if (option == 'l' || option == 'L')
        {
            loadGame(grid);
            printGrid(grid);
            AskUserCordinates(grid);
        }
        else if (option == 'i' || option == 'I')
        {
            instuctions();
        }
        else if (option == 'q' || option == 'Q')
        {
            return 0;
        }
       
    }
}
