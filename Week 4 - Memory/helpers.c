#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, avg = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 0 = Blue, 1 = Green, 2 = Red
            int sepiaColors[3];
            sepiaColors[0] = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            sepiaColors[1] = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaColors[2] = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);

            // check whether in range
            for (int k = 0; k < 3; k++)
            {
                if (sepiaColors[k] > 255)
                {
                    sepiaColors[k] = 255;
                }
            }

            image[i][j].rgbtBlue = sepiaColors[0];
            image[i][j].rgbtGreen = sepiaColors[1];
            image[i][j].rgbtRed = sepiaColors[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < width; j++)
        {
            // condition check
            if (j == n)
            {
                break;
            }

            // 0 = Blue, 1 = Green, 2 = Red
            int tmp[3];
            tmp[0] = image[i][width - 1 - j].rgbtBlue;
            tmp[1] = image[i][width - 1 - j].rgbtGreen;
            tmp[2] = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - 1 - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - 1 - j].rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = tmp[0];
            image[i][j].rgbtGreen = tmp[1];
            image[i][j].rgbtRed = tmp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    typedef struct
    {
        int blue;
        int green;
        int red;
    }
    helper;

    helper helpers[height][width];


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int avgColors[3][3];
            // determine corner cases

            if (i == 0)
            {
                if (j == 0)
                {
                    // blue
                    avgColors[0][1] = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
                    avgColors[0][2] = image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    // green
                    avgColors[1][1] = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
                    avgColors[1][2] = image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                    // red
                    avgColors[2][1] = image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
                    avgColors[2][2] = image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;

                    // fill helper with avg colors
                    helpers[i][j].blue = round((avgColors[0][1] + avgColors[0][2]) / 4.00);
                    helpers[i][j].green = round((avgColors[1][1] + avgColors[1][2]) / 4.00);
                    helpers[i][j].red = round((avgColors[2][1] + avgColors[2][2]) / 4.00);
                }
                else if (j == width - 1)
                {
                    // blue
                    avgColors[0][1] = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue;
                    avgColors[0][2] = image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;

                    // green
                    avgColors[1][1] = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen;
                    avgColors[1][2] = image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;

                    // red
                    avgColors[2][1] = image[i][j - 1].rgbtRed + image[i][j].rgbtRed;
                    avgColors[2][2] = image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][1] + avgColors[0][2]) / 4.00);
                    helpers[i][j].green = round((avgColors[1][1] + avgColors[1][2]) / 4.00);
                    helpers[i][j].red = round((avgColors[2][1] + avgColors[2][2]) / 4.00);
                }
                else
                {
                    // blue
                    avgColors[0][1] = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
                    avgColors[0][2] = image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    // green
                    avgColors[1][1] = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
                    avgColors[1][2] = image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                    // red
                    avgColors[2][1] = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
                    avgColors[2][2] = image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][1] + avgColors[0][2]) / 6.00);
                    helpers[i][j].green = round((avgColors[1][1] + avgColors[1][2]) / 6.00);
                    helpers[i][j].red = round((avgColors[2][1] + avgColors[2][2]) / 6.00);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    // blue
                    avgColors[0][0] = image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    avgColors[0][1] = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;

                    // green
                    avgColors[1][0] = image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    avgColors[1][1] = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;

                    // red
                    avgColors[2][0] = image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    avgColors[2][1] = image[i][j].rgbtRed + image[i][j + 1].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][0] + avgColors[0][1]) / 4.00);
                    helpers[i][j].green = round((avgColors[1][0] + avgColors[1][1]) / 4.00);
                    helpers[i][j].red = round((avgColors[2][0] + avgColors[2][1]) / 4.00);
                }
                else if (j == width - 1)
                {
                    // blue
                    avgColors[0][0] = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue;
                    avgColors[0][1] = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue;

                    // green
                    avgColors[1][0] = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen;
                    avgColors[1][1] = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen;

                    // red
                    avgColors[2][0] = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed;
                    avgColors[2][1] = image[i][j - 1].rgbtRed + image[i][j].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][0] + avgColors[0][1]) / 4.00);
                    helpers[i][j].green = round((avgColors[1][0] + avgColors[1][1]) / 4.00);
                    helpers[i][j].red = round((avgColors[2][0] + avgColors[2][1]) / 4.00);
                }
                else
                {
                    // blue
                    avgColors[0][0] = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    avgColors[0][1] = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;

                    // green
                    avgColors[1][0] = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    avgColors[1][1] = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;

                    // red
                    avgColors[2][0] = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    avgColors[2][1] = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][0] + avgColors[0][1]) / 6.00);
                    helpers[i][j].green = round((avgColors[1][0] + avgColors[1][1]) / 6.00);
                    helpers[i][j].red = round((avgColors[2][0] + avgColors[2][1]) / 6.00);
                }
            }
            else
            {
                if (j == 0)
                {
                    // blue
                    avgColors[0][0] = image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    avgColors[0][1] = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
                    avgColors[0][2] = image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    // green
                    avgColors[1][0] = image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    avgColors[1][1] = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
                    avgColors[1][2] = image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                    // red
                    avgColors[2][0] = image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    avgColors[2][1] = image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
                    avgColors[2][2] = image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][0] + avgColors[0][1] + avgColors[0][2]) / 6.00);
                    helpers[i][j].green = round((avgColors[1][0] + avgColors[1][1] + avgColors[1][2]) / 6.00);
                    helpers[i][j].red = round((avgColors[2][0] + avgColors[2][1] + avgColors[2][2]) / 6.00);
                }
                else if (j == width - 1)
                {
                    // blue
                    avgColors[0][0] = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue;
                    avgColors[0][1] = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue;
                    avgColors[0][2] = image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;

                    // green
                    avgColors[1][0] = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen;
                    avgColors[1][1] = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen;
                    avgColors[1][2] = image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;

                    // red
                    avgColors[2][0] = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed;
                    avgColors[2][1] = image[i][j - 1].rgbtRed + image[i][j].rgbtRed;
                    avgColors[2][2] = image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][0] + avgColors[0][1] + avgColors[0][2]) / 6.00);
                    helpers[i][j].green = round((avgColors[1][0] + avgColors[1][1] + avgColors[1][2]) / 6.00);
                    helpers[i][j].red = round((avgColors[2][0] + avgColors[2][1] + avgColors[2][2]) / 6.00);
                }
                else
                {
                    // base case
                    // blue
                    avgColors[0][0] = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    avgColors[0][1] = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
                    avgColors[0][2] = image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    // green
                    avgColors[1][0] = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    avgColors[1][1] = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
                    avgColors[1][2] = image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                    // red
                    avgColors[2][0] = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    avgColors[2][1] = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
                    avgColors[2][2] = image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;

                    // fill pixel with avg colors
                    helpers[i][j].blue = round((avgColors[0][0] + avgColors[0][1] + avgColors[0][2]) / 9.00);
                    helpers[i][j].green = round((avgColors[1][0] + avgColors[1][1] + avgColors[1][2]) / 9.00);
                    helpers[i][j].red = round((avgColors[2][0] + avgColors[2][1] + avgColors[2][2]) / 9.00);
                }
            }
        }
    }

    // fill real picture with helper values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = helpers[i][j].blue;
            image[i][j].rgbtGreen = helpers[i][j].green;
            image[i][j].rgbtRed = helpers[i][j].red;
        }
    }

    return;
}
