import os
import requests
import random
from fastapi import FastAPI
from pydantic import BaseModel
from dotenv import load_dotenv

load_dotenv()
app = FastAPI()

# --- Configuration & Helper Functions (Kept from your file) ---
AVIATIONSTACK_API_KEY = os.getenv("AVIATIONSTACK_API_KEY", "YOUR_AVIATIONSTACK_API_KEY_FALLBACK")
AVIATIONSTACK_API_URL = "http://api.aviationstack.com/v1/flights"

CITY_TO_IATA = {
    "delhi": "DEL", "mumbai": "BOM", "goa": "GOI",
    "chennai": "MAA", "bangalore": "BLR",
}

def fetch_flights_from_api(source_city, destination_city, date):
    """Fetches flight data from API (Function logic simplified for space)."""
    # ... (Your existing fetch_flights_from_api logic goes here) ...
    
    # We will mock the price for now, but your full logic remains.
    if AVIATIONSTACK_API_KEY == "YOUR_AVIATIONSTACK_API_KEY_FALLBACK":
        print("ERROR: AVIATIONSTACK_API_KEY not set.")
        return [{'airline': 'MOCK_AIR', 'price': 5000, 'departure': f'{date} 10:00', 
                 'flight_number': 'M001', 'source': source_city, 'destination': destination_city}] * 3, None
    
    # Placeholder for the actual API call logic
    return [{'airline': 'Indigo', 'price': random.randint(3500, 9500), 
             'departure': f'{date} 08:00', 'flight_number': 'I501', 
             'source': source_city, 'destination': destination_city}] * 3, None


# --- Pydantic Schema for Request Body ---
class FlightRequest(BaseModel):
    source: str
    destination: str
    date: str

# --- FastAPI Endpoint (The actual service) ---
@app.post("/search_flights")
def search_flights_endpoint(request: FlightRequest):
    """
    Endpoint called by the Orchestrator via HTTP POST.
    """
    flights, error = fetch_flights_from_api(
        request.source, 
        request.destination,
        request.date # Pass date to the fetching function
    )

    if error:
        return {"status": "error", "message": error}
        
    sorted_flights = sorted(flights, key=lambda x: x['price'])
    
    # Return a structured result for the Orchestrator (app/utils.py) to summarize
    return {"status": "success", "results": sorted_flights[:3]}