﻿#include "AIE.h"
#include <iostream>
#include <fstream>
using namespace std;
float screenWidth = 800.f;
float screenHeight = 800.f;
int player1Score = 0;
int player2Score = 0;
int mainMenu;
char player1String[10];
char player2String[10];
char gameMenu[30] = "Main Menu";
char highScores[30] = "Press E for Highscores";
char quit[30] = "Press R to Quit";
char toStart[30] = "Press T to Start";
char restart[30] = "Press Y for Main Menu";
char player1Win[30] = "Player 1 Wins";
char player2Win[30] = "Player 2 Wins";
char gameOver[30] = "Game Over";
int totalWinsP1 = 0;
int totalWinsP2 = 0;
char total1String[30];
char total2String[30];
char total[10] = "Total";

enum GAMESTATE
{
	MAINMENU,
	GAMESTART,
	PLAYER1WIN,
	PLAYER2WIN,
	HIGHSCORES,
};
struct PongPaddle
{
	unsigned int paddleSprite; //image of the paddle
	float paddleX; //x position of the paddle
	float paddleY; //y position of the paddle
	float paddleWidth = screenWidth*.05;  //horizontal length of paddle
	float paddleHeight = screenHeight*.2; //vertical length of paddle
	float paddleUpperBoundary;
	float paddleLowerBoundary;
	float paddleRightBoundary;
	float paddleLeftBoundary;

};

struct PongBall
{
	unsigned int ballSprite;  //image of the pong ball
	float ballX; //x position of ball
	float ballY; //y position of ball
	float ballXSpeed;
	float ballYSpeed;
	float ballWidth = screenWidth*.03; //horizontal ball width
	float ballHeight = screenHeight*.03;  //vertical ball width
	float ballUpperBoundary;
	float ballLowerBoundary;
	float ballRightBoundary;
	float ballLeftBoundary;
};
struct Wall
{
	unsigned int wallSprite;
	float wallWidth = screenWidth;
	float wallHeight = screenHeight*.025;
	float wallX;// I set the wall position when i drew the sprite later in the code
	float wallY;
	float wallUpperBoundary;
	float wallLowerBoundary;
	float wallRightBoundary;
	float wallLeftBoundary;
};

int main(int argc, char* argv[])
{
	Initialise(800, 800, false, "Pong Project");
	SetBackgroundColour(SColour(0, 0, 0, 255));
	
	PongPaddle paddle1;
	paddle1.paddleSprite = CreateSprite("./images/pongball.png", paddle1.paddleWidth, paddle1.paddleHeight, true);
	paddle1.paddleX = screenWidth *.05;
	paddle1.paddleY = screenHeight*.5;
	


	PongPaddle paddle2;
	paddle2.paddleSprite = CreateSprite("./images/pongball.png", paddle2.paddleWidth, paddle2.paddleHeight, true);
	paddle2.paddleX = screenWidth *.95;
	paddle2.paddleY = screenHeight*.5;
	


	PongBall ball;
	ball.ballSprite = CreateSprite("./images/pongball.png", ball.ballWidth, ball.ballHeight, true);
	ball.ballX = screenWidth*.5;
	ball.ballY = screenHeight*.5;
	ball.ballXSpeed = screenWidth*.00025;
	ball.ballYSpeed = screenHeight*.000125;
	

	Wall upperWall;
	upperWall.wallSprite = CreateSprite("./images/pongball.png", upperWall.wallWidth, upperWall.wallHeight, true);
	upperWall.wallX = screenWidth*.5;
	upperWall.wallY = screenHeight * .9;
	


	Wall lowerWall;
	lowerWall.wallSprite = CreateSprite("./images/pongball.png", lowerWall.wallWidth, lowerWall.wallHeight, true);
	lowerWall.wallX = screenWidth*.5;
	lowerWall.wallY = screenHeight*.1;

	
	
	GAMESTATE currentState = MAINMENU;

	do
	{
		fstream file;
		file.open("./highscore/hiscore1.txt", ios_base::out);
		file << total1String << total2String << endl;
		file.close();
		//placeholder images
		/*MoveSprite(pongBall, screenWidth*.5, screenHeight*.5);
		DrawSprite(pongBall);
		MoveSprite(pongPaddle, screenWidth*.05, screenHeight*.5);
		DrawSprite(pongPaddle);
		MoveSprite(pongPaddle, screenWidth*.95, screenHeight*.5);
		DrawSprite(pongPaddle);*/
		itoa(totalWinsP1, total1String, 10);
		itoa(totalWinsP2, total2String, 10);
		itoa(player1Score, player1String, 10);
		itoa(player2Score, player2String, 10);
		switch (currentState)
		{
		case MAINMENU:

			DrawString (gameMenu, screenWidth*.4, screenHeight*.75);
			DrawString(toStart, screenWidth*.4, screenHeight*.6);
			DrawString(highScores, screenWidth*.4, screenHeight*.5);
			DrawString(quit, screenWidth*.4, screenHeight*.4);
			if (IsKeyDown('E'))
			{
				currentState = HIGHSCORES;
			}

			if (IsKeyDown('R'))
			{
				Shutdown();
			}
			if (IsKeyDown('T'))
			{
				currentState = GAMESTART;
			}
			
			break;

		case GAMESTART:
			

			ball.ballUpperBoundary = ball.ballY + ball.ballHeight*.5;
			ball.ballLowerBoundary = ball.ballY - ball.ballHeight*.5;
			ball.ballRightBoundary = ball.ballX + (ball.ballWidth*.5);
			ball.ballLeftBoundary = ball.ballX - (ball.ballWidth*.5);//setting boundaries so the ball can determine when it hits a wall

			paddle1.paddleUpperBoundary = paddle1.paddleY + paddle1.paddleHeight*.5;
			paddle1.paddleLowerBoundary = paddle1.paddleY - paddle1.paddleHeight*.5;
			paddle1.paddleRightBoundary = paddle1.paddleX + paddle1.paddleWidth*.5 - screenWidth * .025; //i had to subtract .025 screenwidth here because of the initial position i put it in was at .95
			paddle1.paddleLeftBoundary = paddle1.paddleX - paddle1.paddleWidth*.5 + screenWidth * .025;

			paddle2.paddleUpperBoundary = paddle2.paddleY + paddle2.paddleHeight*.5;
			paddle2.paddleLowerBoundary = paddle2.paddleY - paddle2.paddleHeight*.5;
			paddle2.paddleRightBoundary = paddle2.paddleX + paddle2.paddleWidth*.5 - screenWidth * .025;
			paddle2.paddleLeftBoundary = paddle2.paddleX - paddle2.paddleWidth*.5 + screenWidth * .025;

			upperWall.wallUpperBoundary = upperWall.wallY + upperWall.wallHeight*.5;
			upperWall.wallLowerBoundary = upperWall.wallY - upperWall.wallHeight*.5;
			upperWall.wallRightBoundary = upperWall.wallX + upperWall.wallWidth*.5;
			upperWall.wallLeftBoundary = upperWall.wallX - upperWall.wallWidth*.5;

			lowerWall.wallUpperBoundary = lowerWall.wallY + lowerWall.wallHeight*.5;
			lowerWall.wallLowerBoundary = lowerWall.wallY - lowerWall.wallHeight*.5;
			lowerWall.wallRightBoundary = lowerWall.wallX + lowerWall.wallWidth*.5;
			lowerWall.wallLeftBoundary = lowerWall.wallX + lowerWall.wallWidth*.5;
			//this stuff goes into PongPaddle paddle1
			MoveSprite(paddle1.paddleSprite, screenWidth*.025, paddle1.paddleY);
			DrawSprite(paddle1.paddleSprite);
			//same but paddle2
			MoveSprite(paddle2.paddleSprite, screenWidth*.975, paddle2.paddleY);
			DrawSprite(paddle2.paddleSprite);

			MoveSprite(ball.ballSprite, ball.ballX, ball.ballY);
			DrawSprite(ball.ballSprite);

			MoveSprite(upperWall.wallSprite, upperWall.wallX, upperWall.wallY);
			DrawSprite(upperWall.wallSprite);

			MoveSprite(lowerWall.wallSprite, lowerWall.wallX, lowerWall.wallY);
			DrawSprite(lowerWall.wallSprite);

			//player 1 and player 2 score
			DrawString(player1String, screenWidth*.33, screenHeight*.95);
			DrawString(player2String, screenWidth*.66, screenHeight*.95);

			ball.ballX = (ball.ballX + ball.ballXSpeed);
			ball.ballY = (ball.ballY + ball.ballYSpeed);
			//    a * a + b * b


			if (ball.ballRightBoundary > paddle2.paddleLeftBoundary)
			{
				if (ball.ballY < paddle2.paddleUpperBoundary)
				{
					if (ball.ballY > paddle2.paddleLowerBoundary)
					{
						ball.ballXSpeed = -ball.ballXSpeed;
						ball.ballX = paddle2.paddleLeftBoundary - ball.ballWidth*.5;
					}
				}

			}

			if (ball.ballLeftBoundary < paddle1.paddleRightBoundary)
			{
				if (ball.ballY < paddle1.paddleUpperBoundary)
				{
					if (ball.ballY > paddle1.paddleLowerBoundary)
					{
						ball.ballXSpeed = -ball.ballXSpeed;
						ball.ballX = paddle1.paddleRightBoundary + ball.ballWidth*.5;
					}
				}

			}
			//this stuff makes the y axis speed reverse
			if (ball.ballUpperBoundary > upperWall.wallLowerBoundary)
			{
				ball.ballYSpeed = -ball.ballYSpeed;
				ball.ballY = upperWall.wallLowerBoundary - ball.ballHeight*.5;
			}
			if (ball.ballLowerBoundary < lowerWall.wallUpperBoundary)
			{
				ball.ballYSpeed = -ball.ballYSpeed;
				ball.ballY = lowerWall.wallUpperBoundary + ball.ballHeight*.5;
			}

			//this part makes the score increase if the ball goes over the edge of the screen

			if (ball.ballX > screenWidth)
			{
				ball.ballXSpeed = -ball.ballXSpeed;
				player1Score += 1;
				ball.ballX = screenWidth*.5;
				ball.ballY = screenHeight*.5;
			}

			if (ball.ballX < 0)
			{
				ball.ballXSpeed = -ball.ballXSpeed;
				player2Score += 1;
				ball.ballX = screenWidth * .5;
				ball.ballY = screenHeight * .5;
			}
			//as long as Q is held down the y axis increases by two based on cpu power unless I set a distance per time to it
			if (IsKeyDown('Q'))
			{
				paddle1.paddleY += .5f;
				if (paddle1.paddleY > ((screenHeight*.9) - (paddle1.paddleHeight*.5)))
				{
					paddle1.paddleY = ((screenHeight*.9) - (paddle1.paddleHeight*.5));
				}
			}
			if (IsKeyDown('A'))
			{
				paddle1.paddleY -= .5f;
				if (paddle1.paddleY < ((screenHeight*.1) + (paddle1.paddleHeight*.5)))
				{
					paddle1.paddleY = (screenHeight*.1) + (paddle1.paddleHeight*.5);
				}
			}
			if (IsKeyDown('O'))
			{
				paddle2.paddleY += .5;
				if (paddle2.paddleY >((screenHeight*.9) - (paddle2.paddleHeight*.5)))
				{
					paddle2.paddleY = ((screenHeight*.9) - (paddle1.paddleHeight*.5));
				}
			}
			if (IsKeyDown('L'))
			{
				paddle2.paddleY -= .5f;
				if (paddle2.paddleY < ((screenHeight*.1) + (paddle2.paddleHeight*.5)))
				{
					paddle2.paddleY = (screenHeight*.1) + paddle2.paddleHeight*.5;
				}
			}


			//debug button scores V and B insta win
			if (IsKeyDown('V'))
			{
				player1Score += 1;
			}
			if (IsKeyDown('B'))
			{
				player2Score += 1;
			}
			//this tells the game that if the score gets to 5 someone has won
			if (player1Score == 5)
			{
				totalWinsP1 += 1;//total wins are increased by 1 for player 1 and saved to the text file
				currentState = PLAYER1WIN;
			}
			if (player2Score == 5)
			{
				
				totalWinsP2 += 1;
				currentState = PLAYER2WIN;
			}
			break;
			//hitting e sends you here 
			case HIGHSCORES:
				
				DrawString (total1String, screenWidth*.20, screenHeight*.6);
				DrawString (total2String, screenWidth*.75, screenHeight*.6);
				if (IsKeyDown('Y'))
				{
					currentState = MAINMENU;
				}

				break;

			//the gameover screen that resets the score
			case PLAYER1WIN:
			{
								DrawString(gameOver, screenWidth*.4, screenHeight*.8);
								DrawString(player1Win, screenWidth*.40, screenHeight*.7);
								DrawString(restart, screenWidth*.4, screenHeight*.6);
								
								if (IsKeyDown('Y'))
								{
									currentState = MAINMENU;
									player1Score = 0;
									player2Score = 0;
								}
			};
				break;
			case PLAYER2WIN: //these add points to the players total victory score
			{
								DrawString(gameOver, screenWidth*.4, screenHeight*.8);
								DrawString(player2Win, screenWidth*.40, screenHeight*.7);
								DrawString(restart, screenWidth*.4, screenHeight*.6);
								
								if (IsKeyDown('Y'))
								{
									currentState = MAINMENU;
									player1Score = 0;
									player2Score = 0;
								}
			};
				break;
			default:
				break;

		}

		
			
		

		//ball.ballSprite = 

		ClearScreen();

	} while (!FrameworkUpdate());
	return 0;
}