with open('5.in') as f:
    arr = [int(i) for i in f.readlines()[1].split(' ')]
    print(max(arr) - min(arr))