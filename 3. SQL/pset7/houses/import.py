from sys import argv
from csv import reader
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit()

db = SQL("sqlite:///students.db")

with open(argv[1], newline='') as characters:
    reader = reader(characters)

    for character in reader:
        if character[0] == 'name':
            continue

        first = character[0].split()[0]
        last = character[0].split()[-1]

        if character[0].count(' ') == 2:
            middle = character[0].split()[1]
        else:
            middle = None
        
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, character[1], character[2])