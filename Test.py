import socket
import json
import struct


LOGIN_CODE = 1
SIGNUP_CODE = 2


def string_to_binary(s):
    return ''.join(format(ord(c), '08b') for c in s)


def build_message(code, message_dict):
    json_str = json.dumps(message_dict)
    
    # str to binary
    binary_str = string_to_binary(json_str)
    

    # calculate size
    size_in_bytes = len(binary_str) // 8


    header = struct.pack('<BI', code, size_in_bytes)  # < = little endian, B = unsigned char, I = unsigned int
    
    full_message = header + binary_str.encode()

    return full_message


def main():
    port = input("what port to use?")
    if int(port) > 65535 or int(port) < 1024:
        print("cant use this port")
        return

    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('127.0.0.1', int(port)))
    except socket.error:
        print("An error occurred while connecting!")
        return


    msg_type = input("Choose message type (login/signup): ").strip().lower()

    if msg_type == 'login':
        username = input("Username: ")
        password = input("Password: ")
        message = {
            "username": username,
            "password": password
        }
        code = LOGIN_CODE
    elif msg_type == 'signup':
        username = input("Username: ")
        password = input("Password: ")
        email = input("Email: ")
        message = {
            "username": username,
            "password": password,
            "email": email
        }
        code = SIGNUP_CODE
    else:
        print("Invalid message type!")
        return

    # Build and send message
    final_message = build_message(code, message)
    client.sendall(final_message)

    response = client.recv(4096)

    if response:
        try:
            # Parse the response
            code = response[0]
            size = int.from_bytes(response[1:5], byteorder='little')
            binary_data = response[5:]

            # Binary to string
            binary_str = binary_data.decode()
            chars = []
            for i in range(0, len(binary_str), 8):
                byte = binary_str[i:i+8]
                chars.append(chr(int(byte, 2)))
            json_str = ''.join(chars)

            # Parse JSON
            response_json = json.loads(json_str)
            print("Parsed response:", response_json)
        except Exception as e:
            print("Error parsing response:", e)

    client.close()

if __name__ == "__main__":
    main()

    