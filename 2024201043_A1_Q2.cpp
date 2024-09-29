#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    Node* links[26];
    bool flag=false;
    bool containsKey(char ch)
    {
        return (links[ch-'a']!=NULL);
    }
    void put(char ch,Node *node)
    {
        links[ch-'a']=node;
    }
    Node* get(char ch)
    {
        return links[ch-'a'];
    }
    void setEnd()
    {
        flag=true;
    }
    bool isEnd()
    {
        return flag;
    }
};

class Trie
{
    private:
        Node* root;
    public:
        Trie()
        {
            root=new Node();
        }
        void insert(string &word)
        {
            Node* node=root;
            for(int i=0;i<word.size();i++)
            {
                if(!node->containsKey(word[i]))
                    node->put(word[i],new Node());
                node=node->get(word[i]);
            }
            node->setEnd();
        }
        bool search(string &word)
        {
            Node* node=root;
            for(int i=0;i<word.size();i++)
            {
                if(!node->containsKey(word[i]))
                    return false;
                node=node->get(word[i]);
            }
            return node->isEnd();
        }
        void getWords(Node* node,string &prefix,vector<string>&result)
        {
            if(node==NULL)
                return;
            if(node->isEnd())
                result.push_back(prefix);
            for(int i=0;i<26;i++)
            {
                char ch=i+'a';
                if(node->get(ch))
                {
                    prefix+=ch;
                    getWords(node->get(ch),prefix,result);
                    prefix.pop_back();
                }
            }
        }
        vector<string> autoComplete(string &word)
        {
            Node* node=root;
            vector<string> wordSet;
            for(int i=0;i<word.size();i++)
            {
                if(!node->containsKey(word[i]))
                    return wordSet;
                node=node->get(word[i]);
            }
            getWords(node,word,wordSet);
            return wordSet;
        }
        int editDistance(string &word, string &prefix)
        {
            int dp[110][110];
            int s1=word.size();
            int s2=prefix.size();
            for(int i=0;i<=s1;i++)
            {
                for(int j=0;j<=s2;j++)
                {
                    if(i==0)
                        dp[i][j]=j;
                    else if(j==0)
                        dp[i][j]=i;
                    else if(word[i-1]==prefix[j-1])
                        dp[i][j]=dp[i-1][j-1];
                    else
                        dp[i][j]=1+min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1]);
                }
            }
            return dp[s1][s2];
        }
        void getAutoCorrectWords(Node *node,string &prefix,string& word,vector<string> &ans)
        {
            if(node->isEnd() && editDistance(word,prefix)<=3)
                ans.push_back(prefix);
            for(int i=0;i<26;i++)
            {
                if(i<26 && node->links[i])
                {
                    prefix+=i+'a';
                    getAutoCorrectWords(node->links[i],prefix,word,ans);
                    prefix.pop_back();
                }
            }
        }
        vector<string> autoCorrect(string &word)
        {
            Node *node=root;
            vector<string> ans;
            string prefix;
            getAutoCorrectWords(node,prefix,word,ans);
            return ans;
        }
};

int main()
{
    while(true)
    {
        cout<<"\nPress 1 to continue, 0 to exit: ";
        int choice;
        cin>>choice;
        if(choice==0)
            return 0;
        int n,q;
        cout<<"\nEnter values: ";
        cin>>n>>q;
        Trie t;
        for(int i=0;i<n;i++)
        {
            string word;
            cin>>word;
            t.insert(word);
        }
        vector<int> v(q);
        vector<string> str(q);
        for(int i=0;i<q;i++)
        {
            cin>>v[i];
            cin>>str[i];
        }
        for(int i=0;i<q;i++)
        {
            switch(v[i])
            {
                case 1:
                {
                    if(t.search(str[i]))
                        cout<<1<<"\n";
                    else
                        cout<<0<<"\n";
                    break;
                }
                case 2:
                {
                    vector<string> words=t.autoComplete(str[i]);
                    if(words.empty())
                        cout<<"\n"<<0<<"\n";
                    else
                    {
                        cout<<words.size()<<"\n";
                        for(int i=0;i<words.size();i++)
                            cout<<words[i]<<"\n";
                    }
                    break;
                }
                case 3:
                {
                    vector<string> correctWords=t.autoCorrect(str[i]);
                    if(correctWords.empty())
                        cout<<"\n"<<0<<"\n";
                    else
                    {
                        cout<<correctWords.size()<<"\n";
                        for(int i=0;i<correctWords.size();i++)
                            cout<<correctWords[i]<<"\n";
                    }
                    break;
                }
                default:
                    cout<<"\nInvalid input";
            }
        }
    }
    return 0;
}