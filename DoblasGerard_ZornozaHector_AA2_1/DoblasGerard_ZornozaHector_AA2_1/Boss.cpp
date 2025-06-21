#include "Boss.h"

Boss::Boss(const Settings& settings, Map& map) 
{
    health = settings.BIGSMOKE_HP;
    damage = settings.BIGSMOKE_DM;
}

Boss::~Boss(){}

bool Boss::BossFound(int posX, int posY, Map& map)
{
    if (map.box[posY - 1][posX] == Boxes::BIGSMOKE)
        return true;
    else if (map.box[posY + 1][posX] == Boxes::BIGSMOKE)
        return true;
    else if (map.box[posY][posX + 1] == Boxes::BIGSMOKE)
        return true;
    else if (map.box[posY][posX - 1] == Boxes::BIGSMOKE)
        return true;
    else
        return false;
}


void Boss::BossAttack(int cJX, int cJY, Map& map, const Settings& settings, int& playerHealth)
{
    now = chrono::system_clock::now();
    elapsed_seconds = now - lastAttackTime;

    
    if (elapsed_seconds.count() >= 1.0 && cJX > (settings.COLUMNS / 3) * 2)
    {
        lastAttackTime = now;
        playerHealth = playerHealth - settings.BIGSMOKE_DM;
    }
}