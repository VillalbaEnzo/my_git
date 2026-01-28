from modules.outlook_manager import authenticate, send_email
from modules.sheet_manager import get_jobs_to_apply

def main():
    print("--- Internship Bot v1.0 ---")

    # 1. Auth Outlook (à faire une seule fois au début)
    authenticate()

    # 2. Lire le sheet
    jobs = get_jobs_to_apply()
    print(f"{len(jobs)} jobs trouvés à traiter.")

    # 3. Boucle (Logique simplifiée pour test)
    for job in jobs:
        print(f"Traitement de {job['Entreprise']}...")
        # TODO: Appeler l'IA pour générer le mail
        # TODO: Appeler outlook pour envoyer
        # TODO: Mettre à jour le Sheet
        pass

if __name__ == "__main__":
    main()