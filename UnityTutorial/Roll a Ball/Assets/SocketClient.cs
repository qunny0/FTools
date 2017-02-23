using UnityEngine;
using System.Collections;

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;


public class SocketClient : MonoBehaviour {
	TcpClient client;

	void start() {
		
	}

	void Update() {
		if (Input.GetKeyDown (KeyCode.Alpha1)) {
			
		}
	}

	private void Client() {
		client = new TcpClient ();
		try {
			client.Connect(IPAddress.Parse("127.0.0.1"), 10000);
		}
		catch (Exception ex) {
			Debug.Log ("connect server failed : " + ex.Message);
		}

		Debug.Log ("LocalEndPoint = " + client.Client.LocalEndPoint + " . RemoteEndPoint = " + client.Client.RemoteEndPoint);

		// 
		for (int i = 0; i < 2; ++i) {
			try {
				string msg = "hello server I am No " + i;
				NetworkStream streamToServer = client.GetStream();
				byte[] buffer = Encoding.Unicode.GetBytes(msg);
				streamToServer.Write(buffer, 0, buffer.Length);
				Debug.Log("send message : " + msg);
			}
			catch (Exception ex) {
				Debug.Log ("server throw exception : " + ex.Message);
			}
		}
	}
}
