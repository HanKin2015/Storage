from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route('/')
def hello_world():  # put application's code here
    return render_template("index.html")

@socketio.on('connect', namespace='/test')
def test_connect():
    emit('my response', {'data': 'Connected'})

@socketio.on('disconnect', namespace='/test')
def test_disconnect():
    print('Client disconnected')

@socketio.on('my_event', namespace='/test')
def handle_my_custom_namespace_event(json):
    print('received json: ' + str(json))
    
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=8029, debug=False)