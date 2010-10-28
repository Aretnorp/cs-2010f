# Echo server program
import socket
import sys
import os

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = int(sys.argv[1])   # Arbitrary non-privileged port
DIR  = sys.argv[2]        # The directory

# Create the socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Create the directory
if not os.path.exists(DIR):
    os.mkdir(DIR)

# Bind and listen
s.bind((HOST, PORT))
s.listen(1)

# Accept a connection
conn, addr = s.accept()

# Receive the file name
name = conn.recv(128)

# Open the test file
f = open(DIR + "/" + name, "w+")
print 'Connected by', addr

# Receive the contents
while 1:
    data = conn.recv(1024)
    if not data: break
    f.write(data)

# Close the connection
conn.close()

