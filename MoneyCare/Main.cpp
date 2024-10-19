/*
 * Program Name: MoneyCare
 * Author: Bae-Seoil
 * Created: 2024-11-04
 * Description: A program for recording and managing usage history.
 * You can use, copy, modify, and distribute this program freely.
 */

#include <functional>
#include <queue>
#include <iostream>
#include "Coroutine.h"

void start();
void updateTest1();
void updateTest2();

int main()
{
	start();
	while (true)
	{
		Coroutine::processFunctions();
	}
}

void start()
{
	Coroutine::AddCoroutine(updateTest1);
	Coroutine::AddCoroutine(updateTest2);
}

void updateTest1()
{
	std::cout << "Test1\n";
	Coroutine::AddCoroutine(updateTest1);
}

void updateTest2()
{
	std::cout << "Test2\n";
	Coroutine::AddCoroutine(updateTest2);
}