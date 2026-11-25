#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <map>
#include <string>
#include <vector>
#include <sstream>


void displayTimesUp (){
    std::cout << R"(
      $$$$$$$$\\$$\                                                                   $$\       
      \__$$  __|\__|                                                                  $$ |      
         $$ |   $$\ $$$$$$\$$$$\   $$$$$$\   $$$$$$$\       $$\   $$\  $$$$$$\        $$ |      
         $$ |   $$ |$$  _$$  _$$\ $$  __$$\ $$  _____|      $$ |  $$ |$$  __$$\       $$ |      
         $$ |   $$ |$$ / $$ / $$ |$$$$$$$$ |\$$$$$$\        $$ |  $$ |$$ /  $$ |      \__|      
         $$ |   $$ |$$ | $$ | $$ |$$   ____| \____$$\       $$ |  $$ |$$ |  $$ |                
         $$ |   $$ |$$ | $$ | $$ |\$$$$$$$\ $$$$$$$  |      \$$$$$$  |$$$$$$$  |      $$\       
         \__|   \__|\__| \__| \__| \_______|\_______/        \______/ $$  ____/       \__|      
                                                                      $$ |                      
                                                                      $$ |                      
                                                                      \__|                      
      )" << std::endl;
}

using namespace std::chrono_literals;
int main() {
    std::map<char, std::vector<std::string>> digits = {
    {'0', {
        R"( $$$$$$\  )",
        R"($$$ __$$\ )",
        R"($$$$\ $$ |)",
        R"($$\$$\$$ |)",
        R"($$ \$$$$ |)",
        R"($$ |\$$$ |)",
        R"(\$$$$$$  /)",
        R"( \______/ )"
    }},

    {'1', {
        R"(  $$\   )",
        R"($$$$ |  )",
        R"(\_$$ |  )",
        R"(  $$ |  )",
        R"(  $$ |  )",
        R"(  $$ |  )",
        R"($$$$$$\ )",
        R"(\______|)"
    }},

    {'2', {
        R"( $$$$$$\  )",
        R"($$  __$$\ )",
        R"(\__/  $$ |)",
        R"( $$$$$$  |)",
        R"($$  ____/ )",
        R"($$ |      )",
        R"($$$$$$$$\ )",
        R"(\________|)"
    }},

    {'3', {
        R"( $$$$$$\  )",
        R"($$ ___$$\ )",
        R"(\_/   $$ |)",
        R"(  $$$$$ / )",
        R"(  \___$$\ )",
        R"($$\   $$ |)",
        R"(\$$$$$$  |)",
        R"( \______/ )"
    }},

    {'4', {
        R"($$\   $$\ )",
        R"($$ |  $$ |)",
        R"($$ |  $$ |)",
        R"($$$$$$$$ |)",
        R"(\_____$$ |)",
        R"(      $$ |)",
        R"(      $$ |)",
        R"(      \__|)"
    }},

    {'5', {
        R"($$$$$$$\  )",
        R"($$  ____| )",
        R"($$ |      )",
        R"($$$$$$$\  )",
        R"(\_____$$\ )",
        R"($$\   $$ |)",
        R"(\$$$$$$  |)",
        R"( \______/ )"
    }},

    {'6', {
        R"( $$$$$$\  )",
        R"($$  __$$\ )",
        R"($$ /  \__|)",
        R"($$$$$$$\  )",
        R"($$  __$$\ )",
        R"($$ /  $$ |)",
        R"( $$$$$$  |)",
        R"( \______/ )"
    }},

    {'7', {
        R"($$$$$$$$\ )",
        R"(\____$$  |)",
        R"(    $$  / )",
        R"(   $$  /  )",
        R"(  $$  /   )",
        R"( $$  /    )",
        R"($$  /     )",
        R"(\__/      )"
    }},

    {'8', {
        R"( $$$$$$\  )",
        R"($$  __$$\ )",
        R"($$ /  $$ |)",
        R"( $$$$$$  |)",
        R"($$  __$$< )",
        R"($$ /  $$ |)",
        R"(\$$$$$$  |)",
        R"( \______/ )"
    }},

    {'9', {
        R"( $$$$$$\  )",
        R"($$  __$$\ )",
        R"($$ /  $$ |)",
        R"(\$$$$$$$ |)",
        R"( \____$$ |)",
        R"($$\   $$ |)",
        R"(\$$$$$$  |)",
        R"( \______/ )"
    }},

    {':', {
        R"(    )",
        R"(    )",
        R"($$\ )",
        R"(\__|)",
        R"(    )",
        R"($$\ )",
        R"(\__|)",
        R"(    )"
    }}
};
    

    int input = 0;
    std::cout << "enter a time (in minutes): " ;
    std::cin >> input;
    
    const auto minutes = std::chrono::minutes(input);  
    const auto start = std::chrono::steady_clock::now();
    auto time_left = minutes - (std::chrono::steady_clock::now() - start);
    std::ostringstream oss;
    struct winsize w;
    

    while (time_left > 0s) {
      system("clear");
        //printf ("lines %d\n", w.ws_row);
        //printf ("columns %d\n", w.ws_col);
       // find middle position

               
       oss.str("");
       oss.clear();
        /*for (int i = 0; i < (w.ws_row/2); i++){
          std::cout << "\n";
        }
        for (int i = 0; i < (w.ws_col/2); i++){
          std::cout << " ";
        }
        */
       ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
       const auto total_secs = std::chrono::ceil<std::chrono::seconds>(time_left);
       const auto hrs = std::chrono::duration_cast<std::chrono::hours>(total_secs);
       const auto mins = std::chrono::duration_cast<std::chrono::minutes>(total_secs - hrs);
       const auto secs = total_secs - hrs - mins;
              oss << std::setfill('0') << std::setw(2) << hrs.count() << ":"
                  << std::setfill('0') << std::setw(2) << mins.count() << ":"
                  << std::setfill('0') << std::setw(2) << secs.count();
        
        std::string timeStr = oss.str();
          for (int i = 0; i < (w.ws_row/2)-8; i++){
            std::cout << "\n";
          }

        for (int row = 0; row < 8; row++){
            for (int i = 0; i < (w.ws_col/2)-36; i++){
              std::cout << " ";
            }
            for (int col = 0; col < timeStr.length(); col++){
              std::cout << digits[timeStr[col]][row] << " ";
            }
            std::cout << "\n";
        }

        std::cout << std::flush;


      //std::this_thread::sleep_for (std::chrono::seconds(1));
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

      time_left = minutes - (std::chrono::steady_clock::now() - start);
      system("clear");

     
    }
    displayTimesUp();
    return 0;
}
