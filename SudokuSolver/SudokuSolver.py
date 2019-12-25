import sys


def print_board(board):
    '''Prints the board'''
    b = board
    for i in range(9):
        if i % 3 == 0:
            print("+-------+-------+-------+")
        print(f"| {b[i][0]} {b[i][1]} {b[i][2]} | {b[i][3]} {b[i][4]} {b[i][5]} | {b[i][6]} {b[i][7]} {b[i][8]} |")
    print("+-------+-------+-------+")


def check_win(board):
    '''Checks if a given board is a valid solution'''
    row_nums = [x for x in range(1, 10)]
    column_nums = [x for x in range(1, 10)]

    # Checks rows and columns
    for i in range(9):
        for j in range(9):
            if board[i][j] in row_nums:
                row_nums.remove(board[i][j])
            else:
                return False

            if board[j][i] in column_nums:
                column_nums.remove(board[j][i])
            else:
                return False
        row_nums = [x for x in range(1, 10)]
        column_nums = [x for x in range(1, 10)]

    # Checks big squares
    for i in range(9):
        square_nums = [x for x in range(1, 10)]
        for j in range(3):
            for k in range(3):
                value = board[((i // 3) * 3) + j][((i % 3) * 3) + k]
                if value in square_nums:
                    square_nums.remove(value)
                else:
                    return False
        
    return True


def is_move_valid(board, value, row, column):
    '''Check if the attempted move is valid'''
    # Checks row and column
    if value in [board[row][i] for i in range(9)]:
        return False
    if value in [board[i][column] for i in range(9)]:
        return False
    
    # Checks big square
    for i in range((row // 3) * 3, ((row // 3) * 3) + 3):
        for j in range((column // 3) * 3, ((column // 3) * 3) + 3):
            if value == board[i][j]:
                return False

    return True


def solve_puzzle(board, row, column):
    '''Recursive function to solve the sudoku'''
    # Space already filled, move on to next space
    if board[row][column] != 0:
        if column + 1 < 9:
            return solve_puzzle(board, row, column + 1)
        elif row + 1 < 9:
            return solve_puzzle(board, row + 1, 0)
        else:
            return True
    # Try each valid value and recurse into the next space
    else:
        for value in range(1, 10):
            if is_move_valid(board, value, row, column):
                board[row][column] = value
                if column + 1 < 9:
                    if solve_puzzle(board, row, column + 1):
                        return True
                    else:
                        board[row][column] = 0
                elif row + 1 < 9:
                    if solve_puzzle(board, row + 1, 0):
                        return True
                    else:
                        board[row][column] = 0
                else:
                    return True
    
    # Combination didn't work, start backtracking
    return False    
        

def main():
    if len(sys.argv) != 2:
        print("Invalid Arguments!\nUsage: ./SudokuSolver.py [input_file]")
        sys.exit(1)

    INFILE = sys.argv[1]
    try:
        with open(INFILE, "r") as fp:
            raw_in = fp.read()
            raw_in = raw_in.rstrip()

            # Check input file length
            if len(raw_in) != 89:
                print("Invalid board!")
                sys.exit(1)
            
            board = [[int(num) for num in row] for row in raw_in.split("\n")]
            print("Loaded Board:")
            print_board(board)

            # Incomplete puzzle, solve it!
            if "0" in raw_in:
                print("\nPuzzle incomplete!\nSolving...")
                
                if solve_puzzle(board, 0, 0):
                    print("\nSolution found:")
                    print_board(board)
                else:
                    print("\nNo solution found!")
            # Completed puzzle, is it right?
            else:
                if check_win(board):
                    print("\nInput is already completed and solution is valid!")
                else:
                    print("\nInput is already completed and solution is not valid!")

    except IOError:
        print("Error opening input file!")
        sys.exit(1)

if __name__ == "__main__":
    main()