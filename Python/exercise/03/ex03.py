ANSWER_COUNT = 0
MAXNUM = 8 # row of board

def print_chess(chess): # print result
    print('answer No: {}:'.format(ANSWER_COUNT))
    for i in range(MAXNUM):
        for j in range(MAXNUM):
            print(chess[i][j],' ',end='')
        print('\n')
    print("more?")
    

"""
Check whether the current coordinates can place the queen

Just check the upper side of the current coordinates, 
whether there is a queen on the diagonally or upper side, if there is, it cannot be placed the queen
"""
def check(x, y, chess): # check position (x,y)
    for i in range(x):
        # check upper side
        if(chess[i][y]== 'Q'):
            return False    

        # check diagonally side
        if(y-1-i >= 0):
            if(chess[x-1-i][y-1-i] == 'Q'):
                return False

        if(y+1+i < MAXNUM):
            if(chess[x-1-i][y+1+i] == 'Q'):
                return False
    return True

def solve(x, chess):  # bracktrack on x row
    global ANSWER_COUNT,MAXNUM

    if(x == MAXNUM): # x is equal to the border of the board, which means last row has been placed, then print the result
        ANSWER_COUNT = ANSWER_COUNT + 1
        print_chess(chess)
        enter = input() # wait user's enter
        return

    for i in range(MAXNUM): # Traverse each column of the row x
        if(check(x,i,chess)): # Determine whether the queen can be placed at the current point
            chess[x][i] = 'Q' # Try to place queen

            solve(x+1,chess) # backtrack to next row
            
            chess[x][i] = '.' # trackbrack

def main():
    print("solve()")
    chess = [['.' for col in range(MAXNUM)] for row in range(MAXNUM)]   # init board
    solve(0, chess)

if __name__ == '__main__':
    main()