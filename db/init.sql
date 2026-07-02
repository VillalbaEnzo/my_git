CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    email VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    -- NOUVEAU : Ajout des rôles qualite et key_user
    role ENUM('client', 'employe', 'qualite', 'key_user') NOT NULL,
    nom VARCHAR(255) DEFAULT 'Non renseigné',
    type_client VARCHAR(100) DEFAULT 'Inconnu',
    must_change_password BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS tickets (
    id                  INT AUTO_INCREMENT PRIMARY KEY,
    nc_number           VARCHAR(50) UNIQUE,
    client_id           INT,
    assigned_to         INT,
    email               VARCHAR(255) NOT NULL,
    profil              ENUM('client','employe') NOT NULL,
    description         TEXT,
    reference           VARCHAR(100),
    order_number        VARCHAR(100),
    installation_pose   DATE,
    ai_type_nc          VARCHAR(100),
    ai_cause            VARCHAR(100),
    ai_action_generale  VARCHAR(100),
    ai_service_impacte  VARCHAR(100),
    ai_resume           TEXT,
    ai_confiance        DECIMAL(4,3),
    ai_errors           JSON,
    ai_visual_analyses  JSON,
    gravity_score       TINYINT UNSIGNED,
    gravity_label       VARCHAR(50),
    gravity_detail      JSON,
    status              VARCHAR(50) DEFAULT 'pending_ai',
    created_at          TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at          TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (client_id) REFERENCES users(id) ON DELETE SET NULL,
    FOREIGN KEY (assigned_to) REFERENCES users(id) ON DELETE SET NULL
);

INSERT INTO users (email, password_hash, role, nom, must_change_password)
VALUES ('admin@transalp.fr', '$2b$10$eOpRWJ4hBSG5dfC1KJwT3emTc5DlQxzLbMUvQaaWfRBI/mtDVCjvu', 'key_user', 'Key User Principal', TRUE)
ON DUPLICATE KEY UPDATE id=id;

INSERT INTO users (email, password_hash, role, nom, must_change_password)
VALUES ('qualite@transalp.fr', '$2b$10$eOpRWJ4hBSG5dfC1KJwT3emTc5DlQxzLbMUvQaaWfRBI/mtDVCjvu', 'qualite', 'Service Qualité', TRUE)
ON DUPLICATE KEY UPDATE id=id;