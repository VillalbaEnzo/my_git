# MADEV Pass

**Carte étudiante numérique de la ville de Vienne** et son réseau de commerçants partenaires.

MADEV Pass digitalise la carte étudiante sous forme d'un **QR code sécurisé à rotation**, met en relation les **étudiants** avec les **commerces locaux** (offres & réductions), fournit aux **administrateurs** les outils de modération et de pilotage du réseau, et s'appuie sur un **micro-service IA** pour vérifier automatiquement l'authenticité des justificatifs d'inscription.

Application **PWA installable** (mobile & desktop) avec **notifications push** et **tableaux de bord analytiques**.

---

## ✨ Aperçu

L'application s'articule autour de **trois espaces**, d'une **landing page vitrine** publique et d'un **micro-service de vérification IA** :

| Espace | Rôle | Fonctionnalités clés |
|--------|------|----------------------|
| 🌐 **Landing** | Public | Vitrine premium (hero 3D, statistiques, showcase) avant connexion |
| 🎓 **Étudiant** | `ETUDIANT` | Carte numérique + QR plein écran avec timer, annuaire des partenaires, favoris, profil/RGPD, notifications push |
| 🏪 **Commerçant** | `COMMERCANT` | Tableau de bord analytique (graphiques `recharts`), UI caisse de scan QR, gestion des offres, édition du commerce |
| 🛡️ **Admin** | `ADMIN` | Validation des inscriptions (assistée par l'IA), gestion des comptes & commerçants, catégories, dashboard analytique (`AdminShell`) |
| 🤖 **AI Service** | Interne | Extraction & vérification automatique des pièces d'identité et attestations de scolarité (vision LLM + MRZ + scoring de risque) |

---

## 🎨 Design System

Interface pensée comme un **produit SaaS / Fintech premium**, avec un **Dark Mode natif** (toggle clair/sombre persistant via `localStorage`).

- **Thème** : fond `slate-950` (dark) / `slate-50` (light), surfaces `slate-900` / `white`
- **Couleur primaire** : `violet-600` (#7C3AED) — CTA, bordures actives, effets de *glow*
- **Typographie** : `Geist`
- **Composants** : glassmorphism (`backdrop-blur`), coins très arrondis (`rounded-2xl`), bordures lumineuses animées
- **Animations** : entrées *stagger*, *scroll reveals*, *scroll-driven progress*, micro-interactions *hover scale*, fond 3D animé (Spline + canvas, projection de points sphériques), bordures coniques animées via `requestAnimationFrame`

---

## 🧱 Stack technique

### Frontend (`/client`)
- **React 18** + **TypeScript**
- **Vite** (build & dev server)
- **React Router DOM** (routing par rôle, routes protégées)
- **Tailwind CSS** (design utilitaire, dark mode `class`)
- **Framer Motion** (animations & transitions)
- **Lucide React** (icônes)
- **@splinetool/react-spline** (scène 3D interactive du hero)
- **react-parallax-tilt** (effets 3D au survol)
- **react-fast-marquee** (bandeau partenaires)
- **qrcode.react** (génération QR)
- **html5-qrcode** (scan caméra)
- **recharts** (graphiques des tableaux de bord)
- **canvas-confetti** (feedback de validation)
- **vite-plugin-pwa** (PWA, service worker, manifest, install prompt)
- **Axios** (client API + intercepteurs auth)
- Polices : **Geist**, **Geist Mono**, **Outfit** (`@fontsource-variable`)

### Backend (`/server`)
- **Node.js** + **Express 5** + **TypeScript**
- **Prisma ORM** + **MySQL**
- **JWT** (`jsonwebtoken`, access + refresh) pour l'authentification
- **bcryptjs** (hash des mots de passe)
- **Zod** (validation des entrées)
- **Multer** (upload des justificatifs)
- **web-push** (notifications push VAPID)
- Appelle le micro-service IA de façon **asynchrone** (`aiVerificationService` : soumission de job + polling du statut, `aiVerificationOrchestrator` : persistance en base et reprise après redémarrage) lors de la validation des inscriptions

### AI Service (`/ai-service`)
- **Python** + **FastAPI** (`uvicorn`)
- **Ollama** (LLM de vision, modèle `minicpm-v`) pour l'extraction des champs visibles des documents
- **OpenCV** (`opencv-python-headless`) pour le prétraitement d'image (redressement, recadrage, score de netteté/luminosité)
- **`mrz`** pour le parsing et la validation des zones MRZ (ICAO 9303, clés de contrôle)
- **`sentence-transformers`** (embeddings `all-MiniLM-L6-v2`) pour la similarité sémantique OCR ↔ MRZ ↔ attestation
- **`pypdf`** pour l'extraction de texte des attestations de scolarité au format PDF
- Scoring de risque pondéré (`FAIBLE` / `MOYEN` / `ELEVE`) combinant validité MRZ, cohérence OCR/MRZ, similarité d'embeddings et qualité d'image

### Infrastructure
- **Docker Compose** orchestrant l'ensemble de la stack en réseau interne (`madevpass-network`) : `mysql` (8.0), `ollama`, `ai-service`, ainsi que `server` et `client` (conteneurisés avec live-reload via bind mount + volume `node_modules` dédié)

---

## 🔐 Sécurité & RGPD

- Authentification **JWT** (access + refresh, rôle encodé dans le token)
- Middlewares de protection : `authMiddleware`, `requireRole` → `adminGuard` / `commercantGuard`
- **QR code à rotation** (token éphémère, anti-rejeu via signature et expiration)
- Mots de passe hachés (bcrypt)
- Validation systématique des payloads (Zod)
- **Vérification IA des justificatifs d'inscription** (CNI recto/verso + attestation de scolarité) : détection de documents falsifiés ou incohérents, score de risque exploitable par les administrateurs
- **Notifications push** sécurisées (VAPID via `web-push`, service worker `push-sw.js`) — clés VAPID exclusivement via variables d'environnement, aucune valeur par défaut hardcodée dans le code
- **Conformité RGPD** : demande de suppression de compte (statut `pending_deletion` + délai légal de 14 jours), gestion des documents justificatifs

---

## 📁 Architecture

```
madevpass/
├── client/                 # Application React (Vite + TS + Tailwind)
│   ├── public/             # favicon, manifest PWA, push-sw.js
│   └── src/
│       ├── pages/          # Landing, Login, Register, Profile + espaces etudiant/commercant/admin
│       ├── components/     # Navigation, BottomNav, StudentCard, MerchantCard, admin/, auth/, ui/, landing/
│       ├── theme/          # ThemeProvider (dark/light)
│       ├── hooks/          # useFavoris
│       ├── lib/, data/, types/
│       └── api/            # client Axios
├── server/                 # API Express (TS + Prisma + MySQL)
│   └── src/
│       ├── routes/         # auth, admin, commerces, categories, passages, documents, notifications, ai
│       ├── services/       # aiVerificationService (soumission/polling de jobs auprès du micro-service IA),
│       │                   # aiVerificationOrchestrator (persistance en base, reprise après redémarrage)
│       ├── middleware/     # authMiddleware, requireRole
│       └── lib/            # prisma client
├── ai-service/              # Micro-service FastAPI de vérification de documents
│   └── app/
│       ├── api/            # routes /health, /verify, /verify-inscription/jobs (soumission + statut,
│       │                   # traitement en tâche de fond via asyncio.to_thread)
│       ├── services/       # image_processor, llm_extractor, mrz_parser, pdf_extractor,
│       │                   # similarity, risk_scorer, identity_merger
│       ├── models/         # schémas Pydantic (ExtractedFields, MRZFields, VerificationResponse…)
│       └── core/           # configuration (pondérations du scoring, seuils de risque)
└── docker-compose.yml       # mysql + ollama + ai-service + server + client
```

---

## ✅ État actuel du projet

### Fonctionnel
- **Authentification** complète (inscription avec justificatif optionnel / différé, connexion, gestion d'erreurs sans rechargement)
- **Landing page** premium responsive (hero 3D Spline, compteurs animés données réelles Vienne — 470 commerçants, 1920 étudiants, 100% RGPD)
- **Espace Étudiant** : carte numérique, QR plein écran avec timer de rafraîchissement, annuaire filtrable (recherche, catégories, proximité), favoris
- **Espace Commerçant** : dashboard analytique (graphiques `recharts`), UI caisse de scan QR (cadre + ligne de balayage animée + confetti de validation), création / édition / suppression d'offres, édition du commerce
- **Espace Admin** : layout dédié (`AdminShell`), dashboard analytique, validation/refus des inscriptions assistée par l'IA (score de risque, champs extraits, incohérences détectées, badge d'échec avec relance manuelle), liste & édition des comptes, liste des commerçants, création directe de commerçants, gestion des catégories, vue QR admin
- **Micro-service IA de vérification de documents** : extraction des champs visibles (nom, prénom, date de naissance, numéro de document) via LLM de vision (Ollama/MiniCPM-V), transcription et validation de la zone MRZ (clés de contrôle ICAO 9303), prétraitement d'image (redressement, recadrage, score de qualité), comparaison OCR ↔ MRZ ↔ attestation de scolarité par similarité d'embeddings, calcul d'un score de risque pondéré
- **PWA** : installable (manifest + service worker via `vite-plugin-pwa`), bouton d'installation (`InstallButton`)
- **Notifications push** : abonnement VAPID, `push-sw.js`, route serveur `/api/notifications`
- **Dark / Light mode** natif avec persistance
- **Conformité RGPD** (demande de suppression, upload différé de justificatif)

### Données réelles intégrées
Statistiques basées sur la ville de Vienne : **470 commerçants partenaires**, **1920 étudiants**, **100% conforme RGPD**, inscription en **2 clics**.

---

## 🚀 Setup — démarrer le projet de zéro

### Prérequis
- **Docker & Docker Compose**
- ~8 Go d'espace disque libre (image `ollama` + poids du modèle `minicpm-v`)
- **Node.js 18+** et npm (uniquement pour l'option manuelle, sans Docker pour `server`/`client`)

### 1. Cloner le dépôt
```bash
git clone https://github.com/msm691/madevpass.git madevpass
cd madevpass
```

### 2. Configurer le backend
```bash
cd server
cp .env.example .env
```
Éditer `server/.env` :
```env
DATABASE_URL="mysql://user:password@localhost:3307/madevpass"
JWT_SECRET="<chaîne aléatoire d'au moins 32 caractères>"
JWT_REFRESH_SECRET="<autre chaîne aléatoire d'au moins 32 caractères>"
PORT=3001
AI_SERVICE_URL="http://localhost:8001"
AI_JOB_SUBMIT_TIMEOUT_MS=30000
AI_JOB_POLL_TIMEOUT_MS=10000
AI_JOB_POLL_INTERVAL_MS=15000
AI_JOB_MAX_WAIT_MS=1200000

VAPID_PUBLIC_KEY="<clé publique VAPID>"
VAPID_PRIVATE_KEY="<clé privée VAPID>"
VAPID_SUBJECT="mailto:contact@madevpass.fr"
```
> `DATABASE_URL` et `AI_SERVICE_URL` ci-dessus servent uniquement au mode manuel (option B). En mode tout-Docker (option A), `docker-compose.yml` surcharge automatiquement ces deux variables pour utiliser les noms de service internes (`mysql`, `ai-service`) — seuls les secrets (`JWT_*`, `VAPID_*`) sont lus depuis ce fichier.

Générer des secrets robustes si besoin :
```bash
node -e "console.log(require('crypto').randomBytes(32).toString('hex'))"
```

Générer une paire de clés VAPID (**obligatoire** — le serveur refuse de démarrer sans `VAPID_PUBLIC_KEY`/`VAPID_PRIVATE_KEY`, aucune valeur par défaut n'est fournie dans le code) :
```bash
npx web-push generate-vapid-keys
```

### 3. Lancer le projet

#### Option A — Tout via Docker Compose (recommandé)
```bash
docker compose up --build -d
```
Cela démarre cinq conteneurs :
- `madevpass-mysql` — MySQL 8.0 sur le port `3307` (interne `3306`)
- `madevpass-ollama` — serveur Ollama sur le port `11435`
- `madevpass-ai` — micro-service FastAPI de vérification de documents sur le port `8001`
- `madevpass-server` — API Express sur le port `3001`, avec live-reload (`ts-node-dev`, code monté en volume)
- `madevpass-client` — frontend Vite sur le port `3002`, avec live-reload (HMR, code monté en volume)

Au premier démarrage, l'API va télécharger automatiquement le modèle de vision `minicpm-v` en tâche de fond (peut prendre plusieurs minutes). Vérifier l'état avec :
```bash
curl http://localhost:8001/api/health
docker compose logs -f ai-service
```

Le conteneur `server` exécute automatiquement `prisma db push` à chaque démarrage (voir `server/Dockerfile`) : le schéma en base reste synchronisé avec `schema.prisma` sans étape manuelle, y compris après un `docker compose down` suivi d'un `up --build -d` (le volume `mysql_data` persiste, seule sa structure est mise à jour). Peupler la base de données de démo reste manuel et optionnel :
```bash
docker compose exec server npm run db:seed     # données de démo (facultatif)
```
> Le projet n'a pas de dossier `prisma/migrations` committé : le schéma est géré en mode déclaratif via `db:push`, pas `db:migrate` (`prisma migrate dev`), qui attendrait une baseline de migrations inexistante ici et pourrait échouer ou proposer un reset destructeur de la base.

Suivre les logs / arrêter :
```bash
docker compose logs -f server client
docker compose down
```

#### Option B — Backend et frontend en local (hors Docker)
Garder MySQL, Ollama et l'AI Service en conteneurs, mais lancer `server`/`client` à la main (utile pour debugger avec des outils natifs) :
```bash
docker compose up -d mysql ollama ai-service
```
Puis :
```bash
cd server
npm install
npm run db:generate
npm run db:push        # synchronise le schéma en base (déclaratif, pas de migrations committées)
npm run db:seed        # données de démo (facultatif)
npm run dev             # démarre l'API sur http://localhost:3001
```
> ⚠️ Sur certains environnements (notamment WSL), `npx prisma db push`/`db:generate` lancés **depuis l'hôte** peuvent échouer avec `Unknown authentication plugin 'sha256_password'` en se connectant au MySQL dockerisé, alors que la même commande fonctionne depuis l'intérieur d'un conteneur. Si ça arrive, lancez plutôt `docker compose exec server npm run db:push` (le conteneur `server` utilise un moteur Prisma compatible avec l'image MySQL du projet).
```bash
cd client
npm install
npm run dev             # démarre l'app sur http://localhost:3000
```
Le serveur de dev Vite proxifie automatiquement `/api` et `/uploads` vers `http://127.0.0.1:3001` (voir `client/vite.config.ts`, variable `VITE_API_PROXY_TARGET` surchargée uniquement par Docker Compose) — aucune variable d'environnement n'est requise côté client en local.

### 4. Vérifier que tout communique
1. Ouvrir le frontend (`http://localhost:3002` en Docker, `http://localhost:3000` en mode manuel) → la landing page doit s'afficher
2. Créer un compte étudiant → connexion à MySQL via Prisma
3. En tant qu'admin (voir `prisma/seed.ts` pour le compte de démo), valider une inscription avec justificatif → soumet un job au micro-service IA (`http://localhost:8001/api/verify-inscription/jobs`) ; le badge de statut passe de « en cours » au résultat final une fois le job terminé (l'admin peut aussi relancer manuellement une analyse en échec)

### Récapitulatif des ports
| Service | Port (Docker) | Port (manuel) | Description |
|---|---|---|---|
| Client (Vite) | `3002` | `3000` | Frontend React |
| Serveur (Express) | `3001` | `3001` | API REST |
| MySQL | `3307` → `3306` | `3307` → `3306` | Base de données |
| AI Service (FastAPI) | `8001` → `8000` | `8001` → `8000` | Vérification de documents |
| Ollama | `11435` → `11434` | `11435` → `11434` | Serveur LLM de vision |

> Le client Docker est exposé sur `3002` (au lieu de `3000`) pour éviter tout conflit avec un port déjà utilisé sur la machine hôte — modifiable dans `docker-compose.yml`.

### Build de production
```bash
# Backend
cd server && npm run build && npm start

# Frontend
cd client && npm run build && npm run preview
```

---

> Projet MADEV Pass — carte étudiante numérique & réseau de commerçants partenaires de Vienne.
