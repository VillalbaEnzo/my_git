# Transalp NC Project Documentation

## 1. Purpose of this repository

This repository appears to be a multi-service application centered around a web-facing workflow and an AI-assisted processing pipeline. From the available folder structure, the system is divided into three main areas:

- `web/`: a Node.js-based application that exposes the user-facing interface and API layer
- `ai-worker/`: a Python-based background/processing service that performs AI-driven classification and analysis
- `db/`: SQL initialization scripts and database-related setup

The project likely supports a workflow where incoming requests (such as tickets, items, or uploaded content) are received by the web layer, persisted in a database, and processed by an AI worker that performs classification, image analysis, and/or product matching.

---

## 2. High-level architecture

The repository follows a modular, service-oriented design:

- The `web` component handles HTTP requests, route definitions, and business-facing interactions.
- The `ai-worker` component handles AI tasks such as:
  - classification
  - image/vision analysis
  - product matching
  - database-backed processing
- The `db` component defines the schema and initial database state.

This separation makes it easier to evolve the UI/API layer independently from the AI processing logic.

---

## 3. Repository structure

### Root
The repository root contains three top-level folders:

- `db/`
- `web/`
- `ai-worker/`

This layout strongly suggests a small distributed system rather than a single monolithic application.

---

## 4. Component breakdown

### 4.1 `db/`
Purpose:
- Contains database initialization and schema setup.

Files:
- `db/init.sql`

Responsibilities:
- Defines the database schema and initial objects
- Likely creates tables, indexes, and seed data if needed
- Serves as the foundation for persistence across the application

This is the data layer for the system and is likely used by both the web service and the AI worker.

---

### 4.2 `web/`
Purpose:
- Provides the application entrypoint for the front-end/back-end layer.
- Likely handles HTTP endpoints, request validation, and communication with the AI worker and database.

Files and folders:
- `web/package.json`
- `web/Dockerfile`
- `web/src/server.js`
- `web/src/routes/tickets.js`
- `web/src/services/aiClient.js`
- `web/src/services/db.js`
- `web/src/views/`

#### `web/package.json`
Likely defines:
- Node.js project metadata
- runtime dependencies
- scripts for development, testing, and start-up

#### `web/Dockerfile`
Used to containerize the web service, making it easier to run consistently across environments.

#### `web/src/server.js`
Likely contains:
- application bootstrapping
- middleware setup
- router registration
- port configuration
- global error handling

This is the primary entrypoint for the web service.

#### `web/src/routes/tickets.js`
Likely defines routes related to ticket management, such as:
- creating tickets
- retrieving tickets
- updating ticket status
- listing tickets
- posting data for AI processing

The name suggests this is one of the core domain workflows of the application.

#### `web/src/services/aiClient.js`
Likely encapsulates communication with the AI worker. It may:
- send payloads to an AI processing endpoint
- wrap API request logic
- handle retries, errors, or response normalization

#### `web/src/services/db.js`
Likely contains:
- database connection logic
- query helpers
- reusable persistence utilities for the web layer

#### `web/src/views/`
Likely contains templates or static content used by the web application. The exact implementation may be server-rendered views or frontend assets.

---

### 4.3 `ai-worker/`
Purpose:
- Implements the AI processing capabilities of the system.
- Acts as a specialized background worker or service for analyzing incoming data.

Files and folders:
- `ai-worker/Dockerfile`
- `ai-worker/config.py`
- `ai-worker/gravity.py`
- `ai-worker/main.py`
- `ai-worker/requirements.txt`
- `ai-worker/catalogue/`
- `ai-worker/prompts/prompt_classify.txt`
- `ai-worker/prompts/prompt_vision.txt`
- `ai-worker/services/__init__.py`
- `ai-worker/services/classifier.py`
- `ai-worker/services/database.py`
- `ai-worker/services/ollama.py`
- `ai-worker/services/product_matcher.py`
- `ai-worker/services/vision.py`
- `ai-worker/uploads/`

#### `ai-worker/main.py`
Likely the main execution entrypoint for the worker.
It may:
- initialize configuration
- load input data
- call the classifier and vision services
- persist results into the database
- coordinate the overall workflow

#### `ai-worker/config.py`
Likely contains environment-specific configuration such as:
- model names
- paths to prompts or data
- upload directories
- database connection settings
- service endpoints

#### `ai-worker/gravity.py`
This file name suggests that it contains a domain-specific or scoring-related component. It may be:
- a helper module for ranking or prioritizing items
- a utility related to weighting or scoring logic
- a specialized algorithm used in the AI pipeline

Its exact role should be confirmed by reading the file directly.

#### `ai-worker/requirements.txt`
Defines the Python dependencies needed by the worker service.

#### `ai-worker/prompts/`
Contains text prompt templates used for AI inference.

- `prompt_classify.txt`
  - likely used to instruct the model to classify an input item or request

- `prompt_vision.txt`
  - likely used for vision/image-based tasks

These files are important because they define how the AI model interprets incoming data.

#### `ai-worker/services/`
Contains modular Python services that divide the worker responsibilities.

- `classifier.py`
  - likely handles text or semantic classification logic
  - may invoke an LLM or heuristic classifier

- `vision.py`
  - likely handles image analysis or computer-vision tasks
  - may extract labels, attributes, or visual features

- `product_matcher.py`
  - likely maps classified results to products or known catalog entries
  - may perform fuzzy matching or similarity-based lookup

- `ollama.py`
  - likely contains logic for interacting with Ollama models
  - may be the main bridge between the Python service and local LLM inference

- `database.py`
  - likely encapsulates database access for the worker
  - may handle reading from and writing to the database

- `__init__.py`
  - marks the folder as a Python package

#### `ai-worker/catalogue/`
Likely contains product catalog or reference data used by the product matching logic. This may include:
- item names
- metadata
- categorization references
- known product mappings

#### `ai-worker/uploads/`
Likely stores temporary or persistent uploaded files such as:
- images
- documents
- user attachments

This directory is important for workflows that depend on file-based input.

---

## 5. Likely runtime workflow

Although the exact business logic cannot be confirmed without reading every source file, the repository structure strongly suggests the following workflow:

1. A user or client sends a request to the web service.
2. The web service receives the request and routes it through `tickets.js`.
3. The request may be stored in the database via `db.js`.
4. The web service calls the AI worker via `aiClient.js`.
5. The AI worker receives the task and uses:
   - prompt templates
   - classifier logic
   - vision analysis
   - product matching
6. The worker writes results back to the database or returns structured output to the web layer.
7. The web layer exposes the enriched response to the client.

This is a classic “web API + background AI processor + database” architecture.

---

## 6. Technology assumptions based on the repository layout

### Web layer
The `web` component appears to be built with Node.js because of:
- `package.json`
- `server.js`
- service modules under `src/services`

The likely stack is:
- Node.js
- an HTTP framework such as Express
- server-side views or API routes

### AI layer
The `ai-worker` component appears to be built in Python because of:
- `.py` files
- `requirements.txt`
- service modules and prompt files

The likely stack includes:
- Python 3
- one or more AI inference libraries
- Ollama integration for local model access
- file and database I/O

### Database layer
The `db` component suggests:
- a relational database
- SQL initialization scripts
- schema design managed in `init.sql`

---

## 7. Deployment and containerization

Both the web service and the AI worker contain their own `Dockerfile`, which suggests the project is intended to be containerized.

This implies a deployment model similar to:

- one container for the web service
- one container for the AI worker
- one container or service for the database

Dockerization helps make the system more portable and easier to deploy in development, staging, or production.

---

## 8. Development considerations

The repository appears to be in an early or intermediate stage of development, based on the presence of:

- a clear service split
- dedicated database initialization
- AI prompt templates
- upload handling
- container support

Possible next steps for the project could include:
- adding a top-level Docker Compose setup
- documenting environment variables
- adding tests to the web and worker services
- improving observability and logging
- adding authentication and authorization if the service is exposed publicly
- defining data models and API contracts more explicitly

---

## 9. Key files at a glance

- `db/init.sql` — database schema and initialization logic
- `web/package.json` — Node.js project metadata and dependencies
- `web/src/server.js` — web service entrypoint
- `web/src/routes/tickets.js` — ticket-related routes
- `web/src/services/aiClient.js` — AI worker integration
- `web/src/services/db.js` — database access layer
- `ai-worker/main.py` — AI worker entrypoint
- `ai-worker/config.py` — configuration
- `ai-worker/gravity.py` — auxiliary domain logic
- `ai-worker/services/classifier.py` — classification logic
- `ai-worker/services/vision.py` — image/vision processing logic
- `ai-worker/services/product_matcher.py` — product matching logic
- `ai-worker/services/ollama.py` — LLM integration
- `ai-worker/services/database.py` — database access for the worker
- `ai-worker/prompts/prompt_classify.txt` — classification prompt
- `ai-worker/prompts/prompt_vision.txt` — vision prompt
- `ai-worker/uploads/` — uploaded files storage

---

## 10. Summary

This project is best understood as a full-stack, multi-service application with:

- a web/API layer
- an AI processing worker
- a relational database
- container-based deployment support

The repository is organized around clear separation of concerns:
- user interaction and API handling live in `web/`
- AI inference and domain-specific processing live in `ai-worker/`
- persistent data and schema definitions live in `db/`

This structure is well suited for building an intelligent application that processes requests, analyzes content, and stores structured results for later use.