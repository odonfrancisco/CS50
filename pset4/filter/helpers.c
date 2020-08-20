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
            int average = round(sum / 3.00);
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
            
            float blue_sum = 0;
            float green_sum = 0;
            float red_sum = 0;
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

void assign_gx_gy(int gx[3][3], int gy[3][3]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    
    RGBTRIPLE edged_image[height][width];
    
    // assign_gx_gy(gx, gy);
    
    for(int i = 0; i < height; i++){
        for(int q = 0; q < width; q++){
            
            int blue_sum_gx = 0;
            int green_sum_gx = 0;
            int red_sum_gx = 0;
            
            int blue_sum_gy = 0;
            int green_sum_gy = 0;
            int red_sum_gy = 0;
            
            for(int y = i - 1; y < i + 2; y++){
                for(int x = q - 1; x < q + 2; x++){
                    
                    if(y >= 0 && y < height && x >= 0 && x < width){
                        // Means coordinates are within boundaries of image
                        int blue_pix = image[y][x].rgbtBlue;
                        int green_pix = image[y][x].rgbtGreen;
                        int red_pix = image[y][x].rgbtRed;
                        
                        blue_sum_gx += gx[y - i+1][x - q+1] * blue_pix;
                        green_sum_gx += gx[y - i+1][x - q+1] * green_pix;
                        red_sum_gx += gx[y - i+1][x - q+1] * red_pix;
                        
                        blue_sum_gy += gy[y - i+1][x - q+1] * blue_pix;
                        green_sum_gy += gy[y - i+1][x - q+1] * green_pix;
                        red_sum_gy += gy[y - i+1][x - q+1] * red_pix;
                        
                    } else {
                        // Means this is a black border
                    }

                }
            }
            
            
            int new_blue = pow(blue_sum_gx, 2) + pow(blue_sum_gy, 2);
            if(new_blue > 255)
                new_blue = 255;
            
            int new_green = pow(green_sum_gx, 2) + pow(green_sum_gy, 2);
            if(new_green > 255)
                new_green = 255;
                
            int new_red = pow(red_sum_gx, 2) + pow(red_sum_gy, 2);
            if(new_red > 255)
                new_red = 255;
            
            edged_image[i][q].rgbtBlue = new_blue;
            edged_image[i][q].rgbtGreen = new_green;
            edged_image[i][q].rgbtRed = new_red;
            
            
            // assign_gx_gy(gx, gy);
        }
    }
    
    memcpy(image, edged_image, height * width * sizeof(RGBTRIPLE));
    return;
}

// void assign_gx_gy(int gx[3][3], int gy[3][3]){
//     gx = { [-1, 0, 1], [-2, 0, 2], [-1, 0, 1] };
//     gy = { [-1, -2, -1], [0, 0, 0], [1, 2, 1] };
// }