#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) //if the cla is different than 2
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open the card.raw file
    char *infile = argv[1];

    FILE *file = fopen(infile, "r");
    if (file == NULL)
    {
        printf("It wasn't possible to open the file.\n");
        return 2;
    }

    BYTE buffer[512]; //this will contain the bytes of the jpg
    int count = 0;
    char filename[8]; //will store the name of each jpg
    FILE *image = NULL; //this is the jpg file

    while (1)
    {
        int totalbytes = fread(buffer, sizeof(BYTE), 1, file); //the block from the card we want to read stored in buffer
        printf("%i",totalbytes);
        if (totalbytes == 0 || feof(file))
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0) //if we find a jpg
        {
            if (image != NULL)
            {
                fclose(image);
                count ++;
            }
            sprintf(filename, "%03i.jpg", count); //create the file like ###.jpg
            image = fopen(filename, "w"); //open the file create above to write in it
        }
        if (image != NULL)
        {
            fwrite(&buffer, sizeof(BYTE), totalbytes, image);
        }
    }
    fclose(image);
    fclose(file);
    return 0;
}
