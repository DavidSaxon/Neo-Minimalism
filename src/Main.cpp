#include <iostream>
#include <map>

#include "src/Utilities/ArgumentsUtil.hpp"
#include "src/Utilities/FileSystemUtil.hpp"

#include "src/engine/Engine.hpp"
#include "src/states/start_up/StartUp.hpp"

//TYPEDEFS
typedef std::map<std::string, bool*> FlagMap;
typedef std::pair<std::string, bool*> FlagPair;

//MAIN FUNCTION
int main(int argc, char* argv[]) {

    //Parse the command line arguments
	//flag booleans
    //is true if the the help text should be displayed
    bool help = false;

    //create a mapping from strings to flags
    FlagMap flagMap;
    flagMap.insert(FlagPair("h", &help));

    //create a vector to contain all the argument strings
    std::vector<std::string> arguments;

    //parse the arguments
    try {

        arguments = util::arg::parseCmdLineArguments(argc, argv, flagMap);
    }
    catch (util::ex::Exception& e) {

        //print the error to console then exit
        std::cout << "ERROR: " << e.getMessage() << std::endl;
        return -1;
    }

    //display the help and exit
    if (help) {

        try {

            util::file::printFile("res/info/help.txt", std::cout);
            return 0;
        }
        catch (...) {

            //report the error and exit
            std::cout << "ERROR: help file is missing or corrupt" << std::endl;
            return -2;
        }
    }

    //create a new display
    SharedDisplay display(new DisplaySurface(util::vec::Vector2D(1600, 900), false));
    //SharedDisplay display(new DisplaySurface(util::vec::Vector2D(0, 0), true));

    //create the start up engine
    SharedSubEngine startUp(new StartUp());

    //create a new game engine
    Engine engine(display, startUp);

    //initialise
    try {

        engine.init();
    }
    catch(util::ex::Exception& e) {

        //report error and exit
        std::cout << "ERROR: Omicron initialisation failed:\n" <<
            e.getMessage() << std::endl;
        return -3;
    }

    //execute
    try {

        engine.execute();
    }
    catch (util::ex::Exception& e) {

        //report error and exit
        std::cout << "ERROR: Omicron execution failure:\n" <<
            e.getMessage() << std::endl;
        return -4;
    }

	return 0;
}