import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


# =========================
# Configuration
# =========================

# INPUT_FILE = "sensor_data.csv"
INPUT_FILE = "sensor_data_5_degree.csv"




# =========================
# Load CSV
# =========================

df = pd.read_csv(INPUT_FILE)

distance = df["CM"].to_numpy()

reading_left = df["reading Left"].to_numpy()
reading_right = df["reading Right"].to_numpy()


# =========================
# Fit sensor
# =========================

def fit_sensor(reading, distance):
    """
    Fit:

        distance = a / log10(reading) - b

    by transforming it into:

        distance = a*x - b

    where:

        x = 1 / log10(reading)
    """

    x = 1 / np.log10(reading)

    # Linear fit:
    # distance = slope*x + intercept
    slope, intercept = np.polyfit(x, distance, 1)

    a = slope
    b = -intercept

    # Calculate fitted distance
    fitted_distance = a / np.log10(reading) - b

    # R^2
    ss_res = np.sum((distance - fitted_distance) ** 2)
    ss_tot = np.sum((distance - np.mean(distance)) ** 2)

    r_squared = 1 - (ss_res / ss_tot)

    return a, b, r_squared, fitted_distance


# =========================
# Fit sensor
# =========================

a_left, b_left, r2_left, fitted_left = fit_sensor(reading_left,distance)
a_right, b_right, r2_right, fitted_right = fit_sensor(reading_right,distance)


# =========================
# Print results
# =========================

print("\n===== Calibration Results =====")

print("\nLEFT SENSOR")
print(f"a = {a_left:.6f}")
print(f"b = {b_left:.6f}")
print(f"R² = {r2_left:.6f}")

print("\nRIGHT SENSOR")
print(f"a = {a_right:.6f}")
print(f"b = {b_right:.6f}")
print(f"R² = {r2_right:.6f}")


# =========================
# Generate calibration CSV
# =========================

output_df = pd.DataFrame({
    "CM": distance,

    "reading Left": reading_left,
    "fitted Left": fitted_left,
    "error Left": fitted_left - distance,

    "reading Right": reading_right,
    "fitted Right": fitted_right,
    "error Right": fitted_right - distance
})

output_df.to_csv("calibration_results.csv", index=False)


# =========================
# Plot Left sensor
# =========================

plt.figure()

plt.scatter(
    reading_left,
    distance,
    label="Measured"
)

# Generate smooth curve
reading_curve = np.linspace(
    min(reading_left),
    max(reading_left),
    500
)

distance_curve = (
    a_left / np.log10(reading_curve)
    - b_left
)

plt.plot(
    reading_curve,
    distance_curve,
    label="Best fit"
)

plt.xlabel("Sensor Reading")
plt.ylabel("Distance (cm)")
plt.title("Left IR Sensor Calibration")
plt.legend()
plt.grid()

plt.show()


# =========================
# Plot Right sensor
# =========================

plt.figure()

plt.scatter(
    reading_right,
    distance,
    label="Measured"
)

reading_curve = np.linspace(
    min(reading_right),
    max(reading_right),
    500
)

distance_curve = (
    a_right / np.log10(reading_curve)
    - b_right
)

plt.plot(
    reading_curve,
    distance_curve,
    label="Best fit"
)

plt.xlabel("Sensor Reading")
plt.ylabel("Distance (cm)")
plt.title("Right IR Sensor Calibration")
plt.legend()
plt.grid()

plt.show()