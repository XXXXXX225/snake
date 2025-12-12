#ifndef SNAKE_H  
#define SNAKE_H
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
typedef struct _Snake {
	int x;
	int y;
	struct _Snake* next;
}Snake;
typedef struct _Food {
	int x;
	int y;
}Food;
Snake* g_pSnake = NULL;
Food g_food;
unsigned int g_score;
unsigned int g_speed = 10;
void StartGame();
void Welcome();
void CreateMap();
void SetCursorPosition();
void InitSnake();
void RunGame();
void MoveSnake(char direction);
void CreateFood();
void EatFood();
int isDie();
void EndGame();
void HideCursor();
#endif #pragma once
