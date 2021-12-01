import serial
import time
import tkinter as tk

window=tk.Tk()
window.configure(background="gray14")
window.title("MSP432 - CAR CTRL")

msp432 = serial.Serial('/dev/cu.usbmodemM43210051', 9600)

def key_pressed(event):
    w=tk.Label(window,text="Key Pressed:"+event.char)
    w.place(x=20,y=90)

    if event.char == 'w':
        msp432.write(b'w')

    if event.char == 'a':
        msp432.write(b'a')

    if event.char == 's':
        msp432.write(b'r')

    if event.char == 'd':
        msp432.write(b'd')

    if event.char == 'e':
        msp432.write(b's')
    reading = True
    myString = []
    while reading:
        
        x = msp432.read()
        decodedx = x.decode()
        if decodedx != '/':
            myString.append(decodedx)
        else:
            reading = False
    print(''.join(myString))


window.bind("<Key>",key_pressed)
window.mainloop()