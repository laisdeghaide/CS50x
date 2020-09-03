import cs50
while True:
    height = cs50.get_int("Height: ")
    if height >= 1 and height <= 8:
        break
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)

