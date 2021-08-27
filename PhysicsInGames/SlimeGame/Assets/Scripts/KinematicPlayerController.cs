using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class KinematicPlayerController : MonoBehaviour
{
    [SerializeField]Rigidbody PlayerRB = null;
    [SerializeField] PlayerInput playerInput;
    [Range(0,50)]
    [SerializeField] float speed = 0;
    [Range(0, 20)]
    [SerializeField] float rotateSpeed;
    public Vector3 Offset;
    // change this value to get desired smoothness
    public float SmoothTime = 0.3f;
    public Transform CameraGameObject = null;
    // This value will change at the runtime depending on target movement. Initialize with zero vector.
    private Vector3 velocity = Vector3.zero;

   
    private void Start()
    {
        CameraGameObject = transform.GetChild(0);
        //Cursor.lockState = CursorLockMode.Locked;
    }
    void FixedUpdate()
    {
        PlayerMovement();
    }
    void PlayerMovement() 
    {
        Vector2 movementVector = playerInput.currentActionMap["PlayerMovement"].ReadValue<Vector2>();
        Vector3 v3Movement = new Vector3(movementVector.x, 0, movementVector.y);
        transform.position += transform.rotation * v3Movement.normalized * Time.deltaTime * speed;

        Vector2 rotationVector = playerInput.currentActionMap["MouseInput"].ReadValue<Vector2>();
        Vector3 v3Rotate = new Vector3(0, rotationVector.x, 0);
        transform.rotation *= Quaternion.Euler(v3Rotate);
    }
}
