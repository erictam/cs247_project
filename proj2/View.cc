#include "View.h"
#include "Game.h"
#include "controller.h"
#include <iostream>

// Sets the horizontal box to have homogeneous spacing (all elements are of the same size), and to put 10 pixels
// between each widget. Initializes the pixel buffer for the null place holder card, and the 10 of spades.
// Puts a frame in the window, and lays out the widgets horizontally. Four widgets are images, the fifth is a button
// with an image in it.
//
// Since widgets cannot be shared, must use pixel buffers to share images.
View::View( Controller* c, Game* g) 
    : mainTable( 5, 4, false), playedCardsTable(4,1,false), newGameButton("New Game"),
    endGameButton("End Game"), game_(g), controller_(c) {

        //const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage( TEN, SPADE );

        // Sets the border width of the window.
        set_border_width( 10 );

        // Set the look of the frame.
        //frame.set_label( "Cards:" );
        //frame.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
        //frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );

        // Add the frame to the window. Windows can only hold one widget, same for frames.
        //add( frame );

        // Add the horizontal box for laying out the images to the frame.
        //frame.add( table );
        //

        add(mainTable);

        // Links the startGame method to the New Game button
        //newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::setPlayerTypes ) );
        newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::newGameButtonClicked ) );

        topHBox.add(newGameButton);
        topHBox.add(endGameButton);

        mainTable.attach(topHBox, 0, 4, 0, 1);
        mainTable.attach(playedCardsFrame, 0, 4, 1, 2);
        for (int i = 0; i < 4; i++) {
            mainTable.attach(playerFrame[i], i, i + 1, 2, 3);
        }
        mainTable.attach(yourHandFrame, 0, 4, 3, 4);
        mainTable.attach(discardHBox, 0, 4, 4, 5);

        playedCardsFrame.add(playedCardsTable);
        playedCardsFrame.set_label("Cards on the table");



        // Initialize 4 empty cards and place them in the box.
        for (int j = 0; j < 4; j++) {
            playedCardsTable.attach(tableHBox[j], 0, 1, j, j+1);
            for (int i = 0; i < 13; i++ ) {
                //card[0] = new Gtk::Image( deck.getCardImage( (Rank)(i), (Suit)(j) ) );
                card[0] = new Gtk::Image ( deck.getNullCardImage() );
                tableButton[j * 13 + i].set_image( *card[0] );	
                tableHBox[j].add( tableButton[j * 13 + i] );
                //button[j*13+i].signal_clicked().connect( sigc::mem_fun( *this, &View::newGameButtonClicked ) );

            } // for
        }

        for (int i = 0; i < 4; i++) {
            std::stringstream sstream;
            sstream << "Player "<< i + 1;
            playerFrame[i].set_label(sstream.str());
            playerFrame[i].add(rageVBox[i]);

            rageButton[i].set_label("Rage!");
            rageVBox[i].add(rageButton[i]);

            pointsLabel[i].set_label("0 points");
            rageVBox[i].add(pointsLabel[i]);

            discardsLabel[i].set_label("0 discards");
            rageVBox[i].add(discardsLabel[i]);
        }

        yourHandFrame.set_label("Your hand");
        yourHandFrame.add(playerHBox);

        for (int i = 0; i < 13; i++ ) {
            //card[0] = new Gtk::Image( deck.getCardImage( (Rank)(i), (Suit)(j) ) );
            card[0] = new Gtk::Image ( deck.getNullCardImage() );
            playerCardButton[i].set_image( *card[0] );	
            playerHBox.add( playerCardButton[i] );
            //button[j*13+i].signal_clicked().connect( sigc::mem_fun( *this, &View::newGameButtonClicked ) );
            
            discardButton[i].set_label("Discard");
            discardHBox.add(discardButton[i]);
            discardButton[i].signal_clicked().connect( sigc::bind( sigc::mem_fun( *this, &View::discardButtonClicked ), i ));
            
        } // for


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

View::~View() {
    for (int i = 0; i < 52; i++ ) delete card[i];
} 

void View::newGameButtonClicked() {
    controller_->newGameButtonClicked();
}

void newGameButtonClicked() {
    std::cout<<"something";
}

void View::update() {
    GameState currentState = game_->getCurrentState();

    bool* table = game_->getTable();

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 13; i++ ) {
            if (table[j * 13 + i])
                card[0] = new Gtk::Image( deck.getCardImage( (Rank)(i), (Suit)(j) ) );
            else
                card[0] = new Gtk::Image( deck.getNullCardImage() );
            tableButton[j * 13 + i].set_image( *card[0] );	
        } 
    }
    
    if (currentState == NEWGAME) {

        //popup boxes prompting player types
        setPlayerTypes();

        //card[0] = new Gtk::Image ( deck.getNullCardImage() );
        //button[ 13 ].set_image( *card[0] );

        game_->startGame();
    }

    if (currentState == TAKETURN) {
        int currentPlayer = game_->getCurrentPlayer();
        std::vector<Card> hand = game_->getHand(currentPlayer - 1);

        for (int i = 0; (unsigned)i < hand.size(); i++) {
            card[0] = new Gtk::Image( deck.getCardImage( hand[i].getRank(), hand[i].getSuit() ) );
            playerCardButton[i].set_image( *card[0] );
            playerCardButton[i].signal_clicked().connect( sigc::bind( sigc::mem_fun( *this, &View::playerCardButtonClicked ), i ));
        }
        for (int i = hand.size(); i < 13; i++) {
            card[0] = new Gtk::Image( deck.getNullCardImage() );
            playerCardButton[i].set_image( *card[0] );
        } 
    }

} // View::~View()

// Creates dialog boxes to allow the user to choose whether each
// player is human or computer
void View::setPlayerTypes() {

    // Create the dialog box with a message and two buttons, Human and Computer.
    Gtk::Dialog dialog( "Player Type Selection", *this );
    Gtk::Label message("");
    Gtk::VBox* contentArea = dialog.get_vbox();
    contentArea->pack_start(message, true, false);
    message.show();

    // Link each button to an integer response when clicked.
    enum PlayerType {HUMAN, COMPUTER};
    dialog.add_button("Human", (int)HUMAN);
    dialog.add_button("Computer", (int)COMPUTER);

    // Stores the value of each player type, as a string.
    std::string playerTypes[4];

    for (int i = 1; i <= 4; i = i + 1) {

        // Sets the dialog box message
        std::stringstream sstream;
        sstream << "Is Player " << i << " a human or a computer?";
        message.set_label(sstream.str());

        // Wait for a response from the dialog box.
        int result = dialog.run();

        // Store the selection type for each player. If the dialog box is closed (Cancel),
        // the function returns with no players set.
        switch (result) {
            case (int)HUMAN:
                playerTypes[i - 1] = "h";
                break;
            case (int)COMPUTER:
                playerTypes[i - 1] = "c";
                break;
            default:
                return;
                break;
        } // switch
    } 
    controller_->setPlayers(playerTypes);
}

void View::playerCardButtonClicked(int cardClicked) {
    //card[0] = new Gtk::Image( deck.getCardImage( (Rank)(0), (Suit)(0) ) );
    //tableButton[ cardClicked ].set_image( *card[0] );	

    int currentPlayer = game_->getCurrentPlayer();
    std::vector<Card> hand = game_->getHand(currentPlayer - 1);
    controller_->tryPlayingCard(hand[cardClicked]); 
}

void View::discardButtonClicked(int cardClicked) {
    int currentPlayer = game_->getCurrentPlayer();
    std::vector<Card> hand = game_->getHand(currentPlayer - 1);
    controller_->tryDiscardingCard(hand[cardClicked]); 
}