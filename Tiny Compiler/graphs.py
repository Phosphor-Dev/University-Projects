import graphviz as gv
class Block():
    def __init__(self, num, instList):
        inst = "{"
        for line in instList:
            inst += line + " | "
        inst = inst[:-3] + "}"
        self.name = "bb" + str(num)
        self.label = "<b>BB" + str(num) + " | " + inst

class Graph():
    def __init__(self):
        self.graph = gv.Digraph()
        self.blockList = {}
        self.blockNum = 0

    def makeBlock(self, instList):
        if instList == []:
            instList = ["\\" + "<" + "empty" + "\\" + ">"]

        block = Block(self.blockNum, instList)
        self.graph.node(block.name, shape='record', label=block.label)
        self.blockList[block.name] = block
        self.blockNum += 1
        return block

    def makeEdge(self, edgeType, block1, block2):
        match edgeType:
            case 'dom':
                self.graph.edge(block1.name + ":b", block2.name + ':b', color="blue", style="dotted", label="dom")
            case 'branch':
                self.graph.edge(block1.name + ":s", block2.name + ':n', label="branch")
            case 'fall-through':
                self.graph.edge(block1.name + ":s", block2.name + ':n', label="fall-through")
            case 'loop':
                self.graph.edge(block1.name + ":e", block2.name + ':e', label="loop")
            case 'exit':
                self.graph.edge(block1.name + ":w", block2.name + ':n', label="exit")
            case 'default':
                self.graph.edge(block1.name, block2.name)

"""g = Graph()

head = g.makeBlock(["3:const #0"])
ifBlock = g.makeBlock(["1:add (1) (1)", "2:cmp (1) (3)", "3:bge (4) (10)"])
elseBlock = g.makeBlock(["1:add (1) (1)", "2:cmp (1) (3)", "3:bge (4) (10)"])
join = g.makeBlock(["1:add (1) (1)", "2:cmp (1) (3)", "3:bge (4) (10)"])

g.makeEdge("branch", head, ifBlock)
g.makeEdge("fall-through", head, elseBlock)
g.makeEdge("fall-through", ifBlock, join)
g.makeEdge("branch", elseBlock, join)

joinBlock = g.makeBlock([])
bodyBlock = g.makeBlock([])
exitBlock = g.makeBlock([])

g.makeEdge("branch", joinBlock, bodyBlock)
g.makeEdge("loop", bodyBlock, joinBlock)
g.makeEdge("exit", joinBlock, exitBlock)
print(g.graph.source)"""

