/*FLUTURE Robert-Gabriel 313CB*/
#include "utils.h"

ADir AllocDir(){


    ADir d = malloc(sizeof(struct directory));
    if(!d){
        return NULL;
    }

    d->name =  malloc(sizeof(char)*50);
    if(!d->name){
        free(d);
        return NULL;
    }

    d->FRoot = NULL;

    d->SDRoot = NULL;

    d->parent = NULL;

    d->st = NULL;

    d->dr = NULL;

    return d;
}

AFile AllocFile(){

    AFile f = malloc(sizeof(struct file));
    if(!f){
        return NULL;
    }
    f->name = malloc(sizeof(char)*50);
    if(!f->name){
        free(f);
        return NULL;
    }

    f->parent = NULL;

    f->st = NULL;

    f->dr = NULL;

    return f;
}

ADir InitRoot(){

    ADir root = AllocDir();
    if(!root){
        return NULL;
    }
    strcpy(root->name,"root\0");
    return root;
}

int InsertDir(ADir root, ADir dir){
    
    char* el = dir->name;

    ADir SDroot = root->SDRoot;

    if (SDroot == NULL){
        root->SDRoot = dir;
        return 1;
    }

    ADir Parent = NULL;

    while(SDroot){
    
        if( strcmp(el, SDroot->name) < 0){

            Parent = SDroot;

            SDroot = SDroot->st;

            continue;

        }

        if( strcmp(el, SDroot->name) > 0){

            Parent = SDroot;

            SDroot = SDroot->dr;

            continue;

        }

        if( strcmp(el, SDroot->name) == 0){

            return 0;
        }
    }

    if( strcmp(el, Parent->name) < 0){
        Parent->st = dir;
    }else{
        Parent->dr = dir;
    }

    return 1;
}

int InsertFile(ADir root, AFile file){
    
    char* el = file->name;

    AFile Froot = root->FRoot;

    if (Froot == NULL){
        root->FRoot = file;
        return 1;
    }

    AFile Parent = NULL;

    while(Froot){
    
        if( strcmp(el, Froot->name) < 0){

            Parent = Froot;

            Froot = Froot->st;

            continue;

        }

        if( strcmp(el, Froot->name) > 0){

            Parent = Froot;

            Froot = Froot->dr;

            continue;

        }

        if( strcmp(el, Froot->name) == 0){

            return 0;
        }
    }

    if( strcmp(el, Parent->name) < 0){
        Parent->st = file;
    }else{
        Parent->dr = file;
    }

    return 1;
}

int SearchFileName(char* name, AFile root){

    while(root){

        if(strcmp(name,root->name) == 0){
            return 0;
        }

        if(strcmp(name,root->name) < 0){
            root = root->st;
            continue;
        }

        if(strcmp(name,root->name) > 0){
            root = root->dr;
            continue;
        }
    }

    return 1;
}

int SearchDirName(char* name, ADir root){

    while(root){

        if(strcmp(name,root->name) == 0){
            return 0;
        }

        if(strcmp(name,root->name) < 0){
            root = root->st;
            continue;
        }

        if(strcmp(name,root->name) > 0){
            root = root->dr;
            continue;
        }
    }

    return 1;
}

void InorderTreePrint_d(ADir node){

    if (node  == NULL ){
        return;
    }

    InorderTreePrint_d(node->st);
    printf("%s ",node->name);
    InorderTreePrint_d(node->dr);

}

void InorderTreePrint_f(AFile node){

    if (node  == NULL ){
        return;
    }

    InorderTreePrint_f(node->st);
    printf("%s ",node->name);
    InorderTreePrint_f(node->dr);

}

void InorderTreePrint_d_Hidden(ADir node){

    if (node  == NULL ){
        return;
    }

    InorderTreePrint_d_Hidden(node->st);
    if(node->name[0] != '.'){
        printf("%s ",node->name);
    }
    InorderTreePrint_d_Hidden(node->dr);

}

void InorderTreePrint_f_Hidden(AFile node){

    if (node  == NULL ){
        return;
    }

    InorderTreePrint_f_Hidden(node->st);
    if((node->name)[0] != '.'){
        printf("%s ",node->name);
    }
    InorderTreePrint_f_Hidden(node->dr);

}

void InorderTreePrint_2(AFile node, int lvl){

    if (node  == NULL ){
        return;
    }

    InorderTreePrint_2(node->st,lvl);
    for(int i = lvl; i > 1; i--){
            printf("   ");
        }
        printf("|--");
  
        
    
    printf("%s\n",node->name);
    InorderTreePrint_2(node->dr,lvl);

}

ADir ValMin_d(ADir root){

    while( (root != NULL) && (root->st != NULL) ){
        root = root->st;
    }
    return root;
}

AFile ValMin_f(AFile root){

    while( (root != NULL) && (root->st != NULL) ){
        root = root->st;
    }
    return root;
}

ADir deleteNode_d(ADir root, char* name,int* found)
{
   
    if (root == NULL){
        return root;
    }
    
    if (strcmp(name,root->name) < 0){
        root->st = deleteNode_d(root->st, name, found);
    
    }else if (strcmp(name,root->name) > 0){
        root->dr = deleteNode_d(root->dr, name, found);
 
    }else {

        *found = 1;

        if (root->st == NULL) {
            ADir aux = root->dr;
            ResetRoot(root->SDRoot);
            FreeFileTree(root->FRoot);
            free(root->name);
            free(root);
            return aux;

        }else if (root->dr == NULL) {
            ADir aux = root->st;
            ResetRoot(root->SDRoot);
            FreeFileTree(root->FRoot);
            free(root->name);
            free(root);
            return aux;
        }

        ADir aux = ValMin_d(root->dr);
        strcpy(root->name,aux->name);         
        root->dr = deleteNode_d(root->dr, aux->name, found);
    }
    return root;
}

AFile deleteNode_f(AFile root, char* name, int* found)
{
   
    if (root == NULL){
        return root;
    }
    
    if (strcmp(name,root->name) < 0){
        root->st = deleteNode_f(root->st, name, found);
    
    }else if (strcmp(name,root->name) > 0){
        root->dr = deleteNode_f(root->dr, name, found);
 
    }else {

        *found = 1;

        if (root->st == NULL) {
            AFile aux = root->dr;
            free(root->name);
            free(root);
            return aux;

        }else if (root->dr == NULL) {
            AFile aux = root->st;
            free(root->name);
            free(root);
            return aux;
        }

        AFile aux = ValMin_f(root->dr);
        strcpy(root->name,aux->name);         
        root->dr = deleteNode_f(root->dr, aux->name, found);
    }
    return root;
}

ADir SearchDirAddress(char* name, ADir root){

    while(root){

        if(strcmp(name,root->name) == 0){
            return root;
        }

        if(strcmp(name,root->name) < 0){
            root = root->st;
            continue;
        }

        if(strcmp(name,root->name) > 0){
            root = root->dr;
            continue;
        }
    }

    return NULL;
}

AFile SearchFileAddress(char* name, AFile root){

    while(root){

        if(strcmp(name,root->name) == 0){
            return root;
        }

        if(strcmp(name,root->name) < 0){
            root = root->st;
            continue;
        }

        if(strcmp(name,root->name) > 0){
            root = root->dr;
            continue;
        }
    }

    return NULL;
}

void Tree(ADir root, int lvl){


  if (root == NULL){
        return;
    }
    
    if(root->parent != NULL){

        for(int i = lvl; i > 1; i--){
            printf("   ");
        }
        printf("|--");
        
    }

    printf("%s/\n",root->name);
    
    Tree(root->SDRoot,lvl+1);

    InorderTreePrint_2(root->FRoot,lvl+1);

    Tree(root->st,lvl);
    
    Tree(root->dr,lvl);
    
    return;
}

void PrintPath(ADir node){
    if(node == NULL){
        return;
    }
    PrintPath(node->parent);
    printf("/%s",node->name);
}

void SearchRec(ADir root,char* el, int* found ){

    if (root == NULL || *found == 1){
        return;
    }
    
    SearchRec(root->SDRoot,el,found);
    

    if(strcmp(root->name,el) < 0){
        SearchRec(root->st,el,found);
    }

    if(strcmp(root->name,el) > 0){
        SearchRec(root->dr,el,found);
    }

    if(strcmp(root->name,el) == 0){
        *found = 1;
        return;
    }

}

void RunDownTreesLikeAChainsaw(ADir root,char*el,ADir* found){

    if(root == NULL){
        return;
    }
    if(*found == NULL){
        RunDownTreesLikeAChainsaw(root->st,el,found);
        RunDownTreesLikeAChainsaw(root->dr,el,found);
        RunDownTreesLikeAChainsaw(root->SDRoot,el,found);
    }else 
        return;

    if(strcmp(root->name,el) == 0){
        *found = root;
    }
    
}

void RunDownTreesLikeAChainsaw_f(ADir root,char*el,AFile* found){

    if(root == NULL){
        return;
    }
    if(*found == NULL){
        *found = SearchFileAddress(el, root->FRoot); 
        RunDownTreesLikeAChainsaw_f(root->st,el,found);
        RunDownTreesLikeAChainsaw_f(root->dr,el,found);
        RunDownTreesLikeAChainsaw_f(root->SDRoot,el,found);
    }else 
        return;

       
}

void FreeFileTree(AFile root){
    if (root == NULL){
        return;
    }
    FreeFileTree(root->st);
    FreeFileTree(root->dr);

    free(root->name);
    free(root);
    
}

void ResetRoot(ADir root){
    if (root == NULL){
        return;
    }
    
    
    ResetRoot(root->st);
    
    ResetRoot(root->dr);

    ResetRoot(root->SDRoot);
    
    
    FreeFileTree(root->FRoot);
    
    free(root->name);
    free(root);
    
    return;

}

int main(void){

    char * line = NULL;

    size_t len = 0;

    const char delim[5] = " ";

    ADir root  = InitRoot();

    ADir Current  = root;

    ADir Previous = root;

    int exit = 0;

    while(getline(&line, &len, stdin) != -1){

    char* tok = strtok(line, delim);

    switch(*tok){

        case 'm' :
            tok = strtok(NULL,delim);
            tok[strlen(tok) - 1] = '\0';
            ADir new_d = AllocDir();
            new_d->parent = Current;
            strcpy(new_d->name, tok);
            if( SearchFileName(new_d->name,Current->FRoot) == 0 ){
                printf("File %s already exists!\n",new_d->name);
                free(new_d->name);
                free(new_d);
                break;
            }else if( InsertDir(Current,new_d) == 0 ){
                printf("Directory %s already exists!\n",new_d->name);
                free(new_d->name);
                free(new_d);
                break;            
            }
            break;

        case 't':

            if(tok[1] == 'r'){

                ADir st = Current->st;
                ADir dr = Current->dr;
                ADir P = Current->parent;
                Current->parent = NULL;
                Current->st = NULL;
                Current->dr = NULL;
                Tree(Current,0);
                printf("\n\n");
                Current->parent = P;
                Current->st = st;
                Current->dr = dr;
                break;           
            } 

        
            tok = strtok(NULL,delim);
            tok[strlen(tok) - 1] = '\0';
            AFile new_f = AllocFile();
            new_f->parent = Current;
            strcpy(new_f->name, tok);
            if( SearchDirName(new_f->name,Current->SDRoot) == 0 ){
                printf("Directory %s already exists!\n",new_f->name);
                free(new_f->name);
                free(new_f);
                break;
            }else if( InsertFile(Current,new_f) == 0 ){
                printf("File %s already exists!\n",new_f->name);
                free(new_f->name);
                free(new_f);
            }
            break;
    

        case 'l' : 

            if(tok[strlen(tok) - 1] == '\n'){
                InorderTreePrint_d_Hidden(Current->SDRoot);
                InorderTreePrint_f_Hidden(Current->FRoot);
                printf("\n");    
                break;      
            }else{
                InorderTreePrint_d(Current->SDRoot);
                InorderTreePrint_f(Current->FRoot);
                printf("\n"); 
            }
            break;

        case 'r' : 

            tok[strlen(tok)] = '\0';            
            if(strcmp(tok,"rmdir\0") == 0){
                int found = 0;
                tok = strtok(NULL,delim);
                tok[strlen(tok) - 1] = '\0';
                Current->SDRoot = deleteNode_d(Current->SDRoot,tok,&found);
                if (!found){
                    printf("Directory %s doesn't exist!\n",tok);
                }
                }else{
                    int found = 0;
                    tok = strtok(NULL,delim);
                    tok[strlen(tok) - 1] = '\0';
                    Current->FRoot = deleteNode_f(Current->FRoot,tok,&found);
                    if (!found){
                        printf("File %s doesn't exist!\n",tok);
                    }
            }
            break;
        

        case 'c' : 
            tok = strtok(NULL,delim);
            tok[strlen(tok) - 1] = '\0';
            if(strcmp(tok,"..\0") == 0 && Current->parent != NULL){
                Previous = Current;
                Current = Current->parent; 
                break;
            }else if(strcmp(tok,"-\0") == 0){
                ADir aux = Current;
                Current = Previous; 
                Previous = aux;
                break;
            }else if(Current->parent == NULL && strcmp(tok,"..\0") == 0){
                break;
            }
            ADir dest_d = SearchDirAddress(tok,Current->SDRoot);
            
            if(dest_d == NULL){
                printf("Directory not found!\n");
            }else{
                Previous = Current;
                Current = dest_d;                
            }
            break;
        

        case 'p':

           PrintPath(Current); 
           printf("\n");
           break;
        

        case 'f' : 

            tok = strtok(NULL,delim);

            if(tok[1] == 'd'){

                tok = strtok(NULL,delim);
                tok[strlen(tok) - 1] = '\0';

                ADir found = NULL;
                RunDownTreesLikeAChainsaw(root->SDRoot,tok,&found);
                if(found != NULL){
                    printf("Directory %s found!\n",found->name);
                    PrintPath(found);
                    printf("\n");
                }else{
                    printf("Directory %s not found!\n",tok);
                }
                break;
            }
            if(tok[1] == 'f'){
    
                tok = strtok(NULL,delim);
                tok[strlen(tok) - 1] = '\0';
                AFile found = NULL;
                RunDownTreesLikeAChainsaw_f(root,tok,&found);
                if(found != NULL){
                    printf("File %s found!\n",found->name);
                   
                    PrintPath(found->parent);
                    
                    printf("\n");
                }else{
                    printf("File %s not found!\n",tok);
                }
            }
            break;

        

        case 'q' :
            exit = 1;
            ResetRoot(root);
            root = NULL;
            break;
        
        default :
            printf("Error - could not process command\n");

        }

        if(exit){
            break;
        }
    }

    free(line);

    return 0;
}

