import os
import requests
import math
from dotenv import load_dotenv

# (The ItineraryAgent class and its methods are refactored to just
# return data, not raise exceptions on missing API key)

class ItineraryAgent:
    def __init__(self):
        load_dotenv()
        self.api_key = os.getenv("GEOAPIFY_API_KEY")
        self.interest_map = {
            "history": "historic,heritage",
            "adventure": "natural.forest,natural.mountain,sport.climbing",
            "food": "catering.restaurant,catering.fast_food,catering.cafe",
            "nature": "natural,national_park,beach,garden",
            "art": "entertainment.culture.theatre,entertainment.museum"
        }

    def _get_city_coordinates(self, city):
        geocode_url = f"https://api.geoapify.com/v1/geocode/search?text={city}&apiKey={self.api_key}"
        response = requests.get(geocode_url)
        if response.status_code == 200 and response.json().get('features'):
            loc = response.json()['features'][0]['properties']
            return loc['lon'], loc['lat']
        return None, None

    def _fetch_pois(self, lon, lat, interests):
        categories = ",".join(self.interest_map.get(i.strip().lower(), "") for i in interests).strip(',')
        if not categories: categories = "tourism.attraction"
        
        places_url = f"https://api.geoapify.com/v2/places?categories={categories}&filter=circle:{lon},{lat},5000&bias=proximity:{lon},{lat}&limit=50&apiKey={self.api_key}"
        response = requests.get(places_url)
        if response.status_code == 200:
            return response.json().get('features', [])
        return []

    def _calculate_distance(self, p1, p2):
        return math.sqrt((p1['lon'] - p2['lon'])**2 + (p1['lat'] - p2['lat'])**2)

    def _plan_daily_itinerary(self, pois, days):
        if not pois: return {}
        days = max(1, days) # Ensure at least 1 day
        pois_per_day = min(5, len(pois) // days if days > 0 else len(pois))
        if pois_per_day == 0 and len(pois) > 0: pois_per_day = 1

        itinerary = {}
        unvisited = [
            {"name": p['properties'].get('name', 'Unknown'),
             "address": p['properties'].get('address_line2', ''),
             "lon": p['properties']['lon'], "lat": p['properties']['lat']}
            for p in pois if 'properties' in p and 'lon' in p['properties']
        ]

        for day in range(1, days + 1):
            if not unvisited: break
            daily_plan = []
            current_poi = unvisited.pop(0)
            daily_plan.append(current_poi)

            for _ in range(pois_per_day - 1):
                if not unvisited: break
                closest = min(unvisited, key=lambda p: self._calculate_distance(current_poi, p))
                daily_plan.append(closest)
                unvisited.remove(closest)
                current_poi = closest
            itinerary[f"Day {day}"] = daily_plan
        return itinerary

    def plan_trip(self, city, days, interests):
        if not self.api_key:
            print("ERROR: GEOAPIFY_API_KEY not found in .env file.")
            return {"error": "API key not configured."}
            
        lon, lat = self._get_city_coordinates(city)
        if lon is None:
            return {"error": f"Could not find coordinates for city: {city}."}
        
        pois = self._fetch_pois(lon, lat, interests)
        if not pois:
            return {"error": f"Could not find attractions for {city}."}
            
        return self._plan_daily_itinerary(pois, days)

def plan_itinerary(context):
    """
    Agent function: Takes full context, returns itinerary results.
    """
    city = context.get('destination_city')
    check_in = context.get('check_in_date')
    check_out = context.get('check_out_date')
    interests_str = context.get('interests', 'nature, food')
    
    if not all([city, check_in, check_out]):
        print("Itinerary Agent: Missing required data (city, dates).")
        return {}
    
    # Calculate duration
    try:
        from datetime import datetime
        d1 = datetime.strptime(check_in, '%Y-%m-%d')
        d2 = datetime.strptime(check_out, '%Y-%m-%d')
        days = max(1, (d2 - d1).days)
    except Exception:
        days = 1 # Default to 1 day on date error
    
    interests = [i.strip() for i in interests_str.split(',')]
    
    agent = ItineraryAgent()
    return agent.plan_trip(city, days, interests)