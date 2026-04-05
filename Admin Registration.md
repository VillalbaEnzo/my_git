# Broken Access Control-3-Admin Registration

## Methodology
* **Techniques used:** Mass Assignment exploitation, Parameter tampering, Privilege escalation.
* **Tools used:** Burp Suite (Proxy and Repeater modules).
* **Steps:**
  1. Initiated the standard user registration process via the application's frontend.
  2. Intercepted the outgoing HTTP POST request targeting the user creation API endpoint using Burp Suite Proxy.
  3. Analyzed the JSON payload and identified that the API might improperly bind client-side input to server-side object properties.
  4. Forwarded the request to the **Repeater** module and manually injected the `"role":"admin"` key-value pair into the JSON body.
  5. Changed the email address parameter to a new, unique value to bypass the server's "user already exists" validation constraint encountered on the first attempt.
  6. Sent the modified payload. The server accepted the request (HTTP 201 Created) and successfully registered the new account with administrator privileges.

## Vulnerabilities
* **Vulnerability name:** Mass Assignment / Improper Privilege Management (Broken Access Control).
* **Affected components:** User Registration API and Identity/Role Management module.
* **Estimated severity level:** Critical.

## Risks
* **Business impact:** Full system compromise. By bypassing the intended authorization flow, an attacker gains unauthorized administrative access. This allows for total control over the application, including the ability to view sensitive data of all users, modify system configurations, alter financial records, or shut down services.

## Actions
* **Suggested remediation fixes:** Implement strict payload whitelisting (using Data Transfer Objects or explicitly defining allowed fields). The backend code must be configured to completely ignore any unexpected parameters, such as `role` or `isAdmin`, supplied during a standard registration request.
* **Risk mitigation strategies:** Hardcode the default role assignment for all public registration endpoints to the lowest possible privilege level (e.g., `customer`). Administrative roles should only be granted through a separate, protected internal dashboard accessible exclusively by existing super-administrators.
* **Best security practices:** Apply the Principle of Least Privilege (PoLP). Ensure that the underlying framework or ORM (Object-Relational Mapper) is explicitly configured to prevent mass assignment vulnerabilities by marking sensitive database fields as read-only or protected from client-side binding.