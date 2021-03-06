﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour {

	public float levelStartDelay = 2f;
	public float turnDelay = 0.1f;
	public int playerFoodPoints = 100;

	public static GameManager instance = null;

	private BoardManager boardScript;

	private int level = 3;

	[HideInInspector] public bool playersTurn = true;

	private List<Enemy> enemies;

	private bool enemiesMoving;


	private Text levelText;
	private GameObject levelImage;
	private bool doingSetup = true;


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

		enemies = new List<Enemy> ();

		boardScript = GetComponent<BoardManager> ();

		InitGame ();
	}

	void OnLevelWasLoaded(int index) {
		level++;

		InitGame ();
	}

	public void GameOver (int level) {
		levelText.text = "After " + level + " days, you starved.";

		levelImage.SetActive (true);

		enabled = false;
	}

	void InitGame() {

		doingSetup = true;

		levelImage = GameObject.Find ("LevelImage");

		levelText = GameObject.Find ("LevelText").GetComponent<Text> ();

		levelText.text = "Day " + level;

		levelImage.SetActive (true);

		Invoke ("HideLevelImage", levelStartDelay);


		enemies.Clear ();
		
		boardScript.SetupScene (level);
	}

	void HideLevelImage() {
		levelImage.SetActive (false);

		doingSetup = false;
	}

	public void AddEnemeyToList(Enemy script) {
		enemies.Add (script);
	}

	void Update() {
		if (playersTurn || enemiesMoving)
			return;

		StartCoroutine (MoveEnemies ());
	}

	IEnumerator MoveEnemies() {
		enemiesMoving = true;

		yield return new WaitForSeconds (turnDelay);

		if (enemies.Count == 0) {
			yield return new WaitForSeconds (turnDelay);
		}

		for (int i = 0; i < enemies.Count; i++) {
			enemies[i].MoveEnemy();
				
			yield return new WaitForSeconds(enemies[i].moveTime);
		}

		playersTurn = true;

		enemiesMoving = false;
	}
}
