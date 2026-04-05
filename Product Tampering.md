# Broken Access Control-3-Product Tampering

## Methodology
* **Techniques used:** HTTP Verb Tampering, Insecure Direct Object Reference (IDOR), Parameter Tampering.
* **Tools used:** Burp Suite (Repeater module).
* **Steps:**
  1. Identified the API endpoint responsible for handling the "OWASP SSL Advanced Forensic Tool (O-Saft)" product data (`/api/Products/9`).
  2. Forwarded the standard request to the **Repeater** module in Burp Suite.
  3. Modified the HTTP method from `GET` to `PUT` to attempt an unauthorized resource update.
  4. Added the `Content-Type: application/json` HTTP header to properly format the payload.
  5. Injected the following JSON body to overwrite the product description and alter the hyperlink:
     ```json
     {
       "description": "O-Saft is an easy to use tool to show information about SSL certificate and tests the SSL connection according given list of ciphers and various SSL configurations. <a href=\"[https://owasp.slack.com](https://owasp.slack.com)\" target=\"_blank\">More...</a>"
     }
     ```
  6. Sent the request. The server accepted the `PUT` request without requiring administrative privileges, successfully updating the database record.

## Vulnerabilities
* **Vulnerability name:** Broken Access Control / Improper Authorization (IDOR on Update Operation).
* **Affected components:** Product Catalog API (`/api/Products`).
* **Estimated severity level:** High.

## Risks
* **Business impact:** Unauthorized data modification and Website Defacement. An attacker can freely alter product catalogs, descriptions, and potentially prices. By injecting arbitrary links, attackers can conduct phishing campaigns directly from the company's domain or redirect customers to malicious websites, causing severe reputational damage and liability issues.

## Actions
* **Suggested remediation fixes:** Implement strict server-side authorization checks on all state-changing HTTP methods (`PUT`, `POST`, `PATCH`, `DELETE`). The API must verify that the currently authenticated user has the explicit `admin` role before processing any modifications to the product catalog.
* **Risk mitigation strategies:** Reject any HTTP methods on endpoints that do not strictly require them (e.g., if regular users only need to view products, explicitly block `PUT` requests for non-admin sessions at the API gateway level).
* **Best security practices:** Adopt a "Deny by Default" security posture for API routing. Ensure that role-based access control (RBAC) is enforced at the controller level for every individual API endpoint.
