class Block():
    def __init__(self, num, join, instList):
        self.num = num
        self.join = join
        self.instList = instList

        self.name = "bb"
        self.line = self.makeBlock()
    
    def makeBlock(self):
        self.name = "bb" + str(self.num)
        attrStart = "[shape=record, label=" + '"' + "<b>"
        if self.join:
            attrStart +="join\\n"
        attrStart += "BB" + str(self.num) + " | "
        attr = self.instList
        attrEnd = '"' + "];"
        line = "\t" + self.name + ' ' + attrStart + attr + attrEnd
        return line

class Path():
    def __init__(self, b1, b2, conType = None):
        self.type = conType
        self.b1 = b1
        self.b2 = b2
        self.line = self.makePath()

    def makePath(self):
        line = ""
        if self.type == "dom":
            line = "\t" + self.b1 + ":b -> " + self.b2 + ':b [color=blue, style=dotted, label="dom"];'
        elif self.type == "branch":
            line = "\t" + self.b1 + ":s -> " + self.b2 + ':n [label="branch"];'
        elif self.type == "fall-through":
            line = "\t" + self.b1 + ":s -> " + self.b2 + ':n [label="fall-through"];'

        elif self.type == "loop":
            line = "\t" + self.b1 + ":e -> " + self.b2 + ':e [label="loop"];'
        elif self.type == "exit":
            line = "\t" + self.b1 + ":w -> " + self.b2 + ':n [label="exit"];'

        else:
            line = "\t" + self.b1 + ":s -> " + self.b2 + ":n;"
        return line

class irGen():
    def __init__(self):
        self.blocks = []
        self.paths = []
        
        ssa =  open(r"outputs\ssa.txt", "r")
        content = ssa.readlines()
        for index in range(len(content)):
            content[index] = content[index][:-1]#.split(" ")
        ssa.close()

        self.content = content
        file = open(r"outputs\graph.txt", 'w')
        file.write("digraph G {\n")
        self.generate()
        print(content)
        for block in self.blocks:
            file.write(block.line + "\n")
        for path in self.paths:
            file.write(path.line + "\n")
        file.write("}")
        file.close()
        """
        #IF ELSE CASE
        self.blocks.append(Block(0, False, '{}'))
        self.blocks.append(Block(1, False, '{}'))
        self.blocks.append(Block(2, False, '{}'))
        self.blocks.append(Block(3, True, '{}'))
        self.blocks.append(Block(4, False, '{}'))
        self.paths.append(Path(self.blocks[4].name, self.blocks[0].name))
        self.paths.append(Path(self.blocks[0].name, self.blocks[3].name, "dom"))
        self.paths.append(Path(self.blocks[0].name, self.blocks[1].name, "branch"))
        self.paths.append(Path(self.blocks[0].name, self.blocks[2].name, "fall-through"))
        self.paths.append(Path(self.blocks[1].name, self.blocks[3].name, "fall-through"))
        self.paths.append(Path(self.blocks[2].name, self.blocks[3].name, "branch"))*/

        #WHILE CASE
        self.blocks.append(Block(0, False, '{}'))
        self.blocks.append(Block(1, False, '{}'))
        self.blocks.append(Block(2, False, '{}'))
        self.blocks.append(Block(3, False, '{}'))
        self.paths.append(Path(self.blocks[0].name, self.blocks[1].name))
        self.paths.append(Path(self.blocks[1].name, self.blocks[2].name))
        self.paths.append(Path(self.blocks[2].name, self.blocks[1].name, "loop"))
        self.paths.append(Path(self.blocks[1].name, self.blocks[3].name, "exit"))
        """

    def generate(self):        
        instList = []
        for line in self.content:
            if line == "if start":
                self.makeInstStr(instList)
                self.blocks.append(Block(0, False, self.makeInstStr(instList)))
                instList = []

            else:
                instList.append(line)

    def makeInstStr(self, instList):
        inst = "{"
        for line in instList:
            inst += line + " | "
        inst = inst[:-3] + "}"
        return inst


irGen()