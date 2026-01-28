from O365 import Account
import os
from dotenv import load_dotenv

load_dotenv()

credentials = (os.getenv('AZURE_CLIENT_ID'), os.getenv('AZURE_CLIENT_SECRET'))

def get_account():
    # token_backend='FileSystemTokenBackend' stocke le token dans un fichier texte local
    # pour ne pas avoir à se reconnecter à chaque fois.
    account = Account(credentials, token_backend='FileSystemTokenBackend', token_path='config', token_filename='o365_token.txt')
    return account

def authenticate():
    account = get_account()
    if not account.is_authenticated:
        # Cela va générer une URL dans la console. Tu cliques, tu te connectes,
        # et tu colles l'URL de retour dans la console.
        account.authenticate(scopes=['basic', 'message_all'])
    print("Outlook Authenticated!")

def send_email(to_email, subject, body):
    account = get_account()
    m = account.new_message()
    m.to.add(to_email)
    m.subject = subject
    m.body = body
    m.send()