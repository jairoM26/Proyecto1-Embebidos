'''
    Simple socket server using threads
'''
 
import socket
import sys
 
HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port
FLAG = True
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

if FLAG: print 'Socket created'
 
#Bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
if FLAG: print 'Socket bind complete'
 
#Start listening on socket
s.listen(10)
if FLAG: print 'Socket now listening'
 
#now keep talking with the client
while 1:
	#wait to accept a connection - blocking call
	conn, addr = s.accept()    
	if FLAG: print 'Connected with ' + addr[0] + ':' + str(addr[1])
	while True:
		data = conn.recv(4096);		
		if FLAG: print data
		if(str(data) == 'close'):
			if FLAG: print 'close: ' + addr[0] + ':' + str(addr[1])
			break
		else:
			if FLAG: print 'sending back message'
			conn.sendall('Hola') 
	break 

s.close()