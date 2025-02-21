def read_file(filename="test_puzzle.txt"):
    words = []
    board = []
    with open(filename) as f:
        for line in f:
            b = line.strip()
            if b.isdigit():
                board.append(str(b))
            else:
                words.append(b)
            for i in range(len(words)):
                if words[i] == '':
                    words.pop(i)    
                else:
                    continue
    return words,board
#[['GTU', 'TECH'], ['111', '010', '010', '010']]
#[['111', '010', '01', '010']]

def check_consistency(board):
    c = True
    a = len(board[0])
    for i in range(len(board)):
        if a == len(board[i]):
            c = True
        else:
            c = False
            break
    return c

def create_board(board):
    for i in range(len(board)):
        board[i] = [int(cell) for cell in board[i]]
#https://stackoverflow.com/questions/2499966/python-a-smarter-way-of-string-to-integer-conversion/2500023#2500023
"""words,board = read_file('test_puzzle.txt')
create_board(board)
print(board)"""
 
def identifier(words):
    result = [False] * len(words)
    return result

def print_board(board):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == 1:
                print(' ', end=' ')
            elif board[i][j] == 0:
                print('+', end=' ')
        print()

def print_board_w_c(board):
    row = [' ']
    column = []
    for j in range(1, len(board[0]) + 1):
        column.append('C' + f"{j}")
    print('   ' + ' '.join(column))
    for i, row_values in enumerate(board, start=1):
        print('R' + f"{i}", end=' ')
        for value in row_values:
            if value == 1:
            
                print(' ', end='  ')
            elif type(value) == str:
                print(value, end='  ')
            else:
                print('+', end='  ')
        print()

"""words,board=read_file("sample_puzzle.txt") #Deneyler
print(check_consistency(board))
create_board(board)
print(board)
print_board(board)
print_board_w_c(board)"""

def print_wordlist(words,wstatus):
    print('Word List    Status')
    for i in range(0,len(words)):
        if wstatus[i]:
            print('W' + f"{i+1} " + words[i]+'        USED')
        elif wstatus[i] == False:
            print('W' + f"{i+1} " +words[i]+ '      ' + 'NOT USED')    
# Sıralamada birazcık kayma var ama bakacağız
def check_entries(coordinates, wordno, board, words):
    if coordinates != None:
        a = coordinates[0]
        b = coordinates[1]
        c = True
        d = False
        if a > len(board[a-1] or b > len(board)):
            c = False
        if len(words) >= wordno > 0:
            d = True
        return c,d
    else:
        return False,False

def check_location(board, words, coordinates, wordno, direction='H'):
    if wordno is None or not (1 <= wordno <= len(words)):
        return False, 1

    a, b = coordinates[0], coordinates[1]
    if board[a - 1][b - 1] == 0:
        return False, 1
    if direction == 'V' and a > 1 and(board[a - 2][b - 1] == 0):
        return False, 2
    if direction == 'H' and b > 1 and board[a - 1][b - 2] == 0:
        return False, 3
    if direction == 'H' and (b - 1) + len(words[wordno - 1]) > len(board[0]):
        return False, 4
    elif direction == 'V' and (a - 1) + len(words[wordno - 1]) > len(board):
        return False, 7
    if direction == 'H' and any(cell == 0 for cell in board[a - 1][b - 1:b + len(words[wordno - 1])]):
        return False, 5
    elif direction == 'V' and any(board[i - 1][a] == 0  for i in range(1,len(board))):
        return False,8
    if direction == 'H' and b + len(words[wordno - 1]) < len(board[0]) and board[a - 1][b + len(words[wordno - 1]) - 1] == 0:
        return False, 6
    elif direction == 'V' and a + len(words[wordno - 1]) < len(board) and board[a + len(words[wordno - 1]) - 1][b - 1] == 0:
        return False, 9

    return True, 0

def check_word_fits(board, words, coordinates, wordno, direction='H'):

    row, col = coordinates[0] - 1 , coordinates[1] - 1
    word = words[wordno - 1]
    
    if direction == 'H':
        for i, letter in enumerate(word):
            if col + i >= len(board[0]) or (board[row][col + i] != 1 and board[row][col + i] != letter):
                return False, 1
    elif direction == 'V':
        for i, letter in enumerate(word):
            if row + i >= len(board) or (board[row + i][col] != 1 and board[row + i][col] != letter):
                return False, 2
    return True, 0

def clear_board(board, wstatus):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if isinstance(board[i][j], str):
                board[i][j] = 1
    for i in range(len(wstatus)):
        wstatus[i] = False

def decompose_command(str1): #GOOOOOOOOOOOOOOL çok kötü bir kod oldu çok karışık
    a = list(str1)
    stack = []
    stack1 = []
    count = 0
    iflag = 0
    direction = 'H'
    wordno = None
    rowno = None
    columnno = None
    for i in range(len(a)):
        count += 1
        stack.append(a[i])
        if count % 2 == 0:
            stack1.append(''.join(stack))
            stack = []
    if len(stack1) != 4:
        iflag = -1
    for i in stack1:
        if 'w' in i or 'W' in i:
            wordno = (''.join(x for x in i if x.isdigit()))
            if wordno == '':
                wordno = None
            else:
                wordno = int(wordno)
        elif 'r' in i or 'R' in i:
            rowno = (''.join(x for x in i if x.isdigit()))
            if rowno == '':
                rowno = None
            else:
                rowno = int(rowno)
        elif 'c' in i or 'C' in i:
            columnno = (''.join(x for x in i if x.isdigit()))
            if columnno == '':
                columnno = None
            else:
                columnno = int(columnno)
        elif 'd' in i or 'D' in i:
            direction = ''.join(x for x in i if x == 'V')
            if direction == '':
                direction = 'H'
    if rowno == None or columnno == None or wordno == None:
        iflag = -1
    if iflag == -1:
        return -1,None,None,None
    else:
        return iflag, wordno, [rowno, columnno], direction 
    
def check_word_combination(board, words, wordno, coordinates, direction='H'):
    row, col = coordinates[0] - 1, coordinates[1] - 1
    existing_letters = []

    def get_existing_letters(position, length):
        letters = []
        for i in range(length):
            if position == 'up':
                letters.append(board[row - i][col])
            elif position == 'down':
                letters.append(board[row + i][col])
            elif position == 'left':
                letters.append(board[row][col - i])
            elif position == 'right':
                letters.append(board[row][col + i])
        return letters

    if direction == 'H':
        existing_letters.extend(get_existing_letters('left', col))
        existing_letters.extend(get_existing_letters('right', len(board[0]) - col - 1))
    elif direction == 'V':
        existing_letters.extend(get_existing_letters('up', row))
        existing_letters.extend(get_existing_letters('down', len(board) - row - 1))

    existing_letters = [str(letter) for letter in existing_letters if letter != 0]

    word = words[wordno - 1]

    for i, letter in enumerate(word):
        if direction == 'H':
            if col + i < len(board[0]) and board[row][col + i] != 1:
                existing_letters.append(str(board[row][col + i]))
        elif direction == 'V':
            if row + i < len(board) and board[row + i][col] != 1:
                existing_letters.append(str(board[row + i][col]))

    for existing_letter in existing_letters:
        for other_word in words:
            if other_word != word and existing_letter + word in other_word:
                return True

    return False

def word_it(board, words, wstatus, coordinates, wordno, direction):
    a, b = coordinates[0], coordinates[1]

    if direction == 'H' and b + len(words[wordno - 1]) <= len(board[0]) + 1:
        for i in range(len(words[wordno - 1])):
            board[a - 1][b - 1 + i] = words[wordno - 1][i]
    elif direction == 'V' and a + len(words[wordno - 1]) <= len(board) + 1:
        for i in range(len(words[wordno - 1])):
            board[a - 1 + i][b - 1] = words[wordno - 1][i]
    else:
        return False
    wstatus[wordno - 1] = True
    return True

def copy_board(board):
    return [[cell for cell in row] for row in board]

def track_move(mvn, trackboard, coordinates, wordno, direction, board, wstatus):
    move_info = (coordinates, wordno, direction, copy_board(board), wstatus.copy())
    trackboard.append(move_info)
    mvn += 1
    return mvn

def check_solved(board):
    for row in board:
        if 1 in row:
            return False 
    return True

def check_words_in_board(board, words):
    for row in board:
        word = ''.join(str(cell) for cell in row if cell != 0)
        if len(word) > 1 and word not in words:
            return False
    for col in range(len(board[0])):
        word = ''.join(str(board[row][col]) for row in range(len(board)) if board[row][col] != 0)
        if len(word) > 1 and word not in words:
            return False

def solve_board(board, words):
    if not check_consistency(board):
        return False
    wstatus = identifier(words)
    for wordno in range(1, len(words) + 1):
        placed = False
        for direction in ['H', 'V']:
            for i in range(len(board)):
                for j in range(len(board[0])):
                    coordinates = [i + 1, j + 1]
                    if check_entries(coordinates, wordno, board, words):
                        if check_location(board, words, coordinates, wordno, direction):
                            if check_word_fits(board,words,coordinates,wordno,direction) == (True,0):
                                    if word_it(board, words, wstatus, coordinates, wordno, direction):
                                        placed = True
                                        print(f"Placed word {wordno} at {coordinates} in direction {direction}")
                                        print(print_board_w_c(board))
                                        print(board)
                                        break
                if placed:
                    break
            if placed:
                break
        if not placed:
            return False
    return True

def word_puzzle(): #çoğunlukla çalışıyor ama hatalar olabilir
    while True:
        a = input("Enter the filename for the puzzle (or press Enter for default): ")
        if a == "":
            a = "sample_puzzle.txt"

        words, board = read_file(a)
        create_board(board)

        if not check_consistency(board):
            print(f"The puzzle board of {a} is not consistent!")

            retry = input("Do you want to try a new file? (y: yes, n: no): ").lower()
            if retry != 'y':
                print("Exiting the game. Goodbye!")
                break
        else:
            break

    wstatus = [False] * len(words)

    print("Game starts")

    while True:
        print("\nWord List Status")
        print_wordlist(words, wstatus)
        print("\nCurrent Board:")
        print_board_w_c(board)

        move = input("\nPlease choose a word from the word list,\n"
                     "choose a row and a column, and\n"
                     "direction of the word, V: Vertical H:Horizontal\n"
                     "Enter your move as in the format: (WXRYCZDT)\n"
                     "Other options:\n"
                     "cb - clear board\n"
                     "q - quit game\n"
                     "s - solve puzzle\n"
                     "Enter your move: ")

        if move == 'cb':
            clear_board(board, wstatus)
            print("Board cleared. Please make a new move.")
            print(board)
            continue
        
        elif move == 'q':
            print("Exiting the game.")
            break
        
        elif move == 's':
            if solve_board(board, words):
                print("PUZZLE SOLVED")
                print_wordlist(words, wstatus)
            else:
                print("Unable to solve the puzzle. Continue making moves.")
            continue
        iflag, wordno, coordinates, direction = decompose_command(move)
        if iflag == -1:
            print("\nInvalid move. Please re-enter the move.")
            continue
        if not check_entries(coordinates, wordno, board, words) or \
           not check_location(board, words, coordinates, wordno, direction) or \
           not check_word_fits(board, words, coordinates, wordno, direction):
            print("Invalid move. Please re-enter the move.")
            continue
        if not word_it(board, words, wstatus, coordinates, wordno, direction):
            print("Error while making the move. Please re-enter the move.")
            continue
        print("Move successful Updated board:")
        print_board_w_c(board)
        if check_solved(board):
            print("PUZZLE SOLVED")
            print_wordlist(words, wstatus)

            again = input("Would you like to play again? (y: yes, n: no): ").lower()
            if again != 'y':
                print("Exiting the game.")
                break
            print("\nRestarting the game!")
            wstatus = [False] * len(words)



"""words, board = read_file("_puzzle.txt")
create_board(board)
print_board(board)
print(words)
print(board)
print_board_w_c(board)
wstatus=identifier(words)
print(wstatus)
print(board)
print_wordlist(words,wstatus)
cmd4='dVW2R1C2'
iflag,wordno,coordinates,direction=decompose_command(cmd4)
print(iflag,wordno,coordinates,direction)
print(check_entries(coordinates,wordno,board,words))
print(check_location(board,words,coordinates,wordno,direction),'----------------------------------')  #Check location yanlış ok False,7 ye girmemesi lazım ama onu bypass etse bile niyeyse false,9 a giriyor
#anladığım kadarıyla örneklerde oyun başlandığı gibi olduğu için bir şeyler mutate olduğu için öyle olıuyor çünkü en sonda doğru çalışıyor ve mantıkende doğru
print(check_word_fits(board, words, coordinates, wordno, direction),'*****************')
print(word_it(board,words,wstatus,coordinates,wordno,direction))
print(board)
print(print_board_w_c(board))
print(print_wordlist(words,wstatus))
moveno=0
trackmoves=[]
moveno=track_move(moveno,trackmoves,coordinates,wordno,direction,board,wstatus)
print(moveno)
print(trackmoves)
copyofboard=copy_board(board)
cmd5='W1R1C1Dh'
iflag,wordno,coordinates,direction=decompose_command(cmd5)
print(iflag,wordno,coordinates,direction)
print(word_it(board,words,wstatus,coordinates,wordno,direction))
print_board_w_c(board)
print_wordlist(words,wstatus)
moveno=track_move(moveno,trackmoves,coordinates,wordno,direction,board,wstatus)
print(moveno)
print(trackmoves)
print(check_solved(board))
print(solve_board(board,words))"""

