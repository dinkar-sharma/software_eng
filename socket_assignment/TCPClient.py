import socket
import sys
import argparse

serverName = '127.0.0.1'
serverPort = 64000
clientSocket = None


def Get_User_Input():
    parser = argparse.ArgumentParser(prog="TCPClient.py", description="TCP client socket communication")
    parser.add_argument("name", metavar="name", type=str, nargs='2', default="Dinkar",
                         help="Name of a user")
    parser.add_argument("id", metavar="id", type=int, default=123456,
                         help="ID > 6 of a user")
    # parser.add_argument("street num", metavar="num", type=int, default="",
    #                      help="Street number of user")
    # parser.add_argument("street name", metavar="street name", type=str, nargs='*',
    #                      help="Street name of user")
    # parser.add_argument("Name", metavar="N", type=str, nargs='+',
    #                      help="name of a person")
    return parser.parse_args()






if __name__ == "__main__":
    i = Get_User_Input()
    print i
    sys.exit(0)


# for res in socket.getaddrinfo(serverName, serverPort, socket.AF_UNSPEC, socket.SOCK_STREAM):
#   # unpacking tuple
#   (family, sockType, protocol, canonName, sockAddress) = res
#   print res
#   try:
#       clientSocket = socket.socket(family, sockType, protocol)
#   except socket.error as msg:
#       clientSocket = None
#       continue

#   try:
#       clientSocket.connect(sockAddress)
#   except socket.error as msg:
#       clientSocket.close()
#       clientSocket = None
#       continue
#   break

# if clientSocket is None:
#   print("Failed to open socket {}".format(serverPort))
#   sys.exit(1)

# clientSocket.sendall("Hello World")
# data = clientSocket.recv(1024)
# clientSocket.close()

# print("Recieved {}".format(repr(data)))
