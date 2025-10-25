import sys
import os
from flask import Flask, render_template, request, jsonify

# --- Add project root to path ---
# This line ensures we can import from 'app' and 'agents'
project_root = os.path.abspath(os.path.dirname(__file__))
sys.path.insert(0, project_root)
# --- End of path fix ---

# Import the new orchestrator functions
from app.orchestrator import parse_initial_query, run_all_agents

app = Flask(__name__)

@app.route('/')
def index():
    """Serves the main index.html webpage."""
    return render_template('index.html')

@app.route('/api/parse_query', methods=['POST'])
def api_parse_query():
    """
    API Endpoint 1:
    Takes the user's free-text query and returns the
    pre-filled data for the web form.
    """
    try:
        data = request.json
        query = data.get('query', '').lower()
        
        # Call the parsing logic
        context = parse_initial_query(query)
        
        return jsonify({"success": True, "context": context})
    except Exception as e:
        print(f"Error in /api/parse_query: {e}")
        return jsonify({"success": False, "error": str(e)}), 500

@app.route('/api/get_plan', methods=['POST'])
def api_get_plan():
    """
    API Endpoint 2:
    Takes the complete, confirmed form data from the user
    and runs all agents to generate the final plan.
    """
    try:
        # This is the full context from the web form
        context = request.json
        
        # Call the main agent runner
        final_plan = run_all_agents(context)
        
        return jsonify({"success": True, "plan": final_plan})
    except Exception as e:
        print(f"Error in /api/get_plan: {e}")
        import traceback
        traceback.print_exc()
        return jsonify({"success": False, "error": str(e)}), 500

if __name__ == '__main__':
    print("Starting Flask server...")
    print("Visit http://127.0.0.1:5000 in your browser.")
    app.run(debug=True, port=5000)