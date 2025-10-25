# Import the mock DB from its new location
from data.db import VEHICLE_DATABASE 

class VehicleFinderAgent:
    """
    The agent responsible for finding and filtering vehicles.
    This is refactored to return data, not print.
    """
    def __init__(self, database):
        self.vehicle_db = database
        print("Car Agent: Vehicle Finder initialized.")

    def find_vehicles(self, location, vehicle_type, num_people, hours):
        print(f"Car Agent: Searching DB for {vehicle_type} in {location}...")
        results = []
        for vehicle in self.vehicle_db:
            if (
                vehicle["location"].lower() == location.lower() and
                vehicle["type"].lower() == vehicle_type.lower() and
                vehicle["capacity"] >= num_people and
                vehicle["available"]
            ):
                total_cost = vehicle["price_per_hour"] * hours
                results.append({
                    "id": vehicle["id"],
                    "name": vehicle["name"],
                    "capacity": vehicle["capacity"],
                    "price_per_hour": vehicle['price_per_hour'],
                    "total_cost": total_cost
                })
        
        return results

def plan_car(context):
    """
    Agent function: Takes full context, returns car rental results.
    """
    location = context.get('destination_city')
    vehicle_type = context.get('vehicle_type', 'car')
    num_people = context.get('num_passengers', 1)
    hours = context.get('car_hours', 8) # Default 8 hours
    
    if not all([location, vehicle_type, num_people, hours]):
        print("Car Agent: Missing required data.")
        return []

    agent = VehicleFinderAgent(database=VEHICLE_DATABASE)
    return agent.find_vehicles(
        location=location,
        vehicle_type=vehicle_type,
        num_people=num_people,
        hours=hours
    )