import processing.serial.*;

int NUMBER_OF_SLAVES = 2;
Box []boxes = new Box[NUMBER_OF_SLAVES];
boolean []bLedOn = new boolean[NUMBER_OF_SLAVES];
byte message[] = new byte[NUMBER_OF_SLAVES];

Serial master;

void setup() {
    size(530, 300);

    for (int i=0; i<Serial.list().length; i++) {
        println(Serial.list()[i]);
    }

    String portName = Serial.list()[1];

    master = new Serial(this, portName, 9600);


    // initiate all box enable to off
    for (int i=0; i<boxes.length; i++) {
        boxes[i] = new Box(i*50 + 20, 80, 40, i+1);
    }
}

void draw() {
    background(54);

    // print title
    pushStyle();
    fill(255, 255, 0);
    noStroke();
    text("LED Control prototype Demo", 20, 50);
    popStyle();

    // draw boxes
    for (int i=0; i<boxes.length; i++) {
        boxes[i].draw();
        if(boxes[i].bLedOn)    message[i] = byte(1);
        else                   message[i] = byte(0);
    }
    
    master.write(message);

}

// control clicking box
void mousePressed() {
    for (int i=0; i<boxes.length; i++) {
        boxes[i].isInside(mouseX, mouseY);
    }
}