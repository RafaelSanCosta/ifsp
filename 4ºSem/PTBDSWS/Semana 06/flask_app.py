
# A very simple Flask Hello World app for you to get started with...

from flask import Flask,render_template,request, url_for, session, flash, redirect
from flask_bootstrap import Bootstrap
from flask_moment import Moment
from datetime import datetime
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField, SelectField, PasswordField
from wtforms.validators import DataRequired

app = Flask(__name__)
app.config['SECRET_KEY'] = 'Chave forte'
bootstrap = Bootstrap(app)
moment = Moment(app)

class NameForm(FlaskForm):
    nome = StringField('Informe o seu nome:', validators = [DataRequired()])
    sobrenome = StringField("Informe o seu sobrenome:", validators = [DataRequired()])
    instituicao = StringField("Informe a sua Instituição e Ensino:", [DataRequired()])
    disciplina = SelectField("Informe a sua Disciplina:", choices=["DSWA5", "DWBA4", "Gestão de Projetos"])
    submit = SubmitField('Submit')

class LoginForm(FlaskForm):
    username = StringField(validators = [DataRequired()])
    password = PasswordField(validators = [DataRequired()])
    submit = SubmitField('Submit')

@app.route('/', methods=['GET','POST'])
def index():
    form = NameForm()
    if form.validate_on_submit():
        old_name = session.get('nome')
        if old_name is not None and old_name != form.nome.data:
            flash('Looks like you have changed your name!')
        session['nome'] = form.nome.data
        session['sobrenome'] = form.sobrenome.data
        session['instituicao'] = form.instituicao.data
        session['disciplina'] = form.disciplina.data
        return redirect(url_for('index'))
    remote_addr = request.remote_addr or "desconhecido"
    host = request.host
    return render_template('index.html', form=form, nome=session.get('nome'), sobrenome=session.get('sobrenome'), instituicao=session.get('instituicao'), disciplina=session.get('disciplina'), remote_addr=remote_addr, host=host, current_time=datetime.utcnow())

@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if request.method == 'POST':
        session['username'] = form.username.data
        return redirect(url_for('login_response'))
    return render_template('login.html', form=form, current_time=datetime.utcnow())

@app.route('/loginResponse')
def login_response():
    return render_template('login-response.html', username=session.get('username'), current_time=datetime.utcnow())

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
