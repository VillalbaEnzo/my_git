import gspread
import os
from dotenv import load_dotenv

load_dotenv()

def get_sheet():
    gc = gspread.service_account(filename='config/google_key.json')
    sh = gc.open_by_key(os.getenv('SHEET_ID'))
    return sh.sheet1

def get_jobs_to_apply():
    ws = get_sheet()
    all_records = ws.get_all_records()
    # Filtre ceux qui ont le statut "À faire"
    return [row for row in all_records if row['Statut'] == 'À faire']