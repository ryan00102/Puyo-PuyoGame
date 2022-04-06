#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>

// COSE101, Spring Semester, 2019
// Computer Science and Engineering, College of Informatics, Korea University, Seoul.

#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32 
#define p 112 
#define P 80 
#define ESC 27

#define MAP_ADJ_X 10
#define MAP_ADJ_Y 5
#define X 8
#define Y 5

typedef struct _block {
	int pos_x; //position of block
	int pos_y;
	int num;
	int nextnum;
	int isactive;
}Block;

Block block, block2;

/* 'DO NOT MODIFY THESE FUNCTIONS.'		'�� �Լ����� ��ġ�� ������.'		 */
void removeCursorFromCMD();
void setCoordinate(int x, int y); //cmd���� Ŀ���� x, y ��ġ�� ����

								  /* display fuctions */
void goMainMenuScreen(); // ���θ޴��� �̵� Moving to main menu.
void printGameScreen();  // ����ȭ�� ���	 Printing game screen.
void printPauseScreen(); // �Ͻ� ���� ȭ��	 Prining pause screen.
void printEndScreen(int endType); //  // �������� ���� ȭ�� ���. ��������Ŭ����, ��罺������Ŭ����, �й�.
									//Printing result of end of stages including 'cleared the stage', 'cleared whole stages', and 'lost'.
void clearScreen();
/* 'DO NOT MODIFY THESE FUNCTIONS.' ends	'�� �Լ����� ��ġ�� ������' ��.	*/

		/* @ --- You can modify following functions ----  �� �Ʒ����ִ� �Լ����� ��ġ����.  */
//Implement these functions below to complete your project.
//�� �Լ����� �����ϼż� ������Ʈ�� �ϼ��ϼ���.

		/* Block generating functions */
int getRandomNumber();
void newBlock();

/* block control and merging functions  */
int takeBlockControl();				//���� ���� ���� �Է� ����			Taking input for moving blocks
void flipBlock();					// Fliping function.
void moveBlock(int direction);		// �Է� ���� �������� ���� �̵�		Moving blocks to corresponding direction of input key.
int checkAdjacentBlock(int, int);	//Checking adjacent blocks for merging conditions
void checkNumber(int, int);			// ���� ���� ���ϼ��� Ȯ��			Checking number of adjacent block

		/* game flow control functions */
int isStageEnd();  // ���������� �������� üũ. (�������� Ŭ����, ��� �������� Ŭ����, �й�)         Checking condition for end of the stage. (stage clear, all stage clear, lost)
void setGameFlow(int type); // �� ���������� �´� ���� ȯ�� ����.   Setting up status values for each stages.




int time_interval_moveBlockDown = 100;
int goal = 64;
int currentStage = 0;
int score = 0;
int best_score = 0;
int gameScreen[X][Y] = { 0 };

void main() {
	system("mode con cols=120 lines=38");
	srand(time(NULL));
	removeCursorFromCMD();
	goMainMenuScreen();

	while (1) {

		for (int j = 0; j < 5; j++) {
			if (takeBlockControl() == SPACE) break;
			printGameScreen();
			Sleep(time_interval_moveBlockDown);
		}
		moveBlock(DOWN);
		if (!block.isactive && !block2.isactive) { // �� �κ��� �������� ������ �ٴ��̳� �ٸ����Ͽ� ��Ҵ��� üũ�մϴ�. This statement is cheking that wether the falling blocks got touched by floor or other blocks.
			checkNumber(block.pos_x, block.pos_y);
			if (isStageEnd() != 1)
				newBlock();
		}
	}
}

int getRandomNumber() {
	int i;
	srand((unsigned)time(NULL));
	i = rand() % 10;
	if (i < 5) {
		return 2;
	}
	else if (i < 8 && i >= 5) {
		return 4;
	}
	else {
		return 8;
	}
	
}

char getRandomOper() {
	int i;
	srand((unsigned)time(NULL));
	i = rand() % 2;
	if (i = 1) {
		return '+';
	}
	else {
		return '-';
	}

}

void newBlock() {
	
	*/
	int i;
	srand((unsigned)time(NULL));
	i = rand() % 4;
	
	block.num = getRandomNumber(); 
	block2.num = getRandomOper();  

	block.pos_x = 1; 
	block.pos_y = i; 
	block.isactive = 1;
	gameScreen[block.pos_x][block.pos_y] = block.num;

	block2.pos_x = 1; 
	block2.pos_y = i+1; 
	block2.isactive = 1;
	gameScreen[block2.pos_x][block2.pos_y] = block2.num;
}

int takeBlockControl() {
	int input_blockControl = 0;

	if (_kbhit()) {
		input_blockControl = _getch();
		if (input_blockControl == 224 && block.isactive && block2.isactive) { 
			do { input_blockControl = _getch(); } while (input_blockControl == 224);
			switch (input_blockControl) {
			case UP:
				flipBlock();
				break;
			case LEFT :
				moveBlock(LEFT);
				break;
			case RIGHT :
				moveBlock(RIGHT);
				break;
			case DOWN :
				moveBlock(DOWN);
			
			}
		}
		else { 
			switch (input_blockControl) {
			case SPACE :
			
				
				while (block.isactive != 0 && block2.isactive != 0) {
					if (block.pos_x < X - 1 && gameScreen[block.pos_x + 1][block.pos_y] == 0) {
						gameScreen[block.pos_x + 1][block.pos_y] = block.num;
						gameScreen[block.pos_x][block.pos_y] = 0;
						block.pos_x++;
					}
					else {
						block.isactive = 0;
					}

					if (block2.pos_x < X - 1 && gameScreen[block2.pos_x + 1][block2.pos_y] == 0) {
						gameScreen[block2.pos_x + 1][block2.pos_y] = block2.num;
						gameScreen[block2.pos_x][block2.pos_y] = 0;
						block2.pos_x++;
					}
					else {
						block2.isactive = 0;
					}
				}
				score += 5;

				break;
			case P:
			case p:
				printPauseScreen();
				break;
			case ESC:
				printEndScreen(0);
				break;
			}
		}
	}
	while (_kbhit()) _getch(); 
	return 0;
}

void flipBlock(void) {
		
	int temp;
	temp = block2.num;
	block2.num = block.num;
	block.num = temp;
	
	
}

void moveBlock(int direction) { 
	switch (direction) {
	case LEFT:
		
		if (block.pos_y>0&&block.pos_y < Y - 1 && gameScreen[block.pos_x][block.pos_y-1] == 0) {
			gameScreen[block.pos_x][block.pos_y-1] = block.num;
			gameScreen[block.pos_x][block.pos_y] = 0;
			block.pos_y--;
		}


		if (block2.pos_y>=0&&block2.pos_y < Y - 1 && gameScreen[block2.pos_x][block2.pos_y-1] == 0) {
			gameScreen[block2.pos_x][block2.pos_y-1] = block2.num;
			gameScreen[block2.pos_x][block2.pos_y] = 0;
			block2.pos_y--;
		}

		break;
	case RIGHT:
		
		if (block.pos_y > 0 && block.pos_y < Y - 1 && gameScreen[block.pos_x][block.pos_y - 1] == 0) {
			gameScreen[block.pos_x][block.pos_y + 1] = block.num;
			gameScreen[block.pos_x][block.pos_y] = 0;
			block.pos_y++;
		}
	
		if (block2.pos_y >= 0 && block2.pos_y < Y - 1 && gameScreen[block2.pos_x][block2.pos_y - 1] == 0) {
			gameScreen[block2.pos_x][block2.pos_y + 1] = block2.num;
			gameScreen[block2.pos_x][block2.pos_y] = 0;
			block2.pos_y++;
		}

	case DOWN:
		if (block.pos_x < X - 1 && gameScreen[block.pos_x + 1][block.pos_y] == 0) {
			gameScreen[block.pos_x + 1][block.pos_y] = block.num;
			gameScreen[block.pos_x][block.pos_y] = 0;
			block.pos_x++;
		}
		else {
			block.isactive = 0;
		}

		if (block2.pos_x < X - 1 && gameScreen[block2.pos_x + 1][block2.pos_y] == 0) {
			gameScreen[block2.pos_x + 1][block2.pos_y] = block2.num;
			gameScreen[block2.pos_x][block2.pos_y] = 0;
			block2.pos_x++;
		}
		else {
			block2.isactive = 0;
		}
	}
}

int checkAdjacentBlock(int x, int y) { 
	
	
	if (gameScreen[x][y + 1] == '+' || gameScreen[x][y + 1] == '-') {
		if (1 < gameScreen[x][y + 2] && gameScreen[x][y+2] < 9 && 1 < gameScreen[x][y] && gameScreen[x][y]< 9) {

			if (gameScreen[x][y + 1] = '+') {
				gameScreen[x][y] += gameScreen[x][y+2];
				gameScreen[x][y+1] = 0;
				gameScreen[x][y + 2] = 0;
			}
			if (gameScreen[x][y + 1] = '-') {
				gameScreen[x][y] = abs(gameScreen[x][y] - gameScreen[x][y + 2]);
				gameScreen[x][y] = 0;
				gameScreen[x][y + 2] = 0;
			}
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	

	if (gameScreen[x][y] == 64) {
		score += 10;
		gameScreen[x][y] = 0;
	}
	
	
}

void checkNumber(int x, int y) {

	checkAdjacentBlock(x, y);
	printGameScreen();
	Sleep(200);

	for (int i = X - 1; i > 0; i--) {
		for (int j = 0; j < Y-2; j++) {
			if (checkAdjacentBlock(i, j)) {
				printGameScreen();
				Sleep(200);
				i = X;
				break;
			}
		}
	}
}

void setGameFlow(int setGameFlowType) {
	switch (setGameFlowType) {
	case 0: 
		if (best_score < score)
			best_score = score;

		currentStage = 0;
		score = 0;

	case 1: 
		currentStage++;

		switch (currentStage) {
		case 1:
			time_interval_moveBlockDown = 100;
			goal = 100;
			break;
		case 2:
			time_interval_moveBlockDown = 130;
			goal = 300;
			break;
		case 3:
			time_interval_moveBlockDown = 150;
			goal = 500;
			break;
		case 4:
			time_interval_moveBlockDown = 170;
			goal = 600;
			break;
		case 5:
			time_interval_moveBlockDown = 200;
			goal = 750;
			break;
		case 6:
			time_interval_moveBlockDown = 250;
			goal = 850;
			break;
		}
		clearScreen();
		newBlock();
		break;

	default:
		clearScreen();
		setCoordinate(MAP_ADJ_X + 2, MAP_ADJ_Y + 13); printf(" @System error: state end condition currupted.");
		exit(0);
	}
}

int isStageEnd() { 
	for (int i = X - 1; i > 1; i--) {
		for (int j = 0; j < Y; j++) {
			if (score >= goal) {
				currentStage < 10 ? printEndScreen(1) : printEndScreen(2);
				return 1;
			}
		}
	}
	for (int i = 0; i < Y; i++) {
		if (gameScreen[0][i] != 0) { 
			printEndScreen(0);
			return 1;
		}
	}
	return 0;
}



void removeCursorFromCMD() { 
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void setCoordinate(int x, int y) {
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printGameScreen() {
	int i, j, k;

	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3));
			if (gameScreen[i][j] == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				if (i == 0) {
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) - 1);
					printf("             ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3));
					printf("     ��      ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 1);
					printf("             ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 2);
					printf("-------------");
				}
				else {
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3));
					printf("             ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 1);
					printf("     ��      ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 2);
					printf("             ");
				}
			}

			else {
				for (k = 0; k < 12;) if (1 << (++k) == gameScreen[i][j]) break;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k + 1);
				if (gameScreen[i][j] == 45 || gameScreen[i][j] == 43)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

				if (i == 0) {
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) - 1);
					printf("���������������������� ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3));
					if (gameScreen[i][j] == 45)
						printf("   %4c", gameScreen[i][j]);
					else if (gameScreen[i][j] == 43)
						printf("   %4c", gameScreen[i][j]);
					else if (gameScreen[i][j] == 999)
						printf("      *", gameScreen[i][j]);
					else
						printf("   %4d", gameScreen[i][j]);
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 1);
					printf("���������������������� ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 2);

				}
				else {
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3));
					printf("����������������������  ");
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 1);
					if (gameScreen[i][j] == 45)
						printf("   %4c", gameScreen[i][j]);
					else if (gameScreen[i][j] == 43)
						printf("   %4c", gameScreen[i][j]);
					else if (gameScreen[i][j] == 999)
						printf("      *", gameScreen[i][j]);
					else
						printf("   %4d", gameScreen[i][j]);
					setCoordinate(MAP_ADJ_X + (j * 6), MAP_ADJ_Y + (i * 3) + 2);
					printf("����������������������  ");
				}

			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y); printf(" Stage : %4d", currentStage);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 1); printf(" GOAL  : %4d", goal);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 2); printf(" SPEED  : %.1f", 100.0 / (float)time_interval_moveBlockDown);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 3); printf("+-  N E X T  -+ ");
	for (k = 0; k < 12;) if (1 << (++k) == block.nextnum) break;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k + 1);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 4); printf("  ����������������������    ");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 5); printf("     %4d    ", block.nextnum);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 6); printf("  ����������������������    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 7); printf("  ����������������������    ");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 8); printf("     %4c    ", block2.nextnum);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 9); printf("  ����������������������    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 10); printf("+-- -  -  - --+ ");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 11); printf(" YOUR SCORE :");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 12); printf("        %6d", score);
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 13); printf(" BEST SCORE :");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 14); printf("        %6d", best_score);

	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 15); printf("  ��   : Flip");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 16); printf("��  �� : Left / Right");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 17); printf("  ��   : Soft Drop ");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 18); printf(" SPACE : Hard Drop");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 19); printf("   P   : Pause");
	setCoordinate(MAP_ADJ_X + 32, MAP_ADJ_Y + 20); printf("  ESC  : Quit");

}

void goMainMenuScreen() { 
	int x = 19;
	int y = 9;
	int input_command = 0;

	setCoordinate(x, y + 2); printf("��������������������������������������������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("�� ��������������������������������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("o �� ��������������������������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("yo �� ������������������������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("yoPuyo �� ������������������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("PuyoPuyo �� ����������������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("�� 64 PuyoPuyo �٦���������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("������ 64 PuyoPuyo �� ������������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("�������� 64 PuyoPuyo �� ����������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("����������  64 PuyoPuyo �� ������������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("��������������  64 PuyoPuyo �� ��������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("����������������  64 PuyoPuyo �� ������������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("������������������  64 PuyoPuyo �� ����������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("��������������������  64 PuyoPuyo �� ��������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("����������������������  64 PuyoPuyo �� ������������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("������������������������  64 PuyoPuyo �� ����������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("��������������������������  64 PuyoPuyo �� ��������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("����������������������������  64 PuyoPuyo �� ������");
	Sleep(30);
	setCoordinate(x, y + 2); printf("������������������������������  64 PuyoPuyo �� ����");
	Sleep(30);
	setCoordinate(x, y + 2); printf("��������������������������������  64 PuyoPuyo �� ��");


	setCoordinate(x + 2, y + 4); printf(" Press any key to start");

	setCoordinate(x, y + 6);  printf(" �ǢǢǢ� HOW TO CONTROL �ǢǢǢ�");
	setCoordinate(x, y + 7);  printf(" ��                            ��");
	setCoordinate(x, y + 8);  printf(" ��      ��   : Flip           ��");
	setCoordinate(x, y + 9); printf(" ��    ��  �� : Left / Right   ��");
	setCoordinate(x, y + 10); printf(" ��      ��   : Soft Drop      ��");
	setCoordinate(x, y + 11); printf(" ��    SPACE  : Hard Drop      ��");
	setCoordinate(x, y + 12); printf(" ��      P    : Pause          ��");
	setCoordinate(x, y + 13); printf(" ��     ESC   : Quit           ��");
	setCoordinate(x, y + 14); printf(" ��                            ��");
	setCoordinate(x, y + 15); printf(" �ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");

	setCoordinate(x, y + 16); printf("          ESC: Exit game.     ");



	while (_kbhit())
		_getch();
	input_command = _getch();


	if (input_command == ESC) {
		clearScreen();
		exit(0);
	}
	else
		setGameFlow(0); 

}

void printPauseScreen() { 
	int x = MAP_ADJ_X + 8;
	int y = MAP_ADJ_Y + 5;

	setCoordinate(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	setCoordinate(x, y + 1); printf("��                              ��");
	setCoordinate(x, y + 2); printf("��  +-----------------------+   ��");
	setCoordinate(x, y + 3); printf("��  |       P A U S E       |   ��");
	setCoordinate(x, y + 4); printf("��  +-----------------------+   ��");
	setCoordinate(x, y + 5); printf("��   Press any key to resume.   ��");
	setCoordinate(x, y + 6); printf("��                              ��");
	setCoordinate(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");

	_getch();

	system("cls");
	printGameScreen();
}



void printEndScreen(int endType) {
	int input_command = 0;
	int x = MAP_ADJ_X + 8;

	switch (endType) {
	case 0:
		setCoordinate(x, MAP_ADJ_Y + 5);  printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		setCoordinate(x, MAP_ADJ_Y + 6);  printf("��                              ��");
		setCoordinate(x, MAP_ADJ_Y + 7);  printf("��  +-----------------------+   ��");
		setCoordinate(x, MAP_ADJ_Y + 8);  printf("��  |  G A M E  O V E R..   |   ��");
		setCoordinate(x, MAP_ADJ_Y + 9);  printf("��  +-----------------------+   ��");
		setCoordinate(x, MAP_ADJ_Y + 10); printf("��   YOUR SCORE: %6d         ��", score);
		setCoordinate(x, MAP_ADJ_Y + 11); printf("��                              ��");
		setCoordinate(x, MAP_ADJ_Y + 12); printf("��   Press any key to restart.  ��");
		setCoordinate(x, MAP_ADJ_Y + 13); printf("��                              ��");
		setCoordinate(x, MAP_ADJ_Y + 14); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		setCoordinate(x, MAP_ADJ_Y + 16); printf("      ESC: Back to main menu.     ");

		while (_kbhit()) _getch();
		input_command = _getch();

		if (input_command == ESC) {
			while (_kbhit()) _getch();
			clearScreen();
			goMainMenuScreen();
			return;
		}

		setGameFlow(0); 
		break;

	case 1:
		setCoordinate(x, MAP_ADJ_Y + 5);  printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		setCoordinate(x, MAP_ADJ_Y + 6);  printf("��                              ��");
		setCoordinate(x, MAP_ADJ_Y + 7);  printf("��  +-----------------------+   ��");
		setCoordinate(x, MAP_ADJ_Y + 8);  printf("��  |      STAGE CLEAR      |   ��");
		setCoordinate(x, MAP_ADJ_Y + 9);  printf("��  +-----------------------+   ��");
		setCoordinate(x, MAP_ADJ_Y + 10); printf("��   YOUR SCORE: %6d         ��", score);
		setCoordinate(x, MAP_ADJ_Y + 11); printf("��                              ��");
		setCoordinate(x, MAP_ADJ_Y + 12); printf("�� Press any key to next stage. ��");
		setCoordinate(x, MAP_ADJ_Y + 13); printf("��                              ��");
		setCoordinate(x, MAP_ADJ_Y + 14); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");

		while (_kbhit()) _getch();
		input_command = _getch();

		setGameFlow(1); 
		break;

	case 2:
		setCoordinate(x, MAP_ADJ_Y + 5);  printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		setCoordinate(x, MAP_ADJ_Y + 6);  printf("��                                      ��");
		setCoordinate(x, MAP_ADJ_Y + 7);  printf("��  +-------------------------------+   ��");
		setCoordinate(x, MAP_ADJ_Y + 8);  printf("��  | WINNER WINNER CHICKEN DINNER! |   ��");
		setCoordinate(x, MAP_ADJ_Y + 9);  printf("��  +-------------------------------+   ��");
		setCoordinate(x, MAP_ADJ_Y + 10); printf("��         YOUR SCORE: %6d           ��", score);
		setCoordinate(x, MAP_ADJ_Y + 11); printf("��                                      ��");
		setCoordinate(x, MAP_ADJ_Y + 12); printf("��         Cleared final stage.         ��");
		setCoordinate(x, MAP_ADJ_Y + 13); printf("��                                      ��");
		setCoordinate(x, MAP_ADJ_Y + 14); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");

		while (_kbhit()) _getch();
		input_command = _getch();
		setGameFlow(0); 
		break;

	default:
		clearScreen();
		setCoordinate(x, MAP_ADJ_Y + 13); printf(" @System error: state end condition currupted.");
		exit(0);
	}
}
void clearScreen() {
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			gameScreen[i][j] = 0;
		}
	}
	block.pos_x = 0;
	block.pos_x = 0;
	block.num = 0;
	block.nextnum = 0;
	block.isactive = 0;

	block2.pos_x = 0;
	block2.pos_x = 0;
	block2.num = 0;
	block2.nextnum = 0;
	block2.isactive = 0;

	system("cls");
}
