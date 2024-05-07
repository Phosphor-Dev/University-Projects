class Parse():
    def __init__(self, path):
        self.letters = "abcdefghijklmnopqrstuvwxyz"
        self.digits = "0123456789"
        self.relOp = ["==", "!=", "<", "<=", ">", ">="]

        self.symbols = "<>+-!="
        self.keywords = ["void", "var", "function", "do", "od", "if", "then", "else", "fi", "return", "call", "let"]
        self.functions = ["main",  "InputNum",  "OutputNum", "OutputNewLine"]
        self.identifiers = self.letters + self.digits

        self.path = path
        with open(path, "r") as file:
            content = file.read()

        self.currentProgram = self.tokenize(content)
        self.currentToken = self.currentProgram[0]
        self.variables = {}

        self.depth = 0

        self.computation()

############################################################################################################################ 
    def step(self, times=1):
        for i in range(times):
            self.currentProgram = self.currentProgram[1:]
            if len(self.currentProgram) > 0:
                self.currentToken = self.currentProgram[0]
            else:
                self.currentToken = None
        print([self.currentToken])

    def tokenize(self, program):
        tokenList = []
        for i in range(len(program)):
            if (program[i].isnumeric() or program[i].isalpha()) and (i > 0) and (program[i] not in self.symbols) and ((tokenList[-1].isnumeric() or tokenList[-1].isalpha()) or tokenList[-1][-1] == ';'):
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
    
############################################################################################################################   
    #computation = “main” [ varDecl ] { funcDecl } “{” statSequence “}” “.” .
    def computation(self):
        print("computation start: ", [self.currentToken])

        if self.currentToken == "main":
            print([self.currentToken])
            self.step()
        
        if self.currentToken == "var":
            self.varDecl()

        while self.currentToken != '{':
            self.funcDecl()
            self.step()

        if self.currentToken == "{":
            self.step()
            self.statSequence()
            self.step()
        print("BOOBIES", self.currentProgram)
        print("computation exit")
        return None

    #funcBody = [varDecl] “{” [statSequence] “}”.    
    def funcBody(self):
        print("funcBody start: ", [self.currentToken])
        
        print("funcBody exit")
        return None
    
    #formalParam = “(“ [ident { “,” ident }] “)” .
    def formalParam(self):
        print("formalParam start: ", [self.currentToken])
        
        print("formalParam exit")
        return None
    
    #funcDecl = [ “void” ] “function” ident formalParam “;” funcBody “;” .
    def funcDecl(self):
        print("funcDecl start: ", [self.currentToken])
        
        print("funcDecl exit")
        return None
    
    #varDecl = “var” ident { “,” ident } “;” .
    def varDecl(self):
        print("varDecl start: ", [self.currentToken])
        
        self.step()
        self.ident()
        while self.currentToken != ';':
            self.step()
            self.ident()
        self.step()
        print("varDecl exit")
        return None
    
############################################################################################################################    
    #statSequence = statement { “;” statement } [ “;” ]4 .
    def statSequence(self):
        self.depth += 1
        print((self.depth*"---- ") + "statSequence start: ", [self.currentToken])
        
        self.statement()
        while self.currentToken == ';':
            self.step()
            if self.currentToken != '}':    
                self.statement()
        

        print((self.depth*"---- ") + "statSequence exit")
        self.depth -= 1
        return None
    
    #statement = assignment | funcCall 3 | ifStatement | whileStatement | returnStatement.
    def statement(self):
        print("\nstatement start: ", [self.currentToken])
        
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

        print("statement exit\n")
        return None
    
############################################################################################################################     
    #returnStatement = “return” [ expression ] .
    def returnStatement(self):
        print("returnStatement start: ", [self.currentToken])

        print("returnStatement exit")
        return None
    
    #whileStatement = “while” relation “do” StatSequence “od”.
    def whileStatement(self):
        print("whileStatement start: ", [self.currentToken])
        
        self.step()
        self.relation()
        self.step()
        self.statSequence()
     
        if self.currentToken == 'od':
            self.step()

        print("whileStatement exit")
        return None
    
    #ifStatement = “if” relation “then” statSequence [ “else” statSequence ] “fi”.
    def ifStatement(self):
        print("ifStatement start: ", [self.currentToken])

        self.step()
        self.relation()
        self.step()
        self.statSequence()

        if self.currentToken == 'else':
            self.step()
            self.statSequence()
        
        if self.currentToken == 'fi':
            self.step()
        
        print("ifStatement exit")
        return None
    
    #funcCall = “call” ident [2 “(“ [expression { “,” expression } ] “)” ].
    def funcCall(self):
        print("funcCall start: ", [self.currentToken])
        
        self.step()
        self.ident()
        
        if self.currentToken == '(':
            self.step()
            if self.currentToken != ")":
                self.expression()
                while self.currentToken == ',':
                    self.step()
                    self.expression()
                self.step()
            else:
                self.step()
        
        print("funcCall exit")
        return None
    
    #assignment = “let” ident “<-” expression.
    def assignment(self):
        print("assignment start: ", [self.currentToken])
        
        self.step()
        self.ident()
        self.step()
        self.expression()

        print("assignment exit")
        return None
    
############################################################################################################################         
    #relation = expression relOp expression .
    def relation(self):
        print("relation start: ", [self.currentToken])
        
        self.expression()
        if self.currentToken in self.relOp:
            self.step()
        
        self.expression()

        print("relation exit")
        return None
   
    #expression = term {(“+” | “-”) term}.
    def expression(self):
        print("expression start: ", [self.currentToken])

        self.term()
        while self.currentToken in '+-':
            if self.currentToken == '+':
                self.step()
                self.term()
            if self.currentToken == '-':
                self.step()
                self.term()

        print("expression exit")
        return None
    
    #term = factor { (“*” | “/”) factor}.
    def term(self):
        print("term start: ", [self.currentToken])

        self.factor()
        while self.currentToken in '*/':
            if self.currentToken == '*':
                self.step()
                self.factor()
            if self.currentToken == '/':
                self.step()
                self.factor()
        print([self.currentToken])
        
        print("term exit")
        return None
    
    #factor = ident | number | “(“ expression “)” | funcCall 1 .
    def factor(self):
        print("factor start: ", [self.currentToken])
        
        if self.currentToken in self.variables:
            self.ident()
        elif self.currentToken == '(':
            self.step()
            self.expression()
            self.step()
        elif self.currentToken == 'call':
            self.funcCall()
        else:
            self.ident()

        print("factor exit")
        return None
    
############################################################################################################################     
    #number = digit {digit}.
    def number(self):
        #print("number start: ", [self.currentToken])
        
        self.step()

        #print("number exit")
        return None
    
    #ident = letter {letter | digit}.
    def ident(self):
        #print("ident start: ", [self.currentToken])

        self.step()

        #print("ident exit")
        return None
    
############################################################################################################################     
    #relOp = “==“ | “!=“ | “<“ | “<=“ | “>“ | “>=“.
    def relOp(self):
        return None
    
    #digit = “0” | “1” | ... | “9”.
    def digit(self):
        return None
    
    #letter = “a” | “b” | ... | “z”.
    def letter(self):
        return None

Parse("test.txt")