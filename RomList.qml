import QtQuick 2.0

ListModel {
    id: romList
    ListElement {
        text: "CHIP8 PICTURE"
        path: ":roms/Chip8 Picture.ch8"
        description: "Chip8 test program"
    }
    ListElement {
        text: "15 PUZZLE"
        path: ":roms/15 Puzzle.ch8"
        description: "15 Puzzle by Roger Ivie<br/><br/>Rearrange the tiles into the sequence 0-F. Moves tile by it associated key."
    }
    ListElement {
        text: "ADDITION PROBLEMS"
        path: ":roms/Addition Problems.ch8"
        description: "Addition Problems by Paul C. Moews<br/><br/>Do simple math."
    }
    ListElement {
        text: "AIRPLANE"
        path: ":roms/Airplane.ch8"
        description: "Airplane - Blitz type of bombing game. Hit \"8\" to drop a bomb."
    }
    ListElement {
        text: "ANIMAL RACE"
        path: ":roms/Animal Race.ch8"
        description: "Animal Race by Brian Astle<br/><br/>Animal Race is a fun game for one person with an element of luck - sure to put a smile on your face.  Five different animals race against one another and you have the chance to test your expertise at picking the winner."
    }
    ListElement {
        text: "ASTRO DODGE"
        path: ":roms/Astro Dodge.ch8"
        description: "Astro Dodge (2008) by Revival Studios<br/><br/>Your goal is to make your way through the asteroids field and dodge the asteroids scoring points for each asteroid you are able to dodge. Button 2468 will move your ship button 5 will start the game."
    }
    ListElement {
        text: "BIORHYTHM"
        path: ":roms/Biorhythm.ch8"
        description: "Biorhythm by Jef Winsor<br/><br/>The theory of Biorhythm states that there are thre predominant cycles that can influence human behavior. These include a 23-day physical cycle a 28-day emotional cycle and a 33-day intellectual cycle.  All three cycles start at birth and continue throughout life.<br/><br/>Each cycle consists of a positive and a negative period.  Physical Emotional and Intellectual aspects are enhanced during positive periods.  Poor performance is indicated by the negative period of a cycle.<br/><br/>A critical day occurs on the crossover from the positive to the negative period or vice versa. A critical day indicates instability in a particular aspect. <br/><br/>How to Use Biorhythm: <br/><br/>1. Enter birthdate using 2-digit month 2-digit day and 4-digit year.<br/><br/>2. Enter start date using 2-digit month 2-digit day and 4-digit year. The start date indicates the first day of the 32-day Biorhythm chart the program will generate.<br/><br/>3. After a period of calculation proportional to the span of time involved the three cycle curves will be shown for a 32-day period. Each horizontal bit position represents one day in the cycle. The start day on the left and every seventh day are indicated by week markers. The first day of a positive or negative period is a critical day.<br/><br/>4. To advance the start date hold key F down until the desired date is reached. To decrement the start date hold key B down. These functions allow changing the start date slightly without reentering all the dates and waiting for the calculations to be preformed.<br/><br/>5. Press Key 0 to clear the screen and enter a new set of dates."
    }
    ListElement {
        text: "BLINKY"
        path: ":roms/Blinky.ch8"
        description: "Blinky (1991) by Hans Christian Egeberg<br/><br/>Pacman clone.<br/>3 6 - down/up. 7 8 - left/right"
    }
    ListElement {
        text: "BLITZ"
        path: ":roms/Blitz.ch8"
        description: "Blitz by David Winter<br/><br/>This game is a BOMBER clone. You are in a plane and you must destroy the towers of a town. Your plane is flying left to right and goes down. Use 5 to drop a bomb. The game ends when you crash yourself on a tower..."
    }
    ListElement {
        text: "BMP VIEWER"
        path: ":roms/BMP Viewer.ch8"
        description: "BMP Viewer (2005) by Hap<br/><br/>works with monochrome BMPs only of course. Put the BMP data (headerless) at offset $30. change offset $0 (200) $00ff to $1202 for Chip-8."
    }
    ListElement {
        text: "BOWLING"
        path: ":roms/Bowling.ch8"
        description: "Bowling by Gooitzen van der Wal<br/><br/>Bowling is a great game for recreation and competion requiring skill and a little bit of luck.  This program simulates bowling closely with regular scoring and the option of using three different spins on the ball."
    }
    ListElement {
        text: "BREAKOUT"
        path: ":roms/Breakout.ch8"
        description: "Breakout (Brix hack) 1997 by David Winter<br/><br/>This game is an \"arkanoid\" precursor. You have 5 lives and your goal is the destruction of all the brixs. Use 4 and 6 to move your paddle. The game ends when all the brixs are destroyed. This game is the same than BRIX but has graphics looking like the game on the Atari 2600 console."
    }
    ListElement {
        text: "BRICK"
        path: ":roms/Brick.ch8"
        description: "BRICK (Brix hack) 1990<br/><br/>A modified version of BRIX a CHIP-8 game. Original BRIX by Andreas Gustafsson. This one is a solid wall; no air between bricks! 4 6 - left/right"
    }
    ListElement {
        text: "BRIX"
        path: ":roms/Brix.ch8"
        description: "Brix (1999) by Andres Gustafsson<br/><br/>Arkanoid clone. 4 6 - left/right"
    }
    ListElement {
        text: "CAVE"
        path: ":roms/Cave.ch8"
        description: "Cave (199x)<br/><br/>Guide the dot to end of the cave maze without bumping into a wall. Navigation: 4 6 2 8."
    }
    ListElement {
        text: "CHIP8 EMULATOR LOGO"
        path: ":roms/Chip8 emulator Logo.ch8"
        description: "Chip8 test program"
    }
    ListElement {
        text: "CLOCK PROGRAM"
        path: ":roms/Clock Program.ch8"
        description: "Clock Program (1981) by Bill Fisher<br/><br/>This neat little clock program is the perfect program to run when someone asks: \"That's nice but what can your computer DO?\" The program features \"reverse\" video numerals on the screen which is a nice change from the usual white numbers on a black background. Instructions:<br/>- Type six digits on the hex keypad for the desired clock starting time using 23 hour format (ex.173055)<br/>- Hit any hex key to start clock running at the above time setting."
    }
    ListElement {
        text: "COIN FLIPPING"
        path: ":roms/Coin Flipping.ch8"
        description: "Coin Flipping (1978) by Carmelo Cortez<br/><br/>The game is a Coin FlLpping program. Flip run up and the computer starts to flip a coin and at the same tine shosing heads and tails on the screen stopping at the value set in VC."
    }
    ListElement {
        text: "CONNECT 4"
        path: ":roms/Connect 4.ch8"
        description: "Connect 4 by David Winter<br/><br/>This game is for two players. The goal is to align 4 coins in the game area. Each player's coins are colored. When you drop a coin it is paced on the latest dropped coin in the same column or at the bottom if the column is empty. Once the column is full you cannot place any more coins in it. To select a column use 4 and 6.<br/><br/>To drop a coin use 5. There is no winner detection yet. This will be soon avalaible (Hey! I don't spend my life on CHIP8 !)."
    }
    ListElement {
        text: "CRAPS"
        path: ":roms/Craps.ch8"
        description: "Craps (1978) by: Camerlo Cortez<br/><br/>To use the Craps program press any key to roll dice. 7 or 11 wins 12 2 or 3 loses on first roll. The second roll must match the first to win but if you roll a seven you lose. This program could be expanded to include on-the-screen scoring of bets."
    }
    ListElement {
        text: "DEFLECTION"
        path: ":roms/Deflection.ch8"
        description: "Deflection by John Fort<br/><br/>In the VIP Deflection game you position mirrors anywhere on the display screen. The object of the game is to deflect a ball of the mirrors a maximum number of times before hitting the target.<br/><br/>The number of deflections times the target number gives you deflection points. These are added to your previous point total. If you fail to hit the target you get no points. The winner of the game is the player who accumulates 257 or more deflected points.<br/><br/>To program the mirrors select the proper mirror type. Key 1 will place a horizontal mirror on the board. Key 2 selects a vertical mirror Key 3 a slant-left mirror Key 4 a slant-right mirror.<br/><br/>After a mirror has been selected you may position the mirror by using keys 1 through 4 and 6 through 9. Once a mirror has been selected and positioned it may be fixed into position by pressing Key 5.<br/><br/>You may position up to 10 mirrors on the game board. After you have the maximum amount on the board you must press Key 0 to progress to the fire mode. If you wish to progress to the fire mode with less than 10 mirrors programmed you may do so by pressing Key 0. You fire the ball in the direction you want by using Keys 1 through 4 and Keys 6 through 9."
    }
    ListElement {
        text: "DELAY TIMER TEST"
        path: ":roms/Delay Timer Test.ch8"
        description: "Delay Timer Test (2010) by Matthew Mikolay<br/><br/>Here's another little program I wrote to test out a feature in my game. This program allows the user to change the value of the V3 register using the 2 and 8 keys. When the 5 key is pressed the delay timer starts counting down from the value the user placed into the V3 register and the screen is updated as the value changes."
    }
    ListElement {
        text: "DIVISION TEST"
        path: ":roms/Division Test.ch8"
        description: "Division Test (2010) by Sergey Naydenov"
    }
    ListElement {
        text: "FIGURES"
        path: ":roms/Figures.ch8"
        description: "Figures<br/><br/>Tetris like game with numbers."
    }
    ListElement {
        text: "FILTER"
        path: ":roms/Filter.ch8"
        description: "Filter<br/><br/>Catch the drop coming from the pipe at the top of the screen with your paddle."
    }
    ListElement {
        text: "FISHIE"
        path: ":roms/Fishie.ch8"
        description: "Fishie (2005) by Hap<br/><br/>used as internal rom for fish n chips"
    }
    ListElement {
        text: "FRAMED MK1"
        path: ":roms/Framed MK1.ch8"
        description: "Framed Mk1 (1980) by G.V. Samways<br/><br/>This program displays a random movement of dots. You will notice a repetition in the pattern after a time."
    }
    ListElement {
        text: "FRAMED MK2"
        path: ":roms/Framed MK2.ch8"
        description: "Framed Mk2 (1980) by G.V. Samways<br/><br/>This program displays a random movement of dots. You will notice a repetition in the pattern after a time."
    }
    ListElement {
        text: "GUESS"
        path: ":roms/Guess.ch8"
        description: "Guess by David Winter<br/><br/>Think to a number between 1 and 63. CHIP8 shows you several boards and you have to tell if you see your number in them. Press 5 if so or another key if not. CHIP8 gives you the number..."
    }
    ListElement {
        text: "HIDDEN"
        path: ":roms/Hidden.ch8"
        description: "Hidden (1996) by David Winter<br/><br/>HIDDEN is a \"memory\" game. It is very simple to play. The rules are as follow: your goal is to find all the identical cards in a minimum time. You are playing in a 4*4 card grid. You can see only two cards at the same time. Once this time passed these two cards will remain shown if they are identical otherwise they will be hidden again. When the game is finished two scores are shown: SC is your score corresponding to the number of tries HI is the best score (smallest number of tries made to finish) The keys are: [8] - Move DOWN [4] - Move LEFT [5] - Show card [6] -  Move RIGHT [2] - Move UP"
    }
    ListElement {
        text: "IBM LOGO"
        path: ":roms/IBM Logo.ch8"
        description: "IBM logo"
    }
    ListElement {
        text: "JUMPING X AND O"
        path: ":roms/Jumping X and O.ch8"
        description: "Jumping X and O (1997) by Harry Kleinberg<br/><br/>Here is what the program is written to do. First a solid 6×6spot block appears in the upper right quadrant of the tv display. A 5×5 \"X\" pattern appears in the center and jumps randomly to a new location every 1/5 second. When the X overlaps the 6×6 block the X disappears an \"0\" pattern appears in the center of the screen and repeats the process being replaced by the X when an overlap with the block occurs. The program continues until the machine IS stopped"
    }
    ListElement {
        text: "KALEIDOSCOPE"
        path: ":roms/Kaleidoscope.ch8"
        description: "Kaleidoscope (1978) by Joseph Weisbecker<br/><br/>Four spots appear in a group at the center of the screen. Press keys 2 4  6 or 8 to create a pattern. Keep your pattern smaller than 138 key depressions. Push key 0 to terminate pattern entry. Pushing key 0 causes your pattern to be continuously repeated forming a fascinating changing kaleidoscope display on the screen. A \"44444442220\" key sequence provides a very nice effect Experiment to find other nice patterns."
    }
    ListElement {
        text: "KEYPAD TEST"
        path: ":roms/Keypad Test.ch8"
        description: "Keypad Test (2006) by Hap<br/><br/>press a chip8 key and the pressed char will light up if you want to do something funny soft-reset the chip8/emulator over and over and the sprite layout will become messed up ;p"
    }
    ListElement {
        text: "LANDING"
        path: ":roms/Landing.ch8"
        description: "Landing<br/><br/>Blitz type game."
    }
    ListElement {
        text: "LIFE"
        path: ":roms/Life.ch8"
        description: "Life (1980) by G.V. Samways<br/><br/>This is a display of cell growth in accordance with the following rules:<br/>1. A cell is born if 3 cells are adjecent to an empty space.<br/>2. A cell lives if 2 or 3 cells are adjacent and dies otherwise.<br/>3. All events take place simultaneously.<br/>To start the game you make a pattern by entering the cell coordinates first the \"Y\" from 0-7 downwards then the \"X\" from 0-F across. F initialises the program and the number of scans is entered plus one so that 1 gives 0 scans to F giving 14 and 0 giving 255. The sit back and watch the colony live or die."
    }
    ListElement {
        text: "LUNAR LANDER"
        path: ":roms/Lunar Lander.ch8"
        description: "Lunar Lander (1979) by Udo Pernisz<br/><br/>You are descending to the floor of a 250-foot crater. The right side of the TV display shows amount of fuel feet from bottom and fall rate per cycle. Lenght of fall rate cycle changes from about 1/4 second to one second.  The fall rate increases by one foot per second/per cycle. The computer will update the display only at the end of each cycle.<br/><br/>The left side of the display shows the Lunar Lander descending from 250 feet. The Lander will first appear at one of sixteen locations. It will then slowly drop down the crater. The crater walls have rock formations protruding from them which must be avoided.  If either rocket motor should touch any part of the crater the Lander will explode in a cloud of smoke and disintegrate. (Remember these are atomic thrusters and react like miniature atomic bombs upon impact).<br/><br/>When you reach 32 feet the display will change and you will see the crater floor. You must now land between the rock formations on the floo and maintain a minimum fall rate.  As you drop your fall rate to zero you soon discover that the Lander becomes more and more unstable just as any hovering object would. And now with perfect skill you guide the ship in for a perfect touch down or?"
    }
    ListElement {
        text: "MASTERMIND"
        path: ":roms/Mastermind FourRow.ch8"
        description: "Mastermind FourRow (1978) by Robert Lindley<br/><br/>The game starts by displaying a series of dashes arranged in rows. As the game progresses the player attempts to  deduce the hidden code by replacing the dashes with digits entered via the hex keyboard. Each tlme a hex key is used the selected digit replaces a dash in  one vertical column. This vertical column is one guess of the ten allowed to deduce the hidden number. When the bottom dash in any column is replaced by a digit  that try is imidiately scored. This score appears below the current column. If any digit in the column exactly matches the hidden number digit in the same row a broken bar will appear. then four or five (one for each row in the game) appear the hidden number has been deduced and it will be revealed at the right end of  the screen. If any digit in the column matches a hidden digit but in an incorrect erorr a white bar will appear. Note that the scoring is across all rows. For example if there are two fives in a column and one of then is in the correct row and there is only one five in the hidden numbers one broken bar will appear. When all allowed ten tries  have been used the hidden number will be revealed. "
    }
    ListElement {
        text: "MAZE DEMO"
        path: ":roms/Maze.ch8"
        description: "Maze (199x) by David Winter<br/><br/>Drawing a random maze like this one consists in drawing random diagonal lines. There are two possibilities: right-to-left line and left-to-right line. Each line is composed of a 4*4 bitmap. As the lines must form non-circular angles the two bitmaps won't be \"/\" and \"\\\". The first one (right line) will be a little bit modified. See at the end of this source.<br/><br/>The maze is composed of 16 lines (as the bitmaps are 4 pixels high) each line consists of 32 bitmaps. Bitmaps are drawn in random mode. We choose a random value (0 or 1). If it is 1 we draw a left line bitmap. If it is 0 we draw a right one."
    }
    ListElement {
        text: "MERLIN"
        path: ":roms/Merlin.ch8"
        description: "Merlin by David Winter<br/><br/>This is the SIMON game. The goal is to remember in which order the squares are lighted. The game begins by lighting 4 random squares and then asks you to light the squares in the correct order. You win a level when you give the exact order and each increasing level shows a additionnal square. The game ends when you light an incorrect square. Keys are 4 and 5 for the two upper squares then 7 and 8 for the two other ones."
    }
    ListElement {
        text: "MINIMAL GAME"
        path: ":roms/Minimal game.ch8"
        description: "Minimal Game (2007) by Revival Studios"
    }
    ListElement {
        text: "MISSILE"
        path: ":roms/Missile.ch8"
        description: "Missile by David Winter<br/><br/>Shoot the targets with the moving gun."
    }
    ListElement {
        text: "MOST DANGEROUS GAME"
        path: ":roms/Most Dangerous Game.ch8"
        description: "Most Dangerous Game by Peter Maruhnic<br/><br/>Most Dangerous Game pits a hunter against a hunted in a maze.  The hunter must shoot the hunted before either time runs out or the hunted escapes the maze. However neither the hunted nor the hunter can see a wall in the maze until he runs into it.  There is always at least one path through the maze."
    }
    ListElement {
        text: "NIM"
        path: ":roms/Nim.ch8"
        description: "Nim (1978) by Carmelo Cortez<br/><br/>The Nim Game is a little less graphic than most games. The player may go first by pressing. \"F\" key any other let the computer go first. You subtract 1 2 or 3 fron the score. The one who ends up with the  last number loses!"
    }
    ListElement {
        text: "PADDLES"
        path: ":roms/Paddles.ch8"
        description: "Paddles<br/><br/>Simple pong game."
    }
    ListElement {
        text: "PARTICLE DEMO"
        path: ":roms/Particle Demo.ch8"
        description: "Particle Demo (2008) by zeroZshadow<br/><br/>This is my particledemo for the Chip-8 SuperChip and MegaChip8. Works on real hardware as well as emulators. Enjoy!"
    }
    ListElement {
        text: "PONG"
        path: ":roms/Pong.ch8"
        description: "Pong (1990) by Paul Vervalin"
    }
    ListElement {
        text: "PONG 2"
        path: ":roms/Pong_2P.ch8"
        description: "Pong 2 (Pong hack 1997) by David Winter"
    }
    ListElement {
        text: "PONG (1 PLAYER)"
        path: ":roms/Pong_1P.ch8"
        description: "Single player pong game"
    }
    ListElement {
        text: "PUZZLE"
        path: ":roms/Puzzle.ch8"
        description: "4x4 tile puzzle - rearrange them into the order 0-F."
    }
    ListElement {
        text: "RANDOM NUMBER TEST"
        path: ":roms/Random Number Test.ch8"
        description: "Random Number Test (2010) by Matthew Mikolay<br/><br/>I don't know if any of you will be interested in this but I wrote this small program while coding my game to test out the random number generator. I wanted to see if there is a chance that zero will show up as the random number and it turns out it can. Anyway when you run the program it brings a random number up on the screen. When you press any of the keys it brings another random number up on the screen. This goes on until you quit the program. Address 0x202 holds the C0FF instruction which commands the CHIP-8 interpreter to set V0 to a random number with the mask 0xFF. This yields 256 different possible numbers (0-255). If C0FF is changed to something like C00A then the mask will change. This would yield 11 different possible numbers (0-10)."
    }
    ListElement {
        text: "REVERSI"
        path: ":roms/Reversi.ch8"
        description: "Reversi by Philip Baltzer<br/><br/>Reversi is a game over 100 years old which has become popular recently under the name Othello.  The game is played on a 8x8 square using two kinds of markers. In VIP Reversi one player has the open markers and the other player the solid markers. The score for either player at any time is the total number of his markers on the square."
    }
    ListElement {
        text: "ROCKET"
        path: ":roms/Rocket.ch8"
        description: "Rocket (1978) by Joseph Weisbecker<br/><br/>Launch your rocket and earn points."
    }
    ListElement {
        text: "ROCKET LAUNCHER"
        path: ":roms/Rocket Launcher.ch8"
        description: "Rocket Launcher game"
    }
    ListElement {
        text: "ROCKET LAUNCH"
        path: ":roms/Rocket Launch.ch8"
        description: "Another Rocket launcher game by Jonas Lindstedt."
    }
    ListElement {
        text: "RUSH HOUR"
        path: ":roms/Rush Hour.ch8"
        description: "Rush Hour (2006) by Hap<br/><br/>The goal of the game is to slide the arrow block(s) out of the 6*6 grid. Completing 10 boards will be awarded with the inclusion of the next boardset(s) as seen from the connections on the boardset select screen a password will be given so you don't have to complete the game in a single session."
    }
    ListElement {
        text: "RUSSIAN ROULETTE"
        path: ":roms/Russian Roulette.ch8"
        description: "Russian Roulette (1978) by Carmelo Cortez<br/><br/>This game is called Russian RouLette. Press any key to Spin and pull the Trigger. A \"Click\" or \"Bang\" will show get ten \"clicks\" in a row and you win."
    }
    ListElement {
        text: "SEQUENCE SHOOT"
        path: ":roms/Sequence Shoot.ch8"
        description: "Sequence Shoot by Joyce Weisbecker<br/><br/>You score points by having the sharp-shooter hit the targets in the proper sequence. Pressing the Key C causes the little man to shoot the top target Key D shoots the one below it Key E the next lower and Key F the bottom target."
    }
    ListElement {
        text: "SHOOTING STARS"
        path: ":roms/Shooting Stars.ch8"
        description: "Shooting Stars (1978) by Philip Baltzer"
    }
    ListElement {
        text: "SIERPINSKI"
        path: ":roms/Sierpinski.ch8"
        description: "Sierpinski Carpet Demo (2010) by Sergey Naydenov"
    }
    ListElement {
        text: "SLIDE"
        path: ":roms/Slide.ch8"
        description: "Slide by Joyce Weisbecker<br/><br/>Slide is a two-person game. Each player tries to slide a \"puck\" over the high-scoring \"spots\" without hitting the back wall. The puck moves up and down randomly. Press \"0\" key to stop the puck. The puck will move towards the spots after you release the key. The longer you hold the key down the further the puck travels (maximum time approximately 2.5 seconds)."
    }
    ListElement {
        text: "SOCCER"
        path: ":roms/Soccer.ch8"
        description: "Pong type of game"
    }
    ListElement {
        text: "SPACE FLIGHT"
        path: ":roms/Space Flight.ch8"
        description: "Space flight game<br/></br>Fly through the asteroid field. Use 1 and 4 key to navigate space ship and E/F to start the game."
    }
    ListElement {
        text: "SPACEFIGHTERS"
        path: ":roms/Programmable Spacefighters.ch8"
        description: "Programmable Spacefighters by Jef Winsor<br/><br/>Programmable Spacefighters is a combat game involving 2 to 8 spaceships competing for the domination of a contained field in space. The field of play is a two-dimensional representation of an oblong spheroid."
    }
    ListElement {
        text: "SPACE INTERCEPT"
        path: ":roms/Space Intercept.ch8"
        description: "Space Intercept (1978) by Joseph Weisbecker<br/><br/>At startup Press 1 to select the large UFO which counts 5 points when hit or 2 to select the small UFO which counts 15 points when hit. Launch your rocket by pressing key 45 or 6. You get 15 rockets as shown in the lower right corner of the screen. Your score is shown in the lower left corner of the screen."
    }
    ListElement {
        text: "SPACE INVADERS"
        path: ":roms/Space Invaders.ch8"
        description: "Space Invaders (1978) by David Winter<br/><br/>The well known game. Destroy the invaders with your ship. Shoot with 5 move with 4 and 6. Press 5 to begin a game."
    }
    ListElement {
        text: "SPOOKY SPOT"
        path: ":roms/Spooky Spot.ch8"
        description: "Spooky Spot (1978) by Joseph Weisbecker<br/><br/>Now you can let the computer make your big decisions or predict the future just like governmentt or industry leaders do. You will see the words YES and NO at the right of the screen. Ask the computer any question that can be answered with YES or NO. Press KEY 0 and the spooky spot will show you the computer's answer. This program replaces your old fashioned mechanical OUIJA board."
    }
    ListElement {
        text: "SQRT TEST PROGRAM"
        path: ":roms/SQRT Test.ch8"
        description: "SQRT Test Program (2010) by Sergey Naydenov"
    }
    ListElement {
        text: "SQUASH"
        path: ":roms/Squash.ch8"
        description: "Squash by David Winter<br/><br/>Bounce a ball around a squash court with your paddle"
    }
    ListElement {
        text: "STARS DEMO"
        path: ":roms/Stars.ch8"
        description: "Stars Demo (2010) by Sergey Naydenov"
    }
    ListElement {
        text: "SUBMARINE"
        path: ":roms/Submarine.ch8"
        description: "Submarine (1978) by Carmelo Cortez<br/><br/>The Sub Game is my favorite. Press \"5\" key to fire depth charges at the subs below. You score 15 points for a small sub and 5 points for the larger. You get 25 depth charges to start."
    }
    ListElement {
        text: "SUM FUN"
        path: ":roms/Sum Fun.ch8"
        description: "Sum Fun by Joyce Weisbecker<br/><br/>The object of this game is to add up the three digits which appear in the middle of the screen and then hit the key representing the total as fast as you can."
    }
    ListElement {
        text: "SUPERWORM V4"
        path: ":roms/Worm V4.ch8"
        description: "SuperWorm V4 (2007) by Revival Studios<br/><br/>SuperWorm V4 is an update of the SuperChip8 game: Worm3 by RB. The original game was only for SuperChip so i've created a Chip-8 port. It also includes several speed fixes and a new control system."
    }
    ListElement {
        text: "SYZYGY"
        path: ":roms/Syzygy.ch8"
        description: "Syzygy (1990) by Roy Trevino<br/><br/>The object of the game is to seek out \"targets\". You do this with your syzygy. Initially small the syzygy will grow by some amount each time a target is hit. Eventually your syzygy will be so long as to make tougher and tougher to get any points (and easier and easier to get killed). Confused? Just try it. To play: 3 - up 6 - down 7 - left 8 - right"
    }
    ListElement {
        text: "TANK"
        path: ":roms/Tank.ch8"
        description: "You are in a tank which has 25 bombs. Your goal is to hit 25 times a mobile target. The game ends when all your bombs are shot. If your tank hits the target you lose 5 bombs. Use 2 4 6 and 8 to move. This game uses the original CHIP8 keyboard so directions 2 and 8 are swapped."
    }
    ListElement {
        text: "TAPEWORM"
        path: ":roms/Tapeworm.ch8"
        description: "Tapeworm (1999)<br/><br/>Tron clone; guide the snake around and around."
    }
    ListElement {
        text: "TETRIS"
        path: ":roms/Tetris.ch8"
        description: "Tetris (1991) by Fran Dachille"
    }
    ListElement {
        text: "TIC-TAC-TOE"
        path: ":roms/Tic-Tac-Toe.ch8"
        description: "Tic-Tac-Toe by David Winter<br/><br/>2-player noughts and crosses board."
    }
    ListElement {
        text: "TIMEBOMB"
        path: ":roms/Timebomb.ch8"
        description: "Reset the bomb."
    }
    ListElement {
        text: "TRIP8 DEMO"
        path: ":roms/Trip8 Demo.ch8"
        description: "Trip8 Demo (2008) by Revival Studios<br/><br/>The Trip8/SuperTrip8 demo are demo's for the Chip-8 and SuperChip8 systems. The demo consists of an intro 3D vectorballs and 4 randomized dot-effects.<br/><br/>Writing a demo for the original Chip-8 interpreter was a real pain since your framerate basically drops in half for every sprite you need to draw. So even clearing and redrawing a few dots will cause the framerate to drop to near zero :) Originally the demo was going to be bigger and there were much more graphical effects programmed/prototyped but a lot of these effects turned out to be too much for the original unoptimized Chip-8 interpreters to handle."
    }
    ListElement {
        text: "TRON"
        path: ":roms/Tron.ch8"
        description: "Tron"
    }
    ListElement {
        text: "UFO"
        path: ":roms/UFO.ch8"
        description: "UFO (1992)<br/><br/>You have a stationary missle launcher at the bottom of the screen. You can shoot in three directions; left diagonal straight up and right diagonal.. using the keys 4 5 and 6 respectively... You try to hit one of two objects flying by... at apparently varying speeds... Your score is displayed on your left the number of missles you have left is displayed on your right."
    }
    ListElement {
        text: "VERS"
        path: ":roms/Vers.ch8"
        description: "Vers (1991) by JMN<br/><br/>Two-player Tron game."
    }
    ListElement {
        text: "VERTICAL BRIX"
        path: ":roms/Vertical Brix.ch8"
        description: "Vertical Brix (1996) by Paul Robson<br/><br/>Vertical breakout type of game."
    }
    ListElement {
        text: "WALL"
        path: ":roms/Wall.ch8"
        description: "Wall by David Winter<br/><br/>Squash type game."
    }
    ListElement {
        text: "WIPE OFF"
        path: ":roms/Wipe Off.ch8"
        description: "Wipe Off by Joseph Weisbecker<br/><br/>Another Breakout variant. Your score is displayed when the game is over."
    }
    ListElement {
        text: "X-MIRROR"
        path: ":roms/X-Mirror.ch8"
        description: "Kaleidoscope type game."
    }
    ListElement {
        text: "ZERO"
        path: ":roms/Zero Demo.ch8"
        description: "Zero Demo (2007) by zeroZshadow<br/><br/>simple demo with 4 bouncing sprites. Enjoy!"
    }
    ListElement {
        text: "ZERO PONG"
        path: ":roms/ZeroPong.ch8"
        description: "Zero Pong (2007) by zeroZshadow<br/><br/>Another pong game"
    }
}
