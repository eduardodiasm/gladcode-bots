// Functions

// Move functions
void startMove();
void goToTheCenter();
void escapeFromGas();
void findAround();

// Fighting functions
void dodge();
void defendToMeleeEnemy();

// Magic functions
void getAwayFromComplot();
void runAwayFromDeath();
void isDying();

// Variables
float simTime = 0, lastSeenTime = 0;
int dodgeSide = 1, isStart = 1, isInTheCenter = 0;

loop()
{

    upgradeAGI(5);

    if(!isSafeHere())
        escapeFromGas();
    
    if(isStart)
    {
        startMove();
        isStart = 0;
    }
    
    if(getCloseEnemy())
    {
        simTime = getSimTime();
        if(doYouSeeMe())
        {
            
            attackRanged(getTargetX(), getTargetY());
            speak("repent of your sins!");
            
            // TODO getAwayFromDeath()

            //if(getHp() <= 40 && !isStunned())
    
            // If there are two or more enemies attacking me
            if (isTargetVisible() && getLastHitTime() <= 2 && getAp() >= 50 
            && doYouSeeMe() && getDistToTarget() >= 3)
            {
                getAwayFromComplot();
                if(getAp() >= 70 && !isStunned())
                    ambush();
                    
                int i = 0;
                while(!getCloseEnemy() && getLastHitTime() > 0 && i < 8)
                {
                    speak("come here!");
                    turn(90);
                    i += 1;
                }
                
            }
            
            else
            {
                 // If is charging to me
                if(getDistToTarget() <= 11 && isRunning() && getAp() >= 70 && 
                doYouSeeMe())
                {
                    speak("chill out, brother");
                    ambush();
                    stepBack();
                    stepBack();
                    stepBack();
                    stepBack();
                    stepBack();
                    stepBack();
                    stepBack();
                    turnToTarget();
                    
                }
                    
                else if(getDistToTarget() <= 3)
                {
                    if(getAp() >= 70)
                        ambush();
                    
                    // If there are a wizard here
                    if(getBurnTimeLeft() > 0)
                        stepBack();
                }
                    
            }
            
            // Dodge from enemy attacks
            if(!isStunned() && getDistToTarget() >= 3 && getLastHitTime() <= 3)
                dodge();
                
        }

        else // You don't see me
        {
            speak("your time is coming!");
            attackRanged(getTargetX(), getTargetY());
        }
    }
    
    else // Do not getCloseEnemy
    {
        
        // there are enemies
        if(getLastHitTime() <= 1.3 && !getCloseEnemy() && getBurnTimeLeft() == 0)
            turnToLastHit();
            
        // there aren't enemies
        else
        {
            lastSeenTime = getSimTime() - simTime;
            // Enemy is using ambush and he hit me  
            if(!isTargetVisible() && getLastHitTime() <= 5 && getAp() >= 70 && 
            getX() != 14 && getY() != 14 && getBurnTimeLeft() == 0)
            {
                ambush();
                int i = 0;
                while(!getCloseEnemy() && getLastHitTime() >= 1 && i < 12 && 
                isSafeHere())
                {
                    speak("show up!");
                    turn(90);
                    i += 1;
                }
            }
            
            // Enemy is using ambush and he does not hit me
            else if(lastSeenTime <= 3.5 && !isTargetVisible() && getAp() >= 70 && 
            getX() != 14 && getY() != 14 && getBurnTimeLeft() == 0) 
            {
                speak("show up, dude!");
                ambush();
                int i = 0;
                while(!getCloseEnemy() && getLastHitTime() >= 1 && i < 15 && 
                isSafeHere())
                {
                    turn(90);
                    i += 1;
                }
            }
            
            // Float on arena
            else 
            {
                if(getX() == 14 && getY() == 14)
                    isInTheCenter = 1;
                
                if(!isInTheCenter)
                    goToTheCenter();
            
                else
                {
                    findAround();
                    isInTheCenter = 0;
                }    
            }
        }
    }
    
}

// Catch the enemy by the corner when starts.
void startMove()
{
    
    stepBack();
    stepBack();
    stepBack();
    stepBack();
    stepBack();
    
    int i = 0;
    turn(90);
    
    while(!getCloseEnemy() && !getHit() && i < 5)
    {
        moveForward(1);
        i++;
    }
    
    if(getLastHitTime() <= 1)
        turnToLastHit();
    
    turn(-30);
    
    while(!getCloseEnemy() && !getHit() && i < 6)
    {
        moveForward(1);
        i++;
    }
    
    if(getLastHitTime() <= 1)
        turnToLastHit();
}


void escapeFromGas()
{
    if(!getCloseEnemy())
    {
        moveTo(12.5, 12.5);
        moveTo(12.5, 12.5);
        moveTo(12.5, 12.5);
    }
    else 
        moveTo(12.5, 12.5);
}

void goToTheCenter()
{
    while(!moveTo(14, 14) && !getCloseEnemy() && !getHit());
}

void findAround()
{
    
    turnLeft(90);
    int i = 0;
    
    while(!getCloseEnemy() && i < 6 && isSafeHere() && !getHit()) 
    {
        moveForward(1);
        i++;
    }
    
}

// Dodge from arrows/fireballs.
void dodge()
{
    if(dodgeSide % 2 == 0)
    {
        int i = 0;
        while(isSafeHere() && i < 3)
        {
            stepLeft();
            //turnToLastHit();
            i++;
        } 
        dodgeSide++;
    }
    
    else
    {
        int i = 0;
        while(isSafeHere() && i < 3)
        {
            stepRight();
            //turnToLastHit();
            i++;
        } 
        dodgeSide++;
    } 
}

// Walking in circles around enemy.
void defendToMeleeEnemy()
{
    stepLeft();
    turnToTarget();
    stepLeft();
    turnToTarget();
    stepLeft();
    turnToTarget();
    stepLeft();
    turnToTarget();
    stepLeft();
    turnToTarget();
    
}

void getAwayFromComplot()
{
    
    int me = (360 - getHead());
    int you = (360 - getLastHitAngle()), difference = 0;
    
    if (me > you)
        difference = me - you;
    else
        difference = you - me;
        
    if (difference >= 40)
    {
        speak("forgive them, father!");
        if (getTargetX() < 12.5 && getTargetY() < 12.5)
            teleport(getTargetX()-3, getTargetY()-3);
        
        else if (getTargetX() > 12.5 && getTargetY() < 12.5)
            teleport(getTargetX()+3, getTargetY()-3);
        
        else if (getTargetX() > 12.5 && getTargetY() > 12.5)
            teleport(getTargetX()+3, getTargetY()+3);
    
        else if (getTargetX() < 12.5 && getTargetY() > 12.5)
            teleport(getTargetX()-3, getTargetY()+3);
        
        turnToLastHit();
        
    }
    
}
