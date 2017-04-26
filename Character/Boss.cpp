#include "Boss.h"

Boss::Boss(int damage, Vector2<double> pos, int defTexture) : 
    Enemy(BOSSHEALTH, damage, 0, pos, defTexture)
{
    mShootDelay = 100;
    mNumStages = BOSS_STAGES;
    mFrameTime = 0;
    mCurrentStage = BOSS_STAGES - 1;
}

// Handles Animation Frame Timing and Stage Indexing (Assumed Last Stage Is Dead)
void Boss::Update()
{
    if (mHealth  == 0)
        mCurrentStage = 3;
    else if (mHealth <= BOSSHEALTH / 3)
        mCurrentStage = 2;
    else if (mHealth <= 2 * BOSSHEALTH / 3)
        mCurrentStage = 1;
    else
        mCurrentStage = 0;

    if (mCurrentStage != 0 && getTicks() - mFrameTime > 10000)
        randomizeFrame();
    else if (getTicks() - mFrameTime > 3000)
        playNextDeathFrame();
}

void Boss::TakeDamage(int damage)
{
    mHealth -= damage;
    if (mHealth <= 0)
        Die();
}

void Boss::AddFrame(int texture, Mix_Chunk *taunt)
{
    AnimationFrame frame = {texture, taunt};
    mFrames[mCurrentStage].push_back(frame);
}

void Boss::randomizeFrame()
{
    mCurrentFrame = mFrames[mCurrentStage][std::rand() % mFrames[mCurrentStage].size()];
    mFrameTime = getTicks();
}

void Boss::playNextDeathFrame()
{
    if (mCurrentDeathFrame < mFrames[mCurrentStage].size())
        mCurrentFrame = mFrames[mCurrentStage][mCurrentDeathFrame++];
    else
        mIsDead = true;
}

void Boss::Die()
{
    mIsDying = true;
    mHealth = 0;
}
