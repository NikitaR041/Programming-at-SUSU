#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// --------------------
// НАСТРОЙКИ
// --------------------

#define MAX_DEPTH 4       // максимальная глубина октодерева
#define CUBE_SIZE 0.5f    // размер отображаемого куба
#define NUM_OBJECTS 1000  // количество объектов

// --------------------
// КАМЕРА
// --------------------

float camX = 0, camY = 0, camZ = 15; // позиция камеры
float rotX = 0, rotY = 0;            // повороты сцены

// --------------------
// СЧЁТЧИК
// --------------------

int totalObjects = 0;  // всего объектов
int drawnObjects = 0;  // сколько реально нарисовано

int debugMode = 0;     // режим отображения октодерева

// --------------------
// СТРУКТУРА ОБЪЕКТА
// --------------------

typedef struct {
    float x, y, z; // позиция
    float r, g, b; // цвет
} Object;

// --------------------
// OCTREE NODE
// --------------------

typedef struct OctreeNode {
    float x, y, z; // центр узла
    float size;    // половина размера
    int depth;     // глубина

    struct OctreeNode* children[8]; // 8 потомков

    Object* object; // один объект в листе
} OctreeNode;

OctreeNode* root = NULL;

// --------------------
// СОЗДАНИЕ УЗЛА
// --------------------

OctreeNode* createNode(float x, float y, float z, float size, int depth)
{
    OctreeNode* node = (OctreeNode*)malloc(sizeof(OctreeNode));

    node->x = x;
    node->y = y;
    node->z = z;
    node->size = size;
    node->depth = depth;
    node->object = NULL;

    // изначально нет детей
    for (int i = 0; i < 8; i++)
        node->children[i] = NULL;

    return node;
}

// --------------------
// ВСТАВКА В OCTREE
// --------------------

void insertObject(OctreeNode* node, Object obj)
{
    // если достигли максимальной глубины → кладём объект
    if (node->depth >= MAX_DEPTH)
    {
        node->object = (Object*)malloc(sizeof(Object));
        *(node->object) = obj;
        return;
    }

    float half = node->size / 2;

    // определяем октант (0..7)
    int oct = 0;
    if (obj.x > node->x) oct |= 1;
    if (obj.y > node->y) oct |= 2;
    if (obj.z > node->z) oct |= 4;

    // если узел ещё не создан → создаём
    if (node->children[oct] == NULL)
    {
        float dx = (oct & 1) ? half : -half;
        float dy = (oct & 2) ? half : -half;
        float dz = (oct & 4) ? half : -half;

        node->children[oct] = createNode(
            node->x + dx,
            node->y + dy,
            node->z + dz,
            half,
            node->depth + 1
        );
    }

    // рекурсивная вставка
    insertObject(node->children[oct], obj);
}

// --------------------
// ПРОВЕРКА ВИДИМОСТИ
// --------------------

int isVisible(float x, float y, float z, float radius)
{
    float dx = x - camX;
    float dy = y - camY;
    float dz = z - camZ;

    float dist = sqrtf(dx * dx + dy * dy + dz * dz);

    // слишком далеко → не рисуем
    if (dist > 30.0f + radius) return 0;

    // за камерой → не рисуем
    if (dz > 0) return 0;

    return 1;
}

// --------------------
// ОТРИСОВКА OCTREE
// --------------------

void drawOctree(OctreeNode* node)
{
    if (!node) return;

    float radius = node->size * 1.7f;

    // отсечение невидимых узлов
    if (!isVisible(node->x, node->y, node->z, radius))
        return;

    // --- режим отладки (каркас куба узла) ---
    if (debugMode)
    {
        glColor3f(0.3f, 0.3f, 0.3f);
        glPushMatrix();
        glTranslatef(node->x, node->y, node->z);
        glutWireCube(node->size * 2);
        glPopMatrix();
    }

    // --- если это лист с объектом ---
    if (node->object)
    {
        drawnObjects++;

        glPushMatrix();

        // перемещение в позицию объекта
        glTranslatef(node->object->x,
            node->object->y,
            node->object->z);

        // 🎨 УЛУЧШЕННЫЙ ЦВЕТ:
        // делаем цвета более яркими (убираем слишком тёмные)
        float r = node->object->r * 0.7f + 0.3f;
        float g = node->object->g * 0.7f + 0.3f;
        float b = node->object->b * 0.7f + 0.3f;

        glColor3f(r, g, b);

        // рисуем куб
        glutSolidCube(CUBE_SIZE);

        glPopMatrix();
    }

    // рекурсивный обход детей
    for (int i = 0; i < 8; i++)
        drawOctree(node->children[i]);
}

// --------------------
// ТЕКСТ НА ЭКРАНЕ
// --------------------

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}

// --------------------
// ИНИЦИАЛИЗАЦИЯ
// --------------------

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // разрешаем использовать glColor3f для цвета объектов
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.1f, 0.1f, 0.1f, 1);

    root = createNode(0, 0, 0, 10, 0);

    srand(42);

    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        Object obj;

        obj.x = (rand() % 2000) / 100.0f - 10;
        obj.y = (rand() % 2000) / 100.0f - 10;
        obj.z = (rand() % 2000) / 100.0f - 10;

        // случайный цвет
        obj.r = rand() / (float)RAND_MAX;
        obj.g = rand() / (float)RAND_MAX;
        obj.b = rand() / (float)RAND_MAX;

        insertObject(root, obj);
        totalObjects++;
    }
}

// --------------------
// ОТРИСОВКА СЦЕНЫ
// --------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawnObjects = 0;

    glLoadIdentity();

    // камера
    gluLookAt(camX, camY, camZ,
        0, 0, 0,
        0, 1, 0);

    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    drawOctree(root);

    // --- текст ---
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);

    char buf[128];
    sprintf(buf, "Drawn: %d / %d", drawnObjects, totalObjects);
    drawText(-0.95f, 0.9f, buf);

    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

// --------------------
// ИЗМЕНЕНИЕ РАЗМЕРА ОКНА
// --------------------

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (float)w / h, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
}

// --------------------
// УПРАВЛЕНИЕ
// --------------------

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': camZ -= 1; break;
    case 's': camZ += 1; break;
    case 'a': camX -= 1; break;
    case 'd': camX += 1; break;

    case 'r': rotY += 5; break;
    case 'f': rotY -= 5; break;

    case 'D': debugMode = !debugMode; break;

    case 27: exit(0);
    }

    glutPostRedisplay();
}

// --------------------
// MAIN
// --------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);

    glutCreateWindow("Octree Culling Demo");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    printf("WASD - move camera\n");
    printf("R/F - rotate\n");
    printf("D - debug octree\n");

    glutMainLoop();
    return 0;
}
