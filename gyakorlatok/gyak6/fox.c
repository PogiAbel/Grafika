#include <GL/glut.h>

#include <SOIL/SOIL.h>

double rotateX;
double rotateY;

typedef GLubyte Pixel[3];

Pixel* images[3];
GLuint texture_names[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename, Pixel* image)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	
    /*
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture_name;
}

void initialize_texture()
{
    unsigned int i;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
    char texture_filenames[][32] = {
        "textures/box1.png",
        "textures/box2.png",
        "textures/box3.png"
    };

    /*
    texture_names[0] = load_texture("box1.png", images[0]);
    texture_names[1] = load_texture("box2.png", images[1]);
    texture_names[2] = load_texture("box3.png", images[2]);
    */

    for (i = 0; i < 3; ++i) {
        texture_names[i] = load_texture(texture_filenames[i], images[i]);
        /*
        cout << "texture filename " << texture_filenames[i] << endl;
        cout << "texture name " << texture_names[i] << endl;
        */
    }

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

void display()
{
    // cout << "display" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

    // cout << "rotateX = " << rotateX << endl;
    glRotatef(rotateX, 1.0, 0, 0);

    // cout << "rotateY = " << rotateY << endl;
    glRotatef(rotateY, 0, 1.0, 0);

    // Top
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);

	glBegin(GL_QUADS);

        glTexCoord2f(0.0,0.0);
        glVertex3d(-0.5,-0.5,0.0);
        
        glTexCoord2f(0.0, 1.0);
        glVertex3d(-0.5,0.0,0.0);
        
        glTexCoord2f(1.0, 1.0);
        glVertex3d(0.5,0.0,0.0);
        
        glTexCoord2f(1.0,0.0);
        glVertex3d(0.5,-0.5,0.0);

    glEnd();

    // Left
    glBindTexture(GL_TEXTURE_2D, texture_names[1]);

	glBegin(GL_QUADS);

        glTexCoord2f(0.0,0.0);
        glVertex3d(-0.5, 0.0, 0.3);
        
        glTexCoord2f(0.0, 1.0);
        glVertex3d(-0.5,0.5,0.3);

        glTexCoord2f(1.0, 1.0);
        glVertex3d(0.0,0.5,0.3);
        
        glTexCoord2f(1.0,0.0);
        glVertex3d(0.0,0.0,0.3);

    glEnd();

    // Right
    glBindTexture(GL_TEXTURE_2D, texture_names[2]);

	glBegin(GL_QUADS);

        glTexCoord2f(0.0,0.0);
        glVertex3d(0.0, 0.0, -0.3);
        
        glTexCoord2f(0.0, 1.0);
        glVertex3d(0.0,0.5,-0.3);
        
        glTexCoord2f(1.0, 1.0);
        glVertex3d(0.5,0.5,-0.3);
        
        glTexCoord2f(1.0,0.0);
        glVertex3d(0.5,0.0,-0.3);

	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    // cout << "Window size: " << width << "x" << height << endl;

	glViewport (0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10.0);
}

void mouseHandler(int button, int state, int x, int y)
{
    /*
    cout << "button : " << button << endl;
    cout << "state  : " << state << endl;
    cout << "x      : " << x << endl;
    cout << "y      : " << y << endl;
    */
}

void motionHandler(int x, int y)
{
    rotateX = x;
    rotateY = y;

    glutPostRedisplay();
}

void idle()
{
}

void initialize()
{
    // glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
        1.0, 1.0, 2.0, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 0.0, 1.0  // up
    );

    glEnable(GL_DEPTH_TEST);
    
    glClearDepth(1.0);

    // Initialize the texture.
    initialize_texture();
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    rotateX = 0.0;
    rotateY = 0.0;

    glutInit(&argc, argv);

	glutInitWindowSize(640, 480);     

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	int window = glutCreateWindow("GLUT Window");
	glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
