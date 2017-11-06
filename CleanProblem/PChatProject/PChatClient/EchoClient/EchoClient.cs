using System;

using System.Net;
using System.Net.Sockets;

namespace PChatClient
{
    class EchoClient
    {
        TcpClient _tcpClient;

        IPAddress _ipAddress;

        int _port;

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
            }
            catch {
                Console.WriteLine("connect failed. ");
                return false;
            }

            Console.WriteLine("connect success. ");
            return true;
        }
    }
}