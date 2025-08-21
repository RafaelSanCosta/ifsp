
# A very simple Flask Hello World app for you to get started with...

from flask import Flask, request, abort, url_for

app = Flask(__name__)

@app.route('/')
def home():
    return f'''
            <h1>Avaliação contínua: Aula 030</h1>
                <ul>
                    <li><a href="{url_for('home')}">Home</a></li>
                    <li><a href="{url_for('identificacao', nome='Rafael Costa', prontuario='PT3031934', instituicao='IFSP')}">Identificação</a></li>
                    <li><a href="{url_for('contexto_requisicao')}">Contexto da requisição</a></li>
                </ul>
            '''

@app.route("/user/<nome>/<prontuario>/<instituicao>")
def identificacao(nome, prontuario, instituicao):
    return f'''
    <h1>Avaliação contínua: Aula 030</h1>

    <h2><b>Aluno:</b> {nome}</h2>
    <h2><b>Prontuário:</b> {prontuario}</h2>
    <h2><b>Instituição:</b> {instituicao}</h2>

    <p><a href="{url_for('home')}">Voltar</a></p>
    '''

@app.route("/contextorequisicao")
def contexto_requisicao():
    user_agent = request.headers.get("User-Agent", "desconhecido")
    remote_ip = request.remote_addr or "desconhecido"
    host = request.host

    return f'''
    <h1>Avaliação contínua: Aula 030</h1>

    <h2><b>Seu navegador é:</b> {user_agent}</h2>
    <h2><b>O IP do computador remoto é:</b> {remote_ip}</h2>
    <h2><b>O host da aplicação é:</b> {host}</h2>

    <p><a href="{url_for('home')}">Voltar</a></p>
    '''

@app.route('/codigostatusdiferente')
def codigostatusdiferente():
    abort(400)
    return '0'

@app.route('/abortar')
def abortar():
    abort(404)
    return '0'

@app.route('/objetoresposta')
def objetoresposta():
    return '<h1>A resposta é 42</h1>'

if __name__ == "__main__":
    app.run(debug=True)
