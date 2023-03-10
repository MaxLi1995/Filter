#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b);
void swap(BYTE *a, BYTE *b);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red = min(round((image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) + (image[i][j].rgbtBlue * .189)), 255);
            int Green =  min(round((image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue * .168)), 255);
            int Blue = min(round((image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue * .131)), 255);
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make an empty copy of image
    RGBTRIPLE copy[height][width];
    //copy image to copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // image bluring process
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            // all of these calculations require a veriable to save the value of the calculation
            // othwise directly making the entry equal to the calcuation will damage the subsequent entry calculations
            if (i == 0 && j == 0)
            {
                int a = round((copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j].rgbtRed) / 4.0);
                int b = round((copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                int c = round((copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            // bottom left corner
            else if (i == height - 1 && j == 0)
            {
                int a = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j].rgbtRed) / 4.0);
                int b = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                int c = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            //top right corner
            else if (i == 0 && j == width - 1)
            {
                int a = round((copy[i][j - 1 ].rgbtRed + copy[i + 1 ][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j].rgbtRed) / 4.0);
                int b = round((copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                int c = round((copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            //bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                int a = round((copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed) / 4.0);
                int b = round((copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                int c = round((copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            // top row
            else if (i == 0)
            {
                int a = round((copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j
                               + 1].rgbtRed + copy[i][j].rgbtRed) / 6.0);
                int b = round((copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                               copy[i + 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen) / 6.0);
                int c = round((copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i +
                               1][j + 1].rgbtBlue + copy[i][j].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            //left collum
            else if (j == 0)
            {
                int a = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j
                               + 1].rgbtRed + copy[i][j].rgbtRed) / 6.0);
                int b = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                               copy[i + 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen) / 6.0);
                int c = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i +
                               1][j + 1].rgbtBlue + copy[i][j].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            // bottom row
            else if (i == height - 1)
            {
                int a = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                               copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);
                int b = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                               copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);
                int c = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                               copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            // right collum
            else if (j == width - 1)
            {
                int a = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i +
                               1][j].rgbtRed + copy[i][j].rgbtRed) / 6.0);
                int b = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                               copy[i + 1][j].rgbtGreen + copy[i][j].rgbtGreen) / 6.0);
                int c = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                               copy[i + 1][j].rgbtBlue + copy[i][j].rgbtBlue) / 6.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
            // everything else in the middle
            else
            {
                int a = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                               copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i +
                                       1][j + 1].rgbtRed) / 9.0);
                int b = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                               copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i +
                                       1][j + 1].rgbtGreen) / 9.0);
                int c = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                               copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j +
                                       1].rgbtBlue) / 9.0);
                image[i][j].rgbtRed = a;
                image[i][j].rgbtGreen = b;
                image[i][j].rgbtBlue = c;
            }
        }
    }

}

//find the smaller of two int
int min(int a, int b)
{
    return (a > b) ? b : a;
}

//swap two values
void swap(BYTE *a, BYTE *b)
{
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
}