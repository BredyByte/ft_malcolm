import socket
import os

DEST_IP = os.getenv("MALCOLM_IP")
DEST_PORT = 12345

MESSAGE = "username:admin\npassword:12345"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.sendto(MESSAGE.encode(), (DEST_IP, DEST_PORT))
print(f"Sent: {MESSAGE}")

sock.close()
