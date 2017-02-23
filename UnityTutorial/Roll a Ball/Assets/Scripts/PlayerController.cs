using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerController : MonoBehaviour {

	public float speed;

	public Text txtScoreCount;
	public Text txtResult;

	private Rigidbody rb;

	private int _count;


	// Use this for initialization
	void Start () {
		rb = GetComponent<Rigidbody> ();
		_count = 0;
		setPickUpCount ();

		txtResult.text = "";
	}

	void FixedUpdate() {
		float moveHorizontal = Input.GetAxis ("Horizontal");
		float moveVertical = Input.GetAxis ("Vertical");

		Vector3 movement = new Vector3 (moveHorizontal, 0, moveVertical);

		rb.AddForce (movement * speed);
	}

	void OnTriggerEnter(Collider other) {
		if (other.gameObject.CompareTag ("Pick Up")) {
			other.gameObject.SetActive (false);
			_count += 1;
			setPickUpCount ();
		}
	}

	void setPickUpCount()
	{
		txtScoreCount.text = "Count: " + _count.ToString ();
		if (_count >= 12) {
			txtResult.text = "-_- haha you win!";
		}
	}
} 
