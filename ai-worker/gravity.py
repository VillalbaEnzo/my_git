"""
Calcul de l'Indice de Gravité Transalp
---------------------------------------
Critère          | Coeff | Niveaux 0-3
Sécurité usager  |   3   | 0=Aucun / 1=Risque mineur / 2=Risque avéré / 3=Incident
Client           |   2   | 0=Aucun / 1=Réclamation/Retard / 2=Retour produit / 3=LRAR
Coût (€)         |   1   | 0=<50€ / 1=<100€ / 2=100-500€ / 3=>500€
Impact poseur    |   2   | 0=Aucune / 1=Temps de pose / 2=Retour site / 3=Intervention TRANSALP
Score max = 24
"""

CRITERIA = {
    "securite": {
        "label": "Sécurité utilisateur",
        "coeff": 3,
        "levels": {
            0: "Aucun",
            1: "Risque mineur ou indirect",
            2: "Risque avéré sans incident",
            3: "Incident",
        },
    },
    "client": {
        "label": "Client",
        "coeff": 2,
        "levels": {
            0: "Aucun",
            1: "Réclamation commerciale / Retard mineur",
            2: "Retour produit / Insatisfaction directe",
            3: "LRAR",
        },
    },
    "cout": {
        "label": "Coût (€)",
        "coeff": 1,
        "levels": {
            0: "< 50€",
            1: "< 100€",
            2: "100 – 500€",
            3: "> 500€",
        },
    },
    "impact_poseur": {
        "label": "Impact poseur",
        "coeff": 2,
        "levels": {
            0: "Aucune incidence",
            1: "Traité dans le temps de pose",
            2: "Besoin retour sur site",
            3: "Intervention TRANSALP / Autre entreprise",
        },
    },
}

GRAVITY_RANGES = [
    (0,  0,  "Aucun",    "Aucun impact"),
    (1,  6,  "Mineur",   "Impact léger, gestion faible"),
    (7,  12, "Moyen",    "Impact visible, retouche ou gestion modérée"),
    (13, 18, "Majeur",   "Impact client ou sécurité, coûts importants"),
    (19, 24, "Critique", "Sécurité ou projet à risque, réclamation sévère"),
]


def compute_gravity(securite: int, client: int, cout: int, impact_poseur: int) -> dict:
    """
    Calcule le score et l'indice de gravité à partir des niveaux (0-3) de chaque critère.
    Retourne un dict complet pour stockage en base et affichage.
    """
    inputs = {
        "securite": securite,
        "client": client,
        "cout": cout,
        "impact_poseur": impact_poseur,
    }
    for key, val in inputs.items():
        if val not in (0, 1, 2, 3):
            raise ValueError(f"Niveau invalide pour '{key}': {val}. Attendu: 0, 1, 2 ou 3.")

    score = (
        securite     * CRITERIA["securite"]["coeff"] +
        client       * CRITERIA["client"]["coeff"] +
        cout         * CRITERIA["cout"]["coeff"] +
        impact_poseur * CRITERIA["impact_poseur"]["coeff"]
    )

    label = "Inconnu"
    signification = ""
    for low, high, lbl, sig in GRAVITY_RANGES:
        if low <= score <= high:
            label = lbl
            signification = sig
            break

    return {
        "score": score,
        "score_max": 24,
        "label": label,
        "signification": signification,
        "detail": {
            "securite":      {"niveau": securite,      "coeff": 3, "points": securite * 3},
            "client":        {"niveau": client,        "coeff": 2, "points": client * 2},
            "cout":          {"niveau": cout,          "coeff": 1, "points": cout * 1},
            "impact_poseur": {"niveau": impact_poseur, "coeff": 2, "points": impact_poseur * 2},
        },
    }


def get_criteria_descriptions() -> dict:
    """Retourne les descriptions de chaque niveau pour aider le LLM à choisir."""
    return CRITERIA
