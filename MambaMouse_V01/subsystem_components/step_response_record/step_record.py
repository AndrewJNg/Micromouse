import serial
import time
import csv

# Configure the serial connection
ser = serial.Serial('COM5', 115200, timeout=1)  # Replace 'COM_PORT' with the Arduino's COM port

# Open a CSV file to save data
with open('step_half.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp (ms)', 'Left Motor Position (mm)', 'Right Motor Position (mm)',
                     'Left Motor Delta (mm)', 'Right Motor Delta (mm)'])

    prev_left = None
    prev_right = None
    start_time = time.time()

    while True:
        try:
            # Read data line from serial
            line = ser.readline().decode('utf-8').strip()
            
            # Parse the line if it contains both left and right motor positions
            if line:
                data = line.split()
                if len(data) == 2:
                    # Convert string data to floats
                    left_position = float(data[0])
                    right_position = float(data[1])
                    
                    # Get the current timestamp
                    timestamp = int((time.time() - start_time) * 1000)  # milliseconds
                    
                    # Calculate the delta in position from the previous reading
                    left_delta = left_position - prev_left if prev_left is not None else 0
                    right_delta = right_position - prev_right if prev_right is not None else 0
                    
                    # Write data to CSV
                    writer.writerow([timestamp, left_position, right_position, left_delta, right_delta])
                    print(f"Timestamp: {timestamp} ms, Left: {left_position} mm, Right: {right_position} mm, "
                          f"Left Delta: {left_delta} mm, Right Delta: {right_delta} mm")

                    # Update previous position
                    prev_left = left_position
                    prev_right = right_position

                    # Wait 10 ms before reading again
                    time.sleep(0.01)
        except KeyboardInterrupt:
            print("Data recording stopped.")
            break