#include "stdafx.h"
#include "Drawing_Torus.h"

Vector3x1 pt[36][18];
GLfloat gpt[36][18][3];

Vector3x1* nom[36][18];
GLfloat gnom[36][18][3];

Vector3x1 seeYa(1, 1, 1);

int akey = 0;
int jkey = 18;
boolean direction = true;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'a':
		if (akey > 35)akey = 36;
		else akey += 1;
		glutPostRedisplay();
		break;

	case 's':
		if (akey <= 0)akey = 0;
		else akey -= 1;
		glutPostRedisplay();
		break;

	case 'j':
		if (jkey > 17 && direction) {
			jkey = 18;
			direction = true;
		}
		else if (!direction && jkey >= 0) {
			jkey += 1;
			direction = true;
		}
		else if (direction) {
			jkey += 1;
			direction = true;
		}
		else {
			jkey += 1;
			direction = false;
		}
		glutPostRedisplay();

		if (direction)printf("direction : %d true\n", jkey);
		else printf("direction : %d flase\n", jkey);

		break;

	case 'k':
		if (jkey < -17 && !direction) {
			jkey = -18;
			direction = false;
		}
		else if (direction && jkey <= 0) {
			jkey -= 1;
			direction = false;;
		}
		else if (direction) {
			jkey -= 1;
			direction = true;
		}
		else {
			jkey -= 1;
			direction = false;
		}

		glutPostRedisplay();

		if (direction)printf("direction : %d true\n", jkey);
		else printf("direction : %d flase\n", jkey);

		break;

	default:
		break;
	}
}
void RenderScene();
void SetupRC();
void ChangeSize(int w, int h);

void ptTogpt()
{
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			
			for (int k = 0; k < 3; k++)
			{
				gpt[i][j][k] = pt[i][j].xyzArr[k];
			}

			
			if (i == 35)
			{
				if (j == 17)
				{
					Vector3x1* v1 = Vector3x1::VectorSubtraction(&pt[i][0], &pt[i][j]);
					Vector3x1* v2 = Vector3x1::VectorSubtraction(&pt[0][j], &pt[i][j]);

					nom[i][j] = Vector3x1::CrossProduct(v1, v2);
				}
				else
				{
					Vector3x1* v1 = Vector3x1::VectorSubtraction(&pt[i][j + 1], &pt[i][j]);
					Vector3x1* v2 = Vector3x1::VectorSubtraction(&pt[0][j], &pt[i][j]);

					nom[i][j] = Vector3x1::CrossProduct(v1, v2);
				}
			}
			else
			{
			
				if (j == 17)
				{
					Vector3x1* v1 = Vector3x1::VectorSubtraction(&pt[i][0], &pt[i][j]);
					Vector3x1* v2 = Vector3x1::VectorSubtraction(&pt[i + 1][j], &pt[i][j]);

					nom[i][j] = Vector3x1::CrossProduct(v1, v2);
				}
				else
				{
					Vector3x1* v1 = Vector3x1::VectorSubtraction(&pt[i][j + 1], &pt[i][j]);
					Vector3x1* v2 = Vector3x1::VectorSubtraction(&pt[i + 1][j], &pt[i][j]);

					nom[i][j] = Vector3x1::CrossProduct(v1, v2);
				}
			
			}
			/*for (int k = 0; k < 3; k++)
			{
				gnom[i][j][k] = nom[i][j]->xyzArr[k];
			}*/
		}
	}
}

void SetTorus()
{
	double theta = 20 * PI / 180.0;
	double theta2 = 10 * PI / 180.0;

	double cx =0.8, cy=0.8, cz =0;
	double sx=1, sy=0.8, sz=0;

	Vector3x1 centerP(cx, cy, cz);
	Vector3x1 startP(sx, sy, sz);

	for (int i = 0; i < 18; i++)
	{
		Vector3x1* newV = Vector3x1::VectorSubtraction(&startP, &centerP);
		Matrix4x4 rotationMat = Matrix4x4(ZAXIS, theta);
		Vector3x1* rotationV = Matrix4x4::Matrix_VectorMultiplication(&rotationMat, newV);
		Vector3x1* resultV = Vector3x1::VectorAddition(rotationV, &centerP);

		pt[0][i] = *resultV;
		theta += 20 * PI / 180.0;
	}
	
	for (int j = 1; j < 36; j++)
	{
		for (int i = 0; i < 18; i++)
		{
			Matrix4x4 rotationMat2 = Matrix4x4(YAXIS, theta2);
			Vector3x1 newV = Vector3x1(pt[0][i].xyzArr[0], pt[0][i].xyzArr[1], pt[0][i].xyzArr[2]);
			Vector3x1* rotationV = Matrix4x4::Matrix_VectorMultiplication(&rotationMat2, &newV);

			pt[j][i] = *rotationV;
		}
		theta2 += 10 * PI / 180.0;
	}
}
void DrawTorus()
{
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < akey; i++)
	{

		for (int j = 0; j < abs(jkey); j++)
		{
			if (direction)
			{
				if (i == 35)
				{
					double dir = Vector3x1::DotProduct(&seeYa, nom[i][j]);
					if (dir > 0) {
						glColor3f(1, 0, 0);
					}
					else {
						glColor3f(0, 0, 1);
					}
					glVertex3fv(gpt[i][j]);
					glVertex3fv(gpt[0][j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][0]);
						glVertex3fv(gpt[0][0]);
					}
					else
					{
						glVertex3fv(gpt[i][j + 1]);
						glVertex3fv(gpt[0][j + 1]);
					}
				}
				else
				{
					double dir = Vector3x1::DotProduct(&seeYa, nom[i][j]);
					if (dir > 0) {
						glColor3f(1, 0, 0);
					}
					else {
						glColor3f(0, 0, 1);
					}
					glVertex3fv(gpt[i][j]);
					glVertex3fv(gpt[i + 1][j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][0]);
						glVertex3fv(gpt[i + 1][0]);
					}
					else
					{
						glVertex3fv(gpt[i][j + 1]);
						glVertex3fv(gpt[i + 1][j + 1]);
					}

				}
				glEnd();
				glBegin(GL_QUAD_STRIP);
			}
			else
			{
				if (i == 35)
				{
					double dir = Vector3x1::DotProduct(&seeYa, nom[i][17 - j]);
					if (dir > 0) {
						glColor3f(1, 0, 0);
					}
					else {
						glColor3f(0, 0, 1);
					}
					glVertex3fv(gpt[i][17 - j]);
					glVertex3fv(gpt[0][17 - j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][17]);
						glVertex3fv(gpt[0][17]);
					}
					else
					{
						glVertex3fv(gpt[i][17 - (j + 1)]);
						glVertex3fv(gpt[0][17 - (j + 1)]);
					}
				}
				else
				{
					double dir = Vector3x1::DotProduct(&seeYa, nom[i][17 - j]);
					if (dir > 0) {
						glColor3f(1, 0, 0);
					}
					else {
						glColor3f(0, 0, 1);
					}
					glVertex3fv(gpt[i][17 - j]);
					glVertex3fv(gpt[i + 1][17 - j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][17]);
						glVertex3fv(gpt[i + 1][17]);
					}
					else
					{
						glVertex3fv(gpt[i][17 - (j + 1)]);
						glVertex3fv(gpt[i + 1][17 - (j + 1)]);
					}

				}
				glEnd();
				glBegin(GL_QUAD_STRIP);
			}
		}

	}
}
void DrawTorusLine()
{
	glColor3f(0, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < akey; i++)
	{

		for (int j = 0; j <  abs(jkey); j++)
		{
			if (direction)
			{
				if (i == 35)
				{
					glVertex3fv(gpt[i][j]);
					glVertex3fv(gpt[0][j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][0]);
						glVertex3fv(gpt[0][0]);
					}
					else
					{
						glVertex3fv(gpt[i][j + 1]);
						glVertex3fv(gpt[0][j + 1]);
					}
				}
				else
				{
					glVertex3fv(gpt[i][j]);
					glVertex3fv(gpt[i + 1][j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][0]);
						glVertex3fv(gpt[i + 1][0]);
					}
					else
					{
						glVertex3fv(gpt[i][j + 1]);
						glVertex3fv(gpt[i + 1][j + 1]);
					}

				}
				glEnd();
				glBegin(GL_QUAD_STRIP);
			}
			else
			{
				if (i == 35)
				{
					glVertex3fv(gpt[i][17-j]);
					glVertex3fv(gpt[0][17-j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][17]);
						glVertex3fv(gpt[0][17]);
					}
					else
					{
						glVertex3fv(gpt[i][17 -(j + 1)]);
						glVertex3fv(gpt[0][17-(j + 1)]);
					}
				}
				else
				{
					glVertex3fv(gpt[i][17-j]);
					glVertex3fv(gpt[i + 1][17-j]);

					if (j == 17)
					{
						glVertex3fv(gpt[i][17]);
						glVertex3fv(gpt[i + 1][17]);
					}
					else
					{
						glVertex3fv(gpt[i][17-(j + 1)]);
						glVertex3fv(gpt[i + 1][17-(j + 1)]);
					}

				}
				glEnd();
				glBegin(GL_QUAD_STRIP);
			}
		}

	}
}
void DrawTorusNom()
{
	glColor3f(0.8, 0.8, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < akey; i++)
	{

		for (int j = 0; j < abs(jkey); j++)
		{
			if (direction)
			{
				if (i == 35)
				{

					if (j == 17)
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][j], &pt[0][0]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][j]);
					}
					else
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][j], &pt[0][j + 1]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][j]);
					}
				}
				else
				{

					if (j == 17)
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][j], &pt[i + 1][0]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][j]);
					}
					else
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][j], &pt[i + 1][j + 1]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][j]);
					}

				}
				glEnd();
				glBegin(GL_LINES);
			}
			else 
			{
				if (i == 35)
				{

					if (j == 17)
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][17-j], &pt[0][17]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][17-j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][17-j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][17-j]);
					}
					else
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][17-j], &pt[0][17-(j + 1)]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][17-j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][17-j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][17-j]);
					}
				}
				else
				{

					if (j == 17)
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][j], &pt[i + 1][17]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][17-j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][17-j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][17-j]);
					}
					else
					{
						Vector3x1* ori = Vector3x1::ScalarMultiplication(Vector3x1::VectorAddition(&pt[i][17-j], &pt[i + 1][17-(j + 1)]), 0.5);
						GLfloat gori[3];

						Vector3x1* nom1 = Vector3x1::ScalarMultiplication(nom[i][17-j], -20);
						Vector3x1* result = Vector3x1::VectorAddition(ori, nom1);

						for (int k = 0; k < 3; k++)
						{
							gnom[i][17-j][k] = result->xyzArr[k];
							gori[k] = ori->xyzArr[k];


						}

						glVertex3fv(gori);
						glVertex3fv(gnom[i][17-j]);
					}

				}
				glEnd();
				glBegin(GL_LINES);
			}

		}

	}
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Rotus");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutKeyboardFunc(keyboard);

	SetupRC();

	glutMainLoop();
	return 0;
}

void RenderScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLineWidth(1);	
	gluLookAt(1.0f, 1.0f, 1.0f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	glBegin(GL_LINES);    
	{
		glColor3f(1.f, 0.f, 0.f);  
		glVertex3f(0, 0.0, 0.0); 
		glVertex3f(200, 0.0, 0.0);  

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.0, 0, 0.0);
		glVertex3f(0.0, 200, 0.0);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.0, 0.0, 100);
	}
	glEnd();

	SetTorus();
	ptTogpt();

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	DrawTorusLine();
	glEnd();

	glDisable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUAD_STRIP);
	DrawTorus();
	glEnd();

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	DrawTorusNom();
	glEnd();
	

	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);						
}
void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		glOrtho(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0*(float)h / (float)w, -10.0, 10.0);
	}
	else
	{
		glOrtho(-2.0, 2.0, -2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -10.0, 10.0);
	}
}


