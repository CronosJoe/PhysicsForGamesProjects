using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlimeAIMotor : MonoBehaviour
{
    [Range(1, 20)]
    [SerializeField] float forwardJumpForce=10;
    [Range(1, 20)]
    [SerializeField] float verticalJumpForce=10;
    public GameObject objective; //making this public so it can be changed when they are created.
    [SerializeField] float jumpDelay = 3;
    [Range(1, 360)]
    [SerializeField] float turnSpeed = 3;
    float jumpTime = 0;
    int happinessScore = 0;
    [SerializeField]int ageUpScore = 0;
    Rigidbody slimeRB;
    [SerializeField]Vector3 sizeLimit = new Vector3(16f,16f,16f);


    public LayerMask layerToHit;
    // Start is called before the first frame update
    void Start()
    {
        slimeRB = GetComponent<Rigidbody>(); 
    }
    // Update is called once per frame
    void FixedUpdate()
    {
        
        TurnTowardsYourGoalSlimey();
        MoveTheSlimeyFriends();
    }
    void MoveTheSlimeyFriends()
    {
        if ((jumpTime += Time.deltaTime) > jumpDelay)
        {
            jumpTime = 0;
            Vector3 movingForce = transform.rotation * new Vector3(0, verticalJumpForce, forwardJumpForce);
            slimeRB.AddForce(movingForce, ForceMode.Impulse);
        }
    }
    void TurnTowardsYourGoalSlimey()
    {
        if (CheckYourHeadingSlimeBro())
        {
         Vector3 targetDirection = new Vector3(objective.transform.position.x - transform.position.x, 0, objective.transform.position.z - transform.position.z);
         float singleStep = turnSpeed * Time.deltaTime;
         Vector3 newDirection = Vector3.RotateTowards(transform.forward, targetDirection, singleStep, 0.0f);
         transform.rotation = Quaternion.LookRotation(newDirection);
        }
        else
        {
         Vector3 targetDirection = new Vector3(Random.Range(-1.0f, 1.0f), 0, Random.Range(-1.0f, 1.0f));
         float singleStep = turnSpeed * Time.deltaTime;
         Vector3 newDirection = Vector3.RotateTowards(transform.forward, targetDirection, singleStep, 0.0f);
         transform.rotation = Quaternion.LookRotation(newDirection);
        }
    }
    bool CheckYourHeadingSlimeBro() 
    {
        Vector3 targetDirection = new Vector3(objective.transform.position.x - transform.position.x, objective.transform.position.y - transform.position.y, objective.transform.position.z - transform.position.z);
        if (Physics.Raycast(transform.position, targetDirection, out RaycastHit hit, 800f))
        {
            return hit.collider.CompareTag("Enemy");
        }
        else
        {
            return false;
        }
    }
    public void RubThePost() 
    {
        happinessScore++;
        if (CheckHappiness()) 
        {
            
            transform.localScale *= 2;
            happinessScore = 0;
        }
    }
    bool CheckHappiness() 
    {
        return happinessScore > ageUpScore;
    }
    void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.CompareTag("Enemy")) 
        {
            if (transform.localScale.x < sizeLimit.x)
            {
                RubThePost();
            }
        }
    }
}
