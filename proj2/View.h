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

class View : public Observer, public Gtk::Window {
public:
	View( Controller*, Game* );
	virtual ~View();
	
private:
	DeckGUI                         deck;             // Knows all of the card pixel buffers.
	
	// Member widgets:
	Gtk::Image                    * card[52];          // Images to display.
	Gtk::Button                     button[52];           // Button that will hold an image.
    Gtk::HBox                       topHBox;
    Gtk::HBox                       rageVBox[4];
	Gtk::HBox                       tableHBox[4];             // Horizontal box for aligning widgets in the window.
    Gtk::HBox                       playerHBox;
	Gtk::Frame                      frame;            // Create a nice framed border for the box.
    Gtk::VBox                       vbox[13];
    Gtk::Table                      table;
    Gtk::Button                     newGameButton;
    Gtk::Button                     endGameButton;
    Gtk::Button                     rageButton[4];
    Gtk::Button                     playerCardButton[13];

    Game*                           game_;

    Controller*                     controller_;

    void update();
    void newGameButtonClicked();
    void setPlayerTypes();   // Brings up four dialog boxes to set each player.
}; // View

#endif
