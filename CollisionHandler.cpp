#include "Objects/CollisionHandler.h"

namespace
{
    void playerZombie(GameObject& player, GameObject& zombie);
    void playerTommyTheDoll(GameObject& player, GameObject& tommyTheDoll);
    void playerGiantAnt(GameObject& player, GameObject& giantAnt);
    void playerMutantPlant(GameObject& player, GameObject& mutantPlant);
    void playerObstacle(GameObject& player, GameObject& obstacle);
    void playerFirstAidKit(GameObject& player, GameObject& firstAidKit);
    void playerHealthPotion(GameObject& player, GameObject& healthPotion);
    void playerPistolAmmo(GameObject& player, GameObject& PistolAmmo);
    void playerKey(GameObject& player, GameObject& key);
    void playerDynamite(GameObject& player, GameObject& dynamite);
    void playerFlameThrowerProjectile(GameObject& player, GameObject& flameThrowerProjectile);
    void playerPelletGunProjectile(GameObject& player, GameObject& pelletGunProjectile);
    void playerExplosiveProjectile(GameObject& player, GameObject& explosiveProjectile);

    // Zombie collision functions
    void zombieObstacle(GameObject& zombie, GameObject& obstacle);
    void zombieFlameThrowerProjectile(GameObject& zombie, GameObject& flameThrowerProjectile);
    void zombiePelletGunProjectile(GameObject& zombie, GameObject& pelletGunProjectile);
    void zombieExplosiveProjectile(GameObject& zombie, GameObject& explosiveProjectile);

    // TommyTheDoll collision functions
    void tommyTheDollObstacle(GameObject& tommyTheDoll, GameObject& obstacle);
    void tommyTheDollFlameThrowerProjectile(GameObject& tommyTheDoll, GameObject& flameThrowerProjectile);
    void tommyTheDollPelletGunProjectile(GameObject& tommyTheDoll, GameObject& pelletGunProjectile);
    void tommyTheDollExplosiveProjectile(GameObject& tommyTheDoll, GameObject& explosiveProjectile);

    // GiantAnt collision functions
    void giantAntObstacle(GameObject& giantAnt, GameObject& obstacle);
    void giantAntFlameThrowerProjectile(GameObject& giantAnt, GameObject& flameThrowerProjectile);
    void giantAntPelletGunProjectile(GameObject& giantAnt, GameObject& pelletGunProjectile);
    void giantAntExplosiveProjectile(GameObject& giantAnt, GameObject& explosiveProjectile);

    // MutantPlant collision functions
    void mutantPlantObstacle(GameObject& mutantPlant, GameObject& obstacle);
    void mutantPlantFlameThrowerProjectile(GameObject& mutantPlant, GameObject& flameThrowerProjectile);
    void mutantPlantPelletGunProjectile(GameObject& mutantPlant, GameObject& pelletGunProjectile);
    void mutantPlantExplosiveProjectile(GameObject& mutantPlant, GameObject& explosiveProjectile);

    // Projectile-Obstacle collision functions
    void flameThrowerProjectileObstacle(GameObject& flameThrowerProjectile, GameObject& obstacle);
    void pelletGunProjectileObstacle(GameObject& pelletGunProjectile, GameObject& obstacle);
    void explosiveProjectileObstacle(GameObject& explosiveProjectile, GameObject& obstacle);

    // Door collision functions
    void playerDoor(GameObject& player, GameObject& door);
    void zombieDoor(GameObject& zombie, GameObject& door);
    void tommyTheDollDoor(GameObject& tommyTheDoll, GameObject& door);
    void giantAntDoor(GameObject& giantAnt, GameObject& door);
    void mutantPlantDoor(GameObject& mutantPlant, GameObject& door);
    void flameThrowerProjectileDoor(GameObject& flameThrowerProjectile, GameObject& door);
    void pelletGunProjectileDoor(GameObject& pelletGunProjectile, GameObject& door);
    void explosiveProjectileDoor(GameObject& explosiveProjectile, GameObject& door);

    // Closet collision functions
    void playerCloset(GameObject& player, GameObject& closet);
    void zombieCloset(GameObject& zombie, GameObject& closet);
    void tommyTheDollCloset(GameObject& tommyTheDoll, GameObject& closet);
    void giantAntCloset(GameObject& giantAnt, GameObject& closet);
    void mutantPlantCloset(GameObject& mutantPlant, GameObject& closet);
    void flameThrowerProjectileCloset(GameObject& flameThrowerProjectile, GameObject& closet);
    void pelletGunProjectileCloset(GameObject& pelletGunProjectile, GameObject& closet);
    void explosiveProjectileCloset(GameObject& explosiveProjectile, GameObject& closet);

    // Survivor collision functions
    void playerSurvivor(GameObject& player, GameObject& survivor);
    void zombieSurvivor(GameObject& zombie, GameObject& survivor);
    void tommyTheDollSurvivor(GameObject& tommy, GameObject& survivor);
    void giantAntSurvivor(GameObject& ant, GameObject& survivor);
    void mutantPlantSurvivor(GameObject& plant, GameObject& survivor);
    void explosiveProjectileSurvivor(GameObject& projectile, GameObject& survivor);

    // Symmetric collision functions (for collision order independence)
    void zombiePlayer(GameObject& zombie, GameObject& player);
    void tommyTheDollPlayer(GameObject& tommyTheDoll, GameObject& player);
    void giantAntPlayer(GameObject& giantAnt, GameObject& player);
    void mutantPlantPlayer(GameObject& mutantPlant, GameObject& player);
    void obstaclePlayer(GameObject& obstacle, GameObject& player);
    void firstAidKitPlayer(GameObject& firstAidKit, GameObject& player);
    void healthPotionPlayer(GameObject& healthPotion, GameObject& player);
    void pistolAmmoPlayer(GameObject& pistolAmmo, GameObject& player);
    void keyPlayer(GameObject& key, GameObject& player);
    void dynamitePlayer(GameObject& dynamite, GameObject& player);
    void flameThrowerProjectilePlayer(GameObject& flameThrowerProjectile, GameObject& player);
    void pelletGunProjectilePlayer(GameObject& pelletGunProjectile, GameObject& player);
    void explosiveProjectilePlayer(GameObject& explosiveProjectile, GameObject& player);
    void obstacleZombie(GameObject& obstacle, GameObject& zombie);
    void obstacleTommyTheDoll(GameObject& obstacle, GameObject& tommyTheDoll);
    void obstacleGiantAnt(GameObject& obstacle, GameObject& giantAnt);
    void obstacleMutantPlant(GameObject& obstacle, GameObject& mutantPlant);
    void obstacleFlameThrowerProjectile(GameObject& obstacle, GameObject& flameThrowerProjectile);
    void obstaclePelletGunProjectile(GameObject& obstacle, GameObject& pelletGunProjectile);
    void obstacleExplosiveProjectile(GameObject& obstacle, GameObject& explosiveProjectile);
    void doorPlayer(GameObject& door, GameObject& player);
    void doorZombie(GameObject& door, GameObject& zombie);
    void doorTommyTheDoll(GameObject& door, GameObject& tommyTheDoll);
    void doorGiantAnt(GameObject& door, GameObject& giantAnt);
    void doorMutantPlant(GameObject& door, GameObject& mutantPlant);
    void doorFlameThrowerProjectile(GameObject& door, GameObject& flameThrowerProjectile);
    void doorPelletGunProjectile(GameObject& door, GameObject& pelletGunProjectile);
    void doorExplosiveProjectile(GameObject& door, GameObject& explosiveProjectile);
    void closetPlayer(GameObject& closet, GameObject& player);
    void closetZombie(GameObject& closet, GameObject& zombie);
    void closetTommyTheDoll(GameObject& closet, GameObject& tommyTheDoll);
    void closetGiantAnt(GameObject& closet, GameObject& giantAnt);
    void closetMutantPlant(GameObject& closet, GameObject& mutantPlant);
    void closetFlameThrowerProjectile(GameObject& closet, GameObject& flameThrowerProjectile);
    void closetPelletGunProjectile(GameObject& closet, GameObject& pelletGunProjectile);
    void closetExplosiveProjectile(GameObject& closet, GameObject& explosiveProjectile);
    void survivorPlayer(GameObject& survivor, GameObject& player);
    void survivorZombie(GameObject& survivor, GameObject& zombie);
    void survivorTommyTheDoll(GameObject& survivor, GameObject& tommy);
    void survivorGiantAnt(GameObject& survivor, GameObject& ant);
    void survivorMutantPlant(GameObject& survivor, GameObject& plant);
    void survivorExplosiveProjectile(GameObject& survivor, GameObject& projectile);

    void playerZombie(GameObject& player, GameObject& zombie)
    {
        Player& p = static_cast<Player&>(player);
        Zombie& z = static_cast<Zombie&>(zombie);
        p.hit(z.getDamageAtContact());
        p.setVelocity(sf::Vector2f(0.f, 0.f));
        std::cout << "Player and Zombie collision!\n";
    }

    void playerTommyTheDoll(GameObject& player, GameObject& tommyTheDoll)
    {
        Player& p = static_cast<Player&>(player);
		TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
		p.hit(t.getDamageAtContact());
		p.setVelocity(sf::Vector2f(0.f, 0.f));
		std::cout << "Player and TommyTheDoll collision!\n";
    }

    void playerGiantAnt(GameObject& player, GameObject& giantAnt)
    {
        Player& p = static_cast<Player&>(player);
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);

        p.setHealth(g.getDamageAtContact());
        p.startDragging();

        // Update the player's position based on the ant's movement
        sf::Vector2f antVelocity = g.getVelocity();
        p.setPosition(p.getPosition() + antVelocity);

        std::cout << "Player and GiantAnt collision! Player is being dragged.\n";
    }

    void playerMutantPlant(GameObject& player, GameObject& mutantPlant)
    {
		Player& p = static_cast<Player&>(player);
		MutantPlant& m = static_cast<MutantPlant&>(mutantPlant);
		p.setHealth(m.getDamageAtContact());
		p.setVelocity(sf::Vector2f(0.f, 0.f));
		std::cout << "Player and MutantPlant collision!\n";
    }

    void playerObstacle(GameObject& player, GameObject& obstacle)
    {
        Player& p = static_cast<Player&>(player);
        Obstacle& o = static_cast<Obstacle&>(obstacle);
        sf::FloatRect playerBounds = p.getGlobalBounds();
        sf::FloatRect obstacleBounds = o.getGlobalBounds();

        if (playerBounds.intersects(obstacleBounds))
        {
            // Determine the overlap on each axis
            float overlapLeft = playerBounds.left + playerBounds.width - obstacleBounds.left;
            float overlapRight = obstacleBounds.left + obstacleBounds.width - playerBounds.left;
            float overlapTop = playerBounds.top + playerBounds.height - obstacleBounds.top;
            float overlapBottom = obstacleBounds.top + obstacleBounds.height - playerBounds.top;

            // Find the smallest overlap
            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            // Adjust the player's position based on the smallest overlap
            if (minOverlapX < minOverlapY)
            {
                if (overlapLeft < overlapRight)
                {
                    p.setPosition(sf::Vector2f(obstacleBounds.left - playerBounds.width, playerBounds.top));
                }
                else
                {
                    p.setPosition(sf::Vector2f(obstacleBounds.left + obstacleBounds.width, playerBounds.top));
                }
            }
            else
            {
                if (overlapTop < overlapBottom)
                {
                    p.setPosition(sf::Vector2f(playerBounds.left, obstacleBounds.top - playerBounds.height));
                }
                else
                {
                    p.setPosition(sf::Vector2f(playerBounds.left, obstacleBounds.top + obstacleBounds.height));
                }
            }

            // Reset the player's velocity to zero
            p.setVelocity(sf::Vector2f(0.f, 0.f));
        }
    }


    void playerFirstAidKit(GameObject& player, GameObject& firstAidKit)
    {
        Player& p = static_cast<Player&>(player);
		FirstAidKit& f = static_cast<FirstAidKit&>(firstAidKit);
        f.onCollect(p);
		std::cout << "Player and FirstAidKit collision!\n";
    }

    void playerHealthPotion(GameObject& player, GameObject& healthPotion)
    {
		Player& p = static_cast<Player&>(player);
        HealthPotion& h = static_cast<HealthPotion&>(healthPotion);
        h.onCollect(p);
        std::cout << "Player and HealthPotion collision!\n";
    }

    void playerPistolAmmo(GameObject& player, GameObject& pistolAmmo)
    {
        Player& p = static_cast<Player&>(player);
        PistolAmmo& pa = static_cast<PistolAmmo&>(pistolAmmo);
        pa.onCollect(p);
        std::cout << "Player and PistolAmmo collision!\n";
    }

    void playerKey(GameObject& player, GameObject& key)
    {   
        Player& p = static_cast<Player&>(player);
		Key& k = static_cast<Key&>(key);
		k.onCollect(p);
		std::cout << "Player and Key collision!\n";
    }

    void playerDynamite(GameObject& player, GameObject& dynamite)
    {
        Player& p = static_cast<Player&>(player);
		Dynamite& d = static_cast<Dynamite&>(dynamite);
		d.onCollect(p);
		std::cout << "Player and Dynamite collision!\n";
    }

    void playerFlameThrowerProjectile(GameObject& player, GameObject& flameThrowerProjectile)
    {
        // friendly fire
    }

    void playerPelletGunProjectile(GameObject& player, GameObject& pelletGunProjectile)
    {
		// friendly fire
    }

    void playerExplosiveProjectile(GameObject& player, GameObject& explosiveProjectile)
    {
        Player& p = static_cast<Player&>(player);
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        p.hit(e.getDamage());
        std::cout << "Player hit by projectile!\n";
    }

    void zombieObstacle(GameObject& zombie, GameObject& obstacle)
    {
        Zombie& z = static_cast<Zombie&>(zombie);
        Obstacle& o = static_cast<Obstacle&>(obstacle);
        // Implement collision logic here
        z.setVelocity(sf::Vector2f(0.f, 0.f));
        std::cout << "Zombie and Obstacle collision!\n";
    }

    void zombieFlameThrowerProjectile(GameObject& zombie, GameObject& flameThrowerProjectile)
    {
        Zombie& z = static_cast<Zombie&>(zombie);
		FlameThrowerProjectile& f = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
		z.hit(f.getDamage(z.getPosition()));
		std::cout << "Zombie hit by FlameThrowerProjectile!\n";
    }

    void zombiePelletGunProjectile(GameObject& zombie, GameObject& pelletGunProjectile)
    {
		Zombie& z = static_cast<Zombie&>(zombie);
        PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
        z.hit(p.getDamage());
        std::cout << "Zombie hit by PelletGunProjectile!\n";
    }

    void zombieExplosiveProjectile(GameObject& zombie, GameObject& explosiveProjectile)
    {
        Zombie& z = static_cast<Zombie&>(zombie);
		ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
		z.hit(e.getDamage());
		std::cout << "Zombie hit by ExplosiveProjectile!\n";
    }

    void tommyTheDollObstacle(GameObject& tommyTheDoll, GameObject& obstacle)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
		Obstacle& o = static_cast<Obstacle&>(obstacle);
		t.setVelocity(sf::Vector2f(0.f, 0.f));
		std::cout << "TommyTheDoll and Obstacle collision!\n";
    }

    void tommyTheDollFlameThrowerProjectile(GameObject& tommyTheDoll, GameObject& flameThrowerProjectile)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
        FlameThrowerProjectile& f = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
        t.hit(f.getDamage(t.getPosition()));
        std::cout << "TommyTheDoll hit by FlameThrowerProjectile!\n";
    }

    void tommyTheDollPelletGunProjectile(GameObject& tommyTheDoll, GameObject& pelletGunProjectile)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
		PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
		t.hit(p.getDamage());
		std::cout << "TommyTheDoll hit by PelletGunProjectile!\n";
    }

    void tommyTheDollExplosiveProjectile(GameObject& tommyTheDoll, GameObject& explosiveProjectile)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        t.hit(e.getDamage());
        std::cout << "TommyTheDoll hit by ExplosiveProjectile!\n";
    }

    void giantAntObstacle(GameObject& giantAnt, GameObject& obstacle)
    {
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);
        Obstacle& o = static_cast<Obstacle&>(obstacle);
        g.setVelocity(sf::Vector2f(0.f, 0.f));
        std::cout << "GiantAnt and Obstacle collision!\n";
    }

    void giantAntFlameThrowerProjectile(GameObject& giantAnt, GameObject& flameThrowerProjectile)
    {
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);
		FlameThrowerProjectile& f = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
		g.hit(f.getDamage(g.getPosition()));
		std::cout << "GiantAnt hit by FlameThrowerProjectile!\n";
    }

    void giantAntPelletGunProjectile(GameObject& giantAnt, GameObject& pelletGunProjectile)
    {
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);
        PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
        g.hit(p.getDamage());
        std::cout << "GiantAnt hit by PelletGunProjectile!\n";
    }

    void giantAntExplosiveProjectile(GameObject& giantAnt, GameObject& explosiveProjectile)
    {
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        g.hit(e.getDamage());
        std::cout << "GiantAnt hit by ExplosiveProjectile!\n";
    }

    void mutantPlantObstacle(GameObject& mutantPlant, GameObject& obstacle)
    {
       // mutant plant is static
    }

    void mutantPlantFlameThrowerProjectile(GameObject& mutantPlant, GameObject& flameThrowerProjectile)
    {
        MutantPlant& m = static_cast<MutantPlant&>(mutantPlant);
        FlameThrowerProjectile& fp = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
        m.hit(fp.getDamage(m.getPosition()));
    }

    void mutantPlantPelletGunProjectile(GameObject& mutantPlant, GameObject& pelletGunProjectile)
    {
        MutantPlant& m = static_cast<MutantPlant&>(mutantPlant);
        PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
        m.hit(p.getDamage());
    }

    void mutantPlantExplosiveProjectile(GameObject& mutantPlant, GameObject& explosiveProjectile)
    {
        MutantPlant& m = static_cast<MutantPlant&>(mutantPlant);
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        m.hit(e.getDamage());
    }

    void flameThrowerProjectileObstacle(GameObject& flameThrowerProjectile, GameObject& obstacle)
    {
        FlameThrowerProjectile& fp = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
        Obstacle& o = static_cast<Obstacle&>(obstacle);
        fp.markForDeletion();
    }

    void pelletGunProjectileObstacle(GameObject& pelletGunProjectile, GameObject& obstacle)
    {
        PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
        Obstacle& o = static_cast<Obstacle&>(obstacle);
        p.markForDeletion();
    }

    void explosiveProjectileObstacle(GameObject& explosiveProjectile, GameObject& obstacle)
    {
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        Obstacle& o = static_cast<Obstacle&>(obstacle);
        e.markForDeletion();
    }

    void playerDoor(GameObject& player, GameObject& door)
    {
        Player& p = static_cast<Player&>(player);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            if (p.getInventory().useKey())
            {
                d.setOpen(true);
                std::cout << "Player unlocked the door with a key!\n";
            }
            else
            {
                std::cout << "Door is locked and player doesn't have a key.\n";
            }
        }
        else
        {
            // Allow player to pass through open door
            std::cout << "Player passed through an open door.\n";
        }
    }

    void zombieDoor(GameObject& zombie, GameObject& door)
    {
        Zombie& z = static_cast<Zombie&>(zombie);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            z.setVelocity(sf::Vector2f(0.f, 0.f));
            std::cout << "Zombie stopped by a locked door.\n";
        }
        else
        {
            // Allow zombie to pass through open door
            std::cout << "Zombie passed through an open door.\n";
        }
    }

    void tommyTheDollDoor(GameObject& tommyTheDoll, GameObject& door)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            t.setVelocity(sf::Vector2f(0.f, 0.f));
            std::cout << "TommyTheDoll stopped by a locked door.\n";
        }
        else
        {
            // Allow TommyTheDoll to pass through open door
            std::cout << "TommyTheDoll passed through an open door.\n";
        }
    }

    void giantAntDoor(GameObject& giantAnt, GameObject& door)
    {
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            g.setVelocity(sf::Vector2f(0.f, 0.f));
            std::cout << "GiantAnt stopped by a locked door.\n";
        }
        else
        {
            // Allow GiantAnt to pass through open door
            std::cout << "GiantAnt passed through an open door.\n";
        }
    }

    void mutantPlantDoor(GameObject& mutantPlant, GameObject& door)
    {
        // MutantPlant is static, so it doesn't interact with doors
    }

    void flameThrowerProjectileDoor(GameObject& flameThrowerProjectile, GameObject& door)
    {
        FlameThrowerProjectile& fp = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            fp.markForDeletion();
            std::cout << "FlameThrowerProjectile hit a closed door and was deleted.\n";
        }
        else
        {
            // Allow projectile to pass through open door
            std::cout << "FlameThrowerProjectile passed through an open door.\n";
        }
    }

    void pelletGunProjectileDoor(GameObject& pelletGunProjectile, GameObject& door)
    {
        PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            p.markForDeletion();
        }
    }

    void explosiveProjectileDoor(GameObject& explosiveProjectile, GameObject& door)
    {
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        Door& d = static_cast<Door&>(door);

        if (!d.isOpen())
        {
            e.markForDeletion();
        }
    }

    // Closet collision functions
    void playerCloset(GameObject& player, GameObject& closet)
    {
        Player& p = static_cast<Player&>(player);
        Closet& c = static_cast<Closet&>(closet);

        if (!c.isOpen())
        {
            if (p.getInventory().useKey())
            {
                c.setOpen(true);
            }
        }
    }

    void zombieCloset(GameObject& zombie, GameObject& closet)
    {
        Zombie& z = static_cast<Zombie&>(zombie);
        z.setVelocity(sf::Vector2f(0.f, 0.f));
    }

    void tommyTheDollCloset(GameObject& tommyTheDoll, GameObject& closet)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommyTheDoll);
        t.setVelocity(sf::Vector2f(0.f, 0.f));
    }

    void giantAntCloset(GameObject& giantAnt, GameObject& closet)
    {
        GiantAnt& g = static_cast<GiantAnt&>(giantAnt);
        g.setVelocity(sf::Vector2f(0.f, 0.f));
    }

    void mutantPlantCloset(GameObject& mutantPlant, GameObject& closet)
    {
        // MutantPlant is static, so it doesn't interact with closets
    }

    void flameThrowerProjectileCloset(GameObject& flameThrowerProjectile, GameObject& closet)
    {
        FlameThrowerProjectile& fp = static_cast<FlameThrowerProjectile&>(flameThrowerProjectile);
        fp.markForDeletion();
        std::cout << "FlameThrowerProjectile hit a closet and was deleted.\n";
    }

    void pelletGunProjectileCloset(GameObject& pelletGunProjectile, GameObject& closet)
    {
        PelletGunProjectile& p = static_cast<PelletGunProjectile&>(pelletGunProjectile);
        p.markForDeletion();
        std::cout << "PelletGunProjectile hit a closet and was deleted.\n";
    }

    void explosiveProjectileCloset(GameObject& explosiveProjectile, GameObject& closet)
    {
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(explosiveProjectile);
        e.markForDeletion();
        std::cout << "ExplosiveProjectile hit a closet and was deleted.\n";
    }

    void playerSurvivor(GameObject& player, GameObject& survivor)
    {
        // Mark survivor for deletion and add score to player
        Player& p = static_cast<Player&>(player);
        Survivor& s = static_cast<Survivor&>(survivor);
        survivor.markForDeletion();
        p.addScore(s.getScore());
    }

    void zombieSurvivor(GameObject& zombie, GameObject& survivor)
    {
        Zombie& z = static_cast<Zombie&>(zombie);
        Survivor& s = static_cast<Survivor&>(survivor);
        s.hit(z.getDamageAtContact());
    }

    void tommyTheDollSurvivor(GameObject& tommy, GameObject& survivor)
    {
        TommyTheDoll& t = static_cast<TommyTheDoll&>(tommy);
        Survivor& s = static_cast<Survivor&>(survivor);
        s.hit(t.getDamageAtContact());
    }

    void giantAntSurvivor(GameObject& ant, GameObject& survivor)
    {
        GiantAnt& a = static_cast<GiantAnt&>(ant);
        Survivor& s = static_cast<Survivor&>(survivor);
        s.hit(a.getDamageAtContact());
    }

    void mutantPlantSurvivor(GameObject& plant, GameObject& survivor)
    {
        MutantPlant& m = static_cast<MutantPlant&>(plant);
        Survivor& s = static_cast<Survivor&>(survivor);
        s.hit(m.getDamageAtContact());
    }

    void explosiveProjectileSurvivor(GameObject& projectile, GameObject& survivor)
    {
        ExplosiveProjectile& e = static_cast<ExplosiveProjectile&>(projectile);
        Survivor& s = static_cast<Survivor&>(survivor);
        s.hit(e.getDamage());
        e.markForDeletion();
    }

    // Secondary collision functions for symmetry
    void zombiePlayer(GameObject& zombie, GameObject& player)
    {
        playerZombie(player, zombie);
    }

    void tommyTheDollPlayer(GameObject& tommyTheDoll, GameObject& player)
    {
		playerTommyTheDoll(player, tommyTheDoll);
    }

    void giantAntPlayer(GameObject& giantAnt, GameObject& player)
    {
		playerGiantAnt(player, giantAnt);
    }

    void mutantPlantPlayer(GameObject& mutantPlant, GameObject& player)
    {
        playerMutantPlant(player, mutantPlant);
    }

    void obstaclePlayer(GameObject& obstacle, GameObject& player)
    {
        playerObstacle(player, obstacle);
    }

    void firstAidKitPlayer(GameObject& firstAidKit, GameObject& player)
    {
        playerFirstAidKit(player, firstAidKit);
    }

    void healthPotionPlayer(GameObject& healthPotion, GameObject& player)
    {
        playerHealthPotion(player, healthPotion);
    }

    void pistolAmmoPlayer(GameObject& pistolAmmo, GameObject& player)
    {
        playerPistolAmmo(player, pistolAmmo);
    }

    void keyPlayer(GameObject& key, GameObject& player)
    {
        playerKey(player, key);
    }

    void dynamitePlayer(GameObject& dynamite, GameObject& player)
    {
        playerDynamite(player, dynamite);
    }

    void flameThrowerProjectilePlayer(GameObject& flameThrowerProjectile, GameObject& player)
    {
        playerFlameThrowerProjectile(player, flameThrowerProjectile);
    }

    void pelletGunProjectilePlayer(GameObject& pelletGunProjectile, GameObject& player)
    {
        playerPelletGunProjectile(player, pelletGunProjectile);
    }

    void explosiveProjectilePlayer(GameObject& explosiveProjectile, GameObject& player)
    {
        playerExplosiveProjectile(player, explosiveProjectile);
    }

    void obstacleZombie(GameObject& obstacle, GameObject& zombie)
    {
        zombieObstacle(zombie, obstacle);
    }

    void obstacleTommyTheDoll(GameObject& obstacle, GameObject& tommyTheDoll)
    {
        tommyTheDollObstacle(tommyTheDoll, obstacle);
    }

    void obstacleGiantAnt(GameObject& obstacle, GameObject& giantAnt)
    {
        giantAntObstacle(giantAnt, obstacle);
    }

    void obstacleMutantPlant(GameObject& obstacle, GameObject& mutantPlant)
    {
        mutantPlantObstacle(mutantPlant, obstacle);
    }

    void obstacleFlameThrowerProjectile(GameObject& obstacle, GameObject& flameThrowerProjectile)
    {
        flameThrowerProjectileObstacle(flameThrowerProjectile, obstacle);
    }

    void obstaclePelletGunProjectile(GameObject& obstacle, GameObject& pelletGunProjectile)
    {
        pelletGunProjectileObstacle(pelletGunProjectile, obstacle);
    }

    void obstacleExplosiveProjectile(GameObject& obstacle, GameObject& explosiveProjectile)
    {
        explosiveProjectileObstacle(explosiveProjectile, obstacle);
    }

    void doorPlayer(GameObject& door, GameObject& player) { playerDoor(player, door); }
    void doorZombie(GameObject& door, GameObject& zombie) { zombieDoor(zombie, door); }
    void doorTommyTheDoll(GameObject& door, GameObject& tommyTheDoll) { tommyTheDollDoor(tommyTheDoll, door); }
    void doorGiantAnt(GameObject& door, GameObject& giantAnt) { giantAntDoor(giantAnt, door); }
    void doorMutantPlant(GameObject& door, GameObject& mutantPlant) { mutantPlantDoor(mutantPlant, door); }
    void doorFlameThrowerProjectile(GameObject& door, GameObject& flameThrowerProjectile) { flameThrowerProjectileDoor(flameThrowerProjectile, door); }
    void doorPelletGunProjectile(GameObject& door, GameObject& pelletGunProjectile) { pelletGunProjectileDoor(pelletGunProjectile, door); }
    void doorExplosiveProjectile(GameObject& door, GameObject& explosiveProjectile) { explosiveProjectileDoor(explosiveProjectile, door); }
    void closetPlayer(GameObject& closet, GameObject& player) { playerCloset(player, closet); }
    void closetZombie(GameObject& closet, GameObject& zombie) { zombieCloset(zombie, closet); }
    void closetTommyTheDoll(GameObject& closet, GameObject& tommyTheDoll) { tommyTheDollCloset(tommyTheDoll, closet); }
    void closetGiantAnt(GameObject& closet, GameObject& giantAnt) { giantAntCloset(giantAnt, closet); }
    void closetMutantPlant(GameObject& closet, GameObject& mutantPlant) { mutantPlantCloset(mutantPlant, closet); }
    void closetFlameThrowerProjectile(GameObject& closet, GameObject& flameThrowerProjectile) { flameThrowerProjectileCloset(flameThrowerProjectile, closet); }
    void closetPelletGunProjectile(GameObject& closet, GameObject& pelletGunProjectile) { pelletGunProjectileCloset(pelletGunProjectile, closet); }
    void closetExplosiveProjectile(GameObject& closet, GameObject& explosiveProjectile) { explosiveProjectileCloset(explosiveProjectile, closet); }
    
    void survivorPlayer(GameObject& survivor, GameObject& player)
    {
        playerSurvivor(player, survivor);
    }

    void survivorZombie(GameObject& survivor, GameObject& zombie)
    {
        zombieSurvivor(zombie, survivor);
    }

    void survivorTommyTheDoll(GameObject& survivor, GameObject& tommy)
    {
        tommyTheDollSurvivor(tommy, survivor);
    }

    void survivorGiantAnt(GameObject& survivor, GameObject& ant)
    {
        giantAntSurvivor(ant, survivor);
    }

    void survivorMutantPlant(GameObject& survivor, GameObject& plant)
    {
        mutantPlantSurvivor(plant, survivor);
    }

    void survivorExplosiveProjectile(GameObject& survivor, GameObject& projectile)
    {
        explosiveProjectileSurvivor(projectile, survivor);
    }

    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using KeyIns = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<KeyIns, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        // Player collisions
        phm[KeyIns(typeid(Player), typeid(Zombie))] = &playerZombie;
        phm[KeyIns(typeid(Player), typeid(TommyTheDoll))] = &playerTommyTheDoll;
        phm[KeyIns(typeid(Player), typeid(GiantAnt))] = &playerGiantAnt;
        phm[KeyIns(typeid(Player), typeid(MutantPlant))] = &playerMutantPlant;
        phm[KeyIns(typeid(Player), typeid(Obstacle))] = &playerObstacle;
        phm[KeyIns(typeid(Player), typeid(FirstAidKit))] = &playerFirstAidKit;
        phm[KeyIns(typeid(Player), typeid(HealthPotion))] = &playerHealthPotion;
        phm[KeyIns(typeid(Player), typeid(PistolAmmo))] = &playerPistolAmmo;
        phm[KeyIns(typeid(Player), typeid(Key))] = &playerKey;
        phm[KeyIns(typeid(Player), typeid(Dynamite))] = &playerDynamite;
        phm[KeyIns(typeid(Player), typeid(FlameThrowerProjectile))] = &playerFlameThrowerProjectile;
        phm[KeyIns(typeid(Player), typeid(PelletGunProjectile))] = &playerPelletGunProjectile;
        phm[KeyIns(typeid(Player), typeid(ExplosiveProjectile))] = &playerExplosiveProjectile;

        // Zombie collisions
        phm[KeyIns(typeid(Zombie), typeid(Obstacle))] = &zombieObstacle;
        phm[KeyIns(typeid(Zombie), typeid(FlameThrowerProjectile))] = &zombieFlameThrowerProjectile;
        phm[KeyIns(typeid(Zombie), typeid(PelletGunProjectile))] = &zombiePelletGunProjectile;
        phm[KeyIns(typeid(Zombie), typeid(ExplosiveProjectile))] = &zombieExplosiveProjectile;

        // TommyTheDoll collisions
        phm[KeyIns(typeid(TommyTheDoll), typeid(Obstacle))] = &tommyTheDollObstacle;
        phm[KeyIns(typeid(TommyTheDoll), typeid(FlameThrowerProjectile))] = &tommyTheDollFlameThrowerProjectile;
        phm[KeyIns(typeid(TommyTheDoll), typeid(PelletGunProjectile))] = &tommyTheDollPelletGunProjectile;
        phm[KeyIns(typeid(TommyTheDoll), typeid(ExplosiveProjectile))] = &tommyTheDollExplosiveProjectile;

        // GiantAnt collisions
        phm[KeyIns(typeid(GiantAnt), typeid(Obstacle))] = &giantAntObstacle;
        phm[KeyIns(typeid(GiantAnt), typeid(FlameThrowerProjectile))] = &giantAntFlameThrowerProjectile;
        phm[KeyIns(typeid(GiantAnt), typeid(PelletGunProjectile))] = &giantAntPelletGunProjectile;
        phm[KeyIns(typeid(GiantAnt), typeid(ExplosiveProjectile))] = &giantAntExplosiveProjectile;

        // MutantPlant collisions
        phm[KeyIns(typeid(MutantPlant), typeid(Obstacle))] = &mutantPlantObstacle;
        phm[KeyIns(typeid(MutantPlant), typeid(FlameThrowerProjectile))] = &mutantPlantFlameThrowerProjectile;
        phm[KeyIns(typeid(MutantPlant), typeid(PelletGunProjectile))] = &mutantPlantPelletGunProjectile;
        phm[KeyIns(typeid(MutantPlant), typeid(ExplosiveProjectile))] = &mutantPlantExplosiveProjectile;

        // Projectile-Obstacle collisions
        phm[KeyIns(typeid(FlameThrowerProjectile), typeid(Obstacle))] = &flameThrowerProjectileObstacle;
        phm[KeyIns(typeid(PelletGunProjectile), typeid(Obstacle))] = &pelletGunProjectileObstacle;
        phm[KeyIns(typeid(ExplosiveProjectile), typeid(Obstacle))] = &explosiveProjectileObstacle;

        phm[KeyIns(typeid(Player), typeid(Door))] = &playerDoor;
        phm[KeyIns(typeid(Zombie), typeid(Door))] = &zombieDoor;
        phm[KeyIns(typeid(TommyTheDoll), typeid(Door))] = &tommyTheDollDoor;
        phm[KeyIns(typeid(GiantAnt), typeid(Door))] = &giantAntDoor;
        phm[KeyIns(typeid(MutantPlant), typeid(Door))] = &mutantPlantDoor;
        phm[KeyIns(typeid(FlameThrowerProjectile), typeid(Door))] = &flameThrowerProjectileDoor;
        phm[KeyIns(typeid(PelletGunProjectile), typeid(Door))] = &pelletGunProjectileDoor;
        phm[KeyIns(typeid(ExplosiveProjectile), typeid(Door))] = &explosiveProjectileDoor;

        phm[KeyIns(typeid(Player), typeid(Closet))] = &playerCloset;
        phm[KeyIns(typeid(Zombie), typeid(Closet))] = &zombieCloset;
        phm[KeyIns(typeid(TommyTheDoll), typeid(Closet))] = &tommyTheDollCloset;
        phm[KeyIns(typeid(GiantAnt), typeid(Closet))] = &giantAntCloset;
        phm[KeyIns(typeid(MutantPlant), typeid(Closet))] = &mutantPlantCloset;
        phm[KeyIns(typeid(FlameThrowerProjectile), typeid(Closet))] = &flameThrowerProjectileCloset;
        phm[KeyIns(typeid(PelletGunProjectile), typeid(Closet))] = &pelletGunProjectileCloset;
        phm[KeyIns(typeid(ExplosiveProjectile), typeid(Closet))] = &explosiveProjectileCloset;

        // Survivor collisions
        phm[KeyIns(typeid(Player), typeid(Survivor))] = &playerSurvivor;
        phm[KeyIns(typeid(Zombie), typeid(Survivor))] = &zombieSurvivor;
        phm[KeyIns(typeid(TommyTheDoll), typeid(Survivor))] = &tommyTheDollSurvivor;
        phm[KeyIns(typeid(GiantAnt), typeid(Survivor))] = &giantAntSurvivor;
        phm[KeyIns(typeid(MutantPlant), typeid(Survivor))] = &mutantPlantSurvivor;
        phm[KeyIns(typeid(ExplosiveProjectile), typeid(Survivor))] = &explosiveProjectileSurvivor;

        // Symmetric collisions (for collision order independence)
        phm[KeyIns(typeid(Zombie), typeid(Player))] = &zombiePlayer;
        phm[KeyIns(typeid(TommyTheDoll), typeid(Player))] = &tommyTheDollPlayer;
        phm[KeyIns(typeid(GiantAnt), typeid(Player))] = &giantAntPlayer;
        phm[KeyIns(typeid(MutantPlant), typeid(Player))] = &mutantPlantPlayer;
        phm[KeyIns(typeid(Obstacle), typeid(Player))] = &obstaclePlayer;
        phm[KeyIns(typeid(FirstAidKit), typeid(Player))] = &firstAidKitPlayer;
        phm[KeyIns(typeid(HealthPotion), typeid(Player))] = &healthPotionPlayer;
        phm[KeyIns(typeid(PistolAmmo), typeid(Player))] = &pistolAmmoPlayer;
        phm[KeyIns(typeid(Key), typeid(Player))] = &keyPlayer;
        phm[KeyIns(typeid(Dynamite), typeid(Player))] = &dynamitePlayer;
        phm[KeyIns(typeid(FlameThrowerProjectile), typeid(Player))] = &flameThrowerProjectilePlayer;
        phm[KeyIns(typeid(PelletGunProjectile), typeid(Player))] = &pelletGunProjectilePlayer;
        phm[KeyIns(typeid(ExplosiveProjectile), typeid(Player))] = &explosiveProjectilePlayer;
        phm[KeyIns(typeid(Obstacle), typeid(Zombie))] = &obstacleZombie;
        phm[KeyIns(typeid(Obstacle), typeid(TommyTheDoll))] = &obstacleTommyTheDoll;
        phm[KeyIns(typeid(Obstacle), typeid(GiantAnt))] = &obstacleGiantAnt;
        phm[KeyIns(typeid(Obstacle), typeid(MutantPlant))] = &obstacleMutantPlant;
        phm[KeyIns(typeid(Obstacle), typeid(FlameThrowerProjectile))] = &obstacleFlameThrowerProjectile;
        phm[KeyIns(typeid(Obstacle), typeid(PelletGunProjectile))] = &obstaclePelletGunProjectile;
        phm[KeyIns(typeid(Obstacle), typeid(ExplosiveProjectile))] = &obstacleExplosiveProjectile;
        phm[KeyIns(typeid(Door), typeid(Player))] = &doorPlayer;
        phm[KeyIns(typeid(Door), typeid(Zombie))] = &doorZombie;
        phm[KeyIns(typeid(Door), typeid(TommyTheDoll))] = &doorTommyTheDoll;
        phm[KeyIns(typeid(Door), typeid(GiantAnt))] = &doorGiantAnt;
        phm[KeyIns(typeid(Door), typeid(MutantPlant))] = &doorMutantPlant;
        phm[KeyIns(typeid(Door), typeid(FlameThrowerProjectile))] = &doorFlameThrowerProjectile;
        phm[KeyIns(typeid(Door), typeid(PelletGunProjectile))] = &doorPelletGunProjectile;
        phm[KeyIns(typeid(Door), typeid(ExplosiveProjectile))] = &doorExplosiveProjectile;
        phm[KeyIns(typeid(Closet), typeid(Player))] = &closetPlayer;
        phm[KeyIns(typeid(Closet), typeid(Zombie))] = &closetZombie;
        phm[KeyIns(typeid(Closet), typeid(TommyTheDoll))] = &closetTommyTheDoll;
        phm[KeyIns(typeid(Closet), typeid(GiantAnt))] = &closetGiantAnt;
        phm[KeyIns(typeid(Closet), typeid(MutantPlant))] = &closetMutantPlant;
        phm[KeyIns(typeid(Closet), typeid(FlameThrowerProjectile))] = &closetFlameThrowerProjectile;
        phm[KeyIns(typeid(Closet), typeid(PelletGunProjectile))] = &closetPelletGunProjectile;
        phm[KeyIns(typeid(Closet), typeid(ExplosiveProjectile))] = &closetExplosiveProjectile;
        phm[KeyIns(typeid(Survivor), typeid(Player))] = &playerSurvivor;
        phm[KeyIns(typeid(Survivor), typeid(Zombie))] = &zombieSurvivor;
        phm[KeyIns(typeid(Survivor), typeid(TommyTheDoll))] = &tommyTheDollSurvivor;
        phm[KeyIns(typeid(Survivor), typeid(GiantAnt))] = &giantAntSurvivor;
        phm[KeyIns(typeid(Survivor), typeid(MutantPlant))] = &mutantPlantSurvivor;
        phm[KeyIns(typeid(Survivor), typeid(ExplosiveProjectile))] = &explosiveProjectileSurvivor;

        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (phf)
    {
        phf(object1, object2);
    }
}
//void processCollision(GameObject& object1, GameObject& object2)
//{
//    auto phf = lookup(typeid(object1), typeid(object2));
//    if (!phf)
//    {
//        throw UnknownCollision(object1, object2);
//    }
//    phf(object1, object2);
//}