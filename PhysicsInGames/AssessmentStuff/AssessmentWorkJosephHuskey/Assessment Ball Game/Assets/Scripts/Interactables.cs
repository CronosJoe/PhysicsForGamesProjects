using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Interactables : MonoBehaviour
{
    [SerializeField] bool hasBeenInteracted = false;
    public GameObject controlledObject;
    private void Start()
    {
        hasBeenInteracted = false;
    }
    public GameObject SelectedByPlayer() 
    {
        return controlledObject;
    }
    public void FinishedControlling() 
    {
        hasBeenInteracted = false;
    }
}
