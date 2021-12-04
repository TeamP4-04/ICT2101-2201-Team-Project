from tkinter.constants import DISABLED, NORMAL
import serial
import time
import tkinter as tk

msp432 = serial.Serial('/dev/cu.usbmodemM43210051', 9600)

#read data from msp432
def readData():
    reading = True
    my_val = ''
    myString = []
    while reading:
        x = msp432.read()
        decodedx = x.decode()
        if decodedx != '/':
            myString.append(decodedx)
        else:
            my_val = ''.join(myString)
            #print(my_val)
            myString = []
            reading = False
    return my_val

while True:

    print("Left wheel rpm is: " + readData())
    print("Left wheel speed is: " + readData())

