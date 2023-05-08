#include "app.h"


int main(int argc, char* argv[])
{
    App app;
    init_app(&app, 800, 600);

    handle_events(&app);

    destroy_app(&app);
    
    return 0;
}