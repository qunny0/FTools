﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Player : MovingObject {

	public float restartLevelDelay = 1f;
	public int pointsPerFood = 10;
	public int pointsPerSoda = 20;
	public int wallDamage = 1;

	private Animator animator;
	private int food;

	public Text foodText;

	public AudioClip moveSound1;
	public AudioClip moveSound2;
	public AudioClip eatSound1;
	public AudioClip eatSound2;
	public AudioClip drinkSound1;
	public AudioClip drinkSound2;
	public AudioClip gameOverSound;

	private Vector2 touchOrigin = -Vector2.one;

	protected override void Start() {
		animator = GetComponent<Animator> ();

		food = GameManager.instance.playerFoodPoints;

		foodText.text = "Food: " + food;

		base.Start ();
	}

	private void OnDisable() {
		GameManager.instance.playerFoodPoints = food;
	}

	// Update is called once per frame
	void Update () {
		if (!GameManager.instance.playersTurn)
			return;

		// Used to store the horizontal move direction
		int horizontal = 0;
		int vertical = 0;

		#if UNITY_STANDALONE || UNITY_WEBPLAYER

		horizontal = (int)(Input.GetAxisRaw ("Horizontal"));
		vertical = (int)(Input.GetAxisRaw ("Vertical"));

		if (horizontal != 0) {
			vertical = 0;
		}

		#elif UNITY_IOS || UNITY_ANDROID || UNITY_WP8 || UNITY_IPHONE

		if (Input.touchCount > 0) {
			Touch myTouch = Input.touches[0];
			
			if (myTouch.TouchPhase == TouchPhase.Began) {
				touchOrigin = myTouch.Position;
			} else if (myTouch.phase == TouchPhase.Ended && touchOrigin.x >= 0) {
				Vector2 touchEnd = myTouch.Position;

				float x = touchEnd.x - touchOrigin.x;

				float y = touchEnd.y - touchOrigin.y;

				touchOrigin.x = -1;

				if (Math.Abs(x) > Math.Abs(y)) {
					horizontal = x > 0 ? 1 : -1;
				} else {
					vertical = y > 0 ? 1 : -1;
				}
			}
		}
		#endif

		if (horizontal != 0 || vertical != 0) {
			// Call AttemptMove passing in the generic parameter Wall, since that is what Player may interact with if they
			// encounter one (by attacking it)
			// Pass in horizontal and vertical as parameters to specify the direction to move Player in
			AttemptMove<Wall> (horizontal, vertical);
		}
	}

	protected override void AttemptMove<T> (int xDir, int yDir) {
		// Every time player moves, subtract from food points total.
		food--;

		foodText.text = "Food: " + food;

		base.AttemptMove<T> (xDir, yDir);

		RaycastHit2D hit;

		if (Move (xDir, yDir, out hit)) {
			// 
		}

		CheckIfGameOver ();

		GameManager.instance.playersTurn = false;
	}

	protected override void OnCanMove <T> (T component) {
		Wall hitWall = component as Wall;

		hitWall.DamageWall (wallDamage);

		animator.SetTrigger ("playerChop");
	}


	private void OnTriggerEnter2D(Collider2D other) {
		if (other.tag == "Exit") {
			Invoke ("Restart", restartLevelDelay);

			enabled = false;
		} else if (other.tag == "Food") {
			food += pointsPerFood;

			foodText.text = " + " + pointsPerFood + " Food: " + food;

			other.gameObject.SetActive (false);
		} else if (other.tag == "Soda") {
			food += pointsPerSoda;

			foodText.text = " + " + pointsPerSoda + " Food: " + food;

			other.gameObject.SetActive (false);
		}
	}

	private void Restart() {
		SceneManager.LoadScene (0);
	}

	public void LoseFood(int loss) {
		animator.SetTrigger ("playerHit");

		food -= loss;

		foodText.text = " - " + loss + " Foods: " + food;

		CheckIfGameOver ();
	}

	private void CheckIfGameOver() {
		if (food <= 0) {
			GameManager.instance.GameOver (0);
		}
	}
}
