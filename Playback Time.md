# Business Logic-4-Playback Time

## Methodology
* **Techniques used:** Source code analysis, OSINT/Enumeration, SQL Injection (Authentication Bypass), Forced Browsing, Parameter Tampering.
* **Tools used:** Browser Developer Tools, Burp Suite (Proxy and Repeater).
* **Steps:**
  1. Analyzed the client-side JavaScript bundle (`main.js`) and discovered a hidden frontend route: `/#/accounting` using CTRL+F and searching `path:`.
  2. Attempted direct access to the route but received a "403 Forbidden" error, indicating missing privileges.
  3. Enumerated product reviews to find a privileged user and identified the email `accountant@juice-sh.op` on the "OWASP Juice Shop Card (non-foil)" product page.
  4. Exploited an SQL Injection vulnerability on the login form by entering the payload `accountant@juice-sh.op'--` in the email field, successfully bypassing the password check and authenticating as the accountant.
  5. Navigated to the now-accessible `/#/accounting` dashboard.
  6. Attempted to change a product's price to a negative value via the UI, which failed as the frontend clamped the value to 0.
  7. Intercepted the price update HTTP request and forwarded it to the **Repeater** module in Burp Suite.
  8. Modified the price parameter to a negative value in the raw JSON payload and sent the request, successfully bypassing the client-side validation.
  9. Added the manipulated product to the shopping basket and completed the checkout process, achieving a negative total and unauthorized financial gain.

## Vulnerabilities
* **Vulnerability name:** Authentication Bypass (SQL Injection) combined with Business Logic Flaw (Missing Server-Side Validation for Negative Prices).
* **Affected components:** Authentication API, Accounting Dashboard, and Shopping Cart / Checkout API.
* **Estimated severity level:** Critical.

## Risks
* **Business impact:** Direct and severe financial loss. An attacker can manipulate product pricing to negative values, forcing the e-commerce platform to effectively "owe" the attacker money upon checkout. Additionally, the SQL injection allows unauthorized access to sensitive employee accounts, which could lead to further data breaches and internal system manipulation.

## Actions
* **Suggested remediation fixes:** 1. **SQLi:** Implement Prepared Statements (Parameterized Queries) on the backend for all database interactions to completely neutralize SQL injection vectors.
  2. **Business Logic:** Enforce strict server-side boundary checks on the price update API to ensure the `price` parameter is strictly greater than or equal to `0`.
* **Risk mitigation strategies:** Implement robust server-side Access Control checks for all sensitive API endpoints (like accounting), ensuring that unauthorized users receive a 403/401 at the API level, rather than just hiding the frontend UI.
* **Best security practices:** Never trust client-side validation. All data inputs (like price values and quantities) must be independently validated and sanitized by the backend server before processing any financial transaction.
