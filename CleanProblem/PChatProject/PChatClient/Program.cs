using System;

namespace PChatClient
{
    class Program
    {
        static void Main(string[] args)
        {
            var echoClient = new EchoClient("127.0.0.1", 3333);
            echoClient.initialize();
        }
    }
}
