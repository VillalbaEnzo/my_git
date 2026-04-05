# Injection-3-Database Schema

## Methodology
* **Techniques used:** UNION-based SQL Injection, Database Enumeration.
* **Tools used:** Web Browser, Interception Proxy (Burp Suite).
* **Steps:**
  1. Identified a potential injection point in the application's product search functionality, where the URL parameter `q` (`/#/search?q=`) directly interacts with the database.
  2. Enumerated the number of columns returned by the original search query. By analyzing the standard JSON response structure, identified 9 columns: `id`, `name`, `description`, `price`, `deluxePrice`, `image`, `createdAt`, `updatedAt`, `deletedAt`.
  3. Crafted a UNION-based SQL injection payload specifically designed for a SQLite database to extract the schema.
  4. Injected the following payload into the search parameter: `test')) UNION SELECT 1,2,3,4,5,6,7,8,sql FROM sqlite_schema--`
  5. **Payload Breakdown:**
     * `test'))` -> Closes the original application query.
     * `UNION SELECT` -> Appends the results of a new, attacker-controlled query.
     * `1,2,3,4,5,6,7,8,sql` -> Fulfills the 9-column requirement of the original query to prevent errors, placing the target data (`sql`) in the 9th column position.
     * `FROM sqlite_schema` -> Targets the built-in SQLite table that holds the database structure/metadata.
     * `--` -> Comments out the remainder of the original legitimate query to prevent syntax errors.
  6. Observation: The server successfully executed the payload, reflecting the entire database schema definition (table creations, columns, constraints) directly into the application's search results UI.

## Vulnerabilities
* **Vulnerability name:** UNION-based SQL Injection (Information Disclosure).
* **Affected components:** Product Search API endpoint.
* **Estimated severity level:** Critical.

## Risks
* **Business impact:** Complete exposure of the database architecture. By exfiltrating the schema, an attacker obtains a perfect blueprint of the backend infrastructure (table names, column names, relationships). This maps out the exact paths needed to execute further critical attacks, such as dumping user credentials, payment information, and proprietary data, inevitably leading to a catastrophic data breach.

## Actions
* **Suggested remediation fixes:** Implement Prepared Statements (Parameterized Queries) within the backend search controller. The search input must be bound as a strictly typed string parameter, preventing the database engine from interpreting user input as executable SQL commands.
* **Risk mitigation strategies:** Utilize a secure Object-Relational Mapping (ORM) library that natively handles query parameterization and escaping, rather than manually concatenating raw SQL strings.
* **Best security practices:** Enforce the Principle of Least Privilege at the database level. The database user account utilized by the web application should be restricted from querying system metadata tables (such as `sqlite_schema` or `sqlite_master`) unless absolutely required for application functionality.