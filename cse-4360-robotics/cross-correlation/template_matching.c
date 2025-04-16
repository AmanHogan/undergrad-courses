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

/**
 * Computes the mean and standard deviation of a region in an image.
 * @param region Pointer to the top-left pixel of the region in the image.
 * @param height Height of the region.
 * @param width Width of the region.
 * @param mean Pointer to a float where the mean will be stored.
 * @param std Pointer to a float where the standard deviation will be stored.
 */
void mean_and_std(unsigned char region[DIM][DIM], int height, int width, double *mean, double *std) 
{
    // Initialize sum and sum of squares
    double sum = 0.0;
    double sum_sq = 0.0;
    int n = height * width;

    // Calculate sum and sum of squares
    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j) 
        {
            sum += region[i][j];
            sum_sq += region[i][j] * region[i][j];
        }
    }

    // Calculate mean
    *mean = sum / n;

    double variance = (sum_sq / n) - (*mean * *mean); // variance
    *std = sqrt(variance); // standard deviation

    // Avoids division by zero in the NCC computation
    if (*std == 0) 
    {
        *std = 1;
    }
}


/**
 * Computes the normalized cross-correlation between an image region and a template.
 * @param image_region Pointer to the top-left pixel of the image region.
 * @param template Pointer to the top-left pixel of the template.
 * @param height Height of the template.
 * @param width Width of the template.
 * @param region_mean Mean of the image region.
 * @param region_std Standard deviation of the image region.
 * @param template_mean Mean of the template.
 * @param template_std Standard deviation of the template.
 * @return The normalized cross-correlation coefficient.
 */
double ncc(unsigned char (*image_region)[DIM], unsigned char (*template)[DIM], int height, int width, double region_mean, double region_std, double template_mean, double template_std) 
{   
    // NCC  = [ sum (sum ((Template[][] - Template_mean) * (Image[][] - Image_mean))) ] / ( Template_std * Image_std)
    // NCC score
    double sum = 0.0;

    // Calculate the sum of products between template and image
    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j) 
        {
            // Normalized image pixels
            double image_pixel_normalized = (image_region[i][j] - region_mean) / region_std;

            // Normalized template pixel
            double template_pixel_normalized = (template[i][j] - template_mean) / template_std;
            
            // Sum the product of the normalized pixels
            sum += image_pixel_normalized * template_pixel_normalized;
        }
    }

    // The sum is divided by the number of elements to get the average
    return sum / (width * height);
}

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
    // Logs Correaltion values and NCC values
    FILE *logfile = fopen("logfile.txt", "w");

    // Height and width of selected region 
    int template_width = roi.width;
    int template_height = roi.height;

    // Max NCC values of the NCC array
    double ncc_max = -10000000;
    double ncc_min = 100000000;

    // Array to store NCC values
    double ncc_array[DIM][DIM];

    // template that stores the pixels of selected region
    unsigned char template[template_height][template_width];

    // Exctract template values from selected region
    for (int i = 0; i < template_height; ++i) 
    {
        for (int j = 0; j < template_width; ++j) 
        {
            template[i][j] = image[roi.y + i][roi.x + j];
        }
    }

    // template mean and std
    double template_mean = 0.00;
    double template_std = 0.00;
    mean_and_std(template, template_height, template_width, &template_mean, &template_std);

    // For each pixel in the image that the template can fit
    for (int x = 0; x <= size[0] - template_height; ++x) 
    {
       for (int y = 0; y <= size[1] - template_width; ++y)
        {
            // Create a subregion of the image corresponding to the current position
            unsigned char subregion[template_height][template_width];
            for (int i = 0; i < template_height; ++i) 
            {
                for (int j = 0; j < template_width; ++j) 
                {
                    subregion[i][j] = image[x + i][y + j];
                }
            }

            // image mean and std
            double region_mean, region_std;
            mean_and_std(subregion, template_height, template_width, &region_mean, &region_std);

            // Compute normalized cross-correlation for the current region
            ncc_array[x][y] = ncc(subregion, template, template_height, template_width, region_mean, region_std, template_mean, template_std);
            
            // Keep track of min and max values, getting a range of [ncc_min, ncc_max]
            if (ncc_array[x][y] > ncc_max) ncc_max = ncc_array[x][y];
            if (ncc_array[x][y] < ncc_min) ncc_min = ncc_array[x][y];
        }
    }

    // Normalize the NCC values based on the global min/max found
    // Range goes from [min, max] -> [0, 255]
    fprintf(logfile, "MAX(%lf) : MIN(%lf)\n", ncc_max, ncc_min);
    for (int x = 0; x < size[0] - template_height; x++) 
    {
        for (int y = 0; y < size[1] - template_width; y++)
        {
            double correlation = ncc_array[x][y];
            double scaled_correlation = ((correlation - ncc_min) / (ncc_max - ncc_min)) * 255.0;
            proc_img[x][y] = (unsigned char) (scaled_correlation);

            fprintf(logfile, "C(%lf) : NCC(%lf)\n", correlation, scaled_correlation);
        }
    }
    fclose(logfile);
}
