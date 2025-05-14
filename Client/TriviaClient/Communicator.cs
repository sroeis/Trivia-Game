using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Text.Json;
using TriviaClient.Requests;
using System.Security.RightsManagement;

using Buffer = System.Collections.Generic.List<byte>;

namespace TriviaClient
{
    public class Communicator
    {
        private TcpClient m_socket;
        private NetworkStream stream;

        public Communicator()
        {
            m_socket = new TcpClient();
            m_socket.Connect("127.0.0.1", 4242);
            stream = m_socket.GetStream();
        }

        public void Send<T>(T request)
        {
            try
            {
                Buffer data = new Buffer();
                if (request is LoginRequest)
                {
                    data.Add((byte)TriviaClient.Constants.LOGIN_CODE);
                }
                
                // Convert the request object to JSON string
                string jsonString = JsonSerializer.Serialize(request);


                // add size to the msg
                int size = jsonString.Length;
                byte[] sizeBytes = BitConverter.GetBytes(size); // 4 bytes

                foreach (byte b in sizeBytes)
                    data.Add((byte)b);

                data.AddRange(Encoding.ASCII.GetBytes(jsonString));

                // Convert the JSON string to bytes and send
                stream.Write(data.ToArray(), 0, data.Count);
            }
            catch (Exception ex)
            {
                throw new Exception($"Failed to send {typeof(T).Name}: " + ex.Message);
            }
        }

        public T Receive<T>()
        {
            try
            {
                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string jsonString = Encoding.ASCII.GetString(buffer, 0, bytesRead);
                
                // Convert the received JSON string back to the specified type
                return JsonSerializer.Deserialize<T>(jsonString);
            }
            catch (Exception ex)
            {
                throw new Exception($"Failed to receive {typeof(T).Name}: " + ex.Message);
            }
        }
    }
}
