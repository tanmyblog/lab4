#include <GL\glew.h>
#include <GL\freeglut.h>
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

char LEFT = 0;
char RIGHT = 1;

/* trang thai di chuyen cua tay chan */
char legStates[2];
char armStates[2];

/* goc xoay hien tai cua tay chan */
float legAngles[2];
float armAngles[2];

/* goc xoay hien tai cua toan bo robot */
float angle;

void DrawCube(float xPos, float yPos, float zPos);
void DrawArm(float xPos, float yPos, float zPos);
void DrawHead(float xPos, float yPos, float zPos);
void DrawTorso(float xPos, float yPos, float zPos);
void DrawLeg(float xPos, float yPos, float zPos);
void DrawRobot(float xPos, float yPos, float zPos);
void Prepare();
void Display();
void Init();
void Rashape(int width, int height);
void Idle();

void DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();	// luu trang thai hien tai vao stack;
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_QUADS);
			/* ve mat tren */
			glNormal3d(0,1,0);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f,0.0f,-1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			/* ve mat truoc */
			glNormal3d(0, 0, 1);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f,0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			/* ve mat phai */
			glNormal3d(1, 0, 0);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f,-1.0f);
			/* ve mat trai */
			glNormal3d(-1, 0, 0);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f,-1.0f, 0.0f);
			/* ve mat duoi */
			glNormal3d(0, -1, 0);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			/* ve mat sau */
			glNormal3d(0, 0, -1);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);

		glEnd();
	glPopMatrix();
}

/* ve canh tay trai */
void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f); // to mau do
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/* ve dau */
void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f); // mau trang
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/* ve than*/
void DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f); //to mau xanh
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/* ve chan */
void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f); //to mau vang
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 5.0f, 1.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawRobot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		/* ve dau va than */
		DrawHead(1.0f, 2.0f, 0.0f);
		DrawTorso(1.5f, 0.0f, 0.0f);
		/* di chuyen canh tay trai va xoay canh tay trai */
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
			DrawArm(2.5f, 0.0f, -0.5f);
		glPopMatrix();
		/* di chuyen canh tay phai va xoay canh tay phai*/
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			DrawArm(-1.5f, 0.0f, -0.5f);
		glPopMatrix();
		/* di chuyen chan trai va xoay chan trai */
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
			DrawLeg(-0.5f, -5.0f, -0.5f);
		glPopMatrix();
		/* di chuyen chan phai va xoay chan phai */
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			DrawLeg(1.5f, -5.0f, -0.5f);
		glPopMatrix();

	glPopMatrix();
}

void Prepare()
{
	for (char side = 0; side < 2; side++)
	{
		/* goc xoay cho tay */
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += 0.1f;
		else
			armAngles[side] -= 0.1f;
		/* thay doi trang thai goc xoay vuot qua goa tri cho phep */
		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = FORWARD_STATE;
		/* goc xoay cho chan */
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 0.1f;
		else
			legAngles[side] -= 0.1f;
		/* thay doi trang thai neo goc xoay vuot qua gia tri cho phep */
		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = FORWARD_STATE;
	}
}

void Display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	angle += 0.05f; // tang goc xoay cua robot
	if (angle >= 360.0f)
		angle = 0.0f;
	glPushMatrix();
		/* xoay robot quanh truc */
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		Prepare();
		DrawRobot(0.0f, 0.0f, 0.0f);  // ve robot
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* mau anh sang ambien */
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	/* mau anh sang diffuse */
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/* bi tri nguon sang */
	GLfloat lightPos[] = { 25.0f, 25.0f, 25.0f, 0.0f };
	/* huong chieu sang */
	GLfloat spotDir[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* gan gia tri mac dinh cho robot */
	angle = 0.0f;
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;
	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;
	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;
}

void Rashape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Idle()
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robot 1");
	glutDisplayFunc(Display);
	glutReshapeFunc(Rashape);
	glutIdleFunc(Idle);

	Init();
	glutMainLoop();
	return 0;
}