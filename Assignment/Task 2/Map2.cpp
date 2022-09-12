#include "Map2.h"



// Helping Function
std::vector<std::string> TaskFilter(std::string inputFile){
    std::ifstream dirty;
    dirty.open("wlist_all/"+inputFile);
    std::string word;

    std::vector<std::string> wordlist;
    while(std::getline(dirty,word)){
        std::regex r("[^0-9a-zA-Z]+");
        std::string cleanedWord = std::regex_replace(word, r,"");
        if(cleanedWord!="") {

            wordlist.push_back(cleanedWord);
        }

    }
    std::sort(wordlist.begin(),wordlist.end());
    return wordlist;
}
// Helping Function
bool comparator(std::string a, std::string b){
    return a[2]<b[2];
}
// Helping Function
std::vector<std::string> sorter(std::vector<std::string> wl){
    std::sort(wl.begin(),wl.end(), comparator);
    return wl;
}

void Map2(){

    std::vector<std::string> wl1;
    std::vector<std::string> wl2;
    DIR *dir; struct dirent *diread;
    std::vector<std::string> files;

    if ((dir = opendir("wlist_all")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");

    }
    files.erase(files.begin());
    files.erase(files.begin());
    std::sort(files.begin(),files.end());
    int numberOfFiles = files.size();


    for(int a =0; a<numberOfFiles/2;a++) {
        pid_t pid = fork();
        if (pid == -1) {
            std::perror("fork");
            exit(1);
        } else if (pid == 0) {
            wl1 = sorter(TaskFilter( files.at(a)));
            std::ofstream clean1;
            clean1.open("wlist_all/"+files.at(a));
            for(auto x : wl1){
                if(x.size()>=2 && x.size()<=15) {
                    clean1 << x << "\n";
                }
            }
            clean1.close();


            break;
        }
        
        else if(pid>0) {

            wl2 =sorter(TaskFilter( files.at(11-a)));
            std::ofstream clean1;
            clean1.open("wlist_all/"+files.at(11-a));
            for(auto x : wl2){
                if(x.size()>2 && x.size()<=15) {
                    clean1 << x << "\n";
                }
            }
            clean1.close();
            wait(0);


        }
    }

}

void reduce(){
    std::vector<std::string> wl1;
    DIR *dir; struct dirent *diread;
    std::vector<std::string> files;

    if ((dir = opendir("wlist_all")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");

    }
    files.erase(files.begin());
    files.erase(files.begin());
    std::sort(files.begin(),files.end());
    std::string word;
    std::vector<std::string> wordlist;
    for(auto x: files){

        std::ifstream file;
        file.open("wlist_all/"+x);
        while(std::getline(file,word)){
            wordlist.push_back(word);
        }
    }
    std::sort(wordlist.begin(),wordlist.end());
    std::set<std::string> wordlist_unique(wordlist.begin(), wordlist.end());

    std::ofstream merged;
    merged.open("merged.txt");
    for(auto x: wordlist_unique){
        merged<< x<<"\n";
    }
}


int main(int argc, char **argv){

    time_t start, end;
    time(&start);
    std::ios_base::sync_with_stdio(false);

    Map2();
    reduce();

    time(&end);
    double time_taken = double(end - start);
    std::cout << "Total time taken:  "
              << time_taken << std::setprecision(5);
    std::cout << " s " << std::endl;

    return 0;
}