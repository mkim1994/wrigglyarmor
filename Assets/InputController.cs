using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Text.RegularExpressions;
using UnityEngine.UI;

public class InputController : MonoBehaviour {

	SerialPort stream = new SerialPort("/dev/cu.usbmodemHIDP1", 9600);
    private float pValue = 0;

    public float potentioMin = 0;
	public float potentioLimit = 0;



	// Use this for initialization
	void Start () {
		stream.Open ();
	}

    // Update is called once per frame
    void Update()
    {
        string value = stream.ReadLine();
        pValue = float.Parse(Regex.Match(value, @"\d+").Value);
		Debug.Log (pValue);



    }

}
