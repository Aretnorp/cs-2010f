# Echo client program
import socket
import sys

HOST = sys.argv[1]      # The remote host
PORT = int(sys.argv[2]) # The same port as used by the server
FILE = sys.argv[3]      # The file

# Create the socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

# Open the file
f = open(FILE, "r")

# Send the file name
s.send(FILE)

# Send the file
s.send(f.read())

# Close the directories
f.close()
s.close()
print 'Finished'


