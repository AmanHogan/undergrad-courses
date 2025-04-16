#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

// Column-major ordering for 3D: (i, j, k) -> i + j*(N+1) + k*(N+1)*(N+1)
#define I3D(i, j, k, N) ((i) + (j) * (N + 1) + (k) * (N + 1) * (N + 1))

void initialize(double *u, int N, double dx, double dy, double dz);
void time_step(double *u, double *u_new, int N, double dt, double dx2, double dy2, double dz2);
double compute_error(double *u, int N, double T, double dx, double dy, double dz);

int main() 
{
    double T = 1.0; // Final time
    int GRID_SIZES[] = {10, 20, 40}; // Grid sizes for 3D
    double CFL = 0.25; // CFL condition

    FILE *csv_file = fopen("heat_solver_3d.csv", "w");
    if (csv_file == NULL) 
    {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(csv_file, "Grid Size,Error\n");

    // For each grid size ...
    for (int k = 0; k < 3; k++) 
    {
        int GRID_SIZE = GRID_SIZES[k];
        double dx = PI / GRID_SIZE;
        double dy = PI / GRID_SIZE;
        double dz = PI / GRID_SIZE;
        double dx2 = dx * dx;
        double dy2 = dy * dy;
        double dz2 = dz * dz;
        double dt = CFL * dx2 / 3.0; // Time step size based on CFL condition

        // Ensure time stepping does not overshoot T
        int nsteps = (int)ceil(T / dt);
        dt = T / nsteps;

        // Allocate memory for the 3D grid
        double *u = (double *)malloc((GRID_SIZE + 1) * (GRID_SIZE + 1) * (GRID_SIZE + 1) * sizeof(double));
        double *u_new = (double *)malloc((GRID_SIZE + 1) * (GRID_SIZE + 1) * (GRID_SIZE + 1) * sizeof(double));
        initialize(u, GRID_SIZE, dx, dy, dz);

        // Time-stepping loop
        for (int t_step = 0; t_step < nsteps; t_step++)
        {
            time_step(u, u_new, GRID_SIZE, dt, dx2, dy2, dz2);
            double *tmp = u;
            u = u_new;
            u_new = tmp;
        }

        // Compute and log the error
        double error = compute_error(u, GRID_SIZE, T, dx, dy, dz);
        printf("Grid size N = %d, Error = %e\n", GRID_SIZE, error);
        fprintf(csv_file, "%d, %e\n", GRID_SIZE, error);

        // Free memory
        free(u);
        free(u_new);
    }

    fclose(csv_file);
    return 0;
}

/**
 * Initialize the grid using the initial condition:
 * u(x,y,z,t=0) = sin(x) * sin(y) * sin(z)
 */
void initialize(double *u, int N, double dx, double dy, double dz) 
{
    for (int i = 0; i <= N; i++) 
    {
        for (int j = 0; j <= N; j++) 
        {
            for (int k = 0; k <= N; k++) 
            {
                double x = i * dx;
                double y = j * dy;
                double z = k * dz;
                u[I3D(i, j, k, N)] = sin(x) * sin(y) * sin(z);
            }
        }
    }
}

/**
 * Apply the heat equation update at each time step for 3D u
 */
void time_step(double *u, double *u_new, int N, double dt, double dx2, double dy2, double dz2) 
{
    for (int i = 1; i < N; i++) 
    {
        for (int j = 1; j < N; j++) 
        {
            for (int k = 1; k < N; k++) 
            {
                u_new[I3D(i, j, k, N)] = u[I3D(i, j, k, N)] 
                    + dt/dx2 * (u[I3D(i+1, j, k, N)] - 2*u[I3D(i, j, k, N)] + u[I3D(i-1, j, k, N)])
                    + dt/dy2 * (u[I3D(i, j+1, k, N)] - 2*u[I3D(i, j, k, N)] + u[I3D(i, j-1, k, N)])
                    + dt/dz2 * (u[I3D(i, j, k+1, N)] - 2*u[I3D(i, j, k, N)] + u[I3D(i, j, k-1, N)]);
            }
        }
    }
}

/**
 * Calculate the error between the numerical solution and the exact solution
 */
double compute_error(double *u, int N, double T, double dx, double dy, double dz) 
{
    double diff = 0.0;
    for (int i = 0; i <= N; i++) 
    {
        for (int j = 0; j <= N; j++) 
        {
            for (int k = 0; k <= N; k++) 
            {
                double x = i * dx;
                double y = j * dy;
                double z = k * dz;
                double exact = exp(-3 * T) * sin(x) * sin(y) * sin(z);
                double error = u[I3D(i, j, k, N)] - exact;
                diff += error * error * dx * dy * dz;
            }
        }
    }
    return sqrt(diff);
}
