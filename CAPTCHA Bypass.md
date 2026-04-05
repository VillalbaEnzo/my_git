# Broken Anti-Automation-3-CAPTCHA Bypass

## Methodology
* **Techniques used:** Replay attack.
* **Tools used:** Burp Suite (Repeater module).
* **Steps:**
  1. Filled out a legitimate customer feedback form on the application and manually solved the CAPTCHA.
  2. Intercepted the corresponding HTTP POST request and sent it to the **Repeater** tab in Burp Suite.
  3. Mass-sent the exact same request by clicking "Send" repeatedly (more than 10 times in under 20 seconds) without changing the `captchaId` token.
  4. Observation: The server processed and accepted all requests (returning positive HTTP status codes), allowing the spam to go through.

## Vulnerabilities
* **Vulnerability name:** Broken Anti-Automation (CAPTCHA validation reuse).
* **Affected components:** Customer Feedback API.
* **Estimated severity level:** Medium.

## Risks
* **Business impact:** Massive spam potential. An attacker can flood the database with fake feedback, completely skewing the company's satisfaction metrics and unnecessarily overloading the database.

## Actions
* **Suggested remediation fixes:** The server must invalidate and destroy the `captchaId` immediately after its first successful use. One token should strictly equal one submission.
* **Risk mitigation strategies:** Implement Rate Limiting to temporarily block IP addresses that send too many similar requests within a short timeframe.
* **Best security practices:** Replace basic mathematical CAPTCHAs with robust, industry-standard anti-bot solutions (e.g., reCAPTCHA, Turnstile) that analyze user behavior and manage session security properly.
