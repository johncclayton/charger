from python.app import AppInterface
from python.rest_interface import Status_iCharger
from flask_restful import Api

#
# Goals:
# - output the current status of the charger via a REST GET URL
# - make it easy to run on the Pi!
#
try:
    flask_app = AppInterface()
    api = Api(flask_app.app)
    api.add_resource(Status_iCharger, "/status")

except Exception as r:
    print("error starting app:", r)
    raise r

if __name__ == "__main__":
    flask_app.app.run(debug=True, host='0.0.0.0')