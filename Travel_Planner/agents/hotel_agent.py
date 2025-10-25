import os
import json
from serpapi.google_search import GoogleSearch
from dotenv import load_dotenv
from urllib.parse import quote_plus  # <-- NEW IMPORT

def find_hotels(inputs):
    """
    Searches for hotels using the SerpApi. Returns a list of results.
    """
    load_dotenv()
    api_key = os.environ.get("SERPAPI_API_KEY")

    if not api_key:
        print("ERROR: SERPAPI_API_KEY not found in .env file.")
        return []

    print(f"Hotel Agent: Searching for hotels in {inputs['city']}...")
    params = {
        "api_key": api_key,
        "engine": "google_hotels",
        "q": f"{inputs['room_preference']} hotels in {inputs['city']}",
        "check_in_date": inputs["check_in_date"],
        "check_out_date": inputs["check_out_date"],
        "adults": inputs["num_guests"],
        "max_price": inputs["max_budget"],
        "currency": "INR", "gl": "in", "hl": "en",
    }
    try:
        search = GoogleSearch(params)
        results = search.get_dict()

        if "error" in results:
            print(f"Hotel Agent Error: {results['error']}")
            return []
        
        hotel_results = []
        if "properties" in results and results["properties"]:
            for hotel in results["properties"][:5]: # Limit to 5
                
                # --- NEW LOGIC FOR LINKS ---
                name = hotel.get("name", "No Name")
                link = hotel.get("link")  # Get the link from API

                # If no link, create a Google search link
                if not link:
                    link = f"https://www.google.com/search?q={quote_plus(name)}"
                # --- END OF NEW LOGIC ---
                
                price = "N/A"
                if "rate_per_night" in hotel and "extracted_lowest" in hotel["rate_per_night"]:
                    price = f"{hotel['rate_per_night']['extracted_lowest']} INR (per night)"
                
                hotel_results.append({
                    "name": name,
                    "price": price,
                    "rating": hotel.get("overall_rating", 0.0),
                    "link": link  # <-- ADDED LINK TO RESULT
                })
            return hotel_results
        else:
            return []
    except Exception as e:
        print(f"Hotel Agent Error: {e}")
        return []

def plan_hotel(context):
    """
    Agent function: Takes full context, returns hotel results.
    (This function is unchanged)
    """
    api_inputs = {
        "city": context.get('destination_city'),
        "check_in_date": context.get('check_in_date'),
        "check_out_date": context.get('check_out_date'),
        "num_guests": context.get('num_passengers'),
        "room_preference": context.get('room_preference', 'Single'),
        "max_budget": context.get('max_budget', '100000')
    }
    
    if not all([api_inputs['city'], api_inputs['check_in_date'], api_inputs['check_out_date']]):
        print("Hotel Agent: Missing required data (city, dates).")
        return []

    return find_hotels(api_inputs)
