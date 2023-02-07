"""
Server receiver buffer is char[256]
If correct, the server will send a message back to you saying "I got your message"
Write your socket client code here in python
Establish a socket connection -> send a short message -> get a message back -> ternimate
use python "input->" function, enter a line of a few letters, such as "abcd"
"""
import socket

def main():
	HOST = "localhost"
	PORT = 19000
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect((HOST,PORT))
		message = str(input("Enter a message: "))
		s.sendall(message.encode("utf-8"))
		data = s.recv(1024)
		s.close()
		decoded = data.decode("utf-8")
	print(f"Received {decoded!r}")   

# TODO: Create a socket and connect it to the server at the designated IP and port
    # TODO: Get user input and send it to the server using your TCP socket
    # TODO: Receive a response from the server and close the TCP connection
if __name__ == '__main__':
    main()
