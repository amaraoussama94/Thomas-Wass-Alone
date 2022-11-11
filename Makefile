#main app
Thomas:   Engine.o TextureHolder.o  Input.o Update.o Draw.o Main.o PlayableCharacter.o  Thomas.o Bob.o
	g++ Engine.o TextureHolder.o  Input.o  Update.o Draw.o  Main.o  PlayableCharacter.o  Thomas.o  Bob.o -o Thomas -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


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

clean:
#cleanup all object file
	  -rm *.o $(objects) 


	  Thomas