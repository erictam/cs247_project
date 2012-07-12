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
	Gtk::Image                     *card[52];          // Images to display.

    Gtk::HBox                       topHBox;
	Gtk::HBox                       tableHBox[4];             // Horizontal box for aligning widgets in the window.
    Gtk::VBox                       rageVBox[4];
    Gtk::HBox                       playerHBox;
    Gtk::HBox                       discardHBox;
	
    Gtk::Frame                      frame;            // Create a nice framed border for the box.
    Gtk::Table                      mainTable;
    Gtk::Table                      playedCardsTable;

    Gtk::Button                     newGameButton;
    Gtk::Button                     endGameButton;
	Gtk::Button                     tableButton[52];           // Button that will hold an image.
    Gtk::Button                     rageButton[4];
    Gtk::Button                     playerCardButton[13];
    Gtk::Button                     discardButton[13];

    Gtk::SpinButton                 seedButton;

    Gtk::Label                      pointsLabel[4];
    Gtk::Label                      discardsLabel[4];
    Gtk::Frame                      playedCardsFrame;
    Gtk::Frame                      playerFrame[4];
    Gtk::Frame                      yourHandFrame;

    Game*                           game_;

    Controller*                     controller_;

    void update();
    void newGameButtonClicked();
    void setPlayerTypes();   // Brings up four dialog boxes to set each player.
    void playerCardButtonClicked(unsigned int);
    void discardButtonClicked(unsigned int);

}; // View

#endif
