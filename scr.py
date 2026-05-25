import requests

# 1. Configuration Variables
jedai_url = "http://atlfsr-dl450-01:5150"  # Your specific Base URL
username = "<your_ldap_username>"          # Enter your LDAP username
password = "<your_ldap_password>"          # Enter your LDAP password
provider = "LDAP"
api_key_name = "voltus_agentic_key"        # Identifier for your key
expires_delta = 0                          # 0 means the key will never expire [cite: 56]

# 2. Setup Request
url = f"{jedai_url}/api/v1/security/api_key"
payload = {
    "api_key_name": api_key_name,
    "expires_delta": expires_delta,
    "password": password,
    "provider": provider,
    "username": username
}

# 3. Execute and Extract Key
resp = requests.post(
    url,
    headers={"Content-Type": "application/json"},
    json=payload
)

if resp.status_code == 200:
    api_key = resp.json().get("access_token")
    print(f"\nSUCCESS! Here is your JEDAI_API_KEY:\n{api_key}\n")
    print("WARNING: Copy this now. The secret value is only displayed once. [cite: 50]")
else:
    print(f"Failed to generate key. Status Code: {resp.status_code}")
    print(resp.text)
