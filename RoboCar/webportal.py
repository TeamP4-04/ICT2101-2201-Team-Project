from flask import Flask, render_template, url_for, request
from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField
from flask_sqlalchemy import SQLAlchemy


app = Flask(__name__)
#app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///Robocar.db'
#db = SQLAlchemy(app)

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)

class Logs(db.Model):
    logID = db.Column(db.Integer, primary_key=True)
    stageID = db.Column(db.Integer, nullable=False)
    commands = db.Column(db.Text, nullable=False)
    
    def __init__(self, stageID, commands):
        self.stageID = stageID
        self.commands = commands

    
class CarInformation(db.Model):
    carInformationID = db.Column(db.Integer, primary_key=True)
    distance_travelled = db.Column(db.Text, nullable=False)
    rotation = db.Column(db.Text, nullable=False)
    acceleration = db.Column(db.Text, nullable=False)
    time_spent = db.Column(db.Text, nullable=False)
    obstacle_position = db.Column(db.Text, nullable=False)
    car_point = db.Column(db.Text, nullable=False)

    
class Tutorial(db.Model):
    tutorialID = db.Column(db.Integer, primary_key=True)
    tutorialName = db.Column(db.Text, nullable=False)
    tutorialOverview = db.Column(db.Text, nullable=False)
    tutorialVideo = db.Column(db.Text, nullable=False)
    
class Configuration(db.Model):
    configurationID = db.Column(db.Integer, primary_key=True)
    max_speed = db.Column(db.Text, nullable=False)
    rotation_speed = db.Column(db.Text, nullable=False)
    object_detection_range = db.Column(db.Text, nullable=False)

#class ConfigForm(FlaskForm):
#    MaxSpeed = IntegerField('Maximum Speed of Robotic Car')
#    RotationSpeed = IntegerField('Rotation Speed of Robotic Car')
#    ObstacleDistance = IntegerField('Obstacle Distance')
#    submit = SubmitField('Submit')

@app.route("/", methods=["POST", "GET"])
def home():
    if request.method == "POST":
        commands = request.get_data()
        logs = Logs(1,commands)
        db.session.add(logs)
        db.session.commit()
        print(commands)

        return render_template('main.html', title='Main')
    else:    
        return render_template('main.html', title='Main')

@app.route("/logs")
def logs():
    return render_template('logs.html', title='Logs')

@app.route("/tutorials")
def tutorials():
    return render_template('tutorials.html', title='Tutorials')
    
@app.route("/tutorial1")
def tutorialdetails():
    return render_template('tutorial1.html', title='Tutorial1')
    
#@app.route("/configuration", methods=["GET", "POST"])
#def configuration():
#    form = ConfigForm() 
#    return render_template('configuration.html', form=form, title='Configuration')
    

if __name__ == '__main__':
    app.run(debug=True)