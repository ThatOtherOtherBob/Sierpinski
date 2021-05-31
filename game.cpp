#include "game.hpp"
#include "ButtonEventCreator.hpp"

using namespace blit;

int iterations = 40000;
bool homeHit = false;
ButtonEventCreator events;
const int SCREEN_WIDTH = 320, SCREEN_HEIGHT = 240, BYTES_PER_PIXEL = 3;
Size bounds(SCREEN_WIDTH, SCREEN_HEIGHT);
uint8_t buffer[SCREEN_WIDTH * SCREEN_HEIGHT * BYTES_PER_PIXEL];
Surface canvas(buffer, PixelFormat::RGB, bounds);

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init()
{
    set_screen_mode(blit::ScreenMode::hires); // 320x240
    screen.alpha = 255;
    screen.mask = nullptr;

    DrawTriangle();
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the 
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time)
{
    CLS();
    screen.blit(&canvas, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Point(0, 0));
}
///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
int z = 0;
void update(uint32_t time)
{
    for (ButtonsEnum button : events.GenerateEvents(blit::buttons))
        switch (button)
        {
        case ButtonsEnum::Up:
            iterations += 1000;
            DrawTriangle();
            break;
        case ButtonsEnum::Down:
            iterations -= 1000;
            if (iterations < 0)
                iterations = 0;
            DrawTriangle();
            break;
        case ButtonsEnum::Left:
            iterations += 10000;
            DrawTriangle();
            break;
        case ButtonsEnum::Right:
            iterations -= 10000;
            if (iterations < 0)
                iterations = 0;
            DrawTriangle();
            break;
        default:
            break;
        }
}

void DrawTriangle()
{
    const int MAX_WIDTH = SCREEN_WIDTH - 1, MAX_HEIGHT = SCREEN_HEIGHT - 1, HALF_WIDTH = SCREEN_WIDTH / 2;
    const int DISTANCE_FROM_TOP = 0;

    float x = 32767 / MAX_WIDTH, y = 32767 / MAX_HEIGHT;
    x = std::rand() / x;
    y = std::rand() / y;

    canvas.pen = Pen(0, 0, 0);
    canvas.clear();
    
    canvas.pen = Pen(255, 255, 255);

    for (int c = iterations; c > 0; c--)
    {
        switch (blit::random() % 3)
        {
        case 0:
            x /= 2;
            y /= 2;
            break;
        case 1:
            x = (x + MAX_WIDTH) / 2;
            y /= 2;
            break;
        default:
            x = (x + HALF_WIDTH) / 2;
            y = (y + MAX_HEIGHT) / 2;
            break;
        }

        canvas.pixel(Point(x, MAX_HEIGHT - y + DISTANCE_FROM_TOP));
    }

    canvas.text(std::to_string(iterations) + " iterations.", minimal_font, Point(0, 0));
    canvas.text("Adjust with d-pad.", minimal_font, Point(0, 10));
}

void CLS()
{
    screen.pen = Pen(255, 0, 0);
    screen.clear();
}