//Sudoku Solver 2 -- Program to solve sudoku puzzles (better than the original)
//Nicholas Harris


#include <stdio.h>
#include <iostream>

using namespace std;

//Function to enter row/col/number into board
bool enterNumber( int row, int col, int num, int board[9][9] );

//Function to print board
void printBoard(int board[9][9]);

//Functions to solve the given board (with brute-force recursive backtracking)
bool solve( int board[9][9] );
bool solveHelper( int board[9][9], int row, int col );

//Function to check for innaccuracies ( used by solver functions )
bool checkMistakes( int board[9][9] );

//Function to make all single-candidate deductions
//(Condition where a given cell has only one possible value)
bool findSingleCandidates ( int board[9][9] );

//Function to make all single-placement deductions
//(Condition where a given number has only one candidate cell in a row, column, or region.)
bool findSinglePlacements ( int board[9][9] );

//Function to determine if board is filled
bool isFilled( int board[9][9] );



//main driver
int main()
{
	cout << endl << endl << "Welcome." << endl << endl;
    
    
    //create board and initialize values to zero (blank)
    int board[9][9];
    
    for( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            board[i][j] = 0;
        }
    }
    
    //Empty board is printed
    printBoard( board );
    
    
    //Instructions for user
    cout << endl << endl << "Enter numbers into the grid: (row col num)." << endl;
    cout << "Enter 0 0 0 when done." << endl << endl;
    
    int row, col, num;
    
    
    //User enters numbers into board until the initial puzzle is given
    do
    {
        row = col = num = 0;
        
        cin >> row;
        cin >> col;
        cin >> num;
        
        enterNumber( row, col , num, board );
        
        printBoard(board);
    }while( row + col + num != 0 );
    
    
    //Now all initial deductions are made ( this may solve some puzzles )
    bool found1 = false;
    bool found2 = false;
    do
    {
        found1 = findSingleCandidates( board );
        found2 = findSinglePlacements( board );
        
        cout << endl << endl;
        printBoard(board);
        cout << endl << endl;
    }while( found1 == true || found2 == true);
    
    
    //if the solution was found using only deductions
    if ( isFilled( board ) == true )
    {
        cout << endl << endl;
        printBoard(board);
        cout << endl << endl;
        
        cout << " A solution was found using only single-candidate and " << endl;
        cout << " single-placement deductions! Brute-force recursive backtracing " << endl;
        cout << " Wasn't necessary!" << endl << endl;
        
        return 0;
    }
   

    //Now we attempt to solve the puzzle through recursive backtracking.
    solve(board);
    
    
    return 0;
}



//Function to determine if board is filled
bool isFilled( int board[9][9] )
{
    for ( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            if ( board[i][j] == 0 )
            {
                return false;
            }
        }
    }
    
    return true;
}


//Function to make all single-placement deductions
bool findSinglePlacements ( int board[9][9] )
{
    int goodRow = -1;
    int goodCol = -1;
    int possibilities = 0;
    
    bool deductionMade = false;
    
    
    //For every number, see if there is only one place to place it
    //in each row, column, and region
    for ( int i = 1; i < 10; i++ )
    {
        //check rows
        for ( int j = 0; j < 9; j++ )
        {
            for ( int k = 0; k < 9; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
            
            //if there is a single placement possibility in this row
            if ( possibilities == 1 )
            {
                board[goodRow][goodCol] = i;
                deductionMade = true;
            }
            
            goodRow = -1;
            goodCol = -1;
            possibilities = 0;
        }
        
        //check columns
        for ( int j = 0; j < 9; j++ )
        {
            for ( int k = 0; k < 9; k++ )
            {
                if ( board[k][j] == 0 )
                { 
                    board[k][j] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = k;
                        goodCol = j;
                    }
                    board[k][j] = 0;
                    
                }
            }
            
            //if there is a single placement possibility in this column
            if ( possibilities == 1 )
            {
                board[goodRow][goodCol] = i;
                deductionMade = true;
            }
            
            goodRow = -1;
            goodCol = -1;
            possibilities = 0;
        }
        
        
        //Check regions
        
        //FIRST REGION//
        for ( int j = 0; j < 3; j++ )
        {
            for( int k = 0; k < 3; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        //SECOND REGION//
        for ( int j = 0; j < 3; j++ )
        {
            for( int k = 3; k < 6; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        //Third Region
        for ( int j = 0; j < 3; j++ )
        {
            for( int k = 6; k < 9; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        
        //Fourth Region
        for ( int j = 3; j < 6; j++ )
        {
            for( int k = 0; k < 3; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        //Fifth Region
        for ( int j = 3; j < 6; j++ )
        {
            for( int k = 3; k < 6; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        
        //Sixth region
        for ( int j = 3; j < 6; j++ )
        {
            for( int k = 6; k < 9; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        //Seventh region
        for ( int j = 6; j < 9; j++ )
        {
            for( int k = 0; k < 3; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        //Eighth region
         for ( int j = 6; j < 9; j++ )
        {
            for( int k = 3; k < 6; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
        
        
        
        //Ninth region
         for ( int j = 6; j < 9; j++ )
        {
            for( int k = 6; k < 9; k++ )
            {
                if ( board[j][k] == 0 )
                { 
                    board[j][k] = i;
                    if ( checkMistakes(board) == false )
                    {
                        possibilities++;
                        goodRow = j;
                        goodCol = k;
                    }
                    board[j][k] = 0;
                    
                }
            }
        }
        
        //if there is a single placement possibility in this region
        if ( possibilities == 1 )
        {
            board[goodRow][goodCol] = i;
            deductionMade = true;
        }
            
        goodRow = -1;
        goodCol = -1;
        possibilities = 0;
       
    
    
        
    }
    
    return deductionMade;
}

//Function to make all single-candidate deductions
bool findSingleCandidates ( int board[9][9] )
{
    int possibilities = 0;
    bool deductionMade = false;
    int deducedAnswer = 0;

    //Check all possibilities for all cells
    for ( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            if ( board[i][j] == 0 )
            {
                for ( int k = 1; k < 10; k++ )
                {
                    board[i][j] = k;
                    if ( checkMistakes(board) == false ) 
                    {
                        possibilities++;
                        deducedAnswer = k;
                    }
                }
                
                //if a lone candidate is found, it is locked in
                if ( possibilities == 1 )
                {
                    board[i][j] = deducedAnswer;
                    deducedAnswer = 0;
                    deductionMade = true;
                    possibilities = 0;
                }
                else
                {
                    board[i][j] = 0;
                    deducedAnswer = 0;
                    possibilities = 0;
                }
                    
            }
        }
    }
    
    
    return deductionMade;
}


//solve function, makes use of helper function
bool solve( int board[9][9] ) 
{
   if ( solveHelper( board, 0, 0 ) == true )
   {
       return true;
   }
   else
   {
       cout << endl << endl;
       cout << "  No solution found! " << endl << endl;
       
       return false;
   }
}


//Function to solve the puzzle through recursive backtracking
bool solveHelper( int board[9][9], int row, int col )
{
    //initialize new board to be manipulated
    int newBoard[9][9];
    
    for( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            newBoard[i][j] = board[i][j];
        }
    }
    
    bool found1 = false;
    bool found2 = false;
    do
    {
        found1 = findSingleCandidates( newBoard );
        found2 = findSinglePlacements( newBoard );
        
    }while( found1 == true || found2 == true);
    
    
    //print the current board being examined for testing purposed
    cout << endl << endl;
    cout << "Row: " << row << "Col: " << col << endl << endl;
    printBoard( newBoard );
    cout << endl << endl;
    
    //check if this space was already given as a hint;
    //if so, move to the next space
    
    if ( newBoard[row][col] != 0 )
    {
        cout << "This space is a hint! " << endl;
        
        //If the puzzle is solved
        if ( isFilled( newBoard ) == true && checkMistakes( newBoard ) == false )
        {
            cout << endl << endl;
            printBoard( newBoard );
            cout << endl << endl;
            cout << "  Solution found through single-candidate deductions," << endl;
            cout << "  single-placement deductions, and recursive backtracking!" << endl << endl;
                
            return true;
        }
        else if ( col < 8 )
        {
            return solveHelper( newBoard, row, col + 1 );
        }
        else if ( col >= 8 && row < 8 )
        {
            return solveHelper( newBoard, row + 1, 0 );
        }
        else if ( col >= 8 && row >= 8 )    //if we find ourselves at the end
        {
            if ( checkMistakes(newBoard) == false )
            {
                cout << endl << endl;
                printBoard( newBoard );
                cout << endl << endl;
                cout << "  Solution found through single-candidate deductions," << endl;
                cout << "  single-placement deductions, and recursive backtracking!" << endl << endl;
                
                return true;
            }
            else
            {
               // cout << endl << endl;
               // cout << "  No solution found! " << endl << endl;
                return false;
            }
        }
    }
    
    
    //This space was not given as a hint.
    //We will try all possible values for this space.
    for( int i = 1; i < 10; i++ )
    {
        newBoard[row][col] = i;
        if ( checkMistakes(newBoard) == false )
        {
            if ( col < 8 )
            {
                if ( solveHelper( newBoard, row, col + 1 ) == true )
                {
                    return true;
                }
            }
            else if ( col >= 8 && row < 8 )
            {
                if ( solveHelper( newBoard, row + 1, 0 ) == true )
                {
                    return true;
                }
            }
            else if ( col >= 8 && row >= 8 )    //if we find ourselves at the end
            {
                if ( checkMistakes(newBoard) == false )
                {
                    cout << endl << endl;
                    printBoard( newBoard );
                    cout << endl << endl;
                    cout << " Solution found through brute-force recursive backtracking! " << endl << endl;
                    
                    return true;
                }
            }
        }
    }
    
    
    //if all of the above fails, return false
    return false;
}



//Function to check if the given board has a mistake
bool checkMistakes( int board[9][9] )
{
    int valueCounter[9];
    
    int valueIndex = 0;
    
    for( int i = 0; i < 9; i++ )
    {
        valueCounter[i] = 0;
    }
    
    
    //////////////////
    //CHECK ALL ROWS
    /////////////////
    for( int i = 0; i < 9; i ++)
    {
        //Examine all numbers in this row
        for ( int j = 0; j < 9; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
        
        //Check valueCounter for repetitions of numbers
        for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
        {
            if ( valueCounter[valueIndex] > 1 )
            {
                return true;
            }
        }
        
        //if there were no repetitions, reset valueCounter for next row
        for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
        {
            valueCounter[valueIndex] = 0;
        }
       
    }
    
    //Reset valueCounter once more for good measure
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    
    /////////////////////
    //CHECK ALL COLUMNS
    ////////////////////
    for( int i = 0; i < 9; i ++)
    {
       //Examine all numbers in this column
        for ( int j = 0; j < 9; j++ )
        {
            if( board[j][i] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[j][i] - 1]++;
            }
        }
        
        //Check valueCounter for repetitions of numbers
        for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
        {
            if ( valueCounter[valueIndex] > 1 )
            {
                return true;
            }
        }
        
        //if there were no repetitions, reset valueCounter for next column
        for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
        {
            valueCounter[valueIndex] = 0;
        }
    }
    
    
    //Reset valueCounter once more for good measure
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    //////////////////////////
    //CHECK ALL SQUARE REGIONS
    //////////////////////////
    
    //FIRST REGION//
    for ( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    //SECOND REGION//
    for ( int i = 0; i < 3; i++ )
    {
        for( int j = 3; j < 6; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    //THIRD REGION//
    for ( int i = 0; i < 3; i++ )
    {
        for( int j = 6; j < 9; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    //FOURTH REGION//
    for ( int i = 3; i < 6; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    //FIFTH REGION//
    for ( int i = 3; i < 6; i++ )
    {
        for( int j = 3; j < 6; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    //SIXTH REGION//
    for ( int i = 3; i < 6; i++ )
    {
        for( int j = 6; j < 9; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    //SEVENTH REGION//
    for ( int i = 6; i < 9; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    //EIGHTH REGION//
    for ( int i = 6; i < 9; i++ )
    {
        for( int j = 3; j < 6; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    //NINTH REGION//
    for ( int i = 6; i < 9; i++ )
    {
        for( int j = 6; j < 9; j++ )
        {
            if( board[i][j] > 0 )
            {
                //Instance of number is counted
                valueCounter[ board[i][j] - 1]++;
            }
        }
    }
        
    //Check valueCounter for repetitions of numbers
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        if ( valueCounter[valueIndex] > 1 )
        {
            return true;
        }
    }
        
    //if there were no repetitions, reset valueCounter for next region
    for ( valueIndex = 0; valueIndex < 9; valueIndex++ )
    {
        valueCounter[valueIndex] = 0;
    }
    
    
    
    
    
    
    
    //No mistakes were found, so the board is acceptable.
    return false;
}




//Function to enter number into the board
bool enterNumber( int row, int col, int num, int board[9][9] )
{
    //Make sure numbers are valid
    if ( row < 0 || row > 9 || col < 0 || col > 9 || num > 9 || num < 0 )
    {
        return false;
    }
    else
    {
        board[row - 1][col - 1] = num;
        return true;
    }
}


//Function to print the board
void printBoard( int board[9][9] )
{
    cout << endl << endl;
    
    for( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            cout << "| ";
            
            if ( board[i][j] != 0 )
            {
                cout << board[i][j];
            }
            else
            {
                cout << " ";
            }
            
            cout << " |";
            
            if ( j == 2 || j == 5 )
            {
                cout << '+';
            }
        }
        cout << endl;
        if ( i == 2 || i == 5 )
        {
            cout << "+  +  +  +  +  +  +  +  +  +  +  +  +  +  +  +  +";
        }
        else
        {
            cout << "               +               +";
        }
        cout << endl;
    }
}
