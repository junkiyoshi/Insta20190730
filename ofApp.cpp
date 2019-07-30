#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto R = 300;
	auto v_span = 20;
	auto u_span = 20;
	for (auto v = 0; v < 360; v += v_span) {

		auto noise_point = glm::vec2(R * cos(v * DEG_TO_RAD), R * sin(v * DEG_TO_RAD));
		for (auto r = 30; r < 100; r += 30) {

			auto u_start = ofMap(ofNoise(noise_point.x * 0.005, noise_point.y * 0.005, (ofGetFrameNum() + r) * 0.005), 0, 1, -180, 180);
			for (auto u = u_start; u < u_start + 180; u += u_span) {

				ofSetColor(39);
				ofFill();

				ofBeginShape();
				ofVertex(this->make_point(R, r, u - v_span * 0.5 - 0.2, v - u_span * 0.3 - 0.1));
				ofVertex(this->make_point(R, r, u + v_span * 0.5 - 0.2, v - u_span * 0.3 - 0.1));
				ofVertex(this->make_point(R, r, u + v_span * 0.5 - 0.2, v + u_span * 0.3 - 0.1));
				ofVertex(this->make_point(R, r, u - v_span * 0.5 - 0.2, v + u_span * 0.3 - 0.1));
				ofEndShape(true);

				ofSetColor(239);
				ofNoFill();

				ofBeginShape();
				ofVertex(this->make_point(R, r, u - v_span * 0.5 + 0.2, v - u_span * 0.3 + 0.1));
				ofVertex(this->make_point(R, r, u + v_span * 0.5 + 0.2, v - u_span * 0.3 + 0.1));
				ofVertex(this->make_point(R, r, u + v_span * 0.5 + 0.2, v + u_span * 0.3 + 0.1));
				ofVertex(this->make_point(R, r, u - v_span * 0.5 + 0.2, v + u_span * 0.3 + 0.1));
				ofEndShape(true);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}