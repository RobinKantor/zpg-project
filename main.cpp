/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Application.h"


int main()
{
    Application app;

    app.initialization();
    app.createShaders();
    app.createModels();
    app.createScenes();
    app.run();

    return 0;
}
