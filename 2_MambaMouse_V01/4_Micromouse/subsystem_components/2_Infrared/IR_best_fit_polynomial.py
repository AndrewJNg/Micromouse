import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


INPUT_FILE = "sensor_data.csv"


# =========================
# Load CSV
# =========================

df = pd.read_csv(INPUT_FILE)

distance = df["CM"].to_numpy()

reading_left = df["reading Left"].to_numpy()
reading_right = df["reading Right"].to_numpy()


# =========================
# Polynomial fitting
# =========================

def fit_sensor(reading, distance, degree=3):

    # Physical input:
    # sensor reading

    # Transform reading for fitting
    x = np.log10(reading)

    # Fit polynomial
    coefficients = np.polyfit(
        x,
        distance,
        degree
    )

    # Calculate fitted distance
    fitted_distance = np.polyval(
        coefficients,
        x
    )

    # Calculate R²
    ss_res = np.sum(
        (distance - fitted_distance) ** 2
    )

    ss_tot = np.sum(
        (distance - np.mean(distance)) ** 2
    )

    r_squared = 1 - ss_res / ss_tot

    return coefficients, r_squared, fitted_distance


# =========================
# Fit Left
# =========================

coeff_left, r2_left, fitted_left = fit_sensor(
    reading_left,
    distance,
    degree=3
)


# =========================
# Fit Right
# =========================

coeff_right, r2_right, fitted_right = fit_sensor(
    reading_right,
    distance,
    degree=3
)


# =========================
# Print results
# =========================

print("\n===== Calibration Results =====")

print("\nLEFT SENSOR")
print(f"R² = {r2_left:.6f}")

print("Coefficients:")
for i, coefficient in enumerate(coeff_left):
    print(f"c{i} = {coefficient:.10f}")


print("\nRIGHT SENSOR")
print(f"R² = {r2_right:.6f}")

print("Coefficients:")
for i, coefficient in enumerate(coeff_right):
    print(f"c{i} = {coefficient:.10f}")


# =========================
# Plot Left
# =========================

plt.figure()

plt.scatter(
    reading_left,
    distance,
    label="Measured"
)

# Sensor reading is still the X-axis
reading_curve = np.linspace(
    min(reading_left),
    max(reading_left),
    500
)

# Transform reading for polynomial
x_curve = np.log10(reading_curve)

# Polynomial output = distance
distance_curve = np.polyval(
    coeff_left,
    x_curve
)

plt.plot(
    reading_curve,
    distance_curve,
    label="Polynomial fit"
)

plt.xlabel("Sensor Reading (Input)")
plt.ylabel("Distance (cm) (Output)")
plt.title("Left IR Sensor Calibration")

plt.legend()
plt.grid()

plt.show()


# =========================
# Plot Right
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

x_curve = np.log10(reading_curve)

distance_curve = np.polyval(
    coeff_right,
    x_curve
)

plt.plot(
    reading_curve,
    distance_curve,
    label="Polynomial fit"
)

plt.xlabel("Sensor Reading (Input)")
plt.ylabel("Distance (cm) (Output)")
plt.title("Right IR Sensor Calibration")

plt.legend()
plt.grid()

plt.show()