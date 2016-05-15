#include <GL/glut.h>
#include "point.h"
#include "game.h"
#include <string>

Game game;
const int k = 3;
int width, height;
int start_btn_x1, start_btn_x2, start_btn_y1, start_btn_y2;
int mouse_x_, mouse_y_;
float scale_msg_ = 1;

void draw_string(void *font, const char* string)
{
	while (*string)
		glutStrokeCharacter(font, *string++);
}

void msg(std::string msg, float x, float y)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scale_msg_, scale_msg_, 1.0);
	glColor3f(1, 1, .5);
	draw_string(GLUT_STROKE_ROMAN, msg.c_str());
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Point p;
	game.draw(p);
	
	if (!game.start_)
	{
		glBegin(GL_QUADS);
		glColor3f(.5, 1, .5);
		glVertex3i(start_btn_x1, start_btn_y1, 1);
		glVertex3i(start_btn_x1, start_btn_y2, 1);
		glVertex3i(start_btn_x2, start_btn_y2, 1);
		glVertex3i(start_btn_x2, start_btn_y1, 1);
		glEnd();
		scale_msg_ = .06f;
		msg("PLAY F1", Line::WIDTH * 4-16, Line::HEIGHT * 4-4);
	}

	glLineWidth(1.5);
	scale_msg_ = 0.04f;
	auto level_s = "Level: " + std::to_string(game.level_);
	msg(level_s, Line::WIDTH - 8, Line::HEIGHT * 10 - 7);
	auto point_s ="Point: " + std::to_string(game.point_game_);
	msg(point_s, Line::WIDTH - 8, Line::HEIGHT * 10 - 14);
	auto point_level_s = "Next level: " + std::to_string(game.next_level_);
	msg(point_level_s, Line::WIDTH - 8, Line::HEIGHT * 10 - 21);
	msg("Pause/Start - F1", Line::WIDTH - 8, Line::HEIGHT * 10 - 28);
	
	glutSwapBuffers();
}

void timer(int)
{
	if(game.start_)
		game.tick();
	display();
	glutTimerFunc(game.time_, timer, 0);
}

void keyEvent(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		game.keyEvent(Game::LEFT);
		break;
	case GLUT_KEY_RIGHT:
		game.keyEvent(Game::RIGHT);
		break;
	case GLUT_KEY_UP:
		game.keyEvent(Game::UP);
		break;
	case GLUT_KEY_DOWN:
		game.keyEvent(Game::DOWN);
		break;
	case GLUT_KEY_F1:
		game.keyEvent(Game::F1);
		break;
	}
	display();
}

void mouse(int button, int state, int mx, int my)
{
	if (state)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			mouse_x_ = mx;
			mouse_y_ = my;
			if (start_btn_x1 * k < mx && start_btn_x2 * k > mx
				&& (height - start_btn_y1 * k) > my && (height - start_btn_y2 * k) < my)
				game.keyEvent(Game::F1);
			break;
		}
	}
}

void reshape(int wid, int ht)
{
	width = wid;
	height = ht;
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width / k, 0, height / k);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	start_btn_x1 = Line::WIDTH * 4 - 20;
	start_btn_x2 = Line::WIDTH * 4 + 20;
	start_btn_y1 = Line::HEIGHT * 4 - 10;
	start_btn_y2 = Line::HEIGHT * 4 + 10;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(245, 600);
	glutCreateWindow("Tetris");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glClearColor(0, 0, 0, 1);
	timer(0);
	glutSpecialFunc(keyEvent);
	glutMouseFunc(mouse);

	glutMainLoop();
}