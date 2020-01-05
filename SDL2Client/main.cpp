#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>


#include "SDL.h"

using namespace std;

#ifdef _WIN32
#undef main
#endif


//vorausdefinitionen...

void update_kloetze();
void update_oklotz();

int running;

SDL_Surface* screen;
SDL_Texture* screenTexture;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* hintergrund;

SDL_Surface* leerhintergrund;

SDL_Surface* klotzquelle;

SDL_Surface* spielgrund;

SDL_Surface* vorschaugrund;

SDL_Surface* leergrund;

SDL_Surface* gameover;

SDL_Surface* vorschauleer;

SDL_Surface* A;
SDL_Surface* B;
SDL_Surface* C;
SDL_Surface* D;
SDL_Surface* E;
SDL_Surface* F;
SDL_Surface* G;
SDL_Surface* H;
SDL_Surface* I;
SDL_Surface* J;
SDL_Surface* K;
SDL_Surface* L;
SDL_Surface* M;
SDL_Surface* N;
SDL_Surface* O;
SDL_Surface* P;
SDL_Surface* Q;
SDL_Surface* R;
SDL_Surface* S;
SDL_Surface* T;
SDL_Surface* U;
SDL_Surface* V;
SDL_Surface* W;
SDL_Surface* X;
SDL_Surface* Y;
SDL_Surface* Z;

SDL_Surface* null;
SDL_Surface* eins;
SDL_Surface* zwei;
SDL_Surface* drei;
SDL_Surface* vier;
SDL_Surface* fuenf;
SDL_Surface* sechs;
SDL_Surface* sieben;
SDL_Surface* acht;
SDL_Surface* neun;

SDL_Surface* tmp;

unsigned long punkte, reihen, gefallene_felder, steine, steineimbild, abgebaut;

unsigned int level = 1;
unsigned long lastlevel = 0;

unsigned int pause = 0;

//fstream highscore/*("highscore.txt",ios::app|ios::binary)*/;

string	name, anzeige_name;

void outzahlxy(SDL_Surface* surface, unsigned int startx, unsigned int starty, unsigned long zahl) {


	SDL_Rect ziel;

	ziel.x = startx;
	ziel.y = starty;

	unsigned long tmp_zahl = zahl;

	unsigned long quotient;
	unsigned long rest = 1;
	unsigned long divisor = 1000000000;		//beginne mit einer milliarde (größte ulong ~4,5mrd)

	SDL_Surface* tmp = null;

	int	fuehrungsnull = 1;
	int nixmachen = 0;

	while (divisor > 0) {

		quotient = tmp_zahl / divisor;
		rest = tmp_zahl % divisor;

		divisor = divisor / 10;
		tmp_zahl = rest;

		//jetzt den quotienten auf die surface bringen

		switch (quotient) {

		case 0: {

			if (fuehrungsnull == 0) {
				tmp = null;
			}
			else {

				if (rest == 0) {
					tmp = null;
				}
				else {
					nixmachen = 1;
				};

			};

			//fuehrungsnull	=0;


			break; };
		case 1: {

			tmp = eins;


			break; };
		case 2: {

			tmp = zwei;


			break; };
		case 3: {

			tmp = drei;


			break; };
		case 4: {

			tmp = vier;


			break; };
		case 5: {

			tmp = fuenf;


			break; };
		case 6: {

			tmp = sechs;


			break; };
		case 7: {

			tmp = sieben;


			break; };
		case 8: {

			tmp = acht;


			break; };

		case 9: {

			tmp = neun;


			break; };

		default: break;

		};	//switch


		if (nixmachen == 0) {
			fuehrungsnull = 0;
			ziel.h = tmp->h;
			ziel.w = tmp->w;

			SDL_BlitSurface(tmp, 0, surface, &ziel);

			ziel.x += ziel.h;
		}
		else {
			nixmachen = 0;
		};




	};	//while

		//SDL_UpdateRect(surface,startx,starty,ziel.x,(starty+30));






};


void outtextxy(SDL_Surface* surface, unsigned int startx, unsigned int starty, string text) {


	SDL_Rect quelle, ziel;

	ziel.x = startx;
	ziel.y = starty;



	for (unsigned int i = 0; i < text.length(); ++i) {

		switch (text[i]) {

		case 'A': {

			tmp = A;


			break; };

		case 'B': {

			tmp = B;

			break; };

		case 'C': {

			tmp = C;


			break; };
		case 'D': {

			tmp = D;


			break; };

		case 'E': {

			tmp = E;


			break; };
		case 'F': {

			tmp = F;


			break; };
		case 'G': {

			tmp = G;


			break; };
		case 'H': {

			tmp = H;


			break; };
		case 'I': {

			tmp = I;


			break; };
		case 'J': {

			tmp = J;


			break; };
		case 'K': {

			tmp = K;


			break; };
		case 'L': {

			tmp = L;


			break; };
		case 'M': {

			tmp = M;


			break; };
		case 'N': {

			tmp = N;


			break; };
		case 'O': {

			tmp = O;


			break; };
		case 'P': {

			tmp = P;


			break; };
		case 'Q': {

			tmp = Q;


			break; };
		case 'R': {

			tmp = R;


			break; };
		case 'S': {

			tmp = S;


			break; };
		case 'T': {

			tmp = T;


			break; };
		case 'U': {

			tmp = U;


			break; };
		case 'V': {

			tmp = V;


			break; };
		case 'W': {

			tmp = W;


			break; };
		case 'X': {

			tmp = X;


			break; };
		case 'Y': {

			tmp = Y;


			break; };
		case 'Z': {

			tmp = Z;


			break; };

		case '0': {

			tmp = null;


			break; };
		case '1': {

			tmp = eins;


			break; };
		case '2': {

			tmp = zwei;


			break; };
		case '3': {

			tmp = drei;


			break; };
		case '4': {

			tmp = vier;


			break; };
		case '5': {

			tmp = fuenf;


			break; };
		case '6': {

			tmp = sechs;


			break; };
		case '7': {

			tmp = sieben;


			break; };
		case '8': {

			tmp = acht;


			break; };

		case '9': {

			tmp = neun;


			break; };

		default: break;




		};

		ziel.h = tmp->h;
		ziel.w = tmp->w;

		SDL_BlitSurface(tmp, 0, surface, &ziel);

		ziel.x += ziel.h;
		//ziel.y	+=ziel.w;



	};

	// only partial update here? shouldnt this behave similarly to outzahlxy?
	// seems unused right now anyways, probably preparation to display hiscore names etc
	//SDL_UpdateRect(surface, startx, starty, ziel.x, (starty + 30));

};

SDL_Surface* LoadBMP(const char* szFile)
{
	SDL_Surface* orig, * convert;

	orig = SDL_LoadBMP(szFile);
	if (!orig) {
		fprintf(stderr, "%s konnte nicht geladen werden: %s\n", szFile, SDL_GetError());
		exit(1);
	}

	convert = SDL_ConvertSurface(orig, screen->format, screen->flags);
	SDL_FreeSurface(orig);
	if (!convert) {
		fprintf(stderr, "%s konnte nicht ins Bildschirmformat konvertiert werden: %s\n",
			szFile, SDL_GetError());
		exit(1);
	}

	return convert;
}

#define maxx	18
#define maxy	25
//die unterste reihe (y=24) ist unsichtbar aber voll belegt um den aufprall berechnen zukönnen

class klotz {
public:
	int gesetzt;
	int typ;	//quelldatei =640*480=307200/(20*20)=>768 versch typen
};

unsigned int zusammenfall = 1;

klotz klotzfeld[4][4];
unsigned int klotz_x, klotz_y;		//linke obere ecke des klotzfeldes in relation zum spielfeld
klotz spielfeld[maxx][maxy];
klotz vorschau[4][4];

unsigned int fallgeschwindigkeit = 500;	//bedeutet ein kästchenfall je sekunde->laaaaaaangsam

unsigned int naechster_stein = 1;

void loesche_klotzfeld() {

	unsigned int x, y;
	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			klotzfeld[x][y].gesetzt = 0;
			klotzfeld[x][y].typ = 0;

		};
};

void loesche_vorschau() {

	unsigned int x, y;
	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			vorschau[x][y].gesetzt = 0;
			vorschau[x][y].typ = 0;

		};
};

void neu_level() {

	level++;
	fallgeschwindigkeit = (fallgeschwindigkeit * 85) / 100;


};

void spielfeld_ini(unsigned int max) {	//max gibt die maximale höhe an anfangsklötzen an

	unsigned int x, y;

	for (x = 0; x < maxx; ++x)
		for (y = 0; y < (maxy - 1); ++y) {

			spielfeld[x][y].gesetzt = 0;
			spielfeld[x][y].typ = 0;

			spielfeld[x][maxy - 1].gesetzt = 1;
			spielfeld[x][maxy - 1].typ = 1;

		};

	loesche_klotzfeld();
};

void voll() {	//prüft bei auftreffen des steins auf vollständige reihen

	unsigned int x, y, y1;
	int	reihevoll = 0;
	for (y = 0; y < (maxy - 1); ++y) {

		if (spielfeld[0][y].gesetzt == 1) {

			reihevoll = 1;
			for (x = 1; x < maxx; ++x) {

				if (spielfeld[x][y].gesetzt == 0) {
					reihevoll = 0;
					//cout<<"reihe nicht voll x"<<x<<" y"<<y<<endl;
					break;
				};

			};
			if (reihevoll == 1) {

				reihen += 1;

				for (x = 0; x < maxx; ++x) spielfeld[x][y].gesetzt = 0;
				steineimbild -= maxx;
				abgebaut++;
				//cout<<"reihe y="<<y<<" geloescht"<<endl;

				update_kloetze();

				SDL_RenderPresent(renderer);

				if (zusammenfall == 1) {

					for (x = 0; x < maxx; ++x)
						for (y1 = y; y1 > 0; --y1) {

							spielfeld[x][y1].gesetzt = spielfeld[x][y1 - 1].gesetzt;
							spielfeld[x][y1].typ = spielfeld[x][y1 - 1].typ;

						};
					if ((abgebaut - lastlevel) == 8) {

						lastlevel = abgebaut;
						neu_level();

					};

					SDL_Delay(50);

					update_kloetze();

					SDL_RenderPresent(renderer);
				};

			};

		};

	};

};
void ende() {

	SDL_Rect	quelle, ziel;

	quelle.h = 40;
	quelle.w = 480;
	quelle.x = 0;
	quelle.y = 0;

	ziel.h = 40;
	ziel.w = 480;
	ziel.x = 0;
	ziel.y = 200;

	SDL_BlitSurface(gameover, &quelle, spielgrund, &ziel);

	quelle.x = 0;
	quelle.y = 0;
	quelle.h = 480;
	quelle.w = 480;

	ziel.x = 80;
	ziel.y = 0;
	ziel.h = 480;
	ziel.w = 240;

	SDL_BlitSurface(spielgrund, &quelle, screen, &ziel);

	SDL_UpdateTexture(screenTexture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000);

	//highscore<<name<<endl;
	//highscore.close();

	running = 0;


};

void steinvorschau() {

	loesche_vorschau();

	switch (naechster_stein) {

	case 0: {

		vorschau[1][0].gesetzt = 1;
		vorschau[1][0].typ = rand() % 768 + 1;
		vorschau[1][1].gesetzt = 1;
		vorschau[1][1].typ = rand() % 768 + 1;
		vorschau[2][0].gesetzt = 1;
		vorschau[2][0].typ = rand() % 768 + 1;
		vorschau[2][1].gesetzt = 1;
		vorschau[2][1].typ = rand() % 768 + 1;

		break; }

	case 1: {

		vorschau[0][0].gesetzt = 1;
		vorschau[0][0].typ = rand() % 768 + 1;
		vorschau[1][0].gesetzt = 1;
		vorschau[1][0].typ = rand() % 768 + 1;
		vorschau[2][0].gesetzt = 1;
		vorschau[2][0].typ = rand() % 768 + 1;
		vorschau[3][0].gesetzt = 1;
		vorschau[3][0].typ = rand() % 768 + 1;

		break; }

	case 2: {

		vorschau[0][0].gesetzt = 1;
		vorschau[0][0].typ = rand() % 768 + 1;
		vorschau[1][0].gesetzt = 1;
		vorschau[1][0].typ = rand() % 768 + 1;
		vorschau[2][0].gesetzt = 1;
		vorschau[2][0].typ = rand() % 768 + 1;
		vorschau[0][1].gesetzt = 1;
		vorschau[0][1].typ = rand() % 768 + 1;

		break; }

	case 3: {

		vorschau[0][0].gesetzt = 1;
		vorschau[0][0].typ = rand() % 768 + 1;
		vorschau[1][0].gesetzt = 1;
		vorschau[1][0].typ = rand() % 768 + 1;
		vorschau[2][0].gesetzt = 1;
		vorschau[2][0].typ = rand() % 768 + 1;
		vorschau[1][1].gesetzt = 1;
		vorschau[1][1].typ = rand() % 768 + 1;

		break; }

	case 4: {

		vorschau[0][0].gesetzt = 1;
		vorschau[0][0].typ = rand() % 768 + 1;
		vorschau[0][1].gesetzt = 1;
		vorschau[0][1].typ = rand() % 768 + 1;
		vorschau[1][1].gesetzt = 1;
		vorschau[1][1].typ = rand() % 768 + 1;
		vorschau[2][1].gesetzt = 1;
		vorschau[2][1].typ = rand() % 768 + 1;


	};
	case 5: {

		unsigned int counter = 4;

		for (unsigned int x = 0; x < 4; ++x)
			for (unsigned int y = 0; y < 4; ++y) {

				if (counter == 0) {}
				else {

					vorschau[x][y].gesetzt = rand() % 2;	//entweder 0 oder 1
					vorschau[x][y].typ = rand() % 768 + 1;

					--counter;
				};


			};

	};
	case 6: {

		for (unsigned int x = 0; x < 4; ++x)
			for (unsigned int y = 0; y < 4; ++y) {

				vorschau[x][y].gesetzt = rand() % 2;	//entweder 0 oder 1
				vorschau[x][y].typ = rand() % 768 + 1;


			};


	};

	};

};

unsigned long pot(unsigned int base, unsigned int exp) {

	unsigned int tmp = base;

	if (exp == 0) {
		return 1;
	}
	else {

		return (base * pot(base, (exp - 1)));

	};


};

void gib_punkte() {

	punkte += 10 + ((reihen > 0) ? (100 * (pot(level, reihen))) : 0) + ((float(gefallene_felder) / float(maxy - 1)) * 10 * level);

	reihen = 0;


};

int erzeuge_stein() {	// erzeugt einen neuen stein im klotzfeld
/*
 siehe dokumentation.txt für steinarten
	*/
	voll();
	loesche_klotzfeld();
	klotz_x = 8;
	klotz_y = 0;
	/*switch(naechster_stein){

	case 0:{

		klotzfeld[1][0].gesetzt	=	1;
		klotzfeld[1][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[1][0].typ<<endl;
		klotzfeld[1][1].gesetzt	=	1;
		klotzfeld[1][1].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[1][1].typ<<endl;
		klotzfeld[2][0].gesetzt	=	1;
		klotzfeld[2][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[2][0].typ<<endl;
		klotzfeld[2][1].gesetzt	=	1;
		klotzfeld[2][1].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[2][1].typ<<endl;

		break;}

	case 1:{

		klotzfeld[0][0].gesetzt	=	1;
		klotzfeld[0][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[0][0].typ<<endl;
		klotzfeld[1][0].gesetzt	=	1;
		klotzfeld[1][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[1][0].typ<<endl;
		klotzfeld[2][0].gesetzt	=	1;
		klotzfeld[2][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[2][0].typ<<endl;
		klotzfeld[3][0].gesetzt	=	1;
		klotzfeld[3][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[3][0].typ<<endl;

		break;}

	case 2:{

		klotzfeld[0][0].gesetzt	=	1;
		klotzfeld[0][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[0][0].typ<<endl;
		klotzfeld[1][0].gesetzt	=	1;
		klotzfeld[1][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[1][0].typ<<endl;
		klotzfeld[2][0].gesetzt	=	1;
		klotzfeld[2][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[2][0].typ<<endl;
		klotzfeld[0][1].gesetzt=	1;
		klotzfeld[0][1].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[0][1].typ<<endl;

		break;}

	case 3:{

		klotzfeld[0][0].gesetzt	=	1;
		klotzfeld[0][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[0][0].typ<<endl;
		klotzfeld[1][0].gesetzt	=	1;
		klotzfeld[1][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[1][0].typ<<endl;
		klotzfeld[2][0].gesetzt	=	1;
		klotzfeld[2][0].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[2][0].typ<<endl;
		klotzfeld[1][1].gesetzt	=	1;
		klotzfeld[1][1].typ		=	rand()%768	+1;
		cout<<"typ: "<<klotzfeld[1][1].typ<<endl;

		break;}

	};*/

	naechster_stein = rand() % 4;

	unsigned int x, y;
	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			klotzfeld[x][y] = vorschau[x][y];

			if (klotzfeld[x][y].gesetzt == 1) {

				if (spielfeld[x + klotz_x][y + klotz_y + 1].gesetzt == 1)	return 1;
				if (spielfeld[x + klotz_x][y + klotz_y].gesetzt == 1)		return 1;

			};


		};

	steinvorschau();
	steineimbild += 4;
	steine++;
	gefallene_felder = 0;
	return 0;

};


unsigned int abstand() {		//gibt null zurück wenn der klotz direkt über einem stein ist sonst 1!

	unsigned int x, y;

	unsigned int neu = 0;

	for (x = 0; x < 4; x++)
		for (y = 0; y < 4; y++) {

			if (klotzfeld[x][y].gesetzt == 1) {
				//if((x+klotz_x)>=maxx)	return 1;
				/*if((y+klotz_y+1)>=maxy){

					return 0;};*/
				if (spielfeld[x + klotz_x][y + klotz_y + 1].gesetzt == 1) {

					for (x = 0; x < 4; ++x)
						for (y = 0; y < 4; ++y) {

							if (klotzfeld[x][y].gesetzt == 1) {
								spielfeld[x + klotz_x][y + klotz_y].gesetzt = 1;
								spielfeld[x + klotz_x][y + klotz_y].typ = klotzfeld[x][y].typ;
							};


						};
					gib_punkte();

					int zuende = erzeuge_stein();
					if (zuende == 1)	ende();

					return 0;
				};

			};

		};

	return 1;

};

void fallen_lassen(Uint32& letzter_fall, Uint32 aktuelleZeit) {

	if ((aktuelleZeit - letzter_fall) >= fallgeschwindigkeit) {
		unsigned int i = abstand();
		if (i > 0) {

			++klotz_y;
			gefallene_felder++;
			letzter_fall = aktuelleZeit;
		}
		else {

			/*			for(x=0;x<4;++x)
							for(y=0;y<4;++y){
								if(klotzfeld[x][y].gesetzt==1){
									spielfeld[x+klotz_x][y+klotz_y].gesetzt	=1;
									spielfeld[x+klotz_x][y+klotz_y].typ		=klotzfeld[x][y].typ;
								};
							};*/



		};
	};

};


/*void update_oklotz(){

	unsigned int x,y,tmptyp,qx,qy;

	SDL_Rect	quelle,ziel;

	quelle.h	=20;
	quelle.w	=20;
	quelle.x	=0;
	quelle.y	=0;

	ziel.h		=20;
	ziel.w		=20;
	ziel.x		=0;
	ziel.y		=0;

	//spielgrund	=	LoadBMP("spielgrund.bmp");//leergrund;
	SDL_BlitSurface(leergrund, 0, spielgrund, 0);


	for(x=0;x<maxx;++x)
		for(y=0;y<(maxy-1);++y){

			if(spielfeld[x][y].gesetzt==1){

			tmptyp			=	spielfeld[x][y].typ;
			quelle.x		=	((tmptyp-1)%32)*20;
			quelle.y		=	((tmptyp-1)/32)*20;

			ziel.x			=	x*20;
			ziel.y			=	y*20;

			SDL_BlitSurface(klotzquelle, &quelle, spielgrund, &ziel);};

		};

	quelle.x	=0;
	quelle.y	=0;
	quelle.h	=480;
	quelle.w	=480;

	ziel.x		=80;
	ziel.y		=0;
	ziel.h		=480;
	ziel.w		=240;

	SDL_BlitSurface(spielgrund, &quelle, screen, &ziel);




};*/

void update_kloetze() {

	unsigned int x, y, tmptyp;

	SDL_Rect	quelle, ziel;

	quelle.h = 20;
	quelle.w = 20;
	quelle.x = 0;
	quelle.y = 0;

	ziel.h = 20;
	ziel.w = 20;
	ziel.x = 0;
	ziel.y = 0;

	//spielgrund	=	LoadBMP("spielgrund.bmp");//leergrund;
	SDL_BlitSurface(leergrund, 0, spielgrund, 0);
	SDL_BlitSurface(vorschauleer, 0, vorschaugrund, 0);


	for (x = 0; x < maxx; ++x)
		for (y = 0; y < (maxy - 1); ++y) {

			if (spielfeld[x][y].gesetzt == 1) {

				tmptyp = spielfeld[x][y].typ;
				quelle.x = ((tmptyp - 1) % 32) * 20;
				quelle.y = ((tmptyp - 1) / 32) * 20;

				ziel.x = x * 20;
				ziel.y = y * 20;

				SDL_BlitSurface(klotzquelle, &quelle, spielgrund, &ziel);
			};

		};

	// den beweglichen klotz extra einberechnen...

	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			if (klotzfeld[x][y].gesetzt == 1) {

				tmptyp = klotzfeld[x][y].typ;
				quelle.x = ((tmptyp - 1) % 32) * 20;
				quelle.y = ((tmptyp - 1) / 32) * 20;

				ziel.x = (klotz_x + x) * 20;
				ziel.y = (klotz_y + y) * 20;

				SDL_BlitSurface(klotzquelle, &quelle, spielgrund, &ziel);


			};

			/*if(vorschau[x][y].gesetzt==1){

				tmptyp		=	vorschau[x][y].typ;
				quelle.x	=	((tmptyp-1)%32)*20;
				quelle.y	=	((tmptyp-1)/32)*20;

				ziel.x		=	(klotz_x+x)*20;
				ziel.y		=	(klotz_y+y)*20;

				SDL_BlitSurface(klotzquelle, &quelle, spielgrund, &ziel);



			};*/


		};


	quelle.x = 0;
	quelle.y = 0;
	quelle.h = 480;
	quelle.w = 360;

	ziel.x = 200;
	ziel.y = 0;
	ziel.h = 480;
	ziel.w = 360;

	SDL_BlitSurface(spielgrund, &quelle, screen, &ziel);

	SDL_UpdateTexture(screenTexture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);


};




void zeichne_hintergrund() {

	//linker rand....

	unsigned int tmptyp, x, y;

	SDL_Rect quelle;
	SDL_Rect ziel;

	quelle.x = 0;
	quelle.y = 0;
	quelle.w = 200;
	quelle.h = 480;

	ziel.x = 0;
	ziel.y = 0;

	SDL_BlitSurface(leerhintergrund, &quelle, hintergrund, &ziel);
	outzahlxy(hintergrund, 0, 340, steine);
	outzahlxy(hintergrund, 0, 380, steineimbild);
	outzahlxy(hintergrund, 0, 420, level);
	outzahlxy(hintergrund, 0, 460, abgebaut);
	outzahlxy(hintergrund, 0, 300, punkte);
	SDL_BlitSurface(hintergrund, &quelle, screen, &ziel);

	//steinvorschauhintergrund im linken rand...

	quelle.x = 0;
	quelle.y = 0;
	quelle.w = 100;
	quelle.h = 100;

	ziel.x = 50;
	ziel.y = 20;

	SDL_BlitSurface(vorschauleer, &quelle, screen, &ziel);

	//steinvorschau zeichnen...

/**/

	quelle.h = 20;
	quelle.w = 20;
	ziel.h = 20;
	ziel.w = 20;

	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			if (vorschau[x][y].gesetzt == 1) {


				tmptyp = vorschau[x][y].typ;
				quelle.x = ((tmptyp - 1) % 32) * 20;
				quelle.y = ((tmptyp - 1) / 32) * 20;

				ziel.x = 20 + (x * 20);
				ziel.y = 20 + (y * 20);


				SDL_BlitSurface(klotzquelle, &quelle, vorschaugrund, &ziel);


			};
		};

	quelle.x = 0;
	quelle.y = 0;
	quelle.h = 100;
	quelle.w = 100;

	ziel.x = 50;
	ziel.y = 20;
	ziel.h = 100;
	ziel.w = 100;

	SDL_BlitSurface(vorschaugrund, 0, screen, &ziel);

	//rechter rand

	quelle.x = 560;
	quelle.y = 0;
	quelle.w = 80;
	quelle.h = 480;

	ziel.x = 560;
	ziel.y = 0;

	SDL_BlitSurface(leerhintergrund, &quelle, screen, &ziel);

	//SDL_UpdateRect(

	SDL_UpdateTexture(screenTexture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);


};

void links_bewegen() {

	int besetzt = 0;

	for (unsigned int x = 0; x < 4; ++x)
		for (unsigned int y = 0; y < 4; ++y) {

			if (klotzfeld[x][y].gesetzt == 1) {
				if ((x + klotz_x) == 0)	besetzt = 1;
				if (spielfeld[x + klotz_x - 1][y + klotz_y].gesetzt == 1) besetzt = 1;
			};


		};

	if (besetzt == 0) --klotz_x;

};
void rechts_bewegen() {

	int besetzt = 0;

	for (unsigned int x = 0; x < 4; ++x)
		for (unsigned int y = 0; y < 4; ++y) {

			if (klotzfeld[x][y].gesetzt == 1) {
				if ((x + klotz_x) == (maxx - 1))	besetzt = 1;
				if (spielfeld[x + klotz_x + 1][y + klotz_y].gesetzt == 1) besetzt = 1;
			};


		};

	if (besetzt == 0) ++klotz_x;

};
void unten_bewegen() {

	int besetzt = 0;

	for (unsigned int x = 0; x < 4; ++x)
		for (unsigned int y = 0; y < 4; ++y) {

			if (klotzfeld[x][y].gesetzt == 1) {

				if (spielfeld[x + klotz_x][y + klotz_y + 1].gesetzt == 1) besetzt = 1;
			};


		};

	if (besetzt == 0) ++klotz_y;

};
void frei_fall() {

	unsigned int angekommen = 0;

	unsigned int x, y;

	while (angekommen != 1) {
		for (x = 0; x < 4; ++x)
			for (y = 0; y < 4; ++y) {

				if (klotzfeld[x][y].gesetzt == 1) {

					if (spielfeld[x + klotz_x][y + klotz_y + 1].gesetzt == 1) {

						angekommen = 1;

					};

				};

			};
		if (angekommen != 1) ++klotz_y;

	};

	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			if (klotzfeld[x][y].gesetzt == 1) {

				spielfeld[x + klotz_x][y + klotz_y].gesetzt = 1;
				spielfeld[x + klotz_x][y + klotz_y].typ = klotzfeld[x][y].typ;


			};

		};

};

void drehen() {	//drehung nach links

	klotz tmpfeld[4][4];
	unsigned int x, y;
	unsigned int drehung = 1;
	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {
			tmpfeld[x][y].gesetzt = 0;
			tmpfeld[x][y].typ = 0;

			tmpfeld[x][y].gesetzt = klotzfeld[3 - y][x].gesetzt;
			tmpfeld[x][y].typ = klotzfeld[3 - y][x].typ;
		};

	for (x = 0; x < 4; ++x)
		for (y = 0; y < 4; ++y) {

			if (tmpfeld[x][y].gesetzt == 1) {

				if (spielfeld[x + klotz_x][y + klotz_y].gesetzt == 1) drehung = 0;
				if ((x + klotz_x) > (maxx - 1)) drehung = 0;
			};

		};

	if (drehung == 1) {

		for (x = 0; x < 4; ++x)
			for (y = 0; y < 4; ++y) {
				klotzfeld[x][y].gesetzt = tmpfeld[x][y].gesetzt;
				klotzfeld[x][y].typ = tmpfeld[x][y].typ;
			};
	};


};

int main()
{
	/* screen und running werden später verwendet */

	srand(time(0));
	Uint32 lastframe, curframe, frametime;
	Uint32 last_fall;

	Uint32 linksrechtsverz = 50;
	Uint32 last_lr;
	Uint32 lastpause;

	cout << "Name?!?" << endl;
	cin >> name;

	anzeige_name = "";



	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL konnte nicht initialisiert werden: %s\n",
			SDL_GetError());
		exit(1);
	}

	atexit(SDL_Quit);

	SDL_CreateWindowAndRenderer(
		640,
		480,
		SDL_WINDOW_BORDERLESS,
		&window,
		&renderer);

	SDL_RenderClear(renderer);

	screen = SDL_CreateRGBSurface(0, 640, 480, 32,
		0x00FF0000,
		0x0000FF00,
		0x000000FF,
		0xFF000000);

	screenTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		640, 480);

	if (!window) {
		fprintf(stderr, "Konnte Bildschirmmodus nicht setzen: %s\n",
			SDL_GetError());
		exit(1);
	}

	hintergrund = LoadBMP("rand.bmp");
	leerhintergrund = LoadBMP("rand.bmp");
	klotzquelle = LoadBMP("klotz.bmp");
	spielgrund = LoadBMP("spielgrund.bmp");
	leergrund = LoadBMP("spielgrund.bmp");
	vorschaugrund = LoadBMP("vorschau.bmp");
	vorschauleer = LoadBMP("vorschau.bmp");
	gameover = LoadBMP("gameover.bmp");
	A = LoadBMP("A.BMP");
	SDL_SetColorKey(A, SDL_TRUE, SDL_MapRGB(A->format, 0, 0, 0));
	B = LoadBMP("B.BMP");
	SDL_SetColorKey(B, SDL_TRUE, SDL_MapRGB(B->format, 0, 0, 0));
	C = LoadBMP("C.BMP");
	SDL_SetColorKey(C, SDL_TRUE, SDL_MapRGB(C->format, 0, 0, 0));
	D = LoadBMP("D.BMP");
	SDL_SetColorKey(D, SDL_TRUE, SDL_MapRGB(D->format, 0, 0, 0));
	E = LoadBMP("E.BMP");
	SDL_SetColorKey(E, SDL_TRUE, SDL_MapRGB(E->format, 0, 0, 0));
	F = LoadBMP("F.BMP");
	SDL_SetColorKey(F, SDL_TRUE, SDL_MapRGB(F->format, 0, 0, 0));
	G = LoadBMP("G.BMP");
	SDL_SetColorKey(G, SDL_TRUE, SDL_MapRGB(G->format, 0, 0, 0));
	H = LoadBMP("H.BMP");
	SDL_SetColorKey(H, SDL_TRUE, SDL_MapRGB(H->format, 0, 0, 0));
	I = LoadBMP("I.BMP");
	SDL_SetColorKey(I, SDL_TRUE, SDL_MapRGB(I->format, 0, 0, 0));
	J = LoadBMP("J.BMP");
	SDL_SetColorKey(J, SDL_TRUE, SDL_MapRGB(J->format, 0, 0, 0));
	K = LoadBMP("K.BMP");
	SDL_SetColorKey(K, SDL_TRUE, SDL_MapRGB(K->format, 0, 0, 0));
	L = LoadBMP("L.BMP");
	SDL_SetColorKey(L, SDL_TRUE, SDL_MapRGB(L->format, 0, 0, 0));
	M = LoadBMP("M.BMP");
	SDL_SetColorKey(M, SDL_TRUE, SDL_MapRGB(M->format, 0, 0, 0));
	N = LoadBMP("N.BMP");
	SDL_SetColorKey(N, SDL_TRUE, SDL_MapRGB(N->format, 0, 0, 0));
	O = LoadBMP("O.BMP");
	SDL_SetColorKey(O, SDL_TRUE, SDL_MapRGB(O->format, 0, 0, 0));
	P = LoadBMP("P.BMP");
	SDL_SetColorKey(P, SDL_TRUE, SDL_MapRGB(P->format, 0, 0, 0));
	Q = LoadBMP("Q.BMP");
	SDL_SetColorKey(Q, SDL_TRUE, SDL_MapRGB(Q->format, 0, 0, 0));
	R = LoadBMP("R.BMP");
	SDL_SetColorKey(R, SDL_TRUE, SDL_MapRGB(R->format, 0, 0, 0));
	S = LoadBMP("S.BMP");
	SDL_SetColorKey(S, SDL_TRUE, SDL_MapRGB(S->format, 0, 0, 0));
	T = LoadBMP("T.BMP");
	SDL_SetColorKey(T, SDL_TRUE, SDL_MapRGB(T->format, 0, 0, 0));
	U = LoadBMP("U.BMP");
	SDL_SetColorKey(U, SDL_TRUE, SDL_MapRGB(U->format, 0, 0, 0));
	V = LoadBMP("V.BMP");
	SDL_SetColorKey(V, SDL_TRUE, SDL_MapRGB(V->format, 0, 0, 0));
	W = LoadBMP("W.BMP");
	SDL_SetColorKey(W, SDL_TRUE, SDL_MapRGB(W->format, 0, 0, 0));
	X = LoadBMP("X.BMP");
	SDL_SetColorKey(X, SDL_TRUE, SDL_MapRGB(X->format, 0, 0, 0));
	Y = LoadBMP("Y.BMP");
	SDL_SetColorKey(Y, SDL_TRUE, SDL_MapRGB(Y->format, 0, 0, 0));
	Z = LoadBMP("Z.BMP");
	SDL_SetColorKey(Z, SDL_TRUE, SDL_MapRGB(Z->format, 0, 0, 0));
	eins = LoadBMP("1.BMP");
	SDL_SetColorKey(eins, SDL_TRUE, SDL_MapRGB(eins->format, 0, 0, 0));
	zwei = LoadBMP("2.BMP");
	SDL_SetColorKey(zwei, SDL_TRUE, SDL_MapRGB(zwei->format, 0, 0, 0));
	drei = LoadBMP("3.BMP");
	SDL_SetColorKey(drei, SDL_TRUE, SDL_MapRGB(drei->format, 0, 0, 0));
	vier = LoadBMP("4.BMP");
	SDL_SetColorKey(vier, SDL_TRUE, SDL_MapRGB(vier->format, 0, 0, 0));
	fuenf = LoadBMP("5.BMP");
	SDL_SetColorKey(fuenf, SDL_TRUE, SDL_MapRGB(fuenf->format, 0, 0, 0));
	sechs = LoadBMP("6.BMP");
	SDL_SetColorKey(sechs, SDL_TRUE, SDL_MapRGB(sechs->format, 0, 0, 0));
	sieben = LoadBMP("7.BMP");
	SDL_SetColorKey(sieben, SDL_TRUE, SDL_MapRGB(sieben->format, 0, 0, 0));
	acht = LoadBMP("8.BMP");
	SDL_SetColorKey(acht, SDL_TRUE, SDL_MapRGB(acht->format, 0, 0, 0));
	neun = LoadBMP("9.BMP");
	SDL_SetColorKey(neun, SDL_TRUE, SDL_MapRGB(neun->format, 0, 0, 0));
	null = LoadBMP("0.BMP");
	SDL_SetColorKey(null, SDL_TRUE, SDL_MapRGB(null->format, 0, 0, 0));

	//SDL_SetColorKey(hintergrund, SDL_SRCCOLORKEY, g_Black);

	spielfeld_ini(12);		//wert erstmal irrelevant...für spätere modifikationen

	steinvorschau();

	int ende = erzeuge_stein();
	//klotz_einbinden();

	zeichne_hintergrund();
	update_kloetze();
	SDL_RenderPresent(renderer);

	running = 1;
	curframe = SDL_GetTicks();
	last_fall = curframe;
	last_lr = curframe;
	lastpause = curframe;

	punkte = 0;
	reihen = 0;
	gefallene_felder = 0;
	steine = 0;
	steineimbild = 0;
	abgebaut = 0;

	while (running) {
		SDL_Event event;
		const Uint8* keystate;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = 0;
					break;

				case SDLK_RCTRL:
					drehen();
					break;

				case SDLK_UP:
					frei_fall();
					break;
				};


				break;

			case SDL_QUIT:
				running = 0;
				break;
			}
		}

		keystate = SDL_GetKeyboardState(0);

		if (keystate[SDL_SCANCODE_LEFT]) {
			if ((last_lr + linksrechtsverz) < curframe) {
				links_bewegen();
				last_lr = curframe;
			};
		};
		if (keystate[SDL_SCANCODE_RIGHT]) {
			if ((last_lr + linksrechtsverz) < curframe) {
				rechts_bewegen();
				last_lr = curframe;
			};
		};
		if (keystate[SDL_SCANCODE_DOWN])	unten_bewegen();

		if (keystate[SDL_SCANCODE_RETURN]) {

			if ((lastpause + 1000) < curframe) {

				lastpause = curframe;

				if (pause == 1) {

					last_fall = curframe;
					pause = 0;

				}
				else {

					last_fall = curframe;
					pause = 1;

				};
			};
		};

		lastframe = curframe;
		curframe = SDL_GetTicks();
		frametime = curframe - lastframe;

		if (pause == 1)	last_fall = curframe;

		fallen_lassen(last_fall, curframe);

		zeichne_hintergrund();

		update_kloetze();

		SDL_RenderPresent(renderer);


	}

	SDL_FreeSurface(hintergrund);
	SDL_FreeSurface(leerhintergrund);
	SDL_FreeSurface(klotzquelle);
	SDL_FreeSurface(spielgrund);
	SDL_FreeSurface(leergrund);
	SDL_FreeSurface(gameover);
	SDL_FreeSurface(vorschaugrund);
	SDL_FreeSurface(vorschauleer);
	SDL_FreeSurface(A);
	SDL_FreeSurface(B);
	SDL_FreeSurface(C);
	SDL_FreeSurface(D);
	SDL_FreeSurface(E);
	SDL_FreeSurface(F);
	SDL_FreeSurface(G);
	SDL_FreeSurface(H);
	SDL_FreeSurface(I);
	SDL_FreeSurface(J);
	SDL_FreeSurface(K);
	SDL_FreeSurface(L);
	SDL_FreeSurface(M);
	SDL_FreeSurface(N);
	SDL_FreeSurface(O);
	SDL_FreeSurface(P);
	SDL_FreeSurface(Q);
	SDL_FreeSurface(R);
	SDL_FreeSurface(S);
	SDL_FreeSurface(T);
	SDL_FreeSurface(U);
	SDL_FreeSurface(V);
	SDL_FreeSurface(W);
	SDL_FreeSurface(X);
	SDL_FreeSurface(Y);
	SDL_FreeSurface(Z);

	SDL_FreeSurface(null);
	SDL_FreeSurface(eins);
	SDL_FreeSurface(zwei);
	SDL_FreeSurface(drei);
	SDL_FreeSurface(vier);
	SDL_FreeSurface(fuenf);
	SDL_FreeSurface(sechs);
	SDL_FreeSurface(sieben);
	SDL_FreeSurface(acht);
	SDL_FreeSurface(neun);

	ofstream highscore("highscore.txt", ios::app | ios::binary);

	highscore << punkte << " " << name << " " << abgebaut << " " << steine << endl;

	highscore.close();

	return 0;

}
