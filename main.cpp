#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class User{
    protected:
    string username;
    string password;

    public:
    User(){};
    User(string u, string p){
        username = u;
        password = p;
    }
    string getUserName(){
        return username;
    }
    string getPassword(){
        return password;
    }
};
//User Manager should not inherit User since it manages User... use composition
class UserManager{
    private:
    vector<User>users;

    public:
    void saveUsersToFile(){
        ofstream file("users.txt");
        for (User u : users){
            file<<u.getUserName()<<" "<<u.getPassword()<<endl;
        }
        file.close();
        cout<<"Saved all users to file"<<endl;
    }
    void loadUsersFromFile(){
        ifstream file("users.txt");
        if(!file) return;
        string u,p;
        while(file>>u>>p){
            users.push_back(User(u,p));
        }
        file.close();
        cout<<"Loaded all users from file"<<endl;
    }
    void addNewUser(){
        string username;
        string password;
        cout<<"Enter user name: ";
        cin>>username;
        cout<<"Enter password: ";
        cin>>password;
        for(User i : users){
            if (i.getUserName()==username){
                cout<<"User already exists";
                return;
            }
        }
        User u(username,password);
        users.push_back(u);
        cout<<"User added successfully";
        cout<<endl;
    }
    void userLogin(){
        string username,password;
        cout<<"Enter user name: ";
        cin>>username;
        cout<<"Enter password: ";
        cin>>password;
        for (User u:users){
            if(u.getUserName()==username && u.getPassword()==password){
                cout<<"Login successful";
                cout<<endl;
                return;
            }
        }
        cout<<"User does not exist. Please add user";
        cout<<endl;
    }
    void changePassword(){
        string username;
        cout<<"Enter username: ";
        cin>>username;
        for (int i=0;i<users.size();i++){
            if(users[i].getUserName()==username){
                string newPassword;
                cout<<"Enter new password: ";
                cin>>newPassword;
                users[i] = User(username,newPassword);
                cout<<"Password changed successfully";
                return;
            }
        }
        cout<<"User does not exist";    
    }
    void deleteUser(){
        string username;
        cout<<"Enter username: ";
        cin>>username;
        for (int i=0;i<users.size();i++){
            if (users[i].getUserName()==username){
                users.erase(users.begin()+i);
                cout<<"User deleted successfully";
            }
        }
    }
};
class Transaction{
    protected:
    int day;
    int month;
    int year;
    double amount;

    public:
    Transaction(){};
    
    Transaction(int d,int m,int y,double a){
        day = d;
        month = m;
        year = y;
        amount = a;
    }
    int getMonth(){
        return month;
    }
    int getDay(){
        return day;
    }
    int getYear(){
        return year;
    }
    double getAmount(){
        return amount;
    }
    void dateCheck(int day,int month,int year){
        try{
            if (month<1||month>12){
                throw 1;
        }
        }
        catch(int x){
            cout<<"Invalid date";
        }
        try{
            if (day<1||day>31){
                throw 1;
        }
        }
        catch(int x){
            cout<<"Invalid date";
        }
    }
};
class Income : public Transaction{
    public:
    Income(){};
    Income(int d,int m,int y,double a){
        day = d;
        month = m;
        year = y;
        amount = a;
    }
};
class IncomeManager{
    private:
    vector<Income>allIncome;
    Transaction t;

    public:
    IncomeManager(){};
    void saveIncomeToFile(){
        ofstream file("income.txt");
        for (Income i: allIncome){
            file <<i.getDay()<<" "<<i.getMonth()<<" "<<i.getYear()<<" "<<i.getAmount()<<endl;
        }
        file.close();
        cout<<"Saved all income to file"<<endl;
    }
    void loadIncomeFromFile(){
        ifstream file("income.txt");
        int d,m,y;
        double a;
        if (!file) return;
        while (file>>d>>m>>y>>a){
            allIncome.push_back(Income(d,m,y,a));
        }
        file.close();
        cout<<"Loaded all income from file"<<endl;
    }
    void addIncome(){
        int day,month,year;
        double amount;
        cout<<"Enter income date(dd mm yy): ";
        cin>>day>>month>>year;
        t.dateCheck(day,month,year);
        cout<<"Enter income amount: ";
        cin>>amount;
        Income i(day,month,year,amount);
        allIncome.push_back(i);
        cout<<"Income added successfully"<<endl;
    }
    void viewIncome(){
        for (Income i : allIncome){
            cout<<"Income Date: "<<i.getDay()<<" "<<i.getMonth()<<" "<<i.getYear()<<endl;
            cout<<"Income Amount: "<<i.getAmount()<<endl;
        }
    }
    void monthlyReportIncome(int m){
        double totalIncome=0;
        for (Income i:allIncome){
            if(i.getMonth()==m){
                cout<<"Income Date: "<<i.getDay()<<" "<<i.getMonth()<<" "<<i.getYear()<<endl;
                cout<<"Income Amount: "<<i.getAmount()<<endl; 
                totalIncome+=i.getAmount();
            }
        }
        cout<<"Total Income for the month: "<<totalIncome;
        cout<<endl;
    }
    void calculateTotalIncome(){
        double totalIncome=0;
        for (Income i:allIncome){
            totalIncome+=i.getAmount();
        }
        cout<<"Total Income: "<<totalIncome;
        cout<<endl;
    }
};
class Expense : public Transaction{
    protected:
    int category;

    public:
    Expense(){};
    Expense(int d,int m,int y,double a,int c){
        day = d;
        month = m;
        year = y;
        amount = a;
        category = c;
    }
    int getCategory(){
        return category;
    }
};
class ExpenseManager{
    private:
    vector<Expense>expenses;
    Transaction t;
    
    public:
    void saveExpenseToFile(){
        ofstream file("expenses.txt");
        for (Expense e : expenses){
            file<<e.getDay()<<" "<<e.getMonth()<<" "<<e.getYear()<<" "<<e.getAmount()<<" "<<e.getCategory()<<endl;
        }
        file.close();
        cout<<"Saved all expenses to file"<<endl;
    }
    void loadExpenseFromFile(){
        ifstream file("expenses.txt");
        int d,m,y,c;
        double a;
        if (!file) return;
        while (file>>d>>m>>y>>a>>c){
            expenses.push_back(Expense(d,m,y,a,c));
        }
        file.close();
        cout<<"Loaded all expenses from file"<<endl;
    }
    void addExpense(){
        int day,month,year;
        double amount;
        int category;
        cout<<"Enter expense date(dd mm yy): ";
        cin>>day>>month>>year;
        t.dateCheck(day,month,year);
        cout<<"Enter expense category(1.Food 2.Clothing 3.Travel 4.Grocery 5.Miscellaneous): ";
        cin>>category;
        cout<<"Enter expense amount: ";
        cin>>amount;
        Expense e(day,month,year,amount,category);
        expenses.push_back(e);
        cout<<"Expense added successfully";
        cout<<endl;
    }
    void printCategory(int x){
        switch(x){
            case 1: cout<<"Food"<<endl;
            break;
            case 2: cout<<"Clothing"<<endl;
            break;
            case 3: cout<<"Travel"<<endl;
            break;
            case 4: cout<<"Grocery"<<endl;
            break;
            case 5: cout<<"Miscellaneous"<<endl;
            break;
        }
    }
    void viewExpenses(){
        for (Expense e : expenses){
            cout<<"Expense Date: "<<e.getDay()<<" "<<e.getMonth()<<" "<<e.getYear()<<endl;
            cout<<"Expense Category: ";
            printCategory(e.getCategory());
            cout<<"Expense Amount: "<<e.getAmount()<<endl;
        }
    }
    void viewExpenseByMonth(){
        int m;
        double totalAmount=0;
        cout<<"Enter month for which you wish to view expenses: ";
        cin>>m;
        for (Expense e: expenses){
            if(e.getMonth()==m){
                cout<<"Expense Date: "<<e.getDay()<<" "<<e.getMonth()<<" "<<e.getYear()<<endl;
                cout<<"Expense Category: ";
                printCategory(e.getCategory());
                cout<<"Expense Amount: "<<e.getAmount()<<endl; 
                totalAmount+=e.getAmount();
            }
        }
    }
    void viewExpenseByCategory(){
        int c;
        cout<<"Enter category(1.Food 2.Clothing 3.Travel 4.Grocery 5.Miscellaneous) for which you wish to view expenses: ";
        cin>>c;
        for (Expense e: expenses){
            if(e.getCategory()==c){
                cout<<"Expense Date: "<<e.getDay()<<" "<<e.getMonth()<<" "<<e.getYear()<<endl;
                cout<<"Expense Category: ";
                printCategory(e.getCategory());
                cout<<"Expense Amount: "<<e.getAmount()<<endl; 
            }
        }
    }
   void totalExpenseByCategory(){
        double totalByCategory[5];
        for (int i=1;i<=5;i++){
            totalByCategory[i]=0;
        }
        for(Expense e:expenses){
            if(e.getCategory()==1) totalByCategory[1]+=e.getAmount();
            if(e.getCategory()==2) totalByCategory[2]+=e.getAmount();
            if(e.getCategory()==3) totalByCategory[3]+=e.getAmount();
            if(e.getCategory()==4) totalByCategory[4]+=e.getAmount();
            if(e.getCategory()==5) totalByCategory[5]+=e.getAmount();
        }
        sort(totalByCategory,totalByCategory+5);
        cout<<"Total Expense by Category: "<<endl;
        for(int i=1;i<=5;i++){
            cout<<"Category: ";
            printCategory(i);
            cout<<"Total: "<<totalByCategory[i]<<endl;
        }
        cout<<endl;
    }
    double monthlyReportExpense(int m){
        double totalAmount=0;
        for (Expense e: expenses){
            if(e.getMonth()==m){
                cout<<"Expense Date: "<<e.getDay()<<" "<<e.getMonth()<<" "<<e.getYear()<<endl;
                cout<<"Expense Category: ";
                printCategory(e.getCategory());
                cout<<"Expense Amount: "<<e.getAmount()<<endl; 
                totalAmount+=e.getAmount();
            }
        }
        cout<<"Total Expenditure: "<<totalAmount;
        cout<<endl;
        return totalAmount;
    }
    void deleteExpense(){
        int day,month,year;
        cout<<"Enter expense date(dd mm yy): ";
        cin>>day>>month>>year;
        //Traverse by index when deleting or editing
        for (int i=0;i<expenses.size();i++){
            if(expenses[i].getDay()==day && expenses[i].getMonth()==month && expenses[i].getYear()==year){
                expenses.erase(expenses.begin()+i);
                cout<<"Expense deleted successfully"<<endl;
            }
        }
    }
    void editExpense(){
        int day,month,year;
        cout<<"Enter expense date(dd mm yy): ";
        cin>>day>>month>>year;
        //Traverse by index when deleting or editing
        for (int i=0;i<expenses.size();i++){
            if(expenses[i].getDay()==day && expenses[i].getMonth()==month && expenses[i].getYear()==year){
                double newAmount=0;
                int newCategory;
                cout<<"Enter new amount: ";
                cin>>newAmount;
                cout<<"Enter new category: ";
                cin>>newCategory;
                expenses[i] = Expense(day,month,year,newAmount,newCategory);
                cout<<"Expense edited successfully"<<endl;
            }
        }
    }
};
class Report{
    public:
    ExpenseManager em;
    IncomeManager im;
    void printMonth(int x){
        switch(x){
            case 1: cout<<"January"<<endl;
            break;
            case 2: cout<<"February"<<endl;
            break;
            case 3: cout<<"March"<<endl;
            break;
            case 4: cout<<"April"<<endl;
            break;
            case 5: cout<<"May"<<endl;
            break;
            case 6: cout<<"June"<<endl;
            break;
            case 7: cout<<"July"<<endl;
            break;
            case 8: cout<<"August"<<endl;
            break;
            case 9: cout<<"September"<<endl;
            break;
            case 10: cout<<"October"<<endl;
            break;
            case 11: cout<<"November"<<endl;
            break;
            case 12: cout<<"December"<<endl;
            break;
        }
    }
    void monthlyReport(){
        int m;
        cout<<"Enter month for which you wish to see report: ";
        cin>>m;
        cout<<"---------MONTHLY REPORT----------"<<endl;
        cout<<"Month: ";
        printMonth(m);
        im.monthlyReportIncome(m);
        em.monthlyReportExpense(m);
        cout<<endl;
    }
    void overallReport(){
        cout<<"-------REPORT-------"<<endl;
        im.viewIncome();
        em.viewExpenses();
        em.totalExpenseByCategory();
        cout<<endl;
    }
};
class Budget{
    double budgetForEachMonth[13]={0}; //Set 0-idx to 0
    double budgetForEachCategory[6]={0}; //Set 0-idx to 0
    ExpenseManager em;
    IncomeManager im;
    Report r;

    public:
    void saveBudgetToFile(){
        ofstream file("budget.txt");
        for(int i=1;i<=12;i++){
            file<<budgetForEachMonth[i]<<" ";
        }
        file<<endl;
        for (int i=1;i<=5;i++){
            file<<budgetForEachCategory[i]<<" ";
        }
        file.close();
    }
    void loadBudgetFromFile(){
        ifstream file("budget.txt");
        if (!file) return;
        for(int i=1;i<=12;i++){
            file>>budgetForEachMonth[i];
        }
        for (int i=1;i<=5;i++){
            file>>budgetForEachCategory[i];
        }
        file.close();
        cout<<"Loaded all budget from file"<<endl;
    }
    void setTotalBudget(){
        for(int i=1;i<12;i++){
            budgetForEachMonth[i]=0;
        }
        int m;
        double budget=0;
        cout<<"Enter month to enter budget: ";
        cin>>m;
        cout<<"Enter budget amount: ";
        cin>>budget;
        budgetForEachMonth[m] = budget;
        cout<<"Budget set successfully for month: ";
        r.printMonth(m);
    }
    void setBudgetByCategory(){
        for(int i=1;i<5;i++){
            budgetForEachCategory[i]=0;
        }
        int c;
        double budget=0;
        cout<<"Enter category(1-5) to enter budget: ";
        cin>>c;
        cout<<"Enter budget amount: ";
        cin>>budget;
        budgetForEachCategory[c] = budget;
        cout<<"Budget set successfully for category: ";
        em.printCategory(c);
    }
    void checkBudget(){
        cout<<"Monthly Budget: "<<endl;
        for(int i=1;i<=12;i++){
            cout<<"Month: ";
            r.printMonth(i);
            cout<<": "<<budgetForEachMonth[i];
            cout<<endl; 
        }
        cout<<"Category wise Budget: "<<endl;
        for (int i=1;i<=5;i++){
            cout<<"Category: ";
            em.printCategory(i);
            cout<<": "<<budgetForEachCategory[i];
            cout<<endl;
        }
    }
};
int main(){
    ExpenseManager e;
    IncomeManager i;
    Report r;
    UserManager u;
    Budget b;
    u.loadUsersFromFile();
    e.loadExpenseFromFile();
    i.loadIncomeFromFile();
    b.loadBudgetFromFile();
    cout<<"Welcome to your PERSONAL EXPENSE TRACKER"<<endl;
    int choice,ch;
    do{
    cout<<"1. Add User"<<endl<<"2. User Login"<<endl<<"3. Change Password"<<endl<<"4. Delete User"<<endl;
    cin>>ch;
    switch(ch){
        case 1: u.addNewUser();
        break;
        case 2: u.userLogin();
            do{
    cout<<" 1.Add Expense \n 2.Add Income \n 3.View Expense by Month \n 4.View Expense by Category \n 5.Delete Expense \n 6.Edit Expense \n 7.View Report \n 8.Monthly Report \n 9.View Total Income \n 10.Set Total Budget \n 11.Set Budget by Category \n 12.Check Budget \n 13.Exit \n ";
    cout<<"Enter choice: ";
    cin>>choice;
    switch(choice){
        case 1: e.addExpense();
        break;
        case 2: i.addIncome();
        break;
        case 3: e.viewExpenseByMonth();
        break;
        case 4: e.viewExpenseByCategory();
        break;
        case 5: e.deleteExpense();
        break;
        case 6: e.editExpense();
        break;
        case 7: r.overallReport();
        break;
        case 8: r.monthlyReport();
        break;
        case 9: i.calculateTotalIncome();
        break;
        case 10: b.setTotalBudget();
        break;
        case 11: b.setBudgetByCategory();
        break;
        case 12: b.checkBudget();
        break;
        case 13: cout<<"Exiting...";
        break;
        default: cout<<"Invalid input";
        break;
    }
    } while (choice!=12);
        break;
        case 3: u.changePassword();
        break;
        case 4: u.deleteUser();
        break;
        default: cout<<"Invalid input";
        break;
    }
    } while(ch!=2);
    u.saveUsersToFile();
    e.saveExpenseToFile();
    i.saveIncomeToFile();
    b.saveBudgetToFile();
}
