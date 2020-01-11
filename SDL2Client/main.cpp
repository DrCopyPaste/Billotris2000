#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

#include "SDL.h"

using namespace std;

#ifdef _WIN32
#undef main
#endif

// make method signature known
void UpdateBricks();

int Running;

SDL_Surface* Screen;
SDL_Texture* ScreenTexture;

SDL_Window* Window;
SDL_Renderer* Renderer;

SDL_Surface* Background;
SDL_Surface* Background_empty;
SDL_Surface* BrickSource;
SDL_Surface* PlayGround;
SDL_Surface* PreviewGround;
SDL_Surface* PlayGround_empty;
SDL_Surface* GameOver;
SDL_Surface* PreviewGround_empty;

SDL_Surface* LetterA;
SDL_Surface* LetterB;
SDL_Surface* LetterC;
SDL_Surface* LetterD;
SDL_Surface* LetterE;
SDL_Surface* LetterF;
SDL_Surface* LetterG;
SDL_Surface* LetterH;
SDL_Surface* LetterI;
SDL_Surface* LetterJ;
SDL_Surface* LetterK;
SDL_Surface* LetterL;
SDL_Surface* LetterM;
SDL_Surface* LetterN;
SDL_Surface* LetterO;
SDL_Surface* LetterP;
SDL_Surface* LetterQ;
SDL_Surface* LetterR;
SDL_Surface* LetterS;
SDL_Surface* LetterT;
SDL_Surface* LetterU;
SDL_Surface* LetterV;
SDL_Surface* LetterW;
SDL_Surface* LetterX;
SDL_Surface* LetterY;
SDL_Surface* LetterZ;

SDL_Surface* Digit0;
SDL_Surface* Digit1;
SDL_Surface* Digit2;
SDL_Surface* Digit3;
SDL_Surface* Digit4;
SDL_Surface* Digit5;
SDL_Surface* Digit6;
SDL_Surface* Digit7;
SDL_Surface* Digit8;
SDL_Surface* Digit9;

SDL_Surface* TmpSurface;

unsigned long Score;

// rows where the user did neither press down to accelerate or up to immediately drop the brick to the lowest possible row
// the lower this number is the higher the score, obviously ;)
unsigned long RowsLetFallen;
unsigned long RowsCleared;

unsigned long TotalBricksSinceStart;
unsigned long TotalBricksOnScreen;
unsigned long TotalRowsCleared;
unsigned long LastLevelRowsCleared = 0;

unsigned int Level = 1;
unsigned int Pause = 0;

void RenderNumber(SDL_Surface* surface, unsigned int startx, unsigned int starty, unsigned long number)
{
    SDL_Rect targetArea;

    targetArea.x = startx;
    targetArea.y = starty;

    unsigned long tmpNumber = number;

    unsigned long digit;
    unsigned long rest = 1;

    // max score ~ 4.5 * 10^9, so we start by moduloing 10^9
    unsigned long divisor = 1000000000;

    SDL_Surface* tmp = Digit0;

    int	leadingZero = 1;
    int doNothing = 0;

    while (divisor > 0)
    {
        digit = tmpNumber / divisor;
        rest = tmpNumber % divisor;

        divisor = divisor / 10;
        tmpNumber = rest;

        //jetzt den quotienten auf die surface bringen
        switch (digit)
        {
            case 0:
            {
                if (leadingZero == 0)
                {
                    tmp = Digit0;
                }
                else
                {
                    if (rest == 0)
                    {
                        tmp = Digit0;
                    }
                    else
                    {
                        doNothing = 1;
                    }
                }

                break;
            }

            case 1:
            {
                tmp = Digit1;
                break;
            }

            case 2:
            {
                tmp = Digit2;
                break;
            }

            case 3:
            {
                tmp = Digit3;
                break;
            }

            case 4:
            {
                tmp = Digit4;
                break;
            }

            case 5:
            {
                tmp = Digit5;
                break;
            }

            case 6:
            {
                tmp = Digit6;
                break;
            }

            case 7:
            {
                tmp = Digit7;
                break;
            }

            case 8:
            {
                tmp = Digit8;
                break;
            }

            case 9:
            {
                tmp = Digit9;
                break;
            }

            default:
            {
                break;
            }

        };	//switch

        if (doNothing == 0)
        {
            leadingZero = 0;
            targetArea.h = tmp->h;
            targetArea.w = tmp->w;

            SDL_BlitSurface(tmp, 0, surface, &targetArea);

            targetArea.x += targetArea.h;
        }
        else
        {
            doNothing = 0;
        };
    };	//while
};

void RenderText(SDL_Surface* surface, unsigned int startx, unsigned int starty, string text)
{
    SDL_Rect sourceArea;
    SDL_Rect targetArea;

    targetArea.x = startx;
    targetArea.y = starty;

    for (unsigned int i = 0; i < text.length(); ++i)
    {
        switch (text[i])
        {
            case 'A':
            {
                TmpSurface = LetterA;
                break;
            }

            case 'B':
            {
                TmpSurface = LetterB;
                break;
            }

            case 'C':
            {
                TmpSurface = LetterC;
                break;
            }

            case 'D':
            {
                TmpSurface = LetterD;
                break;
            }

            case 'E':
            {
                TmpSurface = LetterE;
                break;
            }

            case 'F':
            {
                TmpSurface = LetterF;
                break;
            }

            case 'G':
            {
                TmpSurface = LetterG;
                break;
            }

            case 'H':
            {
                TmpSurface = LetterH;
                break;
            }

            case 'I':
            {
                TmpSurface = LetterI;
                break;
            }

            case 'J':
            {
                TmpSurface = LetterJ;
                break;
            }

            case 'K':
            {
                TmpSurface = LetterK;
                break;
            }

            case 'L':
            {
                TmpSurface = LetterL;
                break;
            }

            case 'M':
            {
                TmpSurface = LetterM;
                break;
            }

            case 'N':
            {
                TmpSurface = LetterN;
                break;
            }

            case 'O':
            {
                TmpSurface = LetterO;
                break;
            }

            case 'P':
            {
                TmpSurface = LetterP;
                break;
            }

            case 'Q':
            {
                TmpSurface = LetterQ;
                break;
            }

            case 'R':
            {
                TmpSurface = LetterR;
                break;
            }

            case 'S':
            {
                TmpSurface = LetterS;
                break;
            }

            case 'T':
            {
                TmpSurface = LetterT;
                break;
            }

            case 'U':
            {
                TmpSurface = LetterU;
                break;
            }

            case 'V':
            {
                TmpSurface = LetterV;
                break;
            };
            case 'W':
            {
                TmpSurface = LetterW;
                break;
            }

            case 'X':
            {
                TmpSurface = LetterX;
                break;
            }

            case 'Y':
            {
                TmpSurface = LetterY;
                break;
            }

            case 'Z':
            {
                TmpSurface = LetterZ;
                break;
            }

            case '0':
            {
                TmpSurface = Digit0;
                break;
            }

            case '1':
            {
                TmpSurface = Digit1;
                break;
            }

            case '2':
            {
                TmpSurface = Digit2;
                break;
            }

            case '3':
            {
                TmpSurface = Digit3;
                break;
            }

            case '4':
            {
                TmpSurface = Digit4;
                break;
            }

            case '5':
            {
                TmpSurface = Digit5;
                break;
            }

            case '6':
            {
                TmpSurface = Digit6;
                break;
            }

            case '7':
            {
                TmpSurface = Digit7;
                break;
            }

            case '8':
            {
                TmpSurface = Digit8;
                break;
            }


            case '9':
            {
                TmpSurface = Digit9;
                break;
            }

            default:
            {
                break;
            }
        }

        targetArea.h = TmpSurface->h;
        targetArea.w = TmpSurface->w;

        SDL_BlitSurface(TmpSurface, 0, surface, &targetArea);

        targetArea.x += targetArea.h;
        //target.y	+=target.w;
    };

    // only partial update here? shouldnt this behave similarly to outzahlxy?
    // seems unused right now anyways, probably preparation to display hiscore names etc
    //SDL_UpdateRect(surface, startx, starty, ziel.x, (starty + 30));
};

SDL_Surface* LoadBMP(const char* szFile)
{
    SDL_Surface* originalBmp;
    SDL_Surface* convertedPixelFormatBmp;

    originalBmp = SDL_LoadBMP(szFile);
    if (!originalBmp)
    {
        fprintf(stderr, "%s could not be loaded: %s\n", szFile, SDL_GetError());
        exit(1);
    }

    convertedPixelFormatBmp = SDL_ConvertSurface(originalBmp, Screen->format, Screen->flags);
    SDL_FreeSurface(originalBmp);
    if (!convertedPixelFormatBmp)
    {
        fprintf(stderr, "%s could not be converted into screen pixel format: %s\n", szFile, SDL_GetError());
        exit(1);
    }

    return convertedPixelFormatBmp;
}

/*
playing grid is 18 x 24

but the bottom row (index 25)
is invisible (but needed for collision detection)
*/
#define maxx	18
#define maxy	25

class BrickTile
{
    public:
    int IsSet;

    // source bitmap is 640x480 => when tiling 20x20 => 307200/(20*20) => 768 tiles (i.e. types)
    int Type;
};

unsigned int CollapseClearedRows = 1;

BrickTile CurrentBrickGrid[4][4];
BrickTile NextBrickGrid[4][4];
BrickTile PlayingGrid[maxx][maxy];

// top left corner of current brick grid in relation to playing grid
unsigned int CurrentBrick_X;
unsigned int CurrentBrick_Y;

// this means, if not for user pressing down or up, this will be the time the brick stays on one row before falling "one step" down
// in milliseconds
unsigned int BrickFallDelay_ms = 500;
unsigned int NextBrickType = 1;

void ClearCurrentBrickGrid()
{
    unsigned int x;
    unsigned int y;

    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            CurrentBrickGrid[x][y].IsSet = 0;
            CurrentBrickGrid[x][y].Type = 0;
        }
    }
}

void ClearNextBrickGrid()
{
    unsigned int x;
    unsigned int y;

    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            NextBrickGrid[x][y].IsSet = 0;
            NextBrickGrid[x][y].Type = 0;
        }
    }
}

void NextLevel()
{
    Level++;
    BrickFallDelay_ms = (BrickFallDelay_ms * 85) / 100;
}

// max should define the max number of BrickTiles at game start (not used right now)
void InitPlayingGrid(unsigned int max)
{
    unsigned int x;
    unsigned int y;

    for (x = 0; x < maxx; ++x)
    {
        for (y = 0; y < (maxy - 1); ++y)
        {
            PlayingGrid[x][y].IsSet = 0;
            PlayingGrid[x][y].Type = 0;

            PlayingGrid[x][maxy - 1].IsSet = 1;
            PlayingGrid[x][maxy - 1].Type = 1;
        }
    }

    ClearCurrentBrickGrid();
}


void ClearRowsIfPossible()
{
    unsigned int x;
    unsigned int y;
    unsigned int y1;
    int	rowComplete = 0;

    for (y = 0; y < (maxy - 1); ++y)
    {
        if (PlayingGrid[0][y].IsSet == 1)
        {
            rowComplete = 1;
            for (x = 1; x < maxx; ++x)
            {
                if (PlayingGrid[x][y].IsSet == 0)
                {
                    rowComplete = 0;
                    //cout<<"row not complete x"<<x<<" y"<<y<<endl;
                    break;
                }
            }

            if (rowComplete == 1)
            {
                RowsCleared += 1;

                for (x = 0; x < maxx; ++x)
                {
                    PlayingGrid[x][y].IsSet = 0;
                }

                TotalBricksOnScreen -= maxx;
                TotalRowsCleared++;
                //cout<<"row y="<<y<<" cleared"<<endl;

                UpdateBricks();

                SDL_RenderPresent(Renderer);

                if (CollapseClearedRows == 1)
                {
                    for (x = 0; x < maxx; ++x)
                    {
                        for (y1 = y; y1 > 0; --y1)
                        {
                            PlayingGrid[x][y1].IsSet = PlayingGrid[x][y1 - 1].IsSet;
                            PlayingGrid[x][y1].Type = PlayingGrid[x][y1 - 1].Type;
                        }
                    }

                    if ((TotalRowsCleared - LastLevelRowsCleared) == 8)
                    {
                        LastLevelRowsCleared = TotalRowsCleared;
                        NextLevel();
                    }

                    SDL_Delay(50);

                    UpdateBricks();

                    SDL_RenderPresent(Renderer);
                }
            }
        }
    }
}

void DrawGameOverAndQuit()
{
    SDL_Rect sourceArea;
    SDL_Rect targetArea;

    sourceArea.h = 40;
    sourceArea.w = 480;
    sourceArea.x = 0;
    sourceArea.y = 0;

    targetArea.h = 40;
    targetArea.w = 480;
    targetArea.x = 0;
    targetArea.y = 200;

    SDL_BlitSurface(GameOver, &sourceArea, PlayGround, &targetArea);

    sourceArea.x = 0;
    sourceArea.y = 0;
    sourceArea.h = 480;
    sourceArea.w = 480;

    targetArea.x = 80;
    targetArea.y = 0;
    targetArea.h = 480;
    targetArea.w = 240;

    SDL_BlitSurface(PlayGround, &sourceArea, Screen, &targetArea);

    SDL_UpdateTexture(ScreenTexture, NULL, Screen->pixels, Screen->pitch);
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);

    SDL_RenderPresent(Renderer);

    SDL_Delay(3000);

    Running = 0;
}

void UpdateNextBrickGrid()
{
    ClearNextBrickGrid();

    switch (NextBrickType)
    {
/*
oo
oo
*/
        case 0:
        {
            NextBrickGrid[1][0].IsSet = 1;
            NextBrickGrid[1][0].Type = rand() % 768 + 1;
            NextBrickGrid[1][1].IsSet = 1;
            NextBrickGrid[1][1].Type = rand() % 768 + 1;
            NextBrickGrid[2][0].IsSet = 1;
            NextBrickGrid[2][0].Type = rand() % 768 + 1;
            NextBrickGrid[2][1].IsSet = 1;
            NextBrickGrid[2][1].Type = rand() % 768 + 1;

            break;
        }
/*
oooo
*/
        case 1:
        {
            NextBrickGrid[0][0].IsSet = 1;
            NextBrickGrid[0][0].Type = rand() % 768 + 1;
            NextBrickGrid[1][0].IsSet = 1;
            NextBrickGrid[1][0].Type = rand() % 768 + 1;
            NextBrickGrid[2][0].IsSet = 1;
            NextBrickGrid[2][0].Type = rand() % 768 + 1;
            NextBrickGrid[3][0].IsSet = 1;
            NextBrickGrid[3][0].Type = rand() % 768 + 1;

            break;
        }
/*
ooo
o
*/
        case 2:
        {
            NextBrickGrid[0][0].IsSet = 1;
            NextBrickGrid[0][0].Type = rand() % 768 + 1;
            NextBrickGrid[1][0].IsSet = 1;
            NextBrickGrid[1][0].Type = rand() % 768 + 1;
            NextBrickGrid[2][0].IsSet = 1;
            NextBrickGrid[2][0].Type = rand() % 768 + 1;
            NextBrickGrid[0][1].IsSet = 1;
            NextBrickGrid[0][1].Type = rand() % 768 + 1;

            break;
        }
/*
ooo
 o
*/
        case 3:
        {
            NextBrickGrid[0][0].IsSet = 1;
            NextBrickGrid[0][0].Type = rand() % 768 + 1;
            NextBrickGrid[1][0].IsSet = 1;
            NextBrickGrid[1][0].Type = rand() % 768 + 1;
            NextBrickGrid[2][0].IsSet = 1;
            NextBrickGrid[2][0].Type = rand() % 768 + 1;
            NextBrickGrid[1][1].IsSet = 1;
            NextBrickGrid[1][1].Type = rand() % 768 + 1;

            break;
        }
/*
o
ooo
*/
        case 4:
        {
            NextBrickGrid[0][0].IsSet = 1;
            NextBrickGrid[0][0].Type = rand() % 768 + 1;
            NextBrickGrid[0][1].IsSet = 1;
            NextBrickGrid[0][1].Type = rand() % 768 + 1;
            NextBrickGrid[1][1].IsSet = 1;
            NextBrickGrid[1][1].Type = rand() % 768 + 1;
            NextBrickGrid[2][1].IsSet = 1;
            NextBrickGrid[2][1].Type = rand() % 768 + 1;
        }
/*
(currently inactive)
"RANDOM BRICK"

any tile in 4x4 COULD be set.
(but still 4 tiles at max for this brick)
*/
        case 5:
        {
            unsigned int counter = 4;

            for (unsigned int x = 0; x < 4; ++x)
            {
                for (unsigned int y = 0; y < 4; ++y)
                {
                    if (counter == 0) {}
                    else
                    {
                        NextBrickGrid[x][y].IsSet = rand() % 2;
                        NextBrickGrid[x][y].Type = rand() % 768 + 1;

                        --counter;
                    }
                }
            }
        }
/*
(currently inactive)
"MEGA BRICK"

any tile in 4x4 COULD be set.
(number of tiles is unlimited)
*/
        case 6:
        {
            for (unsigned int x = 0; x < 4; ++x)
            {
                for (unsigned int y = 0; y < 4; ++y)
                {
                    NextBrickGrid[x][y].IsSet = rand() % 2;	//either 0 or 1
                    NextBrickGrid[x][y].Type = rand() % 768 + 1;
                }
            }
        }
    }
}

unsigned long Pot(unsigned int base, unsigned int exp)
{
    unsigned int tmp = base;

    if (exp == 0)
    {
        return 1;
    }
    else
    {
        return (base * Pot(base, (exp - 1)));
    }
}

void UpdateScore()
{
    Score += 10 +
        ((RowsCleared > 0) ? (100 * (Pot(Level, RowsCleared))) : 0) +
        ((float(RowsLetFallen) / float(maxy - 1)) * 10 * Level);    // shouldn't this division be reversed? this way letting a brick fall for longer uncontrolled would give more points?

    RowsCleared = 0;
};

int CreateBrick()
{
    ClearRowsIfPossible();
    ClearCurrentBrickGrid();
    CurrentBrick_X = 8;
    CurrentBrick_Y = 0;

    NextBrickType = rand() % 4;

    unsigned int x, y;
    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            CurrentBrickGrid[x][y] = NextBrickGrid[x][y];

            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                if (PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y + 1].IsSet == 1)
                {
                    return 1;
                }

                if (PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y].IsSet == 1)
                {
                    return 1;
                }
            }
        }
    }

    UpdateNextBrickGrid();
    TotalBricksOnScreen += 4;
    TotalBricksSinceStart++;
    RowsLetFallen = 0;
    return 0;
}

// returns 0 if there is no space between currently falling brick and ground/bricks lying on the ground
// (quits game if return value is 0)
// returns 1 if threre is any space at all between them
unsigned int CurrentBrickDistanceToGround()
{
    unsigned int neu = 0;

    for (unsigned int x = 0; x < 4; x++)
        for (unsigned int y = 0; y < 4; y++)
        {
            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                if (PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y + 1].IsSet == 1)
                {
                    for (x = 0; x < 4; ++x)
                    {
                        for (y = 0; y < 4; ++y)
                        {
                            if (CurrentBrickGrid[x][y].IsSet == 1)
                            {
                                PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y].IsSet = 1;
                                PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y].Type = CurrentBrickGrid[x][y].Type;
                            }
                        }
                    }

                    UpdateScore();

                    int zuende = CreateBrick();
                    if (zuende == 1)
                    {
                        DrawGameOverAndQuit();
                    }

                    return 0;
                }
            }
        }

    return 1;
}

void AdjustBrickFallSpeedToFrameRate(Uint32& lastActualFall, Uint32 currentTimeStamp)
{
    if ((currentTimeStamp - lastActualFall) >= BrickFallDelay_ms)
    {
        unsigned int i = CurrentBrickDistanceToGround();
        if (i > 0)
        {
            ++CurrentBrick_Y;
            RowsLetFallen++;
            lastActualFall = currentTimeStamp;
        }
    }
}

void UpdateBricks()
{
    unsigned int x;
    unsigned int y;
    unsigned int tmpType;
    SDL_Rect sourceArea;
    SDL_Rect targetArea;

    sourceArea.h = 20;
    sourceArea.w = 20;
    sourceArea.x = 0;
    sourceArea.y = 0;

    targetArea.h = 20;
    targetArea.w = 20;
    targetArea.x = 0;
    targetArea.y = 0;

    SDL_BlitSurface(PlayGround_empty, 0, PlayGround, 0);
    SDL_BlitSurface(PreviewGround_empty, 0, PreviewGround, 0);

    for (x = 0; x < maxx; ++x)
    {
        for (y = 0; y < (maxy - 1); ++y)
        {
            if (PlayingGrid[x][y].IsSet == 1)
            {
                tmpType = PlayingGrid[x][y].Type;
                sourceArea.x = ((tmpType - 1) % 32) * 20;
                sourceArea.y = ((tmpType - 1) / 32) * 20;

                targetArea.x = x * 20;
                targetArea.y = y * 20;

                SDL_BlitSurface(BrickSource, &sourceArea, PlayGround, &targetArea);
            }
        }
    }

    // calculate the movable (currently falling) brick in this last step
    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                tmpType = CurrentBrickGrid[x][y].Type;
                sourceArea.x = ((tmpType - 1) % 32) * 20;
                sourceArea.y = ((tmpType - 1) / 32) * 20;

                targetArea.x = (CurrentBrick_X + x) * 20;
                targetArea.y = (CurrentBrick_Y + y) * 20;

                SDL_BlitSurface(BrickSource, &sourceArea, PlayGround, &targetArea);
            }
        }
    }

    sourceArea.x = 0;
    sourceArea.y = 0;
    sourceArea.h = 480;
    sourceArea.w = 360;

    targetArea.x = 200;
    targetArea.y = 0;
    targetArea.h = 480;
    targetArea.w = 360;

    SDL_BlitSurface(PlayGround, &sourceArea, Screen, &targetArea);

    SDL_UpdateTexture(ScreenTexture, NULL, Screen->pixels, Screen->pitch);
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);
}

void DrawBackground()
{
    // left side of the screen ....
    unsigned int tmpType;

    SDL_Rect sourceArea;
    SDL_Rect targetArea;

    sourceArea.x = 0;
    sourceArea.y = 0;
    sourceArea.w = 200;
    sourceArea.h = 480;

    targetArea.x = 0;
    targetArea.y = 0;

    SDL_BlitSurface(Background_empty, &sourceArea, Background, &targetArea);
    RenderNumber(Background, 0, 340, TotalBricksSinceStart);
    RenderNumber(Background, 0, 380, TotalBricksOnScreen);
    RenderNumber(Background, 0, 420, Level);
    RenderNumber(Background, 0, 460, TotalRowsCleared);
    RenderNumber(Background, 0, 300, Score);
    SDL_BlitSurface(Background, &sourceArea, Screen, &targetArea);

    // next brick preview on the left
    sourceArea.x = 0;
    sourceArea.y = 0;
    sourceArea.w = 100;
    sourceArea.h = 100;

    targetArea.x = 50;
    targetArea.y = 20;

    SDL_BlitSurface(PreviewGround_empty, &sourceArea, Screen, &targetArea);

    // draw brick preview
    sourceArea.h = 20;
    sourceArea.w = 20;
    targetArea.h = 20;
    targetArea.w = 20;

    for (unsigned int x = 0; x < 4; ++x)
    {
        for (unsigned int y = 0; y < 4; ++y)
        {
            if (NextBrickGrid[x][y].IsSet == 1)
            {
                tmpType = NextBrickGrid[x][y].Type;
                sourceArea.x = ((tmpType - 1) % 32) * 20;
                sourceArea.y = ((tmpType - 1) / 32) * 20;

                targetArea.x = 20 + (x * 20);
                targetArea.y = 20 + (y * 20);

                SDL_BlitSurface(BrickSource, &sourceArea, PreviewGround, &targetArea);
            }
        }
    }

    sourceArea.x = 0;
    sourceArea.y = 0;
    sourceArea.h = 100;
    sourceArea.w = 100;

    targetArea.x = 50;
    targetArea.y = 20;
    targetArea.h = 100;
    targetArea.w = 100;

    SDL_BlitSurface(PreviewGround, 0, Screen, &targetArea);

    // right side of the screen
    sourceArea.x = 560;
    sourceArea.y = 0;
    sourceArea.w = 80;
    sourceArea.h = 480;

    targetArea.x = 560;
    targetArea.y = 0;

    SDL_BlitSurface(Background_empty, &sourceArea, Screen, &targetArea);

    SDL_UpdateTexture(ScreenTexture, NULL, Screen->pixels, Screen->pitch);
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);
}

// try to move one field left
void TryMoveLeft()
{
    int isOccupied = 0;

    for (unsigned int x = 0; x < 4; ++x)
    {
        for (unsigned int y = 0; y < 4; ++y)
        {
            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                // cant move anymore to the left than index 0
                if ((x + CurrentBrick_X) == 0)
                {
                    isOccupied = 1;
                }

                // cant move anymore to the left if that index is occupied by something else
                if (PlayingGrid[x + CurrentBrick_X - 1][y + CurrentBrick_Y].IsSet == 1)
                {
                    isOccupied = 1;
                }
            }
        }
    }

    if (isOccupied == 0)
    {
        --CurrentBrick_X;
    }
}

// try to move one field right
void TryMoveRight()
{
    int isOccupied = 0;

    for (unsigned int x = 0; x < 4; ++x)
    {
        for (unsigned int y = 0; y < 4; ++y)
        {
            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                // cant move anymore to the right than index (max - 1)
                if ((x + CurrentBrick_X) == (maxx - 1))
                {
                    isOccupied = 1;
                }

                // cant move anymore to the left if that index is occupied by something else
                if (PlayingGrid[x + CurrentBrick_X + 1][y + CurrentBrick_Y].IsSet == 1)
                {
                    isOccupied = 1;
                }
            }
        }
    }

    if (isOccupied == 0)
    {
        ++CurrentBrick_X;
    }
}

// try to move one field down
void TryMoveDown()
{
    int IsOccupied = 0;

    for (unsigned int x = 0; x < 4; ++x)
    {
        for (unsigned int y = 0; y < 4; ++y)
        {
            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                if (PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y + 1].IsSet == 1)
                {
                    IsOccupied = 1;
                }
            }
        }
    }

    if (IsOccupied == 0) ++CurrentBrick_Y;
}

// brick is to move from current position to the lowest possible (the ground)
void LetFallToGround()
{
    unsigned int groundHit = 0;
    unsigned int x;
    unsigned int y;

    while (groundHit != 1)
    {
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
            {
                if (CurrentBrickGrid[x][y].IsSet == 1)
                {
                    if (PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y + 1].IsSet == 1)
                    {
                        groundHit = 1;
                    }
                }
            }

        if (groundHit != 1)
        {
            ++CurrentBrick_Y;
        }
    };

    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            if (CurrentBrickGrid[x][y].IsSet == 1)
            {
                PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y].IsSet = 1;
                PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y].Type = CurrentBrickGrid[x][y].Type;
            }
        }
    }
}

void TryRotateCounterClockwise()
{
    // this SHOULD try to rotate the current brick 90° counter clockwise
    // but its not correct:
    // some rotations plainly dont work (for the L-Brick for instance)
    // and the rotation axis is outside the brick in most cases, meaning it also moves left when rotating

    BrickTile tmpGrid[4][4];
    unsigned int x;
    unsigned int y;
    unsigned int rotationSuccessful = 1;

    // very cheap shot at rotation :D
    // ToDo make a correct rotation calculation (vector geometry?)
    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            tmpGrid[x][y].IsSet = 0;
            tmpGrid[x][y].Type = 0;

            tmpGrid[x][y].IsSet = CurrentBrickGrid[3 - y][x].IsSet;
            tmpGrid[x][y].Type = CurrentBrickGrid[3 - y][x].Type;
        }
    }

    for (x = 0; x < 4; ++x)
    {
        for (y = 0; y < 4; ++y)
        {
            if (tmpGrid[x][y].IsSet == 1)
            {
                if (PlayingGrid[x + CurrentBrick_X][y + CurrentBrick_Y].IsSet == 1)
                {
                    rotationSuccessful = 0;
                }

                if ((x + CurrentBrick_X) > (maxx - 1))
                {
                    rotationSuccessful = 0;
                }
            }
        }
    }

    if (rotationSuccessful == 1)
    {
        for (x = 0; x < 4; ++x)
        {
            for (y = 0; y < 4; ++y)
            {
                CurrentBrickGrid[x][y].IsSet = tmpGrid[x][y].IsSet;
                CurrentBrickGrid[x][y].Type = tmpGrid[x][y].Type;
            }
        }
    }
}

int main()
{
    srand(time(0));
    Uint32 lastFrameTimestamp;
    Uint32 currentFrameTimestamp;
    Uint32 frameDuration;
    Uint32 last_fall;

    // delay between commands when a key is pressed
    Uint32 keyPressSpamDelay = 50;

    // ToDo this should be some kind of array for each possible command
    // this way you cannot press right directly after left, it wont be processed until keyPressSpamDelay has passed...
    Uint32 lastKeyPressCommand;
    Uint32 lastpause;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL konnte nicht initialisiert werden: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    SDL_CreateWindowAndRenderer(
        640,
        480,
        SDL_WINDOW_BORDERLESS,
        &Window,
        &Renderer);

    SDL_RenderClear(Renderer);

    Screen = SDL_CreateRGBSurface(0, 640, 480, 32,
        0x00FF0000,
        0x0000FF00,
        0x000000FF,
        0xFF000000);

    ScreenTexture = SDL_CreateTexture(Renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        640, 480);

    if (!Window)
    {
        fprintf(stderr, "Konnte Bildschirmmodus nicht setzen: %s\n", SDL_GetError());
        exit(1);
    }

    Background = LoadBMP("images\\rand.bmp");
    Background_empty = LoadBMP("images\\rand.bmp");
    BrickSource = LoadBMP("images\\klotz.bmp");
    PlayGround = LoadBMP("images\\spielgrund.bmp");
    PlayGround_empty = LoadBMP("images\\spielgrund.bmp");
    PreviewGround = LoadBMP("images\\vorschau.bmp");
    PreviewGround_empty = LoadBMP("images\\vorschau.bmp");
    GameOver = LoadBMP("images\\gameover.bmp");
    LetterA = LoadBMP("images\\A.BMP");
    SDL_SetColorKey(LetterA, SDL_TRUE, SDL_MapRGB(LetterA->format, 0, 0, 0));
    LetterB = LoadBMP("images\\B.BMP");
    SDL_SetColorKey(LetterB, SDL_TRUE, SDL_MapRGB(LetterB->format, 0, 0, 0));
    LetterC = LoadBMP("images\\C.BMP");
    SDL_SetColorKey(LetterC, SDL_TRUE, SDL_MapRGB(LetterC->format, 0, 0, 0));
    LetterD = LoadBMP("images\\D.BMP");
    SDL_SetColorKey(LetterD, SDL_TRUE, SDL_MapRGB(LetterD->format, 0, 0, 0));
    LetterE = LoadBMP("images\\E.BMP");
    SDL_SetColorKey(LetterE, SDL_TRUE, SDL_MapRGB(LetterE->format, 0, 0, 0));
    LetterF = LoadBMP("images\\F.BMP");
    SDL_SetColorKey(LetterF, SDL_TRUE, SDL_MapRGB(LetterF->format, 0, 0, 0));
    LetterG = LoadBMP("images\\G.BMP");
    SDL_SetColorKey(LetterG, SDL_TRUE, SDL_MapRGB(LetterG->format, 0, 0, 0));
    LetterH = LoadBMP("images\\H.BMP");
    SDL_SetColorKey(LetterH, SDL_TRUE, SDL_MapRGB(LetterH->format, 0, 0, 0));
    LetterI = LoadBMP("images\\I.BMP");
    SDL_SetColorKey(LetterI, SDL_TRUE, SDL_MapRGB(LetterI->format, 0, 0, 0));
    LetterJ = LoadBMP("images\\J.BMP");
    SDL_SetColorKey(LetterJ, SDL_TRUE, SDL_MapRGB(LetterJ->format, 0, 0, 0));
    LetterK = LoadBMP("images\\K.BMP");
    SDL_SetColorKey(LetterK, SDL_TRUE, SDL_MapRGB(LetterK->format, 0, 0, 0));
    LetterL = LoadBMP("images\\L.BMP");
    SDL_SetColorKey(LetterL, SDL_TRUE, SDL_MapRGB(LetterL->format, 0, 0, 0));
    LetterM = LoadBMP("images\\M.BMP");
    SDL_SetColorKey(LetterM, SDL_TRUE, SDL_MapRGB(LetterM->format, 0, 0, 0));
    LetterN = LoadBMP("images\\N.BMP");
    SDL_SetColorKey(LetterN, SDL_TRUE, SDL_MapRGB(LetterN->format, 0, 0, 0));
    LetterO = LoadBMP("images\\O.BMP");
    SDL_SetColorKey(LetterO, SDL_TRUE, SDL_MapRGB(LetterO->format, 0, 0, 0));
    LetterP = LoadBMP("images\\P.BMP");
    SDL_SetColorKey(LetterP, SDL_TRUE, SDL_MapRGB(LetterP->format, 0, 0, 0));
    LetterQ = LoadBMP("images\\Q.BMP");
    SDL_SetColorKey(LetterQ, SDL_TRUE, SDL_MapRGB(LetterQ->format, 0, 0, 0));
    LetterR = LoadBMP("images\\R.BMP");
    SDL_SetColorKey(LetterR, SDL_TRUE, SDL_MapRGB(LetterR->format, 0, 0, 0));
    LetterS = LoadBMP("images\\S.BMP");
    SDL_SetColorKey(LetterS, SDL_TRUE, SDL_MapRGB(LetterS->format, 0, 0, 0));
    LetterT = LoadBMP("images\\T.BMP");
    SDL_SetColorKey(LetterT, SDL_TRUE, SDL_MapRGB(LetterT->format, 0, 0, 0));
    LetterU = LoadBMP("images\\U.BMP");
    SDL_SetColorKey(LetterU, SDL_TRUE, SDL_MapRGB(LetterU->format, 0, 0, 0));
    LetterV = LoadBMP("images\\V.BMP");
    SDL_SetColorKey(LetterV, SDL_TRUE, SDL_MapRGB(LetterV->format, 0, 0, 0));
    LetterW = LoadBMP("images\\W.BMP");
    SDL_SetColorKey(LetterW, SDL_TRUE, SDL_MapRGB(LetterW->format, 0, 0, 0));
    LetterX = LoadBMP("images\\X.BMP");
    SDL_SetColorKey(LetterX, SDL_TRUE, SDL_MapRGB(LetterX->format, 0, 0, 0));
    LetterY = LoadBMP("images\\Y.BMP");
    SDL_SetColorKey(LetterY, SDL_TRUE, SDL_MapRGB(LetterY->format, 0, 0, 0));
    LetterZ = LoadBMP("images\\Z.BMP");
    SDL_SetColorKey(LetterZ, SDL_TRUE, SDL_MapRGB(LetterZ->format, 0, 0, 0));
    Digit1 = LoadBMP("images\\1.BMP");
    SDL_SetColorKey(Digit1, SDL_TRUE, SDL_MapRGB(Digit1->format, 0, 0, 0));
    Digit2 = LoadBMP("images\\2.BMP");
    SDL_SetColorKey(Digit2, SDL_TRUE, SDL_MapRGB(Digit2->format, 0, 0, 0));
    Digit3 = LoadBMP("images\\3.BMP");
    SDL_SetColorKey(Digit3, SDL_TRUE, SDL_MapRGB(Digit3->format, 0, 0, 0));
    Digit4 = LoadBMP("images\\4.BMP");
    SDL_SetColorKey(Digit4, SDL_TRUE, SDL_MapRGB(Digit4->format, 0, 0, 0));
    Digit5 = LoadBMP("images\\5.BMP");
    SDL_SetColorKey(Digit5, SDL_TRUE, SDL_MapRGB(Digit5->format, 0, 0, 0));
    Digit6 = LoadBMP("images\\6.BMP");
    SDL_SetColorKey(Digit6, SDL_TRUE, SDL_MapRGB(Digit6->format, 0, 0, 0));
    Digit7 = LoadBMP("images\\7.BMP");
    SDL_SetColorKey(Digit7, SDL_TRUE, SDL_MapRGB(Digit7->format, 0, 0, 0));
    Digit8 = LoadBMP("images\\8.BMP");
    SDL_SetColorKey(Digit8, SDL_TRUE, SDL_MapRGB(Digit8->format, 0, 0, 0));
    Digit9 = LoadBMP("images\\9.BMP");
    SDL_SetColorKey(Digit9, SDL_TRUE, SDL_MapRGB(Digit9->format, 0, 0, 0));
    Digit0 = LoadBMP("images\\0.BMP");
    SDL_SetColorKey(Digit0, SDL_TRUE, SDL_MapRGB(Digit0->format, 0, 0, 0));

    InitPlayingGrid(12);

    UpdateNextBrickGrid();

    int ende = CreateBrick();

    DrawBackground();
    UpdateBricks();
    SDL_RenderPresent(Renderer);

    Running = 1;
    currentFrameTimestamp = SDL_GetTicks();
    last_fall = currentFrameTimestamp;
    lastKeyPressCommand = currentFrameTimestamp;
    lastpause = currentFrameTimestamp;

    Score = 0;
    RowsCleared = 0;
    RowsLetFallen = 0;
    TotalBricksSinceStart = 0;
    TotalBricksOnScreen = 0;
    TotalRowsCleared = 0;

    while (Running)
    {
        // ToDo this is irritating cant we somehow unify this
        // first loop just checkes for key down events when they occur (so holding them down does not spam the command)
        SDL_Event event;
        const Uint8* keystate;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            Running = 0;
                            break;
                        }

                        case SDLK_RCTRL:
                        {
                            TryRotateCounterClockwise();
                            break;
                        }

                        case SDLK_UP:
                        {
                            LetFallToGround();
                            break;
                        }
                    }

                    break;
                }

                case SDL_QUIT:
                {
                    Running = 0;
                    break;
                }
            }
        }

        // now keystates actually check what keys are being pressed right now (regardless since when)
        // this is so we can repeat commands when holding keys (see above, maybe somehow unify key checks in general or separate this "special mechanic" into a class
        keystate = SDL_GetKeyboardState(0);

        if (keystate[SDL_SCANCODE_LEFT])
        {
            if ((lastKeyPressCommand + keyPressSpamDelay) < currentFrameTimestamp)
            {
                TryMoveLeft();
                lastKeyPressCommand = currentFrameTimestamp;
            }
        }

        if (keystate[SDL_SCANCODE_RIGHT])
        {
            if ((lastKeyPressCommand + keyPressSpamDelay) < currentFrameTimestamp)
            {
                TryMoveRight();
                lastKeyPressCommand = currentFrameTimestamp;
            }
        }

        if (keystate[SDL_SCANCODE_DOWN])
        {
            TryMoveDown();
        }

        if (keystate[SDL_SCANCODE_RETURN])
        {
            if ((lastpause + 1000) < currentFrameTimestamp)
            {
                lastpause = currentFrameTimestamp;

                if (Pause == 1)
                {
                    last_fall = currentFrameTimestamp;
                    Pause = 0;
                }
                else
                {
                    last_fall = currentFrameTimestamp;
                    Pause = 1;
                }
            }
        }

        lastFrameTimestamp = currentFrameTimestamp;
        currentFrameTimestamp = SDL_GetTicks();

        frameDuration = currentFrameTimestamp - lastFrameTimestamp;

        if (Pause == 1)
        {
            last_fall = currentFrameTimestamp;
        }

        AdjustBrickFallSpeedToFrameRate(last_fall, currentFrameTimestamp);

        DrawBackground();
        UpdateBricks();
        SDL_RenderPresent(Renderer);
    }

    SDL_FreeSurface(Background);
    SDL_FreeSurface(Background_empty);
    SDL_FreeSurface(BrickSource);
    SDL_FreeSurface(PlayGround);
    SDL_FreeSurface(PlayGround_empty);
    SDL_FreeSurface(GameOver);
    SDL_FreeSurface(PreviewGround);
    SDL_FreeSurface(PreviewGround_empty);
    SDL_FreeSurface(LetterA);
    SDL_FreeSurface(LetterB);
    SDL_FreeSurface(LetterC);
    SDL_FreeSurface(LetterD);
    SDL_FreeSurface(LetterE);
    SDL_FreeSurface(LetterF);
    SDL_FreeSurface(LetterG);
    SDL_FreeSurface(LetterH);
    SDL_FreeSurface(LetterI);
    SDL_FreeSurface(LetterJ);
    SDL_FreeSurface(LetterK);
    SDL_FreeSurface(LetterL);
    SDL_FreeSurface(LetterM);
    SDL_FreeSurface(LetterN);
    SDL_FreeSurface(LetterO);
    SDL_FreeSurface(LetterP);
    SDL_FreeSurface(LetterQ);
    SDL_FreeSurface(LetterR);
    SDL_FreeSurface(LetterS);
    SDL_FreeSurface(LetterT);
    SDL_FreeSurface(LetterU);
    SDL_FreeSurface(LetterV);
    SDL_FreeSurface(LetterW);
    SDL_FreeSurface(LetterX);
    SDL_FreeSurface(LetterY);
    SDL_FreeSurface(LetterZ);

    SDL_FreeSurface(Digit0);
    SDL_FreeSurface(Digit1);
    SDL_FreeSurface(Digit2);
    SDL_FreeSurface(Digit3);
    SDL_FreeSurface(Digit4);
    SDL_FreeSurface(Digit5);
    SDL_FreeSurface(Digit6);
    SDL_FreeSurface(Digit7);
    SDL_FreeSurface(Digit8);
    SDL_FreeSurface(Digit9);

    return 0;
}
