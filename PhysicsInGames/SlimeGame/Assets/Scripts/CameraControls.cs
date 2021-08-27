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
        float rotateValue = cameraInput.currentActionMap["CameraRotation"].ReadValue<float>();
        Vector3 rotateVector = new Vector3(0, rotateValue, 0);
        transform.rotation *= Quaternion.Euler(rotateVector);

        float moveValue = cameraInput.currentActionMap["MovingCamera"].ReadValue<float>();
        
    }
}
