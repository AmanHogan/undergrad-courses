#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>
#include <limits.h>
#include <stdlib.h>

/** Dimension of the input image */
#define DIM 512

/** Minimum and maximum gloabl convolutionv alues */
int global_min = INT_MAX;
int global_max = INT_MIN;

unsigned char normalize(int value);

/**
 * Contains coords of box drawn with left mouse.
 * roi.x , roi.y  - left upper corner's coordinates
 * roi.width , roi.height - width and height of the box 
*/
extern XRectangle roi;


/** Sobel Templates */
int verticalSobel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int horizontalSobel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
int majorDiagonalSobel[3][3] = {{0, -1, -2}, {1, 0, -1}, {2, 1, 0}};
int minorDiagonalSobel[3][3] = {{-2, -1, 0}, {-1, 0, 1}, {0, 1, 2}};

/**
 * @brief
 * @param image the original greyscale image
 * @param size the actual size of the image
 * @param proc_image - the image representation 
 * resulting from the processing. 
 * This will be displayed upon return from this function.
 * @return None
*/
void process_image(unsigned char image[DIM][DIM], int size[2], unsigned char proc_img[DIM][DIM])
{
    // Temp array to hold convolution results for each template
    int temp_results_vertical[DIM][DIM] = {0};
    int temp_results_horizontal[DIM][DIM] = {0};
    int temp_results_major_diag[DIM][DIM] = {0};
    int temp_results_minor_diag[DIM][DIM] = {0};

    // Peform convolution for each sobel template
    // Store convolution results in temporary array
    for (int x = 1; x < size[0] - 1; x++) 
    {
        for (int y = 1; y < size[1] - 1; y++) 
        {
            int sum_vertical = 0;
            int sum_horizontal = 0;
            int sum_major_diag = 0;
            int sum_minor_diag = 0;
            
            // Convolution operation for each template
            for (int i = -1; i <= 1; i++) 
            {
                for (int j = -1; j <= 1; j++) 
                {
                    int pixel_value = image[x + i][y + j];
                    sum_vertical += pixel_value * verticalSobel[i + 1][j + 1];
                    sum_horizontal += pixel_value * horizontalSobel[i + 1][j + 1];
                    sum_major_diag += pixel_value * majorDiagonalSobel[i + 1][j + 1];
                    sum_minor_diag += pixel_value * minorDiagonalSobel[i + 1][j + 1];
                }
            }

            // Store the results in temporary arrays
            temp_results_vertical[x][y] = sum_vertical;
            temp_results_horizontal[x][y] = sum_horizontal;
            temp_results_major_diag[x][y] = sum_major_diag;
            temp_results_minor_diag[x][y] = sum_minor_diag;
        }
    }

    // Now iterate over each pixel to calculate the gradient magnitude
    // This involves calculating the gradient of all sobel templates
    for (int x = 0; x < size[0]; x++) 
    {
        for (int y = 0; y < size[1]; y++) 
        {
            // Calculate the gradient magnitude
            int gx = temp_results_vertical[x][y];
            int gy = temp_results_horizontal[x][y];
            int g_diag1 = temp_results_major_diag[x][y];
            int g_diag2 = temp_results_minor_diag[x][y];
            int gradient_magnitude = (int)sqrt(gx * gx + gy * gy + g_diag1 * g_diag1 + g_diag2 * g_diag2);

            // Update global min and max
            if (gradient_magnitude < global_min) { global_min = gradient_magnitude; }
            if (gradient_magnitude > global_max) { global_max = gradient_magnitude; }

            // Temporarily store the unnormalized magnitude
            proc_img[x][y] = (unsigned char) gx;
        }
    }

    // Normalize the combined image
    for (int x = 0; x < size[0]; x++) 
    {
        for (int y = 0; y < size[1]; y++) 
        {
            proc_img[x][y] = normalize(proc_img[x][y]);
        }
    }
}

/**
 * @brief Scales the values of the global min and max convolution values to [0, 255].
 * @param value convolution value
 * @returns unsigned char in range [0, 255]
*/
unsigned char normalize(int value) 
{
    // Scale the value from the range [global_min, global_max] to [0, 255]
    int scaled_value = (int) (255.0 * (value - global_min) / (global_max - global_min));

    // Ensure convolution value is within the [0, 255] range
    if (scaled_value < 0) { scaled_value = 0; }
    if (scaled_value > 255) { scaled_value = 255; } 

    return (unsigned char) scaled_value;
}
