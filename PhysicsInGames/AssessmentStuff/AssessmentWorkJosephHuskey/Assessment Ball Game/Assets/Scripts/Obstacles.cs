using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Obstacles : MonoBehaviour
{
    [SerializeField] int ID; //I plan to set this when I setup the prefabs
    // Start is called before the first frame update
    public bool canMove; //if the object can be moved with wasd or just ad
    [Range(0, 100)]
    [SerializeField] float fanSpeed = 0;
    [SerializeField] bool fanGoing = false;
    [Range(0, 100)]
    [SerializeField] float movementTime = 0;
    [SerializeField] float moveSpeed;
    Vector3 vel = new Vector3();
    public void Activated()
    {
        if (ID < 2)
        {
            switch (ID)
            {
                case 0:
                    SwingActive();
                    break;
                case 1:
                    FanActive();
                    break;
            }
        }
    }
    public void Movement(Vector2 movementVector) 
    {
        print("test " + movementVector);
        Vector3 movementVector3 = new Vector3(movementVector.x, 0, movementVector.y)*Time.deltaTime * moveSpeed;
        transform.Translate(movementVector3, Space.World);
    }
    void SwingActive()
    {
        JointMotor tmpMotor = GetComponent<HingeJoint>().motor;
        tmpMotor.targetVelocity *= -1;
        GetComponent<HingeJoint>().motor = tmpMotor;
    }
    void FanActive() 
    {
        fanGoing = !fanGoing; //this will flip the current enabled/disabled of the fan's trigger collider
    }
    private void OnTriggerStay(Collider other)
    {
        if(other.tag == "Player" && fanGoing) 
        {
            print(other.name);
            other.attachedRigidbody.AddForce(transform.forward*fanSpeed);
        }
    }
}
