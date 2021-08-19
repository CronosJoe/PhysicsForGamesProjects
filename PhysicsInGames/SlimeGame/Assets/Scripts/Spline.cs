using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spline : MonoBehaviour
{
    [SerializeField] GameObject objFab = null;
    [SerializeField] float delay = 1.0f;
    [SerializeField] List<Transform> waypoints = new List<Transform>();
    [SerializeField] GameObject movingPlatform;
    Rigidbody platformRB;
    // Update is called once per frame
    float timer = 0.0f;
    Vector3[] arr = new Vector3[0];

    private void Start()
    {
        arr = new Vector3[waypoints.Count];
        for(int x = 0; x < arr.Length; ++x)
        {
            arr[x] = waypoints[x].position;
        }

        platformRB = movingPlatform.GetComponent<Rigidbody>();
    }

    void Update()
    {
        timer += Time.deltaTime;

        //InstantiateTheSpline(); //note this instantiation doesn't end and is to demonstrate pathing
        FollowTheSpline(); //this should move the platform from waypoint[0] to waypoint[n-1]
        if (timer >= delay)
            timer = 0.0f;
    }
    void InstantiateTheSpline() 
    {
        Instantiate(objFab, SplineIt(waypoints.ToArray(), timer / delay), Quaternion.identity);
    }
    void FollowTheSpline() 
    {
        platformRB.MovePosition(SplineIt(waypoints.ToArray(), timer / delay));
    }
    Vector3 SplineIt(Vector3[] arr, float t)
    {
        List<Vector3> points = new List<Vector3>();
        for(int x = 0; x < arr.Length; ++x)
        {
            points.Add(arr[x]);
        }

        while (points.Count > 1)
        {
            for (int x = 0; x < points.Count - 1; ++x)
            {
                points[x] = Vector3.Lerp(points[x], points[x + 1], t);
            }

            points.RemoveAt(points.Count - 1);
        }

        return points[0];
    }
    Vector3 SplineIt(Transform[] arr, float t)
    {
        List<Vector3> points = new List<Vector3>();
        for (int x = 0; x < arr.Length; ++x)
        {
            points.Add(arr[x].position);
        }
        points.Add(arr[0].position);

        while (points.Count > 1)
        {
            for (int x = 0; x < points.Count - 1; ++x)
            {
                points[x] = Vector3.Lerp(points[x], points[x + 1], t);
            }

            points.RemoveAt(points.Count - 1);
        }

        return points[0];
    }
}
