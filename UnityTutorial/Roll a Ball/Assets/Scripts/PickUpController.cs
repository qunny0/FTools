using UnityEngine;
using System.Collections;

public class PickUpController : MonoBehaviour {

	public float rotationYspeed = 1.0f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		float dt = Time.deltaTime;
		transform.Rotate(new Vector3(45, 30, 35) * dt);
	}
}

