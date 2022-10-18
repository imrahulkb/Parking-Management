#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include <ctime>

using namespace std;
class car
{
    public:
    char ownerName[20];
    char plate[10];
    int contact;
    time_t intime;
    int type;
    car(char n[],char p[],int t)//constructor
    {
        strcpy(ownerName,n);
        strcpy(plate,p);
        intime=time(0);
        type=t;
    }
};

class lot
{
    public:
    int id;
    car * c;
    //functions and constructor
        lot()
        {
            c=NULL;
        }
        void allocate(char p[],char n[],int type)
        {
                c=new car(p,n,type);

                cout<<"Plot "<<id<<" Is Occupied!\n";
        }
        void deallocate()
        {
                delete(c);
                c=NULL;

                cout<<"Plot "<<id<<" Is Now Empty!";
        }

};
int calculateHours(time_t t)
{
    if(t%3600>0)
    {
        return t/3600+1;
    }
    return t/3600;
}
void display(lot lots[])
{
    for(int i=0;i<100;i++)
    {
        if(lots[i].c==NULL)
        {
            cout<<lots[i].id<<"\t";
        }
    }
    cout<<endl;
    getc(NULL);
}

int isfull(lot lots[])
{
    for(int i=0;i<100;i++)
    {
        if(lots[i].c==NULL)
        {
            return i;
        }
    }
    return -1;
}

void generatebill(lot *a,time_t o)
{
    string category[4]={"Auto","Car","Tempo","Bus"};
    int price[4]={100,120,150,180};
    int invoice,type=(*a).c->type;
    int hours=calculateHours(o-(*a).c->intime);
    cout<<"\t\t\t\tABC PARKING LOTS PVT. LTD."<<endl;
    cout<<"\tContact : 7020179259\t\t\t\t\tAddress :New York Nagar"<<endl;
    cout<<"____________________________________________________________________________________________"<<endl;
    cout<<"\t\tIn Date and Time     : "<<ctime(&(*a).c->intime)<<endl;
    cout <<"\t\tOut Date and Time   : " <<ctime(&o)<< endl;
    cout<<"\t\tName:"<<(*a).c->ownerName<<endl;
    cout<<"\t\tVehicle Type: "<<category[type]<<endl;
    cout<<"\t\tVehicle No.:  "<<(*a).c->plate<<endl;
    cout<<"\t\tHours : "<<calculateHours(o-(*a).c->intime)<<endl;
    cout<<"\t\tLot No.:"<<(*a).id<<endl;
    cout<<"_____________________________________________________________________________________________"<<endl;
    cout<<"\t\tTotal Amount: "<<price[type]*hours<<endl;

    ofstream outfile;
    char s[10];
    strcpy(s,(*a).c->plate);
    strcat(s,".txt");
    outfile.open(s);
    outfile<<"\t\t\t\t\tABC PARKING LOTS PVT. LTD."<<endl;
    outfile<<"\tContact : 7020179259\t\t\t\t\tAddress :New York Nagar"<<endl;
    outfile<<"_______________________________________________________________________"<<endl;
    outfile<<"\t\tIn Date and Time     : "<<ctime(&(*a).c->intime)<<endl;
    outfile<<"\t\tOut Date and Time   : " <<ctime(&o)<< endl;
    outfile<<"\t\tName:"<<(*a).c->ownerName<<endl;
    outfile<<"\t\tVehicle Type: "<<category[type]<<endl;
    outfile<<"\t\tVehicle No.:  "<<(*a).c->plate<<endl;
    outfile<<"\t\tHours : "<<hours<<endl;
    outfile<<"\t\tLot No.:"<<(*a).id<<endl;
    outfile<<"_______________________________________________________________________"<<endl;
    outfile<<"\t\tTotal Amount: "<<price[type]*hours<<endl;
}
int main()
{
    lot lots[100];
    for(int i=0;i<100;i++)
    {
        lots[i].id=i;
    }
    int option;
    while(1)
    {
        cout<<"***********************************************************************"<<endl;
        cout<<"1. Allocate a lot"<<endl;
        cout<<"2. Deallocate a lot"<<endl;
        cout<<"3. Display Empty Slots"<<endl;
        cout<<"4. Show Details"<<endl;
        cout<<"***********************************************************************"<<endl;

        cin>>option;
        switch(option)
        {
        case 1:
            char plate[10],name[20];
            int type;
            int j;
            j=isfull(lots);
            if(j!=-1)
            {
                cout<<"Enter Customer Name ";
                cin>>name;
                cout<<"Enter Vehicle Registration Number: ";
                cin>>plate;
                cout<<"Enter Vehicle Category: ";
                cout<<"0. Auto\n 1.Car \n2. Tempo\n3. Bus"<<endl;
                cin>>type;
                lots[j].allocate(name,plate,type);

            }
            else cout<<"Sorry No Slots Empty!!!"<<endl;
            break;
        case 2:
            int n;
            cout<<"Enter Plot No. To Deallocate : ";
            cin>>n;
            if(lot[n].c==NULL)
            {
                cout<<"The slot is already empty\n"<<endl;
                break;
            }
            time_t outtime;
            outtime=time(0);
            generatebill(&lots[n],outtime);

            lots[n].deallocate();
            break;
        case 3:
            display(lots);
            cin.ignore();
            break;
        case 4:
            int op1;
            hell:
            cout<<"Enter 1 to Get Specific Lot details"<<endl;
            cout<<"Enter 2 to Get List of All Parked Cars"<<endl;
            cin>>op1;
            switch(op1)
            {
            case 1:
                int no;
                cout<<"Enter lot number: ";
                cin>>no;
                cout<<"Lot No.: "<<no<<endl;
                if(lots[no].c==NULL)
                {
                    cout<<"LOT is Empty"<<endl;
                }
                else
                {
                     ;
                    cout<<"Details"<<endl;
                    cout<<"Lot No.: "<<no<<endl;
                    cout<<"Owner Name: "<<lots[no].c->ownerName<<endl;
                    cout<<"Car No.: "<<(lots[no].c)->plate<<endl;
                }
                break;
            case 2:
                for(int i=0;i<100;i++)
                {
                    if(lots[i].c!=NULL)
                    {
                        cout<<"Lot No.: "<<i<<endl;
                        cout<<"Owner Name: "<<lots[i].c->ownerName<<endl;
                        cout<<"Car No.: "<<(lots[i].c)->plate<<endl;
                    }
                }
                break;
            default:
            cout<<"Enter correct Choice !!! \n";
            goto hell;
            }
            break;
            default:
            cout<<"Enter correct Choice !!! ";
        }
    }
    return 0;
}
