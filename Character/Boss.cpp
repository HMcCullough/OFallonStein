#include "Boss.h"

//Deals with complex animation of the boss
Boss::Boss(int damage, Vector2<double> pos, int defTexture) : 
    Enemy(BOSSHEALTH, damage, 0, pos, defTexture)
{
    mShootDelay = 50;
    mNumStages = BOSS_STAGES;
    mFrameTime = 0;
    mCurrentStage = BOSS_STAGES - 1;
    mIsDying = false;
    mCurrentDeathFrame = 0;
}

// Handles Animation Frame Timing and Stage Indexing (Assumed Last Stage Is Dead)
// return whether or not boss died
bool Boss::Update()
{
    bool changed = false;
    if (mHealth == 0 && mCurrentStage > 0)
    {
        mCurrentStage = 0;
        changed = true;
    }
    else if (mHealth <= BOSSHEALTH / 3 && mCurrentStage > 1)
    {
        mCurrentStage = 1;
        changed = true;
    }
    else if (mHealth <= 2 * BOSSHEALTH / 3 && mCurrentStage > 2)
    {
        mCurrentStage = 2;
        changed = true;
    }

    if (mCurrentStage == 0)
    {
        if (getTicks() - mFrameTime > 1000)
            playNextDeathFrame();
    }
    else
    {
        if (getTicks() - mFrameTime > 10000 || changed)
            randomizeFrame();
    }
    return mIsDead;
}

void Boss::TakeDamage(int damage)
{
    mHealth -= damage;
    if (mHealth <= 0)
        Die();
}

bool Boss::CanShoot()
{
	return mOldShotTime++ > mShotTime && !mIsDying;
}

void Boss::AddFrame(int texture, Mix_Chunk *taunt, int stage)
{
    AnimationFrame frame = {texture, taunt};
    mFrames[stage].push_back(frame);
}

bool Boss::isDying() const { return mIsDying; }

void Boss::randomizeFrame()
{
    if (mIsDying)
        return;
    mCurrentFrame = mFrames[mCurrentStage][std::rand() % mFrames[mCurrentStage].size()];
    setTexture(mCurrentFrame.texture);
    playSound(mCurrentFrame.sound);
    mFrameTime = getTicks();
}

void Boss::playNextDeathFrame()
{
    if (mCurrentDeathFrame < mFrames[mCurrentStage].size())
    {
        mCurrentFrame = mFrames[mCurrentStage][mCurrentDeathFrame++];
        setTexture(mCurrentFrame.texture);
        if (mCurrentFrame.sound)
            playSound(mCurrentFrame.sound);
    }
    else
        mIsDead = true;

    mFrameTime = getTicks();
}

void Boss::Die()
{
    mIsDying = true;
    mHealth = 0;
}
