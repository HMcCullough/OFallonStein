#pragma once
#include "Enemy.h"

struct AnimationFrame
{
    int texture;
    Mix_Chunk *sound;
};

class Boss : public Enemy
{
public:
    Boss(int damage, Vector2<double> pos, int texture);

    void AddFrame(int texture, Mix_Chunk *taunt);
    void Update();
    
    // Boss Specific Implementations
    void TakeDamage(int damage);
	void Shoot();

private:
    std::vector<AnimationFrame> mFrames[BOSS_STAGES];
    AnimationFrame mCurrentFrame;

    int mCurrentStage, mNumStages, mCurrentDeathFrame;
    unsigned long mFrameTime;
    bool mIsDying;

    void randomizeFrame();
    void playNextDeathFrame();
    void Die();
};
