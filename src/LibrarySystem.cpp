#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>

using namespace std ;




struct User
{
    string f_name ;
    int id ;

    unordered_set<int> borrowedBooks ;

    User(){
        id =0;
    }

    void read(){

        cout << "Enter User and id\n" ;
        cin >> f_name >> id ;
    }

    bool is_borrowed(int &book_id) {
        return (borrowedBooks.find(book_id) != borrowedBooks.end());
    }

    void borrow_book(int &id){
        borrowedBooks.insert(id) ;
    }

    bool return_copy(int &book_id) {
        auto borrowed_book_location = borrowedBooks.find(book_id) ;

        if(borrowed_book_location != borrowedBooks.end()) 
            { 
                borrowedBooks.erase(borrowed_book_location) ;
                return true ;
            }

            return false ;
    }

    
};

struct Book
{

    string f_name ;
    int id ;

    int quantity ;
    int borrowed_books ;

    Book(){
        id =0;
        quantity = 0 ;
        borrowed_books = 0 ;
    }

    void read(){

        cout << "Enter  id, book_name and quantity \n" ;
        cin >> id >> f_name >> quantity ;
    }

    bool isPrefix(string &str) {
        int str_size = str.size() ;
        if (str_size > (int)f_name.size()) return false;

        for (int i = 0; i < str_size; i++)
            if (str[i] != f_name[i]) 
                return false ;
        
        return true ;
    }

    void return_book() {
        borrowed_books-- ;
    }


    bool isBorrowable(){
        return (quantity - borrowed_books > 0);
    }

    void borrow_book() {
        borrowed_books++ ;
    }
};

bool compare_book_id(Book &b1 ,Book &b2) {
    return (b1.id < b2.id) ;
}
bool compare_book_name(Book &b1 ,Book &b2) {
    return (b1.f_name < b2.f_name) ;
}

struct LibrarySystem
{
    vector<User> users ;
    vector<Book> books ;

    void add_user() {
        User temp ;
        temp.read() ;

        users.push_back(temp) ;
    }
    void add_book() {
        Book temp ;
        temp.read() ;

        books.push_back(temp) ;
    }

    int find_user_idx_by_name(string &user_name) {
        int users_size = users.size() ;
        for (int i = 0; i < users_size; i++)
        {
            if (users[i].f_name== user_name) 
                return  i;
        }
        
        cout << "No user with this name\n" ;
        return -1 ;
        
    }
    int find_book_idx_by_name(string &book_name) {
        int books_size = books.size() ;
        for (int i = 0; i < books_size; i++)
        {
            if (books[i].f_name== book_name) 
                return  i;
        }
        
        cout << "No book with this name\n" ;

        return -1 ;
        
    }
    
    bool read_user_name_book_name(int &user_id , int &book_id) {
        string userName , bookName ;
        cin >> userName >> bookName ;

        user_id = find_user_idx_by_name(userName) ;
        book_id = find_book_idx_by_name(bookName) ;

        return (user_id != -1 && book_id != -1) ;
        
    }
    void borrow_book(){

        int user_id  ;
        int book_id  ;

        if (!read_user_name_book_name(user_id,book_id)) return ;

        Book tmpBook = books[book_id] ;
        if (tmpBook.isBorrowable()) {

            tmpBook.borrow_book() ;
            users[user_id].borrow_book(tmpBook.id) ;
        }
        else 
            cout << "there is no copies of this book\n" ;
    }

    void return_book(){
        int user_id  ;
        int book_id  ;

        if (!read_user_name_book_name(user_id,book_id)) return ;
        Book tmpBook = books[book_id];
        if (users[user_id].return_copy(tmpBook.id))
            tmpBook.return_book() ;
        else 
            cout << "this user doesn't borrow this book \n" ;

    }

    void print() {
        for (Book book :books)
        {
            cout << book.id << ' '
                << book.f_name << ' ' 
                << book.quantity << '\n' ;
        }
        
    }
    void print_users() {
        for (User user :users)
        {
            cout << user.id << ' '
                << user.f_name << '\n' ;
        }
        
    }

    void print_library_by_id(){
        sort(books.begin(),books.end(),compare_book_id) ;
        print() ;
    }
    void print_library_by_name(){
        sort(books.begin(),books.end(),compare_book_name) ;
        print() ;
    }
    
    void search_by_prefix() {
        string str ;
        cin >> str ;

        for (Book book :books) {
            if (book.isPrefix(str)) 
                cout << book.f_name << '\n' ;
        }
    }

    void print_book_borrowed_users(){
        string book_name ;
        cin >> book_name ;

        int book_pos = find_book_idx_by_name(book_name) ;

        if (book_pos != -1) 
            {
                int cnt = 0 ;
                int book_id = books[book_pos].id ;
                for(User user :users) {
                    if (user.is_borrowed(book_id)) 
                        {
                            cout << user.f_name << '\n' ;
                            cnt++ ;
                        }
                }

                if (!cnt) cout << "No users borrow this book\n" ;
            }
    }


    int menu() {
        int choice = -1;
        while (choice == -1) {
            cout << "\nLibrary Menu;\n";
            cout << "1) add_book\n";
            cout << "2) search_books_by_prefix\n";
            cout << "3) print_who_borrowed_book_by_name\n";
            cout << "4) print_library_by_id\n";
            cout << "5) print_library_by_name\n";
            cout << "6) add_user\n";
            cout << "7) user_borrow_book\n";
            cout << "8) user_return_book\n";
            cout << "9) print_users\n";
            cout << "10) Exit\n";

            cout << "\nEnter your menu choice [1 - 10]: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 10)) {
                cout << "Invalid choice. Try again\n";
                choice = -1;	// loop keep working
            }
        }
        return choice;
    }


    void run() {
		while (true) {
			int choice = menu();

			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_by_prefix();
			else if (choice == 3)
				print_book_borrowed_users();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				borrow_book();
			else if (choice == 8)
				return_book();
			else if (choice == 9)
				print_users();
			else
				break;
		}
	}
};




int main() {
    //freopen("c.in", "rt", stdin);
    LibrarySystem library ;
    library.run() ;



    return 0 ;
}