from threading import Thread
from flask import current_app, render_template
import requests
from datetime import datetime


def send_async_email(app, payload):
    with app.app_context():
        response = requests.post(
            "https://api.sendgrid.com/v3/mail/send",
            headers={
                "Authorization": f"Bearer {app.config['SENDGRID_API_KEY']}",
                "Content-Type": "application/json"
            },
            json=payload
        )
        print("Status do envio:", response.status_code, flush=True)
        print("Resposta:", response.text, flush=True)


def send_email(to, subject, template, **kwargs):
    app = current_app._get_current_object()

    print("Enviando e-mail com SendGrid...", flush=True)
    print("API KEY:", app.config['SENDGRID_API_KEY'][:6] + "*****", flush=True)
    print("FROM:", app.config['API_FROM'], flush=True)
    print("TO:", to, flush=True)

    # Renderiza o template HTML do email
    html_content = render_template(template + '.html', **kwargs)

    payload = {
        "personalizations": [
            {
                "to": [{"email": to}],
                "subject": app.config['FLASKY_MAIL_SUBJECT_PREFIX'] + " " + subject
            }
        ],
        "from": {"email": app.config['API_FROM']},
        "content": [
            {
                "type": "text/html",
                "value": html_content
            }
        ]
    }

    # Envio assíncrono
    thr = Thread(target=send_async_email, args=[app, payload])
    thr.start()
    return thr
