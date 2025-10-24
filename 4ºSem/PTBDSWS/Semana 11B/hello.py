import os
import sys
from threading import Thread
from flask import Flask, render_template, session, redirect, url_for
from flask_bootstrap import Bootstrap
from flask_moment import Moment
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField, BooleanField
from wtforms.validators import DataRequired
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

from sendgrid import SendGridAPIClient
from sendgrid.helpers.mail import Mail
from datetime import datetime

basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'data.sqlite')
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

# Configurações de ambiente
app.config['SENDGRID_API_KEY'] = os.environ.get('SENDGRID_API_KEY')
app.config['API_FROM'] = os.environ.get('API_FROM')
app.config['FLASKY_MAIL_SUBJECT_PREFIX'] = '[Flasky]'
app.config['FLASKY_ADMIN'] = os.environ.get('FLASKY_ADMIN')

bootstrap = Bootstrap(app)
moment = Moment(app)
db = SQLAlchemy(app)
migrate = Migrate(app, db)



class Role(db.Model):
    __tablename__ = 'roles'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(64), unique=True)
    users = db.relationship('User', backref='role', lazy='dynamic')

    def __repr__(self):
        return '<Role %r>' % self.name


class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(64), unique=True, index=True)
    role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))

    def __repr__(self):
        return '<User %r>' % self.username

class Email(db.Model):
    __tablename__ ='emails'
    id = db.Column(db.Integer, primary_key=True)
    username_id = db.Column(db.Integer, db.ForeignKey('users.id')) #de
    recebidoPor = db.Column(db.String(64), index=True)#para
    assunto = db.Column(db.String(100), index=True)#Assunto
    texto = db.Column(db.String(400), index=True)#Texto
    hora = db.Column(db.TimeStamp)#Data/Hora


def send_simple_message(to, subject, newUser):
    print('Enviando mensagem via SendGrid...', flush=True)
    print(f'From: {app.config.get("API_FROM")}', flush=True)
    print(f'To: {to}', flush=True)
    print(f'Subject: {subject}', flush=True)

    # html_body = f"""
    # <html>
    #     <body>
    #         <p><b>Prontuário:</b> PT3031934</p>
    #         <p><b>Nome do aluno:</b> Rafael Santos Costa</p>
    #         <p>Usuário cadastrado: {newUser}</p>
    #     </body>
    # </html>
    # """

    plain_text_content=f"""
    Prontuário: PT3031934
    Nome do aluno: Rafael Santos Costa
    Usuário cadastrado: {newUser}
    """

    api_key = app.config.get('SENDGRID_API_KEY')
    if not api_key:
        print("SENDGRID_API_KEY não encontrada nas variáveis de ambiente.", flush=True)
        return None

    message = Mail(
        from_email=app.config.get('API_FROM'),
        to_emails=to,
        subject=f"{app.config.get('FLASKY_MAIL_SUBJECT_PREFIX', '')} {subject}",
        plain_text_content=plain_text_content
    )


    try:
        sg = SendGridAPIClient(api_key)
        response = sg.send(message)
        body = getattr(response, 'body', None)
        try:
            body_text = body.decode() if isinstance(body, (bytes, bytearray)) else str(body)
        except Exception:
            body_text = repr(body)

        print(f"Status: {response.status_code}", flush=True)
        print(f"Body: {body_text}", flush=True)
        print(f"Headers: {response.headers}", flush=True)
        print(f"Resposta recebida em: {datetime.now().strftime('%d/%m/%Y %H:%M:%S')}", flush=True)
        return response
    except Exception as e:
        err_msg = str(e)
        try:
            extra = getattr(e, 'body', None)
            if extra:
                err_msg += f" | body: {extra}"
        except Exception:
            pass
        print("Erro ao enviar e-mail:", err_msg, flush=True)
        return None



class NameForm(FlaskForm):
    name = StringField('Qual o seu nome?', validators=[DataRequired()])
    send_extra = BooleanField('Deseja enviar e-mail para flaskaulasweb@zohomail.com?')
    submit = SubmitField('Submit')


@app.shell_context_processor
def make_shell_context():
    return dict(db=db, User=User, Role=Role)


@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404


@app.errorhandler(500)
def internal_server_error(e):
    return render_template('500.html'), 500



@app.route('/', methods=['GET', 'POST'])
def index():
    form = NameForm()
    users = User.query.all()
    emails = Email.query.all()

    if form.validate_on_submit():
        user = User.query.filter_by(username=form.name.data).first()

        if user is None:
            user = User(username=form.name.data)
            db.session.add(user)
            db.session.commit()
            session['known'] = False
            session['name'] = user.username

            print('Novo usuário criado:', user.username, flush=True)

            destinatarios = [app.config['FLASKY_ADMIN']]
            if form.send_extra.data:
                destinatarios.append("flaskaulasweb@zohomail.com")

            send_simple_message(destinatarios, 'Novo usuário cadastrado', user.username)
            email = Email(
                username_id=user.id,
                recebidoPor=destinatarios,
                assunto="Novo usuário cadastrado",#meio problematico né, se o assunto for diferente, mas modifica um ali e modifica o outro aqui
                texto=plain_text_content,
                hora=datetime.now()
            )
            db.session.add(email)
            db.session.commit()

            #if app.config['FLASKY_ADMIN']:
            #    destinatarios = [app.config['FLASKY_ADMIN'], "flaskaulasweb@zohomail.com"]
            #    send_simple_message(destinatarios, 'Novo usuário', user.username)

        else:
            session['known'] = True
            session['name'] = user.username
            print(f"Usuário existente: {user.username}", flush=True)

        #session['name'] = form.name.data
        return redirect(url_for('index'))

    return render_template('index.html', form=form, name=session.get('name'),
                           known=session.get('known', False), user_list=users)
