import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# ============================================================
# SETTINGS
# ============================================================

filename = "speed_data.csv"

time_column = "Time"
speed_column = "Speed"


# ============================================================
# LOAD DATA
# ============================================================

data = pd.read_csv(filename, sep=r"\s+")

time_ms = data[time_column].to_numpy(dtype=float)
speed = data[speed_column].to_numpy(dtype=float)

# Convert milliseconds to seconds
time = time_ms / 1000.0

# Remove invalid values
valid = np.isfinite(time) & np.isfinite(speed)

time = time[valid]
speed = speed[valid]

# Sort according to time
index = np.argsort(time)

time = time[index]
speed = speed[index]


# ============================================================
# RESAMPLE TO UNIFORM TIME INTERVAL
# ============================================================

# Original time differences
dt_original = np.diff(time)

# Use median sampling interval
dt = np.median(dt_original)

print("Median sampling interval:", dt, "seconds")
print("Approximate sampling frequency:", 1 / dt, "Hz")

# Create uniformly spaced time vector
time_uniform = np.arange(
    time[0],
    time[-1],
    dt
)

# Interpolate speed onto uniform time grid
speed_uniform = np.interp(
    time_uniform,
    time,
    speed
)


# ============================================================
# REMOVE MEAN SPEED
# ============================================================

speed_detrended = speed_uniform - np.mean(speed_uniform)


# ============================================================
# FFT
# ============================================================

N = len(speed_detrended)

fft_result = np.fft.rfft(speed_detrended)

frequencies = np.fft.rfftfreq(
    N,
    d=dt
)

# Magnitude
magnitude = np.abs(fft_result) / N

# Correct amplitude because we only use positive frequencies
if N > 1:
    magnitude[1:-1] *= 2


# ============================================================
# FIND DOMINANT FREQUENCIES
# ============================================================

# Ignore 0 Hz
magnitude_no_dc = magnitude.copy()
magnitude_no_dc[0] = 0

# Sort by magnitude
peak_indices = np.argsort(magnitude_no_dc)[::-1]

print("\n==============================")
print("DOMINANT FREQUENCIES")
print("==============================")

for i in peak_indices[:10]:

    print(
        f"{frequencies[i]:8.3f} Hz"
        f"    Magnitude = {magnitude[i]:.3f}"
    )


# ============================================================
# PLOT SPEED DATA
# ============================================================

plt.figure(figsize=(10, 5))

plt.plot(
    time,
    speed,
    label="Original data"
)

plt.plot(
    time_uniform,
    speed_uniform,
    label="Resampled data"
)

plt.xlabel("Time (s)")
plt.ylabel("Speed")
plt.title("Speed vs Time")

plt.legend()
plt.grid()

plt.show()


# ============================================================
# PLOT FFT
# ============================================================

plt.figure(figsize=(10, 5))

plt.plot(
    frequencies,
    magnitude
)

plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("Speed FFT")

plt.grid()

plt.show()