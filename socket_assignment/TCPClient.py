import socket
import sys
import argparse
import json

serverName = '127.0.0.1'
serverPort = 5000
clientSocket = None


def Send_TCP_Request(msgObject):
    for res in socket.getaddrinfo(serverName, serverPort, socket.AF_UNSPEC, socket.SOCK_STREAM):
        # unpacking tuple
        (family, sockType, protocol, canonName, sockAddress) = res
        print res
        try:
          clientSocket = socket.socket(family, sockType, protocol)
        except socket.error as msg:
          clientSocket = None
          continue

        try:
          clientSocket.connect(sockAddress)
        except socket.error as msg:
          clientSocket.close()
          clientSocket = None
          continue
        break

    if clientSocket is None:
        print("Failed to open socket {}".format(serverPort))
        sys.exit(1)

    try:
        clientSocket.sendall(msgObject)
        clientSocket.close()
    except socket.error as msg:
        raise

def Get_User_Input():
    parser = argparse.ArgumentParser(prog="TCPClient.py", description="TCP client socket communication")
    parser.add_argument("name", metavar="name", type=str, nargs='+',default="Dinkar",
                         help="Name of user")
    parser.add_argument("id", metavar="id", type=int, default=123456,
                         help="ID > 6 of a user")
    # parser.add_argument("num", metavar="num", type=int, default=42,
    #                      help="Street number of user")
    # parser.add_argument("street name", metavar="street name", type=str, nargs='*', default="Main St.",
    #                      help="Street name of user")
    return parser.parse_args()




if __name__ == "__main__":
    name = None
    id = None

    # get user input from terminal
    userInputObj = Get_User_Input()
    # serializing the input user object
    encodeJsonData = json.dumps(vars(userInputObj), separators=(',',':'))

    # check for alphabets in name only
    # if not name.isalpha():        
    #     raise  TypeError("Name is not a valid string!")

    try:
        Send_TCP_Request(encodeJsonData)
    except socket.error as msg:
        raise
    
    sys.exit(0)



