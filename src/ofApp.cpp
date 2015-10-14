#include "ofApp.h"

//4464
//6480

//--------------------------------------------------------------
void ofApp::setup(){
    w = 8000;
    h = 2000;
    
    ofSetWindowShape(w, h);
    
    ofFbo::Settings s;
    
    s.width = w;
    s.height = h;
    s.internalformat = GL_RGB;
    s.numColorbuffers = 1;
    s.numSamples = 1;
    s.useDepth = false;
    s.useStencil = false;
    s.depthStencilAsTexture = false;

    compositionFbo.allocate(s);
    
    string path0 = "images/stylemess";
    /*
    string path1 = "images/style1";
    string path2 = "images/style2";
    string path3 = "images/style3";
    string path4 = "images/style4";
    string path5 = "images/style5";
   */
    ofDirectory dir0(path0);
    dir0.listDir();
    
    /*
    ofDirectory dir1(path1);
    dir1.listDir();
    
    ofDirectory dir2(path2);
    dir2.listDir();
    
    ofDirectory dir3(path3);
    dir3.listDir();
    
    ofDirectory dir4(path4);
    dir4.listDir();
    
    ofDirectory dir5(path5);
    dir5.listDir();
    */

    for(int i = 0; i<dir0.numFiles(); i++){
        filenames.push_back(dir0.getPath(i));
    }
    
    /*
    for(int i = 0; i<dir1.numFiles(); i++){
        filenames.push_back(dir1.getPath(i));
    }
    
    for(int i = 0; i<dir2.numFiles(); i++){
        filenames.push_back(dir2.getPath(i));
    }
    
    for(int i = 0; i<dir3.numFiles(); i++){
        filenames.push_back(dir3.getPath(i));
    }
    
    for(int i = 0; i<dir4.numFiles(); i++){
        filenames.push_back(dir4.getPath(i));
    }
    
    for(int i = 0; i<dir5.numFiles(); i++){
        filenames.push_back(dir5.getPath(i));
    }
    */
    std::random_shuffle(filenames.begin(), filenames.end());
    cout<<ofToString(filenames.size())<<endl;
    
    index = 0;
    
    compositionFbo.begin();
        ofClear(255);
    compositionFbo.end();
    
    widthStep = 0;
    heightStep = 0;
    newHeightStep = 0;
    
    didHeightIncrease = false;
    

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    prevHeight = curImg.height;
    
    curImg.loadImage(filenames[index]);
    
    heightStep = max(heightStep, max(prevHeight, curImg.height));
    
    if(ofGetKeyPressed('s')){
        ofPixels savePix;
        
        compositionFbo.readToPixels(savePix);
        ofSaveImage(savePix, "savedImages/part1___"+ofGetTimestampString()+".png");
    }
    
    cout<<ofToString(index)<<endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPixels pixels;
    pixels = curImg.getPixelsRef();
    
    for(int y = 0; y<curImg.height; y++){
        for(int x = 0; x<curImg.width; x++){
            int loc = (y *curImg.width + x )*4;
            
            int red = pixels[loc];
            int green = pixels[loc+1];
            int blue = pixels[loc+2];
            int alpha = pixels[loc+3];
            
            //int avg = floor((red+green+blue)/3.0);
            
            if(red == 255 && green == 255 && blue == 255){
            pixels[loc+3] = 0;
            }
            //alpha = 0;
            
        }
    }
    
    curImg.setFromPixels(pixels);
    
    compositionFbo.begin();

        if(curImg.isAllocated()){
            curImg.draw(widthStep, newHeightStep);
        }
    compositionFbo.end();
    
    //widthStep = (widthStep + curImg.width) % w;
    
    widthStep += curImg.width;
    
    if(widthStep + curImg.width > w){
        widthStep = int(ofRandom(200));
        
        //make sure it never gets too big on the weirdos
        if(heightStep>300){
            heightStep = ofRandom(30,70);
        }
        newHeightStep += floor(heightStep/1.4);
        heightStep = 0;
        
        if(newHeightStep+floor(heightStep/1.4)+200>h){
            
            newHeightStep = 0;
            
            ofPixels savePix;
            compositionFbo.readToPixels(savePix);
            ofSaveImage(savePix, "savedImages/"+ofGetTimestampString()+".png");
            
            compositionFbo.begin();
                ofClear(255);
            compositionFbo.end();
        }
        
    }
    
    compositionFbo.draw(0,0);
    
    index = (index + 1) % filenames.size();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
