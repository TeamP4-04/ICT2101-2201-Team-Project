from flask import Flask, render_template, url_for, request
from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField
from flask_sqlalchemy import SQLAlchemy


app = Flask(__name__)
<<<<<<< Updated upstream
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///Robocar.db'
db = SQLAlchemy(app)
=======
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)

class Logs(db.Model):
    logID = db.Column(db.Integer, primary_key=True)
    gameID = db.Column(db.Integer, db.ForeignKey('Game.gameID'), nullable=False)
    carInformationID = db.Column(db.Integer, db.ForeignKey('CarInformation.carInformationID'), nullable=False)
    commandsExecuted = db.Column(db.Text, nullable=False)
    
    def __init__(self, logID, gameID, carsInformationID, commandsExecuted):
        self.logID = logID
        self.gameID = gameID
        self.carsInformationID = carsInformationID
        self.commandsExecuted = commandsExecuted

    
class Game(db.Model):
    gameID = db.Column(db.Integer, primary_key=True)
    stageID = db.Column(db.Integer, db.ForeignKey('Stage.stageID'), nullable=False)
    
    def __init__(self, gameID, stageID):
        self.gameID = gameID
        self.stageID = stageID
 
 
    
class Stage(db.Model):
    stageID = db.Column(db.Integer, primary_key=True)
    start_point = db.Column(db.Text, nullable=False)
    end_point = db.Column(db.Text, nullable=False)
    checkpoint = db.Column(db.Text, nullable=False)
    obstacles_location_list = db.Column(db.Text, nullable=False)
    
    def __init__(self, stageID, start_point, end_point, checkpoint, obstacles_location_list):
        self.stageID = stageID
        self.start_point = start_point
        self.end_point = end_point
        self.checkpoint = checkpoint
        self.obstacles_location_list = obstacles_location_list
  
    
class CarInformation(db.Model):
    carInformationID = db.Column(db.Integer, primary_key=True)
    distance_travelled = db.Column(db.Text, nullable=False)
    rotation = db.Column(db.Text, nullable=False)
    acceleration = db.Column(db.Text, nullable=False)
    time_spent = db.Column(db.Text, nullable=False)
    obstacle_position = db.Column(db.Text, nullable=False)
    car_point = db.Column(db.Text, nullable=False)
    gameID = db.Column(db.Integer, db.ForeignKey('Game.gameID'), nullable=False)
    
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

class Commands(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    commands = db.Column(db.Text)
    
    def __init__(self, commands):
        self.commands = commands
 
>>>>>>> Stashed changes

#class ConfigForm(FlaskForm):
#    MaxSpeed = IntegerField('Maximum Speed of Robotic Car')
#    RotationSpeed = IntegerField('Rotation Speed of Robotic Car')
#    ObstacleDistance = IntegerField('Obstacle Distance')
#    submit = SubmitField('Submit')

@app.route("/", methods=["POST", "GET"])
def home():
    if request.method == "POST":
        commands = request.get_data()
        test = Commands(commands)

        db.session.add(test)
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