import os
import requests
from fastapi import FastAPI
from pydantic import BaseModel
from dotenv import load_dotenv
from datetime import datetime, timedelta
import random # For variety

load_dotenv()
app = FastAPI()

# --- Enhanced Mock Itinerary Generation Logic ---
def get_trip_duration(start_date_str, end_date_str):
    """Calculates the number of days between start (inclusive) and end (exclusive)."""
    try:
        start_date = datetime.strptime(start_date_str, '%Y-%m-%d')
        end_date = datetime.strptime(end_date_str, '%Y-%m-%d')
        # Duration is number of nights + 1 day
        duration = (end_date - start_date).days + 1 # Add 1 for inclusive days
        return max(1, duration)
    except ValueError:
        print(f"Error parsing dates: {start_date_str}, {end_date_str}")
        return 1 # Default to 1 day on error

def plan_itinerary(context: dict) -> dict:
    """
    Generates a more detailed mock itinerary based on interests.
    """
    city = context.get('destination_city', 'Unknown City')
    start_date_str = context.get('check_in_date')
    end_date_str = context.get('check_out_date')
    interests_str = context.get('interests', 'general') # Default interest

    if not start_date_str or not end_date_str:
        return {"error": "Missing check-in or check-out date for itinerary planning."}

    interests = [i.strip().lower() for i in interests_str.split(',')]
    duration_days = get_trip_duration(start_date_str, end_date_str)
    itinerary = {}

    # More detailed Mock POIs with type, duration, cost
    mock_pois_db = {
        'Goa': {
            'beach': [
                {"name": "Calangute Beach", "type": "Beach Relaxation", "duration": "3-4 hours", "cost": "Free"},
                {"name": "Baga Beach Watersports", "type": "Activity", "duration": "2-3 hours", "cost": "₹1500-₹3000"},
                {"name": "Palolem Beach", "type": "Scenic Beach", "duration": "Half day", "cost": "Free"},
            ],
            'food': [
                {"name": "Martin's Corner", "type": "Restaurant", "duration": "1-2 hours", "cost": "₹1000-₹2000 pp"},
                {"name": "Spice Plantation Tour & Lunch", "type": "Tour/Food", "duration": "3-4 hours", "cost": "₹800 pp"},
                {"name": "Anjuna Flea Market Food Stalls", "type": "Street Food", "duration": "1-2 hours", "cost": "₹300-₹700 pp"},
            ],
            'history': [
                {"name": "Fort Aguada", "type": "Historical Site", "duration": "1-2 hours", "cost": "₹50 entry"},
                {"name": "Basilica of Bom Jesus", "type": "Religious Site", "duration": "1 hour", "cost": "Free (Donations accepted)"},
                {"name": "Old Goa Walking Tour", "type": "Tour", "duration": "2-3 hours", "cost": "₹500-₹1000 pp"},
            ],
            'nature': [
                 {"name": "Dudhsagar Falls Trip", "type": "Nature/Excursion", "duration": "Full day", "cost": "₹2000-₹4000 (incl. travel)"},
                 {"name": "Butterfly Conservatory", "type": "Nature", "duration": "1-2 hours", "cost": "₹150 entry"},
            ]
        },
        'Chennai': {
             'history': [
                 {"name": "Fort St. George", "type": "Historical Site/Museum", "duration": "2-3 hours", "cost": "₹25 entry"},
                 {"name": "Kapaleeshwarar Temple", "type": "Religious Site", "duration": "1-1.5 hours", "cost": "Free (Donations accepted)"},
                 {"name": "Government Museum Chennai", "type": "Museum", "duration": "2-3 hours", "cost": "₹15 entry"},
             ],
            'food': [
                {"name": "Saravana Bhavan", "type": "Restaurant (South Indian)", "duration": "1 hour", "cost": "₹300-₹600 pp"},
                {"name": "Murugan Idli Shop", "type": "Restaurant (Idli/Dosa)", "duration": "1 hour", "cost": "₹200-₹400 pp"},
                {"name": "Sowcarpet Street Food Walk", "type": "Street Food", "duration": "2 hours", "cost": "₹400-₹800 pp"},
            ],
             'beach': [
                  {"name": "Marina Beach", "type": "Beach Walk/Relaxation", "duration": "1-2 hours", "cost": "Free"},
                  {"name": "Elliot's Beach (Besant Nagar)", "type": "Beach/Cafes", "duration": "2-3 hours", "cost": "Free (Food extra)"},
             ],
             'nature': [ # Limited nature in Chennai city itself
                  {"name": "Guindy National Park", "type": "Nature/Park", "duration": "2-3 hours", "cost": "₹20 entry"},
                  {"name": "Theosophical Society Gardens", "type": "Garden/Quiet Space", "duration": "1-2 hours", "cost": "Free"},
             ]
        }
        # Add more cities and interests as needed
    }

    # Select relevant POIs based on interests
    relevant_pois = []
    city_db = mock_pois_db.get(city, {})
    if not city_db: # Handle unknown city
         return {"error": f"Sorry, I don't have detailed itinerary information for {city}."}

    for interest in interests:
        relevant_pois.extend(city_db.get(interest, []))

    if 'general' in interests or not relevant_pois: # Fallback if no specific interests match
        for poi_list in city_db.values():
            relevant_pois.extend(poi_list)

    if not relevant_pois: # If still no POIs after fallback
        return {"error": f"Could not find suggested activities for {city} based on interests: {interests_str}."}

    # Distribute POIs across days (simple distribution, max 2-3 per day)
    pois_per_day = 2 # Adjust as needed
    random.shuffle(relevant_pois) # Shuffle for variety each time

    start_date = datetime.strptime(start_date_str, '%Y-%m-%d')
    for day_num in range(duration_days):
        current_date = start_date + timedelta(days=day_num)
        day_label = f"Day {day_num + 1} ({current_date.strftime('%B %d, %Y')})" # Add date to label
        itinerary[day_label] = []

        # Select POIs for the day
        start_index = day_num * pois_per_day
        day_pois = relevant_pois[start_index : start_index + pois_per_day]

        if not day_pois:
            itinerary[day_label].append({
                "time": "Full Day",
                "name": f"Free time to explore {city} on your own.",
                "type": "Leisure",
                "duration": "N/A", "cost": "Variable"
            })
        else:
            # Assign approximate times
            times = ["Morning", "Afternoon", "Evening"]
            for i, poi in enumerate(day_pois):
                 # Add the POI details including duration and cost
                 itinerary[day_label].append({
                     "time": times[i % len(times)], # Cycle through times
                     "name": poi["name"],
                     "type": poi["type"],
                     "duration": poi.get("duration", "N/A"), # Use .get for safety
                     "cost": poi.get("cost", "N/A")
                 })

    return itinerary

# --- Pydantic Schema ---
class ItineraryRequest(BaseModel):
    destination_city: str
    check_in_date: str
    check_out_date: str
    interests: str = 'general' # Default to general if not specified

# --- FastAPI Endpoint ---
@app.post("/plan_itinerary")
def plan_itinerary_endpoint(request: ItineraryRequest):
    print(f"Itinerary Agent received request: {request.model_dump()}")
    # Convert Pydantic model to dict for the plan_itinerary function
    context = request.model_dump()
    results = plan_itinerary(context)

    if isinstance(results, dict) and results.get('error'):
        # Return 400 Bad Request if input was bad, 500 otherwise?
        # For simplicity, returning success=false might be better for the LLM.
         # Let's return error status for clarity
         return {"status": "error", "message": results['error']}


    return {"status": "success", "results": results}