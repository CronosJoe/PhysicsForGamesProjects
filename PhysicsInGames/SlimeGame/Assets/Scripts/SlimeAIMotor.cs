using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlimeAIMotor : MonoBehaviour
{
    [Range(1, 20)]
    [SerializeField] float forwardJumpForce=10;
    [Range(1, 20)]
    [SerializeField] float verticalJumpForce=10;
    [SerializeField] GameObject objective;
    [SerializeField] float jumpDelay = 3;
    [Range(1, 360)]
    [SerializeField] float turnSpeed = 3;
    float jumpTime = 0;
    Rigidbody slimeRB;


    public LayerMask layerToHit;
    // Start is called before the first frame update
    void Start()
    {
        slimeRB = GetComponent<Rigidbody>(); 
    }
    // Update is called once per frame
    void Update()
    {
        
        TurnTowardsYourGoalSlimey();
        MoveTheSlimeyFriends();
    }
    void MoveTheSlimeyFriends()
    {
        if ((jumpTime += Time.deltaTime) > jumpDelay)
        {
            jumpTime = 0;
            //Vector3 movingForce = transform.rotation * new Vector3(0, verticalJumpForce, forwardJumpForce);
            //slimeRB.AddForce(movingForce, ForceMode.Impulse);
            if (CheckYourHeadingSlimeBro())
            {
                Vector3 movingForce = transform.rotation * new Vector3(0, verticalJumpForce, forwardJumpForce);
                slimeRB.AddForce(movingForce, ForceMode.Impulse);
            }
            else 
            {
                Vector3 movingForce = Random.rotation.y * new Vector3(0, verticalJumpForce, forwardJumpForce);
                slimeRB.AddForce(movingForce, ForceMode.Impulse);
            }
            
        }
    }
    void TurnTowardsYourGoalSlimey()
    {
        if (!(Physics.Raycast(transform.position, transform.forward, 800f, layerToHit)))
        {
            Vector3 targetDirection = new Vector3(objective.transform.position.x - transform.position.x, 0, objective.transform.position.z - transform.position.z);
            float singleStep = turnSpeed * Time.deltaTime;
            Vector3 newDirection = Vector3.RotateTowards(transform.forward, targetDirection, singleStep, 0.0f);
            transform.rotation = Quaternion.LookRotation(newDirection);
        }
    }
    bool CheckYourHeadingSlimeBro() 
    {
        return Physics.Raycast(transform.position, transform.forward, 800f, layerToHit);
    }
}
