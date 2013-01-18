/*
 * main.cpp - entry point for the program
 */

#include <stdio.h>
#include "GameApp.h"

int main(int argc, char* argv[]){
	printf("Hello World!\n");

	GameApp *gameApp = new GameApp();
	gameApp->run();

	return 0;
}
