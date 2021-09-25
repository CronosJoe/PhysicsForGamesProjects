using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ButtonScript : MonoBehaviour
{
    public void Start()
    {
        Cursor.lockState = CursorLockMode.None;
    }
    public void OnPlayButton()
    {
        SceneManager.LoadScene("Testing");
    }
    public void OnQuit()
    {
        Application.Quit();
    }
}
