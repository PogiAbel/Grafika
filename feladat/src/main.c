#include "app.h"


int main(int argc, char* argv[])
{
    App app;

    init_app(&app, 800, 600);
    while(app.is_running)
    {
        handle_events(&app);
        update_app(&app);
        render(&app);
    }
    destroy_app(&app);
    
    return 0;
}