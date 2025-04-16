import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Load the CSV file into a pandas DataFrame
df = pd.read_csv("mpi_omp_results.csv", header=None, names=["Runtime", "Error", "nprocs"])

# Convert the columns to the correct data types
df["Runtime"] = pd.to_numeric(df["Runtime"], errors='coerce')
df["Error"] = pd.to_numeric(df["Error"], errors='coerce')
df["nprocs"] = pd.to_numeric(df["nprocs"], errors='coerce')

# Drop any rows with NaN values (in case conversion failed)
df.dropna(inplace=True)


# Step 2: Extract relevant data
runtimes = df["Runtime"]
nprocs = df["nprocs"]

print(runtimes)
print(nprocs)

# # Step 3: Calculate the ideal (perfect) scaling line
# # Ideal runtime for n processors = runtime with 1 processor / n
ideal_runtimes = runtimes / nprocs

print(ideal_runtimes)

# # Step 4: Calculate scaling efficiency
scaling_efficiency = (ideal_runtimes / runtimes) * 100

print(scaling_efficiency)

# # Step 5: Print the scaling efficiency
print("Scaling Efficiency:")
for idx, row in df.iterrows():
    print(f"Processors: {row['nprocs']}, Actual Runtime: {row['Runtime']}s, "
          f"Ideal Runtime: {ideal_runtimes[idx]:.3f}s, Efficiency: {scaling_efficiency[idx]:.2f}%")

# Step 6: Plot the results
plt.figure(figsize=(10, 6))
plt.plot(nprocs, runtimes, 'o-', label='Actual Runtime')
plt.plot(nprocs, ideal_runtimes, 'x--', label='Ideal (Perfect) Scaling')

plt.xlabel('Number of Processes')
plt.ylabel('Runtime (seconds)')
plt.title('Strong Scaling Performance')
plt.legend()
plt.grid(True)
plt.xticks(nprocs)
plt.savefig('results.png')
