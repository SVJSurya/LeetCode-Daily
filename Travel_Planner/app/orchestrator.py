import re

# Import all agent functions
from agents.flight_agent import plan_flights
from agents.hotel_agent import plan_hotel
from agents.itinerary_agent import plan_itinerary
from agents.car_agent import plan_car

# --- Data extraction logic ---
KNOWN_CITIES = [
    "delhi", "mumbai", "goa", "chennai", "bangalore"
]
KNOWN_ROOMS = ["suite", "single", "double"]

def parse_initial_query(query):
    """
    Parses the user's free-text query to pre-fill the context.
    This is called by the /api/parse_query endpoint.
    """
    context = {}
    print(f"Parsing query: {query}")
    
    # 1. Find dates (YYYY-MM-DD)
    dates = re.findall(r'\d{4}-\d{2}-\d{2}', query)
    if dates:
        if len(dates) >= 2:
            context['check_in_date'] = dates[0]
            context['check_out_date'] = dates[1]
        else:
            context['check_in_date'] = dates[0]

    # 2. Find cities
    for city in KNOWN_CITIES:
        if f"to {city}" in query or f"in {city}" in query:
            context['destination_city'] = city
            break
            
    for city in KNOWN_CITIES:
        if f"from {city}" in query:
            context['source_city'] = city
            break

    # 3. Find room types
    for room in KNOWN_ROOMS:
        if room in query:
            context['room_preference'] = room
            break
    
    print(f"Parsed context: {context}")
    return context


def run_all_agents(context):
    """
    Runs all agents based on the final, confirmed context from the web form.
    This is called by the /api/get_plan endpoint.
    """
    final_plan = {}
    
    print("\n--- Running Agents based on user confirmation ---")

    # 1. Flight Agent
    if context.get('book_flights'):
        print("Running Flight Agent...")
        final_plan['flights'] = plan_flights(context)

    # 2. Hotel Agent
    if context.get('book_hotel'):
        print("Running Hotel Agent...")
        final_plan['hotel'] = plan_hotel(context)

    # 3. Itinerary Agent
    if context.get('book_itinerary'):
        print("Running Itinerary Agent...")
        final_plan['itinerary'] = plan_itinerary(context)

    # 4. Car Agent
    if context.get('book_car'):
        print("Running Car Agent...")
        final_plan['car'] = plan_car(context)
        
    print("--- All agents finished ---")
    return final_plan