using UnityEngine;
using System.Collections;

public class CameraFollowPlayer : MonoBehaviour {

	public GameObject followObject;

	private Vector3 offset;

	// Use this for initialization
	void Start () {
		offset = followObject.transform.position - transform.position;
	}
	
	// Update is called once per frame
	void LateUpdate () {
		transform.position = followObject.transform.position - offset;
	}
}
