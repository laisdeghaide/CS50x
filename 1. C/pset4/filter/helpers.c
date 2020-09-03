#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float RGB; //this will be the averege of the 3 colors
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGB = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); //calculating the averege
            //applying it to all colors
            image[i][j].rgbtBlue = RGB;
            image[i][j].rgbtGreen = RGB;
            image[i][j].rgbtRed = RGB;
        }
    }
    return;
}

float cap(float n)
{
    if (n > 255)
    {
        n = 255;
    }
    return n;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float R, G, B;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating the sepia color of red, green and blue
            R = cap(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            G = cap(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            B = cap(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));

            //applying it to each color
            image[i][j].rgbtRed = R;
            image[i][j].rgbtGreen = G;
            image[i][j].rgbtBlue = B;
        }
    }
    return;
}

//swap pixels
RGBTRIPLE swap(RGBTRIPLE *image, RGBTRIPLE *reflection)
{
    RGBTRIPLE temp = *image;
    *image = *reflection;
    *reflection = temp;

    return *image;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //the pixel will receive his reverted one
            image[i][j] = swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int R, G, B;
    float total;

    RGBTRIPLE rgb[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            R = G = B = 0;
            total = 0.0;

            //this for is to consider the right and left pixels from the one I'm analyzing
            for (int ii = -1; ii <= 1; ii++)
            {
                //this is to consider the bottom and the above pixels from the one I'm analyzing
                for (int jj = -1; jj <= 1; jj++)
                {
                    //if the pixels around the one I'm analyzing are valid, then I will increment them on my avarege
                    if (i + ii >= 0 && i + ii < height && j + jj >= 0 && j + jj < width)
                    {
                        total++;
                        R += image[i + ii][j + jj].rgbtRed;
                        G += image[i + ii][j + jj].rgbtGreen;
                        B += image[i + ii][j + jj].rgbtBlue;
                    }
                }
            }
            //doing the avarege
            rgb[i][j].rgbtRed = round(R / total);
            rgb[i][j].rgbtGreen = round(G / total);
            rgb[i][j].rgbtBlue = round(B / total);
        }
    }

    //applying the averege of pixels in the pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = rgb[i][j].rgbtBlue;
            image[i][j].rgbtGreen = rgb[i][j].rgbtGreen;
            image[i][j].rgbtRed = rgb[i][j].rgbtRed;
        }
    }
    return;
}
