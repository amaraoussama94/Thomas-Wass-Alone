#main app
Thomas:   ZombieArena.o CreateBackground.o  
	g++ ZombieArena.o CreateBackground.o   -o Thomas -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


ZombieArena.o:ZombieArena.cpp
	g++ -c ZombieArena.cpp

 
#Player class 
Player.o:Player.cpp
	g++ -c Player.cpp

#Backgroung function
CreateBackground.o:CreateBackground.cpp  
	g++ -c CreateBackground.cpp
 
 

clean:
#cleanup all object file
	  -rm *.o $(objects) 