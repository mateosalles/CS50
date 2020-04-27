#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE pixel = image[h][w];
            int gray = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            pixel.rgbtRed = gray;
            pixel.rgbtGreen = gray;
            pixel.rgbtBlue = gray;
            image[h][w] = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;
    RGBTRIPLE *pixel = malloc(sizeof(RGBTRIPLE));
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < half; w++)
        {
            if (pixel != NULL)
            {
                *pixel = image[h][w];
                image[h][w] = image[h][(width - 1) - w];
                image[h][(width - 1) - w] = *pixel;
            }
        }
    }
    free(pixel);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Allocate memory for temporary image containing averages for each pixel
    RGBTRIPLE(*averages)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (averages == NULL)
    {
        fprintf(stderr, "Not enough memory to render blur.\n");
        return;
    }

    RGBTRIPLE pixel;

    //Scan image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float count = 0;
            //Scan 3x3 matrix with the actual pixel in the center
            for (int i = h - 1; i <= h + 1; i++)
            {
                for (int j = w - 1; j <= w + 1; j++)
                {
                    //Avoids going out of image bounds
                    if (0 <= i && i < height && 0 <= j && j < width)
                    {
                        red = red + image[i][j].rgbtRed;
                        green = green + image[i][j].rgbtGreen;
                        blue = blue + image[i][j].rgbtBlue;
                        count++;
                    }
                }
            }
            //Load and assign pixel with average colour values to temporary matrix
            pixel.rgbtRed = round(red / count);
            pixel.rgbtGreen = round(green / count);
            pixel.rgbtBlue = round(blue / count);
            averages[h][w] = pixel;
        }
    }
    //Replace input image with blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = averages[i][j];
        }
    }
    free(averages);
    return;
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Allocate memory for Matrix Kernel
    int(*kernel)[3] = calloc(3, 3 * sizeof(int));
    if (kernel == NULL)
    {
        fprintf(stderr, "Not enough memory to render edges.\n");
        return;
    }
    //Populate kernel
    for (int c = 0; c < 3; c++)
    {
        for (int r = 0; r < 3; r++)
        {
            switch (c)
            {
                case 0:
                    switch (r)
                    {
                        case 0:
                            kernel[r][c] = -1;
                            break;
                        case 1:
                            kernel[r][c] = -2;
                            break;
                        case 2:
                            kernel[r][c] = -1;
                            break;
                    }
                    break;
                case 1:
                    kernel[r][c] = 0;
                    break;
                case 2:
                    kernel[r][c] = kernel[r][0] * -1;
                    break;
            }
        }
    }

    //Allocate memory for temporary image containing averages for each pixel
    RGBTRIPLE(*weighted_sum)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (weighted_sum == NULL)
    {
        fprintf(stderr, "Not enough memory to render edges.\n");
        return;
    }

    //Scan image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Variables to store Gx and Gy values
            int redx = 0;
            int redy = 0;
            int greenx = 0;
            int greeny = 0;
            int bluex = 0;
            int bluey = 0;

            //Scan 3x3 matrix with the actual pixel in the center [1][1]
            for (int i = h - 1; i <= h + 1; i++)
            {
                for (int j = w - 1; j <= w + 1; j++)
                {
                    //Avoids going out of image bounds
                    if (0 <= i && i < height && 0 <= j && j < width)
                    {
                        //Perform weighted sum
                        int r = i - h + 1;
                        int c = j - w + 1;
                        //Multiplies color value with according value from the kernels
                        redx = redx + (image[i][j].rgbtRed * kernel[r][c]);
                        redy = redy + (image[i][j].rgbtRed * kernel[c][r]);
                        greenx = greenx + (image[i][j].rgbtGreen * kernel[r][c]);
                        greeny = greeny + (image[i][j].rgbtGreen * kernel[c][r]);
                        bluex = bluex + (image[i][j].rgbtBlue * kernel[r][c]);
                        bluey = bluey + (image[i][j].rgbtBlue * kernel[c][r]);
                    }
                }
            }

            //Load and assign pixel with weighted summed colour values to temporary matrix
            RGBTRIPLE pixel;
            int red = round(sqrt(pow(redx, 2) + pow(redy, 2)));
            int green = round(sqrt(pow(greenx, 2) + pow(greeny, 2)));
            int blue = round(sqrt(pow(bluex, 2) + pow(bluey, 2)));
            //Topping color values at 255
            //Had to add the brackets for the if because of style50 although not needed
            if (red > 255)
            {
                pixel.rgbtRed = 255;
            }
            else
            {
                pixel.rgbtRed = red;
            }
            if (green > 255)
            {
                pixel.rgbtGreen = 255;
            }
            else
            {
                pixel.rgbtGreen = green;
            }
            if (blue > 255)
            {
                pixel.rgbtBlue = 255;
            }
            else
            {
                pixel.rgbtBlue = blue;
            }
            //Assign pixel
            weighted_sum[h][w] = pixel;
        }
    }
    //Replace input image with edged image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = weighted_sum[i][j];
        }
    }
    free(weighted_sum);
    free(kernel);
    return;
}