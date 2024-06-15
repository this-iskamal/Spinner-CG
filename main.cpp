    #include <GL/glu.h>
    #include <GL/glut.h>
    #include <stdio.h>
    #include "glutil.h"

    // Rotation angle and speed variables
    GLfloat spinnerAngle = 0.0f;
    GLfloat spinnerSpeed = 0.01f;
    GLfloat scale = 1.0;

    // Spinner coordinates (3D)
    GLfloat spinner[][3] = {
        {0.0, 0.0, 0.0},   // Center
        {-0.5, 0.0, 0.0},  // Point 1
        {-1.0, 0.0, 0.0},  // Point 2
        {-0.5, 0.5, 0.0},  // Point 3
        {0.0, 0.5, 0.0},   // Point 4
        {0.0, 1.0, 0.0},   // Point 5
        {0.5, 0.5, 0.0},   // Point 6
        {0.5, 0.0, 0.0},   // Point 7
        {1.0, 0.0, 0.0},   // Point 8
        {0.5, -0.5, 0.0},  // Point 9
        {0.0, -0.5, 0.0},  // Point 10
        {0.0, -1.0, 0.0},  // Point 11
        {-0.5, -0.5, 0.0}, // Point 12

        {0.0, 0.03, 0.0},    // Spinner hole (Points 13-20)
        {0.02, 0.02, 0.0},
        {0.03, 0.0, 0.0},
        {0.02, -0.02, 0.0},
        {0.0, -0.03, 0.0},
        {-0.02, -0.02, 0.0},
        {-0.03, 0.0, 0.0},
        {-0.02, 0.02, 0.0}
    };

    // Spinner Stick coordinates (3D)
    GLfloat stick[][3] = {
        {-0.03, 0.03, 0.0},
        {0.03, 0.03, 0.0},
        {0.03, -2.0, 0.0},
        {-0.03, -2.0, 0.0}
    };

    // Converts decimal to RGB
    float d2rgb(float rgbcolor)
    {
        return rgbcolor * (1.0 / 255.0);
    }

    // Draws a leaf
    void draw_leaf(int a, int b, int c, int d, int e)
    {
        glBegin(GL_POLYGON);
        glVertex3fv(spinner[a]);
        glVertex3fv(spinner[b]);
        glVertex3fv(spinner[c]);
        glVertex3fv(spinner[d]);
        glVertex3fv(spinner[e]);
        glEnd();
    }

    // Draws a leaf shade
    void draw_leaf_shade(int a, int b, int c)
    {
        glBegin(GL_POLYGON);
        glVertex3fv(spinner[a]);
        glVertex3fv(spinner[b]);
        glVertex3fv(spinner[c]);
        glEnd();
    }

    // Draws spinner hole
    void draw_spinner_hole()
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex3fv(spinner[13]);
        glVertex3fv(spinner[14]);
        glVertex3fv(spinner[15]);
        glVertex3fv(spinner[16]);
        glVertex3fv(spinner[17]);
        glVertex3fv(spinner[18]);
        glVertex3fv(spinner[19]);
        glVertex3fv(spinner[20]);
        glEnd();
    }

    // Draws spinner stick
    void draw_stick()
    {
        glColor3f(d2rgb(196), d2rgb(167), d2rgb(141));
        glBegin(GL_POLYGON);
        glVertex3fv(stick[0]);
        glVertex3fv(stick[1]);
        glVertex3fv(stick[2]);
        glVertex3fv(stick[3]);
        glEnd();
    }

    // Draws spinner
    void draw_spinner()
    {
        // Draws hole
        draw_spinner_hole();

        // Leaf 1 - Top-Left
        glColor3f(d2rgb(255), d2rgb(152), d2rgb(0));
        draw_leaf_shade(0, 3, 4);
        glColor3f(d2rgb(255.0), d2rgb(188.0), d2rgb(0.0));
        draw_leaf(0, 1, 2, 3, 4);

        // Leaf 2 - Top-Right
        glColor3f(d2rgb(173), d2rgb(20), d2rgb(87));
        draw_leaf_shade(0, 6, 7);
        glColor3f(d2rgb(219.0), d2rgb(68.0), d2rgb(55.0));
        draw_leaf(0, 4, 5, 6, 7);

        // Leaf 3 - Bottom-Right
        glColor3f(d2rgb(51), d2rgb(102), d2rgb(211));
        draw_leaf_shade(0, 9, 10);
        glColor3f(d2rgb(66.0), d2rgb(133.0), d2rgb(244.0));
        draw_leaf(0, 7, 8, 9, 10);

        // Leaf 4 - Bottom-Left
        glColor3f(d2rgb(15), d2rgb(157), d2rgb(88));
        draw_leaf_shade(0, 12, 1);
        glColor3f(d2rgb(139.0), d2rgb(195.0), d2rgb(74.0));
        draw_leaf(0, 10, 11, 12, 1);
    }

    // Function to play sound based on speed
    void playSoundBasedOnSpeed(float speed)
    {
        if (speed == 0.0f)
        {
            // Stop sound
            //StopMusic();
            PlayMusic("C:\\Users\\kamal\\Downloads\\speed_5,speed_4,speed_3\\speed_0.wav");
        }
        else if ((speed > 0.0f && speed <= 0.05f) || (speed < -0.0f && speed >= -0.05f))
        {
            PlayMusic("C:\\Users\\kamal\\Downloads\\speed_5,speed_4,speed_3\\speed_2.wav");
        }
        else if ((speed > 0.05f && speed <= 0.1f) || (speed < -0.05f && speed >= -0.1f))
        {
            PlayMusic("C:\\Users\\kamal\\Downloads\\speed_5,speed_4,speed_3\\speed_3.wav");
        }
        else if (speed > 0.1f || speed < -0.1f)
        {
            PlayMusic("C:\\Users\\kamal\\Downloads\\speed_5,speed_4,speed_3\\speed_5.wav");
        }
    }

    // Display function
    void display(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        glScalef(scale, scale, scale);

        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(spinnerAngle, 0.0f, 0.0f, 1.0f);
        draw_spinner();
        glLoadIdentity();
        glScalef(scale, scale, scale);

        draw_stick();
        spinnerAngle -= spinnerSpeed;
        glPopMatrix();
        glutPostRedisplay();
        glutSwapBuffers();
    }

    // Reshape function
    void myReshape(int w, int h)
    {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
        if (aspectRatio > 1.0f) {
            glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -10.0, 10.0);
        } else {
            glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -10.0, 10.0);
        }

        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
    }

    // Keyboard Controls
    void keyboard(unsigned char key, int x, int y)
    {
        if (key == 'a')
        {
            spinnerSpeed -= 0.01f;
        }
        if (key == 'd')
        {
            spinnerSpeed += 0.01f;
        }
        if (key == 's')
        {
            spinnerSpeed = 0.0f;
        }
        if (key == 'x')
        {
            scale += 0.01f;
        }
        if (key == 'z')
        {
            scale -= 0.01f;
        }

        // Play sound based on the updated speed
        playSoundBasedOnSpeed(spinnerSpeed);

        glutPostRedisplay();
    }

    // Main function
    int main(int argc, char **argv)
    {
        printf("Keyboard Controls:\n");
        printf("a : Anticlockwise spinning\n");
        printf("s : Stops spinning\n");
        printf("d : Clockwise spinning\n");
        printf("x : Increase scale\n");
        printf("z : Decrease scale\n");

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(600, 600);
        glutCreateWindow("Spinner");
        PlayMusic("C:\\Users\\kamal\\Downloads\\speed_5,speed_4,speed_3\\speed_1.wav");
        glutDisplayFunc(display);
        glEnable(GL_DEPTH_TEST);
        glutReshapeFunc(myReshape);
        glClearColor(d2rgb(237), d2rgb(237), d2rgb(237), 1.0);
        glutKeyboardFunc(keyboard);
        glutMainLoop();

        return 0;
    }
