#include <GL/glut.h> 
#include <cmath> 
#include <cstring> 


float rotationX = 0.0f; 
float rotationY = 0.0f; 
const float PI = 3.14159265359f; 
void drawRing(float outerRadius, float innerRadius, int segments) { 
glBegin(GL_QUAD_STRIP); 
for (int i = 0; i <= segments; i++) { 
float angle = 2.0f * PI * i / segments; 
float x = cos(angle); 
float y = sin(angle); 
glNormal3f(0.0f, 0.0f, 1.0f); 
glVertex3f(outerRadius * x, outerRadius * y, 0.0f); 
glVertex3f(innerRadius * x, innerRadius * y, 0.0f); 
} 
glEnd(); 
} 
void drawCenteredText(const char* text, float y, float scale, float strokeWidth) { 
float width = 0.0f; 
for (int i = 0; text[i]; i++) { 
width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]); 
} 
glPushMatrix(); 
glTranslatef(-width * scale / 2.0f, y, 0.0f); 
glScalef(scale, scale, scale); 
glLineWidth(strokeWidth); 
for (int i = 0; text[i]; i++) { 
glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]); 
} 
glPopMatrix(); 
} 
void drawMercedesBenzLogo() { 
glColor3f(0.7f, 0.7f, 0.7f); 
drawRing(4.6f, 4.2f, 100);   
float outerLen = 4.2f;  
float innerLen = 0.0f;  
float widthFactor = 0.6f; 
float depth = 0.8f;     
float angles[3] = { 
90.0f * PI / 180.0f, 
210.0f * PI / 180.0f, 
330.0f * PI / 180.0f  
}; 
glBegin(GL_TRIANGLES); 
for (int i = 0; i < 3; i++) { 
float angleTip = angles[i]; 
float angleValleyRight = angleTip - (120.0f * PI / 180.0f) / 2.0f; 
float angleValleyLeft = angleTip + (120.0f * PI / 180.0f) / 2.0f; 
float tipX = outerLen * cos(angleTip); 
float tipY = outerLen * sin(angleTip); 
float centerX = 0.0f; 
float centerY = 0.0f; 
float centerZ = depth; 
float valleyRad = 0.7f; 
float vRightX = valleyRad * cos(angleTip - (60.0f * PI / 180.0f)); 
float vRightY = valleyRad * sin(angleTip - (60.0f * PI / 180.0f)); 
float vLeftX = valleyRad * cos(angleTip + (60.0f * PI / 180.0f)); 
float vLeftY = valleyRad * sin(angleTip + (60.0f * PI / 180.0f)); 
glColor3f(0.5f, 0.5f, 0.5f); 
glVertex3f(centerX, centerY, centerZ);  
glVertex3f(tipX, tipY, 0.0f);           
glVertex3f(vLeftX, vLeftY, 0.0f);       
glColor3f(0.9f, 0.9f, 0.9f); 
glVertex3f(centerX, centerY, centerZ);  
glVertex3f(tipX, tipY, 0.0f);           
glVertex3f(vRightX, vRightY, 0.0f);     
} 
glEnd(); 
} 
void display() { 
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
glLoadIdentity(); 
glTranslatef(0.0f, 1.0f, -18.0f); 
glRotatef(rotationX, 1, 0, 0); 
glRotatef(rotationY, 0, 1, 0); 
// Draw the Logo 
drawMercedesBenzLogo(); 
//Draw Text Section 
glColor3f(0.1f, 0.1f, 0.1f);  
drawCenteredText("MERCEDES-BENZ", -6.0f, 0.012f, 3.0f); 
glColor3f(0.4f, 0.4f, 0.4f);  
glutSwapBuffers(); 
} 
void reshape(int w, int h) { 
if (h == 0) h = 1; 
glViewport(0, 0, w, h); 
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); 
gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f); 
glMatrixMode(GL_MODELVIEW); 
} 
void keyboard(unsigned char key, int, int) { 
switch (key) { 
case 'w': case 'W': rotationX += 5; break; 
case 's': case 'S': rotationX -= 5; break; 
case 'a': case 'A': rotationY -= 5; break; 
case 'd': case 'D': rotationY += 5; break; 
case 27: exit(0); 
} 
glutPostRedisplay(); 
} 
int main(int argc, char** argv) { 
glutInit(&argc, argv); 
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
glutInitWindowSize(800, 800); 
glutCreateWindow("Mercedes-Benz Logo"); 
glClearColor(0.95f, 0.95f, 0.95f, 1.0f); 
glEnable(GL_DEPTH_TEST); 
glutDisplayFunc(display); 
glutReshapeFunc(reshape); 
glutKeyboardFunc(keyboard); 
glutMainLoop(); 
return 0; 
}
