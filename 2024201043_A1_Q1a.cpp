#include <iostream>
#include <string>

using namespace std;

class Complex
{
   private:
    double x = 0.0;
    double y = 0.0;

   public:
    friend ostream& operator<<(ostream& output, const Complex& D)
    {
        output << D.x << "i + " << D.y << "j";
        return output;
    }
    friend istream& operator>>(istream& input, Complex& D)
    {
        input >> D.x >> D.y;
        return input;
    }
};

template<typename T>
class Deque
{
    private:
        T* arr;
        int fr,rear,si,cap;         /* si for size, cap for capacity */
    public:
        Deque()
        {
            arr=nullptr;
            fr=rear=-1;
            si=cap=0;
        }
        Deque(int n)
        {
            cap=si=n;
            arr=new T[cap];
            fr=0;
            for(int i=fr;i<=n-1;i++)
                arr[i]=T();
            rear=n-1;
        }
        Deque(int n,T x)
        {
            cap=si=n;
            arr=new T[cap];
            fr=0;
            for(int i=fr;i<=n-1;i++)
                arr[i]=x;
            rear=n-1;
        }
        bool push_back(T x)
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
            return true;
        }
        bool pop_back()
        {
            if(si!=0 && fr!=rear)
                rear=(rear-1+cap)%cap;
            else if(si==1)
                fr=rear=-1;
            else if(si==0)
            {
                cout<<"\nPop underflow"<<endl;
                return false;
            }
            si--;
            return true;
        }
        bool push_front(T x)
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
                fr=(fr-1+cap)%cap;
            arr[fr]=x;
            si++;
            return true;
        }
        bool pop_front()
        {
            if(si!=0 && fr!=rear)
                fr=(fr+1)%cap;
            else if(si==1)
                fr=rear=-1;
            else if(si==0)
            {
                cout<<"\nPop underflow"<<endl;
                return false;
            }
            si--;
            return true;
        }
        T front()
        {
            if(si!=0)
                return arr[fr];
            else
                return T();
        }
        T back()
        {
            if(si!=0)
                return arr[rear];
            else
                return T();
        }
        T operator [](int index)
        {
            if(index<0)
                index=si+index;
            if(index>=0 && index<si)
                return arr[(fr+index)%cap];
            else
            {
                cout<<"\nIndex out of bound. ";
                return T();
            }
        }
        bool empty()
        {
            return (si==0);
        }
        int size()
        {
            return si;
        }
        void resize(int n)
        {
            if(n>si)
            {
                if(n>cap)
                {
                    while(cap<n)
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
                }
                for(int i=si;i<n;i++)
                    arr[(fr+i)%cap]=T();
                si=n;
                rear=(fr+si-1)%cap;
            }
            else
            {
                while(si>n)
                    pop_back();
            }
        }
        void resize(int n,T d)
        {
            if(n>cap)
            {
                while(cap<n)
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
            }
            for(int i=si;i<n;i++)
                arr[(fr+i)%cap]=d;
            si=n;
            rear=(fr+si-1)%cap;
        }
        void reserve(int n)
        {
            if(n>cap)
            {
                int new_cap=n;
                T* newArr=new T[new_cap];
                for(int i=0;i<si;i++)
                    newArr[i]=arr[(fr+i)%cap];
                delete[] arr;
                arr=newArr;
                fr=0;
                rear=si-1;
                cap=new_cap;
            }
        }
        void shrink_to_fit()
        {
            T* newArr=new T[si];
            for(int i=0;i<si;i++)
                newArr[i]=arr[(fr+i)%cap];
            delete[] arr;
            arr=newArr;
            cap=si;
            fr=0;
            rear=si-1;
        }
        void clear()
        {
            delete[] arr;
            arr=nullptr;
            fr=rear=-1;
            si=cap=0;
        }
        int capacity()
        {
            return cap;
        }
        void display()
        {
            if(si==0)
                cout<<"\nDeque is empty.";
            else
            {
                cout<<"\n";
                for(int i=0;i<si;i++)
                    cout<<arr[(fr+i)%cap]<<" ";
            }
        }
};

template<typename T>
void menu()
{
    Deque<T> dq;
    while(true)
    {
        cout<<"\nMenu 2:\n";
        cout<<"0-To exit\n1-Deque()\n2-Deque(n)\n3-Deque(n,x)";
        cout<<"\n4-push_back(x)\n5-pop_back()\n6-push_front(x)\n7-pop_front()\n8-front()";
        cout<<"\n9-back()\n10-dq[n]\n11-empty()";
        cout<<"\n12-size()\n13-resize(n)\n14-resize(n,d)\n15-reserve(n)";
        cout<<"\n16-shrink_to_fit()\n17-clear()\n18-capacity()\n19-display()\n>>";
        int op;
        cin>>op;
        int n;
        T x;
        T d;
        switch(op)
        {
            case 0:
                return;
            case 1:
                dq=Deque<T>();
                break;
            case 2:
                cout<<"\nEnter size of the queue: ";
                cin>>n;
                dq=Deque<T>(n);
                break;
            case 3:
                cout<<"\nEnter size of deque: ";
                cin>>n;
                cout<<"\nEnter default value to enter: ";
                cin>>x;
                dq=Deque<T>(n,x);
                break;
            case 4:
                cout<<"\nEnter data to append at the end: ";
                cin>>x;
                if(dq.push_back(x))
                    cout<<"\nTrue";
                else
                    cout<<"\nFalse";
                break;
            case 5:
                if(dq.pop_back())
                    cout<<"\nTrue";
                else
                    cout<<"\nFalse";
                break;
            case 6:
                cout<<"\nEnter data to append at the beginning: ";
                cin>>x;
                if(dq.push_front(x))
                    cout<<"\nTrue";
                else
                    cout<<"\nFalse";
                break;
            case 7:
                if(dq.pop_front())
                    cout<<"\nTrue";
                else
                    cout<<"\nFalse";
                break;
            case 8:
                cout<<"\n"<<dq.front();
                break;
            case 9:
                cout<<"\n"<<dq.back();
                break;
            case 10:
                cout<<"\nEnter index value: ";
                cin>>n;
                cout<<"\ndq["<<n<<"] = "<<dq[n];
                break;
            case 11:
                if(dq.empty())
                    cout<<"\nTrue";
                else 
                    cout<<"\nFalse";
                break;
            case 12:
                cout<<"\nSize: "<<dq.size();
                break;
            case 13:
                cout<<"\nEnter new size: ";
                cin>>n;
                dq.resize(n);
                break;
            case 14:
                cout<<"\nEnter new size: ";
                cin>>n;
                cout<<"\nEnter value to put in deque: ";
                cin>>d;
                dq.resize(n,d);
                break;
            case 15:
                cout<<"\nEnter n: ";
                cin>>n;
                dq.reserve(n);
                break;
            case 16:
                dq.shrink_to_fit();
                break;
            case 17:
                dq.clear();
                break;
            case 18:
                cout<<"\nCapacity: "<<dq.capacity();
                break;
            case 19:
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
        cout<<"\nMenu 1:\nSelect data type for the deque:\n0-Exit Menu\n";
        cout<<"1-int\n";
        cout<<"2-float\n";
        cout<<"3-char\n";
        cout<<"4-string\n5-Complex>>";
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
            case 5:
                menu<Complex>();
            default:
                cout<<"\nInvalid selection";
        }
    }
    return 0;
}