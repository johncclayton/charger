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

num_messages = 0
print "connected..."

while True:
	try:
		socket.send_multipart([b'', "get-device", dev_key])
		resp = json.loads(socket.recv_multipart()[1:][0])
		ch1 = resp['device']['channels'][0]
	
		cells = ch1['cells']
 
		print "req: ", num_messages
		print "cell 1:", float(cells[0]["voltage"])
		print "cell 2:", float(cells[1]["voltage"])
		print "cell 3:", float(cells[2]["voltage"])
		print "cell 4:", float(cells[3]["voltage"])
		print "cell 5:", float(cells[4]["voltage"])
		print "cell 6:", float(cells[5]["voltage"])
		print "cell 7:", float(cells[6]["voltage"])
		print "cell 8:", float(cells[7]["voltage"])
		print "cell 9:", float(cells[8]["voltage"])
		print "cell 10:", float(cells[9]["voltage"])

		num_messages += 1
		print ""

	except KeyboardInterrupt, e:
		break

print "total:", num_messages
