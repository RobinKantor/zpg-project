/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Application.h"


int main(void)
{
    Application* app = new Application();

    app->initialization();
    app->createShaders();
    app->createModels();
    app->createScenes();
    app->run();

    return 0;
}