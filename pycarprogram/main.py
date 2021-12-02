from tkinter.constants import DISABLED, NORMAL
import serial
import time
import tkinter as tk

window=tk.Tk()
window.geometry('400x300')
window.configure(background="#5f734c")
window.title("MSP432 - CAR CTRL")
opened = True
msp432 = serial.Serial('/dev/cu.usbmodemM43210051', 9600)

mvt_label = tk.Label(window)
transm_label = tk.Label(window)
eng_status = tk.Label(window)
power_level_lbl = tk.Label(window)
power_level = 5

def key_pressed(event):
    global mvt_label

    mvt_label.destroy()
    try:
        #forward
        if event.char == 'w':
            msp432.write(b'w')
            mvt_label=tk.Label(window,text="MOVING FORWARD")
        
        #left
        if event.char == 'a':
            msp432.write(b'a')
            mvt_label=tk.Label(window,text="MOVING LEFT")
            
        #reverse
        if event.char == 's':
            msp432.write(b'r')
            mvt_label=tk.Label(window,text="REVERSING")
        #right
        if event.char == 'd':
            msp432.write(b'd')
            mvt_label=tk.Label(window,text="MOVING RIGHT")
        
        mvt_label.grid(row=2, column=1)
    except:
        mvt_label=tk.Label(window,text="NO SUCH COMMAND")
        mvt_label.grid(row=2, column=1)
    

    #read data from msp432
    reading = True
    myString = []
    while reading:
        
        x = msp432.read()
        decodedx = x.decode()
        if decodedx != '/':
            myString.append(decodedx)
        else:
            reading = False
    #print(''.join(myString))

def key_release(event):
    global mvt_label
    mvt_label.destroy()
    mvt_label=tk.Label(window,text="STOPPED")
    mvt_label.grid(row=2, column=1)

    msp432.write(b's')

def autoTransmission():
    global transm_label
    transm_label.destroy()
    transm_label=tk.Label(window,text="Auto")
    transm_label.grid(row=1, column=2)
    auto_button['state'] = DISABLED
    manual_button['state'] = NORMAL

    msp432.write(b'u')
    
def manualTransmission():
    global transm_label
    transm_label.destroy()
    transm_label=tk.Label(window,text="Manual")
    transm_label.grid(row=1, column=2)
    auto_button['state'] = NORMAL
    manual_button['state'] = DISABLED
    
    msp432.write(b'm')

def startEngine():
    global eng_status
    global transm_label
    global power_level_lbl
    global power_level
    eng_status.destroy()
    transm_label.destroy()

    eng_status=tk.Label(window,text="Engine Started")
    transm_label=tk.Label(window,text="Manual")
    power_level_lbl=tk.Label(window,text=f"POWER LEVEL: {power_level}")

    eng_status.grid(row=1, column=1)
    transm_label.grid(row=1, column=2)
    power_level_lbl.grid(row=2, column=2)

    engstart_button['state'] = DISABLED
    engstop_button['state'] = NORMAL
    auto_button['state'] = NORMAL
    manual_button['state'] = DISABLED
    increase_power_button['state'] = DISABLED
    decrease_power_button['state'] = NORMAL

    msp432.write(b'o')

def stopEngine():
    global eng_status
    eng_status.destroy()
    eng_status=tk.Label(window,text="Engine Stopped")
    eng_status.grid(row=1, column=1)
    
    engstart_button['state'] = NORMAL
    engstop_button['state'] = DISABLED
    auto_button['state'] = DISABLED
    manual_button['state'] = DISABLED
    increase_power_button['state'] = DISABLED
    decrease_power_button['state'] = DISABLED

    msp432.write(b'p')

def increase_power():
    global power_level
    global power_level_lbl

    if power_level != 5:
        power_level += 1
        power_level_lbl.destroy()
        power_level_lbl=tk.Label(window,text=f"POWER LEVEL: {power_level}")
        power_level_lbl.grid(row=2, column=2)

        msp432.write(b'+')
    if power_level == 5:
        increase_power_button['state'] = DISABLED
        decrease_power_button['state'] = NORMAL

def decrease_power():
    global power_level
    global power_level_lbl
    
    if power_level != 1:
        power_level -= 1
        msp432.write(b'-')
        power_level_lbl.destroy()
        power_level_lbl=tk.Label(window,text=f"POWER LEVEL: {power_level}")
        power_level_lbl.grid(row=2, column=2)

    if power_level == 1:
        increase_power_button['state'] = NORMAL
        decrease_power_button['state'] = DISABLED

def quit():
    print("\n** END OF PROGRAM **")
    msp432.close()
    window.destroy()
    
mvt_label=tk.Label(window,text="CONTROLS: WASD", padx=5,pady=5)
eng_status=tk.Label(window,text="Engine Stopped")
mvt_label.grid(row=2, column=1)
eng_status.grid(row=1, column=1)

### COLUMN 3 ###
auto_button = tk.Button(window, text="AUTO", command=autoTransmission, font=("Arial", 13))
auto_button.grid(row=1, column=3, padx=5, pady=10)

manual_button = tk.Button(window, text="MANUAL", command=manualTransmission, font=("Arial", 13))
manual_button.grid(row=2, column=3, padx=5, pady=10)

increase_power_button = tk.Button(window, text="+ POWER", command=increase_power, font=("Arial", 13))
increase_power_button.grid(row=3, column=3, padx=5, pady=10)

decrease_power_button = tk.Button(window, text="- POWER", command=decrease_power, font=("Arial", 13))
decrease_power_button.grid(row=4, column=3, padx=5, pady=10)

quit_button = tk.Button(window, text="QUIT", command=quit, font=("Arial", 13))
quit_button.grid(row=5, column=3, padx=5, pady=10)

#### ROW 3 ###
engstart_button = tk.Button(window, text="ENGINE START", command=startEngine, font=("Arial", 13))
engstart_button.grid(row=5, column=1, padx=5, pady=10)

engstop_button = tk.Button(window, text="ENGINE STOP", command=stopEngine, font=("Arial", 13))
engstop_button.grid(row=5, column=2, padx=5, pady=10)

engstart_button['state'] = NORMAL
engstop_button['state'] = DISABLED
auto_button['state'] = DISABLED
manual_button['state'] = DISABLED
increase_power_button['state'] = DISABLED
decrease_power_button['state'] = DISABLED

window.bind("<Key>",key_pressed)
window.bind("<KeyRelease>",key_release)
window.mainloop()