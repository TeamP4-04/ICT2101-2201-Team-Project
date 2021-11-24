from flask import Flask, render_template, url_for, request

from flask_sqlalchemy import SQLAlchemy

from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField

app = Flask(__name__)

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


@app.route("/tutorials")
def tutorials():
    return render_template('tutorials.html', title='Tutorials')
    
@app.route("/tutorial1")
def tutorialdetails():
    return render_template('tutorial1.html', title='Tutorial1')

@app.route("/tutorial2")
def tutorialdetails():
    return render_template('tutorial2.html', title='Tutorial2')

@app.route("/tutorial3")
def tutorialdetails():
    return render_template('tutorial3.html', title='Tutorial3')
    
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