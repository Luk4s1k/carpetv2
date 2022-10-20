#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <string>
#include <math.h>
bool colorized = true;
float distortionLevel = 0.8;
int iterations = 4;
int height = 900;
int width = 900;

float randomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
// Jezeli jest ustawiona flaga na kolorowanie kwadraty beda losowego koloru
void setColor()
{
    int red =255;
    int green = 255;
    int blue = 255;
    if(colorized)
    {
        red = rand()%256;
        green = rand()%256;
        blue = rand()%256;
    }
    glColor3ub(red, green, blue);
}

// Modyfikuje podane koordynaty x oraz y zeby zdeformowac kwadrat
void setDistortion(GLfloat &x, GLfloat &y, GLfloat width)
{
    x += randomFloat(-width * distortionLevel, width * distortionLevel);
    y += randomFloat(-width * distortionLevel, width * distortionLevel);
}

void draw(GLfloat x, GLfloat y, GLfloat width)
{

    if(distortionLevel > 0.0){
        setDistortion(x,y, width);
    }
    glBegin(GL_POLYGON);
    setColor();
    glVertex2f(x + width, y + width);
    setColor();
    glVertex2f(x + width, y - width);
    setColor();
    glVertex2f(x - width, y - width);
    setColor();
    glVertex2f(x - width, y + width);
    glEnd();
}

GLfloat modifyXCoord( int j,GLfloat x,GLfloat width)
{
    switch (j) {
        case 0: x = x - 2*(width); return x;
        case 1: return x;break;
        case 2: x = x + 2*(width); return x;
    }
}

GLfloat modifyYCoord(int i,GLfloat y,GLfloat width)
{
    switch (i) {
        case 0: y = y - 2*(width); return y;
        case 1: return y;
        case 2: y = y + 2*(width); return y;
    }
}

void sierpinskiCarpet(GLfloat x, GLfloat y, GLfloat width, int currentIter, int iterations)
{

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            GLfloat newX = modifyXCoord(j,x,width);
            GLfloat newY = modifyYCoord(i,y,width);
            if(i == 1 && j == 1 ) continue;
            if(iterations == currentIter)
            {
                draw(newX,newY,width);
                glFlush();
                glutPostRedisplay();
            }
            else
            {
                sierpinskiCarpet(newX,newY,width/3,currentIter+1,iterations);
            }
        }
    }


}

void RenderScene(void){
    glClear( GL_COLOR_BUFFER_BIT);
    sierpinskiCarpet(0, 0, 0.333333, 1,iterations);
    return;
}

int main(int argc, char **argv) {

//    for (int i = 1; i < argc; ++i)
//    {
//        std::string flag = argv[i];
//
//        if (flag == "--colorization")
//        {
//            colorized = true;
//            continue;
//        }
//
//        if (flag == "--winH")
//        {
//            height = std::stoi(argv[i]);
//        }
//
//        if (flag == "--winW")
//        {
//            width = std::stoi(argv[i]);
//        }
//        if (flag == "--steps")
//        {
//            iterations = std::stoi(argv[i]);
//
//            if (iterations < 1)
//            {
//                std::cerr << "Liczba krokow ma byc wieksza od zera";
//                return 1;
//            }
//        }
//        if (flag == "--distortion")
//        {
//            distortionLevel = std::stof(argv[i]);
//
//            if (distortionLevel<0.0 | distortionLevel> 1.0)
//            {
//                std::cerr << "Deformation value must be between 0.0 and 1.0";
//                return 1;
//            }
//        }
//    }


    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(width, height);
    glutCreateWindow("Dywan Sierpinskiego");

    glutDisplayFunc(RenderScene);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutMainLoop();


    return (0);
}

