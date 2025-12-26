//[INCLUDES]
#include <iostream>

#include "../inc/utils/log.hpp"
#include "../inc/console.hpp"

#include "../inc/utils/process.hpp"

#include "../inc/data/userman.hpp"

//[MAIN ENTRY]
int main(int argc, char** argv)
{
    //SETUP PROCESS
    Process::Setup();
    
    //BEGIN
    Log::Message(" /$$$$$$$  /$$$$$$$  /$$$$$$$$ /$$    /$$ /$$$$$$$$ /$$$$$$$ ");
    Log::Message("| $$__  $$| $$__  $$| $$_____/| $$   | $$| $$_____/| $$__  $$");
    Log::Message("| $$  \\ $$| $$  \\ $$| $$      | $$   | $$| $$      | $$  \\ $$");
    Log::Message("| $$  | $$| $$$$$$$/| $$$$$   |  $$ / $$/| $$$$$   | $$$$$$$/");
    Log::Message("| $$  | $$| $$__  $$| $$__/    \\  $$ $$/ | $$__/   | $$__  $$");
    Log::Message("| $$  | $$| $$  \\ $$| $$        \\  $$$/  | $$      | $$  \\ $$");
    Log::Message("| $$$$$$$/| $$  | $$| $$$$$$$$   \\  $/   | $$$$$$$$| $$  | $$");
    Log::Message("|_______/ |__/  |__/|________/    \\_/    |________/|__/  |__/");
    Log::Message("================================================================");

    //INITIALIZE SYSTEMS
    Userman::Initialize();


    //Exit
    return 0;
}
