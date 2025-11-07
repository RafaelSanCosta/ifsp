from . import db
from datetime import datetime

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
    hora = db.Column(db.DateTime, default=datetime.utcnow)#Data/Hora

    user = db.relationship('User', backref=db.backref('emails', lazy='dynamic'))
