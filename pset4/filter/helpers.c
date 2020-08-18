#include "helpers.h"
#include <stdio.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // First display all hex values
    for(int i = 0; i < height; i++){
        for(int q = 0; q < width; q++){
            int sum = image[i][q].rgbtBlue + 
                image[i][q].rgbtGreen + image[i][q].rgbtRed;
            int average = sum / 3;
            image[i][q].rgbtBlue = average;
            image[i][q].rgbtGreen = average;
            image[i][q].rgbtRed = average;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE reversed_image[height][width];
    
    for(int i = 0; i < height; i++){
        for(int q = 0; q < width; q++){
            int k = width - q - 1;
            
            reversed_image[i][q].rgbtBlue = image[i][k].rgbtBlue;
            reversed_image[i][q].rgbtGreen = image[i][k].rgbtGreen;
            reversed_image[i][q].rgbtRed = image[i][k].rgbtRed;
        }
    }
    
    memcpy(image, reversed_image, height * width * sizeof(RGBTRIPLE));
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
