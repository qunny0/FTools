using UnityEngine;
using System.Collections;
using System.Net.Sockets;

public class CameraFollowPlayer : MonoBehaviour {

	public GameObject followObject;

	private Vector3 offset;

	// Use this for initialization
	void Start () {
		offset = followObject.transform.position - transform.position;

//		var client = new TcpClient ();
//		client.Connect ("127.0.0.1", 8888);
//		client.Close ();

//		NetworkConnectionError error = Network.Connect ("127.0.0.1", "8888");
//		if (error != NetworkConnectionError.NoError) {
//			Debug.Log ("Client error : " + error);
//		} else {
//			Debug.Log ("Client successful ! ");
//		}
	}
	
	// Update is called once per frame
	void LateUpdate () {
		transform.position = followObject.transform.position - offset;
	}
}
