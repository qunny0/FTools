using System;

namespace PChatServer
{
    class Program
    {
        static void Main(string[] args)
        {
            String ip = "127.0.0.1";

            int port = 3333;

            PEchoServer echoServer = new PEchoServer(ip, port);

            echoServer.initialize();

            // Console.WriteLine("Hello Worldˇ!");
        }
    }
}
