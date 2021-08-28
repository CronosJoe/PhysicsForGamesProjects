using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlimeSpawner : MonoBehaviour
{
    [SerializeField] GameObject SlimePrefab = null;
    [SerializeField]int armySize = 0;
    [SerializeField] Transform spawnLocation = null;
    [SerializeField] GameObject mapObjective = null;

    GameObject[] slimeyArmy = new GameObject[15];
    // Start is called before the first frame update
    void FixedUpdate()
    {
        if (!CheckTheArmy())
        {
            CreateTheArmy();
            armySize++;
        }
    }
    bool CheckTheArmy() 
    {
        return slimeyArmy.Length == armySize;
    }
    void CreateTheArmy() 
    {
      GameObject newSlime = Instantiate(SlimePrefab, spawnLocation);
      newSlime.GetComponent<SlimeAIMotor>().objective = mapObjective;
    }
    
}
