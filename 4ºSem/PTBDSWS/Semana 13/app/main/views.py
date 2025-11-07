from flask import render_template, session, redirect, url_for, current_app
from datetime import datetime
from . import main
from .forms import NameForm
from .. import db
from ..models import User, Email
from ..email import send_simple_message

@main.route('/', methods=['GET', 'POST'])
def index():
    form = NameForm()
    users = User.query.all()

    if form.validate_on_submit():
        user = User.query.filter_by(username=form.name.data).first()

        if user is None:
            user = User(username=form.name.data)
            db.session.add(user)
            db.session.commit()
            session['known'] = False
            session['name'] = user.username

            print('Novo usuário criado:', user.username, flush=True)
            
            destinatarios_brutos = [
                current_app.config.get('FLASKY_ADMIN'), 
                'flaskaulasweb@zohomail.com',
                form.email.data
            ]
            
            destinatarios_validos = [email for email in destinatarios_brutos if email]

            plain_text_content = f"""
            Prontuário: PT3031934
            Nome do aluno: Rafael Santos Costa
            Usuário cadastrado: {user.username}
            """
            
            if destinatarios_validos:
                send_simple_message(destinatarios_validos, 'Novo usuário cadastrado', user.username)
            else:
                print("Nenhum destinatário válido encontrado. E-mail não enviado.", flush=True)

            email_log = Email(
                username_id=user.id,
                recebidoPor=', '.join(destinatarios_validos), 
                assunto="Novo usuário cadastrado",
                texto=plain_text_content.strip(),
                hora=datetime.now()
            )
            db.session.add(email_log)
            db.session.commit()

        else:
            session['known'] = True
            session['name'] = user.username
            print(f"Usuário existente: {user.username}", flush=True)

        return redirect(url_for('.index'))

    return render_template('index.html', form=form, name=session.get('name'),known=session.get('known', False), user_list=users)


@main.route('/emailsEnviados')
def emails_enviados():
    email_list = Email.query.order_by(Email.hora.desc()).all()
    return render_template('emailsEnviados.html', email_list=email_list)
