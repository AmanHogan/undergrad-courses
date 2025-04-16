/*
	Name: Aman Hogan-Bailey
	ID: 1001830469
*/

#include "bitmap.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

// Creating structure that will hold the parameters for the threads 
struct parameters 
{
	struct bitmap *bm;
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	double bit_max;
	int height_start;
	int height_end;
};

// Function computes the rispective pixels to bit map
void* compute_image(void *arg);

// Returns number of iterations at x and y
int iterations_at_point(double x, double y, int max);

// Function converts iteration to color
int iteration_to_color(int i, int max);


// Print statement shows commands that can be used during program
void show_help()
{
	printf("Use: mandel [options]\n");
	printf("Where options are:\n");
	printf("-m <max>    The maximum number of iterations per point. (default=1000)\n");
	printf("-n <threads> The total number of threads used to find Mandlebrot.");
	printf("-x <coord>  X coordinate of image center point. (default=0)\n");
	printf("-y <coord>  Y coordinate of image center point. (default=0)\n");
	printf("-s <scale>  Scale of the image in Mandlebrot coordinates. (default=4)\n");
	printf("-W <pixels> Width of the image in pixels. (default=500)\n");
	printf("-H <pixels> Height of the image in pixels. (default=500)\n");
	printf("-o <file>   Set output file. (default=mandel.bmp)\n");
	printf("-h          Show this help text.\n");
	printf("\nSome examples are:\n");
	printf("mandel -x -0.5 -y -0.5 -s 0.2\n");
	printf("mandel -x -.38 -y -.665 -s .05 -m 100\n");
	printf("mandel -x 0.286932 -y 0.014287 -s .0005 -m 1000\n\n");
}

int main(int argc, char *argv[])
{
	// Structure keeps time the program has run in microseconds
	struct timeval begin_time;
	struct timeval end_time;
	
	// Function gets the number of seconds since 1970
	gettimeofday(&begin_time, NULL );

	// Defining the name of the output file
	const char *outfile = "mandel.bmp";
	
	// Centering grid for image
	double xcenter = 0;
	double ycenter = 0;
	double scale = 4;
	
	// Intitializing default values for bitmap image width and height
	int image_width = 500;
	int image_height = 500;
	int max = 1000;
	
	// Initializing the number of threads and the amount of pixels each thread will be responsible
	// for
	int total_threads = 1;
	int height_increment = 1;
	
	// Variable will store commands
	char c;
	
	// Get the respective values following the command stored in 'c' 
	while((c = getopt(argc, argv, "x:y:s:W:H:m:o:n:h"))!= -1) 
	{
		switch(c) 
		{
			case 'x':
				xcenter = atof(optarg);
				break;
			case 'y':
				ycenter = atof(optarg);
				break;
			case 's':
				scale = atof(optarg);
				break;
			case 'W':
				image_width = atoi(optarg);
				break;
			case 'H':
				image_height = atoi(optarg);
				break;
			case 'm':
				max = atoi(optarg);
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'n':
				total_threads = atoi(optarg);
				break;
			case 'h':
				show_help();
				exit(1);
				break;
		}
	}
	
	// If user entered '0' for number of threads, change back to 1 thread
	if(total_threads == 0)
	{
		total_threads = 1;
	}
	
	// Creating an array that will store threads 
	pthread_t tid[total_threads];
	
	// Creating strcut array that will store the parameters of threads
	struct parameters params[total_threads];
	
	// Formula calculates the amount of pixels a thread will be responsible for in the image
	height_increment = image_height / total_threads;
	
	// Displays image configuration
	printf("mandel: x=%lf y=%lf scale=%lf max=%d outfile=%s\n",xcenter,ycenter,scale,max,outfile);

	// Create a bitmap of the appropriate size
	struct bitmap *bm = bitmap_create(image_width,image_height);
	
	
	
	// For the number of threads, store the inputted values in the paramter structure
	// Use the paramter values to create threads
	// The created threads will compute their respctuive pixels
	int i;
	for(i = 0; i < total_threads; i++)
	{
		// Initialize values for parameters
		params[i].bm = bm;
		params[i].xmin = xcenter-scale;
		params[i].xmax = xcenter+scale;
		params[i].ymin = ycenter-scale;
		params[i].ymax = ycenter+scale;
		params[i].bit_max = max;
		
		// If this is the first paramter, have it responsible for
		// pixel 0 to the pixel increment. EX: [0 to 400]
		if(i == 0) 
		{
			params[i].height_start = 0;
			params[i].height_end = height_increment;
		}

		// Set the start value of current thread to the end value of previous thread
		// Set the end value of current thread equal to previous thread plus
		// the increment value
		else 
		{
			params[i].height_start = params[i-1].height_end;
			params[i].height_end = params[i-1].height_end + height_increment;
			
		}
		
		// Create thread and compute the pixels that the thread is responsible for
		pthread_create(&tid[i], NULL, compute_image, (void *) &params[i]);
	}
	
	
	// For each thread have them join back to original thread
	for(i = 0; i < total_threads; i++ )
	{ 
		pthread_join(tid[i], NULL);
	}

	// Save the image in the stated file.
	// If the image cannot be saved, print error image
	if(!bitmap_save(bm,outfile)) 
	{
		fprintf(stderr,"mandel: couldn't write to %s: %s\n", outfile, strerror(errno));
		return 1;
	}

	// get number of seconds since 1970
	gettimeofday(&end_time, NULL );
	
	// Subtract time calculated from at end of program from begining of program
	double time_to_execute = ( end_time.tv_sec * 1000000 + end_time.tv_usec ) - ( begin_time.tv_sec * 1000000 + begin_time.tv_usec );

	// Print the number of seconds
	printf("This code took %lf seconds to execute\n", time_to_execute / 1000000.00000);
	
	return 0;
}


// Compute an entire Mandelbrot image, writing each point to the given bitmap.
// Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to "max"
void* compute_image(void *arg)
{
	int i;
	int j;
	
	// Store passed in value into a new struct variable 
	struct parameters* params = (struct parameters* ) arg;

	int width = bitmap_width(params->bm);
	int height = bitmap_height(params->bm);

	// For every pixel in the image...
	for(i = params->height_start; i < params->height_end; i++) 
	{
		for(j = 0;j < width; j++) 
		{

			double x = params->xmin + i*(params->xmax-params->xmin)/width;
			double y = params->ymin + j*(params->ymax-params->ymin)/height;
			int iters = iterations_at_point(x,y,params->bit_max);

			bitmap_set(params->bm,i,j,iters);
		}
	}

	return NULL;
}


// Return the number of iterations at point x, y
// in the Mandelbrot space, up to a maximum of max.

int iterations_at_point(double x, double y, int max)
{
	double x0 = x;
	double y0 = y;
	int iter = 0;

	while( (x*x + y*y <= 4) && iter < max ) 
	{
		double xt = x*x - y*y + x0;
		double yt = 2*x*y + y0;

		x = xt;
		y = yt;
		iter++;
	}

	return iteration_to_color(iter, max);
}

// Convert a iteration number to an RGBA color
// Here, we just scale to gray with a maximum of imax
// Modify this function to make more interesting colors

int iteration_to_color(int i, int max )
{
	int gray = 255*i/max;
	
	return MAKE_RGBA(gray, gray, gray, 0);
}
