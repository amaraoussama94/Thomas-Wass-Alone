#main app
Thomas:   Engine.o TextureHolder.o  Input.o
	g++ Engine.o TextureHolder.o  Input.o -o Thomas -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


Engine.o:Engine.cpp
	g++ -c Engine.cpp

	
#Input  Function
Input.o:Input.cpp
	g++ -c Input.cpp 

#Texture Holder
TextureHolder.o:TextureHolder.cpp  
	g++ -c TextureHolder.cpp
 


clean:
#cleanup all object file
	  -rm *.o $(objects) 