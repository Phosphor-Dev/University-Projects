import structures
from tokens import getTokens
class Result():
    def __init__(self, kind, result):      
        self.kind = kind
        self.value = result
        self.address = result
        self.regNum = result
        
class Graph():
    def __init__(self):
        pass

class Tiny():
    def __init__(self):
        self.symTable = structures.SymTable()
        self.variables = {}#structures.DomTree()
        self.regs = structures.RegStack()
        
        self.program = getTokens()
        self.pc = self.program[0]
        self.sp = 0

        self.file = open(r"outputs\graph.txt", 'w')
        self.computation()
        self.file.close()

        print(self.variables)
        #print(self.symTable.regs)
        print(self.regs.regs)
        print(self.regs.allocTable)
        #print(self.regs.kindTable)

    def step(self):
        self.program = self.program[1:]
        self.pc = self.program[0]
        #print(self.program)

    def load(self, result):
        match result.kind:
            case 'const':
                print("LOADING CONST: ", result.kind, result.value)
                result.regNum = self.regs.alloc()
                #self.file.write("ADDI " + str(result.regNum) + " " + "0 " + str(result.value) + "\n")
                #PutF1 ADDI result.regNum 0 result.value
                result.kind = 'reg'
            case 'var':
                print("LOADING VAR: ", result.kind, result.value)
                result.regNum = self.regs.alloc()
                #self.file.write("LDW (" + str(result.regNum) + ")(" + "BASE" + ")(" + str(result.address) + ")\n")
                #PutF1 LDW result.regNum BASEREG result.address
                result.kind = 'reg'

    def compute(self, op, x, y):
        print("##############################################################")
        print("COMPUTING WITH GIVEN KINDS: ", op, x.kind, y.kind)
        #print("STARTING COMPUTE X: ", x.value, x.address, x.regNum)
        #print("STARTING COMPUTE Y: ", y.value, y.address, y.regNum)
        if x.kind == 'const' and y.kind == 'const':
            print()
            self.doRegOp(op, x, y)
        else:
            data = "ERROR"
            match x.kind:
                case 'var':
                    data = x.value
                case 'reg':
                    data = x.address

            print("X: ", x.kind, x.value, x.address, x.regNum)
            self.load(x)
            self.regs.regs[x.regNum] = data
            
            
            print(self.regs.regs)
            if y.kind == 'const':
                self.file.write(op +"I (" + str(x.regNum) + ")(" + str(y.regNum) + ")\n")
                self.doRegOp(op, x, y)
                #PutF1 operator, x.regNum, x.regNum, y.regNum
            else:
                data = "ERROR"
                match x.kind:
                    case 'var':
                        data = x.value
                    case 'reg':
                        data = x.address

                print("Y: ", y.kind, y.value, y.address, y.regNum)
                self.load(y)
                self.regs.regs[x.regNum] = data

                self.file.write(op + " (" + str(x.regNum) + ")(" + str(y.regNum) + ")\n")
                #PutF1 operator, x.regNum, x.regNum, y.regNum
                self.doRegOp(op, x, y)
                self.regs.dealloc(y.regNum)
        print("##############################################################")

    def doRegOp(self, op, x, y):
        match op:
            case "PHI":
                pass
            case "ADD":
                x.value = x.value + y.value
            case "SUB":
                x.value = x.value - y.value
            case "MUL":
                x.value = x.value * y.value
            case "DIV":
                x.value = x.value / y.value
            ############
            case "BNE":
                x.value = x.value != y.value
            case "BEQ":
                x.value = x.value == y.value
            case "BLE":
                x.value = x.value <= y.value
            case "BLT":
                x.value = x.value < y.value
            case "BGE":
                x.value = x.value >= y.value
            case "BGT":
                x.value = x.value > y.value
            case "CMP":
                pass
        
    def computation(self):
        self.step()
        if self.pc == "var":
            self.varDecl()
        while self.pc != '{':
            self.funcDecl()
            self.step()
        self.step()
        self.statSequence()
        self.step()

    def funcBody(self):
        if self.pc == "var":
            self.varDecl()
        self.step()
        if self.pc != "}":
            self.statSequence()
        self.step()

    def formalParam(self):
        self.step()
        if self.pc != ")":
            self.ident()
            while self.pc != ';':
                self.step()
                self.ident()
        self.step()

    def funcDecl(self):
        if self.pc == "void":
            self.step()
        self.step()
        self.ident()
        self.formalParam()
        self.step()
        self.funcBody()
        self.step()

    def varDecl(self):
        self.step()
        self.variables[self.ident()] = 0
        while self.pc != ';':
            self.step()
            self.variables[self.ident()] = 0
        self.step()

    def statSequence(self):
        self.statement()
        while self.pc == ';':
            self.step()
            if self.pc != '}':    
                self.statement()

    def statement(self):
        match self.pc:
            case 'let':
                self.assignment()
            case 'call':
                self.funcCall()
            case 'if':
                self.ifStatement()
            case 'while':
                self.whileStatement()
            case'return':
                self.returnStatement()

    def returnStatement(self):
        self.step()
        if self.pc != "}":
            self.expression()

    def whileStatement(self):
        self.file.write('while\n')
        self.step()
        self.relation()
        self.step()
        self.statSequence()
        self.step()
        self.file.write('elihw\n')

    def ifStatement(self):
        self.file.write('if\n')
        self.step()
        self.relation()
        self.step()
        self.statSequence()
        self.file.write('fi\n')
        if self.pc == 'else':
            self.file.write('else\n')
            self.step()
            self.statSequence()
            self.file.write('esle\n')
        self.step()

    def funcCall(self):     
        self.step()
        funcName = self.pc
        self.step()
        if self.pc == '(':
            self.step()
            params = []
            if self.pc != ")":
                params.append(self.expression())
                while self.pc == ',':
                    self.step()
                    params.append(self.expression())
                self.step()
            else:
                self.step()

        match funcName:
            case "OutputNum":
                print(params[0].value)
                self.file.write("write (" + str(params[0].value) + ")\n")
            case "OutputNewLine":
                print('\n')
                self.file.write("writeNL\n")
            case "InputNum":
                result = Result('const', int(input()))
                self.file.write("read\n")
                return result

    def assignment(self):
        self.step()
        identifier = self.pc
        self.step()
        self.step()
        value = self.expression()
        self.variables[identifier] = value.value

    def relation(self):
        x = self.expression()
        op = self.pc
        self.step()
        y = self.expression()

        match op:
            case '==':
                self.compute('BEQ', x, y)
            case '!=':
                self.compute('BNE', x, y)
            case '<':
                self.compute('BLT', x, y)
            case '<=':
                self.compute('BLE', x, y)
            case '>':
                self.compute('BGT', x, y)
            case '>=':
                self.compute('BGE', x, y)
        return x
    
    def expression(self):
        x = self.term()
        op = self.pc
        while self.pc in ('+', '-'):
            self.step()
            y = self.term()
            match op:
                case '+':
                    self.compute('ADD', x, y)
                case '-':
                    self.compute('SUB', x, y)
        return x

    def term(self):
        x = self.factor()
        op = self.pc
        while self.pc in ('*', '/'):
            self.step()
            y = self.factor()
            match op:
                case '*':
                    self.compute('MUL', x, y)
                case '/':
                    self.compute('DIV', x, y)
        return x
    
    def factor(self):
        if self.pc in self.variables:
            result = Result('var', int(self.variables[self.ident()]))
            return result
        elif self.pc == '(':
            self.step()
            result = self.expression()
            self.step()
            return result
        elif self.pc == 'call':
            result = self.funcCall()
            return result
        else:
            result = Result('const', int(self.pc))
            self.step()
            return result

    def ident(self):
        result = self.pc
        self.step()
        return result

Tiny()