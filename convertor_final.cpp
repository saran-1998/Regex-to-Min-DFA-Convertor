#include<bits/stdc++.h>
using namespace std;

struct nst
{
    vector<int> a[26], e;
    bool f=0;
    bool s=0;
};

struct dst
{
    int a[26] = {-1};
    bool f=0;
    bool s=0;
};

bool present[26];

class Nfa 
{
    private:
        int nfa_size;
        stack<int> st;
    public:
        vector<nst> nfa;
        struct nst init_nfa_state;
        int start_state;
        int final_state;
        Nfa() 
        {
            nfa_size = 0;
            memset(present,false,sizeof(present));
        }
        void union_()
        {
            nfa.push_back(init_nfa_state);
            nfa.push_back(init_nfa_state);
            int d = st.top(); st.pop();
            int c = st.top(); st.pop();
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            nfa[nfa_size].e.push_back(a);
            nfa[nfa_size].e.push_back(c);
            nfa[b].e.push_back(nfa_size+1);
            nfa[d].e.push_back(nfa_size+1);
            st.push(nfa_size);
            nfa_size++;
            st.push(nfa_size);
            nfa_size++;
        }

        void concatenation()
        {
            int d = st.top(); st.pop();
            int c = st.top(); st.pop();
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            nfa[b].e.push_back(c);
            st.push(a);
            st.push(d);
        }

        void kleene_star()
        {
            nfa.push_back(init_nfa_state);
            nfa.push_back(init_nfa_state);
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            nfa[nfa_size].e.push_back(a);
            nfa[nfa_size].e.push_back(nfa_size+1);
            nfa[b].e.push_back(a);
            nfa[b].e.push_back(nfa_size+1);
            st.push(nfa_size);
            nfa_size++;
            st.push(nfa_size);
            nfa_size++;
        }

        void character(int i)
        {
            nfa.push_back(init_nfa_state);
            nfa.push_back(init_nfa_state);
            present[i] = true;
            nfa[nfa_size].a[i].push_back(nfa_size+1);
            st.push(nfa_size);
            nfa_size++;
            st.push(nfa_size);
            nfa_size++;
        }

        void display_nfa()
        {
            cout<<endl<<endl;
            cout<<"Phase 1: regex to nfa conversion using thompson's construction algorithm\n";
            cout<<"------------------------------------------------------------------------\n";
            cout<<"State\t|";
            for(int i=0;i<26;i++)
            {
                if(present[i])
                    cout<<"\t"<<char(i+'a')<<"\t|";
            }
            cout<<"\teps\t|accepting state|   start state   |"<<endl;
            cout<<"------------------------------------------------------------------------\n";
            for(unsigned int i=0; i<nfa.size(); i++)
            {
                
                cout<<i<<"\t|\t";
                for(unsigned int k=0;k<26;k++)
                {
                    if(present[k])
                    {
                        for(unsigned int j=0; j<nfa[i].a[k].size(); j++)
                            cout<<nfa[i].a[k][j]<<' ';
                        cout<<"\t|\t";
                    }    
                }
                for(unsigned int j=0; j<nfa[i].e.size(); j++)cout<<nfa[i].e[j]<<' ';
                cout<<"\t|\t";
                if(nfa[i].f)
                    cout<<"Yes"; 
                else 
                    cout<<"No";
                cout<<"\t|\t";
                if(nfa[i].s)
                    cout<<"Yes"; 
                else 
                    cout<<"No";
                cout<<"\t|\n";

            }
            cout<<"------------------------------------------------------------------------\n";
        }
        void setState()
        {
            final_state=st.top();st.pop();
            start_state=st.top();st.pop();
            nfa[final_state].f=1;
            nfa[start_state].s=1;
        }

};

class Dfa 
{
    private:
        int dfa_size;
    public:
        vector<dst> dfa;
        struct dst init_dfa_state;
        Dfa()
        {
            dfa_size = 0;
        }
        void print_dfa(){
            cout<<endl;
            cout<<"NFA TO DFA CONVERSION"<<endl;
            cout<<"---------------------------------------------------------"<<endl;
            cout<<"STATE\t|";
            for(int i=0;i<26;i++)
            {
                if(present[i])
                    cout<<"\t"<<char(i+'a')<<"\t|";
            }
            cout<<"\tFINAL\t|"<<endl;
            cout<<"---------------------------------------------------------"<<endl;
            for(int i=0;i<dfa.size();i++){
                cout<<i<<"\t|\t";
                for(int j=0;j<26;j++)
                {
                    if(present[j])
                        cout<<dfa[i].a[j]<<"\t|\t";
                }
                cout<<dfa[i].f<<"\t|"<<endl;
            }
            cout<<"---------------------------------------------------------"<<endl;
        }
};

string dispregex;

/***************************** regex to nfa ****************************/

int priority(char c){
    switch(c){
        case '*': return 3;
        case '.': return 2;
        case '+': return 1;
        default: return 0;
    }
}

string insert_concat(string regexp){
    string ret="";
    char c,c2;
    for(unsigned int i=0; i<regexp.size()-1; i++){
        c=regexp[i];
        c2=regexp[i+1];
        ret+=c;
        if(c!='('&&c2!=')'&&c!='+'&&c2!='+'&&c2!='*'){
            ret+='.';
        }
    }
    ret+=regexp[regexp.size()-1];
    return ret;
}

string regexp_to_postfix(string regexp)
{
    string postfix="";
    stack<char> op;
    char c;
    for(unsigned int i=0; i<regexp.size(); i++)
    {
        switch(regexp[i])
        {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                postfix+=regexp[i]; break;
            case '(':
                op.push(regexp[i]); break;
            case ')':
                while(op.top()!='('){
                    postfix+=op.top();
                    op.pop();
                }
                op.pop();
                break;
            default:
                while(!op.empty()){
                    c=op.top();
                    if(priority(c)>=priority(regexp[i])){
                        postfix+=op.top();
                        op.pop();
                    }
                    else break;
                }
                op.push(regexp[i]);
        }
    }
    while(!op.empty())
    {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}


void postfix_to_nfa(string postfix, Nfa* n)
{
    for(unsigned int i=0; i<postfix.size(); i++)
    {
        switch(postfix[i])
        {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z': n->character(postfix[i]-'a'); break;
        case '*': n->kleene_star(); break;
        case '.': n->concatenation(); break;
        case '+': n->union_();
        }
    }
}

/****************************** nfa to dfa ********************************************/

void epsilon_closure(int state, set<int>&si, Nfa* n) {
    for(unsigned int i=0;i<n->nfa[state].e.size();i++){
        if(si.count(n->nfa[state].e[i])==0){
            si.insert(n->nfa[state].e[i]);
            epsilon_closure(n->nfa[state].e[i],si,n);
        }
    }
}

set<int> state_change(int c, set<int>&si ,Nfa* n) {
    set<int> temp;
    for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
        for(unsigned int j=0;j<n->nfa[*it].a[c].size();j++){
            temp.insert(n->nfa[*it].a[c][j]);
        }
    }
    return temp;
}

void nfa_to_dfa(set<int>&si,queue<set<int> >&que,int start_state, Nfa* n, Dfa* d){
    map<set<int>, int> mp;
    mp[si]=-1;
    set<int> temp1;
    set<int> temp2;
    int ct=0;
    si.clear();
    si.insert(start_state);
    epsilon_closure(start_state,si,n);
    if(mp.count(si)==0){
        mp[si]=ct++;
        que.push(si);
    }
    int p=0;    //state count dfa
    bool f1=false;
    while(que.size()!=0){
        for(int i=0;i<26;i++)
        {
            if(present[i])
            {
                d->dfa.push_back(d->init_dfa_state);
                si=que.front();
                f1=false;
                //final state check
                for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
                    if(n->nfa[*it].f==true)
                        f1=true;
                }
                d->dfa[p].f=f1;
                temp1=state_change(i,si,n);
                si=temp1;
                for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
                    epsilon_closure(*it,si,n);
                }
                if(mp.count(si)==0){
                    mp[si]=ct++;
                    que.push(si);
                    d->dfa[p].a[i]=ct-1;
                }
                else{
                    d->dfa[p].a[i]=mp.find(si)->second;
                }
                temp1.clear(); 
            }
        }
        que.pop();
        p++;
    }
    bool final_flg = false;
    for(int i=0;i<p;i++){
        for(int j=0;j<26;j++)
        {
            if(present[j])
            {
                if(d->dfa[i].a[j]==-1)
                {
                    d->dfa[i].a[j]=p;
                    final_flg = true;
                }
            }      
        }
    }
    if(final_flg)
    {
        d->dfa.push_back(d->init_dfa_state);
        for(int i=0;i<26;i++)
        {
            if(present[i])
                d->dfa[p].a[i]=p;
        }
    }
    int sz = d->dfa.size();
    for(int i=p+1;i<sz;i++)
    {
        d->dfa.pop_back();
    }
}

int main()
{
    string regexp,postfix;
    cout<<"Enter Regular Expression: ";
    cin>>regexp;
    dispregex=regexp;
    regexp=insert_concat(regexp);
    postfix = regexp_to_postfix(regexp);
    cout<<"Postfix Expression: "<<postfix<<endl;
    Nfa n;
    postfix_to_nfa(postfix,&n);
    n.setState();
    n.display_nfa();
    set<int> si;
    queue<set<int> > que;
    Dfa d;
    nfa_to_dfa(si,que,n.start_state,&n,&d);
    d.print_dfa();
    return 0;
}