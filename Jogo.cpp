#include "Jogo.h"


Jogo::Jogo()
{
	
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	
	uniInicializar(800, 600, false);

	/*this->inORout.open("assets_all.txt", ios::in);
	if (!inORout.is_open())
	{
		gDebug.erro("Don't opened the file", this);
	}
	else
	{
		//Load Resources

		LoadingResources * Ld_R = new LoadingResources;
		if (!Ld_R->Loader(inORout)) 
		{
			gDebug.erro("Error in loading resources");
		}
		inORout.close(); 
	}*/
	
	//Maps

	mapa.carregar("assets/tilemaps/mapa.json");
	mapa2.carregar("assets/tilemaps/mapa2.json");
	
	//SpriteSheets Person

	gRecursos.carregarSpriteSheet("knight", "assets/spritesheets/Knight.png", 4, 4);
	gRecursos.carregarSpriteSheet("mage", "assets/spritesheets/mage.png", 4, 4);
	gRecursos.carregarSpriteSheet("thief", "assets/spritesheets/thief.png", 4, 4);
	gRecursos.carregarSpriteSheet("sound", "assets/spritesheets/sound.png", 2, 1);

	//Sounds
	
	LoadS.LoadSongs();

	Btn.setSpriteSheet("sound");

	Theme.setThemeSong("Kings_Feast");

	// Knight
	Class[0] = new Knight();
	Class[0]->setSpriteSheet("knight");
		
	// Mage
	
	Class[1] = new Mage();
	Class[1]->setSpriteSheet("mage");
   
	// Thief
   
	Class[2] = new Thief();
	Class[2]->setSpriteSheet("thief");

		
	ObjetoTileMap * ObjPos, *ObjPos2;
	ObjPos = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Pos1"); //ObjPos = map getLayerOfObjects("string") and point to getObject("string");
	ObjPos2 = mapa2.getCamadaDeObjetos("Objetos")->getObjeto("Pos1");
	
	
	Class[0]->setPosCentro(ObjPos->getPosCentro());	// Character type pointer indicate to set position in center (ObjPos point to get position in center).
	Class[0]->setPosCentro(ObjPos2->getPosCentro());
	
	
	//Ground4 and Ground5 collision layers.
	//Ground5 nvl2
	
	
}

void Jogo::finalizar()
{
	gRecursos.descarregarTudo();
	mapa.descarregar();
		
	
	uniFinalizar();
}

void Jogo::executar()
{			
	int x = 0;
		
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{			
		uniIniciarFrame();
		
		//Change Map 

		if (x >= 0 && x <= 1)
		{
			mapa.desenhar();			
		}
		else
		{				
			mapa2.desenhar();
		}
				

		//Switch Character.

		if (gTeclado.soltou[TECLA_1])
		{
			x = 0;
		}

		if (gTeclado.soltou[TECLA_2])
		{
			x = 1;
		}

		if (gTeclado.soltou[TECLA_3])
		{
			x = 2;
											
		}
				
		//Person

		Class[x]->draw();
		
		Class[x]->update();
		
		
		//Button

		Btn.desenhar(780, 10);
		
		bool Mute = true;
		if (Mute == true)
		{

		}
		
		if (gMouse.soltou[BOTAO_MOUSE_ESQ]) //Muted.
		{				
			Btn.setAnimacao(1, false);
			Btn.avancarAnimacao();
			gMusica.setVolumeGlobal(0);			
		}		
		if(gMouse.soltou[BOTAO_MOUSE_DIR])
		{
			Btn.setAnimacao(0, false);
			Btn.avancarAnimacao();
			gMusica.setVolumeGlobal(50);
		}
		
		uniTerminarFrame();
	}
}