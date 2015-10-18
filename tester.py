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

print "sending message..."
socket.send_multipart([b'', "get-device", dev_key])

print "waiting for reply..."
resp = json.loads(socket.recv_multipart()[1:][0])
ch1 = resp['device']['channels'][0]

cells = ch1['cells']
print "cell 1:", float(cells[0]["voltage"])
print "cell 2:", float(cells[1]["voltage"])
print "cell 3:", float(cells[2]["voltage"])
print "cell 4:", float(cells[3]["voltage"])
print "cell 5:", float(cells[4]["voltage"])
print "cell 6:", float(cells[5]["voltage"])
