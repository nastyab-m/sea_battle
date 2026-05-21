#include "types.h"
#include "bot.h"
#include "board.h"
#include <vector>
#include <cstdlib>
#include <ctime>

static std::vector<Point> queue;
static Result lastResult;
static Point lastPoint;

void ResetBot() {
    queue.clear();
    lastResult = Result::Invalid;
    srand((unsigned)time(0));
}

static void AddAround(int px, int py) {
    int offX[] = {1, -1, 0, 0};
    int offY[] = {0, 0, 1, -1};
    
    for (int i = 0; i < 4; i++) {
        int nextX = px + offX[i];
        int nextY = py + offY[i];
        
        if (InBounds(nextX, nextY)) {
            queue.push_back({nextX, nextY});
        }
    }
}

Point MakeBotMove() {
    if (!queue.empty()) {
        Point selected = queue.back();
        queue.pop_back();
        lastPoint = selected;
        return selected;
    }
    
    int randomX = rand() % BOARD_SIZE;
    int randomY = rand() % BOARD_SIZE;

    lastPoint = {randomX, randomY};
    
    return lastPoint;
}

void FeedBotResult(Result outcome, Point coordinates) {
    lastResult = outcome;

    if (outcome == Result::Hit) {
        AddAround(coordinates.x, coordinates.y);
    } else if (outcome == Result::Sink) {
        queue.clear();
    }
}

Point GetBotShot() {
    return MakeBotMove();
}

void SetBotResult(Result result) {
    FeedBotResult(result, lastPoint);
}