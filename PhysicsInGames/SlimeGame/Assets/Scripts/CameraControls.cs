using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class CameraControls : MonoBehaviour
{
    public PlayerInput cameraInput;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        Vector2 rotateVector2 = cameraInput.currentActionMap["CameraRotation"].ReadValue<Vector2>();
        transform.rotation *= Quaternion.Euler(rotateVector2);
    }
}
