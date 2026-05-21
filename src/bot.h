#pragma once
#include "types.h"

void ResetBot();
Point MakeBotMove();
void FeedBotResult(Result outcome, Point coordinates);
Point GetBotShot();
void SetBotResult(Result result);
