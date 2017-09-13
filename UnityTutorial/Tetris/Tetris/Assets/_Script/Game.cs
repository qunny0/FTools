using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Game : MonoBehaviour {

	public Text txtScore;

	public GameObject nextCellShow;

	// Use this for initialization
	void Start () {
		txtScore.text = "0";
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	void setNextCell (GameObject cell) {
		
	}

	void setScore (int score) {
		txtScore.text =  "" + score;
	}
}
