using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlimeMove : MonoBehaviour
{
    [SerializeField] Rigidbody slimeRB;
    [Range(1, 100)]
    [SerializeField] float forwardJumpSpeed = 5;
    [Range(1, 100)]
    [SerializeField] float upForce = 15;
    [Range(0.1f, 100)]
    [SerializeField] float jumpDelay = 3;
    float jumpTime = 0;
    [Range(1,360)]
    [SerializeField] float turnSpeed = 3;
    // Start is called before the first frame update
    void Start()
    {
        slimeRB = GetComponent<Rigidbody>();
    }
    void Update() 
    {
        Jumping();
        Turning();
    }
    #region HideTheUgly
    void Jumping()
    {
        //bool jumpForce = Input.GetButtonDown("Jump");
        //if ((jumpTime+=Time.deltaTime)>jumpDelay && jumpForce)
        //{
        //    jumpTime = 0;
        //    Vector3 movingForce = transform.rotation * new Vector3(0, upForce, forwardJumpSpeed);
        //    slimeRB.AddForce(movingForce, ForceMode.Impulse);
        //}
    }
    void Turning() 
    {
        //bool turnNow = Input.GetButton("Horizontal");
        //if (turnNow) 
        //{
        //    transform.Rotate(new Vector3(0, Input.GetAxisRaw("Horizontal") * turnSpeed*Time.deltaTime, 0));
        //}
    }
    #endregion
}
