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

        private NetworkStream _clientStream;

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

                var clientAddress = ((IPEndPoint)_tcpClient.Client.RemoteEndPoint).Address.ToString();

                Log.i("listen client connect : " + clientAddress);

                _clientStream = _tcpClient.GetStream();

                _clientWriter = new StreamWriter(_clientStream);

                _clientReader = new StreamReader(_clientStream);

                Thread clientT = new Thread(this.clientRun);

                clientT.Start();
            }
        }

        protected void clientRun()
        {
            while (true) 
            {
                try {
                    byte[] buffer = new byte[256];

                    var len = _clientStream.Read(buffer, 0, buffer.Length);

                    var bstr = System.Text.Encoding.Default.GetString(buffer);

                    Log.i(" -- receive : " + bstr);

                    if (bstr == "q") {
                        close();
                    }
                    else {
                        _clientStream.Write(buffer, 0, buffer.Length);
                    }
                }
                catch {
                    
                }
            }
        }

        protected void close()
        {
            _listenThread.Abort();

            _tcpClient.Close();

            _tcpListener.Stop();
        }
    }
}