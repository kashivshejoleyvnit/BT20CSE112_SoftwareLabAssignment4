#include"heap_manager.h"
vector<vector<int>> free_list;
vector<vector<int>> filled_list;
extern int free_space;
extern int filled_space;
extern int merged_space;
extern int freed_space;
int near_index;
void display(vector<vector<int>> v){
    cout<<"{ ";
    for(auto x : v)
    {
        cout<<"{ ";
        for(auto y : x)
        {
            cout<<y<<" ";
        }
        cout<<"}";
    }
    cout<<"}";
}
int near(int size){
    bool found = false;
    int ans = 2;
    for(int i=0;!found;i++){
        if(ans>size){
            found = true;
            return i;
        }
        ans = ans*2;
    }
}
void fill_list(vector<vector<int>>& v,int k){
    for(int i=0;i<=k;i++){
        v[i] = {};
    }
}
int fun(int index){
    free_list[index].erase(find(free_list[index].begin(),free_list[index].end(),free_list[index][0]));
    filled_list[index].push_back(free_list[index][0]);
}
int arrange(int demand,int index){
    int ans;
    free_list[index-1].push_back(free_list[index][0]);
    free_list[index-1].push_back(free_list[index][0]+pow(2,index-1));
    free_list[index].erase(find(free_list[index].begin(),free_list[index].end(),free_list[index][0]));
    if(demand == pow(2,index-1)){
        filled_list[index-1].push_back(free_list[index-1][0]);
        ans = free_list[index-1][0];
        free_list[index-1].erase(find(free_list[index-1].begin(),free_list[index-1].end(),free_list[index-1][0]));
        return ans;
    }
    else{
        arrange(demand,index-1);
    }
}
int allocate_request(int demand,int index,bool x=true){
    int ans=-1;
    if(free_list[index].size() != 0 && x==true){
        free_list[index].erase(find(free_list[index].begin(),free_list[index].end(),free_list[index][0]));
        filled_list[index].push_back(free_list[index][0]);
        return free_list[index][0];
    }
    else if(free_list[index].size() != 0){
        ans = arrange(demand,index);
    }
    else{
        ans = allocate_request(demand,index+1,false);
    }
    return ans;
}
int is_there(vector<vector<int>> v,int k){
    int index = -1;
    bool found = false;
    for(int j=0;j<v.size() && !found;j++){
        auto i = find(v[j].begin(),v[j].end(),k);
        if(i!= v[j].end()){
            found = true;
            index = j;
        }
    }
    return index;
}
int allocate(int request){
    if(request<=0){
        cout<<"invalid request";
        return -1;
    }
    else if(request > pow(2,near_index)){
        cout<<"invalid request";
        return -1;
    }
    else{
        int index = near(request);
        int demand;
        if(pow(2,index)!=request){
            demand = pow(2,index+1);
            index++;
        }
        else
            demand = pow(2,index);
        int ans = allocate_request(demand,index);
        if(ans!=-1)
        {
            free_space = free_space-demand;
            filled_space += demand;
        }
        return ans;
    }
}
void merge(int address,int index){
    int x = address+pow(2,index);
    auto p = find(free_list[index].begin(),free_list[index].end(),x);
    auto j = find(free_list[index].begin(),free_list[index].end(),address-pow(2,index));
    if(j!= free_list[index].end()){
        x = address - pow(2,index);
        address = x;
    }
    if(j==free_list[index].end()&&p==free_list[index].end()){
        free_list[index].push_back(address);
        merged_space += pow(2,index-1);
    }
    else{
        free_list[index].erase(find(free_list[index].begin(),free_list[index].end(),x));
        merge(address,index+1);
    }
}
void deallocate(int address){
    int index = is_there(filled_list,address);
    if(index != -1){
        filled_space -= pow(2,index);
        free_space += pow(2,index);
        freed_space += pow(2,index);
        filled_list[index].erase(find(filled_list[index].begin(),filled_list[index].end(),address));
        merge(address,index);
    }
}
void init(){
    int size;
    size = 100;
    near_index = near(size);
    free_space = pow(2,near_index);
    filled_space = 0;
    merged_space = 0;
    freed_space = 0;
    free_list.resize(near_index+1);
    filled_list.resize(near_index+1);
    fill_list(free_list,near_index);
    fill_list(filled_list,near_index);
    free_list.at(near_index) = {0};
}