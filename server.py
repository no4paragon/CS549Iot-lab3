from flask import Flask
from flask import request

app = Flask(__name__)

@app.route("/")
def hello():
        print("\ntemperature: " + str(request.args.get("t")) + "C")
        print("humidity: " + str(request.args.get("h")) + "%RH\n", end = "\n")
        return "See cloud terminal"
