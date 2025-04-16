#!/bin/bash

# Define the program name
PROGRAM="./3dmpi"

# Define configurations
configs=(
    "1 1 1"   # Configuration a: MPIX = 1, MPIY = 1, MPIZ = 1
    "2 2 2"   # Configuration b: MPIX = 2, MPIY = 2, MPIZ = 2
    "2 5 5"   # Configuration c: MPIX = 2, MPIY = 5, MPIZ = 5
)

# Define process counts
process_counts=(1 8 50)

# Compile the program first
mpicc 3dmpi.c -o "$PROGRAM" -lm $config 2>/dev/null
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Run each configuration
for i in "${!configs[@]}"; do
    config="${configs[i]}"
    process_count="${process_counts[i]}"
    
    echo "Running configuration: MPIX=${config}"
    echo "Using ${process_count} processes"
    
    # Run the program with the specified number of processes and configuration
    mpirun -n "$process_count" "$PROGRAM" $config

    echo "-------------------------------------------------------"
done
