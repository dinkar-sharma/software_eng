import socket
import sys
import json

serverName = '127.0.0.1'
serverPort = 5000
serverSocket = None
repoFilePath = "/home/terminator0o0/dev/software_eng/socket_assignment/repo_data.txt"
nameList = []
idList = []

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
print("Connected by [{}]".format(address))

while(1):
	try:
		rcvData = connectionSocket.recv(1024)
	except socket.error as msg:
		break
	
	if not rcvData:
		break

	decodeRcvData = json.loads(rcvData)

	print("Server recieved data: [{}]".format(rcvData))

	# write to flat text file
	with open(repoFilePath, 'a') as repoFile:
		# iterating over user data and writing to file
		for key, value in decodeRcvData.iteritems():
			if key is "name":
				nameList.append(value)
			if key is "id":
				idList.append(value)
		repoFile.write(str(nameList))
		repoFile.write(str(idList))
	try:
		connectionSocket.send(rcvData)
	except socket.error as msg:
		break
	
serverSocket.close()