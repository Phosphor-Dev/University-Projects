class Parse():
    def __init__(self, text):
        self.letters = "abcdefghijklmnopqrstuvwxyz"
        self.digits = "0123456789"
        self.symbols = "<-"
        self.keywords = ["computation", "var"]
        self.identifiers = self.letters + self.digits
        
        self.variables = {}
        
        self.currentProgram = []
        self.currentToken = None

        self.programs = self.tokenize(text.split('.')[:-1])
        self.solve(self.programs)

    def tokenize(self, programs):
        programList = []        
        for program in programs:
            tokenList = []
            for i in range(len(program)):
                if (program[i].isnumeric() or program[i].isalpha()) and (i > 0) and (program[i] not in self.symbols) and ((tokenList[-1].isnumeric() or tokenList[-1].isalpha()) or tokenList[-1][-1] == ';'):
                    tokenList[-1] += program[i]
                elif program[i] == '-' and tokenList[-1] == '<':
                    tokenList[-1] += program[i]
                else:
                    tokenList.append(program[i])
            while " " in tokenList:
                tokenList.remove(' ')
            programList.append(tokenList)
        return programList
    
    def step(self):
        self.currentProgram = self.currentProgram[1:]
        if len(self.currentProgram) > 0:
            self.currentToken = self.currentProgram[0]
        else:
            self.currentToken = None

    def replace(self):
        for i in range(len(self.currentProgram)):
            if self.currentProgram[i] in self.variables:
                self.currentProgram[i] = str(int(self.variables[self.currentProgram[i]]))
                self.currentToken = self.currentProgram[0]

    def solve(self, programList):
        for program in programList:
            self.currentProgram = program
            self.currentToken = program[0]
            self.comps()

    def comps(self):
        if self.currentToken == "computation":
            self.step()
            while "var" in self.currentProgram:
                if self.currentToken == "var":
                    self.step()
                    name = self.currentToken
                    self.step()
                    self.step()
                    value = self.exprs()
                    self.variables[name] = value
                    self.step()
                    self.replace()
            print(self.exprs())
            while ';' in self.currentProgram:
                self.step()
                print(self.exprs())
        else:
            print(self.exprs())
                 
    def exprs(self):
        result = self.terms()
        while self.currentToken in ('+', '-'):
            if self.currentToken == '+':
                self.step()
                result += self.terms()
            if self.currentToken == '-':
                self.step()
                result -= self.terms()
        return result    

    def terms(self):
        result = self.factors()
        while self.currentToken in ('*', '/'):
            if self.currentToken == '*':
                self.step()
                result *= self.terms()
            if self.currentToken == '/':
                self.step()
                result /= self.terms()
        return result

    def factors(self):
        result = None
        if self.currentToken.isnumeric():
            result = int(self.currentToken)
            self.step()
        elif self.currentToken == '(':
            self.step()
            result = self.exprs()
            self.step()
        return result

#Parse("computation var i <- 2 * 3; i - 5 - 1 .")
#Parse("computation var i <- 2 * 3; var abracadabra <- 7; (((abracadabra * i))); i - 5 - 1 .")
#Parse("computation var i <- 2 * 3; var abracadabra <- 7; (((abracadabra * i))); i - 5 - 1 . computation 1+ 1. ")
#Parse("computation 1+ 1. ")
#Parse("computation 1 +2 *(3+(2-1)+2).2 * 6 .")

#Parse("computation 1 + 1.")
#Parse("computation 1 + 1 - 1 - 1.")
#Parse("computation (3+11)*3-3/3.")
#Parse("computation 3+11*3-3/3.")
#Parse("computation (3+11-(3+5))*3-3/3.")
#Parse("computation var hi <- 10; 1 + 1.")
#Parse("computation var x <- 10 * 2; var y <- (x + 5) / 3; var z <- (y - 1) * 2; z + x - 5.")
#Parse("computation var i <- 2 * 3; var abracadabra <- 7; (((abracadabra * i))); i - 5 - 1 .")


#Tests
"""
"1 + 1."
"1 + 1 - 1 - 1.'
"(3+11)*3-3/3."
"3+11*3-3/3."
"(3+11-(3+5))*3-3/3."
"computation var hi <- 10; 1 + 1."
"computation var x <- 10 * 2; var y <- (x + 5) / 3; var z <- (y - 1) * 2; z + x - 5."
"computation var i <- 2 * 3; var abracadabra <- 7; (((abracadabra * i))); i - 5 - 1 ."
"computation var i <- 2 *  3;    var  abracadabra <- 7; ( ( (abracadabra * i))); i - 5 - 1 . i + 1."
"""
#Grammar
"""
letter = “a” | “b” | ... | “z”.
digit = “0” | “1” | ... | “9”.
identifier = letter {letter | digit}.
number = digit {digit}.
factor = identifier | number | “(“ expression “)”.
term = factor { (“*” | “/”) factor}.
expression = term {(“+” | “-”) term}.
computation = “computation” { “var” identifier “<-” expression “;” } expression { “;” expression } “.”
"""