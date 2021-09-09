using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class CameraRaycast : MonoBehaviour
{
    [SerializeField] PlayerInput cameraMover;
    [Range(0, 100)]
    [SerializeField] float cameraSpeed = 0;
    [SerializeField] float smooth = 0.4f;
    Vector3 vel = new Vector3();
    [SerializeField] Camera cam;
    [SerializeField]LayerMask interactableLayer = 0;

    // Start is called before the first frame update
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = true;
        cameraMover.currentActionMap["Clicking"].started += RayCastFromMouse;
    }

    private void RayCastFromMouse(InputAction.CallbackContext obj)
    {
        //TODO fix this ray so that the raycast goes towards player/interactable
        RaycastHit hitTarget;
        if (Physics.Raycast(cam.transform.position, Vector3.forward, out hitTarget, 400f, interactableLayer))
        {
            print("Current hit is " + hitTarget.transform.name);
            //put the interaction portion here
        }
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        MoveCamera();
    }
    void MoveCamera()
    {
        Vector2 movement = cameraMover.currentActionMap["MovingCamera"].ReadValue<Vector2>();
        transform.position = Vector3.SmoothDamp(transform.position, transform.position + (new Vector3(movement.x, movement.y, 0) * Time.deltaTime * cameraSpeed), ref vel, smooth);
    }
}
