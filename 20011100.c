#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_WORD_LENGTH 50

typedef struct TrieNode {
    struct TrieNode* children[MAX_CHILDREN];
    int value;
    bool isEndOfWord;
    char nodeWord[MAX_WORD_LENGTH];
} TrieNode;

TrieNode* createNode(int value);

int valueOfChar(char krktr);

void insertWord(TrieNode* root, char* word, int j);

void searchNumber(TrieNode* root, char* number, int j);

void freeTrie(TrieNode* root);

int main() {
    TrieNode* root = createNode(0);
	int i = 0;
    // Sφzlόπό dosyadan oku ve trie'ye ekle
    FILE* dictionaryFile = fopen("sozluk.txt", "r");
    if (dictionaryFile == NULL) {
        printf("Sozluk dosyasi bulunamadi.\n");
        return 1;
    }
    char word[MAX_WORD_LENGTH];
    while (fscanf(dictionaryFile, "%s", word) != EOF) {
    	printf("%s\n", word);
        insertWord(root, word, 0);
    }
    fclose(dictionaryFile);
    
    char number[MAX_WORD_LENGTH];
    while(strcmp(number, "q") != 0){
    	printf("> ");
    	scanf("%s", number);
    	printf("Karsilik gelen kelimeler:\n");
    	searchNumber(root, number, 0);
	}

    freeTrie(root);
    return 0;
}

TrieNode* createNode(int value) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (node == NULL) {
        printf("Bellek tahsisi hatasi\n");
        exit(1);
    }
    node->value = value;
    node->isEndOfWord = false;
    int i=0;
    for (i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

int valueOfChar(char krktr){
	int i=0, k, value=0, flag=0;
	char tablo[10][5] = {
        {'#', '\0', '\0', '\0'},
        {'η', 'π', 'ό', 'ώ'},
        {'a', 'b', 'c', '\0'},
        {'d', 'e', 'f', '\0'},
        {'g', 'h', 'i', '\0'},
        {'j', 'k', 'l', '\0'},
        {'m', 'n', 'o', '\0'},
        {'p', 'q', 'r', 's'},
        {'t', 'u', 'v', '\0'},
        {'w', 'x', 'y', 'z'}
    };
    while(flag==0 && i<10){
    	for(k=0;k<4;k++){
    		if(tablo[i][k]==krktr){
    			value=i;
    			flag=1;
			}
		}
		i++;
	}
    return value;
}

void insertWord(TrieNode* root, char* word, int j) {
	TrieNode* current = root;
	int i = 0, flag = 0, value, k = 0, flag1 = 0;
	value = valueOfChar(word[j]);
	
	while(flag==0 && current->children[i]!=NULL){
		if(current->children[i]->value==value){
			flag=1;
		}
		i++;
	}
	
	if(flag==1){
		j++;
		i--;
		if(word[j]=='\0'){
			if(current->children[i]->isEndOfWord){
				while(k<10 && flag1==0){
					if(current->children[i]->children[k]==NULL){
						current->children[i]->children[k]=createNode(0);
						current->children[i]->children[k]->isEndOfWord=true;
						strcpy(current->children[i]->children[k]->nodeWord, word);
						flag1=1;
					}
					k++;
				}
			}else{
				current->children[i]->isEndOfWord=true;
				strcpy(current->children[i]->nodeWord, word);
			}				
		}else{
			insertWord(current->children[i], word, j);
		}
		
	}else{
		current->children[i] = createNode(value);
		j++;
		if(word[j]=='\0'){
			current->children[i]->isEndOfWord=true;
			strcpy(current->children[i]->nodeWord, word);
		}else{
			insertWord(current->children[i], word, j);
		}
	}
}

void searchNumber(TrieNode* root, char* number, int j) {
    int flag = 0, i = 0, k = 0;
    TrieNode* current = root;
    int value = number[j] - '0';
    
    if(number[j]=='\0'){
    	flag=1;
    	if(current->isEndOfWord){
    		while(current->children[k]!=NULL){
    			if(current->children[k]->value==0 && current->children[k]->isEndOfWord){
    				printf("%s ", current->children[k]->nodeWord);
				}
				k++;
			}
    		printf("%s \n", current->nodeWord);
		}else{
			printf("Boyle bir kelime yok.\n");
		}
	}
    while(flag==0 && i<10){
    	if(current->children[i]==NULL){
    		flag=1;
    		printf("Boyle bir kelime yok.\n");
		}else if(current->children[i]->value == value){
    		flag=1;
    		j++;
    		searchNumber(current->children[i], number, j);
		}
		i++;
	}
}

void freeTrie(TrieNode* root) {
    if (root == NULL) {
        return;
    }
    
    int i = 0;
    for (i = 0; i < MAX_CHILDREN; i++) {
        freeTrie(root->children[i]);
    }
    free(root);
}

