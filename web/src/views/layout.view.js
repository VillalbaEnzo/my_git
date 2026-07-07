const renderLayout = (title, content, userRole = null) => {
    const isAdmin = userRole === 'qualite' || userRole === 'key_user';

    const sidebar = isAdmin ? `
        <aside style="width: 250px; flex-shrink: 0; background-color: #2c3e50; color: white; min-height: 100vh; padding: 20px;">
            <h2 style="color: #18bc9c; text-align: center; margin-bottom: 30px;">Admin Panel</h2>
            <nav style="display: flex; flex-direction: column; gap: 15px;">
                <a href="/admin/dashboard" style="color: white; text-decoration: none; padding: 10px; border-radius: 5px; background: #34495e;">📊 Dashboard</a>
                <a href="/admin/validation" style="color: white; text-decoration: none; padding: 10px; border-radius: 5px; background: #34495e;">🤖 Validation IA</a>
                <a href="/tickets" style="color: white; text-decoration: none; padding: 10px; border-radius: 5px; background: #34495e;">📋 Tous les tickets</a>
                <a href="/auth/profile" style="color: white; text-decoration: none; padding: 10px; border-radius: 5px; background: #34495e;">⚙️ Paramètres</a>
            </nav>
        </aside>
    ` : '';

    return `
    <!DOCTYPE html>
    <html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>${title}</title>
        <style>
            /* On force le body à gérer la disposition en ligne */
            body { 
                margin: 0; 
                font-family: Arial, sans-serif; 
                background-color: #f4f7f6; 
                color: #333; 
                display: flex; 
                min-height: 100vh;
            }
            main { 
                flex-grow: 1; 
                padding: 20px; 
                /* Permet au contenu de ne pas déborder si l'écran est petit */
                overflow-x: hidden; 
            }
        </style>
    </head>
    <body>
        ${sidebar}
        <main>
            ${content}
        </main>
    </body>
    </html>
    `;
};

module.exports = {renderLayout};