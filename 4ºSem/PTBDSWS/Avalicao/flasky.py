from flask import Flask, render_template, session, redirect, url_for, flash, request
from flask_bootstrap import Bootstrap
from flask_moment import Moment
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField, SelectField, PasswordField, RadioField
from wtforms.validators import DataRequired
from datetime import datetime
from flask_moment import Moment
from flask_sqlalchemy import SQLAlchemy
import sys
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
app.config['SQLALCHEMY_DATABASE_URI'] =\
    'sqlite:///' + os.path.join(basedir, 'data.sqlite')
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

bootstrap = Bootstrap(app)
moment = Moment(app)
db = SQLAlchemy(app)
migrate = Migrate(app, db)

class Disciplina(db.Model):
    __tablename__ = 'disciplinas'
    id = db.Column(db.Integer, primary_key=True)
    nome = db.Column(db.String(64), unique=True, nullable=False)
    semestre = db.Column(db.String(15), nullable=False)

    def __repr__(self):
        return f'<Disciplina {self.nome}>'

class DisciplinaForm(FlaskForm):
    nomeDisciplina = StringField('Cadastre a nova disciplina e o semestre associado:', validators=[DataRequired()])
    semestre = RadioField(
        'Selecione o Semestre:', 
        choices=[
            ('1° Semestre', '1° Semestre'),
            ('2° Semestre', '2° Semestre'),
            ('3° Semestre', '3° Semestre'),
            ('4° Semestre', '4° Semestre'),
            ('5° Semestre', '5° Semestre'),
            ('6° Semestre', '6° Semestre')
        ],
        validators=[DataRequired()]
    )
    submit = SubmitField('Cadastrar')

@app.shell_context_processor
def make_shell_context():
    return dict(db=db, Disciplina=Disciplina)

@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@app.errorhandler(500)
def internal_server_error(e):
    return render_template('500.html'), 500

@app.route('/')
def index():
    return render_template('index.html', current_time=datetime.utcnow())

@app.route('/disciplinas', methods=['GET', 'POST'])
def disciplinas():       
    form = DisciplinaForm()
  
    disciplinas_all = Disciplina.query.all()
    
    if form.validate_on_submit():
        nome_novo = form.nomeDisciplina.data
        semestre_label = form.semestre.data
        
        disciplina_existente = Disciplina.query.filter_by(nome=nome_novo).first()
        
        if disciplina_existente is None:
            nova_disciplina = Disciplina(nome=nome_novo, semestre=semestre_label)
            
            db.session.add(nova_disciplina)
            db.session.commit()
            
            session['known'] = False
        else:
            session['known'] = True
            
        return redirect(url_for('disciplinas'))
    
    return render_template(
        'disciplinas.html',
        titulo='Cadastro de Disciplinas',
        form=form,
        disciplinas=disciplinas_all
    )

@app.route('/alunos'):
def alunos():
  return render_template('alunos.html', current_time=datetime.utcnow())

@app.route('/professores'):
def professores():
  return render_template('professores.html', current_time=datetime.utcnow())

@app.route('/cursos'):
def cursos():
  return render_template('cursos.html', current_time=datetime.utcnow())

@app.route('/ocorrencias'):
def ocorrencias():
  return render_template('ocorrencias.html', current_time=datetime.utcnow())
  
  
