# Tic Tac Toe
## Objectives
For this project I wanted to do something simple so that the main focus was setting up my environment instead of the code, design, or logic.
I also wanted to set a precedent on how to organize future projects including proper documentation and comments, etc.
This is *getting my feet wet*. The code should be simple, quick, and clean with no if ands or buts. The docs should give an idea as to how I should write my future docs for larger projects.

## Design
### Prelim.
I wanted to make a game with few difficulties and Tic Tac Toe proved as good as any for this. The choice of game really didn't matter here so long as it had some game elements and a UI.
For choice of language I'm interested in a few right now namely:
- Java (with which I am most comfortable through ES1036, SE2205, and SE2203), 
- Rust (I have only heard good things but have never used before), 
- JS (extremely popular and I've taken a course in SE2202), 
- C# (which I had used before and am learning right now in SE2250) 
- or C++. This one seemed the most interesting to me. It was the first language I learned deeply (in highschool) but have since sort of forgotten. It is also extremely popular in Game Dev., graphics, embedded, which all sound super interesting to me.

Regarding C++ tools I could use, it came down to SFML and SDL. At some point I wanted to work in NeoVim with OpenGl and no libraries whatsoever like jdh on youtube but frankly finding docs on how to install OpenGL correctly made me want to kms so that was off the table (for now ;)).
Between SFML and SDL I've heard it doesn't really matter which you choose for the first time as the effort you put into one will partially carry over into the other so I left it up to one google search and found this Reddit post (https://www.reddit.com/r/gamedev/comments/fk8c1q/sfml_vs_sdl_in_2020/) which recommends SFML.
Lastly, the original plan (like I said before) was NV but the trouble I went through to *try* to install OpenGL made me reconsider kms and instead I went with VScode (which also didn't work) and then CLion (which also also took more work than it was worth) so I caved and went with the path of least resistance... VS 2022.

Although this summary makes it seem like I tried and failed for hours, all of this really was over the course of 7 minutes. I wanted to get my feet wet NOT spend hours grinding to get HelloWorld.
### The Code
There are few things to say about the code, the project simply wasn't that complicated. But some things of note:

I extracted the game loop and event loop into seperate functions for readibility but found that I had to pass in like 5 params to keep variables in scope. By moving some definitions I reduced that number slightly but next time I think its best to keep the loops outside of the functions and simple append things that need to be run inside of the loops as functions NOT the entire thing. I.e,
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
### Docs
I love almost everything there is to do with being a software engineering student but the one thing I do miss from being just an **engineering** student and (if I dare go back even further) a physics student, is looking over a clean lab outline.
Theres nothing quite like beautiful headers on a blank page, and writing this has only made that clearer for me. God, just look at the headers on this document!
Oh man I was just salivating thinking of what I was gonna write down... "Prelim."!? I feel like that critic from Ratatoullie at the end. Writing "Outcomes" on my keyboard has delightfully flashed me back to ES1050.

For future reference, project documentation should be elegant and flexible. If I had more time I would write a manifesto on why strict headers are the worst thing since the plague, but since I will probably only ever read this once I will keep it short.
1. Keep abstract sections like "Objectives" and "Outcomes". Feel free to add more if needed to highlight parts of the project. The top-level heading in the main ReadMe.md should always be the name of the project, see 5. for other files.
2. Subheadings should be specific to every project. Very rarely are two projects the same enough to warrant identical subheadings and even if they are, documentation (especially for me student and for these README's) should focus on what's differenet, new, unique not the same, old, and mundane.
3. Docs are NOT a place to put specific notes on language or library features. This is a place for wider themes of the project. Think of project documentation as a method to describe the research and engineering NOT the learning and the programming, that should be saved for your ACTUAL notes. For example "make a variable with the word var" is NOT good but "identifying classes beforehand helped 
4. Write notes that are descriptive of what *happened* not what there is to learn of it, ESPECIALLY under some header that conveys that like "# Issues" or a specific concept like "# Inheritance". For Example:
	- "Writing semi-working code quickly and refactoring iteratively as I went helped to extract meaningful data structures and classes and avoid unnecessary *objectification* when it wasn't needed" is GOOD writing. Especially If you include the specific parts of the software that gave you those insights to help remember.
	- But "Try to write quickly and spot classes as you go." is NOT good writing. Notice how much information was lost between the two sentences. Really, it is NOT always good to write quickly. Write what happened, not why you think it happened.
	- This does not mean to not aim to distill anything from the project. Notice I DID describe a positive effect of my choice in the first one, the issue is I didn't explain in the second one. I didn't describe what *happened*.
5. For larger projects, carve up the documentation under multiple md files with top-level headings that describe what they contain. These should (ideally) be located in the directory that contains that part of the code but if not possible, they should be in a special directory called "Docs" in the main project directory.
6. Sign the bottom with your name and the date (I know git keeps track of this but having to look somewhere else takes away from the copy-paste-ability of the document.

### Format
All docs or project writing otherwise should be in plain markdown.
Write dates as either [Month (short form)] [Day (number)], [4-digit year] (preferably) or DD/MM/YYYY if needed. MM/DD/YYYY is extremely illegal and MM/DD/YY is punishable by death.

## Outcomes
Now for the icky sticky.

The absolute most difficult part of this project (as I expected) was setting it up. Once I was in, it was no problem. The biggest headache was importing files like fonts and images into Visual Studio (which I still don't really get).
I refreshed a TON of my C++ knowledge and learned the basics of SFML.
## Sources
This page was heaven-send https://www.sfml-dev.org/tutorials/2.6/. 
Directly from my notes: "If every guide could be made like this the world would be a better place." It is concise, focuses on what's needed and answers my questions exactly when I have them. 10/10.


Aly Ashour. Feb 24, 2023.