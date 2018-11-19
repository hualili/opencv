# the LSM303 accelerometer & magnetometer library.
# Will print the accelerometer & magnetometer X, Y, Z axis values every half
# second.
# Author: Liuting Chen    
# Note  : This code is from CTI One Corporation developed under Dr. Harry Li's 
#         technial guidance, and released for SJSU Dr. Li's Fall 2018 
#         CMPE 163 Class, for educational purpose only.  
# Status: tested 
#                         
# 
import time
import math
import socket

# Import the LSM303 module.
import Adafruit_LSM303

#set up the receiver IP address
#IP_ADDR = '192.168.1.27'
IP_ADDR = '192.168.2.3'
PORT = 3001
BUFFERSIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP_ADDR, PORT))

# Create a LSM303 instance.
lsm303 = Adafruit_LSM303.LSM303()
pi = 3.14159

# Alternatively you can specify the I2C bus with a bus parameter:
#lsm303 = Adafruit_LSM303.LSM303(busum=2)

print('Printing accelerometer & magnetometer X, Y, Z axis values, press Ctrl-C to quit...')
while True:
    # Read the X, Y, Z axis acceleration values and print them.
    accel = lsm303.read_accel()
    mag = lsm303.read_mag()
    # Grab the X, Y, Z components from the reading and print them out.
    accel_x, accel_y, accel_z = accel 
    mag_x, mag_y, mag_z = mag
    time_cur = int(round(time.time() * 1000000))
    time_str = str(time_cur)
    #print("the current time is:", time_str)
    #s.sendto(time_str.encode('utf-8'), (IP_ADDR, PORT))
    # Calculate the angle of the vector x, y
    heading_f = (math.atan2(mag_y, mag_x) * 180) / pi

    if heading_f < 0:
        heading_f = 360 + heading_f
    #print('Accel X={0}, Accel Y={1}, Accel Z={2}, Mag X={3}, Mag Y={4}, Mag Z={5}'.format(
         # accel_x, accel_y, accel_z, mag_x, mag_y, mag_z))
    heading_int = int(heading_f)
    heading_str = str(heading_int)
    complete_str=heading_str +" "+ time_str
    #s.sendto(heading_str.encode('utf-8'),(IP_ADDR, PORT))
    s.sendto(complete_str.encode('utf-8'),(IP_ADDR, PORT))
    print(complete_str)
    # Wait half a second and repeat.
   # time.sleep(0.5)
    data_recv = s.recv(1024)
    time_recv=int(round(time.time() * 1000000))
    print("RTT wifi : " +str(time_recv-time_cur))
    #print("--------------------the data received is : ", data_recv)
