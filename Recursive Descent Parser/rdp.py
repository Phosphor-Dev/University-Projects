class Parse():
    def __init__(self, text):
        self.letters = "abcdefghijklmnopqrstuvwxyz"
        self.digits = "0123456789"
        self.symbols = "<-"
        self.keywords = ["computation", "var"]
        self.identifiers = self.letters + self.digits

        self.tokenList = []
        self.currentToken = None

        self.variables = {}
        
        compsList = text.replace(";", ".").split(".")[:-1]
        self.solve(compsList)

    def tokenize(self, line):
        tokenList = []
        for i in range(len(line)):
            if (line[i] in self.identifiers and i > 0) and (tokenList[-1][-1] in self.identifiers or tokenList[-1][-1] == '.'):
                tokenList[-1] += line[i]
            elif line[i] in self.symbols and i > 0 and tokenList[-1][-1] in self.symbols:
                tokenList[-1] += line[i]
            else:
                tokenList.append(line[i])
        while ' ' in tokenList:
            tokenList.remove(' ')
        #print(tokenList)
        return tokenList

    def solve(self, compsList):
        for comp in compsList:
            self.tokenList = self.tokenize(comp)
            print(self.tokenList)
            self.currentToken = self.tokenList[0]
            print(self.parseExprs())

    def step(self):
        self.tokenList = self.tokenList[1:]
        if len(self.tokenList) > 0:
            self.currentToken = self.tokenList[0]
        else:
            self.currentToken = None
    
    def parseExprs(self):
        result = self.parseTerms()
        while self.currentToken in ('+', '-'):
            if self.currentToken == '+':
                self.step()
                result += self.parseTerms()
            if self.currentToken == '-':
                self.step()
                result -= self.parseTerms()
        return result    

    def parseTerms(self):
        result = self.parseFactors()
        while self.currentToken in ('*', '/'):
            if self.currentToken == '*':
                self.step()
                result *= self.parseTerms()
            if self.currentToken == '/':
                self.step()
                result /= self.parseTerms()
        return result

    def parseFactors(self):
        result = None
        if self.currentToken.isnumeric():
            result = int(self.currentToken)
            self.step()
        elif self.currentToken == '(':
            self.step()
            result = self.parseExprs()
            self.step()
        return result

#Parse("1 +2 *(3+(4-1)+2).7 * 6 .")
Parse("1+1.")
Parse("1 +2 *(3+(2-1)+2).2 * 6 .")


#Tests
"""
1 +2 *(3+(4-1)+2).7 * 6 . 1 + 1 + 1 + 2.1+2*(3+4).7*86.1+(2+1).
"""

#Grammar
"""
digit = “0” | “1” | ... | “9”.
number = digit {digit}.

factor = number | “(“ expression “)” .
term = factor { (“*” | “/”) factor}.
expression = term {(“+” | “-”) term}.
computation = expression “.”
"""