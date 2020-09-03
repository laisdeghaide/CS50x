from sys import argv
from csv import reader

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

# getting the dna sequence (STR) from the database
with open(argv[1]) as csv_file:
    csv_reader = reader(csv_file)
    for row in csv_reader:
        list_str = row
        list_str.pop(0)
        break

# reading the dna sequence file
with open(argv[2]) as txt_file:
    txt_reader = reader(txt_file)
    for row in txt_reader:
        dna_sequence = row
        
# transforming the list to a string 
dna_sequence = dna_sequence[0]

# this will contain the biggest occurrence of which STR
max_occurs_list = []

# runs through the STR list
for STR in list_str: 
    count = max_count = position = prev_position = 0

    # runs through the DNA sequence
    while position < len(dna_sequence): 
        position = dna_sequence.find(STR, position)
        
        # if didn't find the STR in the dna sequence
        if position == -1:
            count = 0
            break

        # found the str in the sequence for the first time
        elif (position != -1) and prev_position == 0:
            count += 1
            prev_position = position
            max_count = count

        # found other str in sequence
        elif (position != -1) and (position - len(STR) == prev_position):
            count += 1
            prev_position = position
            if max_count < count:
                max_count = count

        # found the str in dna sequence but not for the first time
        elif (position != -1) and (position - len(STR) != prev_position):
            count = 1
            prev_position = position
            if max_count < count:
                max_count = count

        position += 1

    max_occurs_list.append(max_count)

max_occurs_list = list(map(str, max_occurs_list))


# opening the file again to get the list of people and their dna str
with open(argv[1]) as csv_file:
    csv_reader = list(reader(csv_file))
csv_reader.pop(0)

match = 0
for list in csv_reader:
    if list[1:] == max_occurs_list:
        print(list[0])
        match = 1

if match == 0:
    print("No match")
