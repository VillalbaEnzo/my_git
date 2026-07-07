const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
    host: process.env.SMTP_HOST || 'mailpit',
    port: process.env.SMTP_PORT || 1025,
    secure: false,
    auth: {
        user: '',
        pass: ''
    }
});

const sendEmail = async (to, subject, htmlContent) => {
    try {
        const info = await transporter.sendMail({
            from: '"Support Transalp" <noreply@transalp.fr>',
            to: to,
            subject: subject,
            html: htmlContent
        });
        console.log(`[MAIL ENVOYÉ] ${to} | Sujet: "${subject}" | Mailpit ID: ${info.messageId}`);
        return info;
    } catch (error) {
        console.error("[ERREUR MAIL] Échec de l'envoi :", error);
        throw error;
    }
};

const sendAccountCreationEmail = async (email, temporaryPassword) => {
    const html = `
        <div style="font-family: Arial, sans-serif; padding: 20px;">
            <h2>Bienvenue chez Transalp</h2>
            <p>Votre compte a été créé avec succès par l'administrateur.</p>
            <p>Voici votre email et votre mot de passe temporaire: </p>
            <h4 style="background: #f4f4f4; padding: 10px; display: inline-block;">${email}</h4>
            <br>
            <h4 style="background: #f4f4f4; padding: 10px; display: inline-block;">${temporaryPassword}</h4>
            <p>Par mesure de sécurité, il vous sera demandé de modifier ce mot de passe lors de votre première connexion.</p>
            <br>
            <a href="http://localhost:3000/auth/login" style="padding: 10px 15px; background: #007bff; color: white; text-decoration: none; border-radius: 5px;">Se connecter à mon compte</a>
        </div>
    `;
    return sendEmail(email, "Création de votre compte Transalp", html);
};

const sendPasswordResetEmail = async (email, resetLink) => {
    const html = `
        <div style="font-family: Arial, sans-serif; padding: 20px;">
            <h2>Réinitialisation de votre mot de passe</h2>
            <p>Vous (ou un administrateur) avez demandé la réinitialisation de votre mot de passe.</p>
            <p>Veuillez cliquer sur le lien ci-dessous pour en créer un nouveau. Ce lien est valide pendant 1 heure.</p>
            <br>
            <a href="${resetLink}" style="padding: 10px 15px; background: #dc3545; color: white; text-decoration: none; border-radius: 5px;">Réinitialiser mon mot de passe</a>
            <br><br>
            <p style="font-size: 12px; color: #666;">Si vous n'êtes pas à l'origine de cette demande, vous pouvez ignorer cet email en toute sécurité.</p>
        </div>
    `;
    return sendEmail(email, "Réinitialisation de mot de passe Transalp", html);
};

module.exports = {
    sendAccountCreationEmail,
    sendPasswordResetEmail
};
