from webportal import *
import pytest 

app = Flask(__name__)

@app.route("/")
def tutorialstest():
        conn = sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row

        cur = conn.cursor()
        cur.execute("select * from Tutorial order by tutorialID")

        rows = cur.fetchall()
        conn.close()
        return render_template('tutorials.html', title='Tutorials', rows=rows)
        


@app.route("/tutorial/<tutorialID>")
def tutorialdetailstest(tutorialID):

    conn = sql.connect('file:test.db?mode=rw', uri=True)
    conn.row_factory = sql.Row

    cur = conn.cursor()
    cur.execute("select * from Tutorial where tutorialID = ?", tutorialID)
    rows = cur.fetchall()
    #Invalid Statement Here!
    cur.execute("SELECT InvalidStatement FROM Tutorial WHERE tutorialID=(SELECT max(tutorialID) FROM Tutorial)")
    last_id = cur.fetchone()
    conn.close()
    return render_template('tutorial1.html', title='Tutorial ' + tutorialID, rows=rows, last_id=last_id)
        


def test_checkLastTutID():
    client = app.test_client()
    url = '/'
    response = client.get(url)  
    assert response.status_code == 200
    
    url2 = '/tutorial/1'
    response2 = client.get(url2)
    assert response2.status_code == 500
    

    
