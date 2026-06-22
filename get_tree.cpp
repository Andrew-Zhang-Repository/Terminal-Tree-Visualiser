
#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;
using namespace std::filesystem;

void print_tree(const path& target_path, int depth);
void sort_items(vector<directory_entry> &items);



int main() {
    
    print_tree(".",0);

}

void print_tree(const path& target_path, int depth = 0){

    if (depth == 0){

        std::cout << string(depth,' ') << "├──" << canonical(target_path.filename()) << std::endl;
        depth++;

    }

    // Gather items in root directory
    path parent_dir = target_path;
    vector<directory_entry> items = {};
    

    if (exists(parent_dir) && is_directory(parent_dir)){

        for (auto& nig : directory_iterator(parent_dir)){
            if (nig.path().filename() == ".git"){
                continue;
            }
            items.push_back(nig);
        }

    }

    // Sort in directory order
    sort_items(items);

    // Print logic
    for (int i = 0; i < items.size(); i++){

        auto curr = items[i];

        if (i == items.size() - 1){
            std::cout << string(depth,' ') << "└──" << curr.path().filename() << std::endl;
        }
        else{
            std::cout << string(depth,' ') << "├──" << curr.path().filename() << std::endl;
        }

        if (std::filesystem::is_directory(curr.path())) {
            print_tree(curr, depth + 1); 
        }
        



    }



}

void sort_items(vector<directory_entry> &items){

    sort(items.begin(), items.end(), [](const directory_entry& a, const directory_entry& b) {

        if (is_directory(a) && !is_directory(b)){
            return true;
        }
        else if (is_directory(b) && !is_directory(a)){
            return false;
        }
        else{
            string ass = a.path().filename().string();
            string bass = b.path().filename().string();
            transform(ass.begin(), ass.end(), ass.begin(), [](unsigned char c) {
                return static_cast<char>(tolower(c));}
            );
            transform(bass.begin(), bass.end(), bass.begin(), [](unsigned char c) {
                return static_cast<char>(tolower(c));}
            );
            return ass < bass;
        }

  
    });

}