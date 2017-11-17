import processing.serial.*;
import processing.sound.*;
import java.io.File; 

Serial myPort;  // Create object from Serial class
SoundFile transformationMusic;
SoundFile finishMusic;
int val;

float currentRate = 1;

float rateIncrement = 0.001;

String mode = "start";

void setup(){
  size(200,200);
  
  println(Serial.list());
  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 9600);
  
  val = 0;
  
  mode = "start";
  transformationMusic = new SoundFile(this, "transformation.mp3");
  finishMusic = new SoundFile(this, "finished.mp3");
  
}

void draw(){
   
   if ( myPort.available() > 0) {  // If data is available,
   
    val = myPort.read();         // read it and store it in val
    println(val);
   }else{
     val = 0;
   }
   
   
   if (val == 1){
     if(mode == "playing"){
       currentRate+=rateIncrement;
        transformationMusic.rate(currentRate);
     }
     background(200);
   }else if (val == 2){
      if(mode == "playing"){
       currentRate+=rateIncrement;
        transformationMusic.rate(currentRate);
     }
     background(100);
   }else if (val == 3){
     //button pressed for first time
     if (mode == "start"){
       mode = "playing";
       currentRate = 1;
       transformationMusic.loop();
     }
   }else if (val == 4){
     //button pressed for second time
     if (mode == "playing"){
       mode = "start";
       transformationMusic.stop();
       finishMusic.play();
     }
   }
   
   //println(currentRate);
   
}

//for testing :-P
void keyPressed(){
  if (key=='a'){
     if (mode == "playing"){
       mode = "end";
       transformationMusic.stop();
       finishMusic.play();
     }
  }else if (key == 'b'){
     if (mode == "start"){
       mode = "playing";
       transformationMusic.loop();
     }
  }
}