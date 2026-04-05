# Security Misconfiguration-4-Easter Egg

## Methodology
* **Techniques used:** Directory Enumeration, Forced Browsing.
* **Tools used:** Web Browser.
* **Steps:**
  1. Placed a standard order and observed the "Order Confirmation" link, which opened a PDF file hosted at the `/ftp/` directory (e.g., `/ftp/order_8a49-facea20455d38d68.pdf`).
  2. Removed the specific filename from the URL to directly access the parent directory (`/ftp/`).
  3. Discovered that the server had Directory Listing enabled, exposing all hosted files.
  4. Identified a suspicious file named `eastere.gg` among the legitimate order confirmations.
  5. Leveraged a Poison Null Byte attack (`eastere.gg%2500.pdf`) to bypass the server's file extension filter and successfully access the hidden file.

## Vulnerabilities
* **Vulnerability name:** Security Misconfiguration (Directory Listing Enabled).
* **Affected components:** Web Server configuration (serving the `/ftp` route).
* **Estimated severity level:** Low to Medium.

## Risks
* **Business impact:** Exposing directory contents allows attackers to map the server's file structure and discover sensitive files, backups, hidden features (like easter eggs), or other users' confidential documents (e.g., invoices, order receipts).

## Actions
* **Suggested remediation fixes:** Disable directory listing (auto-index) at the web server configuration level (e.g., in Nginx, set `autoindex off;`, or in Apache, remove the `Indexes` option).
* **Risk mitigation strategies:** Serve sensitive files (like user order confirmations) via a secure, authenticated API endpoint rather than a static, public-facing directory.
* **Best security practices:** Ensure that web roots only expose files strictly necessary for the client-side application. Do not store application source files or miscellaneous documents in public directories.
