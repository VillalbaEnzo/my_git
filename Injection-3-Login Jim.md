# Injection-3-Login Jim

## Methodology
* **Techniques used:** OSINT (Open Source Intelligence) / Enumeration, SQL Injection (Authentication Bypass).
* **Tools used:** Web Browser.
* **Steps:**
  1. Performed enumeration by browsing product reviews to identify target user accounts.
  2. Located a review for the "Green Smoothie" product written by "Jim", revealing his email address: `jim@juice-sh.op`.
  3. Navigated to the login page and entered the discovered email followed by an SQL injection payload: `jim@juice-sh.op'--`.
  4. Submitted the form with a dummy password.
  5. Observation: The `'--` sequence successfully commented out the remainder of the server's SQL query (the password check logic), allowing an immediate login to Jim's account without a valid password.

## Vulnerabilities
* **Vulnerability name:** SQL Injection (Authentication Bypass).
* **Affected components:** Login / Authentication API.
* **Estimated severity level:** High.

## Risks
* **Business impact:** Unauthorized account access and data breach. By bypassing the password requirement, an attacker can hijack specific user sessions. This leads to the exposure of personal information, order history, and sensitive data belonging to the victim, severely compromising user trust and legal compliance (GDPR).

## Actions
* **Suggested remediation fixes:** Implement Prepared Statements (Parameterized Queries) for all authentication logic. The application must treat user input as data only, never as executable code.
* **Risk mitigation strategies:** Use a modern ORM (Object-Relational Mapping) or a security library that automatically handles input escaping.
* **Best security practices:** Regularly audit the codebase for raw SQL concatenations and enforce strict input validation for all login fields.
