using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace PChatServer.Src
{
    class CServer
    {
        private TcpListener tcpListener;

        private Thread listenerThread;

        public static volatile Boolean running = false;

        public IPAddress address { set; get; }

        public int port { set; get; }

        public void ListenerClient()
        {
            if (tcpListener == null)
            {
                Console.WriteLine("CServer not initialize, Please Check ... ");
                return;
            }

            try
            {
                tcpListener.Start();
            }
            catch
            {
                Console.WriteLine("tcpListener listener failed. Please Check port whether is using ...");
                return;
            }

            Console.WriteLine("tcpListener listener successful. Start listener connect...");

            while (running)
            {
                try
                {
                    TcpClient tc = tcpListener.AcceptTcpClient();
                    NetworkStream stream = tc.GetStream();

                    StreamWriter tcw = new StreamWriter(stream);
                    StreamReader tcr = new StreamReader(stream);
                }
                catch (SocketException)
                {
                    if (!running)
                    {
                        Console.WriteLine("tcpListener closed. ");
                        return;
                    }
                }
                catch
                {
                    Console.WriteLine("unknow error. ");
                    return;
                }
            }
        }

        public CServer(String ip, int pot)
        {
            address = IPAddress.Parse(ip);

            port = pot;

            running = false;
        }

        public void initialize()
        {
            tcpListener = new TcpListener(address, port);
            listenerThread = new Thread(ListenerClient);
            running = true;
            listenerThread.Start();

            Console.WriteLine("Server initialize finish...");
        }
    }
}
