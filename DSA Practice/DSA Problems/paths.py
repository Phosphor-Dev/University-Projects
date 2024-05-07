import re
def makeGrid(size):
        grid = []
        tempArr = []
        vert = 1
        horiz = 0 
        for i in range(size):
            for j in range(size):
                if j == horiz and i == vert:
                     tempArr.append(1)
                     vert += 1
                     horiz += 1
                else:
                    tempArr.append(0)
            grid.append(tempArr)
            tempArr = []
        return grid

class Paths(object):
    def eval(self, list2):
        size = int(list2) + 1
        grid = makeGrid(size)
        m = size
        n = size
        dp=[[0] * (n+1) for _ in range(m+1)]
        dp[0][1]=1           
        for row in range(1, m+1):
            for col in range(1, n+1):
                if not grid[row-1][col-1]:
                    dp[row][col] = dp[row-1][col] + dp[row][col-1]
        print ("NUMBER OF PATHS:", dp[-1][-1] % 2022)
        return dp[-1][-1] % 2022

if __name__ == '__main__':
    calc = Paths()
    calc.eval('3')
    calc.eval('4')
    calc.eval('8')
    calc.eval('15')
