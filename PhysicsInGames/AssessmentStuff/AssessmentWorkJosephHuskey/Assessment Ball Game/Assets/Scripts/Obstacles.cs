using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Obstacles : MonoBehaviour
{
    [SerializeField] int ID; //I plan to set this when I setup the prefabs
    // Start is called before the first frame update
    [SerializeField] bool canMove; //if the object can be moved with wasd or just ad
    [Range(0, 100)]
    [SerializeField] float fanSpeed;
    [SerializeField] bool fanGoing;
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
    void Move() 
    {
        if (ID == 2) 
        {
            MoveSpring();
        }
    }
    void MoveSpring() 
    {

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
