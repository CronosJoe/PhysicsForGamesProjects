using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControls : MonoBehaviour
{
    public LayerMask SlimeLayer;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    void CameraRay() 
    {
        if (Input.GetMouseButtonDown(1)) 
        {
           Physics.Raycast(transform.position,transform.forward,800f,SlimeLayer);
        }
    }
}
