# app.py

from flask import Flask, request, jsonify

app = Flask(__name__)

# -----------------------------------------------------------------------------
# ✈️ EXPANDED DUMMY FLIGHT DATABASE
# Now with 10+ flights for each route and a new route from Mumbai.
# -----------------------------------------------------------------------------

FLIGHT_DATA = [
    # --- Delhi (DEL) to Mumbai (BOM) ---
    {"airline": "IndiGo", "flight_number": "6E 204", "source": "Delhi", "destination": "Mumbai", "departure_time": "08:30", "price": 4500, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 981", "source": "Delhi", "destination": "Mumbai", "departure_time": "10:00", "price": 5200, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 887", "source": "Delhi", "destination": "Mumbai", "departure_time": "12:45", "price": 4800, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 871", "source": "Delhi", "destination": "Mumbai", "departure_time": "15:15", "price": 4350, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 555", "source": "Delhi", "destination": "Mumbai", "departure_time": "18:00", "price": 4950, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 993", "source": "Delhi", "destination": "Mumbai", "departure_time": "06:00", "price": 5100, "currency": "INR"},
    {"airline": "Akasa Air", "flight_number": "QP 1101", "source": "Delhi", "destination": "Mumbai", "departure_time": "07:20", "price": 4400, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 665", "source": "Delhi", "destination": "Mumbai", "departure_time": "19:30", "price": 5300, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 8169", "source": "Delhi", "destination": "Mumbai", "departure_time": "21:00", "price": 4650, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 2021", "source": "Delhi", "destination": "Mumbai", "departure_time": "22:15", "price": 4750, "currency": "INR"},

    # --- Delhi (DEL) to Goa (GOI) ---
    {"airline": "IndiGo", "flight_number": "6E 331", "source": "Delhi", "destination": "Goa", "departure_time": "06:00", "price": 5800, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 123", "source": "Delhi", "destination": "Goa", "departure_time": "07:30", "price": 5650, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 847", "source": "Delhi", "destination": "Goa", "departure_time": "09:45", "price": 6100, "currency": "INR"},
    {"airline": "Go First", "flight_number": "G8 373", "source": "Delhi", "destination": "Goa", "departure_time": "11:20", "price": 5500, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 865", "source": "Delhi", "destination": "Goa", "departure_time": "14:00", "price": 5950, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 789", "source": "Delhi", "destination": "Goa", "departure_time": "04:30", "price": 5400, "currency": "INR"},
    {"airline": "Akasa Air", "flight_number": "QP 1321", "source": "Delhi", "destination": "Goa", "departure_time": "13:10", "price": 5750, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 855", "source": "Delhi", "destination": "Goa", "departure_time": "16:00", "price": 6250, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 245", "source": "Delhi", "destination": "Goa", "departure_time": "18:45", "price": 5850, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 479", "source": "Delhi", "destination": "Goa", "departure_time": "20:50", "price": 6050, "currency": "INR"},

    # --- Delhi (DEL) to Chennai (MAA) ---
    {"airline": "IndiGo", "flight_number": "6E 601", "source": "Delhi", "destination": "Chennai", "departure_time": "05:30", "price": 6200, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 821", "source": "Delhi", "destination": "Chennai", "departure_time": "08:15", "price": 6800, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 539", "source": "Delhi", "destination": "Chennai", "departure_time": "13:00", "price": 6550, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 441", "source": "Delhi", "destination": "Chennai", "departure_time": "17:45", "price": 6100, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 789", "source": "Delhi", "destination": "Chennai", "departure_time": "20:30", "price": 6400, "currency": "INR"},
    {"airline": "Akasa Air", "flight_number": "QP 1501", "source": "Delhi", "destination": "Chennai", "departure_time": "10:45", "price": 6300, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 833", "source": "Delhi", "destination": "Chennai", "departure_time": "11:50", "price": 6950, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 569", "source": "Delhi", "destination": "Chennai", "departure_time": "15:20", "price": 6600, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 607", "source": "Delhi", "destination": "Chennai", "departure_time": "19:00", "price": 6500, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 3323", "source": "Delhi", "destination": "Chennai", "departure_time": "22:00", "price": 6250, "currency": "INR"},
    
    # --- Mumbai (BOM) to Bangalore (BLR) ---
    {"airline": "IndiGo", "flight_number": "6E 2341", "source": "Mumbai", "destination": "Bangalore", "departure_time": "05:45", "price": 3100, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 809", "source": "Mumbai", "destination": "Bangalore", "departure_time": "07:00", "price": 3500, "currency": "INR"},
    {"airline": "Air India", "flight_number": "AI 501", "source": "Mumbai", "destination": "Bangalore", "departure_time": "09:15", "price": 3350, "currency": "INR"},
    {"airline": "Akasa Air", "flight_number": "QP 1405", "source": "Mumbai", "destination": "Bangalore", "departure_time": "11:30", "price": 3050, "currency": "INR"},
    {"airline": "SpiceJet", "flight_number": "SG 505", "source": "Mumbai", "destination": "Bangalore", "departure_time": "14:00", "price": 3200, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 2345", "source": "Mumbai", "destination": "Bangalore", "departure_time": "16:10", "price": 3450, "currency": "INR"},
    {"airline": "Vistara", "flight_number": "UK 819", "source": "Mumbai", "destination": "Bangalore", "departure_time": "18:30", "price": 3800, "currency": "INR"},
    {"airline": "AirAsia", "flight_number": "I5 777", "source": "Mumbai", "destination": "Bangalore", "departure_time": "20:00", "price": 2999, "currency": "INR"},
    {"airline": "IndiGo", "flight_number": "6E 2349", "source": "Mumbai", "destination": "Bangalore", "departure_time": "21:45", "price": 3600, "currency": "INR"},
    {"airline": "Akasa Air", "flight_number": "QP 1409", "source": "Mumbai", "destination": "Bangalore", "departure_time": "23:00", "price": 3250, "currency": "INR"},
]

@app.route('/api/cheapest-flights', methods=['POST'])
def find_cheapest_flights():
    """
    API endpoint to find the top 3 cheapest flights for a specific route.
    """
    try:
        data = request.get_json()
        source = data['from_location']
        destination = data['to_location']
    except (TypeError, KeyError):
        return jsonify({"error": "Invalid input. Please provide from_location and to_location."}), 400

    print(f"INFO: Controller received request for route: {source} -> {destination}")

    matching_flights = [
        flight for flight in FLIGHT_DATA 
        if flight['source'].lower() == source.lower() and flight['destination'].lower() == destination.lower()
    ]

    if not matching_flights:
        # Return a 404 Not Found status code if no flights match
        return jsonify({
            "message": f"Sorry, no flights found for the route {source} to {destination}."
        }), 404

    sorted_flights = sorted(matching_flights, key=lambda x: x['price'])
    
    top_3_flights = sorted_flights[:3]
    
    print(f"INFO: Found {len(top_3_flights)} cheapest flights. Returning to user.")
    return jsonify({
        "message": f"Top {len(top_3_flights)} cheapest flights found for {source} to {destination}.",
        "flights": top_3_flights
    })

if __name__ == '__main__':
    app.run(debug=True, port=5000)