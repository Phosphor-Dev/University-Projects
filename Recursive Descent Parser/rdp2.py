class Parse():
    def __init__(self, text):
        letters = "abcdefghijklmnopqrstuvwxyz"
        digits = "0123456789"
        symbols = "<-"
        keywords = ["computation", "var"]
        identifiers = letters + digits
        
        variables = {}
        
        currentProgram = []
        currentToken = None

        programs = tokenize(text.split('.')[:-1])
        solve(programs)

    def tokenize(self, programs):
        programList = []        
        for program in programs:
            tokenList = []
            for i in range(len(program)):
                if (program[i].isnumeric() or program[i].isalpha()) and (i > 0) and (program[i] not in symbols) and ((tokenList[-1].isnumeric() or tokenList[-1].isalpha()) or tokenList[-1][-1] == ';'):
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
        currentProgram = currentProgram[1:]
        if len(currentProgram) > 0:
            currentToken = currentProgram[0]
        else:
            currentToken = None

    def replace(self):
        for i in range(len(currentProgram)):
            if currentProgram[i] in variables:
                currentProgram[i] = str(int(variables[currentProgram[i]]))
                currentToken = currentProgram[0]

    def solve(self, programList):
        for program in programList:
            currentProgram = program
            currentToken = program[0]
            comps()

    def comps(self):
        if currentToken == "computation":
            step()
            while "var" in currentProgram:
                if currentToken == "var":
                    step()
                    name = currentToken
                    step()
                    step()
                    value = exprs()
                    variables[name] = value
                    step()
                    replace()
            print(exprs())
            while ';' in currentProgram:
                step()
                print(exprs())
        else:
            print(exprs())
                 
    def exprs(self):
        result = terms()
        while currentToken in ('+', '-'):
            if currentToken == '+':
                step()
                result += terms()
            if currentToken == '-':
                step()
                result -= terms()
        return result    

    def terms(self):
        result = factors()
        while currentToken in ('*', '/'):
            if currentToken == '*':
                step()
                result *= terms()
            if currentToken == '/':
                step()
                result /= terms()
        return result

    def factors(self):
        result = None
        if currentToken.isnumeric():
            result = int(currentToken)
            step()
        elif currentToken == '(':
            step()
            result = exprs()
            step()
        return result

#Parse("computation var i <- 2 * 3; i - 5 - 1 .")
#Parse("computation var i <- 2 * 3; var abracadabra <- 7; (((abracadabra * i))); i - 5 - 1 .")
#Parse("computation var i <- 2 * 3; var abracadabra <- 7; (((abracadabra * i))); i - 5 - 1 . computation 1+ 1. ")
#Parse("computation 1+ 1. ")
#Parse("computation 1 +2 *(3+(2-1)+2).2 * 6 .")

#Parse("computation 1 + 1.")
Parse("computation 1 + 1 - 1.")
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