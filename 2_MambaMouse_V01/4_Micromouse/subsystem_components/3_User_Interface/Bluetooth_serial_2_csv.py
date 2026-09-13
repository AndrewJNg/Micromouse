import serial
import csv

ser = serial.Serial("COM5", 115200)

filename = "serial_data2.csv"

try:
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)

        print("Recording serial data...")
        print("Press Ctrl+C to stop and save the CSV file.")

        while True:
            line = ser.readline().decode("utf-8", errors="replace").strip()

            if line:
                print(line)

                # Split serial data by TAB
                row = line.split("\t")

                # Write the row to CSV
                writer.writerow(row)

except KeyboardInterrupt:
    print("\nCtrl+C detected. Stopping recording...")

finally:
    ser.close()
    print(f"CSV file saved as: {filename}") 