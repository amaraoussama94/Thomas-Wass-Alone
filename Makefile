#main app
Thomas:   Engine.o TextureHolder.o  Input.o Update.o Draw.o
	g++ Engine.o TextureHolder.o  Input.o  Update.o Draw.o -o Thomas -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


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
 


clean:
#cleanup all object file
	  -rm *.o $(objects) 