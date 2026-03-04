#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

// ==================== ИНИЦИАЛИЗАЦИЯ OPENGL ====================
void initGL()
{
    glEnable(GL_DEPTH_TEST);        // Включаем Z-buffer
    glEnable(GL_NORMALIZE);         // Нормализация нормалей (для корректного освещения)
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Темно-синий фон

    // Настройка света
    GLfloat lightPos[] = { 0.0f, 5.0f, 10.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

// ==================== НАСТРОЙКА ПРОЕКЦИИ ====================
void changeViewPort(int w, int h)
{
    if (h == 0) h = 1; // защита от деления на 0

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(60.0, (float)w / (float)h, 1.0, 100.0);
    gluPerspective(70.0, (float)w / (float)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// ==================== ОТРИСОВКА СЦЕНЫ ====================
void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Камера чуть дальше и ниже
    gluLookAt(0, 0, 18,
        0, 0, 0,
        0, 1, 0);

    float x_wire = -3.0f;
    float x_solid = 3.0f;

    float y = 8.5f;   // Расположение фигур по оси Y
    float dy = 1.6f;  // Расстояние между фигурами

    // 1. КУБ
    glColor3f(1, 0, 0);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidCube(1); glPopMatrix();
    y -= dy;

    // 2. СФЕРА
    glColor3f(0, 1, 0);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireSphere(0.6, 20, 20); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidSphere(0.6, 20, 20); glPopMatrix();
    y -= dy;

    // 3. КОНУС
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(x_wire, y, 0);
    glRotatef(-90, 1, 0, 0);
    glutWireCone(0.5, 1, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x_solid, y, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.5, 1, 20, 20);
    glPopMatrix();
    y -= dy;

    // 4. ТОР
    glColor3f(1, 1, 0);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireTorus(0.2, 0.5, 20, 20); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidTorus(0.2, 0.5, 20, 20); glPopMatrix();
    y -= dy;

    // 5. ДОДЕКАЭДР
    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(x_wire, y, 0);
    glScalef(0.4f, 0.4f, 0.4f);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x_solid, y, 0);
    glScalef(0.4f, 0.4f, 0.4f);
    glutSolidDodecahedron();
    glPopMatrix();
    y -= dy;

    // 6. ОКТАЭДР
    glColor3f(0, 1, 1);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireOctahedron(); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidOctahedron(); glPopMatrix();
    y -= dy;

    // 7. ТЕТРАЭДР
    glColor3f(1, 0.5f, 0);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireTetrahedron(); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidTetrahedron(); glPopMatrix();
    y -= dy;

    // 8. ИКОСАЭДР  <-- ВОТ ОНА!
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireIcosahedron(); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidIcosahedron(); glPopMatrix();
    y -= dy;

    // 9. ЧАЙНИК
    glColor3f(1, 1, 1);
    glPushMatrix(); glTranslatef(x_wire, y, 0); glutWireTeapot(0.6); glPopMatrix();
    glPushMatrix(); glTranslatef(x_solid, y, 0); glutSolidTeapot(0.6); glPopMatrix();

    glutSwapBuffers();
}

// ==================== MAIN ====================
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 900);
    glutCreateWindow("Lab 3 - GLUT Primitives");

    GLenum err = glewInit();
    if (GLEW_OK != err)
        return 1;

    initGL();

    glutReshapeFunc(changeViewPort);
    glutDisplayFunc(render);

    glutMainLoop();
    return 0;
}