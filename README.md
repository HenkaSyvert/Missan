# Missan

/////// How to run in visual studio /////////////////////////

1. Create Folder named "Missan"
2. open visual studio, click "clone repository"
    * link = https://github.com/HenkaSyvert/Missan
    * local path = the Missan folder
5. build solution
6. run in debug (press F5)


//// How to make a game using MissanEngine /////////////

1. since MissanEngine is not a library yet, make a folder
  in MissanEngine, same level as MissanGame, and place your
  game there and pretend MissanEngine is a library.
2. YOU make the main() function
3. include missan.hpp to reach MissanEngine API
4. structure the game in this order:
  * Engine::Initialize();
  * Scene scene;
  * // add gameobjects to scene, including writing scripts for gameobjects
  * // see MissanGame for examples
  * Engine::SetActiveScene(scene);
  * Engine::Run();
  * Engine::Terminate();
