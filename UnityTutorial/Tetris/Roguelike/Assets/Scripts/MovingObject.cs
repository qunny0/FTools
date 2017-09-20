using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class MovingObject : MonoBehaviour {

	public float moveTime = .1f;

	// Layer on which collision will be checked
	public LayerMask blockingLayer;

	private BoxCollider2D boxCollider;
	private Rigidbody2D rb2D;
	// Used to make movement more efficient.
	private float inverseMoveTime;

	protected virtual void Start () {
		boxCollider = GetComponent<BoxCollider2D> ();

		rb2D = GetComponent<Rigidbody2D> ();

		inverseMoveTime = 1f / moveTime;
	}

	// Move return true if it is able to move and false it not.
	// Move takes parameters for x direction, y direction and a RaycaseHit2D to check collision
	protected bool Move(int xDir, int yDir, out RaycastHit2D hit) {
		Vector2 start = transform.position;

		Vector2 end = start + new Vector2 (xDir, yDir);

		// Disable the boxCollider so that linecast doesn`t hit this object`s own collider
		boxCollider.enabled = false;

		// Cast a line from start point to end point checking collision on blockingLayer.
		hit = Physics2D.Linecast (start, end, blockingLayer);

		// Re-enable boxCollider after linecast
		boxCollider.enabled = true;

		// Check if anything was hit
		if (hit.transform == null) {
			// If nothing was hit, start SmoothMovement co-routine passing in the vector2 end as destination
			StartCoroutine (SmoothMovement (end));

			return true;
		}

		return false;
	}

	protected IEnumerator SmoothMovement(Vector3 end) {
		float sqrRemainingDistance = (transform.position - end).sqrMagnitude;

		while (sqrRemainingDistance > float.Epsilon) {
			Vector3 newPosition = Vector3.MoveTowards (rb2D.position, end, inverseMoveTime * Time.deltaTime);

			rb2D.MovePosition (newPosition);

			sqrRemainingDistance = (transform.position - end).sqrMagnitude;

			yield return null;
		}
	}

	protected virtual void AttemptMove <T> (int xDir, int yDir) where T : Component {
		RaycastHit2D hit;

		bool canMove = Move (xDir, yDir, out hit);

		// check if nothing was hit by linecast
		if (hit.transform == null) {
			return;
		}

		T hitComponent = hit.transform.GetComponent<T> ();

		if (!canMove && hitComponent != null) {
			OnCanMove (hitComponent);
		}
	}

	protected abstract void OnCanMove <T> (T component) where T : Component;
}
