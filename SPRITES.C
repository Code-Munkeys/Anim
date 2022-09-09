/*	SPRITES.C

	Developed by Franz Ayestaran 1992 - https://github.com/Code-Munkeys/Anim

	Example source code for loading, saving and displaying a set of nine 50x50 pixel 16 colour sprites (45KB in size).
  
  	You may use this code in your own projects and upon doing so, you the programmer are solely
  	responsible for determining it's worthiness for any given application or task. Here clearly
  	states that the code is for learning purposes only and is not guaranteed to conform to any
  	programming style, standard, or be an adequate answer for any given problem.
*/

#include <stdio.h>
#include <graphics.h>

#define WRITE "w"
#define READ  "r"

int    GraphDriver;		/* The Graphics device driver */
int    GraphMode;	  	/* The Graphics mode value */
double AspectRatio;       	/* Aspect ratio of a pixel on the screen */
int    MaxX, MaxY;		/* The maximum resolution of the screen */
int    MaxColors;	  	/* The maximum # of colors available */
int    ErrorCode;	        /* Reports any graphics errors */
struct palettetype palette;	/* Used to read palette info */

int Anim[9*50*50];

int index, index_x, index_y, row, column, Data, read_file, write_file;

/*####################################################*/

void Initialize(void)
{
	int xasp, yasp;	/* Used to read the aspect ratio*/
	GraphDriver = DETECT; /* Request auto-detection	*/

  	initgraph( &GraphDriver, &GraphMode, "" );

	ErrorCode = graphresult(); /* Read result of initialization*/
	if( ErrorCode != grOk ){ /* Error occured during init	*/

	printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
    	exit( 1 );
  	}

	getpalette( &palette ); /* Read the palette from board	*/
	MaxColors = getmaxcolor() + 1; /* Read maximum number of colors*/

    	MaxX = getmaxx();
	MaxY = getmaxy();   /* Read size of screen		*/

	getaspectratio( &xasp, &yasp );	/* read the hardware aspect	*/
	AspectRatio = (double)xasp / (double)yasp; /* Get correction factor	*/
}

/*####################################################*/
/*###  S A V E   9   F R A M E   A N I M A T I O N  ##*/

void Save_Sprite(char *filename, int first, int last)
{

	FILE *fp, *fopen();

	write_file = 1;

	if ((fp = fopen(filename, WRITE)) == NULL) {write_file = 0;}

	 if (write_file == 1)
	 {
		index = 0;

			while (index < 9*(50*50)+1)
			{

			 Data = Anim[index];
			 putw(Data, fp);
			 index++;

			} /* End Of File Writing */

			fclose(fp);

	 } /* End Of While */
}

/*####################################################*/
/*###  L O A D   9   F R A M E   A N I M A T I O N  ##*/

void Load_Sprites(char *filename, int first, int last)
{

	FILE *fp, *fopen();

	read_file = 1;

	if ((fp = fopen(filename, READ)) == NULL) {read_file = 0;}

	 if (read_file == 1)
	 {
		index = 0;

		index_x = 25;
		row = index_x;

		index_y = 25;
		column = index_y;

			while (index < 9*(50*50)+1)
			{

			 Data = getw(fp);
			 Anim[index] = Data;

			 if (row == index_x + 50)
			 {
				 row = index_x;
				 column++;
			 }

			 if (column == index_y + 50)
			 {
				 column = index_y;
				 index_x = index_x + 51;
				 row = index_x;
			 }

			 row++;
			 index++;
       			 putpixel(row, column, Data);

			} /* End Of File Reading */

			fclose(fp);

	 } /* End Of While */
}

/*##############################################################*/
/*###  P A U S E   U N T I L   E S C   K E Y   P R E S S E D  ##*/

void Pause(void)
{
  	#define ESC	  0x1b
  	int c;

  	c = getch();				/* Read a character from kbd	*/

  	if( ESC == c ){			/* Does user wish to leave?	*/
    	closegraph();			/* Change to text mode		*/
    	exit( 1 );				/* Return to OS 		*/
  	}

  	if( 0 == c ){ 			/* Did use hit a non-ASCII key? */
   	 c = getch();			/* Read scan code for keyboard	*/
  	}
}

/*#########################################################################*/
/*###  M A I N   P R O G R A M   F O R   C A L L I N G   R O U T I N E S ##*/

main()
{
	Initialize();
	Load_Sprites("DEFAULT.ANM",1,9);
	Pause();
	closegraph();
}


