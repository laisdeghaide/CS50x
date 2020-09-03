import cs50

while True:
    dollars = cs50.get_float("Change owed: ")
    if dollars >= 0:
        break

cents = round(dollars * 100)
tcoins = 0

while cents >= 25:
    cents -= 25
    tcoins += 1

while cents >= 10:
    cents -= 10
    tcoins += 1

while cents >= 5:
    cents -= 5
    tcoins += 1

while cents >= 1:
    cents -= 1
    tcoins += 1

print(tcoins)