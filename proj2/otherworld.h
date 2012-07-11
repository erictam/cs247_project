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

class OtherWorld : public Observer {
public:
	OtherWorld();
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

    void startGame();   // Brings up four dialog boxes to set each player.
}; // OtherWorld

#endif
