class Box{
    float x, y;        // position   
    float size;        // size
    boolean bLedOn;    // on/off ?
    int index;         // index number
    
    
    // constructor
    Box(float _x, float _y, float _size, int _index){
        x = _x;
        y = _y;
        size = _size;
        bLedOn = false;
        index = _index;        
    }
    
    void draw(){
        pushMatrix();
        pushStyle();
        translate(x, y);
        noStroke();
        if(bLedOn)    fill(255, 255, 0);
        else          fill(0);
        
        rect(0, 0, size, size);
        
        stroke(255);
        noFill();
        rect(0, 0, size, size);
        
        if(!bLedOn)    fill(255);
        else           fill(0);
        
        noFill();
        //textMode(CENTER);
        textAlign(CENTER);
        text(index, 20, 24); 
        
        popStyle();
        popMatrix();
    }
    
    // toggle on/off
    void controlLed(){
        bLedOn = !bLedOn;
    }
    
    // check whether click inside or not
    void isInside(float _x, float _y){
        if(_x > x && _x < x+size && _y > y && _y < y + size){
            controlLed();
        }
    }
    
    boolean getLedStatus(){
        return bLedOn;
    }
}