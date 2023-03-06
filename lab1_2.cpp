#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include "windows.h"
#include <math.h>


float vert[] = { 1,1,0, 1,-1,0, -1,-1,0, -1,1,0 };
float xAlfa = 20;
float zAlfa = 0;
float alpha = 0;
POINTFLOAT pos = { 0,0 };
float pyramid[] = { 0,0,2,1,1,0,1,-1,0,-1,-1,0,-1,1,0,1,1,0 };

void LightShow(float &kaka) {
    glNormal3f(0, 0, 1);
    glPushMatrix();
    float positionl[] = { 0,0,10,0 };
    glRotatef(kaka, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, positionl);

    glTranslatef(0, 0, 10);
    glScalef(0.5, 0.5, 0.5);
    glColor3f(1, 1, 0);
    float x, y;
    float cnt = 40;
    float l = 3;
    float a = M_PI * 2 / cnt;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for (int i = -1; i < cnt; i++)
    {
        x = sin(a * i) * l;
        y = cos(a * i) * l;
        glVertex3f(x, y, 0);
    }
    glEnd();
    glPopMatrix();
}
void SphereShow() {
    
    
    float x, y;
    float cnt = 40;
    float l = 3;
    float a = M_PI * 2 / cnt;
    for (int j = -1; j < 20; j++) {
        glRotatef(alpha, 1, 1, 1);
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        for (int i = -1; i < cnt; i++)
        {
            x = sin(a * i) * l;
            y = cos(a * i) * l;
            glVertex3f(x, y, 0);
        }
        glEnd();
        alpha += 0.01;
    }
}

void CubShow() {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, -1, -1);      
    glVertex3f(1, 1, -1);      
    glVertex3f(-1, 1, -1); 
    glVertex3f(-1, -1, -1);    
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glEnd();
}
void ShowWorld() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert);
    for (int i = -5; i < 5; i++) {
    for (int j = -5; j < 5; j++) {
        glPushMatrix();
        if ((i + j) % 2 == 0) glColor3f(0, 0.5, 0);
        else glColor3f(1, 1, 1);
        glTranslatef(i * 2, j * 2, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glPopMatrix();
    }
    }

    glVertexPointer(3, GL_FLOAT, 0, &pyramid);
    glColor3f(1, 0, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    glPushMatrix();
    glTranslatef(3, 3, 0);
    CubShow();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, -3, 3);
    SphereShow();
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
}

void MoveCamera()
{
    if (GetKeyState(VK_UP) < 0) xAlfa = ++xAlfa > 180 ? 180 : xAlfa;
    if (GetKeyState(VK_DOWN) < 0) xAlfa = --xAlfa > 180 ? 180 : xAlfa;
    if (GetKeyState(VK_LEFT) < 0) zAlfa = ++zAlfa > 180 ? 180 : zAlfa;
    if (GetKeyState(VK_RIGHT) < 0) zAlfa = --zAlfa > 180 ? 180 : zAlfa;

    float ugol = -zAlfa / 180 * M_PI;
    float speed = 0;
    if (GetKeyState('W') < 0) speed = 0.1;
    if (GetKeyState('S') < 0) speed = -0.1;
    if (GetKeyState('A') < 0) {
        speed = 0.1; ugol -= M_PI * 0.5;
    }
    if (GetKeyState('D') < 0) {
        speed = 0.1; ugol += M_PI * 0.5;
    }
    if (speed != 0) {
        pos.x += sin(ugol) * speed;
        pos.y += cos(ugol) * speed;
    }
    glRotatef(-zAlfa, 0, 1, 0);
    glRotatef(-xAlfa, 1, 0, 0);
    glTranslatef(-pos.x, -pos.y, -3);
}
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mod e window and its OpenGL context */
    window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 80);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    float kaka = 0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
       
        /* Render here */
        glClearColor(0, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        MoveCamera();
        LightShow(kaka);
        ShowWorld();
        glPopMatrix();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        kaka += 0.5;
    }

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
