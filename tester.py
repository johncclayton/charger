#!/usr/local/bin/python
import zmq, time, json

# make up a request to fetch the info for a single device
dev_key = "483-5751-1504308022"

# create a socket to handle the req/resp
print "connecting..."
ctx = zmq.Context()
socket = ctx.socket(zmq.DEALER)
socket.setsockopt(zmq.IDENTITY, b'tester')
socket.connect("tcp://pi.home:23011")

time.sleep(1)

print "connected..."
msg = { "action": "get-device", "key": dev_key }

print "sending message..."
socket.send_multipart([b'', "get-device", json.dumps(msg)])

print "waiting for reply..."
resp = socket.recv_multipart()

print resp
