
#include <GLUT/glut.h>
#include <iostream>
#include <cmath>

using namespace std;
void display(void);
void MyKeyboard(unsigned char,int,int);
void MyMouse(int,int,int,int);
double sub(double, double);

//double org_xs[] = {100,500,300};
//double org_ys[] = {100,100, 300};

double org_xs[] = {-1,-1,-1};
double org_ys[] = {-1,-1,-1};
int zcount = -1;
int org_order=0;
int rot=0;
int delta_x=0;
int delta_y=0;
float scale=1.;


int main(int argc,char** argr)
{
	glutInit(&argc,argr);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
   
	glutInitWindowSize(1000,600);
	glutInitWindowPosition(00,00);
	glutCreateWindow("Mouse and Keyboard");
	glutDisplayFunc(display);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouse);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	gluOrtho2D(0.0,1000.0,0.0,600.0);
	glutMainLoop();
    return 0;
}

double sub(double a, double b)
{
    return fabs(a-b);
}


void drawTriangle(double xs[], double ys[], int order, bool first,
                  bool container)
{
    
    glPushMatrix();

    if (container)
    {
        glTranslatef(delta_x, delta_y, 0.);
        glRotatef(rot, 0, 0, 1.);
        glScalef(scale, scale, scale);
        
        glColor3f(1,0.2,0.2);
        glBegin(GL_TRIANGLES);
        glVertex3f(xs[0], ys[0], 0.0f);
        glVertex3f(xs[1], ys[1], 0.0f);
        glVertex3f(xs[2], ys[2], 0.0f);
        glEnd();
    }
    
    if (!first)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(xs[0], ys[0], 0.0f);
        glVertex3f(xs[1], ys[1], 0.0f);
        glVertex3f(xs[2], ys[2], 0.0f);
        glEnd();
    }
    
    if (order == 0){
        glPopMatrix();
        glFlush();
        return ;
    }
    
    double n_xs[] = {min(xs[2],xs[0])+sub(xs[2],xs[0])/2,
                     min(xs[2],xs[1])+sub(xs[2],xs[1])/2,
                     min(xs[0],xs[1])+sub(xs[0], xs[1])/2};

    double n_ys[] = {min(ys[2],ys[0])+sub(ys[2],ys[0])/2,
                     min(ys[2],ys[1])+sub(ys[2],ys[1])/2,
                     min(ys[0],ys[1])+sub(ys[0],ys[1])/2};
    
    drawTriangle(n_xs, n_ys, 0, false, false);
    

    double n_xs1[] = {min(xs[2],xs[0])+sub(xs[2],xs[0])/2,
                      min(xs[2],xs[1])+sub(xs[2],xs[1])/2,
                      xs[2]};


    double n_ys1[] = {min(ys[2],ys[0])+sub(ys[2],ys[0])/2,
                      min(ys[2],ys[1])+sub(ys[2],ys[1])/2,
                      ys[2]};
    drawTriangle(n_xs1, n_ys1, order-1, true, false);
    
    
    double n_xs2[] = {xs[0],
                      min(xs[0],xs[1])+sub(xs[0], xs[1])/2,
                      min(xs[2],xs[0])+sub(xs[2],xs[0])/2};


    double n_ys2[] = {ys[0],
                     min(ys[0],ys[1])+sub(ys[0],ys[1])/2,
                     min(ys[2],ys[0])+sub(ys[2],ys[0])/2};
    drawTriangle(n_xs2, n_ys2, order-1, true, false);

    
    double n_xs3[] = {min(xs[0],xs[1])+sub(xs[0], xs[1])/2,
                      xs[1],
                      min(xs[2],xs[1])+sub(xs[2],xs[1])/2 };


    double n_ys3[] = {min(ys[0],ys[1])+sub(ys[0],ys[1])/2,
                      ys[1],
                      min(ys[2],ys[1])+sub(ys[2],ys[1])/2};
    drawTriangle(n_xs3, n_ys3, order-1, true, false);
    glPopMatrix();
    
    glFlush();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (org_xs[0] != -1)
        drawTriangle(org_xs, org_ys, org_order, true, true);
    
    
    glEnd();
    glFlush();
}

void MyKeyboard(unsigned char thekey,int mouseX,int mouseY)
{
    if (zcount != -1)
        return;
    
    int temp = thekey - '0';
    if (temp >= 0 && temp < 7)
    {
        org_order = temp;
    }
    
    switch (thekey) {
        case 'u':
            delta_y += 4;
            break;
        case 'd':
            delta_y -= 4;
            break;
        case 'l':
            delta_x -= 4;
            break;
        case 'r':
            delta_x += 4;
            break;
        case 'o':
            rot += 1.;
            rot = (int)rot % 360;
            break;
        case 'O':
            rot -= 1.;
            rot = (int)rot % 360;
            break;
        case 'b':
            scale += 0.1;
            break;
        case 's':
            scale -= 0.1;
            break;
        default:
            break;
    }
    
    glutPostRedisplay();
}

void MyMouse(int button, int state,int x, int y)
{
    if (state == 0)
    {
        zcount++;
        org_xs[zcount]=x;
        org_ys[zcount]=600 - y;
        if (zcount == 2){
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
            zcount = -1;
        }
    }
}
