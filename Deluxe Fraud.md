# Broken Access Control-3-Deluxe Fraud

## Methodology
* **Techniques used:** Client-side restriction bypass (DOM manipulation), Parameter tampering, Business logic bypass.
* **Tools used:** Web Browser Developer Tools (Inspector), Burp Suite (Proxy/Repeater).
* **Steps:**
  1. Created a standard, non-premium user account and navigated to the Deluxe Membership purchase page (`/#/deluxe-membership`).
  2. Inspected the disabled "Continue" button using the browser's Developer Tools and manually modified its HTML classes/attributes to remove the restriction and render it clickable.
  3. Clicked the newly enabled button and intercepted the resulting HTTP checkout request using Burp Suite.
  4. Forwarded the request to the **Repeater** module and manipulated the payload: altered the `paymentMode` parameter to `"none"` and changed the `paymentId` to a random, non-existent ID.
  5. Sent the modified request. The server failed to validate the actual payment and granted the Deluxe Membership status based solely on the manipulated parameters.

## Vulnerabilities
* **Vulnerability name:** Broken Access Control / Business Logic Flaw (Client-side validation bypass & Insecure Parameter Tampering).
* **Affected components:** Checkout/Payment API and Client-side UI validation.
* **Estimated severity level:** High.

## Risks
* **Business impact:** Direct financial loss and service theft. Attackers can access premium features, content, and services without paying. This directly harms the business's revenue stream and can consume premium server resources.

## Actions
* **Suggested remediation fixes:** Implement strict server-side validation for all payment workflows. The backend must independently verify that a valid, confirmed payment transaction exists (e.g., via a secure payment gateway webhook) before upgrading any user's account tier.
* **Risk mitigation strategies:** Never rely on client-side state (such as disabled buttons or hidden HTML fields) to enforce authorization or payment rules.
* **Best security practices:** Adopt a secure state-machine approach for checkout flows. The server should reject any request containing an invalid or bypassed `paymentMode` and should validate the integrity of the `paymentId` against the actual payment provider's database.