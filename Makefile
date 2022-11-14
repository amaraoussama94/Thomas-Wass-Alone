#main app
Thomas:   Engine.o TextureHolder.o  Input.o Update.o Draw.o Main.o PlayableCharacter.o  Thomas.o  Bob.o  LevelManager.o LoadLevel.o DetectCollisions.o SoundManager.o
	g++ Engine.o TextureHolder.o  Input.o  Update.o Draw.o  Main.o  PlayableCharacter.o  Thomas.o  Bob.o  LevelManager.o  LoadLevel.o DetectCollisions.o SoundManager.o -o Thomas -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


Engine.o:Engine.cpp
	g++ -c Engine.cpp

	
#Engine Function
Input.o:Input.cpp
	g++ -c Input.cpp 


Update.o:Update.cpp
	g++ -c Update.cpp 


Draw.o:Draw.cpp
	g++ -c Draw.cpp 


#Texture Holder
TextureHolder.o:TextureHolder.cpp  
	g++ -c TextureHolder.cpp
 
#Main Function
Main.o:Main.cpp  
	g++ -c Main.cpp


#Playable Character  class
PlayableCharacter.o:PlayableCharacter.cpp  
	g++ -c PlayableCharacter.cpp

#Thomas class
Thomas.o:Thomas.cpp  
	g++ -c Thomas.cpp

#Bob class
Bob.o:Bob.cpp  
	g++ -c Bob.cpp



#Level Manager class
LevelManager.o:LevelManager.cpp  
	g++ -c LevelManager.cpp

 
LoadLevel.o:LoadLevel.cpp  
	g++ -c LoadLevel.cpp

#Detect Collisions class
DetectCollisions.o:DetectCollisions.cpp  
	g++ -c DetectCollisions.cpp

#SoundManager class
SoundManager.o:SoundManager.cpp  
	g++ -c SoundManager.cpp
clean:
#cleanup all object file
	  -rm *.o $(objects) 

