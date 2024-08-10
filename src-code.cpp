// Include necessary libraries 
#include <algorithm> 
#include <conio.h> 
#include <graphics.h> 
#include <stdlib.h> 
#include <time.h> 
#include <vector> 

using namespace std; 

int main() 
{ 
	// Initialize the graphics environment 
	int gd = DETECT, gm; 
	initgraph(&gd, &gm, NULL); 
	// Set the background color 
	setbkcolor(CYAN); 
	// Define variables and constants for sliders, bars, 
	// colors, and scoring 
	int barWidth = 20; 
	int barHeight = 120; 
	int spaceBetweenBars = 50; 
	int minY = 50; 
	int maxY = getmaxy() - 50; 
	int barX = getmaxx() - 50 - barWidth; 

	srand(time(NULL)); 

	int yellowColor = YELLOW; 
	int cyanColor = BLACK; 
	int magentaColor = MAGENTA; 
	int otherColor = WHITE; 

	int redBarY = minY; 
	int greenBarY = minY + spaceBetweenBars; 
	int blueBarY = minY + 2 * spaceBetweenBars; 
	int redBarVelocity = 3; 
	int greenBarVelocity = 5; 
	int blueBarVelocity = 10; 

	int redColor = RED; 
	int greenColor = GREEN; 
	int blueColor = BLUE; 

	int scoreRed = 0; 
	int scoreGreen = 0; 
	int scoreBlue = 0; 

	int ballRadius = 10; 

	// Create arrays to store ball colors, positions, 
	// velocities, and directions 
	vector<int> colors; 
	for (int i = 0; i < 9; ++i) { 
		if (i < 2) 
			colors.push_back(redColor); 
		else if (i < 4) 
			colors.push_back(greenColor); 
		else if (i < 6) 
			colors.push_back(blueColor); 
		else if (i == 6) 
			colors.push_back(yellowColor); 
		else if (i == 7) 
			colors.push_back(cyanColor); 
		else if (i == 8) 
			colors.push_back(magentaColor); 
		else
			colors.push_back(otherColor); 
	} 

	vector<int> ballX; 
	for (int i = 0; i < colors.size(); ++i) { 
		ballX.push_back(rand() % (getmaxx() + ballRadius) 
						/ 2); 
	} 
	vector<int> ballY; 
	for (int i = 0; i < colors.size(); ++i) { 
		ballY.push_back(rand() 
							% (getmaxy() - ballRadius * 2) 
						+ ballRadius); 
	} 
	vector<int> ballVelocitiesX(colors.size(), 
								rand() % 5 + 5); 
	vector<int> ballVelocitiesY(colors.size(), 
								rand() % 5 + 5); 
	vector<int> ballDirectionsX(colors.size(), 1); 
	vector<int> ballDirectionsY(colors.size(), 1); 
	// Game loop 
	while (!kbhit()) { 
		clearviewport(); 
		// Update slider positions 
		redBarY += redBarVelocity; 
		greenBarY += greenBarVelocity; 
		blueBarY += blueBarVelocity; 

		if (redBarY <= minY 
			|| redBarY + barHeight >= maxY) { 
			redBarVelocity *= -1; 
		} 
		if (greenBarY <= minY 
			|| greenBarY + barHeight >= maxY) { 
			greenBarVelocity *= -1; 
		} 
		if (blueBarY <= minY 
			|| blueBarY + barHeight >= maxY) { 
			blueBarVelocity *= -1; 
		} 
		// Draw sliders 
		setcolor(redColor); 
		setfillstyle(SOLID_FILL, redColor); 
		bar(barX, redBarY, barX + barWidth, 
			redBarY + barHeight); 
		setcolor(greenColor); 
		setfillstyle(SOLID_FILL, greenColor); 
		bar(barX, greenBarY, barX + barWidth, 
			greenBarY + barHeight); 
		setcolor(blueColor); 
		setfillstyle(SOLID_FILL, blueColor); 
		bar(barX, blueBarY, barX + barWidth, 
			blueBarY + barHeight); 
		// Update ball positions 
		for (int i = 0; i < colors.size(); ++i) { 
			ballX[i] 
				+= ballVelocitiesX[i] * ballDirectionsX[i]; 
			if (ballX[i] >= barX - barWidth 
				|| ballX[i] - ballRadius <= 0) { 
				ballDirectionsX[i] *= -1; 

				if (ballX[i] - ballRadius > 0) { 
					setcolor(YELLOW); 
					circle(barX, ballY[i], 10); 
					int hitBarColor 
						= getpixel(barX + 10, ballY[i]); 
					// Handle ball-slider collisions and 
					// update scores 
					if (hitBarColor == colors[i] 
						&& colors[i] == RED) { 
						scoreRed += 4; 
					} 
					else if (hitBarColor == colors[i] 
							&& colors[i] == GREEN) { 
						scoreGreen += 4; 
					} 
					else if (hitBarColor == colors[i] 
							&& colors[i] == BLUE) { 
						scoreBlue += 4; 
					} 
					else if (hitBarColor && colors[i] 
							&& colors[i] != GREEN 
							&& colors[i] != RED 
							&& colors[i] != BLUE 
							&& hitBarColor == RED) { 
						scoreRed--; 
					} 
					else if (hitBarColor && colors[i] 
							&& colors[i] != GREEN 
							&& colors[i] != RED 
							&& colors[i] != BLUE 
							&& hitBarColor == GREEN) { 
						scoreGreen--; 
					} 
					else if (hitBarColor && colors[i] 
							&& colors[i] != GREEN 
							&& colors[i] != RED 
							&& colors[i] != BLUE 
							&& hitBarColor == BLUE) { 
						scoreBlue--; 
					} 
				} 
			} 

			ballY[i] 
				+= ballVelocitiesY[i] * ballDirectionsY[i]; 
			if (ballY[i] > getmaxy() - ballRadius - 5 
				|| ballY[i] <= ballRadius) { 
				ballDirectionsY[i] *= -1; 
			} 
			// Draw balls 
			setcolor(colors[i]); 
			setfillstyle(SOLID_FILL, colors[i]); 
			fillellipse(ballX[i], ballY[i], ballRadius, 
						ballRadius); 
		} 
		// Display scores 
		setcolor(WHITE); 
		const char* scoreText = "Score: "; 
		outtextxy(20, 40, const_cast<char*>(scoreText)); 

		char redScoreText[10], greenScoreText[10], 
			blueScoreText[10]; 
		sprintf(redScoreText, "Red: %d", scoreRed); 
		sprintf(greenScoreText, "Green: %d", scoreGreen); 
		sprintf(blueScoreText, "Blue: %d", scoreBlue); 

		outtextxy(70, 40, redScoreText); 
		outtextxy(120, 40, greenScoreText); 
		outtextxy(180, 40, blueScoreText); 
		// Check for a winner and exit the game if necessary 
		if (scoreRed >= 10 || scoreGreen >= 10 
			|| scoreBlue >= 10) { 
			clearviewport(); 
			setcolor(WHITE); 
			settextstyle(6, 0, 4); 
			const char* winners = "Congratulations"; 
			outtextxy(100, getmaxy() / 4, 
					const_cast<char*>(winners)); 
			delay(500); 
			if (scoreRed >= 10) { 
				const char* red_w = "RED is WINNER"; 
				outtextxy(100, getmaxy() / 2 + 30, 
						const_cast<char*>(red_w)); 
			} 
			if (scoreGreen >= 10) { 
				const char* green_w = "GREEN is WINNER"; 
				outtextxy(100, getmaxy() / 2 + 30, 
						const_cast<char*>(green_w)); 
			} 
			if (scoreBlue >= 10) { 
				const char* blue_w = "BLUE is WINNER"; 
				outtextxy(100, getmaxy() / 2 + 30, 
						const_cast<char*>(blue_w)); 
			} 
			const char* out = "Press any key to EXIT"; 
			outtextxy(100, getmaxy() / 2 + 200, 
					const_cast<char*>(out)); 
			break; 
		} 

		delay(10); 
	} 
	// Wait for a key press before closing the window 
	while (!kbhit()) { 
		delay(100); 
	} 
	// Close the graphics environment 
	closegraph(); 
	return 0; 
}
