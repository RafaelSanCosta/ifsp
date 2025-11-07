from flask import current_app
from sendgrid import SendGridAPIClient
from sendgrid.helpers.mail import Mail
from datetime import datetime

def send_simple_message(to, subject, newUser):
    app_config = current_app.config
    
    print('Enviando mensagem via SendGrid...', flush=True)
    print(f'From: {app_config.get("API_FROM")}', flush=True)
    print(f'To: {to}', flush=True)
    print(f'Subject: {subject}', flush=True)

    plain_text_content=f"""
    Prontuário: PT3031934
    Nome do aluno: Rafael Santos Costa
    Usuário cadastrado: {newUser}
    """

    api_key = app_config.get('SENDGRID_API_KEY')
    if not api_key:
        print("SENDGRID_API_KEY não encontrada nas variáveis de ambiente.", flush=True)
        return None

    message = Mail(
        from_email=app_config.get('API_FROM'),
        to_emails=to,
        subject=f"{app_config.get('FLASKY_MAIL_SUBJECT_PREFIX', '')} {subject}",
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
