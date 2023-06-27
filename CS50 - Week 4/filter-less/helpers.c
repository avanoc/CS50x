#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the original RGB
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Change the image to greyscale
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the sepia value for RGB
            int sepiaBlue = round(image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131);
            int sepiaGreen = round(image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168);
            int sepiaRed = round(image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189);
            // Check that no value is larger than 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            // Change the image to sepia
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // Iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap bytes to reflect the image
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    int average_blue = 0;
    int average_green = 0;
    int average_red = 0;
    // Iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Make sure the image stays within limits
            int k = i - 1;
            int l = i + 1;
            int m = j - 1;
            int n = j + 1;
            // Calculate the values of blurred RGB, depending on pixel position
            // Middle pixel:
            if (k > 0 || l < height || m > 0 || n < width)
            {
                average_blue = round((image[i][j].rgbtBlue + image[k][j].rgbtBlue + image[l][j].rgbtBlue + image[i][m].rgbtBlue +
                                      image[i][n].rgbtBlue + image[k][m].rgbtBlue + image[l][m].rgbtBlue + image[l][n].rgbtBlue + image[k][n].rgbtBlue) / 9.0);
                average_green = round((image[i][j].rgbtGreen + image[k][j].rgbtGreen + image[i][m].rgbtGreen + image[k][m].rgbtGreen +
                                       image[l][j].rgbtGreen + image[i][n].rgbtGreen + image[l][n].rgbtGreen + image[l][m].rgbtGreen + image[k][n].rgbtGreen) / 9.0);
                average_red = round((image[i][j].rgbtRed + image[k][j].rgbtRed + image[i][m].rgbtRed + image[k][m].rgbtRed + image[l][j].rgbtRed +
                                     image[i][n].rgbtRed + image[l][n].rgbtRed + image[l][m].rgbtRed + image[k][n].rgbtRed) / 9.0);
            }
            // Pixel on edge:
            if (k < 0 && (m >= 0 || n < width - 1))
            {
                average_blue = round((image[i][j].rgbtBlue + image[i][m].rgbtBlue + image[l][j].rgbtBlue + image[i][n].rgbtBlue +
                                      image[l][n].rgbtBlue + image[l][m].rgbtBlue) / 6.0);
                average_green = round((image[i][j].rgbtGreen + image[i][m].rgbtGreen + image[l][j].rgbtGreen + image[i][n].rgbtGreen +
                                       image[l][n].rgbtGreen + image[l][m].rgbtGreen) / 6.0);
                average_red = round((image[i][j].rgbtRed + image[i][m].rgbtRed + image[l][j].rgbtRed + image[i][n].rgbtRed + image[l][n].rgbtRed +
                                     image[l][m].rgbtRed) / 6.0);
            }
            if (l > height - 1 && (m >= 0 || n < width - 1))
            {
                average_blue = round((image[i][j].rgbtBlue + image[k][j].rgbtBlue + image[i][m].rgbtBlue + image[k][m].rgbtBlue +
                                      image[i][n].rgbtBlue + image[k][n].rgbtBlue) / 6.0);
                average_green = round((image[i][j].rgbtGreen + image[k][j].rgbtGreen + image[i][m].rgbtGreen + image[k][m].rgbtGreen +
                                       image[i][n].rgbtGreen + image[k][n].rgbtGreen) / 6.0);
                average_red = round((image[i][j].rgbtRed + image[k][j].rgbtRed + image[i][m].rgbtRed + image[k][m].rgbtRed +
                                     image[i][n].rgbtRed + image[k][n].rgbtRed) / 6.0);
            }
            if (m < 0 && (k >= 0 || l < height - 1))
            {
                average_blue = round((image[i][j].rgbtBlue + image[k][j].rgbtBlue + image[l][j].rgbtBlue + image[i][n].rgbtBlue +
                                      image[l][n].rgbtBlue + image[k][n].rgbtBlue) / 6.0);
                average_green = round((image[i][j].rgbtGreen + image[k][j].rgbtGreen + image[l][j].rgbtGreen + image[i][n].rgbtGreen +
                                       image[l][n].rgbtGreen + image[k][n].rgbtGreen) / 6.0);
                average_red = round((image[i][j].rgbtRed + image[k][j].rgbtRed + image[l][j].rgbtRed + image[i][n].rgbtRed +
                                     image[l][n].rgbtRed + image[k][n].rgbtRed) / 6.0);
            }
            if (n > width - 1 && (k >= 0 || l < height - 1))
            {
                average_blue = round((image[i][j].rgbtBlue + image[k][j].rgbtBlue + image[i][m].rgbtBlue + image[k][m].rgbtBlue +
                                      image[l][j].rgbtBlue + image[l][m].rgbtBlue) / 6.0);
                average_green = round((image[i][j].rgbtGreen + image[k][j].rgbtGreen + image[i][m].rgbtGreen + image[k][m].rgbtGreen +
                                       image[l][j].rgbtGreen + image[l][m].rgbtGreen) / 6.0);
                average_red = round((image[i][j].rgbtRed + image[k][j].rgbtRed + image[i][m].rgbtRed + image[k][m].rgbtRed +
                                     image[l][j].rgbtRed + image[l][m].rgbtRed) / 6.0);
            }
            //Pixel in corner:
            if (k < 0 && m < 0)
            {
                average_blue = round((image[i][j].rgbtBlue + image[i][n].rgbtBlue + image[l][j].rgbtBlue + image[l][n].rgbtBlue) / 4.0);
                average_green = round((image[i][j].rgbtGreen + image[i][n].rgbtGreen + image[l][j].rgbtGreen + image[l][n].rgbtGreen) / 4.0);
                average_red = round((image[i][j].rgbtRed + image[i][n].rgbtRed + image[l][j].rgbtRed + image[l][n].rgbtRed) / 4.0);
            }
            if (k < 0 && n > width - 1)
            {
                average_blue = round((image[i][j].rgbtBlue + image[i][m].rgbtBlue + image[l][j].rgbtBlue + image[l][m].rgbtBlue) / 4.0);
                average_green = round((image[i][j].rgbtGreen + image[i][m].rgbtGreen + image[l][j].rgbtGreen + image[l][m].rgbtGreen) / 4.0);
                average_red = round((image[i][j].rgbtRed + image[i][m].rgbtRed + image[l][j].rgbtRed + image[l][m].rgbtRed) / 4.0);
            }
            if (l > height - 1 && m < 0)
            {
                average_blue = round((image[i][j].rgbtBlue + image[i][n].rgbtBlue + image[k][j].rgbtBlue + image[k][n].rgbtBlue) / 4.0);
                average_green = round((image[i][j].rgbtGreen + image[i][n].rgbtGreen + image[k][j].rgbtGreen + image[k][n].rgbtGreen) / 4.0);
                average_red = round((image[i][j].rgbtRed + image[i][n].rgbtRed + image[k][j].rgbtRed + image[k][n].rgbtRed) / 4.0);
            }
            if (l > height - 1 && n > width - 1)
            {
                average_blue = round((image[i][j].rgbtBlue + image[i][m].rgbtBlue + image[k][j].rgbtBlue + image[k][m].rgbtBlue) / 4.0);
                average_green = round((image[i][j].rgbtGreen + image[i][m].rgbtGreen + image[k][j].rgbtGreen + image[k][m].rgbtGreen) / 4.0);
                average_red = round((image[i][j].rgbtRed + image[i][m].rgbtRed + image[k][j].rgbtRed + image[k][m].rgbtRed) / 4.0);
            }
            // Blur the image
            image_copy[i][j].rgbtBlue = average_blue;
            image_copy[i][j].rgbtGreen = average_green;
            image_copy[i][j].rgbtRed = average_red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
    return;
}
