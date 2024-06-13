from tokens import *
from structures import *
from graphs import *

class Result():
    def __init__(self, kind, result):      
        self.kind = kind
        self.value = result
        self.address = result
        self.regNum = result
    
class Inst():
    def __init__(self, num,  op, arg1 = None, arg2 = None):      
        self.num = num
        self.op = op
        self.arg1 = arg1
        self.arg2 = arg2

        if arg1 != None and arg2 != None:
            self.text = num + op +" (" + str(arg1) + ")(" + str(arg2) + ")"
        if arg1 != None and arg2 == None:
            self.text = num + op +" (" + str(arg1) + ")"
        if arg1 == None and arg2 == None:
            self.text = num + op

class Tiny():
    def __init__(self):
        self.variables = {}
        self.regs = RegStack()
        self.CSEtree = CSETree()
        self.varTable = VarTable()
        
        self.program = getTokens()
        self.pc = self.program[0]
        self.sp = 0

        self.graph = Graph()
        self.instIndex = 1

        self.file = open(r"outputs\insts.txt", 'w')
        self.computation()
        self.file.close()

        self.CSEtree.print()
        self.varTable.print()
        print(self.variables)
        print(self.regs.regs)
        print(self.regs.allocTable)

    def step(self):
        self.program = self.program[1:]
        self.pc = self.program[0]

    def getInstIndex(self):
        instsList = self.instIndex
        self.instIndex += 1
        return str(instsList) + ":"

    def load(self, result):
        match result.kind:
            case 'const':
                #print("LOADING CONST: ", result.kind, result.value)
                result.regNum = self.regs.alloc()
                result.kind = 'reg'
            case 'var':
                #print("LOADING VAR: ", result.kind, result.value)
                result.regNum = self.regs.alloc()
                result.kind = 'reg'

    def compute(self, op, x, y):
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

            #print("X: ", x.kind, x.value, x.address, x.regNum)
            self.load(x)
            self.regs.regs[x.regNum] = data
            if y.kind == 'const':
                inst = Inst(self.getInstIndex(), op, str(x.regNum), str(y.regNum)) #PutF1 operator, x.regNum, x.regNum, y.regNum
                
                self.CSEtree.add(op, x.regNum, y.regNum)
                
                self.file.write(inst.text + "\n")
                self.doRegOp(op, x, y)
                
            else:
                data = "ERROR"
                match x.kind:
                    case 'var':
                        data = x.value
                    case 'reg':
                        data = x.address

                #print("Y: ", y.kind, y.value, y.address, y.regNum)
                self.load(y)
                self.regs.regs[x.regNum] = data
                inst = Inst(self.getInstIndex(), op, str(x.regNum), str(y.regNum)) #PutF1 operator, x.regNum, x.regNum, y.regNum
                
                self.CSEtree.add(op, x.regNum, y.regNum)
                
                self.file.write(inst.text + "\n")
                self.doRegOp(op, x, y)
                self.regs.dealloc(y.regNum)

    def doRegOp(self, op, x, y):
        match op:
            case "phi":
                pass
            case "add":
                x.value = x.value + y.value
            case "sub":
                x.value = x.value - y.value
            case "mul":
                x.value = x.value * y.value
            case "div":
                x.value = x.value / y.value
            case "bne":
                x.value = x.value != y.value
            case "beq":
                x.value = x.value == y.value
            case "ble":
                x.value = x.value <= y.value
            case "blt":
                x.value = x.value < y.value
            case "bge":
                x.value = x.value >= y.value
            case "bgt":
                x.value = x.value > y.value
            case "cmp":
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
        self.file.write("end\n")

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
                #print(params[0].value)
                inst = Inst(self.getInstIndex(), "write", str(params[0].value))
                self.file.write(inst.text + "\n")
            case "OutputNewLine":
                #print('\n')
                inst = Inst(self.getInstIndex(), "writeNL")
                self.file.write(inst.text + "\n")
            case "InputNum":
                result = Result('const', int(input()))
                self.load(result)
                inst = Inst(self.getInstIndex(), "read")
                self.file.write(inst.text + "\n")
                return result

    def assignment(self):
        self.file.write("assign\n")
        self.step()
        identifier = self.pc
        self.step()
        self.step()
        value = self.expression()
        self.variables[identifier] = value.value
        print(value.kind)
        if value.kind != 'const':
            self.varTable.update(identifier, value.regNum)

    def relation(self):
        x = self.expression()
        op = self.pc
        self.step()
        y = self.expression()

        match op:
            case '==':
                self.compute('beq', x, y)
            case '!=':
                self.compute('bne', x, y)
            case '<':
                self.compute('blt', x, y)
            case '<=':
                self.compute('ble', x, y)
            case '>':
                self.compute('bgt', x, y)
            case '>=':
                self.compute('bge', x, y)
        return x
    
    def expression(self):
        x = self.term()
        op = self.pc
        while self.pc in ('+', '-'):
            self.step()
            y = self.term()
            match op:
                case '+':
                    self.compute('add', x, y)
                case '-':
                    self.compute('sub', x, y)
        return x

    def term(self):
        x = self.factor()
        op = self.pc
        while self.pc in ('*', '/'):
            self.step()
            y = self.factor()
            match op:
                case '*':
                    self.compute('mul', x, y)
                case '/':
                    self.compute('div', x, y)
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