#include <SFML/Graphics.hpp>
#include <iostream>

std::string fontFile = "EnvyCodeRNerdFontMono-Regular.ttf";
float windowWidth = 800.f;
float windowMargin = 50.f;
sf::FloatRect playArea{ windowMargin, windowMargin, windowWidth - 2 * windowMargin, windowWidth - 2 * windowMargin };
float lineThickness = 20.f;

enum State {
    X,
    O,
    Empty
};

struct Cell {
    State state;
    sf::FloatRect bounds;
};

void updateState(int numOfTurnsPassed, State& state) {
    // calculate who's turn it is
    // x always goes first so if the total number of turns passed is even, its Xs turn, otherwise O
    // and if the number of turns passed is 9 the game is over!
    if (numOfTurnsPassed >= 9) std::cout << "The game is over!" << std::endl;
    else if (numOfTurnsPassed % 2 == 0) state = State::X;
    else state = State::O;
}

/// <summary>
/// This is an event handler for left mouse clicks
/// </summary>
/// <param name="event">The event object. It contains the click type and click position</param>
/// <param name="gameBoard">The board that contains the current game state</param>
void handleLeftMouseClick(sf::Event::MouseButtonEvent event, Cell gameBoard[][3]) {
    sf::Vector2f mousePosition{ static_cast<float>(event.x), static_cast<float>(event.y) };
    // break out if click is outside the playing area
    if (!playArea.contains(mousePosition)) {
        std::cout << "Click was outside the game boundary" << std::endl;
        return;
    }

    // find board indices & count how many x's and o's there are in the board currently
    int gridX, gridY;
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

    // update the state
    updateState(numOfTurnsPassed, gameBoard[gridX][gridY].state);

    // check for win
}

/// <summary>
/// Creates the visual board (the background lines)
/// </summary>
/// <param name="displayBoard">An array of size 4 that will contain the rectangles that make up the board</param>
/// <param name="length">The length of the lines</param>
/// <param name="thickness">The width of the lines</param>
void initializeBoard(sf::RectangleShape displayBoard[], float length, float thickness) {
    // make the board
    displayBoard[0] = sf::RectangleShape{sf::Vector2f(length, thickness)};
    displayBoard[1] = sf::RectangleShape{sf::Vector2f(length, thickness)};
    displayBoard[2] = sf::RectangleShape{sf::Vector2f(thickness, length)};
    displayBoard[3] = sf::RectangleShape{sf::Vector2f(thickness, length)};

    // set universal properties like colour 
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape rect = displayBoard[i];
        rect.setFillColor(sf::Color::White);
    }

    // position the board lines
    // they are at 1/3 and 2/3 vertically and horizontally + the margins + the thickness of the line
    // horizontal
    displayBoard[0].setPosition(windowMargin, windowWidth / 3.f);       // 1/3
    displayBoard[1].setPosition(windowMargin, 2 * windowWidth / 3.f);   // 2/3
    // vertical
    displayBoard[2].setPosition(windowWidth / 3.f - 0.5f * lineThickness, windowMargin);       // 1/3
    displayBoard[3].setPosition(2 * windowWidth / 3.f - 0.5f * lineThickness, windowMargin);   // 2/3
    
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

        // this is the drawing part
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

                switch (state) {
                    case X:
                        x.setPosition(cell.bounds.getPosition());
                        window.draw(x);
                        //std::cout << "Drawing X at (" << x.getPosition().x << ", " << x.getPosition().y << ")" << std::endl;
                        break;
                    case O:
                        o.setPosition(cell.bounds.getPosition());
                        window.draw(o);
                        // std::cout << "Drawing O at (" << i << ", " << j << ")" << std::endl;
                        break;
                }
            }
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

    // populate with empty states
    float boundSideLength = playArea.height / 3.f;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j].state = State::Empty;
            gameBoard[i][j].bounds = sf::FloatRect{ windowMargin + i * boundSideLength, windowMargin + j * boundSideLength, boundSideLength, boundSideLength };
        }
    }

    /** It may be better to use a glyph of X and O as a picture here to be able to size it directly using Cell bounds.
     * But since font sizes are measured in pixels and I know the size of my window in pixels this works just great */
    // load fonts
    
    // make text
    sf::Font font;
    font.loadFromFile(fontFile);

    sf::Text x;
    x.setFont(font);
    x.setString("X");
    x.setCharacterSize(playArea.height / 3.f);
    x.setFillColor(sf::Color::White);
    x.setStyle(sf::Text::Bold);
    x.setPosition(0, 0);
    sf::Text o;
    o.setFont(font);
    o.setString("O");
    o.setCharacterSize(playArea.height / 3.f);
    o.setFillColor(sf::Color::White);
    o.setStyle(sf::Text::Bold);
    o.setPosition(0, 0);
    

    // enter game loop
    gameUpdate(window, displayBoard, gameBoard, x, o);

    return 0;
}