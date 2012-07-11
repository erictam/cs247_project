#include "View.h"
#include "Game.h"
#include "controller.h"
#include <gtkmm/main.h>

int main( int argc, char * argv[] ) {
	Gtk::Main  kit( argc, argv );      // Initialize gtkmm with the command line arguments, as appropriate.
    
    srand48(0);

    Game game;
    Controller controller(&game);

	View window(&controller, &game);                 // Create the window with the image.

	Gtk::Main::run( window );          // Show the window and return when it is closed.
	
	return 0;
} // main
