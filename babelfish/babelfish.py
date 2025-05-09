dict = {}
line = input()

while line:
    a,b = line.split()
    dict[b] = a
    line = input()

while True:
    try:
        c = input()
        print("eh" if c not in dict else dict[c])
    except:
        break

    

