#include <iostream>

using namespace std;

class Priority_queue{
    private:
        int* arr;
        int si,cap;         /* si for size, cap for capacity */
    public:
        Priority_queue()
        {
            arr=nullptr;
            si=cap=0;
        }
        int size()
        {
            return si;
        }
        void push(int el)
        {
            if(si==cap)
            {
                int new_cap=(cap==0)?1:(2*cap);
                int* newArr=new int[new_cap];
                for(int i=0;i<si;i++)
                    newArr[i]=arr[i];
                delete[] arr;
                arr=newArr;
                cap=new_cap;
            }
            si++;
            arr[si-1]=el;
            int i=si-1;
            while(i>0 && arr[(i-1)/2]>arr[i])
            {
                int tmp=arr[i];
                arr[i]=arr[(i-1)/2];
                arr[(i-1)/2]=tmp;
                i=(i-1)/2;
            }
        }
        int top()
        {
            if(si!=0)
                return arr[0];
            else
            {
                cout<<"Priority queue is empty";
                return 0;
            }
        }
        void pop()
        {
            if(si==0)
            {
                cout<<"\nPop underflow";
                return;
            }
            arr[0]=arr[si-1];
            si--;
            if(si==0)
                return;
            int i=0;
            while(2*i+1<si)
            {
                int left=2*i+1;
                int right=2*i+2;
                int currmin=i;
                if(left<si && arr[left]<arr[currmin])
                    currmin=left;
                if(right<si && arr[right]<arr[currmin])
                    currmin=right;
                if(currmin==i)
                    break;
                int tmp=arr[i];
                arr[i]=arr[currmin];
                arr[currmin]=tmp;
                i=currmin;
            }
        }
        bool empty()
        {
            return (si==0);
        }
        void display(int ch)
        {
            if(si==0)
                cout<<"\nPriority queue is empty";
            if(ch==1)
            {
                for(int i=0;i<si;i++)
                    cout<<arr[i]<<" ";
                cout<<"\n";
            }
            else
            {
                for(int i=0;i<si;i++)
                    cout<<-1*arr[i]<<" ";
                cout<<"\n";
            }
        }
};

int main()
{
    while(true)
    {
        Priority_queue min_pq;
        Priority_queue max_pq;
        cout<<"\nMenu 1 :\n1 - Minimum number gets Maximum Priority\n2 - Maximum Number gets Maximum Priority\n0 - Exit\n>>";
        int ch;
        cin>>ch;
        if(ch==0)
            return 0;
        else if(ch==1)
        {
            while(true)
            {
                cout<<"\nMenu:\n0. Exit\n1. Initialize empty priority queue\n2. Get size of priority queue\n3. Push integer key value\n4. Get the top priority element\n5. Pop the top priority element\n6. Check if priority queue is empty\n7. Display priority queue\n>>";
                int n;
                cin>>n;
                if(n==0)
                    break;
                if(n==1)
                {
                    min_pq=Priority_queue();
                    continue;
                }
                switch(n)
                {
                    case 2:
                        cout<<"\n"<<min_pq.size();
                        break;
                    case 3:
                        int ele;
                        cout<<"\nEnter element to push: ";
                        cin>>ele;
                        min_pq.push(ele);
                        break;
                    case 4:
                        cout<<"\n"<<min_pq.top();
                        break;
                    case 5:
                        min_pq.pop();
                        break;
                    case 6:
                        if(min_pq.empty())
                            cout<<"\nPriority Queue is empty";
                        else
                            cout<<"\nPriority Queue is not empty";
                        break;
                    case 7:
                        min_pq.display(ch);
                        break;
                    default:
                        cout<<"\nInvalid choice";
                }
            }
        }
        else if(ch==2)
        {
            while(true)
            {
                cout<<"\nMenu 2 :\n0. Exit\n1. Initialize empty priority queue\n2. Get size of priority queue\n3. Push integer key value\n4. Get the top priority element\n5. Pop the top priority element\n6. Check if priority queue is empty\n7. Display priority queue\n>>";
                int n;
                cin>>n;
                if(n==0)
                    break;
                if(n==1)
                {
                    max_pq=Priority_queue();
                    continue;
                }
                switch(n)
                {
                    case 2:
                        cout<<"\n"<<max_pq.size();
                        break;
                    case 3:
                        int ele;
                        cout<<"\nEnter element to push: ";
                        cin>>ele;
                        max_pq.push(-1*ele);
                        break;
                    case 4:
                        cout<<"\n"<<-1*max_pq.top();
                        break;
                    case 5:
                        max_pq.pop();
                        break;
                    case 6:
                        if(max_pq.empty())
                            cout<<"\nPriority Queue is empty";
                        else
                            cout<<"\nPriority Queue is not empty";
                        break;
                    case 7:
                        max_pq.display(ch);
                        break;
                    default:
                        cout<<"\nInvalid choice";
                }
            }
        }
        else
            cout<<"\nInvalid choice";
    }
    return 0;
}