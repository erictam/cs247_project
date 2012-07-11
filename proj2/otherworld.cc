#include "otherworld.h"
#include "Game.h"
#include "controller.h"
#include <iostream>

// Sets the horizontal box to have homogeneous spacing (all elements are of the same size), and to put 10 pixels
// between each widget. Initializes the pixel buffer for the null place holder card, and the 10 of spades.
// Puts a frame in the window, and lays out the widgets horizontally. Four widgets are images, the fifth is a button
// with an image in it.
//
// Since widgets cannot be shared, must use pixel buffers to share images.
OtherWorld::OtherWorld( Controller* c, Game* g) 
    : table( 5, 4, false), newGameButton("New Game"), endGameButton("End Game"),
        game_(g), controller_(c) {

    //const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage( TEN, SPADE );

    // Sets the border width of the window.
    set_border_width( 10 );

    // Set the look of the frame.
    frame.set_label( "Cards:" );
    frame.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
    frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
 
    // Add the frame to the window. Windows can only hold one widget, same for frames.
    add( frame );

    // Add the horizontal box for laying out the images to the frame.
    frame.add( table );
    
    hbox[0].add(newGameButton);
    hbox[0].add(endGameButton);


    table.attach(hbox[0], 0, 4, 0, 1);
    for (int i = 1; i < 5; i++) {
        table.attach(hbox[i], 0, 4, i, i + 1);
    }

    // Initialize 4 empty cards and place them in the box.
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 13; i++ ) {
            card[0] = new Gtk::Image( deck.getCardImage( (Faces)(i), (Suits)(j) ) );
            button[j * 13 + i].set_image( *card[0] );	
            hbox[j + 1].add( button[j * 13 + i] );
            button[j*13+i].signal_clicked().connect( sigc::mem_fun( *this, &OtherWorld::newGameButtonClicked ) );

        } // for
    }

    std::cout<<"something";

    newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &OtherWorld::newGameButtonClicked ) );
    //newGameButton.signal_clicked().connect( sigc::ptr_fun( &newGameButtonClicked ) );

    // Initialize the 5th card and place the image into the button.
    //card[4] = new Gtk::Image( cardPixbuf );	
    //button.set_image( *card[4] );	

    // Add the button to the box.
    //hbox.add( button );

    // The final step is to display this newly created widget.
    show_all();

    game_->subscribe(this);
} 

OtherWorld::~OtherWorld() {
    for (int i = 0; i < 52; i++ ) delete card[i];
} 

void OtherWorld::newGameButtonClicked() {
    controller_->newGameButtonClicked();
}

void newGameButtonClicked() {
    std::cout<<"something";
}

void OtherWorld::update() {
    int currentPlayer = game_->getCurrentPlayer();

    if (currentPlayer == 12) {
         card[0] = new Gtk::Image ( deck.getNullCardImage() );
        
    }
    button[ 13 ].set_image( *card[0] );	
}
