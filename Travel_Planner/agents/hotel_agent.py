import os
import json
# Remove serpapi import if only using mock data
# from serpapi.google_search import GoogleSearch
from dotenv import load_dotenv
from urllib.parse import quote_plus # Needed for creating search links
from fastapi import FastAPI
from pydantic import BaseModel

load_dotenv()
app = FastAPI()

class HotelRequest(BaseModel):
    city: str
    check_in: str
    check_out: str
    budget: str | None = None
    room_preference: str | None = None

@app.post("/search_hotels")
def search_hotels_endpoint(request: HotelRequest):
    print(f"Hotel Agent received request: {request.model_dump()}") # Log received data

    # --- Your actual logic using SerpApi or another provider would go here ---
    # Example: filter results based on request.budget / request.room_preference

    # --- Updated Mock Results with Dynamic Google Link ---
    mock_hotel_data = [
        {"name": "Seaside Resort Mock", "rating": 4.8, "price_per_night": 9000},
        {"name": "City Center Budget Hotel", "rating": 3.5, "price_per_night": 3500},
        {"name": "Luxury Palace Mock", "rating": 5.0, "price_per_night": 25000}
    ]

    processed_results = []
    for hotel in mock_hotel_data:
        # Generate Google Search link
        search_query = f"{hotel['name']} {request.city}"
        google_link = f"https://www.google.com/search?q={quote_plus(search_query)}"

        processed_results.append({
            "name": hotel["name"],
            "rating": hotel["rating"],
            "price_per_night": hotel["price_per_night"],
            "link": google_link # Add the generated link
        })

    # Optional: Basic filtering based on mock budget (example)
    if request.budget == 'budget':
        processed_results = [h for h in processed_results if h['price_per_night'] < 5000]
    elif request.budget == 'luxury':
         processed_results = [h for h in processed_results if h['price_per_night'] > 15000]
    elif request.budget == 'mid-range':
         processed_results = [h for h in processed_results if 5000 <= h['price_per_night'] <= 15000]
    # (Add similar logic for room_preference if needed for mock)


    if not processed_results:
        return {"status": "success", "results": []} # Return success but empty if filters remove all

    return {"status": "success", "results": processed_results[:3]} # Return top 3 matching results