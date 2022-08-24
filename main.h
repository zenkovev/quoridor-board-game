//Constants of game parameteres

/* Recommended values:

static const int NumberOfPlayers = 2;
static const int FieldSizesForFigure = 9;
static const int NumberOfWalls = 10;
static const int SquarePixelSizes = 80;

*/

//If you want to change this parameters
//You must changes numeric values below

static int NumberOfPlayers = 2;
//Number of players
//Correct values: 2 or 4

static int FieldSizesForFigure = 9;
//Sizes of game table which can be occupied figures
//Correct values: odd number >= 3
//Big vlaues can be bad because field can not fit in screen

static int NumberOfWalls = 10;
//Maximum number of walls which one player can install
//Correct values: All numbers > 0

static int SquarePixelSizes = 80;
//Size of square which contains figure
//If you have problems as field can not fit in screen
//You should change this value
//Graphic library contains limit below on this value
//Than some sizes can be different to installed
//Correct values: 50, 60, 70, 80, 90, 100
