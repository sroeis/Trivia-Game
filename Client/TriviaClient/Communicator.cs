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
            m_socket.Connect("127.0.0.1", 6969);
            stream = m_socket.GetStream();
        }

        public void Send(Buffer data)
        {
            // Convert the JSON string to bytes and send
            stream.Write(data.ToArray(), 0, data.Count);
        }


        //returns only the json!
        public string Receive()
        {
            byte[] size = new byte[4];
            stream.Read(size, 0, 1);
            int bytesRead = stream.Read(size, 0, 4);
            byte[] buffer = new byte[BitConverter.ToInt32(size)];

            string jsonString = Encoding.ASCII.GetString(buffer, 0, BitConverter.ToInt32(size));
            return jsonString;
        }
    }
}
