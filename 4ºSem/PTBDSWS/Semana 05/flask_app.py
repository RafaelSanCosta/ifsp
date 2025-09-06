
# A very simple Flask Hello World app for you to get started with...

from flask import Flask,render_template,request, url_for, session, flash, redirect
from flask_bootstrap import Bootstrap
from flask_moment import Moment
#from datetime import datetime
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired

app = Flask(__name__)
app.config['SECRET_KEY'] = 'Chave forte'
bootstrap = Bootstrap(app)
moment = Moment(app)

class NameForm(FlaskForm):
    name = StringField('What is your name?', validators= [DataRequired()])
    submit = SubmitField('Submit')

@app.route('/', methods=['GET','POST'])
def index():
    form = NameForm()
    if form.validate_on_submit():
        old_name = session.get('name')
        if old_name is not None and old_name != form.name.data:
            flash('Looks like you have changed your name!')
        session['name'] = form.name.data
        return redirect(url_for('index'))
    return render_template('index.html', form= form, name = session.get('name'))

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
