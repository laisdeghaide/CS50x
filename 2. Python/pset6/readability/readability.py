import cs50


def main():
    text = cs50.get_string("Text: ")

    letter = count_letters(text)
    word = count_words(text)
    sentence = count_sentences(text)
    
    L = float(letter) / float(word) * 100
    S = float(sentence) / float(word) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print("Grade", index)


def count_letters(text):
    sum_letters = sum(letter.isalpha() for letter in text)
    return sum_letters
    

def count_words(text):
    sum_words = sum(word.isspace() for word in text)
    return sum_words + 1
    

def count_sentences(text):
    symbols = ['.', '?', '!']
    sum_sentences = sum(letter in symbols for letter in text)
    return sum_sentences
    

if __name__ == "__main__":
    main()