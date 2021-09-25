using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResetScript : MonoBehaviour
{
    [SerializeField] Camera camera;
    [SerializeField] GameObject playerSphere;
    Vector3 playerStartingPosition = Vector3.zero;
    Vector3 cameraStartingPosition = Vector3.zero;

    [SerializeField]float smoothTime;
    private Vector3 distanceVec = Vector3.zero;
    private Vector3 velocity = Vector3.zero;
    private bool completedMovement = false;
    [Range(0, 100)]
    [SerializeField] float cameraSpeed = 0;
    // Start is called before the first frame update
    void Start()
    {
        cameraStartingPosition = camera.transform.position;
        playerStartingPosition = playerSphere.transform.position;
    }
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.transform.CompareTag("Player"))
        {
            ResetTheWorld(); //this will only activate when the player falls off the map, I shouldn't have other things fall down here? still safe to check for something like this
        }
    }
    private void ResetTheWorld() 
    {
        camera.transform.position = cameraStartingPosition;
        playerSphere.GetComponent<Rigidbody>().velocity = Vector3.zero;
        playerSphere.transform.position = playerStartingPosition;
    }
}
