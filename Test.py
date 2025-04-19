import socket
import json
import struct

LOGIN_CODE = 1
SIGNUP_CODE = 2

def bytes_to_binary_string(b):
    return ''.join(f'{byte:08b}' for byte in b)

def binary_string_to_bytes(s):
    return int(s, 2).to_bytes(len(s) // 8, byteorder='big')

def build_message(code, message_dict):
    json_str = json.dumps(message_dict)
    data_bytes = json_str.encode()  # Turn JSON string into bytes
    size_in_bytes = len(data_bytes)

    header = struct.pack('<BI', code, size_in_bytes)  # < = little endian, B = unsigned char, I = unsigned int
    print(size_in_bytes)
    full_message = header + data_bytes
    return full_message  # Return the byte string directly!

def main():
    port = input("What port to use? ")
    if int(port) > 65535 or int(port) < 1024:
        print("Can't use this port")
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



    # Build the message (byte string)
    full_message = build_message(code, message)
    print(full_message)
    # Send message
    client.sendall(full_message)



    # Receive response
    response = client.recv(4096)

    if response:
        try:
            # Ensure we have enough bytes for header
            if len(response) < 5:
                print(f"Error: Received incomplete header ({len(response)} bytes)")
                return # Or handle differently

            # Parse the header
            code = response[0]
            size = int.from_bytes(response[1:5], byteorder='little')
            header_size = 5
            payload_end_index = header_size + size

            # Ensure we have enough bytes for the promised payload
            if len(response) < payload_end_index:
                 print(f"Error: Received incomplete payload. Expected {size} bytes, got {len(response) - header_size}")
                 # Consider receiving more data if payload might be fragmented
                 return # Or handle differently

            # Extract *only* the payload bytes using the size
            data_bytes = response[header_size:payload_end_index]

            # Decode the payload bytes to a string (assuming UTF-8)
            data_str = data_bytes.decode('utf-8')
            
            # Parse the JSON string
            response_json = json.loads(data_str)

            print(f"Received Code: {code}")
            print(f"Received Size: {size}")
            print("Parsed response JSON:", response_json)

        except json.JSONDecodeError as e:
            print(f"Error parsing JSON response: {e}")
            print(f"Raw payload bytes received: {data_bytes!r}") # Log raw bytes on error
        except IndexError:
             print("Error: Not enough data received to parse header or payload.")
        except Exception as e:
            print(f"Error parsing response: {e}")

    client.close()

if __name__ == "__main__":
    main()