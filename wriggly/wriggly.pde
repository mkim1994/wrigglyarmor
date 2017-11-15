import processing.serial.*;
import processing.sound.*;
import java.io.File; 

Serial myPort;  // Create object from Serial class

int val;

SoundFile music;
SoundFile endMusic;

boolean isEnd;

void setup(){
  music = new SoundFile(this, "rio8 - Totorie Tower OST - 10 P and J's Spicy Cafe.mp3");
  endMusic = new SoundFile(this, "The Legend Of Korra_182218852_soundcloud.mp3");
  
  size(200,200);
  
  println(Serial.list()[2]);
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
  
  val = 0;
  
  music.play();
  
  isEnd = false;
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
   }else if (val == 3){
     //button pressed
     if (!isEnd){
       isEnd = true;
       music.stop();
       endMusic.play();
     }
   }
   
}

//for testing :-P
void keyPressed(){
  if (key=='a'){
    if (!isEnd){
      isEnd = true;
      music.stop();
      endMusic.play();
    }
  }
}