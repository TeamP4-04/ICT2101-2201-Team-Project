from flask import Flask, render_template, url_for, request

from flask_sqlalchemy import SQLAlchemy

from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField

from sqlalchemy.engine import create_engine
import sqlite3 as sql

import tutorial as tut

app = Flask(__name__)

db = SQLAlchemy(app)


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
    return render_template('logs.html', title='Logs')


# Main Tutorial Page
@app.route("/tutorials")
def tutorials():
    conn = sql.connect("Robocar.db")
    # conn=db
    conn.row_factory = sql.Row

    cur = conn.cursor()
    cur.execute("select * from Tutorial order by tutorialID")

    rows = cur.fetchall()
    print(rows)
    return render_template('tutorials.html', title='Tutorials', rows=rows)

# Individual Tutorial Page
@app.route("/tutorial/<tutorialID>")
def tutorialdetails(tutorialID):
    conn = sql.connect("Robocar.db")
    # conn=db
    conn.row_factory = sql.Row

    cur = conn.cursor()
    cur.execute("select * from Tutorial where tutorialID = ?", tutorialID)
    rows = cur.fetchall()
    cur.execute("SELECT * FROM Tutorial WHERE tutorialID=(SELECT max(tutorialID) FROM Tutorial)")
    # cur.execute("select max(tutorialID) from Tutorial")
    last_id = cur.fetchone()

    return render_template('tutorial1.html', title='Tutorial ' + tutorialID, rows=rows, last_id=last_id)

@app.route("/configuration", methods=["GET", "POST"])
def configuration():
    form = ConfigForm()
    return render_template('configuration.html', form=form, title='Configuration')


# @app.route("/contact", methods=["GET", "POST"])
# def contact():
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
