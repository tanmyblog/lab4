#include <GL\glew.h>
#include <GL\freeglut.h>
#include <math.h>

/* cac huong di chuyen */
const char MOVE_LEFT = 0;
const char MOVE_RIGHT = 1;
const char MOVE_UP = 3;
const char MOVE_DOWN = 4;

/* goc xoay tuong ung khi su dung cac phim  */
const int TURN_LEFT = -90;
const int TURN_RIGHT = 90;
const int TURN_UP = 180;
const int TURN_DOWN = 0;

const int GROUND_SIZE = 200; // kich thuoc cua mat san
const float FLOOR_HEIGHT = -2; // do cao cua mat san
const int CHECK_SIZE = 5;	// kich thuoc moi o

int moveDireaction; // huong di chuyen
float moveX; // vt huong di chuyen theo truc x
float moveZ; // vt huong di chuyen theo truc z

float theta; // goc xoay theo camera (tinh toa do x y)
float y; // toa do y cua camera
float dTheta; // Muc tang/giam theta khi dieu khien
float dy; // muc tang/giam y khi dieu khien

void DrawGround();
void SettingCamera(float theta, float y);
void Keyboard(unsigned char key, int, int);
void Special(int key, int, int);

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
	glNormal3d(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	/* ve mat truoc */
	glNormal3d(0, 0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	/* ve mat phai */
	glNormal3d(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	/* ve mat trai */
	glNormal3d(-1, 0, 0);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
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

void DrawGround()
{
	int x, z;
	int couter = 0;
	for (x = -GROUND_SIZE; x < GROUND_SIZE; x += CHECK_SIZE)
	{
		for (z = -GROUND_SIZE; z < GROUND_SIZE; z += CHECK_SIZE)
		{
			if (couter % 2 == 0)
				glColor3d(0.2, 0.2, 1.0); // to mau xanh
			else
				glColor3f(1.0, 1.0, 1.0); // to mau trang
			glBegin(GL_QUADS);
			glNormal3d(0, 1, 0);
			glVertex3f(x, FLOOR_HEIGHT, z);
			glVertex3f(x, FLOOR_HEIGHT, z + CHECK_SIZE);
			glVertex3f(x + CHECK_SIZE, FLOOR_HEIGHT, z + CHECK_SIZE);
			glVertex3f(x + CHECK_SIZE, FLOOR_HEIGHT, z);
			glEnd();
			couter++;
		}
		couter++;
	}
}

void SettingCamera(float theta, float y)
{
	gluLookAt(50 * sin(theta), y, 50 * cos(theta),
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'a': theta -= dTheta; break;
		case 'd': theta += dTheta; break;
		case 'w': y += dy; break;
		case 's': if (y > dy) y -= dy; break;
	}
}

void Special(int key, int, int)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
			moveDireaction = MOVE_LEFT;
			angle = TURN_LEFT;
			break;
		case GLUT_KEY_RIGHT:
			moveDireaction = MOVE_RIGHT;
			angle = TURN_RIGHT;
			break;
		case GLUT_KEY_UP:
			moveDireaction = MOVE_UP;
			angle = TURN_UP;
			break;
		case GLUT_KEY_DOWN:
			moveDireaction = MOVE_DOWN;
			angle = TURN_DOWN;
			break;
	}
	glutPostRedisplay();
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
	switch (moveDireaction)
	{
		case MOVE_LEFT: 
			moveX -= 0.015f; break;
		case MOVE_RIGHT:
			moveX += 0.015f; break;
		case MOVE_UP:
			moveZ -= 0.015f; break;
		case MOVE_DOWN:
			moveZ += 0.015f; break;
	}
}

void Display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	SettingCamera(theta, y);

	glPushMatrix();
		glTranslatef(moveX, 8.0f, moveZ);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		Prepare();
		DrawRobot(0.0f, 0.0f, 0.0f);  // ve robot
	glPopMatrix();

	glPushMatrix();
		DrawGround();
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

	moveDireaction = MOVE_LEFT;
	angle = TURN_LEFT;
	moveX = 0.0f;
	moveZ = 0.0f;

	/* gan gia tri mac dinh ban dau cho camera */
	theta = 0.0f;
	y = 5.0;
	dTheta = 0.04f;
	dy = 1.0f;
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
	glutSpecialFunc(Special);
	glutKeyboardFunc(Keyboard);

	Init();
	glutMainLoop();
	return 0;
}