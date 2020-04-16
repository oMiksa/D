#include <GL/glut.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "world.hpp"

int selection = 0;
int whiles = 0;

world wrd(80, 300, 60, 100);
//world wrd(1);
char num[2][20][10];
unsigned int speed = 1;
float draw_size_element = 14.0f;
float draw_size_element_indent = 1.0f;
float draw_indent_from_the_edge = 25.0f;
float draw_start_pos_statistic = 125.0f;
float WinWid = draw_indent_from_the_edge * 3 + worldX * draw_size_element + draw_start_pos_statistic;
float WinHei = draw_indent_from_the_edge * 2 + worldY * draw_size_element;


void* thread_fn(void *) {
    int lvl = 0;
    while (1) {
        if (wrd.countBot <= 10) {
            selection++;
            whiles = 0;
            lvl++;
            if (lvl >= 20)
                lvl = 0;
            wrd.newGenerration();
            wrd.init(80, 300, 60, 100);
            wrd.legacy();
        }
        wrd.run();
        whiles++;
        sprintf(num[0][lvl], "%d", selection);
        sprintf(num[1][lvl], "%d", whiles);
        usleep(1000);
    }
}

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
            glVertex2f(draw_indent_from_the_edge + (float)i * draw_size_element + draw_size_element_indent, draw_indent_from_the_edge + (float)j * draw_size_element + draw_size_element_indent);
            glVertex2f(draw_indent_from_the_edge + (float)i * draw_size_element + draw_size_element - draw_size_element_indent, draw_indent_from_the_edge + (float)j * draw_size_element + draw_size_element_indent);
            glVertex2f(draw_indent_from_the_edge + (float)i * draw_size_element + draw_size_element - draw_size_element_indent, draw_indent_from_the_edge + (float)j * draw_size_element + draw_size_element - draw_size_element_indent);
            glVertex2f(draw_indent_from_the_edge + (float)i * draw_size_element + draw_size_element_indent, draw_indent_from_the_edge + (float)j * draw_size_element + draw_size_element - draw_size_element_indent);
        }
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge, draw_indent_from_the_edge);
    glVertex2f(WinWid - draw_indent_from_the_edge, draw_indent_from_the_edge);
    glVertex2f(WinWid - draw_indent_from_the_edge, WinHei - draw_indent_from_the_edge);
    glVertex2f(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge, WinHei - draw_indent_from_the_edge);
    
    glEnd();
    
    for (int i = 0; i < 20; i++) {
        renderBitmapString(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge + 2, draw_indent_from_the_edge + 15 * (1 + i) + 2, num[0][i]);
        renderBitmapString(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge + 50 + 2, draw_indent_from_the_edge + 15 * (1 + i) + 2, num[1][i]);
    }

    // sprintf(num[0][0], "%d", wrd.countBot);
    // renderBitmapString(WinWid - draw_start_pos_statistic - draw_indent_from_the_edge + 2, draw_indent_from_the_edge + 15 + 2, num);
    
    glutSwapBuffers();
}

void Timer(int) {
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
    pthread_t pf;
    pthread_create(&pf, NULL, thread_fn, NULL);    
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



