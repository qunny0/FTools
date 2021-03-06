using System;

using System.Net;
using System.Net.Sockets;

using System.Threading;
using System.IO;

namespace PChatServer
{
    class PEchoServer
    {
        private volatile Boolean _running;

        private TcpListener _tcpListener;

        private IPAddress _ipAddress {set; get;}

        private int _port {set; get;}

        private Thread _listenThread;

        private TcpClient _tcpClient;

        private StreamWriter _clientWriter;

        private StreamReader _clientReader;

        public PEchoServer(String ip, int port)
        {
            _ipAddress = IPAddress.Parse(ip);

            _port = port;

            _running = false;

            _tcpClient = null;
        }

        public void initialize()
        {
            Log.i("EchoServer initialize start ....");

            _tcpListener = new TcpListener(_ipAddress, _port);

            _listenThread = new Thread(this.listenClient);

            _running = true;

            _listenThread.Start();

            Log.i("EchoServer initialize end ....");            
        }
        
        protected void listenClient()
        {
            Log.i("start listener client .");

            if (_tcpListener == null) 
            {
                Log.i("EchoServer not initialize. Please Check ...");
                return ;
            }

            try {
                _tcpListener.Start();
            }
            catch {
                Log.i("EchoServer start failed.");
                return ;
            }

            while (_running) 
            {
                _tcpClient = _tcpListener.AcceptTcpClient();

                Log.i("listen client connect");

                var clientStream = _tcpClient.GetStream();

                _clientWriter = new StreamWriter(clientStream);

                _clientReader = new StreamReader(clientStream);

                Thread clientT = new Thread(this.clientRun);

                clientT.Start();
            }
        }

        protected void clientRun()
        {
            while (true) 
            {
                try {
                    String message = _clientReader.ReadLine();

                    Log.i(" -- receive : " + message);

                    _clientWriter.WriteLine(message);

                    Log.i(" -- response: " + message);
                }
                catch {
                    
                }
            }
        }
    }
}