#include <GL/glut.h>
#include <time.h>
#include "world.hpp"

world wrd(180, 1200, 0, 0);
char num[4];
int speed = 1000;
float draw_size_element = 14.0f;
float draw_size_element_indent = 1.0f;
float draw_indent_from_the_edge = 25.0f;
float draw_start_pos_statistic = 125.0f;
float WinWid = draw_indent_from_the_edge * 3 + worldX * draw_size_element + draw_start_pos_statistic;
float WinHei = draw_indent_from_the_edge * 2 + worldY * draw_size_element;

void renderBitmapString(
		int x,
		int y,
		char *string) {
    char *c;
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2d(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    for (int i = 0; i < worldX; i++) 
        for (int j = 0; j < worldY; j++) {
            switch (wrd.getElem(i, j).getStatus()) {
                case EMPTY: glColor3f(1.0f, 1.0f, 1.0f); break;
                case BOT: glColor3f(1.0f, 1.0f, 0.0f); break;
                case FOOD: glColor3f(0.0f, 1.0f, 0.0f); break;
                case POISON: glColor3f(1.0f, 0.0f, 0.0f); break;
                case WALL: glColor3f(0.0f, 0.0f, 1.0f); break;
                default: glColor3f(0.0f, 0.0f, 0.0f); break;
            }
            glVertex2f(draw_indent_from_the_edge + wrd.getElem(i, j).getPosX() * draw_size_element + draw_size_element_indent, draw_indent_from_the_edge + wrd.getElem(i, j).getPosY() * draw_size_element + draw_size_element_indent);
            glVertex2f(draw_indent_from_the_edge + wrd.getElem(i, j).getPosX() * draw_size_element + draw_size_element - draw_size_element_indent, draw_indent_from_the_edge + wrd.getElem(i, j).getPosY() * draw_size_element + draw_size_element_indent);
            glVertex2f(draw_indent_from_the_edge + wrd.getElem(i, j).getPosX() * draw_size_element + draw_size_element - draw_size_element_indent, draw_indent_from_the_edge + wrd.getElem(i, j).getPosY() * draw_size_element + draw_size_element - draw_size_element_indent);
            glVertex2f(draw_indent_from_the_edge + wrd.getElem(i, j).getPosX() * draw_size_element + draw_size_element_indent, draw_indent_from_the_edge + wrd.getElem(i, j).getPosY() * draw_size_element + draw_size_element - draw_size_element_indent);
        }
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge, draw_indent_from_the_edge);
    glVertex2f(WinWid - draw_indent_from_the_edge, draw_indent_from_the_edge);
    glVertex2f(WinWid - draw_indent_from_the_edge, WinHei - draw_indent_from_the_edge);
    glVertex2f(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge, WinHei - draw_indent_from_the_edge);
    
    glEnd();
    
    sprintf(num, "%d", wrd.countBot);
    renderBitmapString(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge + 2, draw_indent_from_the_edge + 15 + 2, num);
    sprintf(num, "%d", wrd.countFood);
    renderBitmapString(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge + 2, draw_indent_from_the_edge + 30 + 2, num);
    glutSwapBuffers();
}

void Timer(int) {
    wrd.run();
    glutPostRedisplay();
    glutTimerFunc(speed, Timer, 0);
}

void Initialize() {
    glMatrixMode(GL_PROJECTION);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLoadIdentity();
    glOrtho(0.0f, WinWid, WinHei, 0.0f, 0.0f, 1.0f);
}



int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WinWid, WinHei);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("artificialLife");
    glutDisplayFunc(Draw);
    glutTimerFunc(speed, Timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}



