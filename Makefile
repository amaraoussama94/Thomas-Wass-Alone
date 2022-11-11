#main app
Zombie:   ZombieArena.o CreateBackground.o Player.o  TextureHolder.o  Zombie.o CreateHorde.o Bullet.o Pickup.o
	g++ ZombieArena.o CreateBackground.o Player.o   TextureHolder.o Zombie.o CreateHorde.o Bullet.o Pickup.o -o Zombie -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


ZombieArena.o:ZombieArena.cpp
	g++ -c ZombieArena.cpp

 
#Player class 
Player.o:Player.cpp
	g++ -c Player.cpp

#Backgroung function
CreateBackground.o:CreateBackground.cpp  
	g++ -c CreateBackground.cpp

#Texture holder for  zombies
TextureHolder.o:TextureHolder.cpp  
	g++ -c TextureHolder.cpp


#TZombie class
Zombie.o:Zombie.cpp  
	g++ -c Zombie.cpp

#Create Horde
CreateHorde.o:CreateHorde.cpp  
	g++ -c CreateHorde.cpp

#Bullet class
Bullet.o:Bullet.cpp  
	g++ -c Bullet.cpp

#Pickup class  
Pickup.o:Pickup.cpp  
	g++ -c Pickup.cpp

clean:
#cleanup all object file
	  -rm *.o $(objects) 