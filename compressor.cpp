#include<bits/stdc++.h>
#include<fstream>
using namespace std;
class node{  // each node has left , right pointer , character and its freq
    public:
    char ch;
    int freq;  
    node* left;
    node* right;
    node(char ch,int freq){
        this->ch = ch;
        this->freq = freq;
        this->left = NULL;
        this->right= NULL;
    }
};

struct Comp{
    bool operator()(const node* const&a ,const node* const&b){
        return a->freq > b->freq; 
    }
};
class huffmanCode{
    public:
    string path;  // path to the text file
    priority_queue<node*,vector<node*>,Comp> minHeap; 
    node* root;
    map<char,string> huffCode;
    map<string,char> reverseHuffCode; // for decompression
    // huffmanCode(string path){
    //     this->path = path;
    // }
    map<char,int> freqTable(string text){
        map<char,int> mp;
        for(int i=0;i<text.length();i++){
            mp[text[i]]++;
        }
        return mp;
    }
    void creatingPriorityQ(map<char,int> freq){ 
        for( auto it : freq){
            node* binaryNode = new node(it.first,it.second);
            (this->minHeap).push(binaryNode);
        }
    }
    void createBinaryTree(priority_queue<node*,vector<node*>,Comp>& minHeap){
        while(minHeap.size() >1){
            // take two nodes and psuh
            node* first = minHeap.top();
            minHeap.pop();
            node* second = minHeap.top();
            minHeap.pop();
            int sum = first->freq + second->freq;
            // char ch = ' ';
            char ch='@';  // IF THIS CHAR IS PRESENT IN THE INPUT FILE THEN IT WILL BE IGNORED IN THE DECOMPRESSED FILE . SO ITS FILE 
            node* newNode = new node(ch,sum); // SIZE WILL BE SLIGHTLY SMALLER THAN THE INPUT FILE SIZE
            newNode->left = first;
            newNode->right = second;
            minHeap.push(newNode);
        }
        this -> root = minHeap.top();
        minHeap.pop();
        return;
    }
    void createBinaryCode(node* root,map<char,string>& huffCode,string code){
        if(root == NULL){
            return ;
        }
        if(root->ch!='@'){
            huffCode[root->ch]=code;
            this->reverseHuffCode[code]=root->ch;
            return ;
        }
        createBinaryCode(root->left,huffCode,code+'0');
        createBinaryCode(root->right,huffCode,code+'1');
        return;
    }
    string createEncodedText(string text){
        string encodedText = "";
        for(int i=0;i<text.length();i++){
            encodedText+=(this->huffCode[text[i]]);
        }
        return encodedText;
    }
    string createBinary(int val){
        string s;
        while(val!=0){
             s.insert(s.begin(), '0' + (val % 2));
            val/=2;
        }
        // cout<<"s = "<<s.size()<<endl;
        while (s.length() < 8) {
            s.insert(s.begin(), '0');  // Add leading zeros to make it 8-bit
        }
        // cout<<"Padding = "<<s<<" "<<s.length()<<endl;
        // reverse(s.begin(),s.end());
        return s;
    }
    string createPaddedText(string& encodedText){
        int paddingValue = (8 - (encodedText.length()%8))%8;  // last %8 so as if the string is already multiple of 8 
        for(int i=1;i<=paddingValue;i++){
            encodedText.push_back('0');
        }
        // converting the padding count to  8 bit binary
        string binaryVal = createBinary(paddingValue);
        return binaryVal;
    }
    vector<int> convertToBytes(string text){
        vector<int> arr;
        // cout<<text<<" "<<text.length()<<endl;
        for(int i=0;i<text.length();i+=8){
            string temp = text.substr(i,8);
            int num = 0;
            for (int j = 0; j < 8; j++) {
                if (temp[j] == '1') {
                    num |= (1 << (7 - j)); // Correct bit position mapping
                }
            }

            // cout<<"num = "<<num<<endl;
            arr.push_back(num);
        }
        return arr;
    }
    void compression(){
        ifstream inputFile("input.txt");
        if(!inputFile){
            cout<<"Not able to open the input file"<<endl;
            return ;
        }

        string input="";
        string content;
        while(getline(inputFile,content)){
            input += content +"\n";  // considering the newline characters as well
        }
        
        // string text = "kldsfjdflkjfljdfldjgnlnflsdnfldng";
        map<char,int> freq_map = freqTable(input);
        // for(auto it :freq_map){
        //     cout<<it.first <<" "<<it.second<<endl;
        // }
        creatingPriorityQ(freq_map);
        createBinaryTree(minHeap);
        createBinaryCode(this->root,this->huffCode,"");
        string encodedText = createEncodedText(input);
        // cout<<encodedText<<endl;
        string paddedText = createPaddedText(encodedText);
        // cout<<paddedText<<endl;
        string finalEncodedText = paddedText + encodedText;
        // cout<<finalEncodedText<<endl;
        vector<int> arr = convertToBytes(finalEncodedText);
        // cout<<"Arr = "<<endl;
        // for(int i=0;i<arr.size();i++){
        //     cout<<arr[i]<<endl;
        // }
        vector<uint8_t> bytes ;
        for(int num : arr){
            bytes.push_back(static_cast<uint8_t>(num));
        }
        // cout<<"Bytes = "<<endl;
        // for(uint8_t byte:bytes){
        //     cout<<byte;
        // }   
        size_t arraySize = sizeof(bytes) / sizeof(bytes[0]);
        ofstream outputFile("output.bin", std::ios::binary);
        outputFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        inputFile.close();
        outputFile.close();
        cout<<endl;
        cout<<"Compression Successfull......."<<endl;
    }
    string decodeText(string encodedText){
        string temp="";
        string decodedText = "";
        // cout<<reverseHuffCode.size();
        // for(auto it:reverseHuffCode){
            // cout<<"reverse map = "<<it.second<<" ";
        // }
        // cout<<endl;
        for(int i=0;i<encodedText.length();i++){
            temp+=encodedText[i];
            if((this->reverseHuffCode).find(temp)!=(this->reverseHuffCode).end()){
                // cout<<"Hi---------------"<<endl;
                decodedText+=(this->reverseHuffCode[temp]);
                temp="";
            }
        }
        return decodedText;
    }
    void decompression(){
        ifstream inputFile("output.bin",ios::binary);   // opens the compressed binary file
        vector<uint8_t> data;
        uint8_t byte;
        while(inputFile.read(reinterpret_cast<char*>(&byte),sizeof(byte))){
            data.push_back(byte);
            // cout<<"Bytes = "<<(int)byte<<endl; 
        }
        string bin = "";
        for(uint8_t b : data){
            // cout<<(int)b<<" ";
            bin+= (createBinary((int)b));
        }
        // cout<<"binary size = "<<bin.length()<<endl; 
        // the bin string contains padding .. which needs to be removed before decompressing
        // first 8 bits of bin contain the padding info 
        string paddingInfo = bin.substr(0,8);
        int num = 0;
        for (int j = 0; j < 8; j++) {
            if (paddingInfo[j] == '1') {
                num |= (1 << (7 - j)); // Correct bit position mapping
            }
        }
        // cout<<"num = "<<num<<endl;
        // remove the first 8 bit and the last num count of zeroes from the bin
        string encodedText = bin.substr(8,bin.length());
        while(num!=0){
            encodedText.pop_back();
            num--;
        }
        // cout<<"encoded Text "<<bin.length()<<" "<<encodedText.length()<<endl;
        // convert each (int)b into binary of 8 bit long
        string decodedText = decodeText(encodedText);
        // cout<<"Decoded text = "<<decodedText<<endl;
        ofstream file("decompressed.txt");
        file<<decodedText;
        file.close();
        inputFile.close();
    }
};
int main(){
    // auto a = huffmanCode("dfdfsda");
    auto fileInput = huffmanCode();
    fileInput.compression();
    fileInput.decompression();
}