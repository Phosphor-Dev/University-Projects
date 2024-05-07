import re
class Zapping(object):   
    def eval(self, list2):
        tokens2 = list2.split()
        list3 = list(map(int, tokens2))
        maxCh = list3.pop(0)
        unique = [*set(list3)]
        distArr = []
        distSum = 0

        for index in range(len(unique)):
            for channel in list3:
                if (channel > unique[index]):
                    distSum += unique[index] + maxCh - channel
                else:
                    distSum += abs(channel - unique[index])
            distArr.append(distSum)
            distSum = 0

        if len(list3) <= 2:
            value = "ERROR"
            return value
        
        elif len(unique) == 2:
            if len(list3) > 3:
                if maxCh - max(unique) + min(unique) >= abs(unique[0] - unique[1]):
                    value = min((len(list3) + abs(unique[0] - unique[1])),  abs(unique[1] - unique[0]) * (len(list3) - 1))
                    return value
                else:
                    value = max(distArr)
                    return value
            else:
                if len(list3) == 3:
                    value = min((len(list3) * (abs(unique[0] - unique[1]) - 1) + abs(unique[0] - unique[1])), 2 * (maxCh + unique[0] - unique[1]))
                    return value
        else:
            value = min(distArr)

        return value

if __name__ == '__main__':
    calc = Zapping()
    calc.eval("6 4 3 1 4 5")
    calc.eval("5 3 1 3 3")
    calc.eval("10 5 8 3 4 1 2 2 10 9 7")
    calc.eval("10 3 2 9 1")
    calc.eval("3 1 2 1 1 3 1 3 3 3 3 2 3 2 1 2 2 1 2 3 3 1 1 1 1 3 1 3 1 2 3 3 2 1 3 3 2 1 1 3 1 2 3 3 3 3 2 2 3")
    calc.eval("5 1 2 2")
    calc.eval("5 1 3 3")
    calc.eval("5 1 4 4")
    calc.eval("5 1 5 5")


    