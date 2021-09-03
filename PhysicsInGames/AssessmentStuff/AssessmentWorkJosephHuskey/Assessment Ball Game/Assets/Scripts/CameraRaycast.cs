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

    // Start is called before the first frame update
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = true;
        cameraMover.currentActionMap["Clicking"].started += RayCastFromMouse;
    }

    private void RayCastFromMouse(InputAction.CallbackContext obj)
    {
        //TODO fix this ray so that the raycast goes towards player/interactables
        Ray cameraRay = cam.ViewportPointToRay(Vector3.forward);
        RaycastHit hitTarget;
        Debug.DrawRay(cameraRay.origin, cameraRay.direction,Color.red);
        if (Physics.Raycast(cameraRay, out hitTarget))
        {
            print("Current hit is " + hitTarget.transform.name);
        }
        else
        {
            print("missed");
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
