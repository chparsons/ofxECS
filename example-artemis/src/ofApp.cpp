#include "ofApp.h"

void ofApp::setup()
{

  sm = world.getSystemManager();
  em = world.getEntityManager();

  movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());

  sm->initializeAll();

  artemis::Entity & player = em->create();
  player.addComponent(new VelocityComponent(2,4));
  player.addComponent(new PositionComponent(0,0));
  player.refresh();

  playerpos = (PositionComponent*)player.getComponent<PositionComponent>();

}

void ofApp::exit()
{}

void ofApp::update()
{

  world.loopStart();
  world.setDelta(0.0016f);

  movementsys->process();

  std::cout << "X:"<< playerpos->posX << std::endl;
  std::cout << "Y:"<< playerpos->posY << std::endl;

}

//--------------------------------------------------------------
void ofApp::draw(){

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
