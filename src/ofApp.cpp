#include "ofApp.h"

void ofApp::GenerateStaticBodies() {
  for (int i = 0; i < kBodyCount; i++) {
    bodies.push_back(Body(Vector(ofRandom(-ofGetWidth(), ofGetWidth()),
                                 ofRandom(-ofGetWidth(), ofGetWidth()),
                                 ofRandom(-ofGetWidth(), ofGetWidth())),
                          Vector(0, 0, 0), ofRandom(kMinMass, kMaxMass),
                          ofRandom(kMinRadius, kMaxRadius)));
  }
}

void ofApp::GenerateKineticBodies() {
  for (int i = 0; i < kBodyCount; i++) {
    bodies.push_back(Body(Vector(ofRandom(-ofGetWidth(), ofGetWidth()),
                                 ofRandom(-ofGetWidth(), ofGetWidth()),
                                 ofRandom(-ofGetWidth(), ofGetWidth())),
                          Vector(ofRandom(kMinVelocity, kMaxVelocity),
                                 ofRandom(kMinVelocity, kMaxVelocity),
                                 ofRandom(kMinVelocity, kMaxVelocity)),
                          ofRandom(kMinMass, kMaxMass),
                          ofRandom(kMinRadius, kMaxRadius)));
  }
}

void ofApp::ResetSimulation() {
  bodies.clear();
  time_passed_ = 0;
}

void ofApp::setup() {
  ofBackground(0, 0, 0);
  GenerateStaticBodies();
  time_passed_ = 0;

  ofDisableArbTex();
  fbo_.allocate(ofGetWidth(), ofGetHeight());
  ofEnableArbTex();
  bloom_ = std::make_shared<ofxBloom>(ofGetWidth(), ofGetHeight(), &fbo_);
}

void ofApp::update() {
  BHTree* bhtree = new BHTree(q);
  for (int i = 0; i < bodies.size(); ++i) {
      if (q->contains(bodies[i].position_))
          bhtree->insert(&bodies[i]);
  }

  for (int i = 0; i < bodies.size(); ++i) {
      bodies[i].ResetForce();
      if (q->contains(bodies[i].position_))
        bhtree->updateForce(&bodies[i]);
  }

  for (int i = 0; i < bodies.size(); ++i) {
    bodies[i].UpdatePosition(time_step_);
  }
  time_passed_ += time_step_;
}

void ofApp::draw() {
  fbo_.begin();
  ofClear(0);
  camera_.begin();

  for (Body b : bodies) {
    b.Draw();
  }

  camera_.end();

  fbo_.end();

  bloom_->setBrightness(5.5);
  bloom_->setScale(1.5);
  bloom_->setThreshold(.25);
  bloom_->process();
  bloom_->draw();

  ofSetColor(255, 255);

  ofDrawBitmapString("1 - Generate static bodies", 100, 70);
  ofDrawBitmapString("2 - Generate kinetic bodies", 100, 85);
  ofDrawBitmapString("Left/Right for speed modification", 100, 100);

  string frame_rate = "Frame rate: " + ofToString(ofGetFrameRate(), 2);
  ofDrawBitmapString(frame_rate, 100, 135);

  string years = "Years passed: " + ofToString((time_passed_));
  ofDrawBitmapString(years, 100, 150);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  switch (key) {
    case OF_KEY_RIGHT:
      time_step_ *= 2;
      break;
    case OF_KEY_LEFT:
      time_step_ /= 2;
      break;
    case '1':
      ResetSimulation();
      GenerateStaticBodies();
      break;
    case '2':
      ResetSimulation();
      GenerateKineticBodies();
      break;
  }
}
