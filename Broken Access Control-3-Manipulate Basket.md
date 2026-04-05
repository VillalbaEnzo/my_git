# Broken Access Control-3-Manipulate Basket

## Methodology
* **Techniques used:** Insecure Direct Object Reference (IDOR), JSON Parameter Pollution.
* **Tools used:** Burp Suite (Proxy and Repeater modules).
* **Steps:**
  1. Interacted with the application by adding a product to the personal shopping basket.
  2. Intercepted the resulting HTTP request using Burp Suite and identified the relevant API endpoint (e.g., `/api/BasketItems/1`).
  3. Forwarded the state-changing request (in this case, a `PUT` or `POST` request) to the **Repeater** module.
  4. Analyzed the JSON payload and manipulated it by duplicating the target parameter. Specifically, injected `"BasketId": 2` immediately after the original `"BasketId": 1` within the JSON body.
  5. Sent the manipulated request. The backend JSON parser processed the payload, likely overwriting the initial value with the final one (ID 2), successfully placing the item into another user's shopping basket.

## Vulnerabilities
* **Vulnerability name:** Broken Access Control / Insecure Direct Object Reference (IDOR).
* **Affected components:** Shopping Basket API (`/api/BasketItems`).
* **Estimated severity level:** Medium.

## Risks
* **Business impact:** Unauthorized manipulation of user sessions. An attacker can silently add expensive or unwanted items to other customers' shopping carts. If unnoticed by the victim during checkout, this leads to erroneous charges, customer frustration, an influx of refund requests, and severe damage to the platform's reliability and reputation.

## Actions
* **Suggested remediation fixes:** The backend API must completely ignore any `BasketId` parameter supplied by the client in the request body or URL. Instead, the server must securely retrieve the user's assigned basket ID directly from their authenticated session token.
* **Risk mitigation strategies:** Implement strict server-side ownership validation. Before modifying any basket item, the application must verify that the target basket definitively belongs to the user making the request.
* **Best security practices:** Avoid using predictable, incremental integers (like 1, 2, 3) for sensitive object references. Utilize secure, randomly generated UUIDs for entities like user profiles, shopping baskets, and orders to significantly reduce the feasibility of enumeration attacks.
