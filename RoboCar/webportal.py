from flask import Flask, render_template, url_for, request

from flask_sqlalchemy import SQLAlchemy

from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField

app = Flask(__name__)
#db = SQLAlchemy(app)

class ConfigForm(FlaskForm):
    MaxSpeed = IntegerField('Maximum Speed of Robotic Car')
    RotationSpeed = IntegerField('Rotation Speed of Robotic Car')
    ObstacleDistance = IntegerField('Obstacle Distance')
    submit = SubmitField('Submit')

from flask import Flask, render_template, url_for, request
# from flask_nav import Nav
# from flask_nav.elements import Navbar, Subgroup, View, Link, Text, Separator

# from flask_sqlalchemy import SQLAlchemy

from flask_wtf import FlaskForm
from wtforms import IntegerField, SubmitField

app = Flask(__name__)
# nav = Nav(app)
#db = SQLAlchemy(app)

# nav.register_element('my_navbar', Navbar(
#     'thenav',
#     View('Home Page', 'Main')))

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

@app.route("/logs/log1")
def logdetails():
    return render_template('log1.html', title='Log1')

@app.route("/tutorials")
def tutorials():
    return render_template('tutorials.html', title='Tutorials')
    
@app.route("/tutorials/tutorial1")
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
