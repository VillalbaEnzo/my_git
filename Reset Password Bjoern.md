# Broken Authentication-3-Reset Password Bjoern

## Methodology
* **Techniques used:** OSINT (Open Source Intelligence), Data Enumeration.
* **Tools used:** Web Browser, Search Engine / Twitter (X).
* **Steps:**
  1. Attempted to trigger the password reset using `bjoern@juice-sh.op`, but the security question ("Your ZIP/postal code when you were a teenager?") did not match the target question ("Name of your favorite pet?").
  2. Enumerated customer feedback on various products to find the correct email. Discovered `bjoern@owasp.org` in a review for the "OWASP Juice Shop LEGO™ Tower".
  3. Entered the correct email into the Forgot Password form, which successfully prompted the expected security question: "Name of your favorite pet?".
  4. Conducted OSINT by investigating the target (Bjoern Kimminich) on social media.
  5. Located a public tweet from his official account (`@bkimminich`): `https://x.com/bkimminich/status/1594985736650035202`, which explicitly mentioned his cat named "Zaya".
  6. Submitted "Zaya" as the answer to the security question, which was accepted and allowed for a successful password reset.

## Vulnerabilities
* **Vulnerability name:** Broken Authentication (Insecure Knowledge-Based Authentication / OSINT vulnerability).
* **Affected components:** Password Reset Mechanism / Authentication API.
* **Estimated severity level:** High.

## Risks
* **Business impact:** Account Takeover (ATO). Relying on publicly available or easily discoverable personal information allows attackers to bypass authentication entirely. This can lead to unauthorized data access, identity theft, lateral movement within the application, and severe reputational damage.

## Actions
* **Suggested remediation fixes:** Completely deprecate the use of Knowledge-Based Authentication (security questions). Replace it with secure, time-limited password reset tokens sent directly to the user's verified email address.
* **Risk mitigation strategies:** If security questions are absolutely mandatory due to legacy constraints, force users to create their own custom questions and answers, and treat the answers as salted hashes in the database.
* **Best security practices:** Implement Multi-Factor Authentication (MFA / 2FA) so that even if a password or reset mechanism is compromised, a secondary dynamic factor is required to gain access.
