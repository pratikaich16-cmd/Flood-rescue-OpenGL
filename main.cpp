#include<windows.h>
#include<mmsystem.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.1415926



float sunX = 0.75;
float cloudX = -1.0;
float personX = -1.0;
float wave = 0.0;

// Scene 2 Variables
float rainY = 0.0;
bool lightning = false;
int flashCount = 0;

// Scene 3 / 4 Variables
float helicopterX = -1.2;
float floodLevel = -0.75;
bool houseLight = false;
float ropeY=0.65;
bool rescue=false;
float rotorAngle=0;
float helicopterY=0;
float searchLight=0;
float lightDirection=true;

const float FLOOD_MAX = -0.05f;


int rescueStage = 0;


bool villagerAttached = false;
bool villagerInside = false;
float villagerX = -0.50f;
float villagerY = 0.48f;



float boatX = -1.2f;
bool boatStart = false;



float boat2X = -1.2f;
int boatRescueStage = 0;


bool villager2Attached = false;
bool villager2Rescued = false;
float villager2X = 0.20f;
float villager2Y = 0.05f;

bool villager3Attached = false;
bool villager3Rescued = false;
float villager3X = 0.38f;
float villager3Y = 0.05f;

float boat3X = -1.3f;



float skyT = 0.0f;


float hammerAngle = 0.0f;
bool hammerUp = true;
bool housesRepaired = false;



float bellAngle = 0.0f;
bool bellSwingRight = true;
float saplingScale = 0.2f;
bool saplingGrowing = true;
float flagRiseY = 0.0f;
float flagWave = 0.0f;


float sirenAngle = 0.0f;
float warnScale = 1.0f;
bool warnGrow = true;
float patrolBoatX = -1.2f;
float bannerFloat = 0.0f;


float windmillAngle = 0.0f;
float birdX = -1.2f;
float birdX2 = -0.4f;
float flowerPulse = 0.0f;
float lampSwing = 0.0f;
bool lampSwingRight = true;
float debrisX1 = -1.2f;
float debrisX2 = 1.2f;
float buoyBob = 0.0f;
float beaconAngle = 0.0f;

int scene = 1;
int sceneTimer = 0;
const int totalScenes = 10;


void drawBitmapText(float x,float y,void* font,const char* text)
{
    glRasterPos2f(x,y);

    for(const char* c=text; *c!='\0'; c++)
        glutBitmapCharacter(font,*c);
}

void circle(float x,float y,float r)
{
    glBegin(GL_POLYGON);

    for(int i=0;i<360;i++)
    {
        float angle=i*PI/180;
        glVertex2f(x+r*cos(angle),y+r*sin(angle));
    }

    glEnd();
}


//==========================
// AUDIO SYSTEM
//==========================

void stopAudio()
{
    PlaySound(NULL, NULL, 0);
}

void playSceneAudio(int s)
{
    stopAudio();

    switch(s)
    {
        case 1:
            PlaySound("audio\\village.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 2:
            PlaySound("audio\\storm.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 3:
            PlaySound("audio\\flood.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 4:
            PlaySound("audio\\helicopter.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 5:
            PlaySound("audio\\boat.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 6:
            PlaySound("audio\\calm.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 7:
            PlaySound("audio\\hope.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 8:
            PlaySound("audio\\repair.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 9:
            PlaySound("audio\\memorial.wav", NULL, SND_ASYNC | SND_LOOP);
            break;

        case 10:
            PlaySound("audio\\finale.wav", NULL, SND_ASYNC | SND_LOOP);
            break;
    }
}

void changeScene(int newScene)
{
    if(newScene < 1 || newScene > totalScenes)
        return;

    scene = newScene;
    sceneTimer = 0;


    playSceneAudio(scene);
}

//==========================
// Sky
//==========================

void drawSky()
{
    glBegin(GL_QUADS);

    glColor3ub(135,206,235);

    glVertex2f(-1,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(-1,1);

    glEnd();
}

void drawDarkSky()
{
    glBegin(GL_QUADS);

    glColor3ub(60,60,60);

    glVertex2f(-1,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(-1,1);

    glEnd();
}

// Blended sky used while the flood is receding (t: 0 = dark storm sky, 1 = bright sunny sky)
void drawSkyBlend(float t)
{
    if(t<0) t=0;
    if(t>1) t=1;

    int r = (int)(60 + (135-60)*t);
    int g = (int)(60 + (206-60)*t);
    int b = (int)(60 + (235-60)*t);

    glBegin(GL_QUADS);

    glColor3ub(r,g,b);

    glVertex2f(-1,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(-1,1);

    glEnd();
}

//==========================
// Hills (distant scenery, sits above the horizon line)
//==========================

void drawHillShape(float cx,float groundY,float rx,float ry,unsigned char r,unsigned char g,unsigned char b)
{
    glColor3ub(r,g,b);

    glBegin(GL_POLYGON);

    for(int i=180;i>=0;i-=4)
    {
        float angle=i*PI/180;
        glVertex2f(cx+rx*cos(angle), groundY+ry*sin(angle));
    }

    glEnd();
}

void drawHills()
{
    // Back range - distant, muted

    drawHillShape(-0.55,0.0,0.55,0.34,95,145,85);
    drawHillShape( 0.60,0.0,0.60,0.32,85,135,75);

    // Front range - closer, greener

    drawHillShape(-0.10,0.0,0.50,0.22,60,150,60);
    drawHillShape( 0.35,0.0,0.45,0.20,70,160,65);
}

//==========================
// Waterfall (flows down the back-right hill)
//==========================

void drawWaterfall()
{
    float x=0.60, topY=0.30, bottomY=0.0;

    // Water body

    glColor3ub(190,235,255);

    glBegin(GL_QUADS);
    glVertex2f(x-0.03,topY);
    glVertex2f(x+0.03,topY);
    glVertex2f(x+0.045,bottomY);
    glVertex2f(x-0.045,bottomY);
    glEnd();

    // Flowing streaks

    glColor3ub(255,255,255);

    glBegin(GL_LINES);

    for(float y=topY;y>bottomY;y-=0.04)
    {
        float off=0.008*sin(wave*2+y*20);

        glVertex2f(x+off,y);
        glVertex2f(x+off,y-0.02);
    }

    glEnd();

    // Splash pool

    glColor3ub(210,240,255);
    circle(x,bottomY,0.05);
}

//==========================
// Grass
//==========================

void drawGrass()
{
    glBegin(GL_QUADS);

    glColor3ub(34,177,76);

    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(1,0);
    glVertex2f(-1,0);

    glEnd();
}

//==========================
// Road
//==========================

void drawRoad()
{
    glBegin(GL_QUADS);

    glColor3ub(80,80,80);

    glVertex2f(-1,-0.40);
    glVertex2f(1,-0.40);
    glVertex2f(1,-0.15);
    glVertex2f(-1,-0.15);

    glEnd();

    // Road Divider

    glColor3ub(255,255,255);

    glBegin(GL_LINES);

    for(float x=-1;x<1;x+=0.20)
    {
        glVertex2f(x,-0.275);
        glVertex2f(x+0.10,-0.275);
    }

    glEnd();
}

void drawRiver()
{
    // Deeper base band

    glBegin(GL_QUADS);

    glColor3ub(20,110,200);

    glVertex2f(-1,-0.75);
    glVertex2f(1,-0.75);
    glVertex2f(1,-0.60);
    glVertex2f(-1,-0.60);

    glEnd();

    // Lighter surface band

    glBegin(GL_QUADS);

    glColor3ub(30,144,255);

    glVertex2f(-1,-0.60);
    glVertex2f(1,-0.60);
    glVertex2f(1,-0.45);
    glVertex2f(-1,-0.45);

    glEnd();

    // Moving Wave Lines

    glColor3ub(255,255,255);

    glBegin(GL_LINES);

    for(float x=-1; x<=1; x+=0.10)
    {
        glVertex2f(x,      -0.55 + 0.015*sin(wave + x*10));
        glVertex2f(x+0.05, -0.55 + 0.015*sin(wave + x*10));
    }

    glEnd();

    // Sparkle dots

    for(float x=-0.9; x<=0.9; x+=0.25)
    {
        float sy = -0.50 + 0.02*sin(wave*1.5 + x*8);
        circle(x,sy,0.008);
    }
}

//==========================
// House 1 (left side of the village)
//==========================

void drawHouse1()
{
    // Body

    glBegin(GL_QUADS);
    glColor3ub(255,220,180);
    glVertex2f(-0.70,-0.05);
    glVertex2f(-0.30,-0.05);
    glVertex2f(-0.30,0.25);
    glVertex2f(-0.70,0.25);
    glEnd();

    // Roof

    glBegin(GL_TRIANGLES);
    glColor3ub(170,0,0);
    glVertex2f(-0.75,0.25);
    glVertex2f(-0.25,0.25);
    glVertex2f(-0.50,0.45);
    glEnd();

    // Chimney

    glBegin(GL_QUADS);
    glColor3ub(120,90,70);
    glVertex2f(-0.42,0.32);
    glVertex2f(-0.37,0.32);
    glVertex2f(-0.37,0.45);
    glVertex2f(-0.42,0.45);
    glEnd();

    // Chimney smoke

    glColor3ub(230,230,230);
    circle(-0.395,0.50,0.020);
    circle(-0.390,0.55,0.025);
    circle(-0.400,0.60,0.030);

    // Door

    glBegin(GL_QUADS);
    glColor3ub(139,69,19);
    glVertex2f(-0.56,-0.05);
    glVertex2f(-0.46,-0.05);
    glVertex2f(-0.46,0.10);
    glVertex2f(-0.56,0.10);
    glEnd();

    // Door knob

    glColor3ub(255,215,0);
    circle(-0.48,0.02,0.007);

    // Window frame

    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(-0.415,0.065);
    glVertex2f(-0.315,0.065);
    glVertex2f(-0.315,0.175);
    glVertex2f(-0.415,0.175);
    glEnd();

    // Window pane

    glBegin(GL_QUADS);

    if(houseLight)
        glColor3ub(255,255,0);
    else
        glColor3ub(0,255,255);

    glVertex2f(-0.40,0.08);
    glVertex2f(-0.33,0.08);
    glVertex2f(-0.33,0.16);
    glVertex2f(-0.40,0.16);
    glEnd();

    // Flower box

    glBegin(GL_QUADS);
    glColor3ub(101,67,33);
    glVertex2f(-0.41,0.045);
    glVertex2f(-0.32,0.045);
    glVertex2f(-0.32,0.065);
    glVertex2f(-0.41,0.065);
    glEnd();

    glColor3ub(255,90,120);
    circle(-0.385,0.068,0.010);
    glColor3ub(255,220,60);
    circle(-0.365,0.070,0.010);
    glColor3ub(255,255,255);
    circle(-0.345,0.068,0.010);
}

//==========================
// House 1 - storm damaged version
//==========================

void drawHouse1Damaged()
{
    // Cracked walls

    glBegin(GL_QUADS);
    glColor3ub(200,180,150);
    glVertex2f(-0.70,-0.05);
    glVertex2f(-0.30,-0.05);
    glVertex2f(-0.30,0.25);
    glVertex2f(-0.70,0.25);
    glEnd();

    // Partial roof (a chunk is missing)

    glBegin(GL_TRIANGLES);
    glColor3ub(120,20,20);
    glVertex2f(-0.75,0.25);
    glVertex2f(-0.48,0.25);
    glVertex2f(-0.55,0.40);
    glEnd();

    // Broken door hole

    glBegin(GL_QUADS);
    glColor3ub(30,20,10);
    glVertex2f(-0.56,-0.05);
    glVertex2f(-0.46,-0.05);
    glVertex2f(-0.46,0.10);
    glVertex2f(-0.56,0.10);
    glEnd();

    // Broken window (cracked X)

    glColor3ub(255,255,255);
    glBegin(GL_LINES);
    glVertex2f(-0.40,0.08); glVertex2f(-0.33,0.16);
    glVertex2f(-0.40,0.16); glVertex2f(-0.33,0.08);
    glEnd();

    // Crack lines on the wall

    glColor3ub(90,70,50);
    glBegin(GL_LINES);
    glVertex2f(-0.65,0.20); glVertex2f(-0.60,0.05);
    glVertex2f(-0.60,0.05); glVertex2f(-0.63,-0.03);
    glEnd();

    // Debris pile

    glColor3ub(120,100,80);
    circle(-0.56,-0.07,0.030);
    circle(-0.48,-0.06,0.025);
    circle(-0.63,-0.06,0.020);
}

//==========================
// House 2 (right side of the village)
//==========================

void drawHouse2()
{
    // Body

    glBegin(GL_QUADS);
    glColor3ub(200,225,255);
    glVertex2f(0.05,-0.05);
    glVertex2f(0.45,-0.05);
    glVertex2f(0.45,0.25);
    glVertex2f(0.05,0.25);
    glEnd();

    // Roof

    glBegin(GL_TRIANGLES);
    glColor3ub(40,70,130);
    glVertex2f(0.00,0.25);
    glVertex2f(0.50,0.25);
    glVertex2f(0.25,0.45);
    glEnd();

    // Chimney

    glBegin(GL_QUADS);
    glColor3ub(150,150,150);
    glVertex2f(0.06,0.32);
    glVertex2f(0.11,0.32);
    glVertex2f(0.11,0.45);
    glVertex2f(0.06,0.45);
    glEnd();

    // Chimney smoke

    glColor3ub(230,230,230);
    circle(0.085,0.50,0.020);
    circle(0.090,0.55,0.025);
    circle(0.080,0.60,0.030);

    // Door

    glBegin(GL_QUADS);
    glColor3ub(160,110,60);
    glVertex2f(0.18,-0.05);
    glVertex2f(0.28,-0.05);
    glVertex2f(0.28,0.10);
    glVertex2f(0.18,0.10);
    glEnd();

    // Door knob

    glColor3ub(255,215,0);
    circle(0.26,0.02,0.007);

    // Window frame

    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(0.335,0.065);
    glVertex2f(0.435,0.065);
    glVertex2f(0.435,0.175);
    glVertex2f(0.335,0.175);
    glEnd();

    // Window pane

    glBegin(GL_QUADS);

    if(houseLight)
        glColor3ub(255,255,0);
    else
        glColor3ub(0,255,255);

    glVertex2f(0.35,0.08);
    glVertex2f(0.42,0.08);
    glVertex2f(0.42,0.16);
    glVertex2f(0.35,0.16);
    glEnd();

    // Flower box

    glBegin(GL_QUADS);
    glColor3ub(101,67,33);
    glVertex2f(0.34,0.045);
    glVertex2f(0.43,0.045);
    glVertex2f(0.43,0.065);
    glVertex2f(0.34,0.065);
    glEnd();

    glColor3ub(255,220,60);
    circle(0.365,0.068,0.010);
    glColor3ub(255,90,120);
    circle(0.385,0.070,0.010);
    glColor3ub(255,255,255);
    circle(0.405,0.068,0.010);
}

//==========================
// House 2 - storm damaged version
//==========================

void drawHouse2Damaged()
{
    // Cracked walls

    glBegin(GL_QUADS);
    glColor3ub(170,190,200);
    glVertex2f(0.05,-0.05);
    glVertex2f(0.45,-0.05);
    glVertex2f(0.45,0.25);
    glVertex2f(0.05,0.25);
    glEnd();



    glBegin(GL_TRIANGLES);
    glColor3ub(25,45,85);
    glVertex2f(0.27,0.25);
    glVertex2f(0.50,0.25);
    glVertex2f(0.35,0.38);
    glEnd();

    // Broken door hole

    glBegin(GL_QUADS);
    glColor3ub(20,25,30);
    glVertex2f(0.18,-0.05);
    glVertex2f(0.28,-0.05);
    glVertex2f(0.28,0.10);
    glVertex2f(0.18,0.10);
    glEnd();

    // Broken window (cracked X)

    glColor3ub(255,255,255);
    glBegin(GL_LINES);
    glVertex2f(0.35,0.08); glVertex2f(0.42,0.16);
    glVertex2f(0.35,0.16); glVertex2f(0.42,0.08);
    glEnd();

    // Crack lines on the wall

    glColor3ub(80,90,95);
    glBegin(GL_LINES);
    glVertex2f(0.10,0.20); glVertex2f(0.15,0.05);
    glVertex2f(0.15,0.05); glVertex2f(0.12,-0.03);
    glEnd();

    // Debris pile

    glColor3ub(130,140,140);
    circle(0.20,-0.07,0.030);
    circle(0.28,-0.06,0.025);
    circle(0.12,-0.06,0.020);
}



float treeSway = 0.0f;
void drawTree(float cx)
{


    glBegin(GL_QUADS);
    glColor3ub(120,60,20);
    glVertex2f(cx-0.035,-0.05);
    glVertex2f(cx+0.035,-0.05);
    glVertex2f(cx+0.035,0.20);
    glVertex2f(cx-0.035,0.20);
    glEnd();

    glColor3ub(150,90,40);
    glBegin(GL_QUADS);
    glVertex2f(cx-0.008,-0.05);
    glVertex2f(cx+0.006,-0.05);
    glVertex2f(cx+0.006,0.20);
    glVertex2f(cx-0.008,0.20);
    glEnd();

    // Leaves - swaying gently in the wind (ROTATION), layered for a fuller canopy

    glPushMatrix();
    glTranslatef(cx,0.20,0);                                   // TRANSLATION - pivot at treetop
    glRotatef(3.0f*sin(treeSway+cx*4.0f),0,0,1);                // ROTATION - wind sway
    glTranslatef(-cx,-0.20,0);

    // Shadow-layer leaves (darker, behind)
    glColor3ub(0,90,0);
    circle(cx-0.01,0.29,0.085);
    circle(cx-0.06,0.24,0.075);
    circle(cx+0.06,0.24,0.075);

    // Mid-tone leaves
    glColor3ub(20,140,20);
    circle(cx,0.31,0.075);
    circle(cx-0.05,0.26,0.065);
    circle(cx+0.05,0.26,0.065);
    circle(cx,0.22,0.055);

    // Highlight leaves (catching the sun, upper-left)
    glColor3ub(90,200,90);
    circle(cx-0.03,0.34,0.035);
    circle(cx+0.01,0.30,0.025);

    // A few little fruit/blossom dots for extra beauty
    glColor3ub(255,120,120);
    circle(cx-0.02,0.27,0.010);
    circle(cx+0.04,0.20,0.010);

    glPopMatrix();
}

void drawPineTree(float cx)
{
    // Trunk

    glBegin(GL_QUADS);
    glColor3ub(101,67,33);
    glVertex2f(cx-0.025,-0.05);
    glVertex2f(cx+0.025,-0.05);
    glVertex2f(cx+0.025,0.05);
    glVertex2f(cx-0.025,0.05);
    glEnd();

    glPushMatrix();
    glTranslatef(cx,0.05,0);                                   // TRANSLATION - pivot at base of foliage
    glRotatef(2.5f*sin(treeSway*1.3f+cx*3.0f),0,0,1);           // ROTATION - wind sway
    glTranslatef(-cx,-0.05,0);

    // Layered foliage, richer tri-tone shading

    glColor3ub(15,90,35);
    glBegin(GL_TRIANGLES);
    glVertex2f(cx-0.09,0.06);
    glVertex2f(cx+0.09,0.06);
    glVertex2f(cx,0.20);
    glEnd();

    glColor3ub(25,115,45);
    glBegin(GL_TRIANGLES);
    glVertex2f(cx-0.075,0.15);
    glVertex2f(cx+0.075,0.15);
    glVertex2f(cx,0.27);
    glEnd();

    glColor3ub(35,140,55);
    glBegin(GL_TRIANGLES);
    glVertex2f(cx-0.06,0.23);
    glVertex2f(cx+0.06,0.23);
    glVertex2f(cx,0.34);
    glEnd();

    // Snow-cap style highlight tip for extra polish
    glColor3ub(120,230,140);
    glBegin(GL_TRIANGLES);
    glVertex2f(cx-0.02,0.31);
    glVertex2f(cx+0.02,0.31);
    glVertex2f(cx,0.35);
    glEnd();

    glPopMatrix();
}

void drawFlowerBush(float cx,float cy)
{
    glColor3ub(40,140,40);
    circle(cx,cy,0.035);

    glColor3ub(255,80,120);
    circle(cx-0.02,cy+0.015,0.008);

    glColor3ub(255,220,60);
    circle(cx+0.02,cy+0.010,0.008);

    glColor3ub(255,255,255);
    circle(cx,cy-0.015,0.008);
}

void drawForest()
{
    drawTree(0.65);
    drawPineTree(0.85);
    drawTree(0.97);

    drawPineTree(-0.85);
    drawTree(-0.97);

    drawFlowerBush(-0.15,-0.03);
}

void drawSun()
{
    // Gentle pulsing glow (SCALING) around a steady sun disc
    glPushMatrix();
    glTranslatef(sunX,0.75,0);              // TRANSLATION - pivot at sun centre
    float glowS = 1.0f+0.08f*sin(wave*0.5f);
    glColor3ub(255,250,200);
    glPushMatrix();
    glScalef(glowS,glowS,1.0f);             // SCALING - breathing glow halo
    circle(0,0,0.10);
    glPopMatrix();

    glColor3ub(255,255,0);
    circle(0,0,0.08);
    glPopMatrix();
}

void drawCloud()
{
    glColor3ub(255,255,255);

    circle(cloudX,0.75,0.05);
    circle(cloudX+0.05,0.78,0.06);
    circle(cloudX+0.10,0.75,0.05);

    circle(cloudX+0.45,0.70,0.05);
    circle(cloudX+0.50,0.73,0.06);
    circle(cloudX+0.55,0.70,0.05);
}

void drawDarkCloud()
{
    glColor3ub(50,50,50);

    circle(cloudX,0.75,0.05);
    circle(cloudX+0.05,0.78,0.06);
    circle(cloudX+0.10,0.75,0.05);

    circle(cloudX+0.45,0.70,0.05);
    circle(cloudX+0.50,0.73,0.06);
    circle(cloudX+0.55,0.70,0.05);
}


void drawPerson()
{
    //Head

    glColor3ub(255,220,177);
    circle(personX,-0.08,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    //Body
    glVertex2f(personX,-0.11);
    glVertex2f(personX,-0.23);

    //Hands
    glVertex2f(personX-0.03,-0.16);
    glVertex2f(personX+0.03,-0.16);

    //Left Leg
    glVertex2f(personX,-0.23);
    glVertex2f(personX-0.02,-0.32);

    //Right Leg
    glVertex2f(personX,-0.23);
    glVertex2f(personX+0.02,-0.32);

    glEnd();
}

void drawPersonAt(float x)
{
    glColor3ub(255,220,177);
    circle(x,-0.08,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    glVertex2f(x,-0.11);
    glVertex2f(x,-0.23);

    glVertex2f(x-0.03,-0.16);
    glVertex2f(x+0.03,-0.16);

    glVertex2f(x,-0.23);
    glVertex2f(x-0.02,-0.32);

    glVertex2f(x,-0.23);
    glVertex2f(x+0.02,-0.32);

    glEnd();
}



void drawSeatedVillager(float x,float y)
{
    // Head

    glColor3ub(255,220,177);
    circle(x,y+0.055,0.020);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    // Torso
    glVertex2f(x,y+0.035);
    glVertex2f(x,y+0.005);

    // Bent thigh (sitting on the bench)
    glVertex2f(x,y+0.005);
    glVertex2f(x+0.045,y+0.005);

    // Shin down to the deck
    glVertex2f(x+0.045,y+0.005);
    glVertex2f(x+0.045,y-0.030);

    // Resting arm
    glVertex2f(x,y+0.025);
    glVertex2f(x+0.03,y+0.010);

    glEnd();
}

void drawSafeWaitingVillager(float x,float y)
{
    glColor3ub(255,220,177);
    circle(x,y+0.03,0.022);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    // Torso
    glVertex2f(x,y+0.01);
    glVertex2f(x,y-0.07);


    glVertex2f(x,y-0.01);
    glVertex2f(x+0.05,y+0.07);

    // Other arm resting
    glVertex2f(x,y-0.01);
    glVertex2f(x-0.04,y-0.03);


    glVertex2f(x,y-0.07);
    glVertex2f(x-0.03,y-0.10);

    glVertex2f(x,y-0.07);
    glVertex2f(x+0.03,y-0.10);

    glEnd();
}

void drawRain()
{
    glColor3ub(180,220,255);

    glBegin(GL_LINES);

    for(float x=-1; x<=1; x+=0.04)
    {
        for(float y=0; y<=1; y+=0.06)
        {
            float streak = 0.03*sin(x*50);

            glVertex2f(x+streak, y-rainY);
            glVertex2f(x+streak-0.02, y-0.05-rainY);
        }
    }

    glEnd();
}

void drawLightning()
{
    if(lightning)
    {
        glColor3ub(255,255,0);

        glLineWidth(3);

        glBegin(GL_LINES);

        glVertex2f(0.20,1.00);
        glVertex2f(0.10,0.80);

        glVertex2f(0.10,0.80);
        glVertex2f(0.25,0.60);

        glVertex2f(0.25,0.60);
        glVertex2f(0.15,0.35);

        glEnd();

        glLineWidth(1);
    }
}

void drawFloodRiver()
{
    glBegin(GL_QUADS);

    glColor3ub(20,90,200);

    glVertex2f(-1,-0.75);
    glVertex2f(1,-0.75);
    glVertex2f(1,-0.45);
    glVertex2f(-1,-0.45);

    glEnd();

    glColor3ub(255,255,255);

    glBegin(GL_LINES);

    for(float x=-1;x<=1;x+=0.08)
    {
        glVertex2f(x,-0.60+0.02*sin(wave+x*15));
        glVertex2f(x+0.05,-0.60+0.02*sin(wave+x*15));
    }

    glEnd();
}

void drawRunningPerson()
{
    glColor3ub(255,220,177);
    circle(personX,-0.08,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    // Body
    glVertex2f(personX,-0.11);
    glVertex2f(personX,-0.23);

    // Hands
    glVertex2f(personX-0.04,-0.17);
    glVertex2f(personX+0.04,-0.13);

    // Left Leg
    glVertex2f(personX,-0.23);
    glVertex2f(personX-0.04,-0.32);

    // Right Leg
    glVertex2f(personX,-0.23);
    glVertex2f(personX+0.04,-0.28);

    glEnd();
}

void drawRunningPersonAt(float x)
{
    glColor3ub(255,220,177);
    circle(x,-0.08,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    glVertex2f(x,-0.11);
    glVertex2f(x,-0.23);

    glVertex2f(x-0.04,-0.17);
    glVertex2f(x+0.04,-0.13);

    glVertex2f(x,-0.23);
    glVertex2f(x-0.04,-0.32);

    glVertex2f(x,-0.23);
    glVertex2f(x+0.04,-0.28);

    glEnd();
}


void drawScene4Villager()
{
    if(villagerInside)
        return;

    float x;
    float y;

    if(villagerAttached)
    {
        // Follow the rope
        x = helicopterX + 0.18;
        y = ropeY;
    }
    else
    {

        x = villagerX;
        y = villagerY;
    }

    // Head
    glColor3ub(255,220,177);
    circle(x,y,0.025);

    // Body
    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    glVertex2f(x,y-0.03);
    glVertex2f(x,y-0.15);

    // Hands
    glVertex2f(x-0.04,y-0.07);
    glVertex2f(x+0.04,y-0.07);

    // Legs
    glVertex2f(x,y-0.15);
    glVertex2f(x-0.03,y-0.23);

    glVertex2f(x,y-0.15);
    glVertex2f(x+0.03,y-0.23);

    glEnd();
}


void drawRescueBoat(float bx)
{
    float waterY = floodLevel;

    // Hull (smooth curved silhouette)

    glColor3ub(139,69,19);

    glBegin(GL_POLYGON);
    glVertex2f(bx-0.02,waterY);
    glVertex2f(bx+0.32,waterY);
    glVertex2f(bx+0.34,waterY-0.05);
    glVertex2f(bx+0.15,waterY-0.15);
    glVertex2f(bx-0.04,waterY-0.05);
    glEnd();

    // Hull trim

    glColor3ub(190,120,40);

    glBegin(GL_QUADS);
    glVertex2f(bx-0.02,waterY);
    glVertex2f(bx+0.32,waterY);
    glVertex2f(bx+0.32,waterY+0.015);
    glVertex2f(bx-0.02,waterY+0.015);
    glEnd();

    // Deck

    glColor3ub(255,255,255);

    glBegin(GL_QUADS);
    glVertex2f(bx+0.06,waterY+0.015);
    glVertex2f(bx+0.24,waterY+0.015);
    glVertex2f(bx+0.24,waterY+0.075);
    glVertex2f(bx+0.06,waterY+0.075);
    glEnd();

    // Cabin roof

    glColor3ub(200,30,30);

    glBegin(GL_TRIANGLES);
    glVertex2f(bx+0.04,waterY+0.075);
    glVertex2f(bx+0.26,waterY+0.075);
    glVertex2f(bx+0.15,waterY+0.11);
    glEnd();

    // Porthole

    glColor3ub(120,220,255);
    circle(bx+0.15,waterY+0.045,0.015);

    // Life-ring

    glColor3ub(255,255,255);
    circle(bx+0.315,waterY+0.03,0.020);
    glColor3ub(200,30,30);
    circle(bx+0.315,waterY+0.03,0.012);

    // Mast + flag

    glColor3ub(120,60,10);

    glBegin(GL_LINES);
    glVertex2f(bx+0.15,waterY+0.11);
    glVertex2f(bx+0.15,waterY+0.19);
    glEnd();

    glColor3ub(255,0,0);

    glBegin(GL_TRIANGLES);
    glVertex2f(bx+0.15,waterY+0.19);
    glVertex2f(bx+0.15,waterY+0.15);
    glVertex2f(bx+0.22,waterY+0.17);
    glEnd();


    glPushMatrix();
    glTranslatef(bx+0.15,waterY+0.095,0);
    glRotatef(beaconAngle,0,0,1);
    glColor3ub(255,60,60);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,0);
    glVertex2f(0.12,0.02);
    glVertex2f(0.12,-0.02);
    glEnd();
    glPopMatrix();

    // Wake ripples

    glColor3ub(255,255,255);

    glBegin(GL_LINES);
    glVertex2f(bx-0.05,waterY-0.02);
    glVertex2f(bx-0.15,waterY-0.03);

    glVertex2f(bx-0.05,waterY-0.05);
    glVertex2f(bx-0.15,waterY-0.06);
    glEnd();
}

void drawScene5Villager()
{
    if(villager2Rescued)
        return;

    if(villager2Attached)
    {
        drawSeatedVillager(boat2X+0.03, floodLevel+0.015);
        return;
    }

    drawSafeWaitingVillager(villager2X,villager2Y);
}

void drawScene5Villager3()
{
    if(villager3Rescued)
        return;

    if(villager3Attached)
    {
        drawSeatedVillager(boat2X+0.27, floodLevel+0.015);
        return;
    }

    drawSafeWaitingVillager(villager3X,villager3Y);
}

void drawRisingFlood()
{
    glBegin(GL_QUADS);

    glColor3ub(0,100,220);

    glVertex2f(-1,-1);
    glVertex2f(1,-1);

    glVertex2f(1,floodLevel);
    glVertex2f(-1,floodLevel);

    glEnd();

    // Surface ripple for realism

    glColor3ub(180,220,255);

    glBegin(GL_LINES);

    for(float x=-1;x<=1;x+=0.10)
    {
        glVertex2f(x,      floodLevel+0.01*sin(wave+x*12));
        glVertex2f(x+0.05, floodLevel+0.01*sin(wave+x*12));
    }

    glEnd();
}


void drawFloatingDebris(float x)
{
    float y = floodLevel + 0.015f*sin(buoyBob + x*10.0f);

    glPushMatrix();
    glTranslatef(x,y,0);                         // TRANSLATION - drifting & bobbing on the flood
    float s = 0.85f+0.15f*sin(buoyBob*2.0f+x*5.0f);
    glScalef(s,s,1.0f);                          // SCALING - bobbing squash/stretch

    glColor3ub(120,80,40);
    glBegin(GL_QUADS);
    glVertex2f(-0.035,-0.006);
    glVertex2f(0.035,-0.006);
    glVertex2f(0.035,0.012);
    glVertex2f(-0.035,0.012);
    glEnd();

    glColor3ub(90,60,30);
    glBegin(GL_LINES);
    glVertex2f(-0.02,0.003);
    glVertex2f(0.02,0.003);
    glEnd();

    glPopMatrix();
}


void drawHelicopter()
{
    glPushMatrix();

    // Hovering
    glTranslatef(0, helicopterY, 0);

    //========================
    // Body
    //========================
    glColor3ub(70,70,70);

    glBegin(GL_POLYGON);
    glVertex2f(helicopterX+0.02,0.62);
    glVertex2f(helicopterX+0.08,0.57);
    glVertex2f(helicopterX+0.28,0.57);
    glVertex2f(helicopterX+0.38,0.63);
    glVertex2f(helicopterX+0.35,0.72);
    glVertex2f(helicopterX+0.10,0.74);
    glVertex2f(helicopterX+0.02,0.68);
    glEnd();

    // Belly shade (depth)
    glColor3ub(45,45,45);

    glBegin(GL_POLYGON);
    glVertex2f(helicopterX+0.08,0.57);
    glVertex2f(helicopterX+0.28,0.57);
    glVertex2f(helicopterX+0.24,0.605);
    glVertex2f(helicopterX+0.12,0.605);
    glEnd();

    // Cockpit
    glColor3ub(120,220,255);

    glBegin(GL_POLYGON);
    glVertex2f(helicopterX+0.03,0.64);
    glVertex2f(helicopterX+0.12,0.61);
    glVertex2f(helicopterX+0.12,0.70);
    glVertex2f(helicopterX+0.05,0.69);
    glEnd();

    // Side Window
    glBegin(GL_QUADS);
    glVertex2f(helicopterX+0.15,0.63);
    glVertex2f(helicopterX+0.27,0.63);
    glVertex2f(helicopterX+0.27,0.70);
    glVertex2f(helicopterX+0.15,0.70);
    glEnd();

    // Nose light
    glColor3ub(255,230,120);
    circle(helicopterX+0.03,0.655,0.012);

    // Tail Boom (thicker, more realistic)
    glColor3ub(80,80,80);

    glBegin(GL_QUADS);
    glVertex2f(helicopterX+0.28,0.655);
    glVertex2f(helicopterX+0.62,0.675);
    glVertex2f(helicopterX+0.62,0.705);
    glVertex2f(helicopterX+0.28,0.685);
    glEnd();

    // Tail Fin
    glBegin(GL_TRIANGLES);
    glVertex2f(helicopterX+0.62,0.665);
    glVertex2f(helicopterX+0.62,0.715);
    glVertex2f(helicopterX+0.70,0.69);
    glEnd();

    // Landing Skids
    glColor3ub(20,20,20);

    glLineWidth(3);

    glBegin(GL_LINES);
    glVertex2f(helicopterX+0.08,0.57);
    glVertex2f(helicopterX+0.30,0.57);

    glVertex2f(helicopterX+0.10,0.54);
    glVertex2f(helicopterX+0.32,0.54);
    glEnd();

    glLineWidth(1);

    // Skid Struts
    glBegin(GL_LINES);
    glVertex2f(helicopterX+0.10,0.57);
    glVertex2f(helicopterX+0.10,0.545);

    glVertex2f(helicopterX+0.26,0.57);
    glVertex2f(helicopterX+0.26,0.545);
    glEnd();

    // Main Rotor
    glPushMatrix();

    glTranslatef(helicopterX+0.18,0.82,0);
    glRotatef(rotorAngle,0,0,1);

    glLineWidth(3);

    glBegin(GL_LINES);
    glVertex2f(-0.35,0);
    glVertex2f(0.35,0);
    glVertex2f(0,-0.35);
    glVertex2f(0,0.35);
    glEnd();

    glLineWidth(1);

    glPopMatrix();

    // Tail Rotor
    glPushMatrix();

    glTranslatef(helicopterX+0.70,0.69,0);
    glRotatef(rotorAngle*2,0,0,1);

    glBegin(GL_LINES);
    glVertex2f(-0.05,0);
    glVertex2f(0.05,0);
    glVertex2f(0,-0.05);
    glVertex2f(0,0.05);
    glEnd();

    glPopMatrix();

    // Rescue Rope
    if(rescue)
    {
        glColor3ub(255,255,255);

        glBegin(GL_LINES);
        glVertex2f(helicopterX+0.18,0.57);
        glVertex2f(helicopterX+0.18,ropeY);
        glEnd();
    }

    glPopMatrix();
}

//==========================
// Rainbow (double rainbow: vivid primary + pale secondary)
//==========================

void drawRainbowArc(float cx,float cy,float radiusScale,bool faint)
{
    float radii[7] = {0.85f,0.79f,0.73f,0.67f,0.61f,0.55f,0.49f};

    unsigned char colors[7][3] =
    {
        {255,0,0},
        {255,127,0},
        {255,255,0},
        {0,200,0},
        {0,100,255},
        {75,0,130},
        {148,0,211}
    };

    glLineWidth(2);

    for(int i=0;i<7;i++)
    {
        unsigned char r = colors[i][0];
        unsigned char g = colors[i][1];
        unsigned char b = colors[i][2];

        if(faint)
        {
            r = (unsigned char)((r+255*2)/3);
            g = (unsigned char)((g+255*2)/3);
            b = (unsigned char)((b+255*2)/3);
        }

        glColor3ub(r,g,b);

        glBegin(GL_LINE_STRIP);

        for(int a=0;a<=180;a+=2)
        {
            float angle=a*PI/180;
            glVertex2f(cx+radii[i]*radiusScale*cos(angle), cy+radii[i]*radiusScale*sin(angle));
        }

        glEnd();
    }

    glLineWidth(1);
}

void drawRainbow()
{
    drawRainbowArc(0.0f,-0.15f,1.18f,true);   // secondary, pale, larger
    drawRainbowArc(0.0f,-0.15f,1.0f,false);   // primary, vivid
}

//==========================
// Scene 8 Rebuild Villagers
//==========================

void drawRebuildVillagers()
{
    // Villager A - hammering House 1's roof

    float x1=-0.62, y1=-0.10;

    glColor3ub(255,220,177);
    circle(x1,y1+0.05,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    glVertex2f(x1,y1+0.02);
    glVertex2f(x1,y1-0.10);

    glVertex2f(x1,y1-0.10);
    glVertex2f(x1-0.03,y1-0.20);

    glVertex2f(x1,y1-0.10);
    glVertex2f(x1+0.03,y1-0.20);

    glEnd();

    glPushMatrix();

    glTranslatef(x1+0.02,y1-0.02,0);
    glRotatef(hammerAngle,0,0,1);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0.10,0.02);
    glEnd();

    glColor3ub(139,69,19);

    glBegin(GL_LINES);
    glVertex2f(0.09,0.00);
    glVertex2f(0.09,0.04);
    glEnd();

    glPopMatrix();

    // Villager B - holding a plank near House 1

    float x2=-0.32, y2=-0.10;

    glColor3ub(255,220,177);
    circle(x2,y2+0.05,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    glVertex2f(x2,y2+0.02);
    glVertex2f(x2,y2-0.10);

    glVertex2f(x2,y2-0.10);
    glVertex2f(x2-0.03,y2-0.20);

    glVertex2f(x2,y2-0.10);
    glVertex2f(x2+0.03,y2-0.20);

    glEnd();

    glColor3ub(139,69,19);

    glBegin(GL_LINES);
    glVertex2f(x2-0.08,y2-0.02);
    glVertex2f(x2+0.08,y2-0.02);
    glEnd();

    // Villager C - hammering House 2's roof

    float x3=0.15, y3=-0.10;

    glColor3ub(255,220,177);
    circle(x3,y3+0.05,0.025);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);

    glVertex2f(x3,y3+0.02);
    glVertex2f(x3,y3-0.10);

    glVertex2f(x3,y3-0.10);
    glVertex2f(x3-0.03,y3-0.20);

    glVertex2f(x3,y3-0.10);
    glVertex2f(x3+0.03,y3-0.20);

    glEnd();

    glPushMatrix();

    glTranslatef(x3+0.02,y3-0.02,0);
    glRotatef(-hammerAngle,0,0,1);

    glColor3ub(0,0,0);

    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0.10,0.02);
    glEnd();

    glColor3ub(139,69,19);

    glBegin(GL_LINES);
    glVertex2f(0.09,0.00);
    glVertex2f(0.09,0.04);
    glEnd();

    glPopMatrix();
}

//==========================
// Shared decorative "transformation demo" objects, reused across scenes so
// EVERY scene visibly contains translation + scaling + rotation.
//==========================

// Windmill: ROTATION (spinning sails) + TRANSLATION (pivot moved to the hub)
void drawWindmill(float cx,float baseY)
{
    glColor3ub(190,190,190);
    glBegin(GL_QUADS);
    glVertex2f(cx-0.018,baseY);
    glVertex2f(cx+0.018,baseY);
    glVertex2f(cx+0.012,baseY+0.26);
    glVertex2f(cx-0.012,baseY+0.26);
    glEnd();

    glPushMatrix();
    glTranslatef(cx,baseY+0.26,0);       // TRANSLATION - move pivot to the hub
    glRotatef(windmillAngle,0,0,1);       // ROTATION - spinning sails

    glColor3ub(240,240,240);
    for(int i=0;i<4;i++)
    {
        glPushMatrix();
        glRotatef(i*90.0f,0,0,1);
        glBegin(GL_TRIANGLES);
        glVertex2f(0,0);
        glVertex2f(0.018,0.11);
        glVertex2f(-0.018,0.11);
        glEnd();
        glPopMatrix();
    }

    glColor3ub(90,90,90);
    circle(0,0,0.012);
    glPopMatrix();
}

// A small bird gliding by: pure TRANSLATION
void drawBird(float x,float y)
{
    glPushMatrix();
    glTranslatef(x,y,0);                 // TRANSLATION - flight path
    glColor3ub(40,40,40);
    glBegin(GL_LINES);
    glVertex2f(-0.02,0); glVertex2f(0,0.014);
    glVertex2f(0,0.014); glVertex2f(0.02,0);
    glEnd();
    glPopMatrix();
}


void drawPulsingFlower(float cx,float cy)
{
    glPushMatrix();
    glTranslatef(cx,cy,0);                       // TRANSLATION
    float s=1.0f+0.18f*sin(flowerPulse+cx*6.0f);
    glScalef(s,s,1.0f);                          // SCALING - breathing bloom
    glColor3ub(255,105,180);
    circle(0,0,0.018);
    glColor3ub(255,240,80);
    circle(0,0,0.007);
    glPopMatrix();
}


void drawStreetLamp(float x,float baseY)
{
    glColor3ub(50,50,50);
    glBegin(GL_LINES);
    glVertex2f(x,baseY);
    glVertex2f(x,baseY+0.22);
    glEnd();

    glPushMatrix();
    glTranslatef(x,baseY+0.22,0);        // TRANSLATION - pivot at lamp arm
    glRotatef(lampSwing,0,0,1);          // ROTATION - swinging in the storm wind
    glColor3ub(255,225,120);
    circle(0.02,0,0.018);
    glColor3ub(60,60,60);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0.02,0);
    glEnd();
    glPopMatrix();
}

void resetAll()
{
    sunX = 0.75;
    cloudX = -1.0;
    personX = -1.0;
    wave = 0.0;

    rainY = 0.0;
    lightning = false;
    flashCount = 0;

    helicopterX = -1.2;
    floodLevel = -0.75;
    houseLight = false;
    ropeY = 0.55;
    rescue = false;
    rotorAngle = 0;
    helicopterY = 0;
    searchLight = 0;
    lightDirection = true;

    rescueStage = 0;
    villagerAttached = false;
    villagerInside = false;

    boatX = -1.2f;
    boatStart = false;

    boat2X = -1.2f;
    boatRescueStage = 0;
    villager2Attached = false;
    villager2Rescued = false;
    villager3Attached = false;
    villager3Rescued = false;

    boat3X = -1.3f;

    skyT = 0.0f;

    hammerAngle = 0.0f;
    hammerUp = true;
    housesRepaired = false;

    bellAngle = 0.0f;
    bellSwingRight = true;
    saplingScale = 0.2f;
    saplingGrowing = true;
    flagRiseY = 0.0f;
    flagWave = 0.0f;

    sirenAngle = 0.0f;
    warnScale = 1.0f;
    warnGrow = true;
    patrolBoatX = -1.2f;
    bannerFloat = 0.0f;

    windmillAngle = 0.0f;
    birdX = -1.2f;
    birdX2 = -0.4f;
    flowerPulse = 0.0f;
    lampSwing = 0.0f;
    lampSwingRight = true;
    debrisX1 = -1.2f;
    debrisX2 = 1.2f;
    buoyBob = 0.0f;
    beaconAngle = 0.0f;
}

//==========================
// Keyboard: scenes are now advanced/rewound by the USER instead of a timer.
// 'n' / 'N'  -> next scene   (each of the 10 scenes is one group member's part)
// 'p' / 'P'  -> previous scene
// 'r' / 'R'  -> restart the whole story from Scene 1
// ESC        -> quit
//==========================

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'n':
    case 'N':

        if(scene < totalScenes)
        {

            changeScene(scene + 1);


            if(scene==4)
            {
                helicopterX=-1.2f;
                helicopterY=0;
                ropeY=0.55f;
                villagerAttached=false;
                villagerInside=false;
                boatX=-1.2f;
                boatStart=false;
                rescue=false;
                rescueStage=0;
            }

            if(scene==5)
            {
                boat2X=-1.2f;
                boatRescueStage=0;
                villager2Attached=false;
                villager2Rescued=false;
                villager3Attached=false;
                villager3Rescued=false;
            }
        }

        break;

    case 'p':
    case 'P':

        if(scene > 1)
        {
            // Move to previous scene and change its audio
            changeScene(scene - 1);
        }

        break;

    case 'r':
    case 'R':

        resetAll();
        changeScene(1);

        break;

    case 27: // ESC

        stopAudio();
        exit(0);
    }

    glutPostRedisplay();
}



void update(int value)
{
    //========================
    // Ambient motion (sun / cloud / villager / water shimmer / bg boat)
    //========================

    sunX -= 0.0003;

    if(sunX < -1.1)
        sunX = 1.1;

    cloudX += 0.0008;

    if(cloudX > 1.2)
        cloudX=-1.2;

    personX += 0.0015;

    if(personX > 1.2)
        personX=-1.2;

    wave +=0.08;

    boat3X += 0.006;

    if(boat3X > 1.3)
        boat3X = -1.3;

    // Shared decorative transform demo objects

    treeSway += 0.03f;
    windmillAngle += 2.5f;
    if(windmillAngle>=360) windmillAngle=0;

    birdX += 0.006f;
    if(birdX>1.2f) birdX=-1.2f;

    birdX2 += 0.004f;
    if(birdX2>1.3f) birdX2=-1.3f;

    flowerPulse += 0.06f;

    if(lampSwingRight) lampSwing += 0.6f; else lampSwing -= 0.6f;
    if(lampSwing>8.0f) lampSwingRight=false;
    if(lampSwing<-8.0f) lampSwingRight=true;

    buoyBob += 0.06f;
    beaconAngle += 4.0f;
    if(beaconAngle>=360) beaconAngle=0;

    sceneTimer++;

    //========================
    // Scene 2 Animation (storm)
    //========================

    if(scene==2)
    {
        rainY +=0.02;

        if(rainY>1)
            rainY=0;

        cloudX +=0.004;

        personX +=0.01;

        flashCount++;

        if(flashCount%80==0)
            lightning=true;
        else
            lightning=false;

        debrisX1 += 0.01f;
        if(debrisX1>1.2f) debrisX1=-1.2f;

        debrisX2 -= 0.008f;
        if(debrisX2<-1.2f) debrisX2=1.2f;
    }


    if(scene==3)
    {
        // Helicopter movement (patrol / search)

        helicopterX +=0.005;

        if(helicopterX>1.2)
        {
            helicopterX=-1.2;
        }

        // Helicopter hovering

        helicopterY = 0.02*sin(wave);

        // Rotor spinning

        rotorAngle +=20;

        if(rotorAngle>=360)
            rotorAngle=0;

        // Search light sweep

        if(lightDirection)
            searchLight +=0.01;
        else
            searchLight -=0.01;

        if(searchLight>0.15)
            lightDirection=false;

        if(searchLight<-0.15)
            lightDirection=true;

        // Flood keeps rising (higher than before) - this is what submerges the road

        floodLevel +=0.0014;

        if(floodLevel>FLOOD_MAX)
            floodLevel=FLOOD_MAX;

        houseLight=true;
    }


    if(scene==4)
    {
        rotorAngle +=20;

        if(rotorAngle>=360)
            rotorAngle=0;

        switch(rescueStage)
        {
        case 0:

            helicopterX +=0.004;

            if(helicopterX>=-0.68)
            {
                helicopterX=-0.68;
                rescue=true;
                rescueStage=1;
            }

            break;

        case 1:

            ropeY-=0.003;

            if(ropeY<=villagerY)
            {
                ropeY=villagerY;
                villagerAttached=true;
                rescueStage=2;
            }

            break;

        case 2:

            ropeY+=0.003;

            if(ropeY>=0.55)
            {
                villagerInside=true;
                rescueStage=3;
            }

            break;

        case 3:

            helicopterX+=0.006;

            if(helicopterX>1.2)
            {
                helicopterX=1.2f;
                boatStart=true;
                rescue=false;
                rescueStage=4;
            }

            break;

        case 4:

            if(boatX<1.2f)
                boatX+=0.004;
            else
                boatX=1.2f;

            break;
        }
    }



    if(scene==5)
    {
        switch(boatRescueStage)
        {
        case 0:

            boat2X += 0.005;

            if(boat2X >= villager2X-0.15)
            {
                boat2X = villager2X-0.15;
                villager2Attached = true;
                villager3Attached = true;
                boatRescueStage = 1;
            }

            break;

        case 1:

            if(boat2X < 1.2f)
                boat2X += 0.005;
            else
            {
                boat2X = 1.2f;
                villager2Rescued = true;
                villager3Rescued = true;
            }

            break;
        }
    }



    if(scene==6)
    {
        if(skyT<1)
            skyT += 0.0021;
        else
            skyT=1;

        if(floodLevel>-1.0)
            floodLevel -= 0.0021;
        else
            floodLevel=-1.0;

        houseLight=false;
    }



    if(scene==8)
    {
        if(hammerUp)
            hammerAngle += 3;
        else
            hammerAngle -= 3;

        if(hammerAngle>30)
            hammerUp=false;

        if(hammerAngle<-10)
            hammerUp=true;

        if(sceneTimer==250)
        {
            housesRepaired = true;
        }
    }


    if(scene==9)
    {
        if(bellSwingRight) bellAngle += 2.0f; else bellAngle -= 2.0f;
        if(bellAngle>20) bellSwingRight=false;
        if(bellAngle<-20) bellSwingRight=true;

        if(saplingGrowing)
        {
            saplingScale += 0.0015f;
            if(saplingScale>=1.0f){ saplingScale=1.0f; saplingGrowing=false; }
        }

        if(flagRiseY<1.0f)
            flagRiseY += 0.0035f;
        else
            flagRiseY=1.0f;

        flagWave += 0.15f;
    }



    if(scene==10)
    {
        sirenAngle += 3.0f;
        if(sirenAngle>=360) sirenAngle=0;

        if(warnGrow) warnScale += 0.004f; else warnScale -= 0.004f;
        if(warnScale>1.15f) warnGrow=false;
        if(warnScale<0.9f) warnGrow=true;

        patrolBoatX += 0.003f;
        if(patrolBoatX>1.2f) patrolBoatX=-1.2f;

        bannerFloat += 0.04f;
    }

    glutPostRedisplay();

    glutTimerFunc(16,update,0);
}

//==========================
// Scenes
//==========================

void scene1()
{
    drawSky();
    drawHills();
    drawWaterfall();
    drawGrass();
    drawSun();
    drawCloud();
    drawRiver();
    drawRoad();
    drawHouse1();
    drawHouse2();
    drawForest();
    drawPerson();
    drawPersonAt(0.15);
    drawPersonAt(-0.85);
    drawPersonAt(0.85);


    drawWindmill(0.92,0.0);
    drawBird(birdX,0.55);
    drawBird(birdX2,0.62);
    drawPulsingFlower(-0.55,-0.02);
    drawPulsingFlower(0.55,-0.03);
}

void scene2()
{
    drawDarkSky();
    drawHills();
    drawGrass();
    drawDarkCloud();
    drawLightning();
    drawRain();
    drawFloodRiver();
    drawRoad();
    drawHouse1();
    drawHouse2();
    drawTree(0.85);
    drawTree(-0.85);
    drawRunningPerson();
    drawRunningPersonAt(0.55);
    drawRunningPersonAt(-0.60);

    drawStreetLamp(-0.10,-0.05);
    drawBird(debrisX1,0.30);
    drawBird(debrisX2,0.20);
    drawPulsingFlower(0.75,-0.02);
}

void scene3()
{
    drawDarkSky();
    drawHills();
    drawWaterfall();
    drawGrass();

    drawRoad();
    drawRisingFlood();

    drawHouse1();
    drawHouse2();
    drawTree(0.85);
    drawTree(-0.85);
    drawHelicopter();
    drawRescueBoat(boat3X);


    drawFloatingDebris(-0.4f);
    drawFloatingDebris(0.3f);
    drawFloatingDebris(0.75f);
    drawWindmill(0.92,0.0);
}

void scene4()
{
    drawDarkSky();
    drawHills();
    drawWaterfall();
    drawGrass();


    drawRoad();
    drawRisingFlood();

    drawHouse1();
    drawHouse2();
    drawTree(0.85);
    drawTree(-0.85);
    drawHelicopter();


    drawScene4Villager();

    drawRescueBoat(boat3X);

    if(boatStart)
    {
        drawRescueBoat(boatX);
    }

    drawFloatingDebris(0.0f);
    drawFloatingDebris(-0.7f);
}

void scene5()
{
    drawDarkSky();
    drawHills();
    drawWaterfall();
    drawGrass();

    // Road hidden beneath the flood, same fix as Scene 3/4
    drawRoad();
    drawRisingFlood();

    drawHouse1();
    drawHouse2();
    drawTree(0.85);
    drawTree(-0.85);
    drawRescueBoat(boat3X);
    drawRescueBoat(boat2X);


    drawScene5Villager();
    drawScene5Villager3();

    drawFloatingDebris(0.9f);
}

void scene6()
{
    drawSkyBlend(skyT);
    drawHills();
    drawWaterfall();
    drawGrass();
    drawRoad();
    drawRisingFlood();
    drawHouse1Damaged();
    drawHouse2Damaged();
    drawForest();
    drawRescueBoat(boat3X);

    drawFloatingDebris(-0.2f);
    drawBird(birdX,0.55);
}

void scene7()
{
    drawSky();
    drawRainbow();
    drawHills();
    drawWaterfall();
    drawGrass();
    drawRiver();
    drawRoad();
    drawHouse1Damaged();
    drawHouse2Damaged();
    drawForest();
    drawSun();
    drawPerson();
    drawPersonAt(0.20);

    drawWindmill(0.92,0.0);
    drawBird(birdX,0.55);
    drawPulsingFlower(-0.10,-0.02);
}

void scene8()
{
    drawSky();
    drawHills();
    drawWaterfall();
    drawGrass();
    drawRiver();
    drawRoad();

    if(housesRepaired)
    {
        drawHouse1();
        drawHouse2();
    }
    else
    {
        drawHouse1Damaged();
        drawHouse2Damaged();
    }

    drawForest();
    drawSun();
    drawRebuildVillagers();
    drawPersonAt(0.60);
    drawPersonAt(-0.90);

    drawWindmill(0.92,0.0);
    drawBird(birdX2,0.60);
    drawPulsingFlower(0.75,-0.02);
}


void drawMemorialBell(float x,float y)
{
    glColor3ub(120,90,60);
    glBegin(GL_QUADS);
    glVertex2f(x-0.015,y);
    glVertex2f(x+0.015,y);
    glVertex2f(x+0.015,y+0.22);
    glVertex2f(x-0.015,y+0.22);
    glEnd();

    glColor3ub(100,70,40);
    glBegin(GL_TRIANGLES);
    glVertex2f(x-0.08,y+0.20);
    glVertex2f(x+0.08,y+0.20);
    glVertex2f(x,y+0.30);
    glEnd();


    glPushMatrix();
    glTranslatef(x,y+0.20,0);
    glRotatef(bellAngle,0,0,1);
    glColor3ub(200,170,60);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03,0);
    glVertex2f(0.03,0);
    glVertex2f(0,-0.07);
    glEnd();
    glPopMatrix();
}

void drawMemorialSapling(float x,float y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    glScalef(saplingScale,saplingScale,1.0f);
    glColor3ub(120,70,30);
    glBegin(GL_QUADS);
    glVertex2f(-0.015,0);
    glVertex2f(0.015,0);
    glVertex2f(0.015,0.12);
    glVertex2f(-0.015,0.12);
    glEnd();
    glColor3ub(40,170,60);
    circle(0,0.17,0.06);
    circle(-0.04,0.13,0.045);
    circle(0.04,0.13,0.045);
    glPopMatrix();
}

void drawRisingFlag(float x,float y)
{
    float poleTop = y+0.32f;

    glColor3ub(90,90,90);
    glBegin(GL_QUADS);
    glVertex2f(x-0.008,y);
    glVertex2f(x+0.008,y);
    glVertex2f(x+0.008,poleTop);
    glVertex2f(x-0.008,poleTop);
    glEnd();


    glColor3ub(200,170,60);
    circle(x,poleTop,0.012f);

    float hoistY = y + 0.04f + flagRiseY*(0.32f-0.04f-0.10f);   // stays between pole base and just below the top
    hoistY += 0.09f;
    glPushMatrix();
    glTranslatef(x,hoistY,0);
    float w = 1.0f+0.15f*sin(flagWave);
    glScalef(w,1.0f,1.0f);               // SCALING - cloth bulging as if waving
    glColor3ub(220,30,40);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,-0.07);
    glVertex2f(0.12,-0.04);
    glVertex2f(0,-0.01);
    glEnd();

    // Hoist edge - the vertical strip that binds the flag to the pole
    glColor3ub(150,20,30);
    glBegin(GL_QUADS);
    glVertex2f(-0.004,-0.07);
    glVertex2f(0.004,-0.07);
    glVertex2f(0.004,-0.01);
    glVertex2f(-0.004,-0.01);
    glEnd();
    glPopMatrix();
}

void scene9()
{
    drawSky();
    drawHills();
    drawWaterfall();
    drawGrass();
    drawRiver();
    drawRoad();
    drawHouse1();
    drawHouse2();
    drawForest();
    drawSun();

    // The whole village gathers for the memorial
    drawPersonAt(-0.15);
    drawPersonAt(0.05);
    drawPersonAt(-0.90);
    drawPersonAt(0.90);

    drawMemorialBell(0.62,-0.05);
    drawMemorialSapling(-0.15,-0.05);
    drawRisingFlag(0.05,-0.25);

    drawWindmill(0.92,0.0);
    drawBird(birdX,0.55);
    drawPulsingFlower(-0.55,-0.02);
}

void drawSirenTower(float x,float baseY)
{
    glColor3ub(150,150,150);
    glBegin(GL_QUADS);
    glVertex2f(x-0.02,baseY);
    glVertex2f(x+0.02,baseY);
    glVertex2f(x+0.012,baseY+0.30);
    glVertex2f(x-0.012,baseY+0.30);
    glEnd();

    glPushMatrix();
    glTranslatef(x,baseY+0.30,0);        // TRANSLATION - pivot at the siren head
    glRotatef(sirenAngle,0,0,1);         // ROTATION - rotating warning beacon
    glColor3ub(255,60,60);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,0);
    glVertex2f(0.10,0.02);
    glVertex2f(0.10,-0.02);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0,0);
    glVertex2f(-0.10,0.02);
    glVertex2f(-0.10,-0.02);
    glEnd();
    glColor3ub(255,220,0);
    circle(0,0,0.02);
    glPopMatrix();
}

void drawWaterLevelSign(float x,float y)
{
    glPushMatrix();
    glTranslatef(x,y,0);                 // TRANSLATION - sign position
    glScalef(warnScale,warnScale,1.0f);  // SCALING - pulsing to draw the eye
    glColor3ub(255,210,0);
    glBegin(GL_QUADS);
    glVertex2f(-0.06,0);
    glVertex2f(0.06,0);
    glVertex2f(0.06,0.08);
    glVertex2f(-0.06,0.08);
    glEnd();
    glColor3ub(30,30,30);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.02,0.045);
    glVertex2f(0.02,0.045);
    glVertex2f(0,0.065);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.006,0.02);
    glVertex2f(0.006,0.02);
    glVertex2f(0.006,0.04);
    glVertex2f(-0.006,0.04);
    glEnd();
    glPopMatrix();

    glColor3ub(90,90,90);
    glBegin(GL_LINES);
    glVertex2f(x,y);
    glVertex2f(x,y-0.10);
    glEnd();
}

void drawPatrolBoat(float bx)
{
    float waterY=-0.55f;

    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex2f(bx-0.10,waterY);
    glVertex2f(bx+0.10,waterY);
    glVertex2f(bx+0.11,waterY-0.03);
    glVertex2f(bx-0.11,waterY-0.03);
    glEnd();

    glColor3ub(0,120,180);
    glBegin(GL_QUADS);
    glVertex2f(bx-0.04,waterY);
    glVertex2f(bx+0.04,waterY);
    glVertex2f(bx+0.04,waterY+0.05);
    glVertex2f(bx-0.04,waterY+0.05);
    glEnd();
}

void drawHopeBanner()
{
    // A simple floating ribbon-style banner shape (no external text assets),
    // rising and gently swaying - the "something different and meaningful"
    // closing touch for the very last scene of the story.
    float y = 0.62f + 0.02f*sin(bannerFloat);

    glPushMatrix();
    glTranslatef(0,y,0);                 // TRANSLATION - gentle float
    float s = 1.0f+0.03f*sin(bannerFloat*1.5f);
    glScalef(s,1.0f,1.0f);               // SCALING - subtle breathing
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
    glVertex2f(-0.45,-0.05);
    glVertex2f(0.45,-0.05);
    glVertex2f(0.45,0.05);
    glVertex2f(-0.45,0.05);
    glEnd();
    glColor3ub(230,30,60);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.45,-0.05);
    glVertex2f(-0.45,0.05);
    glVertex2f(-0.55,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.45,-0.05);
    glVertex2f(0.45,0.05);
    glVertex2f(0.55,0.0);
    glEnd();
    glPopMatrix();


    glColor3ub(40,40,40);
    drawBitmapText(-0.34f,y-0.006f,GLUT_BITMAP_HELVETICA_18,"TOGETHER WE REBUILD, TOGETHER WE STAND");
}

void scene10()
{
    drawSky();
    drawRainbow();
    drawHills();
    drawWaterfall();
    drawGrass();
    drawRiver();
    drawRoad();
    drawHouse1();
    drawHouse2();
    drawForest();
    drawSun();

    drawPersonAt(-0.20);
    drawPersonAt(0.30);


    drawSirenTower(-0.95,0.0);
    drawWaterLevelSign(0.70,-0.15);
    drawPatrolBoat(patrolBoatX);
    drawWindmill(0.92,0.0);

    drawBird(birdX,0.55);
    drawBird(birdX2,0.62);
    drawPulsingFlower(-0.55,-0.02);

    // Special closing touch for the final scene
    drawHopeBanner();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(scene==1)       scene1();
    else if(scene==2)  scene2();
    else if(scene==3)  scene3();
    else if(scene==4)  scene4();
    else if(scene==5)  scene5();
    else if(scene==6)  scene6();
    else if(scene==7)  scene7();
    else if(scene==8)  scene8();
    else if(scene==9)  scene9();
    else if(scene==10) scene10();

    glFlush();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1,1,-1,1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1400,900);
    glutInitWindowPosition(50,50);

    glutCreateWindow("Flood Rescue Mission - Press N/P to change scene, R to restart");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);   // scene changes are now driven by the keyboard

    glutTimerFunc(16, update, 0);

    // Start Scene 1 audio
    playSceneAudio(scene);

    glutMainLoop();

    return 0;
}





















