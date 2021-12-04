from flask import Flask, render_template, url_for, request
from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField
import sqlite3 as sql
import tutorial as tut

app = Flask(__name__)


@app.route("/dashboard", methods=["POST", "GET"])
def home():
    conn=sql.connect("test.db")
    conn.row_factory = sql.Row
    cur=conn.cursor()
    cur.execute("select distance_travelled, rotation, acceleration, obstacle_distance from CarInformation where carInformationID = abs(random()) % (3 - 1) + 1")
    row=cur.fetchone()
    if request.method == "POST":
        connInsert=sql.connect("test.db")
        connInsert.row_factory = sql.Row
        curInsert=connInsert.cursor()
        
        commands = request.get_data()
        commands = commands.decode()
        curInsert.execute("insert into Logs (stageID, commands) values (?, ?)", (1, commands))
        connInsert.commit()
        connInsert.close()
        conn.close()
        return render_template('main.html', title='Main', row = row)
    else:  
        conn.close()    
        return render_template('main.html', title='Main', row = row)



@app.route("/logs")
def logs():
    conn=sql.connect("test.db")
    conn.row_factory = sql.Row

    cur=conn.cursor()
    cur.execute("select logID from Logs order by logID DESC")

    rows=cur.fetchall()
    conn.close()
    return render_template('logs.html', title='Logs', rows = rows)


@app.route("/logs/log<logID>")
def logdetails(logID):
    conn=sql.connect("test.db")
    conn.row_factory = sql.Row

    cur=conn.cursor()
    cur.execute("select logID, commands, stageID, distance_travelled, rotation, obstacle_distance, time_spent from Logs, CarInformation where carInformationID = abs(random()) % (3 - 1) + 1 and logID = ?", (logID))

    rows=cur.fetchall()
    conn.close()
    return render_template('log1.html', title='Logs' + logID, rows = rows)


# Main Tutorial Page
@app.route("/")
def tutorials():
    conn = sql.connect("test.db")
    conn.row_factory = sql.Row

    cur = conn.cursor()
    cur.execute("select * from Tutorial order by tutorialID")

    rows = cur.fetchall()
    conn.close()
    return render_template('tutorials.html', title='Tutorials', rows=rows)

# Individual Tutorial Page
@app.route("/tutorial/<tutorialID>")
def tutorialdetails(tutorialID):
    conn = sql.connect("test.db")
    conn.row_factory = sql.Row

    cur = conn.cursor()
    cur.execute("select * from Tutorial where tutorialID = ?", tutorialID)
    rows = cur.fetchall()
    cur.execute("SELECT * FROM Tutorial WHERE tutorialID=(SELECT max(tutorialID) FROM Tutorial)")
    last_id = cur.fetchone()
    conn.close()
    return render_template('tutorial1.html', title='Tutorial ' + tutorialID, rows=rows, last_id=last_id)


if __name__ == '__main__':
    app.run(debug=True)
