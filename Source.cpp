
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "glut.h"

#define W 10        // �n�ʂ̕��@�@�@�@�@�@�@ 
#define D 10        // �n�ʂ̒����@�@�@�@�@�@  
#define QY 1.5      // ���̏����ʒu�̂����W�l  
#define G (-9.8)    // �d�͉����x�@�@�@�@�@�@ �@�@�@�@�@�@�@�@ �@�@ 
#define R 0.1       // �{�[���̔��a�@�@�@�@�@ 

GLfloat white[] = { 0.8, 0.8, 0.8, 1.0 };    // �� 
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };    // �� 
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };    // �� 
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };    // ���F 
GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; // �����̈ʒu 

//�X�^�[�g���[�h
int start_screen = 1;
double start_t = 0.0;
//�Q�[�����[�h
int game_screen = 0;
//���ʃ��[�h
int result_screen = 0;
double result_t = 0.0;
double result_t2 = 0.0;
//�{�[���̍��W
double px, py, pz;
//����
double t = 0.0;
//�o�E���h����
int bound = 0;
//�v���C���[�̈ʒu
double player_x = 1.0, player_y = 0.0, player_z = 4.0;
//�G�̈ʒu
double enemy_x = -1.0, enemy_y = 0.0, enemy_z = -14.0;
//�l�̎肪�����@���̔���
int hit = 0;
//double hit_t = 0.0;
//�����p�̕ϐ�
char str[20];
//���_���ς��̂�����
double kakudo = 0.0;
int kaiten = 0;
double kaiten_t = 0.0;
//�X�^�[�g
int start = 0;
//���v�_�̊�����ɂ���čŏ��̗����ʒu���ς��
int count = 0;
//�G���^�[�L�[���������烉�P�b�g��U��
int my_shot = 0;
double my_shot_time = 0.0;
//�X�g���[�N�̂����蔻��
int atari = 0;
//�T�[�u�̃{�[���ʒu
double serve_x, serve_y, serve_z;
double serve_time = 0.0;

double return_bound_x, return_bound_y, return_bound_z;
//�v���C���[�{�[����
int player_ball = 0;
//�G�{�[����
int enemy_ball = 0;

//�{�[�����ł��������̗�������
int my_course_x;
int my_course_x2;
int enemy_course;
int my_course_z;

//�_��
int enemy_score = 0;
int my_score = 0;

//�|�C���g�I��
int point = 0;

//���������̎��_�ړ��Ɏg������
double win_t = 0;
int win = 0;
int player_win = 0;
int enemy_win = 0;

//�ł��Ă���r�����ǂ����̔���
int hitting = 0;

//�A�E�g�̕����̕\��
int out = 0;

//�G�[�X�̕����̕\��
int ace = 0;

//�X�^�[�g�𑣂������̕\��
int button_s = 0;
double button_s_t = 0.0; //��������

//�T�[�u�Ƃ���ȊO�̋��
int serve = 1;

GLdouble vertex[][3] = {
	{ 0.0, 0.0, 0.0 },
	{ 0.1, 0.0, 0.0 },
	{ 0.1, 0.1, 0.0 },
	{ 0.0, 0.1, 0.0 },
	{ 0.0, 0.0, 0.4 },
	{ 0.1, 0.0, 0.4 },
	{ 0.1, 0.1, 0.4 },
	{ 0.0, 0.1, 0.4 }
};

//�ʂ̒�`
int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};

void explain() {
	puts("===========================������@================================================================================");
	puts("s�L�[�ŃX�^�[�g���܂��I");
	puts("���L�[�����������g���ă����o�E���h��������ł���̈ʒu�܂Ŏ����Ă��������ŏ���ɑł��Ă���܂�");
	puts("�łƂ������͑̂ɓ��Ă����ł����ł��I");
	puts("���̃|�C���g���n�߂�������s�L�[�������Ă�������");
	puts("1�Q�[�����m�[�A�h�o���e�[�W--->4�_���A����3-3�ɂȂ�������1�_�Ƃ������������ł�");
	puts("1-->15, 2-->30, 3-->40�ƕ\������܂�");
	puts("");
	puts("");

	puts("============================���l=====================================================================================");
	puts("����̃A�E�g�Ń|�C���g������܂��A�S��܂��傤�I");
	puts("�����̃A�E�g�A����̃G�[�X�ő���Ƀ|�C���g������܂�");
	puts("���X�A�����̂킩��Ȃ������G���[���o�邱�Ƃ�����܂��A�\���󂠂�܂���I�I�I");
	puts("�I�v�V�����@�\������������̂Ŏ����Ă݂Ă��炢�����ł��I");
	puts("enter������");
	puts("b�L�[������");
	puts("�t�@���N�V�����L�[������F1,F2,F3,F4");

}


//�R�[�g��`��
void drawCoat(double height)
{
	GLfloat ground[][4] = {
		{ 0.0, 0.9, 0.9, 1.0 },
		{ 0.0, 0.9, 0.9, 1.0 }
	};
	GLfloat white[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat green[] = { 0.6, 1.0, 0.1, 1.0 };
	GLfloat brown[] = { 0.5, 0.5, 0.4, 1.0 };
	//�n��(����)
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	glVertex3d(-D / 2, 0, -(3 * W) / 2);
	glVertex3d(-D / 2, 0, W / 2);
	glVertex3d(-2.5, 0, W / 2);
	glVertex3d(-2.5, 0, -(3 * W) / 2);
	glEnd();

	//�n��(�E��)
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	glVertex3d(2.5, 0, -(3 * W) / 2);
	glVertex3d(2.5, 0, W / 2);
	glVertex3d(D / 2, 0, W / 2);
	glVertex3d(D / 2, 0, -(3 * W) / 2);
	glEnd();

	//�R�[�g��
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glVertex3d(-2.5, 0, -14);
	glVertex3d(-2.5, 0, 4);
	glVertex3d(2.5, 0, 4);
	glVertex3d(2.5, 0, -14);
	glEnd();

	//�l�b�g�̍��|�[��
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 1.0, -5.0);
	glVertex3d(-2.5, 0.0, -5.0);
	glEnd();

	//�l�b�g�̉E�|�[��
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(2.5, 1.0, -5.0);
	glVertex3d(2.5, 0.0, -5.0);
	glEnd();

	glLineWidth(1);
	//�l�b�g�̖ԕ���
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	for (int i = 0; i<10; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(-2.5, 0.0 + 0.1*i, -5.0);
		glVertex3d(2.5, 0.0 + 0.1*i, -5.0);
		glEnd();
	}
	for (int i = 0; i<25; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(-2.5 + 0.2*i, 0.0, -5.0);
		glVertex3d(-2.5 + 0.2*i, 1.0, -5.0);
		glEnd();
	}

	glLineWidth(2); //���C���̑���
	//�l�b�g�̏㕔��
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 1.0, -5.0);
	glVertex3d(-2.5, 0.9, -5.0);
	glVertex3d(2.5, 0.9, -5.0);
	glVertex3d(2.5, 1.0, -5.0);
	glEnd();

	glLineWidth(5);
	//�����C��(�_�u���X)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 0.0, -14.0);
	glVertex3d(-2.5, 0.0, 4.0);
	glEnd();

	//�E���C��(�_�u���X)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(2.5, 0.0, -14.0);
	glVertex3d(2.5, 0.0, 4.0);
	glEnd();

	//�����C��(�V���O���X)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.0, 0.0, -14.0);
	glVertex3d(-2.0, 0.0, 4.0);
	glEnd();

	//�E���C��(�_�u���X)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(2.0, 0.0, -14.0);
	glVertex3d(2.0, 0.0, 4.0);
	glEnd();

	//�T�[�r�X���C��(��O)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.0, 0.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);
	glEnd();
	//�T�[�r�X���C��(��)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.0, -10.0, 0.0);
	glVertex3d(2.0, -10.0, 0.0);
	glEnd();

	//�T�[�r�X�Z���^�[���C��(��O)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(0.0, 0.0, -5.0);
	glVertex3d(0.0, 0.0, 0.0);
	glEnd();

	//�T�[�r�X�Z���^�[���C��(��)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(0.0, 0.0, -5.0);
	glVertex3d(0.0, 0.0, -10.0);
	glEnd();

	//�x�[�X���C��(��O)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 0.0, 4.0);
	glVertex3d(2.5, 0.0, 4.0);
	glEnd();

	//�x�[�X���C��(��)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 0.0, -14.0);
	glVertex3d(2.5, 0.0, -14.0);
	glEnd();

}

//�G�̕`��
void drawEnemy(void) {
	//�����ʒu
	if (start == 1) {
		if (count % 2 == 0) {
			enemy_x = -1.5;
		}
		else {
			enemy_x = 1.5;
		}
	}
	
	//�~��(����)
	glPushMatrix();
	glTranslated(enemy_x, enemy_y, enemy_z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glutSolidCone(0.2, 1.0, 16, 8);//�����F(���a, ����, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();

	//������(�E��)
	glPushMatrix();
	glTranslated(enemy_x + 0.1, enemy_y + 0.5, enemy_z);//���s�ړ��l�̐ݒ�
	if (hit) {
		glRotated(30.0 + t * 2, 0.0, 1.0, 0.0);
	}
	else {
		glRotated(30.0, 0.0, 0.0, 1.0);
	}
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

	//������(����)
	glPushMatrix();
	//���s�ړ��l�̐ݒ�
	glTranslated(enemy_x - 0.1, enemy_y + 0.5, enemy_z);
	if (hit) {
		glRotated(-(30.0 + t * 2), 0.0, 1.0, 0.0);
	}
	else {
		glRotated(30.0, 0.0, 0.0, 1.0);
	}
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

	//��(��)
	glPushMatrix();
	//�F�̐ݒ�
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(enemy_x, enemy_y + 0.8, enemy_z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glutSolidSphere(0.2, 20, 20);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();
}

//�v���C���[�̕`��
void drawPlayer(void) {

	//�~��(����)
	glPushMatrix();
	//double player_x=0.0, player_y=0.0, player_z=4.0;�̓O���[�o���ϐ�
	glTranslated(player_x, player_y, player_z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	//�����F(���a, ����, Z���܂��̕�����, Z���ɉ�����������)
	glutSolidCone(0.2, 1.0, 16, 8);
	glPopMatrix();

	//������(�E��)
	glPushMatrix();
	//���s�ړ��l�̐ݒ�
	glTranslated(player_x + 0.1, player_y + 0.5, player_z);
	if (my_shot) {
		hitting = 1;
		glRotated(30.0 + my_shot_time * 2, 0.0, 1.0, 0.0);
		if (30.0 + my_shot_time * 2 > 180) {
			my_shot = 0;
			my_shot_time = 0.0;

		}
	}
	else {
		hitting = 0;
		glRotated(30.0, 0.0, 0.0, 1.0);
	}
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

	//������(����)
	glPushMatrix();
	//���s�ړ��l�̐ݒ�
	glTranslated(player_x - 0.1, player_y + 0.5, player_z);
	if (my_shot) {
		glRotated(-(30.0 + my_shot_time * 2), 0.0, 1.0, 0.0);
	}
	else {
		glRotated(30.0, 0.0, 0.0, 1.0);
	}
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

	//��(��)
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0); //�F�̐ݒ�
	glTranslated(player_x, player_y + 0.8, player_z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glutSolidSphere(0.2, 20, 20);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();

}

//�G���ł֐�
void enemy_stroke() {

	//�T�[�u�̕����F�T�[�u�͍��E�ɑł���������
	if (start != 1) {
		my_course_x = rand() % 10 + 1;
		if (my_course_x % 3 == 0) {
			if (count%2 == 0) {
				my_course_x = 4;
			}
			else {
				my_course_x = -4;
			}
		}
		else if (my_course_x % 3 == 1) {
			if (count%2 == 0) {
				my_course_x = 3;
			}
			else {
				my_course_x = -3;
			}
		}
		else if (my_course_x % 3 == 2) {
			if (count%2 == 0) {
				my_course_x = 3.5;
			}
			else {
				my_course_x = -3.5;
			}
		}
	}

	if (enemy_ball != 1) {
		//�X�g���[�N�̐U�蕪��
		my_course_x2 = rand() % 10 + 1;
		if (enemy_x >= 0) {
			if (my_course_x2 % 3 == 0) {
				//���߂̃N���X
				my_course_x2 = 3.5;
			}
			else if (my_course_x2 % 3 == 1) {
				//���߂̃N���X
				my_course_x2 = 2;
			}
			else if (my_course_x2 % 3 == 2) {
				//�X�g���[�g
				my_course_x2 = 0.5;
			}
		}
		else {
			if (my_course_x2 % 3 == 0) {
				//���߂̃N���X
				my_course_x2 = -3.5;
			}
			else if (my_course_x2 % 3 == 1) {
				//���߂̃N���X
				my_course_x2 = -2;
			}
			else if (my_course_x2 % 3 == 2) {
				//�X�g���[�g
				my_course_x2 = -1;
			}
		}

		//�x�[�X���C���𒴂��Ȃ����߂̍H�v
		if (return_bound_z > -8) {
			my_course_z = 17;
		}
		else if (return_bound_z > -11) {
			my_course_z = 17;
		}
		else {
			my_course_z = 25;
		}
	}

	if (start == 1 || enemy_ball == 1) {
		if (start == 1) {
			px = enemy_x + t * my_course_x;
		}
		else {
			px = enemy_x + t * my_course_x2;
		}

		py = (enemy_y + 2) + (0.5 * G * t * t);
		if (start == 1) {
			pz = enemy_z + t * 20;
		}
		else if (enemy_ball == 1) {
			pz = enemy_z + t * my_course_z;
		}
		//�o�E���h����
		if ((abs(py) - R) <= 0) {
			bound = 1;
			if (px > 2 || px < -2 || py < -5 || py > 4) {
				printf("�A�E�g");
				out = 1;
				button_s = 1;
				my_score += 15;
				count++;
				//�킩��₷���悤�ɗ����ʒu���|�C���g���n�܂�O�ɕς��Ă���
				if (count % 2 == 0) {
					enemy_x = -1.5;
				}
				else {
					enemy_x = 1.5;
				}
				serve = 1;
				enemy_ball = 0;
				player_ball = 0;
				start = 0;
				bound = 0;
			}
		}
		if (bound == 1) {
			py = (enemy_y)-(0.025 * G * t * t);
		}
		else {
			py = (enemy_y + 2) + (0.5 * G * t * t);
		}
		glPushMatrix();
		glTranslated(px, py, pz);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		glutSolidSphere(R, 16, 8);
		glPopMatrix();

		if ((start == 1 || enemy_ball == 1) && pz > 4.5) {
			bound = 0;
			player_ball = 1;
			enemy_ball = 0;

		}
	}
}

//�v���C���[�̃V���b�g
void my_stroke() {
	//�T�[�u����X�g���[�N��
	serve++;
	//�����蔻��
	double return_x, return_y, return_z;

	if (player_ball == 1) {
		if (pz >= 4.5) {
			//�����蔻��
			//if (abs(px - player_x)<2 && abs(py - player_y)<2 && (abs(pz - player_z)<2) ){
			if (abs(px - player_x)<1 && abs(py - player_y)<1 && (abs(pz - player_z)<2)) {
				atari = 1;
				serve_x = px;
				serve_y = py;
				serve_z = pz;
			}
			//�{�[���ɒǂ����Ȃ������Ƃ�
			else {
				printf("�G�[�X"); 
				ace = 1;
				button_s = 1;
				enemy_score += 15;
				count++;
				//�킩��₷���悤�ɗ����ʒu���|�C���g���n�܂�O�ɕς��Ă���
				if (count % 2 == 0) {
					enemy_x = -1.5;
				}
				else {
					enemy_x = 1.5;
				}
				serve = 1;
				px = enemy_x, py = enemy_y + 2, pz = enemy_z;
				player_ball = 0;
				t = 0;
				enemy_ball = 0;
				start = 0;
			}
		}

		if (atari == 1) {
			return_x = serve_x;
			return_y = (serve_y + 2) + (0.5 * G * serve_time * serve_time);
			return_z = serve_z - serve_time * 22;
			start = 0;

			//�o�E���h����
			if ((abs(return_y) - R) <= 0) {
				return_bound_x = return_x, return_bound_y = return_y, return_bound_z = return_z;
				bound = 2;
				//�A�E�g����
				if (return_x > 2 || return_x < -2 || return_y < -14 ) {
					printf("�A�E�g");
					out = 1;
					enemy_score += 15;
					button_s = 1;
					count++;
					//�킩��₷���悤�ɗ����ʒu���|�C���g���n�܂�O�ɕς��Ă���
					if (count % 2 == 0) {
						enemy_x = -1.5;
					}
					else {
						enemy_x = 1.5;
					}
					serve = 1;
					enemy_ball = 0;
					player_ball = 0;
					start = 0;
					bound = 0;
				}

			}
			if (bound == 2) {
				return_y = (serve_y + 2) - (0.5 * G * serve_time * serve_time);
				enemy_x = return_bound_x, enemy_y = return_bound_y, enemy_z = return_bound_z - 3;
				player_ball = 0;
				enemy_ball = 1;
				atari = 0;
			}
			else {
				return_y = (serve_y + 2) + (0.5 * G * serve_time * serve_time);
			}
			glPushMatrix();
			glTranslated(return_x, return_y, return_z);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
			glutSolidSphere(R, 16, 8);
			glPopMatrix();
		}
	}

}

// ��ʕ\��
void display(void)
{
	//��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//���f���r���[�ϊ��s��̏����� 
	glLoadIdentity();
	//�����̈ʒu��ݒ� 
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	//�X�^�[�g���
	if (start_screen) {
		glTranslated(0.0, -5.0+kakudo, -D);
		drawCoat(0.0);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		sprintf(str, "Tennis");
		glColor3d(1.0, 0.0, 0.0);
		glRasterPos3d(-0.5, 2.0, 0.0);
		for (int i = 0; i < strlen(str); i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
		}
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	//�Q�[�����
	if (game_screen) {
		//���_�̈ړ��i���̂̕������Ɉڂ��j
		glTranslated(0.0, -QY, -D + kakudo);
		//���_�������̂�����
		if (kaiten == 1) {
			glTranslated(0.0 + kaiten_t, -QY, -D);
		}
		if (win == 1) {
			glTranslated(0.0, -QY, -D - win_t);
		}
		//�A�E�g�̕\��
		if (out == 1) {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			sprintf(str, "Out!!!");
			glColor3d(1.0, 0.0, 0.0);
			glRasterPos3d(1.5, 3.0, 0.0);
			for (int i = 0; i < strlen(str); i++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
			}
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}
		//�G�[�X�̕\��
		if (ace == 1) {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			sprintf(str, "Ace!!!");
			glColor3d(1.0, 0.0, 0.0);
			glRasterPos3d(1.5, 3.0, 0.0);
			for (int i = 0; i < strlen(str); i++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
			}
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}
		//s�{�^���������悤�ɑ�������
		if (button_s== 1) {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			sprintf(str, "Start with 's' key.");
			glColor3d(0.0, 0.0, 1.0);
			glRasterPos3d(2.5-button_s_t, 2.0, 0.0);
			for (int i = 0; i < strlen(str); i++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
			}
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}
		//�R�[�g�̕`��
		drawCoat(0.0);
		//�G�̃X�g���[�N
		enemy_stroke();
		//�����̃X�g���[�N
		my_stroke();
		drawPlayer();
		drawEnemy();
		//�_���̕\��
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		//�G�̓_��
		if (enemy_score == 45) {
			sprintf(str, "enemy  : %d", 40);
		}
		else {
			sprintf(str, "enemy  : %d", enemy_score);
		}
		glColor3d(1.0, 0.0, 0.0);
		glRasterPos3d(-1.5, 3.5, 0.0);
		for (int i = 0; i < strlen(str); i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
		}
		//�����̓_��
		if (my_score == 45) {
			sprintf(str, "player : %d", 40);
		}
		else {
			sprintf(str, "player : %d", my_score);
		}
		
		glColor3d(1.0, 0.0, 0.0);
		glRasterPos3d(-1.5, 3.2, 0.0);
		for (int i = 0; i < strlen(str); i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
		}
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		//�������G�̂ǂ���������������result��ʂ�
		if ((my_score > 45 && enemy_score < 45) ||( enemy_score > 45 && my_score < 45)){
			if (my_score > 45) {
				player_win = 1;
			}
			else {
				enemy_win = 1;
			}
			game_screen = 0;
			result_screen = 1;
		}
		
		else if((my_score == 60 && enemy_score == 45) || (enemy_score == 60 && my_score == 45)) {
			if (my_score == 60) {
				player_win = 1;
				game_screen = 0;
				result_screen = 1;
			}
			else {
				enemy_win = 1;
				game_screen = 0;
				result_screen = 1;
			}
			game_screen = 0;
			result_screen = 1;
		}
	}

	if (result_screen) {
		glTranslated(0.0, -QY, -D + kakudo);
		
		drawPlayer();
		drawEnemy();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		if (player_win) {
			sprintf(str, "You Win!!");
			player_x = 1.0, player_y = player_y + result_t, player_z = 3.0;
			enemy_x = -1.0, enemy_y = 0.0, enemy_z = 3.0 - result_t2;

		}
		else {
			sprintf(str, "You Lose!!");
			player_x = 1.0, player_y = 0.0, player_z = 3.0 - result_t2;
			enemy_x = -1.0, enemy_y = enemy_y + result_t, enemy_z = 3.0;
		}
		glColor3d(1.0, 0.0, 0.0);
		glRasterPos3d(-0.5, 2.0, 0.0);
		for (int i = 0; i < strlen(str); i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
		}
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

	//�S�̂��O�̐F�ɂȂ�̂�h��
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glFlush();
}


void resize(int w, int h)
{
	//�E�B���h�E�S�̂��r���[�|�[�g�ɂ��� 
	glViewport(0, 0, w, h);
	//�����ϊ��s��̎w�� 
	glMatrixMode(GL_PROJECTION);
	//�����ϊ��s��̏����� 
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	//���f���r���[�ϊ��s��̎w��
	glMatrixMode(GL_MODELVIEW);

}

//�L�[�{�[�h�֐�
void keyboard(unsigned char key, int x, int y)
{
	//ESC �� q ���^�C�v������I�� 
	if (key == '\033' || key == 'q') {
		exit(0);
	}
	if (key == 'b') {
		kaiten = 1;
	}
	if (key == 's') {
		printf("s");
		start = 1;
		out = 0;
		ace = 0;
		button_s = 0;
	}
	if (key == '\015') //ENTER
	{
		my_shot = 1;
		printf("ENTER");
	}

}

//idle�֐�
void idle() {
	if (start == 1 || enemy_ball == 1) {
		t += 0.00015;
		//t+=1;
	}
	else {
		t = 0;
	}
	if (my_shot == 1) {
		my_shot_time += 0.030;
		
	}
	if (win == 1) {
		win_t += 0.1;
		printf("%lf", -D - win_t);
		
		if ((-D - win_t) < -50) {
			printf("finish move");
			win_t = 0;
		}

	}
	else {
		win_t = 0;
	}

	//���_���ړ�������
	if (kaiten == 1) {
		kaiten_t += 0.0015;
		if (kaiten_t > 20) {
			kaiten = 0;
		}
	}
	else {
		kaiten_t = 0;
	}
	if (atari == 1) {
		serve_time += 0.00015;
	}
	else {
		serve_time = 0.0;
	}

	if (start_screen == 1) {
		start_t += 0.001;
		kakudo += 0.0001;
		if (start_t > 20.0) {
			button_s = 1;
			start_screen = 0;
			game_screen = 1;
			kakudo = 0;
		}
	}

	if (result_screen == 1) {
		result_t += 0.000001;
		result_t2 += 0.0002;
		if (result_t > 0.0009) {
	
			result_t = 0.0;
			enemy_y = 0.0;
			player_y = 0.0;
		}
	}

	if (button_s == 1) {
		button_s_t += 0.001;
		if (-button_s_t < -7.5) {
			button_s_t = 0;
		}
	}
	else {
		button_s_t = 0;
	}
	
	//�ĕ`��
	glutPostRedisplay();
}

//���L�[
void specialkeydown(int key, int x, int y) {
	if (key == GLUT_KEY_UP) //��
	{
		player_z -= 0.1;
		//���_�̈ړ�
		//kakudo += 0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN) //��
	{
		player_z += 0.1;
		//kakudo-=0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_LEFT) //��
	{
		player_x -= 0.1;
		//kakudo-=0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_RIGHT) //�E
	{
		player_x += 0.1;
		//kakudo += 0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F1) {
		kakudo += 0.1;
		printf("F1");
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F2) {
		kakudo -= 0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F3) {
		kakudo += 0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_F4) {
		kakudo -= 0.1;
		glutPostRedisplay();
	}
}

void init(void)
{
	///�����ݒ� 
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	explain();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeydown);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 0;
}


