Next = []
moves = []
pos = -1

### If there is a solution, the number of steps is exactly 13. 
### -> Find a solution.

def Init():
    global Next
    Next = [[] for i in range(15)]
    
    ## Horizontal move
    for i in range(3, 6):
        start = i * (i - 1) // 2
        end = i * (i + 1) // 2
        for j in range(start, end):
            if j + 2 < end:
                Next[j].append(j + 2)
                Next[j + 2].append(j)

    ## Cross move
    for i in range(1, 4):
        start = i * (i - 1) // 2
        end = i * (i + 1) // 2
        for j in range(start, end):
            Next[j].append(j + i * 2 + 1)
            Next[j + i * 2 + 1].append(j)
            Next[j].append(j + i * 2 + 3)
            Next[j + i * 2 + 3].append(j)

## mask[i] = 0 if hole i is empty, 1 if hole i is occupied
def Backtracking(mask):
    if len(moves) == 13:
        return True
    
    for s in range(15):
        if (mask & (1 << s)) > 0: ## Check if hole s is occupied
            for t in Next[s]:
                if (mask & (1 << t)) == 0 and (mask & (1 << ((s + t) >> 1))) > 0: ## Check if hole t is empty and immediate hole is occupied
                    new_mask = mask ^ (1 << s) ^ (1 << t) ^ (1 << ((s + t) >> 1))
                    
                    moves.append((s, t))
                    if (Backtracking(new_mask)):
                        return True
                    moves.pop()
    
    return False

if __name__ == "__main__":
    print('Board:')
    print('        0     ')
    print('      1  2    ')
    print('    3  4  5   ')
    print('  6  7  8  9  ')
    print('10 11 12 13 14')
    pos = int(input('Enter location of the empty hole: '))
    
    mask = (1 << 15) - 1
    mask ^= (1 << pos) ## Hole pos is empty
    
    Init()
    if Backtracking(mask):
        print('Number of moves:', 13)
        for i in range(13):
            print(i + 1, '.', moves[i][0], '->', moves[i][1])
    else:
        print('No solution')
