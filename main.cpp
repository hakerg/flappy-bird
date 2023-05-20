#include <allegro.h>

int main()
{
	srand(time(0));
	allegro_init();
	install_keyboard();
	install_mouse();
	install_sound(-1, -1, 0);
	set_color_depth(32);
	set_gfx_mode(2, 640, 480, 0, 0);
	BITMAP *bufor = create_bitmap(SCREEN_W, SCREEN_H);
	
	BITMAP *biel = create_bitmap(SCREEN_W, SCREEN_H);   clear_to_color(biel, makecol(255,255,255));
	BITMAP *atlas = load_bitmap("atlas.bmp", 0);
	BITMAP *bird[4];
	bird[0] = create_bitmap(34, 24);			blit(atlas, bird[0], 62, 982, 0, 0, 34, 24);
	bird[1] = create_bitmap(34, 24);			blit(atlas, bird[1], 118, 982, 0, 0, 34, 24);
	bird[2] = create_bitmap(34, 24);			blit(atlas, bird[2], 62, 982, 0, 0, 34, 24);
	bird[3] = create_bitmap(34, 24);			blit(atlas, bird[3], 6, 982, 0, 0, 34, 24);
	BITMAP *day = create_bitmap(1152, 512);		blit(atlas, day, 0, 0, 0, 0, 288, 512);
												blit(atlas, day, 0, 0, 288, 0, 288, 512);
												blit(atlas, day, 0, 0, 576, 0, 288, 512);
												blit(atlas, day, 0, 0, 864, 0, 288, 512);
	BITMAP *night = create_bitmap(1152, 512);	blit(atlas, night, 292, 0, 0, 0, 288, 512);
												blit(atlas, night, 292, 0, 288, 0, 288, 512);
												blit(atlas, night, 292, 0, 576, 0, 288, 512);
												blit(atlas, night, 292, 0, 864, 0, 288, 512);
	BITMAP *ground = create_bitmap(1344, 112);	blit(atlas, ground, 584, 0, 0, 0, 336, 112);
												blit(atlas, ground, 584, 0, 336, 0, 336, 112);
												blit(atlas, ground, 584, 0, 672, 0, 336, 112);
												blit(atlas, ground, 584, 0, 1008, 0, 336, 112);
	BITMAP *dol = create_bitmap(52, 320);		blit(atlas, dol, 168, 646, 0, 0, 52, 320);
	BITMAP *gora = create_bitmap(52, 320);		blit(atlas, gora, 112, 646, 0, 0, 52, 320);
	BITMAP *ready = create_bitmap(184, 50);		blit(atlas, ready, 590, 118, 0, 0, 184, 50);
	BITMAP *push = create_bitmap(114, 91);		blit(atlas, push, 584, 182, 0, 0, 114, 91);
	BITMAP *p[10];
	p[0] = create_bitmap(24, 36);				blit(atlas, p[0], 992, 120, 0, 0, 24, 36);
	p[1] = create_bitmap(24, 36);				blit(atlas, p[1], 272, 910, 0, 0, 24, 36);
	p[2] = create_bitmap(24, 36);				blit(atlas, p[2], 584, 320, 0, 0, 24, 36);
	p[3] = create_bitmap(24, 36);				blit(atlas, p[3], 612, 320, 0, 0, 24, 36);
	p[4] = create_bitmap(24, 36);				blit(atlas, p[4], 640, 320, 0, 0, 24, 36);
	p[5] = create_bitmap(24, 36);				blit(atlas, p[5], 668, 320, 0, 0, 24, 36);
	p[6] = create_bitmap(24, 36);				blit(atlas, p[6], 584, 368, 0, 0, 24, 36);
	p[7] = create_bitmap(24, 36);				blit(atlas, p[7], 612, 368, 0, 0, 24, 36);
	p[8] = create_bitmap(24, 36);				blit(atlas, p[8], 640, 368, 0, 0, 24, 36);
	p[9] = create_bitmap(24, 36);				blit(atlas, p[9], 668, 368, 0, 0, 24, 36);
	BITMAP *tablica = create_bitmap(226, 114);	blit(atlas, tablica, 6, 518, 0, 0, 226, 114);
	BITMAP *over = create_bitmap(192, 42);		blit(atlas, over, 790, 118, 0, 0, 192, 42);
	BITMAP *brown = create_bitmap(44, 44);		blit(atlas, brown, 224, 954, 0, 0, 44, 44);
	BITMAP *silver = create_bitmap(44, 44);		blit(atlas, silver, 224, 906, 0, 0, 44, 44);
	BITMAP *gold = create_bitmap(44, 44);		blit(atlas, gold, 242, 564, 0, 0, 44, 44);
	BITMAP *platyna = create_bitmap(44, 44);	blit(atlas, platyna, 516, 954, 0, 0, 44, 44);
	
	destroy_bitmap(atlas);
	SAMPLE *mach = load_sample("sfx_wing.wav");
	SAMPLE *hit = load_sample("sfx_die.wav");
	SAMPLE *point = load_sample("sfx_point.wav");
	SAMPLE *chuch = load_sample("sfx_swooshing.wav");
	
	int rekord = 0;
	bool pokazrekord = false;
	
	game:
	double y = 200, sy = 0;
	int rogx[6], rogy[6], odl = 0, pts = 0, ptak = 0;
	bool tempkey = false, bgday = rand()%2;
	
	if(bgday==true)	draw_sprite(screen, day, 0, SCREEN_H-512);
	else  			draw_sprite(screen, night, 0, SCREEN_H-512);
	pivot_sprite(screen, bird[0], 100, y, 17, 12, 0);
	draw_sprite(screen, ground, -odl%336, SCREEN_H-112);
	pivot_sprite(screen, push, SCREEN_W/2-57, SCREEN_H/2-45, 0, 0, 0);
	pivot_sprite(screen, ready, SCREEN_W/2-92, SCREEN_H/8, 0, 0, 0);
	
	for(int n=0;	n<6;	n++)
	{
		rogx[n] = SCREEN_W/2+n*156;
		rogy[n] = rand()%(SCREEN_H-(212+SCREEN_H/4))+SCREEN_H/8;
	}
	while(!(key[KEY_UP] || mouse_b & 1 || key[KEY_ESC]))	rest(1);
	while(!key[KEY_ESC])
	{
			if(bgday==true)	draw_sprite(bufor, day, -(int)(odl*0.1)%288, SCREEN_H-512);
			else			draw_sprite(bufor, night, -(int)(odl*0.1)%288, SCREEN_H-512);
			
			if((key[KEY_UP] || mouse_b & 1) && tempkey==false)
			{
				tempkey = true;
				sy = -5.15-pts*0.0025;
				play_sample(mach, 255, 127, 1000, 0);
			}
			
			if(!(key[KEY_UP] || mouse_b & 1))	tempkey = false;
			
			sy += 0.3;
			y += sy;
			odl+=2;
			ptak++;
			
			for(int n=0;	n<6;	n++)
			{
				rogx[n]-=2;
				if(rogx[n]<(-52))
				{
					rogx[n] = -52+6*156;
					rogy[n] = rand()%(SCREEN_H-(212+SCREEN_H/4))+SCREEN_H/8;
				}
				pivot_sprite(bufor, gora, rogx[n], rogy[n]-320, 0, 0, 0);
				pivot_sprite(bufor, dol, rogx[n], rogy[n]+100, 0, 0, 0);
				
				if((rogx[n]<117 && rogx[n]>31 && (y<rogy[n]+12 || y>rogy[n]+88)) || y>=SCREEN_H-112)
				{
	    			play_sample(hit, 255, 127, 1000, 0);
					sy = 0;
					int n = 0;
					while(1)
					{
		     			if(bgday==true)	draw_sprite(bufor, day, 0, SCREEN_H-512);
						else			draw_sprite(bufor, night, 0, SCREEN_H-512);
						sy += 0.3;
						y += sy;
						for(int i=0;	i<6;	i++)
						{
							pivot_sprite(bufor, gora, rogx[i], rogy[i]-320, 0, 0, 0);
							pivot_sprite(bufor, dol, rogx[i], rogy[i]+100, 0, 0, 0);
						}
						pivot_sprite(bufor, bird[0], 100, y, 17, 12, ftofix(sy*5));
						draw_sprite(bufor, ground, -odl%336, SCREEN_H-112);
						set_trans_blender(255,255,255, 255-n*20);
						if(n<13)    draw_trans_sprite(bufor, biel, 0, 0);
						n++;
						vsync();
						draw_sprite(screen, bufor, 0, 0);
						if(n==50)	goto gocd;
					}
					gocd:
					play_sample(chuch, 255, 127, 1000, 0);
					pivot_sprite(screen, over, SCREEN_W/2-96, SCREEN_H/8, 0, 0, 0);
					pivot_sprite(screen, tablica, SCREEN_W/2-113, SCREEN_H/2-57, 0, 0, 0);
					if(pts>=100)	pivot_sprite(screen, platyna, SCREEN_W/2-87, SCREEN_H/2-15, 0, 0, 0);	else
					if(pts>=30)		pivot_sprite(screen, gold, SCREEN_W/2-87, SCREEN_H/2-15, 0, 0, 0);		else
					if(pts>=10)		pivot_sprite(screen, silver, SCREEN_W/2-87, SCREEN_H/2-15, 0, 0, 0);	else
					if(pts>=3)		pivot_sprite(screen, brown, SCREEN_W/2-87, SCREEN_H/2-15, 0, 0, 0);
					if(pts>rekord)  rekord = pts;
					textprintf_right_ex(screen, font, 92+SCREEN_W/2, SCREEN_H/2-19, makecol(255,255,255), -1, "%d", pts);
					textprintf_right_ex(screen, font, 92+SCREEN_W/2, SCREEN_H/2+23, makecol(255,255,255), -1, "%d", rekord);
					if(pokazrekord==false)	textout_ex(screen, font, "Rekord jest wazny tylko do zamkniecia gry", 8, SCREEN_H-16, makecol(0,0,0), -1);
					pokazrekord = true;
					while(!(key[KEY_UP] || mouse_b & 1) && !key[KEY_ESC])    rest(10);
					goto game;
				}
				
				if(rogx[n]<=100 && rogx[n]>=99)
				{
					play_sample(point, 255, 127, 1000, 0);
					pts++;
				}
			}
			
	  		if(pts<10)	pivot_sprite(bufor, p[pts], SCREEN_W/2-12, 10, 0, 0, 0);
			else
			if(pts<100)
			{
				pivot_sprite(bufor, p[pts/10], SCREEN_W/2-25, 10, 0, 0, 0);
				pivot_sprite(bufor, p[pts%10], SCREEN_W/2+1, 10, 0, 0, 0);
			}
			else
			if(pts<100)
			{
				pivot_sprite(bufor, p[pts/100], SCREEN_W/2-38, 10, 0, 0, 0);
				pivot_sprite(bufor, p[(pts/10)%10], SCREEN_W/2-12, 10, 0, 0, 0);
				pivot_sprite(bufor, p[pts%10], SCREEN_W/2+14, 10, 0, 0, 0);
			}

			pivot_sprite(bufor, bird[(ptak/4)%4], 100, y, 17, 12, ftofix(sy*4));
			draw_sprite(bufor, ground, -(int)(odl*1.2)%336, SCREEN_H-112);
			vsync();
			draw_sprite(screen, bufor, 0, 0);
	}
	allegro_exit();
}
END_OF_MAIN();
