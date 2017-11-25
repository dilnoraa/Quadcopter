#include<GL/glut.h>

#include <cmath>

static GLfloat spin = 0.0; // pervaneleri etrafýnda dönmesi için kullanýlan sttaik deðiþken
static float h=0; // dörtdönerin ileri yönde hareket etmesi için kullanýlan deðiþken

// iki tane dik kesiþen çizgidir
void cizgiler() {
	glPointSize(5.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, 0.0f);
    glEnd();
 }

// silindirin üstündeki yönü gösteren uçgendir
void ucgen() {

glBegin( GL_TRIANGLES );
glColor3f(0.0,0.8,0.0);
glVertex3f( 4.0, 6.0 ,-5.0);
glVertex3f( -4.0, 6.0,-5.0 );
glVertex3f( -4.0, 2.0,-5.0 );
glEnd();



}

// dörtdönerin ortasýndaki silindir
void silindir() {
	glShadeModel(GL_FLAT);
	GLUquadricObj *qobj = gluNewQuadric();
	glColor3f(0.5,0.0,0.0);
 
   gluDisk(qobj, 0.0, 1.0, 32, 1);
   gluCylinder(qobj, 1.0f, 1.0, 2.0, 32, 1);
   glTranslatef(0.0f, 0.0f, 2.0f);
   gluDisk(qobj, 0.0, 1.0, 32, 1);
   glTranslatef(0.0f, 0.0f, -12.0f);
   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
   gluDeleteQuadric(qobj);
}


   void tekerlek() {
      cizgiler(); // tekerleðin ortasýndaki dik çizgiler toplam 4 tane olduðu için bu prosedür 2 defa çaðýrýlýyor
      glPushMatrix();
      glRotatef(45, 0.0, 0.0, 1.0);
      cizgiler();
      glPopMatrix();
      glColor3f(0.0,0.0,0.8);
      glutSolidTorus(0.6, 2.8, 20, 20); // torus
    }


// silindirýn dairesel kenarý belli etmek için kullanýlan daire
void daire() {
	glColor3f(0.0,0.0,0.0);
	const float pi = 3.14159/180;
 
    glBegin(GL_LINE_LOOP);
    for (int i=0; i< 360; i++)
   {
      float degInRad = i*pi;
      glVertex2f(cos(degInRad)*6,sin(degInRad)*6);
   }
 
   glEnd();
}




  // pervanelerin kendi etrafýnda dönmesidir
     void spinDisplay(void)
    {
      spin = spin + 0.3;
      if (spin > 360.0)
      spin = spin - 360.0;
      glutPostRedisplay();
    }


// parçalarý birleþerek dörtdöner olusturulur
	 // her parça uzayda uygun konumda olmalýdýr
void dortdoner() {
	// 1ci tekerlek
	glPushMatrix();
    glTranslatef(7,10,-15.0);
    glRotatef(90,0,0,1);  // z eksen etrafýnda 90 derece cevrildi
    glRotatef(spin, 0.0, 0.0, 1.0);  // kendi ekseni etrafýnda dönmesi
    tekerlek(); 
    glPopMatrix();


	//2ci tekerlek
    glPushMatrix();
    glTranslatef(7,-10,-15);
    glRotatef(90,0,0,1);
    glRotatef(-spin, 0.0, 0.0, 1.0);
    tekerlek();
    glPopMatrix();

	//3cu tekerlek
    glPushMatrix();
    glTranslatef(-7,10,-15);
    glRotatef(90,0,0,1);
    glRotatef(-spin, 0.0, 0.0, 1.0);
    tekerlek();
    glPopMatrix();

	//4cu tekerlek
    glPushMatrix();
    glTranslatef(-7,-10,-15);
    glRotatef(90,0,0,1);
    glRotatef(spin, 0.0, 0.0, 1.0);
    tekerlek();
    glPopMatrix();


	//çubuk, kübün bir kenarý uzatarak yapýldý
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(0,0,-17.0);
    glRotatef(35, 0.0, 0.0, 1.0);
    glScalef(2.4, 28.8, 1.8);
    glutSolidCube(1.0);
    glPopMatrix();

	//2cý çubuk
    glPushMatrix();
    glTranslatef(0,0,-17);
    glRotatef(-35, 0.0, 0.0, 1.0);
    glScalef(2.4, 28.8, 1.8);
    glutSolidCube(1.0);
    glPopMatrix();


    // uçgen
    glPushMatrix();
    glTranslatef(0,-1,-10);
    glScalef(0.3,0.3,0.3);
    ucgen();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-18);
    glScalef(3.0,3.0,3.0);
    silindir();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-12);
    glScalef(0.5,0.5,1);
    glRotatef(-90,0,0,1);
    daire();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-15);
    glScalef(0.3,0.3,0.3);
    glRotatef(-90,0,0,1);
    daire();
    glPopMatrix();
}



    void Draw() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Ekrani ve bellegi temizler
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // 1ci dördöner
   glPushMatrix();
   glTranslatef(-9,2,0);
   glTranslatef(h,0,0);
   dortdoner();
   glPopMatrix();

   //2ci dörtdöner
    glPushMatrix();
    glTranslatef(-13,5,0);
    glScalef(0.4,0.4,0.4);
    glRotatef(25,0,0,1);
    glTranslatef(h+1,0,0);
    dortdoner();
    glPopMatrix();

	//3cu dörtdöner    
   glPushMatrix();
   glTranslatef(-22,-11,-6);
   glRotatef(45,0,0,1);
   glScalef(0.5,0.5,0.5);
   glTranslatef(h,0,0);
   dortdoner();
   glPopMatrix();

   // 4cu dörtdöner
   glPushMatrix();
   glTranslatef(9,0,0);
   glRotatef(45,0,1,0);
   glScalef(0.5,0.5,0.5);
   glTranslatef(h+1,0,0);
   dortdoner();
   glPopMatrix();

   // 5ci dörtdöner
    glPushMatrix();
    glTranslatef(-5.6,-6,-7);
    glRotatef(-45,1,0,0);
    glScalef(0.2,0.2,0.2);
    glTranslatef(h+2,0,0);
    dortdoner();
    glPopMatrix();


    glutSwapBuffers();
    glFlush();
  }




   void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);


   glLoadIdentity ();
   gluPerspective(120.0, (GLfloat) w/(GLfloat) h, 0.5, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0);
  }

   /// farenin sol tuþa basarak tekerleklerin dönmesi saðlanýr sað tuþu ile dönmeleri durdurulur
  void mouse(int button, int state, int x, int y) 
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN)
    glutIdleFunc(spinDisplay);
    break;
    case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN)
    glutIdleFunc(0);
    break;
    default:
   break;
  }
}



  // klavyeden d harfi basýlý tutup seklin hareket etmesini saðlanýr

    void keyboard (unsigned char key, int x, int y) {
     switch (key) {
     case 'd':
     h = h + 0.1;
     glutPostRedisplay();
     break;
     default:
     break;
    }
  }

   void Initialize()
  {
    glShadeModel(GL_FLAT);
    glClearColor(0.8f, 1.0f, 1.0f, 1.0f); 
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-22.0, 22.0, -22.0, 22.0, -22.0, 22.0); // Koordinat sistemin sýnýrlarý
  }

    int main(int iArgc, char** cppArgv)
	{
    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1300, 1000);
    glutCreateWindow("Quadcopter");
    Initialize();
    glutDisplayFunc(Draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}


















