import os
from dotenv import load_dotenv

# Carrega as variáveis do arquivo .env para o ambiente
dotenv_path = os.path.join(os.path.dirname(__file__), '.env')
if os.path.exists(dotenv_path):
    load_dotenv(dotenv_path)

import sys
from app import create_app, db
from app.models import User, Role, Email
from flask_migrate import Migrate

app = create_app(os.getenv('FLASK_CONFIG') or 'default')
migrate = Migrate(app, db)

@app.shell_context_processor
def make_shell_context():
    return dict(db=db, User=User, Role=Role, Email=Email)

if __name__ == '__main__':
    app.run(debug=True)
