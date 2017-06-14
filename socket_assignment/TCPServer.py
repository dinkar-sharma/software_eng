import socket
import sys


serverName = '127.0.0.1'
serverPort = 64000
serverSocket = None

for res in socket.getaddrinfo(serverName, serverPort, socket.AF_INET, 
							 socket.SOCK_STREAM):
	(family, sockType, protocol, canonName, sockAddress) = res

	try:
		serverSocket = socket.socket(family, sockType, protocol)
	except socket.error as msg:
		serverSocket = None
		continue

	try:
		serverSocket.bind(sockAddress)
		serverSocket.listen(1)
	except socket.error as msg:
		serverSocket.close()
		serverSocket = None
		continue
	break

if serverSocket is None:
	print("Failed to open socket {}".format(serverPort))
	sys.exit(1)

print "The server is ready to receive"
(connectionSocket, address) = serverSocket.accept()
print("Connected by {}".format(address))

while(1):
	data = connectionSocket.recv(1024)
	if not data:
		break
	connectionSocket.send(data)
	
serverSocket.close()