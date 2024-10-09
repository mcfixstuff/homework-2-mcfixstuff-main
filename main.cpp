/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * Install Make, GCC, OpenGL and freeglut.                              *
 * To compile your program, run "make" in the          *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp, link   *
 * to your OpenGL libs, build and run the executable   *
 * as you normally would.                              *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0, 0, 4, 1};
int windowWidth = 800, windowHeight = 600;
double xRot = 0;
double yRot = 0;
int curProblem = 3; // TODO: change this number to try different examples

float specular[] = {0.2, 0.2, 0.2, 0.2};
float shininess[] = {1.0};

void problem1()
{
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);  // Scale the entire pyramid down by 50%

    int rows = 6;
    float spacing = 1.8f;
    float teapotSize = 0.5f;

    for (int i = 0; i < rows; i++)
    {
        int teapotsInRow = rows - i;
        float yPos = i * -spacing;

        for (int j = 0; j < teapotsInRow; j++)
        {
            glPushMatrix();
            float xPos = (j - (teapotsInRow - 1) / 2.0f) * spacing;
            glTranslatef(xPos, yPos, 0.0f);
            glColor3f(0.5f, 0.2f, 0.8f);
            glutSolidTeapot(teapotSize);
            glPopMatrix();
        }
    }

    glPopMatrix();
}


void problem2()
{
    int totalPieces = 11;
    float baseWidth = 2.0f;   // Width of the base (largest) rectangular prism
    float baseHeight = 0.2f;  // Height of each prism layer
    float baseDepth = 2.0f;   // Depth of the base rectangular prism
    float yOffset = -2.5f;     // Starting y-offset for the pyramid (stack height)
    
    // Loop through all 11 pieces, creating progressively smaller prisms
    for (int i = 0; i < totalPieces; i++)
    {
        glPushMatrix();  // Save the current transformation matrix

        // Calculate the scaling factors for each rectangular prism
        float scaleFactor = 1.0f - (i * 0.08f);  // Make each level slightly smaller
        float width = baseWidth * scaleFactor;
        float depth = baseDepth * scaleFactor;
        float height = baseHeight;

        // The last (top) piece is a cube
        if (i == totalPieces - 1)
        {
            width = height = depth = baseHeight;  // Make the top piece a cube
        }

        // Position each rectangular prism along the y-axis, stacking them
        glTranslatef(0.0f, yOffset + (height / 2.0f), 0.0f);

        // Draw a rectangular prism by scaling a cube
        glScalef(width, height, depth);
        glColor3f(0.5f, 0.8f - (i * 0.06f), 0.4f + (i * 0.03f));  // Vary color slightly
        glutSolidCube(1.0);  // Use glutSolidCube to draw a cube, which we'll scale into a prism

        glPopMatrix();  // Restore the previous transformation matrix

        // Increment the y-offset for the next prism
        yOffset += height;
    }
}


void problem3()
{
    float teapotSize = 0.2f; 
    float distance = 1.0f;    
    struct TeapotPosition {
        float x, y, z;  
        float rotationY;     
    };

    TeapotPosition teapots[] = {
        {-distance, 0.0f,  distance,  135.0f},  
        {-distance, 0.0f, -distance,  45.0f},   

        {distance, 0.0f,  distance,  -135.0f},  
        {distance, 0.0f, -distance,  -45.0f},   

        {0.0f, 0.0f,  distance,     180.0f}, 
        {0.0f, 0.0f, -distance,      0.0f},    

        {-distance, 0.0f,  0.0f,      90.0f}, 
        {distance, 0.0f,  0.0f,     -90.0f}   
    };

    // loop through each teapot and position it
    for (int i = 0; i < 8; i++)
    {
        glPushMatrix(); 

        glTranslatef(teapots[i].x, teapots[i].y, teapots[i].z);

        glRotatef(teapots[i].rotationY, 0.0f, 1.0f, 0.0f); 
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  

        glColor3f(0.8f, 0.3f, 0.3f); 
        glutSolidTeapot(teapotSize);

        glPopMatrix(); 
    }
}



void problem4()
{
    // TODO: Your code here!
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0); // x axis
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0); // y axis
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1); // z axis
    glEnd(/*GL_LINES*/);
   float light0Diffuse[] = {0.2, 0.2, 0.2, 1.0};  // Lower diffuse light intensity
glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    if (curProblem == 1)
        problem1();
    if (curProblem == 2)
        problem2();
    if (curProblem == 3)
        problem3();
    if (curProblem == 4)
        problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON)
        rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
    if (leftDown)
    {
        xRot += (y - lastPos[1]) * .1;
        yRot += (x - lastPos[0]) * .1;
    }
    if (rightDown)
    {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
    }

    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    curProblem = key - '0';
    if (key == 'q' || key == 'Q' || key == 27)
    {
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("HW2");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}