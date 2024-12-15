import socket
import json
import threading

def receive_messages(client_socket):
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if message:
                print(f"Message reçu: {message}")
            else:
                break
        except:
            break

def send_message(client_socket, username):
    while True:
        msg = input(f"{username} > ")
        if msg:
            message = json.dumps({"type": "message", "username": username, "content": msg})
            client_socket.send(message.encode('utf-8'))

def main():
    server_address = ('localhost', 12345)
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(server_address)
    
    username = input("Entrez votre nom d'utilisateur: ")
    login_message = json.dumps({"type": "login", "username": username})
    client_socket.send(login_message.encode('utf-8'))
    
    # Thread pour recevoir les messages
    receive_thread = threading.Thread(target=receive_messages, args=(client_socket,))
    receive_thread.start()
    
    # Thread pour envoyer des messages
    send_thread = threading.Thread(target=send_message, args=(client_socket, username))
    send_thread.start()

if __name__ == "__main__":
    main()
