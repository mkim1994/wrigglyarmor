import processing.serial.*;

Serial myPort;  // Create object from Serial class

int val;

void setup(){
  size(200,200);
  
  println(Serial.list()[2]);
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
  
  val = 0;
}

void draw(){
   
   if ( myPort.available() > 0) {  // If data is available,
   
    val = myPort.read();         // read it and store it in val
    println(val);
   }
   
   if (val == 1){
     background(200);
   }else if (val == 2){
     background(100);
   }
   
}