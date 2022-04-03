import random

with open("in.txt", "w+") as f:
    for i in range(0, 100):
        a = random.randint(0, 1000000000000000000)
        b = random.randint(0, 1000000000000000000)
        f.write(f"{a} {b} {a + b} {a - b} {a * b} {a // b} {a % b}\n")
