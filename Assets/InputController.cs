using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Text.RegularExpressions;
using UnityEngine.UI;

public class InputController : MonoBehaviour {

	SerialPort stream = new SerialPort("/dev/cu.usbmodemHIDP1", 9600);
	private int pValue = 0;

    public int potentioMin = 0;
	public int potentioLimit = 0;



	// Use this for initialization
	void Start () {
		stream.Open ();
	}

    // Update is called once per frame
    void Update()
    {
        string value = stream.ReadLine();
        pValue = int.Parse(Regex.Match(value, @"\d+").Value);
//		Debug.Log (pValue);



    }

}
