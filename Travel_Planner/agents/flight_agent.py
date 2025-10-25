import random
import requests

# --- CONFIGURATION (from test.py) ---
AVIATIONSTACK_API_KEY = "89877acc5303fe5a7f91143368acd178" # <-- PASTE YOUR KEY HERE
AVIATIONSTACK_API_URL = "http://api.aviationstack.com/v1/flights"

CITY_TO_IATA = {
    "delhi": "DEL", "mumbai": "BOM", "goa": "GOI",
    "chennai": "MAA", "bangalore": "BLR",
}

def fetch_flights_from_api(source_city, destination_city):
    """Fetches flight data from API."""
    if AVIATIONSTACK_API_KEY == "YOUR_AVIATIONSTACK_API_KEY":
        print("ERROR: AVIATIONSTACK_API_KEY not set in agents/flight_agent.py")
        return None, "API key has not been configured."

    source_iata = CITY_TO_IATA.get(source_city.lower())
    dest_iata = CITY_TO_IATA.get(destination_city.lower())

    if not source_iata or not dest_iata:
        return None, f"Source city '{source_city}' or destination '{destination_city}' not supported."

    params = {
        'access_key': AVIATIONSTACK_API_KEY, 'dep_iata': source_iata,
        'arr_iata': dest_iata, 'flight_status': 'scheduled', 'limit': 10
    }
    try:
        api_response = requests.get(AVIATIONSTACK_API_URL, params=params)
        api_response.raise_for_status()
        raw_data = api_response.json()

        if 'error' in raw_data:
            return None, raw_data['error'].get('info', 'API error')

        processed_flights = []
        for flight_data in raw_data.get('data', []):
            processed_flights.append({
                "airline": flight_data['airline']['name'],
                "flight_number": flight_data['flight']['iata'],
                "source": flight_data['departure']['airport'],
                "destination": flight_data['arrival']['airport'],
                "departure_time": flight_data['departure']['scheduled'],
                "price": random.randint(3500, 9500), # Mock price
                "currency": "INR"
            })
        return processed_flights, None
    except requests.exceptions.RequestException as e:
        print(f"ERROR: API request failed: {e}")
        return None, "Failed to connect to flight provider."

def plan_flights(context):
    """
    Agent function: Takes full context, returns flight results.
    """
    source_city = context.get('source_city')
    destination_city = context.get('destination_city')
    
    if not source_city or not destination_city:
        return [] # Not enough info

    flights, error = fetch_flights_from_api(source_city, destination_city)

    if error:
        print(f"Flight Agent Error: {error}")
        return [] # Return empty on error
    if not flights:
        return []

    sorted_flights = sorted(flights, key=lambda x: x['price'])
    return sorted_flights[:3] # Return top 3