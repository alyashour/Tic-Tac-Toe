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

/// <summary>
/// This is an event handler for left mouse clicks
/// </summary>
/// <param name="event">The event object. It contains the click type and click position</param>
/// <param name="gameBoard">The board that contains the current game state</param>
void handleLeftMouseClick(sf::Event::MouseButtonEvent event, Cell gameBoard[3][3]) {
    // find board indices & count how many x's and o's there are in the board currently
    int gridX = -1, gridY = -1;
    int numOfEmptys = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            // find mouse index
            if (gameBoard[i][j].bounds.contains(event.x, event.y)) gridX = i, gridY = j;

            // count number of emptys
            if (gameBoard[i][j].state == State::Empty) numOfEmptys++;
        }
    int numOfTurnsPassed = 9 - numOfEmptys;

    // break out if click is outside the playing area
    if (gridX == -1 || gridY == -1) {
        std::cout << "Click was outside the game boundary" << std::endl;
        return;
    }

    // as of this point we have the mouse location and number of turns played
    std::cout << "Mouse clicked on (" << gridX << ", " << gridY << ")" << std::endl;

    // calculate who's turn it is
    // x always goes first so if the total number of turns passed is even, its Xs turn, otherwise O
    // and if the number of turns passed is 9 the game is over!
    if (numOfTurnsPassed >= 9) std::cout << "The game is over!" << std::endl;
    else if (numOfTurnsPassed % 2 == 0) {
        // it was Xs turn so place an X
        gameBoard[gridX][gridY].state = State::X;
        std::cout << "It is X's Turn" << std::endl;
    }
    else {
        gameBoard[gridX][gridY].state = State::O;
        std::cout << "It is O's Turn" << std::endl;
    }
}

/// <summary>
/// Creates the visual board (the background lines)
/// </summary>
/// <param name="margin">The boundaries around the edge of the window. This is symmetrical (top/bottom and left/right)</param>
/// <param name="length">The length of the lines</param>
/// <param name="width">The width of the lines</param>
/// <returns>An array containing 4 rectangles that make up the game board</returns>
void initializeBoard(sf::RectangleShape displayBoard[], float margin, float length, float width) {
    // make the board
    displayBoard[0] = sf::RectangleShape{sf::Vector2f(length, width)};
    displayBoard[1] = sf::RectangleShape{sf::Vector2f(length, width)};
    displayBoard[2] = sf::RectangleShape{sf::Vector2f(width, length)};
    displayBoard[3] = sf::RectangleShape{sf::Vector2f(width, length)};

    // set universal properties like colour 
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape rect = displayBoard[i];
        rect.setFillColor(sf::Color::White);
    }

    // position the board lines
    displayBoard[0].setPosition(800 / 3.f, margin);
    displayBoard[1].setPosition(2 * 800 / 3.f, margin);
    displayBoard[2].setPosition(margin, 800 / 3.f);
    displayBoard[3].setPosition(margin, 2 * 800 / 3.f);
}

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

void gameUpdate(sf::RenderWindow& window, sf::RectangleShape displayBoard[], Cell gameBoard[3][3]) {
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

        // draw an X
        

        window.display();
    }
}

int main()
{
    // initialize window
    float windowLen = 800;
    sf::RenderWindow window(sf::VideoMode(windowLen, windowLen), "Tic Tac Toe!", sf::Style::Titlebar | sf::Style::Close);
    float margin = 50;
    float boardWidth = 700.f, boardLength = 20.f;

    // make the board
    sf::RectangleShape displayBoard[4];
    initializeBoard(displayBoard, margin, boardLength, boardWidth);

    // make the gameboard
    Cell gameBoard[3][3];

    // populate with empty states
    float boundSideLength = 700.f / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j].state = State::Empty;
            gameBoard[i][j].bounds = sf::FloatRect{ margin + i * boundSideLength, margin + j * boundSideLength, boundSideLength, boundSideLength };
        }
    }

    // load fonts
    sf::Font font;
    font.loadFromFile("EnvyCodeRNerdFontMono-Regular.ttf");

    // enter game loop
    gameUpdate(window, displayBoard, gameBoard);

    return 0;
}