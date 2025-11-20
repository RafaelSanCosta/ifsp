from flask import render_template
from . import main
from ..models import User


@main.route('/')
def index():
    users = User.query.order_by(User.username).all()
    print(users)
    return render_template('index.html', user_list=users)
