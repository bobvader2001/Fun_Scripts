//Author: bobvader2001

#include <stdio.h>
#include <stdlib.h>

int board[9][9];

void initialiseBoard(char * filename) //Populates the board array from the input file
{
  FILE *input; //Initialise file pointer
  if((input = fopen(filename, "r"))) //Open file as read
  {
    int counter = 0;
    char line[15];
    while (fgets(line, sizeof line, input) != NULL) //Read the file line by line
    {
       for(int i = 0; i < 9; i++)
       {
         board[counter][i] = line[i] - '0'; //Save the int value of each number in the line into the board array
       }
       counter++; //Increment the counter (used to identify the row in the board)
    }
    fclose (input); //Close the file
  }
  else
  {
    printf("\nError: File not found\n\n");
    exit(1);
  }

}

void printBoard(int input_board[9][9]) //Prints the board out
{
  printf("+-------+-------+-------+\n");
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[0][0], input_board[0][1], input_board[0][2], input_board[0][3], input_board[0][4], input_board[0][5], input_board[0][6], input_board[0][7], input_board[0][8]);
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[1][0], input_board[1][1], input_board[1][2], input_board[1][3], input_board[1][4], input_board[1][5], input_board[1][6], input_board[1][7], input_board[1][8]);
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[2][0], input_board[2][1], input_board[2][2], input_board[2][3], input_board[2][4], input_board[2][5], input_board[2][6], input_board[2][7], input_board[2][8]);
  printf("+-------+-------+-------+\n");
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[3][0], input_board[3][1], input_board[3][2], input_board[3][3], input_board[3][4], input_board[3][5], input_board[3][6], input_board[3][7], input_board[3][8]);
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[4][0], input_board[4][1], input_board[4][2], input_board[4][3], input_board[4][4], input_board[4][5], input_board[4][6], input_board[4][7], input_board[4][8]);
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[5][0], input_board[5][1], input_board[5][2], input_board[5][3], input_board[5][4], input_board[5][5], input_board[5][6], input_board[5][7], input_board[5][8]);
  printf("+-------+-------+-------+\n");
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[6][0], input_board[6][1], input_board[6][2], input_board[6][3], input_board[6][4], input_board[6][5], input_board[6][6], input_board[6][7], input_board[6][8]);
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[7][0], input_board[7][1], input_board[7][2], input_board[7][3], input_board[7][4], input_board[7][5], input_board[7][6], input_board[7][7], input_board[7][8]);
  printf("| %d %d %d | %d %d %d | %d %d %d |\n", input_board[8][0], input_board[8][1], input_board[8][2], input_board[8][3], input_board[8][4], input_board[8][5], input_board[8][6], input_board[8][7], input_board[8][8]);
  printf("+-------+-------+-------+\n");
}

int checkZero(int * array) //Checks a 9 byte array contains only 0s
{
  for(int i = 0; i < 9; i++)
  {
    if(array[i] != 0)
    {
      return 0;
    }
  }
  return 1;
}

int checkWin() //Checks if the given array is a valid solution
{
  int numbers1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int numbers2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  //CHECK VERTICAL AND HORIZONTAL VALID
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(board[i][j] == 0) //If there is an empty space on the board, there is no win
      {
        return 0;
      }

      for(int index = 0; index < 9; index++)
      {
        if(board[i][j] == numbers1[index])
        {
          numbers1[index] = 0;
        }
        if(board[j][i] == numbers2[index])
        {
          numbers2[index] = 0;
        }
      }
    }
    if(checkZero(numbers1))
    {
      for(int i = 1; i < 10; i++)
      {
        numbers1[i] = i;
      }
    }else
    {
      return 0;
    }
    if(checkZero(numbers2))
    {
      for(int i = 1; i < 10; i++)
      {
        numbers2[i] = i;
      }
    }else
    {
      return 0;
    }
  }

  //CHECK SQUARE VALID
  for(int vert_square = 0; vert_square < 3; vert_square++)
  {
    for(int horiz_square = 0; horiz_square < 3; horiz_square++)
    {
      for(int square_row = 0; square_row < 3; square_row++)
      {
        for(int square_column = 0; square_column < 3; square_column++)
        {
          for(int index = 0; index < 9; index++)
          {
            if(board[vert_square * 3 + square_row][horiz_square * 3 + square_column] == numbers1[index])
            {
              numbers1[index] = 0;
              break;
            }
          }
        }
      }
      if(checkZero(numbers1))
      {
        for(int i = 1; i < 10; i++)
        {
          numbers1[i] = i;
        }
      }else
      {
        return 0;
      }
    }
  }

  return 1; //If it makes it to the end of the funciton, the solution is valid
}

int isValid(int input_board[9][9], int value, int row, int column)
{
  int temp_array[9];
  int vert_square_start = 3 * (row / 3);
  int horiz_square_start = 3 * (column / 3);
  int counter = 0;
  for(int i = vert_square_start; i < vert_square_start + 3; i++)
  {
    for(int j = horiz_square_start; j < horiz_square_start + 3; j++)
    {
      if(input_board[i][j] == value)
      {
        return 0;
      }
    }
  }

  for(int i = 0; i < 9; i++)
  {
      if(input_board[row][i] == value)
      {
        return 0;
      }
      if(input_board[i][column] == value)
      {
        return 0;
      }
  }
  return 1;
}

int solvePuzzle(int input_board[9][9], int row, int column)
{
  if(row < 9 && column < 9)
  {
    if(input_board[row][column] != 0)
    {
      if((column + 1) < 9)
      {
        return solvePuzzle(input_board, row, column+1);
      }
      else if((row + 1) < 9)
      {
        return solvePuzzle(input_board, row+1, 0);
      }
      else
      {
        return 1;
      }
    }else
    {
      for(int i = 1; i < 10; i++)
      {
        if(isValid(input_board, i, row, column))
        {
          input_board[row][column] = i;
          if((column + 1) < 9)
          {
            if(solvePuzzle(input_board, row, column + 1))
            {
              return 1;
            }
            else 
            {
              input_board[row][column] = 0;
            }
          }else if((row + 1) < 9)
          {
            if(solvePuzzle(input_board, row + 1, 0))
            {
              return 1;
            }
            else
            {
              input_board[row][column] = 0;
            }
          }else
          {
            return 1;
          }
        }
      }
    }
    return 0;
  }else
  {
    return 1;
  }
}

int main(int argc, char ** argv)
{
  if(argc == 1)
  {
    printf("\nUsage: ./SudokuSolver <input file>\n\n");
    exit(1);
  }

  printf("\nReading input.txt...\n");
  printf("Initialising board...\n");
  initialiseBoard(argv[1]);
  printf("Checking input...\n");
  if(checkWin())
  {
    printf("\nValid solution entered!\n\n");
  }else
  {
    printf("\nInitial board:\n");
    printBoard(board);
    printf("\nSolving...\n");
    if(solvePuzzle(board, 0, 0))
    {
      printf("\nOutput:\n");
      printBoard(board);
      printf("\n");
    }else
    {
      printf("\nNo solution found!\n\n");
    }
  }

  return 0;
}
