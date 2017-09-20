using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour {

	public static GameManager instance = null;

	private BoardManager boardScript;

	private int level = 3;

	public int playerFoodPoints = 100;

	[HideInInspector] public bool playersTurn = true;

	// Awake is always called before any Start functions
	void Awake () {
		if (instance == null) {
			instance = this;
		} else if (instance != this) {
			// Destroy this. this enforces our singleton pattern, meaning there can only ever be one instance of a GameManager.
			DestroyObject (gameObject);
		}

		//
		DontDestroyOnLoad(gameObject);

		boardScript = GetComponent<BoardManager> ();

		InitGame ();
	}

	public void GameOver (int level) {
		
	}

	void InitGame() {
		boardScript.SetupScene (level);
	}
}
