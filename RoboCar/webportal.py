from flask import Flask, render_template, url_for
app = Flask(__name__)


@app.route("/")
@app.route("/main")
def main():
    return render_template('main.html', title='Main')


@app.route("/logs")
def logs():
    return render_template('logs.html', title='Logs')


if __name__ == '__main__':
    app.run(debug=True)