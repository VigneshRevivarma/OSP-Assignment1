#include "Task3.h"
#include <fcntl.h>
#include <pthread.h>
#define THREAD_NUM 12


std::vector<std::string> TaskFilterModified(std::string inputFile){
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

bool comparator2(int a, int b){
    return global[a][2]<global[b][2];
}

std::vector<int> sorter2(std::vector<int> wl){
    std::sort(wl.begin(),wl.end() ,comparator2);
    return wl;
}

void * map3(void * args){
    std::vector<std::string> wl;
    std::string file = *((std::string*)args);
    wl = TaskFilterModified(file);
    int limit = wl.size()-1;
    for(int x=0; x<limit;x++){
        global.push_back(wl[x]);
        indexes.push_back(x);
    }
    indexes = sorter2(indexes);
    std::ofstream clean1;
    clean1.open("wlist_all/"+file);
    for(auto x : indexes){
        std::string word = global[x];
        if(word.size()>2 && word.size()<=15) {
            clean1 << word << "\n";
        }
    }
    clean1.close();
    global.clear();
    indexes.clear();
    pthread_exit(NULL);
}


void reduce3(std::vector<std::string> files) {
    std::vector<std::string> wordlist;
    std::string word;
    for(auto x: files){
        std::ifstream file;
        file.open("wlist_all/"+x);
        while(std::getline(file,word)){
            wordlist.push_back(word);
        }
    }
    std::sort(wordlist.begin(), wordlist.end());
    std::set<std::string> wordlist_unique(wordlist.begin(), wordlist.end());
    const char * myfifo ="/merged.txt";
    mkfifo(myfifo, 0666);
    int fd = open(myfifo,O_WRONLY);
    for (auto x: wordlist_unique) {
        const char * word= (x+ "\n").c_str();
        write(fd,word, strlen(word)+1);
    }
    close(fd);
}



int main(int argc, char** argv) {

    pthread_t pid[THREAD_NUM];
    DIR *dir;
    struct dirent *diread;
    std::vector<std::string> files;
    if ((dir = opendir("wlist_all")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir(dir);
    } 
    else 
    {
        perror("opendir");
    }
    files.erase(files.begin());
    files.erase(files.begin());
    std::sort(files.begin(), files.end());

    for (int x = 0; x < THREAD_NUM; x++) 
    {
        std::ios_base::sync_with_stdio(false);
        std::string file = files.at(x);
        std::string *argument = &(file);
        int rv = pthread_create(&pid[x], NULL, &map3, (void *) (argument));
        if (rv < 0) {
            perror("Failed to create Thread!!!");
            exit(0);
        }
    }
    for (int i = 0; i < THREAD_NUM; i++) 
    {
        time_t start, end;
        time(&start);
        std::ios_base::sync_with_stdio(false);
        pthread_join(pid[i], NULL);
        time(&end);
    
    double time_taken = double(end - start);
    std::cout << "Time taken: "<< files[i]<<" file: " << std::fixed
              << time_taken << std::setprecision(5);
    std::cout << " s " << std::endl;
    }

    reduce3(files);
    return 0;
}
