import sys
def minBills(bills, V):
    m = len(bills)
    table = [1000 for i in range(V + 1)]
    table[0] = 0

    for i in range(1, V + 1):
        for j in range(m):
            print(table)
            if (bills[j] <= i):
                sub_res = table[i - bills[j]]
                if (sub_res != 1000 and
                    sub_res + 1 < table[i]):
                    table[i] = sub_res + 1     
    if table[V] == 1000:
        return -1
       
    return table[V]
 
if __name__ == "__main__":
    bills = [9, 6, 5, 1]
    m = len(bills)
    V = 11
    print("Minimum coins required is ", minBills(bills, V))