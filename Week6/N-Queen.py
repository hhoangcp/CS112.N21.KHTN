cheochinh = cheophu = cot = x = ans = []
n = 0

def Backtracking(pos):
    # Kiem tra da du n quan hau hay chua
    if pos >= n:
        # Luu ket qua
        one = []
        for i in range(n):
            s = ""
            for j in range(n):
                if j != x[i]:
                    s += '.'
                else:
                    s += 'Q'
            
            one.append(s)
        
        ans.append(one)
        return
    
    for i in range(n):
        # Kiem tra xem quan hau thu pos + 1 co the dat tai o (pos, i) hay khong. Neu thoa, thu dat roi tiep tuc voi quan hau pos + 2
        if not cot[i] and not cheochinh[i - pos + n - 1] and not cheophu[i + pos]: 
            cot[i] = cheochinh[i - pos + n - 1] = cheophu[i + pos] = True
            x[pos] = i
            Backtracking(pos + 1)
            cot[i] = cheochinh[i - pos + n - 1] = cheophu[i + pos] = False
            x[pos] = -1
    

if __name__ == '__main__':     
    n = int(input('n = '))
    
    cheochinh = [False for i in range(2 * n - 1)]
    cheophu = [False for i in range(2 * n - 1)]
    cot = [False for i in range(n)]
    x = [-1 for i in range(n)]
    
    # Ban co (0, 0) -> (n - 1, n - 1)
    Backtracking(0)
    
    # Xuat theo format output de bai
    print('[', end = '')
    for i in range(len(ans)):
        print('[', end = '')
        for j in range(len(ans[i])):
            print('"' + ans[i][j] + '"', end = '')
            if j < len(ans[i]) - 1:
                print(',', end = '')
        
        print(']', end = '')
        if i < len(ans) - 1:
            print(',', end = '')
    print(']')    
