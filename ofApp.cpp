#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(1);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		this->radius_list[i] += this->speed_list[i];

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for (int i = 0; i < 60; i++) {

		float deg = (360 - (i * 60 % 360)) + (ofGetFrameNum() * 6) + ofRandom(-15, 15);
		float radius = (ofGetFrameNum() * 3 + (i * 100)) % 600 + ofRandom(-10, 10);
		color.setHsb(ofRandom(255), 255, 200);

		auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		this->location_list.push_back(location);
		this->radius_list.push_back(1);
		this->speed_list.push_back(ofRandom(0.5, 3));
		this->max_radius_list.push_back(ofRandom(5, ofMap(radius, 0, 600, 10, 70)));
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofNoFill();
		ofSetColor(this->color_list[i], this->radius_list[i] < this->max_radius_list[i] * 0.75 ? 255 : ofMap(this->radius_list[i], this->max_radius_list[i] * 0.75, this->max_radius_list[i], 255, 0));
		ofDrawCircle(this->location_list[i], this->radius_list[i]);

		ofFill();
		ofSetColor(this->color_list[i], ofMap(this->radius_list[i], 1, this->max_radius_list[i], 255, 30));
		ofDrawCircle(this->location_list[i], this->radius_list[i]);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}