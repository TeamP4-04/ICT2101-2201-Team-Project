from flask import Flask, render_template, url_for, request
from sqlalchemy.engine import create_engine

from flask_sqlalchemy import SQLAlchemy

from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField

import sqlite3 as sql

app = Flask(__name__)
#app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///Robocar.db'
#db = SQLAlchemy(app)

class ConfigForm(FlaskForm):
    MaxSpeed = IntegerField('Maximum Speed of Robotic Car')
    RotationSpeed = IntegerField('Rotation Speed of Robotic Car')
    ObstacleDistance = IntegerField('Obstacle Distance')
    submit = SubmitField('Submit')

@app.route("/")

@app.route("/main")
def main():
    return render_template('main.html', title='Main')

@app.route("/logs")
def logs():
    conn=sql.connect("Robocar.db")
    #conn=db
    conn.row_factory = sql.Row

    cur=conn.cursor()
    cur.execute("select gameID, logID from logs_page order by gameID DESC, logID DESC")

    rows=cur.fetchall()
    return render_template('logs.html', title='Logs', rows = rows)

@app.route("/logs/game<gameID>/log<logID>")
def logdetails(gameID, logID):
    conn=sql.connect("Robocar.db")
    print(gameID)
    print(logID)
    #conn=db
    conn.row_factory = sql.Row

    cur=conn.cursor()
    cur.execute("select * from logs_page where gameID = ? and logID = ?", (gameID, logID))

    rows=cur.fetchall()
    print(rows)

    return render_template('log1.html', title='Game ' + gameID + ' Log ' + logID, rows = rows)


@app.route("/tutorials")
def tutorials():
    return render_template('tutorials.html', title='Tutorials')
    
@app.route("/tutorial1")
def tutorialdetails():
    return render_template('tutorial1.html', title='Tutorial1')
    
@app.route("/configuration", methods=["GET", "POST"])
def configuration():
    form = ConfigForm() 
    return render_template('configuration.html', form=form, title='Configuration')
    
    
#@app.route("/contact", methods=["GET", "POST"])
#def contact():
#    """Standard `contact` form."""
#    form = ContactForm()
#    if form.validate_on_submit():
#        return redirect(url_for("success"))
#    return render_template(
#        "contact.jinja2",
#        form=form,
#        template="form-template"
#    )

if __name__ == '__main__':
    app.run(debug=True)
