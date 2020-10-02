
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "glut.h"

#define W 10        // 地面の幅　　　　　　　 
#define D 10        // 地面の長さ　　　　　　  
#define QY 1.5      // 球の初期位置のｙ座標値  
#define G (-9.8)    // 重力加速度　　　　　　 　　　　　　　　 　　 
#define R 0.1       // ボールの半径　　　　　 

GLfloat white[] = { 0.8, 0.8, 0.8, 1.0 };    // 白 
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };    // 赤 
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };    // 青 
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };    // 黄色 
GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; // 光源の位置 

//スタートモード
int start_screen = 1;
double start_t = 0.0;
//ゲームモード
int game_screen = 0;
//結果モード
int result_screen = 0;
double result_t = 0.0;
double result_t2 = 0.0;
//ボールの座標
double px, py, pz;
//時間
double t = 0.0;
//バウンド判定
int bound = 0;
//プレイヤーの位置
double player_x = 1.0, player_y = 0.0, player_z = 4.0;
//敵の位置
double enemy_x = -1.0, enemy_y = 0.0, enemy_z = -14.0;
//人の手が動く　その判定
int hit = 0;
//double hit_t = 0.0;
//文字用の変数
char str[20];
//視点が変わるのか実験
double kakudo = 0.0;
int kaiten = 0;
double kaiten_t = 0.0;
//スタート
int start = 0;
//合計点の奇数偶数によって最初の立ち位置が変わる
int count = 0;
//エンターキーを押したらラケットを振る
int my_shot = 0;
double my_shot_time = 0.0;
//ストロークのあたり判定
int atari = 0;
//サーブのボール位置
double serve_x, serve_y, serve_z;
double serve_time = 0.0;

double return_bound_x, return_bound_y, return_bound_z;
//プレイヤーボールへ
int player_ball = 0;
//敵ボールへ
int enemy_ball = 0;

//ボールが打たれる方向の乱数生成
int my_course_x;
int my_course_x2;
int enemy_course;
int my_course_z;

//点数
int enemy_score = 0;
int my_score = 0;

//ポイント終了
int point = 0;

//勝った時の視点移動に使う時間
double win_t = 0;
int win = 0;
int player_win = 0;
int enemy_win = 0;

//打っている途中かどうかの判定
int hitting = 0;

//アウトの文字の表示
int out = 0;

//エースの文字の表示
int ace = 0;

//スタートを促す文字の表示
int button_s = 0;
double button_s_t = 0.0; //流したい

//サーブとそれ以外の区別
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

//面の定義
int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};

void explain() {
	puts("===========================操作方法================================================================================");
	puts("sキーでスタートします！");
	puts("矢印キー→↓←↑を使ってワンバウンドした球を打つつもりの位置まで持っていくだけで勝手に打ってくれます");
	puts("打つというよりは体に当てるつもりでいいです！");
	puts("次のポイントを始めたい時はsキーを押してください");
	puts("1ゲーム先取ノーアドバンテージ--->4点先取、もし3-3になったら先に1点とった方が勝ちです");
	puts("1-->15, 2-->30, 3-->40と表示されます");
	puts("");
	puts("");

	puts("============================備考=====================================================================================");
	puts("相手のアウトでポイントが入ります、粘りましょう！");
	puts("自分のアウト、相手のエースで相手にポイントが入ります");
	puts("時々、原因のわからなかったエラーが出ることがあります、申し訳ありません！！！");
	puts("オプション機能がいくつかあるので試してみてもらいたいです！");
	puts("enterを押す");
	puts("bキーを押す");
	puts("ファンクションキーを押すF1,F2,F3,F4");

}


//コートを描く
void drawCoat(double height)
{
	GLfloat ground[][4] = {
		{ 0.0, 0.9, 0.9, 1.0 },
		{ 0.0, 0.9, 0.9, 1.0 }
	};
	GLfloat white[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat green[] = { 0.6, 1.0, 0.1, 1.0 };
	GLfloat brown[] = { 0.5, 0.5, 0.4, 1.0 };
	//地面(左側)
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	glVertex3d(-D / 2, 0, -(3 * W) / 2);
	glVertex3d(-D / 2, 0, W / 2);
	glVertex3d(-2.5, 0, W / 2);
	glVertex3d(-2.5, 0, -(3 * W) / 2);
	glEnd();

	//地面(右側)
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	glVertex3d(2.5, 0, -(3 * W) / 2);
	glVertex3d(2.5, 0, W / 2);
	glVertex3d(D / 2, 0, W / 2);
	glVertex3d(D / 2, 0, -(3 * W) / 2);
	glEnd();

	//コート内
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glVertex3d(-2.5, 0, -14);
	glVertex3d(-2.5, 0, 4);
	glVertex3d(2.5, 0, 4);
	glVertex3d(2.5, 0, -14);
	glEnd();

	//ネットの左ポール
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 1.0, -5.0);
	glVertex3d(-2.5, 0.0, -5.0);
	glEnd();

	//ネットの右ポール
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(2.5, 1.0, -5.0);
	glVertex3d(2.5, 0.0, -5.0);
	glEnd();

	glLineWidth(1);
	//ネットの網部分
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

	glLineWidth(2); //ラインの太さ
	//ネットの上部分
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 1.0, -5.0);
	glVertex3d(-2.5, 0.9, -5.0);
	glVertex3d(2.5, 0.9, -5.0);
	glVertex3d(2.5, 1.0, -5.0);
	glEnd();

	glLineWidth(5);
	//左ライン(ダブルス)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 0.0, -14.0);
	glVertex3d(-2.5, 0.0, 4.0);
	glEnd();

	//右ライン(ダブルス)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(2.5, 0.0, -14.0);
	glVertex3d(2.5, 0.0, 4.0);
	glEnd();

	//左ライン(シングルス)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.0, 0.0, -14.0);
	glVertex3d(-2.0, 0.0, 4.0);
	glEnd();

	//右ライン(ダブルス)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(2.0, 0.0, -14.0);
	glVertex3d(2.0, 0.0, 4.0);
	glEnd();

	//サービスライン(手前)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.0, 0.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);
	glEnd();
	//サービスライン(奥)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.0, -10.0, 0.0);
	glVertex3d(2.0, -10.0, 0.0);
	glEnd();

	//サービスセンターライン(手前)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(0.0, 0.0, -5.0);
	glVertex3d(0.0, 0.0, 0.0);
	glEnd();

	//サービスセンターライン(奥)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(0.0, 0.0, -5.0);
	glVertex3d(0.0, 0.0, -10.0);
	glEnd();

	//ベースライン(手前)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 0.0, 4.0);
	glVertex3d(2.5, 0.0, 4.0);
	glEnd();

	//ベースライン(奥)
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glVertex3d(-2.5, 0.0, -14.0);
	glVertex3d(2.5, 0.0, -14.0);
	glEnd();

}

//敵の描画
void drawEnemy(void) {
	//立ち位置
	if (start == 1) {
		if (count % 2 == 0) {
			enemy_x = -1.5;
		}
		else {
			enemy_x = 1.5;
		}
	}
	
	//円錐(胴体)
	glPushMatrix();
	glTranslated(enemy_x, enemy_y, enemy_z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glutSolidCone(0.2, 1.0, 16, 8);//引数：(半径, 高さ, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();

	//直方体(右手)
	glPushMatrix();
	glTranslated(enemy_x + 0.1, enemy_y + 0.5, enemy_z);//平行移動値の設定
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

	//直方体(左手)
	glPushMatrix();
	//平行移動値の設定
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

	//球(頭)
	glPushMatrix();
	//色の設定
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(enemy_x, enemy_y + 0.8, enemy_z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glutSolidSphere(0.2, 20, 20);//引数：(半径, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();
}

//プレイヤーの描画
void drawPlayer(void) {

	//円錐(胴体)
	glPushMatrix();
	//double player_x=0.0, player_y=0.0, player_z=4.0;はグローバル変数
	glTranslated(player_x, player_y, player_z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	//引数：(半径, 高さ, Z軸まわりの分割数, Z軸に沿った分割数)
	glutSolidCone(0.2, 1.0, 16, 8);
	glPopMatrix();

	//直方体(右手)
	glPushMatrix();
	//平行移動値の設定
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

	//直方体(左手)
	glPushMatrix();
	//平行移動値の設定
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

	//球(頭)
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0); //色の設定
	glTranslated(player_x, player_y + 0.8, player_z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glutSolidSphere(0.2, 20, 20);//引数：(半径, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();

}

//敵が打つ関数
void enemy_stroke() {

	//サーブの方向：サーブは左右に打ち分けたい
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
		//ストロークの振り分け
		my_course_x2 = rand() % 10 + 1;
		if (enemy_x >= 0) {
			if (my_course_x2 % 3 == 0) {
				//きつめのクロス
				my_course_x2 = 3.5;
			}
			else if (my_course_x2 % 3 == 1) {
				//ゆるめのクロス
				my_course_x2 = 2;
			}
			else if (my_course_x2 % 3 == 2) {
				//ストレート
				my_course_x2 = 0.5;
			}
		}
		else {
			if (my_course_x2 % 3 == 0) {
				//きつめのクロス
				my_course_x2 = -3.5;
			}
			else if (my_course_x2 % 3 == 1) {
				//ゆるめのクロス
				my_course_x2 = -2;
			}
			else if (my_course_x2 % 3 == 2) {
				//ストレート
				my_course_x2 = -1;
			}
		}

		//ベースラインを超えないための工夫
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
		//バウンド判定
		if ((abs(py) - R) <= 0) {
			bound = 1;
			if (px > 2 || px < -2 || py < -5 || py > 4) {
				printf("アウト");
				out = 1;
				button_s = 1;
				my_score += 15;
				count++;
				//わかりやすいように立ち位置をポイントが始まる前に変えておく
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

//プレイヤーのショット
void my_stroke() {
	//サーブからストロークへ
	serve++;
	//当たり判定
	double return_x, return_y, return_z;

	if (player_ball == 1) {
		if (pz >= 4.5) {
			//当たり判定
			//if (abs(px - player_x)<2 && abs(py - player_y)<2 && (abs(pz - player_z)<2) ){
			if (abs(px - player_x)<1 && abs(py - player_y)<1 && (abs(pz - player_z)<2)) {
				atari = 1;
				serve_x = px;
				serve_y = py;
				serve_z = pz;
			}
			//ボールに追いつかなかったとき
			else {
				printf("エース"); 
				ace = 1;
				button_s = 1;
				enemy_score += 15;
				count++;
				//わかりやすいように立ち位置をポイントが始まる前に変えておく
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

			//バウンド判定
			if ((abs(return_y) - R) <= 0) {
				return_bound_x = return_x, return_bound_y = return_y, return_bound_z = return_z;
				bound = 2;
				//アウト判定
				if (return_x > 2 || return_x < -2 || return_y < -14 ) {
					printf("アウト");
					out = 1;
					enemy_score += 15;
					button_s = 1;
					count++;
					//わかりやすいように立ち位置をポイントが始まる前に変えておく
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

// 画面表示
void display(void)
{
	//画面クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//モデルビュー変換行列の初期化 
	glLoadIdentity();
	//光源の位置を設定 
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	//スタート画面
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
	//ゲーム画面
	if (game_screen) {
		//視点の移動（物体の方を奥に移す）
		glTranslated(0.0, -QY, -D + kakudo);
		//視点が動くのか実験
		if (kaiten == 1) {
			glTranslated(0.0 + kaiten_t, -QY, -D);
		}
		if (win == 1) {
			glTranslated(0.0, -QY, -D - win_t);
		}
		//アウトの表示
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
		//エースの表示
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
		//sボタンを押すように促す文字
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
		//コートの描画
		drawCoat(0.0);
		//敵のストローク
		enemy_stroke();
		//自分のストローク
		my_stroke();
		drawPlayer();
		drawEnemy();
		//点数の表示
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		//敵の点数
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
		//自分の点数
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

		//自分か敵のどっちかが勝ったらresult画面へ
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

	//全体が前の色になるのを防ぐ
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glFlush();
}


void resize(int w, int h)
{
	//ウィンドウ全体をビューポートにする 
	glViewport(0, 0, w, h);
	//透視変換行列の指定 
	glMatrixMode(GL_PROJECTION);
	//透視変換行列の初期化 
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	//モデルビュー変換行列の指定
	glMatrixMode(GL_MODELVIEW);

}

//キーボード関数
void keyboard(unsigned char key, int x, int y)
{
	//ESC か q をタイプしたら終了 
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

//idle関数
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

	//視点を移動させる
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
	
	//再描画
	glutPostRedisplay();
}

//矢印キー
void specialkeydown(int key, int x, int y) {
	if (key == GLUT_KEY_UP) //上
	{
		player_z -= 0.1;
		//視点の移動
		//kakudo += 0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN) //下
	{
		player_z += 0.1;
		//kakudo-=0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_LEFT) //左
	{
		player_x -= 0.1;
		//kakudo-=0.1;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_RIGHT) //右
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
	///初期設定 
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


