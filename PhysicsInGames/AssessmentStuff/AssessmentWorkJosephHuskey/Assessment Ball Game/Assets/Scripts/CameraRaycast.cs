using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class CameraRaycast : MonoBehaviour
{
    //this script will handle player input and 
    [SerializeField] PlayerInput cameraMover;
    [Range(0, 100)]
    [SerializeField] float cameraSpeed = 0;
    [SerializeField] float smooth = 0.4f;
    Vector3 vel = new Vector3();
    [SerializeField] Camera cam;
    [SerializeField]LayerMask interactableLayer = 0;
    GameObject currentControlled = null;
    bool currentlyControlling = false;
    GameObject activatorObject = null;
    // Start is called before the first frame update
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = true;
        cameraMover.currentActionMap["Clicking"].started += RayCastFromMouse;
        cameraMover.currentActionMap["Activated"].started += UseCurrentAction;
    }

    private void MoveControlledObject()
    {
        if (currentControlled)
            if (currentControlled.GetComponent<Obstacles>().canMove)
            currentControlled.GetComponent<Obstacles>().Movement(cameraMover.currentActionMap["MovingObstacle"].ReadValue<Vector2>());
    }

    private void UseCurrentAction(InputAction.CallbackContext obj)
    {
        if(currentControlled)
        currentControlled.GetComponent<Obstacles>().Activated();
    }

    private void RayCastFromMouse(InputAction.CallbackContext obj)
    {
        //TODO fix this ray so that the raycast goes towards player/interactable
        RaycastHit hitTarget;
        if (Physics.Raycast(cam.transform.position, Vector3.forward, out hitTarget, 400f, interactableLayer))
        {
            print(hitTarget.transform.name);
            currentControlled = hitTarget.transform.GetComponent<Interactables>().controlledObject;
            currentlyControlling = true;
            if (activatorObject) 
            {
                activatorObject.GetComponent<Interactables>().FinishedControlling();
            }
            activatorObject = hitTarget.collider.gameObject;
        }
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        MoveCamera();
        MoveControlledObject();
    }
    void MoveCamera()
    {
        Vector2 movement = cameraMover.currentActionMap["MovingCamera"].ReadValue<Vector2>();
        transform.position = Vector3.SmoothDamp(transform.position, transform.position + (new Vector3(movement.x, movement.y, 0) * Time.deltaTime * cameraSpeed), ref vel, smooth);
    }
}
