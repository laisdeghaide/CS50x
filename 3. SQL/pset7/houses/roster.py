from sys import argv
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python roster.py House")
    exit()

db = SQL("sqlite:///students.db")

characteres = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last", argv[1])

for c in characteres:
    if c['middle'] != None:
        print("{} {} {}, born {}" .format(c['first'], c['middle'], c['last'], c['birth']))
    else:
        print("{} {}, born {}" .format(c['first'], c['last'], c['birth']))