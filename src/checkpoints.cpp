#include <checkpoints.hpp>

int checkpointNum = 1;
int errorNum = 1;
void checkpoint(const std::string& str){
    std::cout <<"\n\n" <<  "Checkpoint  " << checkpointNum++ << " " << str << "\n\n";
}
void reportError(const std::string& err){
     std::cout <<"\n\n" <<  "Error: " << errorNum++ << " " << err << "\n\n";
}