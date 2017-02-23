using UnityEngine;
using System.Collections;

public class PickUpController : MonoBehaviour {

	public float rotationYspeed = 1.0f;

	public float rotationX = 0;
	public float rotationY = 30;
	public float rotationZ = 0;


	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		float dt = Time.deltaTime;
		transform.Rotate(new Vector3(rotationX, rotationY, rotationZ) * dt);
	}
}

