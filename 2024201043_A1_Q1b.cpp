#include <iostream>
#include <random>
#include <string>

using namespace std;

static random_device rd;
static mt19937 rng{rd()};

template<typename T>
class Deque
{
    private:
        T* arr;
        int fr,rear,si,cap;
    public:
        Deque()
        {
            arr=nullptr;
            fr=rear=-1;
            si=cap=0;
        }
        void enqueue(T x)
        {
            if(si==cap)
            {
                int new_cap=(cap==0)?1:(2*cap);
                T* newArr=new T[new_cap];
                for(int i=0;i<si;i++)
                    newArr[i]=arr[(fr+i)%cap];
                delete[] arr;
                arr=newArr;
                fr=0;
                rear=si-1;
                cap=new_cap;
            }
            if(si==0)
                fr=rear=0;
            else
                rear=(rear+1)%cap;
            arr[rear]=x;
            si++;
        }
        T sample()
        {
            if(si==0)
            {
                cout<<"\nDequeue is empty";
                return T();
            }
            uniform_int_distribution<int> uid(0,si-1);
            int randomIndex=uid(rng);
            int modIndex=(fr+randomIndex)%cap;
            return arr[modIndex];
        }
        T dequeue()
        {
            if(si==0)
            {
                cout<<"\nDequeue underflow";
                return T();
            }
            uniform_int_distribution<int> uid(0, si-1);
            int randomIndex=uid(rng);
            int modIndex=(fr+randomIndex)%cap;
            T item=arr[modIndex];
            arr[modIndex]=arr[rear];
            if(si==1)
                fr=rear=-1;
            else
                rear=(rear-1+cap)%cap;
            si--;
            return item;
        }
        void display()
        {
            if(si==0)
                cout<<"\nDeque is empty.";
            else
            {
                cout<<"\n";
                for(int i=0;i<si;i++)
                {
                    int modIndex=(fr+i)%cap;
                        cout<<arr[modIndex]<<" ";
                }
            }
        }
        int size()
        {
            return si;
        }
};

template<typename T>
void menu()
{
    Deque<T> dq;
    while(true)
    {
        cout<<"\nMenu 2:\n";
        cout<<"0-To exit Menu 2\n1-enqueue(x)\n2-dequeue()\n3-sample()\n4-display()\n>>";
        int op;
        cin>>op;
        int n;
        T x;
        T val;
        switch(op)
        {
            case 0:
                return;
            case 1:
                cout<<"\nEnter value x: ";
                cin>>x;
                dq.enqueue(x);
                break;
            case 2:
                val=dq.dequeue();
                cout<<"\nRemoved item- "<<val;
                break;
            case 3:
                val=dq.sample();
                cout<<"\nValue is: "<<val;
                break;
            case 4:
                dq.display();
                break;
            default:
                cout<<"\nInvalid input";
        }
    }
}

int main()
{
    while(true)
    {
        int dtype;
        cout<<"\nMenu 1:\nSelect data type forthe deque:\n0-Exit Menu 1\n";
        cout<<"1-int\n";
        cout<<"2-float\n";
        cout<<"3-char\n4-string\n>>";
        cin>>dtype;
        switch(dtype)
        {
            case 0:
                return 0;
            case 1:
                menu<int>();
                break;
            case 2:
                menu<float>();
                break;
            case 3:
                menu<char>();
                break;
            case 4:
                menu<string>();
                break;
            default:
                cout<<"\nInvalid selection";
        }
    }
    return 0;
}