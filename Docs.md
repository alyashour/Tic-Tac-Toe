# Tic Tac Toe
## Overview
**Objectives**: I intended to make a game with few complexities so the choice of game really didn't matter here so long as it had *some* game elements and a UI. Really the point is to 1) gain experience implementing game logic in code, 2) become more comfortable in a language I need to improve on, and 3) setup libraries for future projects.

**Languages**: I'm interested in a few right now namely:
- Java (with which I am most comfortable),
- Rust (I have only heard good things but have never used before),
- JS (extremely popular and I've taken a course in),
- C# (which I had used before and am learning right now),
- and C++. 

That last one seemed the most interesting to me. It was the first language I learned deeply (in highschool) but have since forgotten. It is also extremely popular in Game Dev., graphics, embedded, which all sound super interesting to me.

**Tools, Libraries, & Other Resources**: the most popular C++ graphics libraries are SFML and SDL. They are (as far as a quick google search showed me) both equally good enough for a small game but the quality of the resources on the SFML page pushed me to start with that.

## Formatting Future Documents
I love almost everything there is to do with being a software engineering student but the one thing I do miss from being just an **engineering** student and (if I dare go back even further) a physics student, is looking over a clean lab outline.
Theres nothing quite like beautiful headers on a blank page, and writing this has only made that clearer for me.

For future reference, project documentation should be elegant and flexible. 
If I had more time I would write a manifesto on why strict headers are the worst thing since the plague, but since I will probably only ever read this once I will keep it short.

1. The README MUST contain:
    - a brief summary of the project. Include info like the language(s), tools, and libraries used,
    - at minimum 1 link to a docs page (default is Docs.md),
    - and screenshots/videos of the project working.
    - See [README.md](https://github.com/alyashour/Tic-Tac-Toe/blob/dc03ec2eb738fdbd713903acd8ca34bbe8582128/README.md) for an example
2. Keep a more detailed log in a seperate file called Docs with the project name as its top-level heading. Headings are specific to each project but a few should be consistent across all docs:
    - "Overview" gives an introduction into the project. Think of this as an area to describe the information in the ReadMe in more detail.
    - "Outcomes" or alternative.
    - "Sources", "References", "Resources", or alternative.
    - End the document with a top-level heading called End
    - Then sign the document after every major edit. [Name], [Date].

### Other Formatting
All docs or project writing otherwise should be in plain markdown.

Write dates as either [Month (short form)] [Day (number)], [4-digit year] (preferably) or DD/MM/YYYY if needed. MM/DD/YYYY is extremely illegal and MM/DD/YY is punishable by death.

## The Code
I extracted the game loop and event loop into seperate functions for readibility but found that I had to pass in like 5 params to keep variables in scope. By moving some variables into global positions at the top of the file I was able to reorganize into a format that I think is pretty clean and legible BUT this is not always possible (like in java for example) nor is it best practice (probably idk). In the future this could be totally navigated by writing purer functions and moving the gameLoop and eventLoop functions inside their respective loops instead of including them.
```C++
int main() {
	/* initializations go here */
	// make the window
	// maybe some variables

	/* the game loop starts here */
	while (window.isOpen()){
		// pre-event stuff goes here (if applicable)
		fooListener();

		/ * the event loop starts here */
		sf::Event event;
		while (window.pollEvent(event)){
			// add event listeners here
			mouseLeftClickListener(x, y, z);
			moveListener();
		}

		// drawing the screen goes here
		draw(a, b, c);
	}

	return 0;
}
```

Lastly, this was my first time writing doxygen comments and I was shocked to find out that they are different across different IDE's?! In vscode they follow this format:
```cpp
/// @brief Lorem Ipsum
/// @param dolor sit amet, consectetur adipiscing elit.
/// @param Fusce in quam cursus, suscipit arcu ut, blandit turpis
```
While Visual Studio (2022) follows this format:
```cpp
/// <summary>
/// Donec in bibendum sem. 
/// </summary>
/// <param name="Fusce"> eget sollicitudin sem.
```

I have kept both in the code for reference.
### Building and Running
Setup on Windows was relatively easy and I had no problems following the instructions on the SFML page.

On MacOS Sonoma however, I got it working properly by:
1. Installing using brew.
2. Compiling using
```bash
g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o game -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
```
3. Running the app from the terminal (because if you run by double-clicking the working directory becomes the home directory which makes the font inaccessible).

## Sources
This page was heaven-send https://www.sfml-dev.org/tutorials/2.6/.
Directly from my notes: "If every guide could be made like this the world would be a better place." It is concise, focuses on what's needed and answers my questions exactly when I have them. 10/10.

# End
Aly Ashour. Feb 24, 2023.
Aly Ashour. Feb 26, 2023.