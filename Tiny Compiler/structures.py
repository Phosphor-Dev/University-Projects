class RegStack():
    def __init__(self):     
        self.allocTable = [True]
        self.regs = {0:0}
    
    def alloc(self):
        for regNum in range(len(self.allocTable)):
            if self.allocTable[regNum] == False:
                self.allocTable[regNum] = True
                return regNum
        if False not in self.allocTable:
            regNum = len(self.regs)
            self.regs[regNum] = 0
            self.allocTable.append(True)
            return regNum
            
    def dealloc(self, regNum):
        self.regs[regNum] = 0
        self.allocTable[regNum] = False

class CSETree():
    def __init__(self):
        self.addLL = Node()
        self.subLL = Node()
        self.mulLL = Node()
        self.divLL = Node()
    
    def add(self, op, reg1, reg2):
        match op:
            case 'add':
                self.addLL.insert(op, reg1, reg2)
            case 'sub':
                self.subLL.insert(op, reg1, reg2)
            case 'mul':
                self.mulLL.insert(op, reg1, reg2)
            case 'div':
                self.divLL.insert(op, reg1, reg2)

    def print(self):
        print("-----------------")
        self.addLL.printLL()
        print("-----------------")
        self.subLL.printLL()
        print("-----------------")
        self.mulLL.printLL()
        print("-----------------")
        self.divLL.printLL()
        print("-----------------")

class Node():
    def __init__(self, op = None, reg1 = None, reg2 = None):
        self.op = op
        self.reg1 = reg1
        self.reg2 = reg2
        self.next = None
        self.head = None
    
    def insert(self, op, reg1, reg2):
        newNode = Node(op, reg1, reg2)
        if self.head is None:
            self.head = newNode
            return
        else:
            newNode.next = self.head
            self.head = newNode
    
    def printLL(self):
        currentNode = self.head
        while(currentNode):
            print(currentNode.op, currentNode.reg1, currentNode.reg2)
            currentNode = currentNode.next

class VarTable():
    def __init__(self):
        self.table = {}
    
    def update(self, ident, reg):
        for k,v in list(self.table.items()):
            if ident in v:
                self.table[k].remove(ident)
                if len(self.table[k]) == 0:
                    del self.table[k]
        if reg in self.table:
            self.table[reg].append(ident)
        else:
            self.table[reg] = [ident]
        print(self.table)
    
    def print(self):
        print(self.table)

class SymTable():
    def __init__(self):
        self.map = {}

    def add(self, ident, value = 0):
        self.map[ident] = [len(self.map)+1, value]

    def getID(self, ident):
        return self.map[ident][0] if ident in self.map else False
    
    def getVal(self, ident):
        return self.map[ident][1] if ident in self.map else False
    
    def print(self):
        print(self.map)

"""symTable = SymTable()
symTable.add('a')
symTable.add('b')
symTable.add('c')
symTable.add('d')
symTable.print()

table = VarTable()
table.update('a', 1)
#table.update('b', 2)
#table.update('c', 3)
#table.update('d', 2)
#table.update('d', 3)

tree = CSETree()

#print("----------")
#tree.addLL.printLL()
#print("----------")
tree.addLL.insert("add", 1, 2)
#tree.addLL.printLL()
#print("----------")
tree.addLL.insert("add", 3, 4)
#tree.addLL.printLL()
tree.print()"""
