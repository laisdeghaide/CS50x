import cs50

number = cs50.get_int("Number: ")

number_copy = number
sum_others = 0
sum_checksum = 0
lenght = 0

while number > 0:
    first_to_last = number % 10
    sum_others += first_to_last
    number = number // 10
    lenght += 1
    second_to_last = number % 10
    number = number // 10
    lenght += 1
    mult = second_to_last * 2
    division = mult // 10
    module = mult % 10
    sum_checksum = sum_checksum + division + module

total_sum = sum_others + sum_checksum

while number_copy >= 10:
    first_digit = number_copy // 10
    second_digit = number_copy % 10
    number_copy = number_copy // 10


if total_sum % 10 == 0:
    if (lenght - 1) == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7):
        print("AMEX")
    
    elif lenght == 16 and first_digit == 5 and (second_digit >= 1 and second_digit <= 5):
        print("MASTERCARD")
    
    elif (lenght == 16 or lenght == 13) and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
