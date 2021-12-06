from webportal import *
import pytest 

app = Flask(__name__)

@app.route("/")
def tutorialstest():
        conn = sql.connect('file:test.db?mode=rw', uri=True)
        conn.row_factory = sql.Row

        cur = conn.cursor()
        #Invalid Statement Here!
        cur.execute("select InvalidStatement from Tutorial order by tutorialID")
           
        rows = cur.fetchall()
        conn.close()
        return render_template('tutorials.html', title='Tutorials', rows=rows)
        


def test_loadAllTutID():
    client = app.test_client()
    url = '/'
    response = client.get(url)  
    assert response.status_code == 500
    
    
    
