# Injection-4-Poison Null Byte

## Methodology
* **Techniques used:** File Extension Bypass, Poison Null Byte Injection.
* **Tools used:** Web Browser.
* **Steps:**
  1. Attempted to access the restricted file `eastere.gg` located in the `/ftp/` directory.
  2. Encountered a server-side validation error: `403 Error: Only .md and .pdf files are allowed!`.
  3. Analyzed the filter mechanism and determined it likely validates the string suffix but passes the raw string to a lower-level filesystem API.
  4. Modified the URL to include a double-URL-encoded null byte followed by an allowed extension: `/ftp/eastere.gg%2500.pdf`.
  5. Sent the request. The application's high-level validation logic saw the `.pdf` suffix and allowed the request. However, the underlying filesystem API terminated the string reading at the null byte (`%00`), successfully fetching and returning the `eastere.gg` file instead.

## Vulnerabilities
* **Vulnerability name:** Poison Null Byte Injection (CWE-158: Improper Neutralization of Null Byte or NUL Character).
* **Affected components:** File fetching/routing mechanism and Extension Validation logic.
* **Estimated severity level:** High.

## Risks
* **Business impact:** Bypassing file access controls allows attackers to read arbitrary files that the application has access to. If combined with a path traversal vulnerability, this technique could lead to the exfiltration of critical system files, source code, or internal configuration files containing database credentials.

## Actions
* **Suggested remediation fixes:** Explicitly strip or reject any null byte characters (`\0` or `%00` / `%2500`) from user-supplied input *before* performing any validation or passing the input to the filesystem.
* **Risk mitigation strategies:** Implement a strict, server-side allowlist mapping specific, safe identifiers (like database UUIDs) to files, rather than trusting and parsing raw filenames provided directly in the URL.
* **Best security practices:** When validating file extensions, ensure the validation logic accurately reflects how the underlying OS and file API parse the file path. Rely on robust framework-level routing rather than manual regex matching for file extensions.
