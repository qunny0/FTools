using System;

using System.Net;
using System.Net.Sockets;

using System.Threading;
using System.IO;

namespace PChatClient
{
    class EchoClient
    {
        TcpClient _tcpClient;

        IPAddress _ipAddress;

        int _port;

        Thread _thread;

        NetworkStream _networkStream;

        public EchoClient(string ip, int port)
        {
            _ipAddress = IPAddress.Parse(ip);
            _port = port;
        }

        public bool initialize()
        {
            _tcpClient = new TcpClient();

            try {
                _tcpClient.Connect(_ipAddress, _port);

                _networkStream = _tcpClient.GetStream();

                responseRunning();

                _thread = new Thread(receiveRunning);
                _thread.Start();
            }
            catch {
                Console.WriteLine("connect failed. ");
                return false;
            }

            Console.WriteLine("connect success. ");
            return true;
        }

        protected void responseRunning()
        {
            while (true)
            {
                var instr = Console.ReadLine();
                byte[] str = System.Text.Encoding.Default.GetBytes(instr);
                Console.WriteLine("input: {0} : {1} ", instr, str.Length);

                _networkStream.Write(str, 0, str.Length);

                if (instr == "q") {
                    close();
                }
            }
        }

        protected void receiveRunning()
        {
            var data = new Byte[256];
            String responseData = String.Empty;

            while(true)
            {
                responseData = String.Empty;

                var bytes = _networkStream.Read(data, 0, data.Length);
                responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                Console.WriteLine("Received: {0}", responseData);


            }
        }

        public void close()
        {
            _thread.Abort();

            _tcpClient.Close();
        }
    }
}