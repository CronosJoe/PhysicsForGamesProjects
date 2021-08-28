using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class KinematicPlayerController : MonoBehaviour
{
    [SerializeField] Rigidbody PlayerRB = null;
    [SerializeField] Collider playerBoundsOnlyCollider = null;
    [SerializeField] PlayerInput playerInput = null;
    [SerializeField] Collider[] collisionResults = new Collider[12];
    [SerializeField] float skinWidth = 0.001f;
    [Range(0,50)]
    [SerializeField] float speed = 0;
    [SerializeField] float gravity = 1;
    public Vector3 Offset;
    // change this value to get desired smoothness
    public float SmoothTime = 0.3f;

    //inputs
    [SerializeField] float movementVector;
    [SerializeField] Vector2 rotationVector;

    [SerializeField] Vector3 projectedPosition = Vector3.zero;
    [SerializeField] Vector3 velocity = Vector3.zero; //set back to zero when updating movement
    private void Start()
    {
        PlayerRB = GetComponentInChildren<Rigidbody>();
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }
    void FixedUpdate()
    {
        InputObtainer();
        CharacterMovement(movementVector, rotationVector);
        KinematicCollision();
        ApplyVelocity();
    }
    void InputObtainer() 
    {
       movementVector = playerInput.currentActionMap["PlayerMovement"].ReadValue<float>();
       rotationVector = playerInput.currentActionMap["MouseInput"].ReadValue<Vector2>();
    }
    void CharacterMovement(float moveF, Vector2 rotateV2) 
    {
        Vector3 v3Rotate = new Vector3(0, rotateV2.x, 0);
        PlayerRB.transform.parent.rotation *= Quaternion.Euler(v3Rotate);
        projectedPosition = transform.position;
        projectedPosition += transform.forward * moveF * Time.deltaTime * speed;
        velocity = transform.forward * moveF * Time.deltaTime * speed;
      
    }
    void KinematicCollision() 
    {
        Vector3 tmpV3 = new Vector3();
        Physics.OverlapBoxNonAlloc(new Vector3(transform.position.x + skinWidth, transform.position.y + skinWidth, transform.position.z + skinWidth), playerBoundsOnlyCollider.bounds.extents, collisionResults, transform.rotation);
        for(int i = 0; i< collisionResults.Length; i++) 
        {
            if (!collisionResults[i] || collisionResults[i] == playerBoundsOnlyCollider) continue;
            Physics.ComputePenetration(playerBoundsOnlyCollider, projectedPosition, transform.rotation, collisionResults[i], collisionResults[i].transform.position, collisionResults[i].transform.rotation, out Vector3 moreTmpDirection, out float tmpDistance);
            Debug.Log("distance "  + tmpDistance);
            Debug.Log("direction "  + moreTmpDirection);
            tmpV3 = moreTmpDirection * tmpDistance;
            Depentrate(tmpV3);
        }
    }

    void Depentrate(Vector3 MTV) 
    {
        PlayerRB.transform.parent.position += MTV;
        ClipVelocity(MTV);
    }
    void ApplyVelocity() 
    {
        PlayerRB.transform.parent.position += velocity;
    }
    void ClipVelocity(Vector3 MTV) 
    {
        velocity = Vector3.ProjectOnPlane(velocity, MTV);
    }
    void AddGravity() 
    {

    }
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.matrix = transform.localToWorldMatrix * Matrix4x4.TRS(Vector3.zero, Quaternion.Euler(0, -90, 0),Vector3.one);
        Gizmos.DrawCube(projectedPosition-transform.position, Vector3.one);
    }

}
