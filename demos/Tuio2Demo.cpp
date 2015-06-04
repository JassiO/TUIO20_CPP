/*
 TUIO C++ GUI Demo
 Copyright (c) 2009-2014 Martin Kaltenbrunner <martin@tuio.org>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Tuio2Demo.h"

void Tuio2Demo::tuioAdd(TuioObject *tobj) {
	/*if (verbose)
		std::cout << "add obj " << ttok->getSymbolID() << " (" << ttok->getSessionID() << ") "<< ttok->getX() << " " << ttok->getY() << " " << ttok->getAngle() << std::endl;*/
}

void Tuio2Demo::tuioUpdate(TuioObject *tobj) {

	/*if (verbose)
		std::cout << "set obj " << ttok->getSymbolID() << " (" << ttok->getSessionID() << ") "<< ttok->getX() << " " << ttok->getY() << " " << ttok->getAngle()
		<< " " << ttok->getMotionSpeed() << " " << ttok->getRotationSpeed() << " " << ttok->getMotionAccel() << " " << ttok->getRotationAccel() << std::endl;*/
}

void Tuio2Demo::tuioRemove(TuioObject *tobj) {
	
	/*if (verbose)
		std::cout << "del obj " << ttok->getSymbolID() << " (" << ttok->getSessionID() << ")" << std::endl;*/
}

void Tuio2Demo::tuioRefresh(TuioTime frameTime) {
	//drawObjects();
}

void Tuio2Demo::drawObjects() {
	glClear(GL_COLOR_BUFFER_BIT);
	char id[3];
	
	// draw the pointers
	std::list<TuioPointer*> pointerList = tuioClient->getTuioPointerList();
    tuioClient->lockObjectList();
	for (std::list<TuioPointer*>::iterator iter = pointerList.begin(); iter!=pointerList.end(); iter++) {
		TuioPointer *tptr = (*iter);
        if (tptr==NULL) continue;
 		std::list<TuioPoint> path = tptr->getPath();
		if (path.size()>0) {
			
			TuioPoint last_point = path.front();
			glBegin(GL_LINES);
			glColor3f(0.0, 0.0, 1.0);
			/*
			for (std::list<TuioPoint>::iterator point = path.begin(); point!=path.end(); point++) {
				glVertex3f(last_point.getScreenX(width), last_point.getScreenY(height), 0.0f);
				glVertex3f(point->getScreenX(width), point->getScreenY(height), 0.0f);
				last_point.update(point->getX(),point->getY());
			} glEnd();
			*/
			//std::cout << "X, Y: \t" << tptr->getX() << ", " << tptr->getY() << std::endl;
			/*
			// draw the finger tip
			glColor3f(0.75, 0.75, 0.75);
			glPushMatrix();
			glTranslatef(last_point.getScreenX(width), last_point.getScreenY(height), 0.0);
			glBegin(GL_TRIANGLE_FAN);
			for(double a = 0.0f; a <= 2*M_PI; a += 0.2f) {
				glVertex2d(cos(a) * height/100.0f, sin(a) * height/100.0f);
			} glEnd();
			glPopMatrix();
			
			glColor3f(0.0, 0.0, 0.0);
			glRasterPos2f(tptr->getScreenX(width),tptr->getScreenY(height));
			sprintf(id,"%d",tptr->getPointerID());
			drawString(id);*/
		}
	}
    tuioClient->unlockObjectList();
	
	// draw the objects
	std::list<TuioToken*> objectList = tuioClient->getTuioTokenList();
    tuioClient->lockObjectList();
	for (std::list<TuioToken*>::iterator iter = objectList.begin(); iter!=objectList.end(); iter++) {
		TuioToken *ttok = (*iter);
		int pos_size = height/25.0f;
		int neg_size = -1*pos_size;
		float xpos  = ttok->getScreenX(width);
		float ypos  = ttok->getScreenY(height);
		float angle = ttok->getAngleDegrees();
		
		glColor3f(0.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(xpos, ypos, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2f(neg_size, neg_size);
		glVertex2f(neg_size, pos_size);
		glVertex2f(pos_size, pos_size);
		glVertex2f(pos_size, neg_size);
		glEnd();
		glPopMatrix();
		
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(xpos,ypos+5);
		sprintf(id,"%d",ttok->getSymbolID());
		drawString(id);
	}
    tuioClient->unlockObjectList();
	
	// draw the blobs
	std::list<TuioBounds*> blobList = tuioClient->getTuioBoundsList();
    tuioClient->lockObjectList();
	for (std::list<TuioBounds*>::iterator iter = blobList.begin(); iter!=blobList.end(); iter++) {
		TuioBounds *tbnd = (*iter);
		float blob_width = tbnd->getScreenWidth(width);
		float blob_height = tbnd->getScreenHeight(height);
		float xpos  = tbnd->getScreenX(width);
		float ypos  = tbnd->getScreenY(height);
		float angle = tbnd->getAngleDegrees();
		std::cout << xpos << ", " << ypos << std::endl;
		
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(xpos, ypos, 0.0);
		glRotatef(-angle, 0.0, 0.0, 1.0);
		std::cout << xpos << ", " << ypos << std::endl;
		/*glBegin(GL_QUADS);
		 glVertex2f(blob_width/-2, blob_height/-2);
		 glVertex2f(blob_width/-2, blob_height/2);
		 glVertex2f(blob_width/2, blob_height/2);
		 glVertex2f(blob_width/2, blob_height/-2);
		 glEnd();*/
		
		glBegin(GL_TRIANGLE_FAN);
		for(double a = 0.0f; a <= 2*M_PI; a += 0.2f) {
			glVertex2d(cos(a) * blob_width *2, sin(a) * blob_height*2);
		} glEnd();
		
		glPopMatrix();
		
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(xpos,ypos);
		drawString(id);
		//std::cout << xpos << ", " << ypos << std::endl;
	}
    tuioClient->unlockObjectList();

	SDL_GL_SwapBuffers();
}

void Tuio2Demo::drawString(char *str) {
	if (str && strlen(str)) {
		while (*str) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *str);
			str++;
		}
	}
}

void Tuio2Demo::initWindow(bool flipped) {
	
	int videoFlags = SDL_OPENGL | SDL_DOUBLEBUF;
	if( fullscreen ) {
		videoFlags |= SDL_FULLSCREEN;
		width = screen_width;
		height = screen_height;
	} else {
		width = window_width;
		height = window_height;
	}
	
	window = SDL_SetVideoMode(width, height, 32, videoFlags);
	if ( window == NULL ) {
		std::cerr << "Could not open window: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	int flip = -1;
	if( flipped == true ) {
		flip = -1;
	}
	else {
		flip = 1;
	}
	
	SDL_ShowCursor(!fullscreen);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	glScalef(1, flip, 1);
	gluOrtho2D(0, (GLfloat)width, (GLfloat)height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Tuio2Demo::processEvents()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE ){
					running = false;
					SDL_ShowCursor(true);
					SDL_Quit(); } 
				else if( event.key.keysym.sym == SDLK_F1 ){
					fullscreen = !fullscreen;
					initWindow(flipped); }
				else if( event.key.keysym.sym == SDLK_v ){
					verbose = !verbose;	} 
				
				break;
			case SDL_QUIT:
				running = false;
				SDL_ShowCursor(true);
				SDL_Quit();
        }
    }
}

Tuio2Demo::Tuio2Demo(int port) 
: verbose (false)
, flipped(true)
, fullscreen(true)
, screen_width (1920)
, screen_height (1080)
, window_width (1920)
, window_height (1080)
{
	osc_receiver = new UdpReceiver(port);
//	osc_receiver = new TcpReceiver("127.0.0.1",3333);
	tuioClient = new TuioClient(osc_receiver);
	tuioClient->addTuioListener(this);
	tuioClient->connect();
	
	if (!tuioClient->isConnected()) {
		SDL_Quit();
	}
	
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		std::cerr << "SDL could not be initialized: " <<  SDL_GetError() << std::endl;
		SDL_Quit();
	}
	
	screen_width = SDL_GetVideoInfo()->current_w;
	screen_height = SDL_GetVideoInfo()->current_h;
	
	SDL_WM_SetCaption("Tuio2Demo", NULL);
	initWindow(flipped);
}

void Tuio2Demo::run() {
    running=true;
    //drawObjects();
	while (running) {
		drawObjects();
		processEvents();
		SDL_Delay(10);
	}
}

int main(int argc, char* argv[])
{

#ifndef __MACOSX__
	glutInit(&argc,argv);
#else
	if ((argc>1) && ((std::string(argv[1]).find("-NSDocumentRevisionsDebugMode")==0 ) || (std::string(argv[1]).find("-psn_")==0))) argc = 1;
#endif

	if( argc >= 2 && strcmp( argv[1], "-h" ) == 0 ){
		std::cout << "usage: Tuio2Demo [port]\n";
		return 0;
	}

	unsigned short port = 3333;
	if( argc >= 2 ) port = atoi( argv[1] );

	Tuio2Demo *app = new Tuio2Demo(port);
	app->run();
	delete app;

	return 0;
}


