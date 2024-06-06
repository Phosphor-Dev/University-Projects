class parse():
    def __init__(self):
        with open("input.txt", "r") as file:
            content = file.read()
               
        self.currentProgram = self.tokenize(content)
        self.currentToken = self.currentProgram[0]
        self.variables = {}
        
        self.output = open(r"outputs\output.txt", 'w')
        self.ssa = open(r"outputs\ssa.txt", 'w')

        self.computation()
        print(self.variables)
        self.output.close()
        self.ssa.close()

############################################################################################################################

    #computation = “main” [ varDecl ] { funcDecl } “{” statSequence “}” “.” .
    def computation(self):
        self.step()
        if self.currentToken == "var":
            self.varDecl()
        while self.currentToken != '{':
            self.funcDecl()
            self.step()
        self.step()
        self.statSequence()
        self.step()
        self.step()
        self.step()
        print("EOF Reached")

    #funcBody = [varDecl] “{” [statSequence] “}”.    
    def funcBody(self):
        if self.currentToken == "var":
            self.varDecl()
        self.step()
        if self.currentToken != "}":
            self.statSequence()
        self.step()
    
    #formalParam = “(“ [ident { “,” ident }] “)” .
    def formalParam(self):
        self.step()
        if self.currentToken != ")":
            self.ident()
            while self.currentToken != ';':
                self.step()
                self.ident()
        self.step()
    
    #funcDecl = [ “void” ] “function” ident formalParam “;” funcBody “;” .
    def funcDecl(self):
        if self.currentToken == "void":
            self.step()
        self.step()
        self.ident()
        self.formalParam()
        self.step()
        self.funcBody()
        self.step()
    
    #varDecl = “var” ident { “,” ident } “;” .
    def varDecl(self):
        self.step()
        self.variables[self.ident()] = '0'
        while self.currentToken != ';':
            self.step()
            self.variables[self.ident()] = '0'
        self.step()

    
############################################################################################################################    

    #statSequence = statement { “;” statement } [ “;” ]4 .
    def statSequence(self):
        self.statement()
        while self.currentToken == ';':
            self.step()
            if self.currentToken != '}':    
                self.statement()
    
    #statement = assignment | funcCall 3 | ifStatement | whileStatement | returnStatement.
    def statement(self):
        if self.currentToken == 'let':
            self.assignment()
        if self.currentToken == 'call':
            self.funcCall()
        if self.currentToken == 'if':
            self.ifStatement()
        if self.currentToken == 'while':
            self.whileStatement()
        if self.currentToken == 'return':
            self.returnStatement()

############################################################################################################################   
  
    #returnStatement = “return” [ expression ] .
    def returnStatement(self):
        self.ssa.write("returnStatement")

        self.step()
        if self.currentToken != "}":
            self.expression()

    #whileStatement = “while” relation “do” StatSequence “od”.
    def whileStatement(self):
        self.ssa.write("whileStatement Start")

        self.step()
        self.relation()
        self.step()
        self.statSequence()
        self.step()

        self.ssa.write("whileStatement End")

    #ifStatement = “if” relation “then” statSequence [ “else” statSequence ] “fi”.
    def ifStatement(self):
        self.ssa.write("if start" + "\n")
        self.step()
        self.relation()
        self.step()
        self.statSequence()
        self.ssa.write("if end" + "\n")
        if self.currentToken == 'else':
            self.ssa.write("else start" + "\n")
            self.step()
            self.statSequence()
            self.ssa.write("else end" + "\n")
        self.step()
    
    #funcCall = “call” ident [“(“ [expression { “,” expression } ] “)” ].
    def funcCall(self):     
        self.step()
        funcName = self.ident()
        if self.currentToken == '(':
            self.step()
            params = []
            if self.currentToken != ")":
                params.append(self.expression())
                while self.currentToken == ',':
                    self.step()
                    params.append(self.expression())
                self.step()
            else:
                self.step()
 
        if funcName == "OutputNum":
            self.output.write(params[0])
            self.ssa.write("write " + str(params[0]) + "\n")
        if funcName == "OutputNewLine":
            self.output.write('\n')
            self.ssa.write("writeNL" + "\n")
        if funcName == "InputNum":
            self.ssa.write("read" + "\n")
            return input()

    #assignment = “let” ident “<-” expression.
    def assignment(self):
        self.step()
        var = self.ident()
        self.step()
        value = self.expression()
        self.variables[var] = value
        #self.ssa.write("assignment " + var + " " + str(value))
    
############################################################################################################################   
      
    #relation = expression relOp expression .
    def relation(self):        
        term1 = self.expression()
        relOp = self.currentToken
        self.step()
        term2 = self.expression()

        if relOp == '==':
            self.ssa.write("beq " + str(term1) + " " + str(term2) + "\n")
            return term1 == term2
        if relOp == '!=':
            self.ssa.write("bne " + str(term1) + " " + str(term2) + "\n")
            return term1 != term2
        if relOp == '<':
            self.ssa.write("blt " + str(term1) + " " + str(term2) + "\n")
            return term1 < term2
        if relOp == '<=':
            self.ssa.write("ble " + str(term1) + " " + str(term2) + "\n")
            return term1 <= term2
        if relOp == '>':
            self.ssa.write("bgt " + str(term1) + " " + str(term2) + "\n")
            return term1 > term2
        if relOp == '>=':
            self.ssa.write("bge " + str(term1) + " " + str(term2) + "\n")
            return term1 >= term2

    #expression = term {(“+” | “-”) term}.
    def expression(self):
        term1 = int(self.term())
        while self.currentToken in ('+', '-'):
            if self.currentToken == '+':
                self.step()
                term2 = int(self.term())
                term1 += term2
                self.ssa.write("add " + str(term1) + " " + str(term2) + "\n")
            if self.currentToken == '-':
                self.step()
                term2 = int(self.term())
                term1 -= term2
                self.ssa.write("sub " + str(term1) + " " + str(term2) + "\n")
        return str(int(term1))
    
    #term = factor { (“*” | “/”) factor}.
    def term(self):
        term1 = int(self.factor())
        while self.currentToken in ('*', '/'):
            if self.currentToken == '*':
                self.step()
                term2 = int(self.factor())
                term1 *= term2
                self.ssa.write("mul " + str(term1) + " " + str(term2) + "\n")
            if self.currentToken == '/':
                self.step()
                term2 = int(self.factor())
                term1 /= term2
                self.ssa.write("div " + str(term1) + " " + str(term2) + "\n")
        return str(int(term1))
    
    #factor = ident | number | “(“ expression “)” | funcCall 1 .
    def factor(self):  
        if self.currentToken in self.variables:
            result = self.variables[self.ident()]
        elif self.currentToken == '(':
            self.step()
            result = self.expression()
            self.step()
        elif self.currentToken == 'call':
            result = self.funcCall()
        else:
            result = self.number()
        return result
    
############################################################################################################################

    #number = digit {digit}.
    def number(self):   
        result = self.currentToken
        self.step()
        return result
    
    #ident = letter {letter | digit}.
    def ident(self):
        result = self.currentToken
        self.step()
        return result
       
    #relOp = “==“ | “!=“ | “<“ | “<=“ | “>“ | “>=“.
    def relOp(self):
        print("relOp")
        result = self.currentToken
        self.step()
        return result

############################################################################################################################
   
    def step(self):
        self.currentProgram = self.currentProgram[1:]
        if len(self.currentProgram) > 0:
            self.currentToken = self.currentProgram[0]
        else:
            self.currentToken = None

    def tokenize(self, program):
        tokenList = []
        for i in range(len(program)):
            if (program[i].isnumeric() or program[i].isalpha()) and (i > 0) and (program[i] not in "<>+-!=") and ((tokenList[-1].isnumeric() or tokenList[-1].isalpha()) or tokenList[-1][-1] == ';'):
                tokenList[-1] += program[i]
            elif program[i] in '-=' and tokenList[-1] in '<>!=':
                tokenList[-1] += program[i]           
            else:
                tokenList.append(program[i])
        while ' ' in tokenList:
            tokenList.remove(' ')
        while '\n' in tokenList:
            tokenList.remove('\n')
        return tokenList

parse()