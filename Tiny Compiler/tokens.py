def getTokens():
    with open(r"inputs\input.txt", "r") as file:
        program = file.read()  
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