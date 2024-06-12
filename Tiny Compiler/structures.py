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
        #print("DEALLOC CALLED", self.regs)


class SymTable():
    def __init__(self):
        self.regs = {}
        self.id = 0

    def lookup(self, name):
        return self.regs[name]
    
    def add(self, name):
        self.regs[name] = self.id
        self.id += 1

class DomTree():
    def __init__(self):
        
        pass

"""reg = RegStack()
print(reg.allocTable)
print(reg.regs)
print('')

reg.alloc()
print(reg.allocTable)
print(reg.regs)
print('')

reg.alloc()
print(reg.allocTable)
print(reg.regs)
print('')

reg.dealloc(1)
print(reg.allocTable)
print(reg.regs)
print('')

reg.alloc()
print(reg.allocTable)
print(reg.regs)
print('')

reg.dealloc(2)
print(reg.allocTable)
print(reg.regs)
print('')"""