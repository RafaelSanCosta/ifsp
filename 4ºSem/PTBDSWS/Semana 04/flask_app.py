
# A very simple Flask Hello World app for you to get started with...

from flask import Flask,render_template,request #abort, url_for,
from flask_bootstrap import Bootstrap
from flask_moment import Moment
from datetime import datetime

app = Flask(__name__)
bootstrap = Bootstrap(app)
moment = Moment(app)

@app.route('/')
def index():
    return render_template('index.html', current_time=datetime.utcnow())

@app.route('/user/<username>')
def user(username):
    return render_template('user.html', name=username)

@app.route('/rotainexistente')
def rotaNaoExistente():
    return render_template('404.html'),404

@app.errorhandler(404)
def pagina_nao_encontrada(e):
    return render_template('404.html'),404

@app.route('/contextorequisicao/<username>')
def contextoReqCmUser(username):
    return render_template('contextorequisicao.html', name=username,
    user_agent = request.headers.get("User-Agent", "desconhecido"),
    remote_ip = request.remote_addr or "desconhecido",
    host = request.host)

if __name__ == "__main__":
    app.run(debug=True)
