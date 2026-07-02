"""
========================================================
FICHIER DE CONFIGURATION TRANSALP - NE PAS ÉCRASER
Toutes les valeurs métier sont ici. Édite ce fichier
librement sans risque lors des mises à jour du code.
========================================================
"""

# ── Chemin vers le catalogue Excel (monté via volume Docker) ─────────────────
CATALOGUE_EXCEL_PATH = "/app/catalogue/catalogue.xlsx"

# ── Colonnes de référence dans l'Excel (colonnes A et B = index 0 et 1) ──────
EXCEL_COL_REFERENCE_A = 0    # Colonne A : Référence Article SAGE
EXCEL_COL_REFERENCE_B = 1    # Colonne B : Désignation (parfois aussi utilisée comme ref)
EXCEL_COL_DESIGNATION = 2    # Colonne pour la recherche mot-clé
EXCEL_COL_FAMILLE_ACHAT = 3 # Colonne FAMILLE ACHAT (à ajuster selon ton fichier)

FAMILLE_TO_NC_TYPE = {
    "PRODUIT FINI NÉGOCE":    "NCF",
    "PRODUIT FINI FABRIQUE":  "NCE",
    "PRODUIT FINI FABRIQUÉ":  "NCE",
    "SOUS-ENSEMBLE ACHETÉ":   "NCF",
    "SOUS-ENSEMBLE ACHETE":   "NCF",
    "SOUS-ENSEMBLE FABRIQUÉ": "NCE",
    "SOUS-ENSEMBLE FABRIQUE": "NCE",
    "PIÈCE FABRIQUÉE":        "NCE",
    "PIECE FABRIQUEE":        "NCE",
    "CONSOMMABLE":            "NCF",
    "COMPOSANT ACHETÉ":       "NCF",
    "COMPOSANT ACHETE":       "NCF",
    "MATIÈRE PREMIÈRE":       "NCF",
    "MATIERE PREMIERE":       "NCF",
}

SEUIL_MOIS_SAV = 2

VALID_TYPES_NC = ["NCE", "NCF", "NCI", "Non recevable", "SAV"]

VALID_CAUSES = [
    "Défaut de fabrication",
    "Défaut de montage sur site",
    "Demande d'information",
    "Erreur de conception",
    "Info client incorrecte",
    "Manquement en production",
    "Manquement en visserie",
    "Manquement sur site",
    "Mauvaise communication interservices",
    "Non respect des délais",
    "Non-conformités d'audit",
    "Notice incorrecte",
    "Pièce endommagée",
    "Plan incorrect",
    "Problème de devis",
    "Rouille",
]

VALID_ACTIONS = [
    "Correction sur le site",
    "Devis",
    "Mise à jour conception",
    "Mise à jour documents",
    "Réclamation au fournisseur",
    "Refabrication",
    "Renvoi pièces",
]

VALID_SERVICES = [
    "Achats / Appro",
    "ADV",
    "BE Com",
    "BE Methode",
    "Commercial",
    "Expédition / Assemblage Jeux",
    "Expédition / Assemblage Sport",
    "Fournisseur",
    "Peinture",
    "Poseur",
    "Serrurerie",
    "Transport",
    "Transalp",
]

CONFIDENCE_THRESHOLD = 0.65
MAX_ERRORS_ALLOWED   = 2
