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
            while(i>0 && arr[(i-1)/2]<arr[i])
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
                cout<<"\nPriority queue is empty";
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
                int currmax=i;
                if(left<si && arr[left]>arr[currmax])
                    currmax=left;
                if(right<si && arr[right]>arr[currmax])
                    currmax=right;
                if(currmax==i)
                    break;
                int tmp=arr[i];
                arr[i]=arr[currmax];
                arr[currmax]=tmp;
                i=currmax;
            }
        }
        bool empty()
        {
            return (si==0);
        }
};

int offerDays(int n,int d,int arr[])
{
    int offerdays=0;
    Priority_queue smaller,greater;
    double* vec=new double[n];
    double* vec1=new double[n-d+1];
    for(int i=0;i<n;i++)
    {
        smaller.push(arr[i]);
        int tmp=smaller.top();
        smaller.pop();
        greater.push(-1*tmp);
        if(greater.size()>smaller.size())
        {
            tmp=greater.top();
            greater.pop();
            smaller.push(-1*tmp);
        }
        if(greater.size()!=smaller.size())
            vec[i]=(double)(smaller.top());
        else
            vec[i]=(double)(smaller.top()*1.0-greater.top()*1.0)/2;
    }
    for(int i=0;i<n-d+1;i++)
    {
        smaller=Priority_queue();
        greater=Priority_queue();
        for(int j=i;j<i+d;j++)
        {
            smaller.push(arr[j]);
            int tmp=smaller.top();
            smaller.pop();
            greater.push(-1*tmp);
            if(greater.size()>smaller.size())
            {
                tmp=greater.top();
                greater.pop();
                smaller.push(-1*tmp);
            }
        }
        if(greater.size()!=smaller.size())
            vec1[i]=(double)(smaller.top());
        else
            vec1[i]=(double)(smaller.top()*1.0-greater.top()*1.0)/2;
    }
    for(int i=d;i<n;i++)
    {
        if(arr[i]>=vec[i]+vec1[i-d])
            offerdays++;
    }
    delete[] vec;
    delete[] vec1;
    return offerdays;
}




int main()
{
    while(true)
    {
        cout<<"\nEnter 1 to continue, 0 to exit\n>>";
        int choice;
        cin>>choice;
        if(choice==0)
            return 0;
        else if(choice==1)
        {
            int n,d;
            cout<<"\nEnter n and d:\n>>";
            cin>>n>>d;
            int *arr=new int[n];
            cout<<"\nEnter sales data>>";
            for(int i=0;i<n;i++)
                cin>>arr[i];
            int offerdays=offerDays(n,d,arr);
            cout<<"\nTotal number of days offer is given: "<<offerdays;
            delete[] arr;
        }
        else
            cout<<"\nInvalid choice";
    }
    return 0;
} 