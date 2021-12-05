from flask import Flask, render_template, url_for, request, redirect, jsonify
import sqlite3 as sql
import tutorial as tut
import jinja2
import serial

#msp432 = serial.Serial('/dev/cu.usbmodemM43210051', 9600)
app = Flask(__name__)
my_val = 'Initial Value'

# @app.route('/update_mspvalues', methods = ["POST"])
# def readData():
#     reading = True
#     my_val = ''
#     myString = []
#     while reading:
#         x = msp432.read()
#         decodedx = x.decode()
#         if decodedx != '/':
#             myString.append(decodedx)
#         else:
#             my_val = ''.join(myString)
#             #print(my_val)
#             myString = []
#             reading = False
#             return jsonify('',render_template('mspvalue.html', mspval = my_val))

@app.route("/dashboard", methods=["POST", "GET"])
def dashboard():
    try:
        conn=sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row
        cur=conn.cursor()
        cur.execute("select distance_travelled, rotation, acceleration, obstacle_distance from CarInformation where carInformationID = abs(random()) % (3 - 1) + 1")
        row=cur.fetchone()
        
        if request.method == "POST":
            commands = request.get_data()
            commands = commands.decode()
        
            try:
                connInsert=sql.connect('file:test.db?mode=rw', uri=True)
                connInsert.row_factory = sql.Row
                curInsert=connInsert.cursor()
                    
                curInsert.execute("insert into Logs (stageID, commands) values (?, ?)", (1, commands))
                connInsert.commit()
                connInsert.close()
                conn.close()
                return render_template('main.html', title='Dashboard', row = row, mspval = my_val)
                
            except sql.Error as e:     
                conn.close()
                print(e)
                return render_template('main.html', title='Dashboard', row = row, mspval = my_val)
        else:  
            conn.close()    
            return render_template('main.html', title='Dashboard', row = row, mspval = my_val)
        
    except (sql.Error, jinja2.TemplateError) as e:
        return render_template('errors.html', title='Error', e=e)
    
    return render_template('errors.html', title='Error')
  
    
@app.route("/logs")
def logs():
    try:
        conn=sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row
        cur=conn.cursor()
        cur.execute("select logID from Logs order by logID DESC")

        rows=cur.fetchall()
        conn.close()
        return render_template('logs.html', title='Logs', rows = rows)
        
    except (sql.Error, jinja2.TemplateError) as e:
        return render_template('errors.html', title='Error', e=e)


@app.route("/logs/log<logID>")
def logdetails(logID):
    try:
        conn=sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row
        cur=conn.cursor()
        cur.execute("select logID, commands, stageID, distance_travelled, rotation, obstacle_distance, time_spent from Logs, CarInformation where carInformationID = abs(random()) % (3 - 1) + 1 and logID = ?", [logID])

        rows=cur.fetchall()
        conn.close()
        return render_template('log1.html', title='Logs' + logID, rows = rows)

    except (sql.Error, jinja2.TemplateError) as e:
        return render_template('errors.html', title='Error', e=e)

# Main Tutorial Page
@app.route("/")
def tutorials():
    try:
        conn = sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row

        cur = conn.cursor()
        cur.execute("select * from Tutorial order by tutorialID")

        rows = cur.fetchall()
        conn.close()
        return render_template('tutorials.html', title='Tutorials', rows=rows)
        
    except (sql.Error, jinja2.TemplateError) as e:
        return render_template('errors.html', title='Error', e=e)

# Individual Tutorial Page
@app.route("/tutorial/<tutorialID>")
def tutorialdetails(tutorialID):
    try:
        conn = sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row

        cur = conn.cursor()
        cur.execute("select * from Tutorial where tutorialID = ?", tutorialID)
        rows = cur.fetchall()
        cur.execute("SELECT * FROM Tutorial WHERE tutorialID=(SELECT max(tutorialID) FROM Tutorial)")
        last_id = cur.fetchone()
        conn.close()
        return render_template('tutorial1.html', title='Tutorial ' + tutorialID, rows=rows, last_id=last_id)
        
    except (sql.Error, jinja2.TemplateError) as e:
        return render_template('errors.html', title='Error', e=e)

# Configuration Page
@app.route("/configuration", methods=["POST", "GET"])
def configuration():
    if request.method == "POST":
        form = request.form
        maxSpd = form.get("max")
        rotSpd = form.get("rot")
        obsDist = form.get("obs")
   
        if not maxSpd and not rotSpd and not obsDist:
            return render_template('configuration.html', title='Configuration', validate = 1)
        elif float(maxSpd) > 50 or float(rotSpd) > 50:
            return render_template('configuration.html', title='Configuration', validate = 2)
        else:
            try:
                connInsert=sql.connect('file:test.db?mode=rw', uri=True)
                connInsert.row_factory = sql.Row
                curInsert=connInsert.cursor()
               
                curInsert.execute("insert into Configuration (max_speed, rotation_speed, object_detection_range) values (?, ?, ?)", (maxSpd,rotSpd,obsDist))
                connInsert.commit()
                connInsert.close()
                return render_template('configuration.html', title='Configuration', validate = 3)
                
            except (sql.Error, jinja2.TemplateError) as e:
                return render_template('errors.html', title='Error', e=e)
        
    return render_template('configuration.html', title='Configuration')
  

if __name__ == '__main__':
    app.run(debug=True)
