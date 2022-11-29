#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION

// MUHAMMAD ANDHIKA ADHISATYA
// 5221600011
// ALFIAN MAJIDDAN NUR
// 5221600021

#include "stb_image.h"

static float X = 0.0;
static float Y = 0.0;
static float Z = -9.0;

void loadTextureFromFile(const char *filename, unsigned int texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
					 GL_RGB, GL_UNSIGNED_BYTE, data);
		// glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture - " << filename << std::endl;
	}
	stbi_image_free(data);
}

const char *filename1 = "dar.bmp";
const char *filename2 = "dar.bmp";
unsigned int tob[2];

static void
drawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
		{
			{-1.0, 0.0, 0.0},
			{0.0, 1.0, 0.0},
			{1.0, 0.0, 0.0},
			{0.0, -1.0, 0.0},
			{0.0, 0.0, 1.0},
			{0.0, 0.0, -1.0}};

	static GLint faces[6][4] =
		{
			{0, 1, 2, 3},
			{3, 2, 6, 7},
			{7, 6, 5, 4},
			{4, 5, 1, 0},
			{5, 6, 2, 1},
			{7, 4, 0, 3}};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--)
	{
		glBegin(type);
		glNormal3fv(&n[i][0]);

		glTexCoord2d(0.0, 0.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2d(0.0, 1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2d(1.0, 1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2d(1.0, 0.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void APIENTRY
myglutSolidCube(GLdouble size)
{
	drawBox(size, GL_QUADS);
}

void init()
{								 // for 3d lighting
	glEnable(GL_DEPTH_TEST);	 // depth test
	glEnable(GL_LIGHTING);		 // enable light from a single source
	glEnable(GL_LIGHT0);		 // enable white light , diffuse and specular components
	glEnable(GL_COLOR_MATERIAL); // track the current color
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(X, Y, Z);
	glEnable(GL_TEXTURE_2D);

	///belakang
	glBindTexture(GL_TEXTURE_2D, tob[1]);
	glPushMatrix();
	glColor3f(0.f, 0.f, 0.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1., 0, -2.0);
	glScalef(0.1, 1.5, 1.0);
	myglutSolidCube(4.8);
	glPopMatrix();

	/// kanan
	glBindTexture(GL_TEXTURE_2D, tob[1]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(2.4, 0., -2.0);
	glScalef(0.1, 1.5, 1.0);
	myglutSolidCube(4.8);
	glPopMatrix();

	// tengah
	glBindTexture(GL_TEXTURE_2D, tob[0]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1., 2.8, -2.0);
	glScalef(1.5, 0.1, 1.0);
	myglutSolidCube(2.7);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tob[0]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1., 1.03, -2.0);
	glScalef(1.5, 0.1, 1.0);
	myglutSolidCube(2.7);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tob[0]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1., -1.03, -2.0);
	glScalef(1.5, 0.1, 1.0);
	myglutSolidCube(2.7);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tob[0]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1., -2.8, -2.0);
	glScalef(1.5, 0.1, 1.0);
	myglutSolidCube(2.7);
	glPopMatrix();

	// atas
	glBindTexture(GL_TEXTURE_2D, tob[1]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1.2, 4., -2.0);
	glScalef(2., 0.1, 1.0);
	myglutSolidCube(2.7);
	glPopMatrix();

	// bawah
	glBindTexture(GL_TEXTURE_2D, tob[1]);
	glPushMatrix();
	glColor3f(0.f, 0.f, 0.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1.2, -4., -2.0);
	glScalef(2., 0.1, 1.0);
	myglutSolidCube(2.7);
	glPopMatrix();

	/// kiri
	glBindTexture(GL_TEXTURE_2D, tob[1]);
	glPushMatrix();
	glColor3f(1.f, 1.f, 1.f);
	glRotatef(35, 0, 1, 0);
	glTranslatef(-1.7, 0., -2.0);
	glScalef(0.1, 1.5, 1.0);
	myglutSolidCube(4.8);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		X += 0.5;
		glutPostRedisplay();
		break;
	case 'd':
		X -= 0.5;
		glutPostRedisplay();
		break;
	case 's':
		Y -= 0.5;
		glutPostRedisplay();
		break;
	case 'w':
		Y += 0.5;
		glutPostRedisplay();
		break;
	case 'q':
		Z -= 0.5;
		glutPostRedisplay();
		break;
	case 'e':
		Z += 0.5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lemari.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glGenTextures(3, &tob[0]);
	loadTextureFromFile(filename1, tob[0]);
	loadTextureFromFile(filename2, tob[1]);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}