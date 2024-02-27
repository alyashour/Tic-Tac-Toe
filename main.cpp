#include <SFML/Graphics.hpp>
#include <iostream>


enum State {
    X,
    O,
    Empty
};

struct Cell {
    State state;
    sf::FloatRect bounds;
};

// global constants
const std::string fontFile = "EnvyCodeRNerdFontMono-Regular.ttf";
const float windowWidth = 800.f;
const float windowMargin = 50.f;
const sf::FloatRect playArea(windowMargin, windowMargin, windowWidth - 2 * windowMargin, windowWidth - 2 * windowMargin);
const float lineThickness = 20.f;
const float cellSideLength = (playArea.height - 2.f * lineThickness) / 3.f;

// global variables
State winningPlayer = State::Empty;
bool gameIsTied = false;

/// @brief Checks all the conditions for a win
/// @param gameBoard the current game board (a 3x3 board of cells)
/// @param currentTurn who just went (i.e, the person who just won)
void checkForWin(Cell gameBoard[][3], State currentTurn){
    // there are 8 ways to win
    // 2 diagonals
    if ((gameBoard[0][0].state == gameBoard[1][1].state && gameBoard[1][1].state == gameBoard[2][2].state) ||
        (gameBoard[2][0].state == gameBoard[1][1].state && gameBoard[1][1].state == gameBoard[0][2].state)) {
        if (gameBoard[1][1].state != State::Empty) winningPlayer = currentTurn; // empty states are also equivalent so they must be weeded out
    }
    // 3 horizontal and 3 vertical
    for (int i = 0; i < 3; i++)
        if ((gameBoard[i][0].state != State::Empty && gameBoard[i][0].state == gameBoard[i][1].state && gameBoard[i][1].state == gameBoard[i][2].state)
            || (gameBoard[0][i].state != State::Empty && gameBoard[0][i].state == gameBoard[1][i].state && gameBoard[1][i].state == gameBoard[2][i].state)) {
            winningPlayer = currentTurn;
        }
}

/// @brief Calculates who's turn it currently is using the number of turns passed (assuming X goes first)
/// Optionally, pass in the current state of the cell that was just clicked to keep it the same
/// @param numOfTurnsPassed 
/// @param currentState 
/// @return 
State whosTurn(int numOfTurnsPassed) {
    // calculate who's turn it is
    // x always goes first so if the total number of turns passed is even, its Xs turn, otherwise O
    // and if the number of turns passed is 9 the game is over!
    if (numOfTurnsPassed % 2 == 0) {
        std::cout << "It is X's turn" << std::endl;
        return State::X;
    }
    else {
        std::cout << "It is O's turn" << std::endl;
        return State::O;
    }
}

sf::Text createText(sf::Font &font, std::string s, sf::Vector2f origin = sf::Vector2f(0, 0)){
    sf::Text text(s, font, playArea.height / 3.f);
    text.setCharacterSize(playArea.height / 3.f);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(origin);
    text.setPosition(0, 0);

    return text;
}


/// <summary>
/// This is an event handler for left mouse clicks
/// </summary>
/// <param name="event">The event object. It contains the click type and click position</param>
/// <param name="gameBoard">The board that contains the current game state</param>
void handleLeftMouseClick(sf::Event::MouseButtonEvent event, Cell gameBoard[][3]) {
    // break out if a player has already won!
    if (winningPlayer != State::Empty)
        return;

    // find board indices & count how many x's and o's there are in the board currently
    int gridX = -1, gridY = -1;
    int numOfTurnsPassed = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Cell cell = gameBoard[i][j];

            // find mouse index
            if (cell.bounds.contains(event.x, event.y)) gridX = i, gridY = j;

            // count number of emptys
            if (cell.state != State::Empty) numOfTurnsPassed++;
        }
    }
    
    // there are three event cases:
    // 1. the player clicked outside of the playing area
    if (gridX == -1 || gridY == -1) {
        // do nothing
        return;
    }

    // 2. the player clicked a vacant cell
    Cell &cell = gameBoard[gridX][gridY];
    State currentTurn = whosTurn(numOfTurnsPassed);

    if (cell.state == State::Empty) {
        // set the state of the cell to be the correct state
        std::cout << "cell is empty" << std::endl;
        cell.state = currentTurn;
    }

    // 3. the player clicked an occupied cell
    else {
        // do nothing
        std::cout << "Cell is occupied!" << std::endl;
        return;
    }

    // there are two final cases
    // check for win
    std::cout << "Checking for win!" << std::endl;
    checkForWin(gameBoard, currentTurn);
    // check for draw
    std::cout << "Checking for draw!" << std::endl;
    if (numOfTurnsPassed >= 8) gameIsTied = true;
}

/// @brief This is the right mouse click event handler
/// @param event the mouse button event information
/// @param gameBoard the current gameboard
void handleRightMouseClick(sf::Event::MouseButtonEvent event, Cell gameBoard[][3]){
    // reset global variables
    winningPlayer = State::Empty;
    gameIsTied = false;

    // reset gameBoard
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            gameBoard[i][j].state = State::Empty;
        }
    }
}

/// <summary>
/// Creates the visual board (the background lines)
/// </summary>
/// <param name="displayBoard">An array of size 4 that will contain the rectangles that make up the board</param>
/// <param name="length">The length of the lines</param>
/// <param name="thickness">The width of the lines</param>
void initializeBoard(sf::RectangleShape displayBoard[], float length, float thickness) {
    // make the board
    displayBoard[0] = sf::RectangleShape(sf::Vector2f(length, thickness));
    displayBoard[1] = sf::RectangleShape(sf::Vector2f(length, thickness));
    displayBoard[2] = sf::RectangleShape(sf::Vector2f(thickness, length));
    displayBoard[3] = sf::RectangleShape(sf::Vector2f(thickness, length));

    // set universal properties like colour
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape rect = displayBoard[i];
        rect.setFillColor(sf::Color::White);
    }

    // position the board lines
    // they are at 1/3 and 2/3 vertically and horizontally + the margins + the thickness of the line
    // horizontal
    displayBoard[0].setPosition(windowMargin, windowMargin + cellSideLength);       // 1/3
    displayBoard[1].setPosition(windowMargin, windowMargin + 2 * cellSideLength + lineThickness);   // 2/3
    // vertical
    displayBoard[2].setPosition(windowMargin + cellSideLength, windowMargin);       // 1/3
    displayBoard[3].setPosition(windowMargin + 2 * cellSideLength + lineThickness, windowMargin);   // 2/3
    
}

/// <summary>
/// This contains the event loop. It runs until the window runs out of events.
/// </summary>
/// <param name="window">The current playing window</param>
/// <param name="gameBoard">The 3 by 3 gameboard</param>
void eventUpdate(sf::RenderWindow& window, Cell gameBoard[3][3]) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        // attach event listeners here
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) handleLeftMouseClick(event.mouseButton, gameBoard);
                else if (event.mouseButton.button == sf::Mouse::Right) handleRightMouseClick(event.mouseButton, gameBoard);
                break;
        }
    }
}

/// <summary>
/// This is the main game loop.
/// </summary>
/// <param name="window">The main window</param>
/// <param name="displayBoard">An array of size 4 containing the lines that make up the board</param>
/// <param name="gameBoard">The 3 by 3 gameboard</param>
/// <param name="x">A Text object of proper size containing the letter "X"</param>
/// <param name="o">A Text object of proper size containing the letter "O"</param>
void gameUpdate(sf::RenderWindow& window, sf::RectangleShape displayBoard[], Cell gameBoard[3][3], sf::Text x, sf::Text o) {
    // runs the program as long as the window is open
    // this is the main/game loop
    while (window.isOpen())
    {
        eventUpdate(window, gameBoard);

        // start drawing
        window.clear();

        // draw the board
        for (int i = 0; i < 4; i++) {
            window.draw(displayBoard[i]);
        }

        // draw the Xs and Os
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Cell cell = gameBoard[i][j];
                State state = cell.state;
                sf::Vector2f cellCenter(cell.bounds.width / 2.f, cell.bounds.height / 2.f);
                sf::Vector2f offset(0, 0);
                switch (state) {
                    case X:
                        x.setPosition(cell.bounds.getPosition());
                        offset = cellCenter - sf::Vector2f(x.getLocalBounds().getSize().x / 2, x.getLocalBounds().getSize().y / 2);
                        x.move(offset);
                        window.draw(x);
                        break;
                    case O:
                        o.setPosition(cell.bounds.getPosition());
                        offset = cellCenter - sf::Vector2f(o.getLocalBounds().getSize().x / 2, o.getLocalBounds().getSize().y / 2);
                        o.move(offset);
                        window.draw(o);
                        break;
                    default:
                        break;
                }
            }
        }

        // if the game is won
        if (winningPlayer != State::Empty){
            // generate winCardText
            sf::Font font;
            font.loadFromFile(fontFile);

            std::string s = (winningPlayer == State::X ? "X" : "O");
            s.append(" has won!!!");
            sf::String s2 = "Right click to play again...";

            const uint textSize = 25;
            sf::Text winCardText(s, font, textSize);
            sf::Text winCardText2(s2, font, textSize);
            winCardText.setColor(sf::Color::Red);
            winCardText2.setColor(sf::Color::Red);
            winCardText.setPosition(200.f, 300.f);
            winCardText2.setPosition(200.f, 330.f);

            sf::RectangleShape winCard(sf::Vector2f(500.f, 300.f));
            winCard.setFillColor(sf::Color::White);
            winCard.setPosition(150.f, 250.f);

            window.draw(winCard);
            window.draw(winCardText);
            window.draw(winCardText2);
        }

        else if (gameIsTied){
            // generate winCardText
            sf::Font font;
            font.loadFromFile(fontFile);

            std::string s = "Game ended in a tie!!";
            sf::String s2 = "Right click to play again...";

            const uint textSize = 25;
            sf::Text drawCardText(s, font, textSize);
            sf::Text playAgainText(s2, font, textSize);
            drawCardText.setColor(sf::Color::Red);
            playAgainText.setColor(sf::Color::Red);
            drawCardText.setPosition(200.f, 300.f);
            playAgainText.setPosition(200.f, 330.f);

            sf::RectangleShape drawCard(sf::Vector2f(500.f, 300.f));
            drawCard.setFillColor(sf::Color::White);
            drawCard.setPosition(150.f, 250.f);

            window.draw(drawCard);
            window.draw(playAgainText);
            window.draw(drawCardText);
        }
        
        window.display();
    }
}

int main()
{
    // initialize window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowWidth), "Tic Tac Toe!", sf::Style::Titlebar | sf::Style::Close);

    // make the board
    sf::RectangleShape displayBoard[4];
    initializeBoard(displayBoard, playArea.height, lineThickness);

    // make the gameboard
    Cell gameBoard[3][3];

    // populate with empty states and define bounds
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j].state = State::Empty;
            gameBoard[i][j].bounds = sf::FloatRect(
                windowMargin + i * (cellSideLength + lineThickness), 
                windowMargin + j * (cellSideLength + lineThickness), 
                cellSideLength, 
                cellSideLength
            );
        }
    }

    /** It may be better to use a glyph of X and O as a picture here to be able to size it directly using Cell bounds.
     * But since font sizes are measured in pixels and I know the size of my window in pixels this works just great */
    // load fonts
    
    // make text
    sf::Font font;
    font.loadFromFile(fontFile);

    // these origin vectors come from the size of the glyphs relative to the global window
    sf::Text x = createText(font, "X", sf::Vector2f(17, 70));
    sf::Text o = createText(font, "O", sf::Vector2f(18, 70));

    // enter game loop
    gameUpdate(window, displayBoard, gameBoard, x, o);

    return 0;
}