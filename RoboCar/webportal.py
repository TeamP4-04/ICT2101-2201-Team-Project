from flask import Flask, render_template, url_for, request

from flask_sqlalchemy import SQLAlchemy

from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///Robocar.db'
db = SQLAlchemy(app)

class dash(db.Model):
    row_id = db.Column(db.Integer, primary_key=True)
    distance_travelled = db.Column(db.String(20))
    rotation=db.Column(db.String(20))
    obstacle_distance=db.Column(db.String(20))
    acceleration=db.Column(db.String(20))

    
    def __init__(self, row_id, distance_travelled,rotation,obstacle_distance,acceleration):
        self.row_id=row_id
        self.distance_travelled=distance_travelled
        self.rotation=rotation
        self.obstacle_distance=obstacle_distance
        self.acceleration=acceleration
        db.session.add(self)
        db.session.commit()
    
    def set_distance(self, distance_travelled,rotation,obstacle_distance,acceleration):
        query=dash(distance_travelled,rotation,obstacle_distance,acceleration)
        db.session.add(query)
        db.session.commit()
        return True
    
   
db.create_all()



class ConfigForm(FlaskForm):
    MaxSpeed = IntegerField('Maximum Speed of Robotic Car')
    RotationSpeed = IntegerField('Rotation Speed of Robotic Car')
    ObstacleDistance = IntegerField('Obstacle Distance')
    Speed = IntegerField('Speed')
    submit = SubmitField('Submit')

@app.route("/")

@app.route("/main")
def main():
    a=dash.query.filter_by(row_id=1).first()
    return render_template('main.html', title='Main', distance_travelled=a.distance_travelled,rotation=a.rotation,obstacle_distance=a.obstacle_distance,
    acceleration=a.acceleration)
    

@app.route("/logs")
def logs():
    return render_template('logs.html', title='Logs')


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