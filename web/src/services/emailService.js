// To use : Nodemailer (SMTP)
const sendAccountCreationEmail = async (email, password) => {
  console.log(`\n=============================================================`);
  console.log(`✉️  [SIMULATION EMAIL] Envoi à : ${email}`);
  console.log(`Sujet : Votre compte Transalp NC a été créé`);
  console.log(`Corps du message :`);
  console.log(`Bonjour,`);
  console.log(`Votre ticket de non-conformité a bien été pris en compte.`);
  console.log(`Un espace client a été créé automatiquement pour vous permettre de suivre son avancement.`);
  console.log(`\nVoici vos identifiants de connexion temporaires :`);
  console.log(`- Email : ${email}`);
  console.log(`- Mot de passe : ${password}`);
  console.log(`\n⚠️ Lors de votre première connexion, il vous sera demandé de modifier ce mot de passe pour des raisons de sécurité.`);
  console.log(`=============================================================\n`);

  return true;
};

const sendPasswordResetEmail = async (email, password) => {
  console.log(`\n=============================================================`);
  console.log(`✉️  [SIMULATION EMAIL] Réinitialisation pour : ${email}`);
  console.log(`Sujet : Réinitialisation de votre mot de passe Transalp NC`);
  console.log(`Corps du message :`);
  console.log(`Bonjour,`);
  console.log(`Une demande de réinitialisation de mot de passe a été effectuée pour votre compte.`);
  console.log(`Voici votre mot de passe temporaire : ${password}`);
  console.log(`⚠️ Lors de votre prochaine connexion, vous serez obligé de le modifier.`);
  console.log(`=============================================================\n`);
  return true;
};

module.exports = {
  sendAccountCreationEmail,
  sendPasswordResetEmail
};