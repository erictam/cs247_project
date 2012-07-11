#ifndef __OTHER_WORLD_H
#define __OTHER_WORLD_H
/*#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>*/

//#include <gtkmm.h>
#include "Observer.h"

#include "DeckGUI.h"

class Game;
class Controller;

class OtherWorld : public Observer, public Gtk::Window {
public:
	OtherWorld( Controller*, Game* );
	virtual ~OtherWorld();
	
private:
	DeckGUI                         deck;             // Knows all of the card pixel buffers.
	
	// Member widgets:
	Gtk::Image                    * card[52];          // Images to display.
	Gtk::Button                     button[52];           // Button that will hold an image.
	Gtk::HBox                       hbox[5];             // Horizontal box for aligning widgets in the window.
	Gtk::Frame                      frame;            // Create a nice framed border for the box.
    Gtk::VBox                       vbox[13];
    Gtk::Table                      table;
    Gtk::Button                     newGameButton;
    Gtk::Button                     endGameButton;

    Game*                           game_;

    Controller*                     controller_;

    void update();
    void newGameButtonClicked();

}; // OtherWorld

#endif
