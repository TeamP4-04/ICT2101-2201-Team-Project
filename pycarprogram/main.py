import serial
import time
import tkinter as tk

window = tk.Tk()
window.configure(background="gray14")
window.title("MSP432 - CAR CTRL")

msp432 = serial.Serial('/dev/cu.usbmodemM43210051', 9600)


def car_control():
    print(">>> CAR CTRL - PROGRAM <<<\n")
    

    def FORWARD():
        print(">FORWARD<")
        msp432.write(b'w')

    def LEFT():
        print(">LEFT<")
        msp432.write(b'a')

    def RIGHT():
        print(">RIGHT<")
        msp432.write(b'd')

    def REVERSE():
        print(">REVERSE<")
        msp432.write(b'r')

    def STOP():
        print(">STOP<")
        msp432.write(b's')

    def quit():
        print("\n** END OF PROGRAM **")
        msp432.write(b'q')
        msp432.close()
        window.destroy()

    b1 = tk.Button(window, text="FORWARD", command=FORWARD, bg="lime green", fg="gray7", font=("Arial", 20))
    b2 = tk.Button(window, text="LEFT", command=LEFT, bg="firebrick2", fg="gray7", font=("Arial", 20))
    b3 = tk.Button(window, text="RIGHT", command=RIGHT, bg="dodger blue", fg="gray7", font=("Arial", 20))
    b4 = tk.Button(window, text="STOP", command=STOP, bg="MediumOrchid3", fg="gray7", font=("Arial", 20))
    b5 = tk.Button(window, text="EXIT", command=quit, bg="gold", fg="gray7", font=("Arial", 20))
    b6 = tk.Button(window, text="REVERSE", command=REVERSE, bg="MediumOrchid3", fg="gray7", font=("Arial", 20))

    b1.grid(row=1, column=2, padx=5, pady=10)
    b2.grid(row=2, column=1, padx=5, pady=10)
    b3.grid(row=2, column=3, padx=5, pady=10)
    b4.grid(row=3, column=1, padx=5, pady=10)
    b5.grid(row=3, column=2, padx=5, pady=10)
    b6.grid(row=2, column=2, padx=5, pady=10)

    
    window.mainloop()


time.sleep(2)
car_control()