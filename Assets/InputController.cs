using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Text.RegularExpressions;
using UnityEngine.UI;
using System;

public class InputController : MonoBehaviour {

    SerialPort stream = new SerialPort("/dev/cu.usbmodem1421", 9600);
    private int pValue = 0;

    public int potentioMin = 0;
	public int potentioLimit = 0;



	// Use this for initialization
	void Start () {
        stream.ReadTimeout = 50;
		stream.Open ();

	}

    // Update is called once per frame
    void Update()
    {
       // Debug.Log("what");
        StartCoroutine(
            AsynchronousReadFromArduino(
                (string s) => Debug.Log(s),
                () => Debug.LogError("Error!"),
            10f
            )
        );
      /*  string value = stream.ReadLine();
        //pValue = int.Parse(Regex.Match(value, @"\d+").Value);
        pValue = int.Parse(value);
        Debug.Log (pValue);*/


    }

    public string ReadFromArduino(int timeout = 0){
        stream.ReadTimeout = timeout;
        try{
            return stream.ReadLine();
        }
        catch(TimeoutException e){
            return null;
        }
    }

    public IEnumerator AsynchronousReadFromArduino(Action<string> callback, Action fail = null, float timeout = float.PositiveInfinity){
        DateTime initialTime = DateTime.Now;
        DateTime nowTime;
        TimeSpan diff = default(TimeSpan);
        string dataString = null;

        do
        {
            try
            {
                dataString = stream.ReadLine();
            }
            catch (TimeoutException)
            {
                dataString = null;
            }
            if (dataString != null)
            {
                callback(dataString);
                yield return null;
            }
            else
            {
                yield return new WaitForSeconds(0.05f);
            }
            nowTime = DateTime.Now;
            diff = nowTime - initialTime;
        } while (diff.Milliseconds < timeout);
        if (fail != null){
            fail();

        }
        yield return null;
    }

}
