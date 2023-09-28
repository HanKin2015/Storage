from flask import Flask, request,render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)


@app.route('/')
def hello_world():  # put application's code here
    return render_template("index.html")


@socketio.on('connect')
def connect():
    print('ip:' + request.remote_addr)
    print('sid:' + request.sid)

@socketio.on('zhiliao')
def zhiliao_event(data):
    print(data)
    return {"result":"success"}

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=8080, debug=False)

