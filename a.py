import socket
import threading
import string
import random

host = ''
port = 4000
con = 0

def sendPassword():
    print('send')

def getInput():
    while(True):
        data = con.recv(4).decode()
        print('client: ', data)
        con.send("OK")
    con.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
s.listen(1)
print("doorlock server now listen..")

while True:
    con, addr = s.accept()
    print('Connected by :' , addr)
    threading._start_new_thread(getInput, ())
