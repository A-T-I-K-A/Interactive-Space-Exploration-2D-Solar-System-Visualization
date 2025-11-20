#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <vector>
// -------------------- GLOBALS --------------------
// -------------------- CLOUD AND TREE --------------------
float cloudX = -700;  // starting x for moving clouds
float cloudSpeed = 0.5f; // speed of clouds
// -------------------- STAR BACKGROUND --------------------
const int STAR_COUNT = 100;
float star_x[STAR_COUNT];
float star_y[STAR_COUNT];
bool star_on[STAR_COUNT];
float telescopeAngle = 0.0f; // current tilt of telescope
float telescopeAngleStep = 2.0f; // speed of up/down rotation
// Rotation angles
float angle_planet[9] = {0};
// Slower orbit speeds
float angle_speed[9]  = {0.01f, 0.008f, 0.006f, 0.004f, 0.003f, 0.002f, 0.0015f, 0.0012f, 0.001f};
// Orbit radii
float orbit_radius[9] = {70, 110, 150, 200, 260, 320, 380, 440, 500};
// Planet sizes
float planet_size[9] = {6, 10, 12, 10, 18, 16, 14, 14, 8};
// Planet colors (R,G,B)
float planet_color[9][3] = {
    {0.55f, 0.55f, 0.55f}, // Mercury (gray)
    {0.90f, 0.75f, 0.55f}, // Venus (beige)
    {0.25f, 0.45f, 0.85f}, // Earth (blue)
    {0.85f, 0.35f, 0.20f}, // Mars (red-orange)
    {0.85f, 0.70f, 0.45f}, // Jupiter (tan)
    {0.95f, 0.85f, 0.55f}, // Saturn (pale yellow)
    {0.65f, 0.85f, 0.90f}, // Uranus (cyan)
    {0.30f, 0.45f, 0.80f}, // Neptune (deep blue)
    {1.00f, 0.60f, 0.00f}  // Pluto (warm orange tone)
};
// Names
std::string planet_names[10] = {
    "Mercury", "Venus", "Earth", "Mars", "Jupiter",
    "Saturn", "Uranus", "Neptune", "Pluto", "Sun"
};
// Facts
std::vector<std::string> planet_facts[10] = {
    {"Mercury:", "Smallest and fastest planet","Diameter: 4,879 km","orbits in 88 days.", "No atmosphere causes extreme temperatures."},
    {"Venus:", "Hottest planet with thick CO2 atmosphere.","Diameter: 12,104 km", "Spins backward (retrograde rotation)."},
    {"Earth:", "Only known planet with life and liquid water.","Diameter: 12,742 km", "Has a nitrogen-oxygen atmosphere."},
    {"Mars:", "Red surface due to iron oxide (rust).", "Diameter: 6,779 km","Home to Olympus Mons, the largest volcano."},
    {"Jupiter:", "Largest planet; massive gas giant.","Diameter: 139,820 km", "Has Great Red Spot, a centuries-old storm."},
    {"Saturn:", "Famous for its icy ring system.", "Diameter: 116,460 km", "Has over 80 moons including Titan."},
    {"Uranus:", "Rotates on its side at 98 degree tilt.","Diameter: 50,724 km", "Blue-green color from methane gas."},
    {"Neptune:", "Windiest planet with 2000 km/h storms.","Diameter: 49,244 km",  "Discovered through mathematical prediction."},
    {"Pluto:", "Dwarf planet with icy surface.","Diameter: 2,377 km", "Has heart-shaped glacier","called Tombaugh Regio."},
    {"The Sun:", "Contains 99.8% of Solar System's mass.", "Diameter: 1.39M km",  "Core reaches 15 million degree Celsius", "powering fusion."}
};
// Screen state
int currentScreen = 0; // 0 = intro, 1 = solar system, 2 = planet info
int selectedPlanetIndex = -1;
bool paused = false;   // toggle pause/resume
// ---------------- Utility: Draw circle ----------------
void drawCircle(float cx, float cy, float r, int num_segments, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
// ---------------- Utility: Draw text ----------------
void drawText(const std::string &text, float x, float y, float scale = 0.2f) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }
    glPopMatrix();
}
// ---------------- Draw Background Stars ----------------
void drawStars() {
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < STAR_COUNT; i++) {
        if (star_on[i]) {
            glColor3f(1.0f, 1.0f, 1.0f); // white star
            glVertex2f(star_x[i], star_y[i]);
        }
    }
    glEnd();
}
void displayIntroScene() {
    glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(0.0f, 0.1f, 0.3f);
    // Background gradient
    glBegin(GL_QUADS);
    glVertex2f(-700, 600);
    glVertex2f(700, 600);
    glVertex2f(700, -600);
    glVertex2f(-700, -600);
    glEnd();
drawStars();
     // --- Moving clouds ---
   glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(cloudX, 350, 25, 40, 1, 1, 1);
    drawCircle(cloudX+20, 360, 30, 40, 1, 1, 1);
    drawCircle(cloudX+40, 350, 25, 40, 1, 1, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(cloudX+250, 400, 30, 40, 1, 1, 1);
    drawCircle(cloudX+274, 412, 36, 40, 1, 1, 1);
    drawCircle(cloudX+298, 400, 30, 40, 1, 1, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(cloudX+550, 500, 20, 40, 1, 1, 1);
    drawCircle(cloudX+566, 508, 24, 40, 1, 1, 1);
    drawCircle(cloudX+582, 500, 20, 40, 1, 1, 1);
    // Ground
    glColor3f(0.1f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-700, -200);
    glVertex2f(700, -200);
    glVertex2f(700, -600);
    glVertex2f(-700, -600);
    glEnd();
    glColor3f(0.4f, 0.25f, 0.1f);//tree1
    glBegin(GL_QUADS);
    glVertex2f(-520, -100);
    glVertex2f(-480, -100);
    glVertex2f(-480, -200);
    glVertex2f(-520, -200);
    glEnd();
    drawCircle(-500, -85, 50, 50, 0.0f, 0.6f, 0.0f);
    drawCircle(-530, -100, 40, 50, 0.0f, 0.7f, 0.0f);
    drawCircle(-470, -100, 40, 50, 0.0f, 0.7f, 0.0f);
    glColor3f(0.4f, 0.25f, 0.1f);//tree2
    glBegin(GL_QUADS);
    glVertex2f(-320, -80);
    glVertex2f(-275, -80);
    glVertex2f(-275, -200);
    glVertex2f(-320, -200);
    glEnd();
    drawCircle(-300, -62, 60, 50, 0.0f, 0.6f, 0.0f);
    drawCircle(-336, -80, 48, 50, 0.0f, 0.7f, 0.0f);
    drawCircle(-264, -80, 48, 50, 0.0f, 0.7f, 0.0f);
     glColor3f(0.4f, 0.25f, 0.1f);//tree3
    glBegin(GL_QUADS);
    glVertex2f(385, -100);
    glVertex2f(420, -100);
    glVertex2f(420, -200);
    glVertex2f(385, -200);
    glEnd();
    drawCircle(400, -85, 50, 50, 0.0f, 0.6f, 0.0f);
    drawCircle(370, -100, 40, 50, 0.0f, 0.7f, 0.0f);
    drawCircle(430, -100, 40, 50, 0.0f, 0.7f, 0.0f);
     glColor3f(0.4f, 0.25f, 0.1f);//tree4
    glBegin(GL_QUADS);
    glVertex2f(530, -70);
    glVertex2f(580, -70);
    glVertex2f(580, -200);
    glVertex2f(530, -200);
    glEnd();
    drawCircle(550, -49, 70, 50, 0.0f, 0.6f, 0.0f);
    drawCircle(508, -70, 56, 50, 0.0f, 0.7f, 0.0f);
    drawCircle(592, -70, 56, 50, 0.0f, 0.7f, 0.0f);
    // Telescope tripod
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
    glVertex2f(-100, -200); glVertex2f(-130, -320);
    glVertex2f(-100, -200); glVertex2f(-70, -320);
    glEnd();
    // Telescope body (rotating)
    glPushMatrix();
    glTranslatef(-100, -200, 0);
    glRotatef(telescopeAngle, 0, 0, 1);
    glColor3f(0.7f, 0.7f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0); glVertex2f(150, 20);
    glVertex2f(150, -20); glVertex2f(0, 0);
    glEnd();
    drawCircle(150, 0, 10, 30, 0.6f, 0.8f, 1.0f); // lens
    glPopMatrix();
    // person next to telescope
    drawCircle(-160, -200, 20, 80, 1.0f, 0.8f, 0.6f); // head
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_QUADS); // neck
    glVertex2f(-158, -218);
    glVertex2f(-170, -218);
    glVertex2f(-170, -240);
    glVertex2f(-158, -240);
    glEnd();
glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); // body
    glVertex2f(-140, -237);
    glVertex2f(-185, -237);
    glVertex2f(-185, -280);
    glVertex2f(-140, -280);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); // hand
    glVertex2f(-165, -250);
    glVertex2f(-145, -243);
    glVertex2f(-125, -265);
    glVertex2f(-135, -275);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); // right leg
    glVertex2f(-140, -280);
    glVertex2f(-160, -280);
    glVertex2f(-160, -320);
    glVertex2f(-140, -320);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); // left leg
    glVertex2f(-185, -280);
    glVertex2f(-165, -280);
    glVertex2f(-165, -320);
    glVertex2f(-185, -320);
    glEnd();
    // Instructions
    glColor3f(1, 1, 1);
    drawText("Welcome To Interactive Space Exploration: 2D Solar System Visualization", -430, 450, 0.2f);
    glutSwapBuffers();
}
void specialKeys(int key, int x, int y) {
    if (currentScreen == 0) {
        if (key == GLUT_KEY_UP && telescopeAngle < 45)
            telescopeAngle += telescopeAngleStep;
        else if (key == GLUT_KEY_DOWN && telescopeAngle > -20)
            telescopeAngle -= telescopeAngleStep;
        glutPostRedisplay();
    }
}
// ---------------- Draw Gradient Universe Background ----------------
void drawUniverseBackground() {
    glBegin(GL_QUADS);
    // Dark outer space colors (based on palette)
    glColor3f(0.05f, 0.07f, 0.12f); // top-left (dark navy)
    glVertex2f(-700, 600);
    glColor3f(0.07f, 0.09f, 0.15f); // top-right (deep blue-gray)
    glVertex2f(700, 600);
    // Bottom colors (slightly purple-red tone)
    glColor3f(0.12f, 0.06f, 0.09f); // bottom-right (muted maroon)
    glVertex2f(700, -600);
    glColor3f(0.10f, 0.04f, 0.08f); // bottom-left (deep purple)
    glVertex2f(-700, -600);
    glEnd();
    // Central nebula glow overlay (lighter gradient)
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.6f, 0.5f, 0.8f, 0.6f); // center glow (light lavender-blue)
    glVertex2f(0, 0);
    glColor4f(0.2f, 0.15f, 0.25f, 0.0f); // edge fade
    for (int i = 0; i <= 100; i++) {
        float theta = 2.0f * 3.1415926f * i / 100;
        float x = 700 * cosf(theta);
        float y = 600 * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
// ---------------- Solar System Screen ----------------
void displaySolarSystem() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawUniverseBackground(); // gradient universe
    drawStars();              // then stars on top
    // Title
    glColor3f(1,1,1);
    drawText("Solar System", -600, 450, 0.3f);
    // Draw the Sun
    drawCircle(0.0f, 0.0f, 40.0f, 200, 1.0f, 1.0f, 0.0f);
    drawText("Sun", -20, -60, 0.2f);
    // Draw orbits and planets
    for (int i = 0; i < 9; i++) {
        // Orbit
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 100; j++) {
            float theta = 2.0f * 3.1415926f * j / 100;
            float x = orbit_radius[i] * cosf(theta);
            float y = orbit_radius[i] * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
        // Planet position
        float px = orbit_radius[i] * cos(angle_planet[i]);
        float py = orbit_radius[i] * sin(angle_planet[i]);

        drawCircle(px, py, planet_size[i], 50,
                   planet_color[i][0], planet_color[i][1], planet_color[i][2]);
         drawText(planet_names[i], px + 12, py + 12, 0.15f);
    }
    glutSwapBuffers();
}
// ---------------- Planet Info Screen ----------------
void displayPlanetInfo() {
    glClear(GL_COLOR_BUFFER_BIT);
    // ---- Background Gradient ----
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.07f, 0.12f); // top
    glVertex2f(-700, 600);
    glColor3f(0.07f, 0.09f, 0.15f); // top-right
    glVertex2f(700, 600);
    glColor3f(0.12f, 0.06f, 0.09f); // bottom-right
    glVertex2f(700, -600);
    glColor3f(0.10f, 0.04f, 0.08f); // bottom-left
    glVertex2f(-700, -600);
    glEnd();
    // ---- Planet Display on Left ----
    if (selectedPlanetIndex == 9) { // Sun
        drawCircle(-250, 0, 80, 200, 1.0f, 1.0f, 0.0f);
    } else {
        drawCircle(-250, 0, 60, 200,
                   planet_color[selectedPlanetIndex][0],
                   planet_color[selectedPlanetIndex][1],
                   planet_color[selectedPlanetIndex][2]);
    }
    // ---- Title Header ----
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(planet_names[selectedPlanetIndex], -80, 220, 0.35f);
    // ---- Fact Box Background Glow ----
    glBegin(GL_QUADS);
    glColor4f(0.3f, 0.3f, 0.4f, 0.4f); // light glow
    glVertex2f(40, 170);
    glVertex2f(650, 170);
    glVertex2f(650, -170);
    glVertex2f(40, -170);
    glEnd();
    // ---- Border ----
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(40, 170);
    glVertex2f(650, 170);
    glVertex2f(650, -170);
    glVertex2f(40, -170);
    glEnd();
    // ---- Facts ----
    float yPos = 120;
    for (const auto &line : planet_facts[selectedPlanetIndex]) {
        drawText(line, 60, yPos, 0.2f);
        yPos -= 45;
    }
    // ---- Hint ----
    glColor3f(0.8f, 0.8f, 0.8f);
    drawText("Click anywhere to return", -160, -250, 0.18f);
    glutSwapBuffers();
}
// ---------------- Display ----------------
void display() {
    if (currentScreen == 0)
        displayIntroScene();
    else if (currentScreen == 1)
        displaySolarSystem();
    else
        displayPlanetInfo();
}
// ---------------- Update Animation ----------------
void update(int value) {
    if (!paused && currentScreen == 1) {  // solar system screen animates
        for (int i = 0; i < 9; i++) {
            angle_planet[i] += angle_speed[i];
            if (angle_planet[i] > 2 * M_PI) angle_planet[i] -= 2 * M_PI;
        }

        // Twinkling stars
        for (int i = 0; i < STAR_COUNT; i++) {
            if (rand() % 20 == 0) {
                star_on[i] = !star_on[i];
            }
        }
    }
if (currentScreen == 0) { // intro scene
    cloudX += cloudSpeed;
    if (cloudX > 800) cloudX = -730; // loop clouds
}

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
// ---------------- Mouse Input ----------------
void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) return;
    int windowW = glutGet(GLUT_WINDOW_WIDTH);
    int windowH = glutGet(GLUT_WINDOW_HEIGHT);
    // Convert mouse coordinates to OpenGL space
    float glX = (x / (float)windowW) * 1400 - 700;
    float glY = ((windowH - y) / (float)windowH) * 1200 - 600;
    // ---------- Intro Screen ----------
    if (currentScreen == 0) {
        if (x > windowW / 2) { // clicked right side
            currentScreen = 1;
        }
        return;
    }
    // ---------- Solar System Screen ----------
    if (currentScreen == 1) {
        // Check Sun
        if (sqrt(glX * glX + glY * glY) < 50) {
            selectedPlanetIndex = 9;
            currentScreen = 2;
            return;
        }
        // Check planets
        for (int i = 0; i < 9; i++) {
            float px = orbit_radius[i] * cos(angle_planet[i]);
            float py = orbit_radius[i] * sin(angle_planet[i]);
            float dist = sqrt((glX - px) * (glX - px) + (glY - py) * (glY - py));
            if (dist < planet_size[i] + 10) { // small click buffer
                selectedPlanetIndex = i;
                currentScreen = 2;
                return;
            }
        }
        // If clicked elsewhere -> back to intro
        currentScreen = 0;
        return;
    }
    // ---------- Planet Info Screen ----------
    if (currentScreen == 2) {
        currentScreen = 1; // return to solar system
    }
}
// ---------------- Main ----------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutCreateWindow("2D Solar System");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-700, 700, -600, 600);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(25, update, 0);
        // Generate random star positions
    for (int i = 0; i < STAR_COUNT; i++) {
        star_x[i] = (rand() % 1400) - 700; // Range -700 to 700 (X)
        star_y[i] = (rand() % 1200) - 600; // Range -600 to 600 (Y)
        star_on[i] = rand() % 2;           // Random on/off
    }
    glutMainLoop();
    return 0;
}
