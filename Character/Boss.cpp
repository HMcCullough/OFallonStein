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
        mCurrentStage = 0;
    else if (mHealth <= BOSSHEALTH / 3)
        mCurrentStage = 1;
    else if (mHealth <= 2 * BOSSHEALTH / 3)
        mCurrentStage = 2;
    else
        mCurrentStage = 3;

    if (mCurrentStage != 0 && getTicks() - mFrameTime > 10000)
        randomizeFrame();
    else if (mCurrentStage == 0 && getTicks() - mFrameTime > 30000)
        playNextDeathFrame();
}

void Boss::TakeDamage(int damage)
{
    mHealth -= damage;
    if (mHealth <= 0)
        Die();
}

void Boss::AddFrame(int texture, Mix_Chunk *taunt, int stage)
{
    AnimationFrame frame = {texture, taunt};
    mFrames[stage].push_back(frame);
}

bool Boss::isDying() const { return mIsDying; }

void Boss::randomizeFrame()
{
    mCurrentFrame = mFrames[mCurrentStage][std::rand() % mFrames[mCurrentStage].size()];
    setTexture(mCurrentFrame.texture);
    playSound(mCurrentFrame.sound);
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
