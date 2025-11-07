from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField #BooleanField
from wtforms.validators import DataRequired, Email

class NameForm(FlaskForm):
    name = StringField('Qual o seu nome?', validators=[DataRequired()])
    email = StringField('Qual é o seu email (Envio de notificação de novo usuário)?', validators=[DataRequired(), Email()])
    #send_extra = BooleanField('Deseja enviar e-mail para flaskaulasweb@zohomail.com?')
    submit = SubmitField('Submit')
