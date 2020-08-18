#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

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
    RGBTRIPLE blurred_image[height][width];
    
    for(int i = 0; i < height; i++){
        for(int q = 0; q < width; q++){
            
            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;
            int surrounding_blocks = 0;
            
            for(int y = i - 1; y < i + 2; y++){
                for(int x = q - 1; x < q + 2; x++){
                    if(y >= 0 && y < height && x >= 0 && x < width){
                        blue_sum += image[y][x].rgbtBlue;
                        green_sum += image[y][x].rgbtGreen;
                        red_sum += image[y][x].rgbtRed;
                        surrounding_blocks++;
                    }

                }
            }
            
            int blurred_blue = round(blue_sum / surrounding_blocks);
            int blurred_green = round(green_sum / surrounding_blocks);
            int blurred_red = round(red_sum / surrounding_blocks);
            
            blurred_image[i][q].rgbtBlue = blurred_blue;
            blurred_image[i][q].rgbtGreen = blurred_green;
            blurred_image[i][q].rgbtRed = blurred_red;
        }
    }
    
    memcpy(image, blurred_image, height * width * sizeof(RGBTRIPLE));
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
