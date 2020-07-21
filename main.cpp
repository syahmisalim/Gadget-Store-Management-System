//GADGET STORE MANAGEMENT SYSTEM //MOHD SYAHMI BIN SALIM // B031910423 //WORKSHOP1

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
#include <iomanip>

using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "gadgetdb", 3306, NULL, 0);
		if (conn)
		{
			cout << "Database Connected To MySql" << conn << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}
};
//MAIN
int adminmain();
int staffmain();
int adminproduct();
int staffproduct();
int adminemployee();
int adminsupplier();
int staffsupplier();
int adminsales();

//SUBMAIN
void AddProduct(), StaffAddProduct();
void UpdateProduct(), StaffUpdateProduct();
void ViewProduct(), StaffViewProduct();
void DeleteProduct(), StaffDeleteProduct();
void AddEmployee();
void UpdateEmployee();
void ViewEmployee();
void DeleteEmployee();
void AddSupplier();
void UpdateSupplier();
void ViewSupplier();
void DeleteSupplier();
void StaffTransaction();
void AdminDailySales();
void AdminSalesReport();
void YearlySales();

int main()
{
	char ch;
	string username;
	string password;

	// Call Methods
	db_response::ConnectionFunction();
	// Call Methods End

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "Username : ";
	cin >> username;

	cout << "\nPassword : ";
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			// Process a destructive backspace
			if (password.size() > 0) {
				password.erase(password.size() - 1, 1);
				std::cout << "\b \b";
			}
		}
		else {
			password.push_back(ch);
			std::cout.put('*');//password asterisk
		}
	}
	goto auth;

auth:
	string checkuser = "SELECT * FROM users WHERE username='"+username+"' AND password='"+password+"'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if ((row = mysql_fetch_row(res)))
		{

			system("cls");
			cout << "******************************" << endl;
			cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
			cout << "******************************" << endl << endl;
			cout << "Authorized!" << endl;
			system("pause");

			if (strcmp(row[3],"s" ))
			{
				adminmain();
			}
			else 
			{
				staffmain();
			}
		}

	else
	{
		system("cls");
		cout << "******************************" << endl;
		cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
		cout << "******************************" << endl << endl;
		cout << "Incorrect Username or Password!" << endl;
		cout << "Please Try Again . . ." << endl << endl;
		system("pause");

		main();
	}
	}
}

int adminmain()
{
	//variables
	int chooseOneFromMenu = 0;
	char exitSurity;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO ADMIN MENU" << endl;
	cout << "1. PRODUCT." << endl;
	cout << "2. EMPLOYEE." << endl;
	cout << "3. SUPPLIER." << endl;
	cout << "4. SALES." << endl;
	cout << "5. LOG OUT." << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 5)) {
		cout << "Please choose between 1 - 5. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}
		switch (chooseOneFromMenu)
		{
		case 1:
			adminproduct();
			break;
		case 2:
			adminemployee();
			break;
		case 3:
			adminsupplier();
			break;
		case 4:
			adminsales();
			break;
		case 5:
		LogOut:
			cout << "Loging out.. Are you sure? (y/N): ";
			cin >> exitSurity;
			if (exitSurity == 'y' || exitSurity == 'Y') {
				main();
			}
			else if (exitSurity == 'n' || exitSurity == 'N') {
				system("cls");
				adminmain();
			}
			else {
				cout << "Next time choose after read the corresponding line." << endl;
				goto LogOut;
			}
			break;
		default:
			cout << "Please choose between 1 - 5. ";
			system("PAUSE");
			system("cls");
			adminmain();
			break;
		}
	system("pause");
	return 0;
}

int staffmain()
{
	//variables
	int chooseOneFromMenu = 0;
	char exitSurity;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO STAFF MENU" << endl;
	cout << "1. PRODUCT." << endl;
	cout << "2. SUPPLIER LIST." << endl;
	cout << "3. TRANSACTION." << endl;
	cout << "4. LOG OUT." << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 4)) {
		cout << "Please choose between 1 - 4. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}

	switch (chooseOneFromMenu)
	{
	case 1:
		staffproduct();
		break;
	case 2:
		staffsupplier();
		break;
	case 3:
		StaffTransaction();
		break;
	case 4:
	LogOut:
		cout << "Loging out.. Are you sure? (y/N): ";
		cin >> exitSurity;
		if (exitSurity == 'y' || exitSurity == 'Y') {
			main();
		}
		else if (exitSurity == 'n' || exitSurity == 'N') {
			system("cls");
			adminmain();
		}
		else {
			cout << "Next time choose after read the corresponding line." << endl;
			goto LogOut;
		}
		break;
	default:
		cout << "Please choose between 1 - 4. ";
		system("PAUSE");
		system("cls");
		staffmain();
		break;
	}
	system("pause");
	return 0;
}

//PRODUCT
int adminproduct()
{
	//variables
	int chooseOneFromMenu = 0;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO PRODUCT WINDOW" << endl;
	cout << "1. ADD PRODUCT." << endl;
	cout << "2. UPDATE PRODUCT." << endl;
	cout << "3. VIEW PRODUCT." << endl;
	cout << "4. DELETE PRODUCT" << endl;
	cout << "5. EXIT" << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 5)) {
		cout << "Please choose between 1 - 5. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}

	switch (chooseOneFromMenu)
	{
	case 1:
		AddProduct();
		break;
	case 2:
		UpdateProduct();
		break;
	case 3:
		ViewProduct();
		break;
	case 4:
		DeleteProduct();
		break;
	case 5:
		adminmain();
		break;
	default:
		cout << "Please choose between 1 - 5. ";
		system("PAUSE");
		system("cls");
		adminproduct();
		break;
	}
	system("pause");
	return 0;
}
int staffproduct()
{
	//variables
	int chooseOneFromMenu = 0;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO PRODUCT WINDOW" << endl;
	cout << "1. ADD PRODUCT." << endl;
	cout << "2. UPDATE PRODUCT." << endl;
	cout << "3. VIEW PRODUCT." << endl;
	cout << "4. DELETE PRODUCT" << endl;
	cout << "5. EXIT" << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 5)) {
		cout << "Please choose between 1 - 5. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}

	switch (chooseOneFromMenu)
	{
	case 1:
		StaffAddProduct();
		break;
	case 2:
		StaffUpdateProduct();
		break;
	case 3:
		StaffViewProduct();
		break;
	case 4:
		StaffDeleteProduct();
		break;
	case 5:
		staffmain();
		break;
	default:
		cout << "Please choose between 1 - 5. ";
		system("PAUSE");
		system("cls");
		staffproduct();
		break;
	}
	system("pause");
	return 0;
}
//ADMIN PRODUCT>ADD PRODUCT
void AddProduct() 
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string suppid = "";
	string name = "";
	string category = "";
	string brand = "";
	double price = 0.0;
	int quantity = 0;
	char choose;
	string itemId[15];
	int itemIndex = 0;
	bool itemFalse = false;

	string storeSuppId[15];
	string storeSuppName[15];
	string storeSuppContact[15];
	int storeIndex = 0;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "ADD NEW PRODUCT" << endl;

	cout << "Please Choose the Supplier : \n";

	qstate = mysql_query(conn, "select * from supplier");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(20) << "Supplier Name"; cout << " | ";
		cout << left << setw(15) << "Contact No."; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(20) << row[1]; cout << " | ";
			cout << left << setw(15) << row[2]; cout << "|"<< endl;

			storeSuppId[storeIndex] = row[0];
			storeSuppName[storeIndex] = row[1];
			storeSuppContact[storeIndex] = row[2];
			storeIndex++;
		}
		cout << "__________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cin.ignore(1, '\n');
	cout << "Choose Supplier ID ['m' to Menu]: ";
	getline(cin, suppid);
	for (int i = 0; i < storeIndex; i++)
	{
		if (suppid == "m" || suppid == "M")
		{
			adminproduct();
		}
		else if (suppid == storeSuppId[i])
		{
			itemId[itemIndex] = suppid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Supplier Id." << endl;
		itemIndex--;
		itemFalse = false;
		AddProduct();
	}

	cout << "Enter Product Name: ";
	getline(cin, name);
	cout << "Enter Product Category: ";
	getline(cin, category);
	cout << "Enter Product Brand: ";
	getline(cin, brand);
	cout << "Enter Product Price: ";
	while (!(cin >> price)) // or if(cin.fail())
	{
		cout << " >Please Enter Numbers Only." << endl;
		cout << "Enter Product Price: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	cout << "Enter Product Quantity in Stock: ";
	while (!(cin >> quantity)) // or if(cin.fail())
	{
		cout << " >Please Enter Numbers Only." << endl;
		cout << "Enter Product Quantity in Stock: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	stringstream streamPrice,streamQuantity;
	string sprice,squantity;
	streamPrice << price;
	streamPrice >> sprice;
	streamQuantity << quantity; 
	streamQuantity >> squantity;

	string insert_query = "insert into product (supplierId, productName, productCategory, productBrand, productPrice, productQuantity) select supplierId,'"+ name + "','" + category + "','" + brand + "','" + sprice + "','" + squantity + "' from supplier where supplierId = '"+ suppid +"'";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminproduct();
	}
	else if (choose == 'a' || choose == 'A')
	{
		AddProduct();
	}
	else
	{
		exit(0);
	}
}
//ADMIN PRODUCT>UPDATE PRODUCT
void UpdateProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variabes
	char choose;
	string prodid;
	string name;
	string category = "";
	string brand = "";
	string price;
	double dprice;
	string quantity;
	int iquantity;
	string itemId[15];
	int itemIndex = 0;
	bool itemFalse = false;

	string storeProdId[15];
	string storeProdName[15];
	string storeProdBrand = "";
	string storeProdCategory = "";
	string storeProdPrice = "";
	string storeProdQuantity = "";
	int storeIndex = 0;

	//variables for store the selected product
	string storeProductId;
	string storeProductName;
	string storeProductCategory;
	string storeProductBrand;
	string storeProductPrice;
	string storeProductQuantity;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "UPDATE PRODUCT " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(8) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(8) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand = row[4];
			storeProdCategory = row[3];
			storeProdQuantity = row[6];
			storeIndex++;
		}
		cout << "_____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << endl << "UPDATE NEW PRODUCT DETAIL" << endl;
	cout << "Choose Product ID ['m' to Menu]: ";
	cin >> prodid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (prodid == "m" || prodid == "M")
		{
			adminproduct();
		}
		else if (prodid == storeProdId[i])
		{
			itemId[itemIndex] = prodid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Product Id." << endl;
		itemIndex--;
		itemFalse = false;
		UpdateProduct();
	}

	string checkuser = "SELECT * FROM product WHERE productId='" + prodid + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			storeProductId = row[0];
			storeProductName = row[2];
			storeProductCategory = row[3];
			storeProductBrand = row[4];
			storeProductPrice = row[5];
			storeProductQuantity = row[6];
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter New Product Name (x  to not change): ";
	cin >> ws;
	getline(cin, name);
	if (name == "x" || name == "X")
	{
		name = storeProductName;
	}

	cout << "Enter New Product Brand (x  to not change): ";
	getline(cin, brand);
	if (brand == "x" || brand == "X")
	{
		brand = storeProductBrand;
	}

	cout << "Enter New Product Category (x  to not change): ";
	getline(cin, category);
	if (category == "x" || category == "X")
	{
		category = storeProductCategory;
	}

	cout << "Enter New Product Price (x  to not change): ";
	getline(cin, price);
	if (price == "x" || price == "X")
	{
		price = storeProductPrice;
		stringstream geek(price);
		geek >> dprice;
	}
	else
	{
		stringstream geek(price);
		geek >> dprice;
		while (!dprice)
		{
			cout << " >Please Enter Numbers Only." << endl;
			cout << "Enter New Product Price :";
			cin >> dprice;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	cout << "Enter New Product Quantity in Stock (x  to not change): ";
	getline(cin, quantity);
	if (quantity == "x" || quantity == "X")
	{
		quantity = storeProductQuantity;
		stringstream geek(quantity);
		geek >> iquantity;
	}
	else
	{
		stringstream geek(quantity);
		geek >> iquantity;
		while (!iquantity)
		{
			cout << " >Please Enter Numbers Only." << endl;
			cout << "Enter New Product Quantity in Stock :";
			cin >> iquantity;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	stringstream streamPrice, streamQuantity;
	string sprice, squantity;
	streamPrice << dprice;
	streamPrice >> sprice;
	streamQuantity << iquantity;
	streamQuantity >> squantity;

	string insert_query = "UPDATE `product` SET `productName`= '" + name + "' ,`productCategory`='" + category + "',`productBrand`='" + brand + "',`productPrice`='" + sprice + "',`productQuantity`='" + squantity + "' WHERE `productId`='" + prodid + "'";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	cout << "Press 'm' to Menu or 'u' to Update Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminproduct();
	}
	else if (choose == 'u' || choose == 'U')
	{
		UpdateProduct();
	}
	else
	{
		exit(0);
	}
}
//ADMIN PRODUCT>VIEW PRODUCT
void ViewProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string storeProdId[50];
	string storeProdName[50];
	string storeProdBrand[50];
	string storeProdCategory[50];
	string storeProdPrice[50];
	string storeProdQuantity[50];
	int storeIndex = 0;
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "PRODUCT LIST : " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(7) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|"<< endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(7) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|"<< endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand[storeIndex] = row[4];
			storeProdCategory[storeIndex] = row[3];
			storeProdPrice[storeIndex] = row[5];
			storeProdQuantity[storeIndex] = row[6];
			storeIndex++;
		}
		cout << "____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	qstate = mysql_query(conn,"select productName AS Name from product WHERE productQuantity < 5");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "Notify : " << row[0] << " Stock running low, please re-stock." << endl;
		}
	}
	else
	{
		cout << "Error find product running low stock!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << endl << "Press 'm' to Menu. ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminproduct();
	}
	else
	{
		exit(0);
	}
}
//ADMIN PRODUCT>DELETE PRODUCT
void DeleteProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string storeProdId[15];
	string storeProdName[15];
	string storeProdBrand[15];
	string storeProdCategory[15];
	string storeProdPrice[15];
	string storeProdQuantity[15];
	int storeIndex = 0;
	char choose;
	string prodid;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];


	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "PRODUCT LIST : " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(7) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(7) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand[storeIndex] = row[4];
			storeProdCategory[storeIndex] = row[3];
			storeProdPrice[storeIndex] = row[5];
			storeProdQuantity[storeIndex] = row[6];
			storeIndex++;
		}
		cout << "____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter Product ID To Delete The Product . ['m' to Menu] : ";
	cin >> prodid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (prodid == "m" || prodid == "M")
		{
			adminproduct();
		}
		else if (prodid == storeProdId[i])
		{
			itemId[itemIndex] = prodid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Product Id." << endl;
		itemIndex--;
		itemFalse = false;
		DeleteProduct();
	}
	cout << "Are You Sure To Delete This Product ? ['y' or 'N'] : ";
	cin >> choose;
	if (choose == 'y' || choose == 'Y')
	{
		string insert_query = "DELETE FROM `product` WHERE `productId`='" + prodid + "'";

		const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << endl << "Successfully deleted in database." << endl;
			DeleteProduct();
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		DeleteProduct();
	}
}
//STAFF PRODUCT>ADD PRODUCT
void StaffAddProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string suppid = "";
	string name = "";
	string category = "";
	string brand = "";
	double price = 0.0;
	int quantity = 0;
	char choose;
	string itemId[15];
	int itemIndex = 0;
	bool itemFalse = false;

	string storeSuppId[15];
	string storeSuppName[15];
	string storeSuppContact[15];
	int storeIndex = 0;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "ADD NEW PRODUCT" << endl;

	cout << "Please Choose the Supplier : \n";

	qstate = mysql_query(conn, "select * from supplier");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(20) << "Supplier Name"; cout << " | ";
		cout << left << setw(15) << "Contact No."; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(20) << row[1]; cout << " | ";
			cout << left << setw(15) << row[2]; cout << "|" << endl;

			storeSuppId[storeIndex] = row[0];
			storeSuppName[storeIndex] = row[1];
			storeSuppContact[storeIndex] = row[2];
			storeIndex++;
		}
		cout << "__________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cin.ignore(1, '\n');
	cout << "Choose Supplier ID ['m' to Menu]: ";
	getline(cin, suppid);
	for (int i = 0; i < storeIndex; i++)
	{
		if (suppid == "m" || suppid == "M")
		{
			staffproduct();
		}
		else if (suppid == storeSuppId[i])
		{
			itemId[itemIndex] = suppid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Supplier Id." << endl;
		itemIndex--;
		itemFalse = false;
		StaffAddProduct();
	}

	cout << "Enter Product Name: ";
	getline(cin, name);
	cout << "Enter Product Category: ";
	getline(cin, category);
	cout << "Enter Product Brand: ";
	getline(cin, brand);
	cout << "Enter Product Price: ";
	while (!(cin >> price)) // or if(cin.fail())
	{
		cout << " >Please Enter Numbers Only." << endl;
		cout << "Enter Product Price: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	cout << "Enter Product Quantity in Stock: ";
	while (!(cin >> quantity)) // or if(cin.fail())
	{
		cout << " >Please Enter Numbers Only." << endl;
		cout << "Enter Product Quantity in Stock: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	stringstream streamPrice, streamQuantity;
	string sprice, squantity;
	streamPrice << price;
	streamPrice >> sprice;
	streamQuantity << quantity;
	streamQuantity >> squantity;

	string insert_query = "insert into product (supplierId, productName, productCategory, productBrand, productPrice, productQuantity) select supplierId,'" + name + "','" + category + "','" + brand + "','" + sprice + "','" + squantity + "' from supplier where supplierId = '" + suppid + "'";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		staffproduct();
	}
	else if (choose == 'a' || choose == 'A')
	{
		StaffAddProduct();
	}
	else
	{
		exit(0);
	}
}
//STAFF PRODUCT>UPDATE PRODUCT
void StaffUpdateProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variabes
	char choose;
	string prodid;
	string name;
	string category = "";
	string brand = "";
	string price;
	double dprice;
	string quantity;
	int iquantity;
	string itemId[15];
	int itemIndex = 0;
	bool itemFalse = false;

	string storeProdId[15];
	string storeProdName[15];
	string storeProdBrand = "";
	string storeProdCategory = "";
	string storeProdPrice = "";
	string storeProdQuantity = "";
	int storeIndex = 0;

	//variables for store the selected product
	string storeProductId;
	string storeProductName;
	string storeProductCategory;
	string storeProductBrand;
	string storeProductPrice;
	string storeProductQuantity;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "UPDATE PRODUCT  " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(8) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(8) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand = row[4];
			storeProdCategory = row[3];
			storeProdQuantity = row[6];
			storeIndex++;
		}
		cout << "_____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << endl << "UPDATE NEW PRODUCT DETAIL" << endl;
	cout << "Choose Product ID ['m' to Menu]: ";
	cin >> prodid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (prodid == "m" || prodid == "M")
		{
			staffproduct();
		}
		else if (prodid == storeProdId[i])
		{
			itemId[itemIndex] = prodid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Product Id." << endl;
		itemIndex--;
		itemFalse = false;
		StaffUpdateProduct();
	}

	string checkuser = "SELECT * FROM product WHERE productId='" + prodid + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			storeProductId = row[0];
			storeProductName = row[2];
			storeProductCategory = row[3];
			storeProductBrand = row[4];
			storeProductPrice = row[5];
			storeProductQuantity = row[6];
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter New Product Name (x  to not change): ";
	cin >> ws;
	getline(cin, name);
	if (name == "x" || name == "X")
	{
		name = storeProductName;
	}

	cout << "Enter New Product Brand (x  to not change): ";
	getline(cin, brand);
	if (brand == "x" || brand == "X")
	{
		brand = storeProductBrand;
	}
	
	cout << "Enter New Product Category (x  to not change): ";
	getline(cin, category);
	if (category == "x" || category == "X")
	{
		category = storeProductCategory;
	}
		
	cout << "Enter New Product Price (x  to not change): ";
	getline(cin, price);
	if (price == "x" || price == "X")
	{
		price = storeProductPrice;
		stringstream geek(price);
		geek >> dprice;
	}
	else
	{
		stringstream geek(price);
		geek >> dprice;
		while (!dprice)
		{
			cout << " >Please Enter Numbers Only." << endl;
			cout << "Enter New Product Price :";
			cin >> dprice;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	cout << "Enter New Product Quantity in Stock (x  to not change): ";
	getline(cin, quantity);
	if (quantity == "x" || quantity == "X")
	{
		quantity = storeProductQuantity;
		stringstream geek(quantity);
		geek >> iquantity;
	}
	else
	{
		stringstream geek(quantity);
		geek >> iquantity;
		while (!iquantity)
		{
			cout << " >Please Enter Numbers Only." << endl;
			cout << "Enter New Product Quantity in Stock :";
			cin >> iquantity;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	stringstream streamPrice, streamQuantity;
	string sprice, squantity;
	streamPrice << dprice;
	streamPrice >> sprice;
	streamQuantity << iquantity;
	streamQuantity >> squantity;

	string insert_query = "UPDATE `product` SET `productName`= '" + name + "' ,`productCategory`='" + category + "',`productBrand`='" + brand + "',`productPrice`='" + sprice + "',`productQuantity`='" + squantity + "' WHERE `productId`='" + prodid + "'";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	cout << "Press 'm' to Menu and 'u' to Update Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		staffproduct();
	}
	else if (choose == 'u' || choose == 'U')
	{
		StaffUpdateProduct();
	}
	else
	{
		exit(0);
	}
}
//STAFF PRODUCT>VIEW PRODUCT
void StaffViewProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string storeProdId[15];
	string storeProdName[15];
	string storeProdBrand[15];
	string storeProdCategory[15];
	string storeProdPrice[15];
	string storeProdQuantity[15];
	int storeIndex = 0;
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "PRODUCT LIST : " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(7) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(7) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand[storeIndex] = row[4];
			storeProdCategory[storeIndex] = row[3];
			storeProdPrice[storeIndex] = row[5];
			storeProdQuantity[storeIndex] = row[6];
			storeIndex++;
		}
		cout << "____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	qstate = mysql_query(conn, "select productName AS Name from product WHERE productQuantity < 5");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "Notify  : " << row[0] << " Stock running low, please re-stock." << endl;
		}
	}
	else
	{
		cout << "Error find product running low stock!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << endl << "Press 'm' to Menu. ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		staffproduct();
	}
	else
	{
		exit(0);
	}
}
//STAFF PRODUCT>DELETE PRODUCT
void StaffDeleteProduct()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string storeProdId[15];
	string storeProdName[15];
	string storeProdBrand[15];
	string storeProdCategory[15];
	string storeProdPrice[15];
	string storeProdQuantity[15];
	int storeIndex = 0;
	char choose;
	string prodid;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];


	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "PRODUCT LIST : " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(7) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(7) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand[storeIndex] = row[4];
			storeProdCategory[storeIndex] = row[3];
			storeProdPrice[storeIndex] = row[5];
			storeProdQuantity[storeIndex] = row[6];
			storeIndex++;
		}
		cout << "____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter Product ID To Delete The Product . ['m' to Menu] : ";
	cin >> prodid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (prodid == "m" || prodid == "M")
		{
			staffproduct();
		}
		else if (prodid == storeProdId[i])
		{
			itemId[itemIndex] = prodid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Product Id." << endl;
		itemIndex--;
		itemFalse = false;
		StaffDeleteProduct();
	}
	cout << "Are You Sure To Delete This Product ? ['y' or 'N'] : ";
	cin >> choose;
	if (choose == 'y' || choose == 'Y')
	{
		string insert_query = "DELETE FROM `product` WHERE `productId`='" + prodid + "'";

		const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << endl << "Successfully deleted in database." << endl;
			StaffDeleteProduct();
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		StaffDeleteProduct();
	}
}

//EMPLOYEE
int adminemployee()
{
	//variables
	int chooseOneFromMenu = 0;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO EMPLOYEE WINDOW" << endl;
	cout << "1. ADD EMPLOYEE." << endl;
	cout << "2. UPDATE EMPLOYEE." << endl;
	cout << "3. VIEW EMPLOYEE." << endl;
	cout << "4. DELETE EMPLOYEE" << endl;
	cout << "5. EXIT" << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 5)) {
		cout << "Please choose between 1 - 5. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}

	switch (chooseOneFromMenu)
	{
	case 1:
		AddEmployee();
		break;
	case 2:
		UpdateEmployee();
		break;
	case 3:
		ViewEmployee();
		break;
	case 4:
		DeleteEmployee();
		break;
	case 5:
		adminmain();
		break;
	default:
		cout << "Please choose between 1 - 5. ";
		system("PAUSE");
		system("cls");
		adminemployee();
		break;
	}
	system("pause");
	return 0;
}
//EMPLOYEE>ADD EMPLOYEE
void AddEmployee()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string emname;
	string emic;
	string emcontact;
	string emaddress;
	string emposition;
	double emsalary;
	string emusername;
	string empassword;
	string emtype;
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "ADD NEW EMPLOYEE" << endl;

	cin.ignore(1, '\n');
	cout << "Enter Fullname: ";
	getline(cin, emname);
	cout << "Enter Identification Card: ";
	getline(cin, emic);
	cout << "Enter Contact Number: ";
	getline(cin, emcontact);
	cout << "Enter Address: ";
	getline(cin, emaddress);
	cout << "Enter Position: ";
	getline(cin, emposition); 
	cout << "Enter Salary: ";
	while (!(cin >> emsalary)) // or if(cin.fail())
	{
		cout << " >Please Enter Numbers Only." << endl;
		cout << "Enter Salary: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	stringstream streamSalary;
	string semsalary;
	streamSalary << emsalary;
	streamSalary >> semsalary;

	string insert_query = "insert into employee (employeeName, employeeIc, employeeContact, employeeAddress, employeePosition, employeeSalary) values ('" + emname + "','" + emic + "','" + emcontact + "','" + emaddress + "','" + emposition + "','" + semsalary + "')";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminemployee();
	}
	else if (choose == 'a' || choose == 'A')
	{
		AddEmployee();
	}
	else
	{
		exit(0);
	}
}
//EMPLOYEE>UPDATE EMPLOYEE
void UpdateEmployee()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string emid;
	string emname;
	string emic;
	string emcontact;
	string emaddress;
	string emposition;
	string emsalary;
	double demsalary;

	string storeEmplId[15];
	string storeEmplName = "";
	string storeEmplPosition = "";

	// Store Variables
	string storeemid = "";
	string storeemname = "";
	string storeemic = "";
	string storeemcontact = "";
	string storeemaddress = "";
	string storeemposition = "";
	string storeemsalary = "";
	// Variables End

	int storeIndex = 0;
	char choose;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "UPDATE EMPLOYEE" << endl;

	qstate = mysql_query(conn, "select * from employee");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Employee Name"; cout << " | ";
		cout << left << setw(10) << "Position"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[1]; cout << " | ";
			cout << left << setw(10) << row[5]; cout << " | "<< endl;

			storeEmplId[storeIndex] = row[0];
			storeEmplName = row[1];
			storeEmplPosition = row[5];
			storeIndex++;
		}
		cout << "________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Enter Employee ID ['m' to Menu] : ";
	cin >> emid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (emid == "m" || emid == "M")
		{
			adminemployee();
		}
		else if (emid == storeEmplId[i])
		{
			itemId[itemIndex] = emid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Employee Id." << endl;
		itemIndex--;
		itemFalse = false;
		UpdateEmployee();
	}

	string checkuser = "SELECT * FROM employee WHERE employeeId='" + emid + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID : " << row[0] << "\nName : " << row[1] << "\nIC No. : " << row[2] << "\nContact No. : " << row[3] << "\nAddress : " << row[4] << "\nPosition : " << row[5] << "\nSalary : RM" << row[6] << endl << endl;
			storeemid = row[0];
			storeemname = row[1];
			storeemic = row[2];
			storeemcontact = row[3];
			storeemaddress = row[4];
			storeemposition = row[5];
			storeemsalary = row[6];
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter New Employee Name (x to not change): ";
	cin >> ws;
	getline(cin, emname);
	if (emname == "x" || emname == "X")
	{
		emname = storeemname;
	}
	cout << "Enter New Employee IC No. (x to not change): ";
	getline(cin, emic);
	if (emic == "x" || emic == "X")
	{
		emic = storeemic;
	}
	cout << "Enter New Employee Contact (x to not change): ";
	getline(cin, emcontact);
	if (emcontact == "x" || emcontact == "X")
	{
		emcontact = storeemcontact;
	}
	cout << "Enter New Employee Address (x to not change): ";
	getline(cin, emaddress);
	if (emaddress == "x" || emaddress == "X")
	{
		emaddress = storeemaddress;
	}
	cout << "Enter New Employee Position (x to not change): ";
	getline(cin, emposition);
	if (emposition == "x" || emposition == "X")
	{
		emposition = storeemposition;
	}
	cout << "Enter New Employee Salary (x to not change): ";
	getline(cin, emsalary);
	if (emsalary == "x" || emsalary == "X")
	{
		emsalary = storeemsalary;
		stringstream geek(emsalary);
		geek >> demsalary;
	}
	else
	{
		stringstream geek(emsalary);
		geek >> demsalary;
		while (!demsalary)
		{
			cout << " >Please Enter Numbers Only." << endl;
			cout << "Enter New Employee Salary:";
			cin >> demsalary;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	stringstream streamSalary;
	string semsalary;
	streamSalary << demsalary;
	streamSalary >> semsalary;

	string insert_query = "UPDATE `employee` SET `employeeName`= '" + emname + "' ,`employeeIc`='" + emic + "',`employeeContact`='" + emcontact + "',`employeeAddress`='" + emaddress + "',`employeePosition`='" + emposition + "', `employeeSalary`='" + semsalary + "' WHERE `employeeId`='" + emid + "'";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully updated in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	cout << "Press 'm' to Menu or 'u' to Update Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminemployee();
	}
	else if (choose == 'u' || choose == 'U')
	{
		UpdateEmployee();
	}
	else
	{
		exit(0);
	}
}
//EMPLOYEE>VIEW EMPLOYEE
void ViewEmployee()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string emid;
	string emname;
	string emic;
	string emcontact;
	string emaddress;
	string emposition;
	string emsalary;

	string storeEmplId[15];
	string storeEmplName = "";
	string storeEmplIC = "";
	string storeEmplContact = "";
	string storeEmplAddress = "";
	string storeEmplPosition = "";
	string storeEmplSalary = "";
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "EMPLOYEE LIST" << endl;

	qstate = mysql_query(conn, "select * from employee");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Employee Name"; cout << " | ";
		cout << left << setw(10) << "Position"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[1]; cout << " | ";
			cout << left << setw(10) << row[5]; cout << " | " << endl;

			storeEmplId[storeIndex] = row[0];
			storeEmplName = row[1];
			storeEmplPosition = row[5];
			storeIndex++;
		}
		cout << "________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Enter Employee ID ['m' to Menu] : ";
	cin >> emid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (emid == "m" || emid == "M")
		{
			adminemployee();
		}
		else if (emid == storeEmplId[i])
		{
			itemId[itemIndex] = emid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Employee Id." << endl;
		itemIndex--;
		itemFalse = false;
		ViewEmployee();
	}

	string checkuser = "SELECT * FROM employee WHERE employeeId='" + emid + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID : " << row[0] << "\nName : " << row[1] << "\nIC No. : " << row[2] << "\nContact No. : " << row[3] << "\nAddress : " << row[4] << "\nPosition : " << row[5] << "\nSalary : RM" << row[6] << endl << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	system("PAUSE");
	ViewEmployee();
}
//EMPLOYEE>DELETE EMPLOYEE
void DeleteEmployee()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	string emid;
	string storeEmplId[15];
	string storeEmplName = "";
	string storeEmplPosition = "";
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "DELETE EMPLOYEE" << endl;


	qstate = mysql_query(conn, "select * from employee");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Employee Name"; cout << " | ";
		cout << left << setw(10) << "Position"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[1]; cout << " | ";
			cout << left << setw(10) << row[5]; cout << " | " << endl;

			storeEmplId[storeIndex] = row[0];
			storeEmplName = row[1];
			storeEmplPosition = row[5];
			storeIndex++;
		}
		cout << "________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Enter Employee ID You Want To Delete ['m' to Menu] : ";
	cin >> emid;
	for (int i = 0; i < storeIndex; i++)
	{
		if (emid == "m" || emid == "M")
		{
			adminemployee();
		}
		else if (emid == storeEmplId[i])
		{
			itemId[itemIndex] = emid;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Employee Id." << endl;
		itemIndex--;
		itemFalse = false;
		DeleteEmployee();
	}
	cout << "Are You Sure To Delete This Employee ? ['y' or 'N'] : ";
	cin >> choose;
	if (choose == 'y' || choose == 'Y')
	{
		string insert_query = "DELETE FROM `employee` WHERE `employeeId`='" + emid + "'";

		const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << endl << "Successfully deleted in database." << endl;
			DeleteEmployee();
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		DeleteEmployee();
	}
}

//SUPPLIER
int adminsupplier()
{
	//variables
	int chooseOneFromMenu = 0;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO SUPPLIER WINDOW" << endl;
	cout << "1. ADD SUPPLIER." << endl;
	cout << "2. UPDATE SUPPLIER." << endl;
	cout << "3. VIEW SUPPLIER." << endl;
	cout << "4. DELETE SUPPLIER" << endl;
	cout << "5. EXIT" << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 5)) {
		cout << "Please choose between 1 - 5. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}

	switch (chooseOneFromMenu)
	{
	case 1:
		AddSupplier();
		break;
	case 2:
		UpdateSupplier();
		break;
	case 3:
		ViewSupplier();
		break;
	case 4:
		DeleteSupplier();
		break;
	case 5:
		adminmain();
		break;
	default:
		cout << "Please choose between 1 - 5. ";
		system("PAUSE");
		system("cls");
		adminsupplier();
		break;
	}
	system("pause");
	return 0;
}
//STAFF SUPPLIER LIST
int staffsupplier()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	string SuppId;
	string storeSuppId[15];
	string storeSuppName[15];
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "SUPPLIER LIST" << endl;


	qstate = mysql_query(conn, "select * from supplier");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(20) << "Supplier Name"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(20) << row[1]; cout << " | " << endl;

			storeSuppId[storeIndex] = row[0];
			storeSuppName[storeIndex] = row[1];
			storeIndex++;
		}
		cout << "_________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter Supplier ID ['m' to Menu] : ";
	cin >> SuppId;
	for (int i = 0; i < storeIndex; i++)
	{
		if (SuppId == "m" || SuppId == "M")
		{
			staffmain();
		}
		else if (SuppId == storeSuppId[i])
		{
			itemId[itemIndex] = SuppId;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Supplier Id." << endl;
		itemIndex--;
		itemFalse = false;
		staffsupplier();
	}

	string checkuser = "SELECT * FROM supplier WHERE supplierId='" + SuppId + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID : " << row[0] << "\nSupplier Name : " << row[1] << "\nContact No. : " << row[2] << "\nAddress : " << row[3] << endl << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	system("PAUSE");
	staffsupplier();
}
//SUPPLIER>ADD SUPPLIER
void AddSupplier()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string suppname;
	string suppcontact;
	string suppaddress;
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "ADD NEW SUPPLIER" << endl;

	cin.ignore(1, '\n');
	cout << "Enter Supplier Name: ";
	getline(cin, suppname);
	cout << "Enter Contact Number: ";
	getline(cin, suppcontact);
	cout << "Enter Address: ";
	getline(cin, suppaddress);

	string insert_query = "insert into supplier (supplierName, supplierContact, supplierAddress) values ('" + suppname + "','" + suppcontact + "','" + suppaddress + "')";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminsupplier();
	}
	else if (choose == 'a' || choose == 'A')
	{
		AddSupplier();
	}
	else
	{
		exit(0);
	}
}
//SUPPLIER>UPDATE SUPPLIER
void UpdateSupplier()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	string SuppId;
	string suppname;
	string suppcontact;
	string suppaddress;
	string storeSuppId[15];
	string storeSuppName[15];
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];
	char choose;

	//Variables store selected supplier want to update
	string storesupid;
	string storesupname;
	string storesupcontact;
	string storesupaddress;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "UPDATE SUPPLIER" << endl;

	qstate = mysql_query(conn, "select * from supplier");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(20) << "Supplier Name"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(20) << row[1]; cout << " | " << endl;

			storeSuppId[storeIndex] = row[0];
			storeSuppName[storeIndex] = row[1];
			storeIndex++;
		}
		cout << "_________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Enter Supplier ID ['m' to Menu] : ";
	cin >> SuppId;
	for (int i = 0; i < storeIndex; i++)
	{
		if (SuppId == "m" || SuppId == "M")
		{
			adminsupplier();
		}
		else if (SuppId == storeSuppId[i])
		{
			itemId[itemIndex] = SuppId;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Supplier Id." << endl;
		itemIndex--;
		itemFalse = false;
		UpdateSupplier();
	}

	string checkuser = "SELECT * FROM supplier WHERE supplierId='" + SuppId + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID : " << row[0] << "\nSupplier Name : " << row[1] << "\nContact No. : " << row[2] << "\nAddress : " << row[3] << endl << endl;
			storesupid = row[0];
			storesupname = row[1];
			storesupcontact = row[2];
			storesupaddress = row[3];
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter New Supplier Name (x to not change): ";
	cin >> ws;
	getline(cin, suppname);
	if (suppname == "x" || suppname == "X")
	{
		suppname = storesupname;
	}
	cout << "Enter New Supplier Contact (x to not change): ";
	getline(cin, suppcontact);
	if (suppcontact == "x" || suppcontact == "X")
	{
		suppcontact = storesupcontact;
	}
	cout << "Enter New Supplier Address (x to not change): ";
	getline(cin, suppaddress);
	if (suppaddress == "x" || suppaddress == "X")
	{
		suppaddress = storesupaddress;
	}


	string insert_query = "UPDATE `supplier` SET `supplierName`= '" + suppname + "' ,`supplierContact`='" + suppcontact + "',`supplierAddress`='" + suppaddress + "' WHERE `supplierId`='" + SuppId + "'";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully updated in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	cout << "Press 'm' to Menu or 'u' to Update Again Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminsupplier();
	}
	else if (choose == 'u' || choose == 'U')
	{
		UpdateSupplier();
	}
	else
	{
		exit(0);
	}
}
//SUPPLIER>VIEW SUPPLIER
void ViewSupplier()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	string SuppId;
	string storeSuppId[15];
	string storeSuppName[15];
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "SUPPLIER LIST" << endl;


	qstate = mysql_query(conn, "select * from supplier");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(20) << "Supplier Name"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(20) << row[1]; cout << " | " << endl;

			storeSuppId[storeIndex] = row[0];
			storeSuppName[storeIndex] = row[1];
			storeIndex++;
		}
		cout << "_________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Enter Supplier ID ['m' to Menu] : ";
	cin >> SuppId;
	for (int i = 0; i < storeIndex; i++)
	{
		if (SuppId == "m" || SuppId == "M")
		{
			adminsupplier();
		}
		else if (SuppId == storeSuppId[i])
		{
			itemId[itemIndex] = SuppId;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Supplier Id." << endl;
		itemIndex--;
		itemFalse = false;
		ViewSupplier();
	}

	string checkuser = "SELECT * FROM supplier WHERE supplierId='" + SuppId + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID : " << row[0] << "\nSupplier Name : " << row[1] << "\nContact No. : " << row[2] << "\nAddress : " << row[3] << endl << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	system("PAUSE");
	ViewSupplier();
}
//SUPPLIER>DELETE SUPPLIER
void DeleteSupplier()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	string SuppId;
	string storeSuppId[15];
	string storeSuppName[15];
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "DELETE SUPPLIER" << endl;


	qstate = mysql_query(conn, "select * from supplier");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(20) << "Supplier Name"; cout << " | " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(20) << row[1]; cout << " | " << endl;

			storeSuppId[storeIndex] = row[0];
			storeSuppName[storeIndex] = row[1];
			storeIndex++;
		}
		cout << "_________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Enter Supplier ID You Want To Delete ['m' to Menu] : ";
	cin >> SuppId;
	for (int i = 0; i < storeIndex; i++)
	{
		if (SuppId == "m" || SuppId == "M")
		{
			adminsupplier();
		}
		else if (SuppId == storeSuppId[i])
		{
			itemId[itemIndex] = SuppId;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Supplier Id." << endl;
		itemIndex--;
		itemFalse = false;
		DeleteSupplier();
	}
	cout << "Are You Sure To Delete This Supplier ? ['y' or 'N'] : ";
	cin >> choose;
	if (choose == 'y' || choose == 'Y')
	{
		string insert_query = "DELETE FROM `supplier` WHERE `supplierId`='" + SuppId + "'";

		const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << endl << "Successfully deleted in database." << endl;
			DeleteSupplier();
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		DeleteSupplier();
	}
}

//TRANSACTION
void StaffTransaction()
{
	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	char another;
	char choose;
	string ProdId;
	string storeProdId[15];
	string storeProdName[15];
	string storeProdBrand[15];
	string storeProdCategory[15];
	string storeProdPrice[15];
	string storeProdQuantity[15];
	string storetotalprice[15];
	int storeIndex = 0, storeIndexN = 0, storeTransaction = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];
	int quantity, newquantity;
	double totalprice, discount, transactiontotalprice = 0, producttotalprice=0;
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl;
	cout << "TRANSACTION " << endl << endl;
	cout << "Product List : " << endl;

	qstate = mysql_query(conn, "select * from product");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(20) << "Brand"; cout << " | ";
		cout << left << setw(20) << "Category"; cout << " | ";
		cout << left << setw(7) << "Price"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " | ";
			cout << left << setw(20) << row[3]; cout << " |RM";
			cout << left << setw(7) << row[5]; cout << "| ";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeProdId[storeIndex] = row[0];
			storeProdName[storeIndex] = row[2];
			storeProdBrand[storeIndex] = row[4];
			storeProdCategory[storeIndex] = row[3];
			storeProdPrice[storeIndex] = row[5];
			storeProdQuantity[storeIndex] = row[6];
			storeIndex++;
		}
		cout << "____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	qstate = mysql_query(conn, "select productName AS Name from product WHERE productQuantity < 5");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "Notify  : " << row[0] << " Stock running low, please re-stock." << endl;
		}
	}
	else
	{
		cout << "Error find product running low stock!" << mysql_errno(conn) << endl;
	}

	string insert_query = "insert into transaction (date) values ( NOW() )";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Transaction session created." << endl;
	}
	else
	{
		cout << "Transaction session failed!" << mysql_errno(conn) << endl;
	}

	string update_query = "update transaction set date = NOW() WHERE totalprice=0";
	const char* qu = update_query.c_str();
	//cout << update_query << endl;

	qstate = mysql_query(conn, qu);

	if (qstate)
	{
		cout << "Failed To Update Transaction Session!" << mysql_errno(conn) << endl;
	}

SELL:
	cout << endl << "Any Purchase Above RM50 Discount 10%! " << endl;
	cout << "Enter Product ID To Sell [Press 'm' to Menu.] : ";
	cin >> ProdId;
	for (int i = 0; i < storeIndex; i++)
	{
		if (ProdId == "m" || ProdId == "M")
		{
			staffmain();
		}
		else if (ProdId == storeProdId[i])
		{
			itemId[itemIndex] = ProdId;
			itemFalse = false;
			break;
		}
		else
		{
			itemFalse = true;
		}
	}
	if (itemFalse == true)
	{
		cout << "Enter a valid Product ID." << endl;
		itemIndex--;
		itemFalse = false;
		goto SELL;
	}

	string checkuser = "SELECT * FROM product WHERE productId='" + ProdId + "'";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID : " << row[0] << "\nProduct Name : " << row[2] << "\nPrice : RM" << row[5] << "\nStock Available : " << row[6] << endl << endl;
			storeProdName[storeIndexN] = row[2];
			storeProdPrice[storeIndexN] = row[5];
			storeProdQuantity[storeIndexN] = row[6];
			storeIndexN++;
		}
		storeIndexN = 0;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

QUANTITY:
	cout << "Enter Quantity:";
	cin >> quantity;

	if (quantity > strtof((storeProdQuantity[storeIndexN]).c_str(), 0))
	{
		cout << "Insufficient Stock!" << endl;
		goto QUANTITY;
	}
	else if (quantity < strtof((storeProdQuantity[storeIndexN]).c_str(), 0))
	{

		newquantity = stoi((storeProdQuantity[storeIndexN]).c_str(), 0) - quantity;
		totalprice = quantity * strtod((storeProdPrice[storeIndexN]).c_str(), 0);

		stringstream streamQuantity, streamTotalPrice, streamNewQuantity;
		string squantity, stotalprice, snewquantity;
		streamQuantity << quantity;
		streamQuantity >> squantity;
		streamTotalPrice << totalprice;
		streamTotalPrice >> stotalprice;
		streamNewQuantity << newquantity;
		streamNewQuantity >> snewquantity;

		string insert_query = "INSERT INTO salesdetails(ProductId,TransactionId,quantity,price) VALUES ('" + ProdId + "',(SELECT transactionid FROM transaction WHERE totalprice=0 AND date = (SELECT max(date)) ORDER BY transactionid DESC LIMIT 1),'" + squantity + "','" + stotalprice + "')";

		const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << endl << "Added In Cart." << endl;
		}
		else
		{
			cout << "Failed Add In Cart!" << mysql_errno(conn) << endl;
		}

		string update_query = "update product set productQuantity = '" + snewquantity + "' where productId = '" + ProdId + "'";
		const char* qu = update_query.c_str();
		//cout << update_query << endl;

		qstate = mysql_query(conn, qu);

		if (qstate)
		{
			cout << "Failed To Update New Quantity In Product Database!" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		cout << "Please Enter Valid Quantity" << endl;
		goto QUANTITY;
	}

ANOTHER:
	cout << "Add Another Product (y/N): ";
	cin >> another;
	if (another == 'y' || another == 'Y')
	{
		goto SELL;
	}
	else if (another == 'n' || another == 'N')
	{
		qstate = mysql_query(conn, "SELECT a.ProductId, b.productName, a.quantity, b.productPrice, a.price FROM salesdetails a INNER JOIN product b on a.ProductId = b.productId INNER JOIN transaction c on a.transactionid = c.transactionid INNER JOIN (SELECT transactionid FROM transaction WHERE date = (SELECT max(date)) ORDER BY transactionid DESC LIMIT 1) d on c.transactionid = d.transactionid");
		if (!qstate)
		{
			res = mysql_store_result(conn);

			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "|";
			cout << left << setw(7) << "ID"; cout << " | ";
			cout << left << setw(30) << "Product Name"; cout << " | ";
			cout << left << setw(7) << "Price"; cout << " | ";
			cout << left << setw(8) << "Quantity"; cout << "|" << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

			while ((row = mysql_fetch_row(res)))
			{
				cout << "|";
				cout << left << setw(7) << row[0]; cout << " | ";
				cout << left << setw(30) << row[1]; cout << " |RM";
				cout << left << setw(7) << row[3]; cout << "| ";
				cout << left << setw(8) << row[2]; cout << "|" << endl;

				storeProdId[storeTransaction] = row[0];
				storeProdName[storeTransaction] = row[1];
				storeProdQuantity[storeTransaction] = row[2];
				storeProdPrice[storeTransaction] = row[3];
				storetotalprice[storeTransaction] = row[4];
				storeTransaction++;
			}
			cout << "_______________________________________________________________" << endl;

			string select_query = "SELECT transactionid from transaction where totalprice=0 AND date = (SELECT max(date)) ORDER BY transactionid DESC LIMIT 1";

			const char* k = select_query.c_str(); // c_str converts string to constant char and this is required

			qstate = mysql_query(conn, k);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)))
				{
					cout << "Receipt No : " << row[0] << endl;
				}
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}

			for (int i = 0; i < storeTransaction; i++)
			{
				transactiontotalprice += strtod((storetotalprice[i]).c_str(), 0);
			}
			if (transactiontotalprice > 50)
			{
				discount = (transactiontotalprice * 0.10);
				transactiontotalprice = transactiontotalprice - discount;
				cout << "Include Discount 10%" << endl;
			}

			cout << "*********SALE**********" << endl;
			cout << fixed << setprecision(2) << "Total Amount : RM" << transactiontotalprice << endl;
			cout << "***********************" << endl;
			cout << "Payment On " << dt << endl;

			

			stringstream streamtransactiontotalprice;
			string stransactiontotalprice;
			streamtransactiontotalprice << transactiontotalprice;
			streamtransactiontotalprice >> stransactiontotalprice;
			string update_query = "UPDATE transaction SET totalprice = '" + stransactiontotalprice + "' WHERE totalprice=0 AND date = (SELECT max(date)) ORDER BY transactionid DESC LIMIT 1";

			const char* q = update_query.c_str(); // c_str converts string to constant char and this is required

			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << endl << "Successfully added in database." << endl;
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
	}
	else 
	{
		cout << "Next time choose after read the corresponding line." << endl;
		goto ANOTHER;
	}
	// Exit Code
	cout << "Press 'm' to Menu Or Any Other key to exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		staffmain();
	}
	else
	{
		exit(0);
	}	
}


//SALES
int adminsales()
{
	//variables
	int chooseOneFromMenu = 0;

	system("cls");
	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	cout << "WELCOME TO SALES WINDOW" << endl;
	cout << "1. DAILY SALES." << endl;
	cout << "2. SALES REPORT." << endl;
	cout << "3. YEARLY SALES." << endl;
	cout << "4. EXIT." << endl;
	cout << "\nEnter Your Option : ";
	while ((!(cin >> chooseOneFromMenu)) || (chooseOneFromMenu < 1 || chooseOneFromMenu > 4)) {
		cout << "Please choose between 1 - 3. \n";
		// reset error flags
		cin.clear();
		// throw away garbage input
		cin.ignore(10000, '\n');
		cout << "\nEnter Your Option : ";

		// the above two statements prevent infinite loop due to
		// bad stream state
	}

	switch (chooseOneFromMenu)
	{
	case 1:
		AdminDailySales();
		break;
	case 2:
		AdminSalesReport();
		break;
	case 3:
		YearlySales();
		break;
	case 4:
		adminmain();
		break;
	default:
		cout << "Please choose between 1 - 4. ";
		system("PAUSE");
		system("cls");
		adminsales();
		break;
	}
	system("pause");
	return 0;
}

//SALES>DAILY SALES
void AdminDailySales()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	time_t curr_time;
	tm* curr_tm;
	char date_string[100];
	int storeIndex = 0;
	string storeTransId[500];
	string storeProdId[500];
	string storeProdName[500];
	string storeProdPrice[500];
	string storeTTPrice[500];
	string storeSDPrice[500];
	string storeQuantity[500];
	string storeDate[500];
	double totalamount = 0;
	char choose;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;

	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(date_string, 50, "DAILY SALES FOR :  %d %B %Y", curr_tm);
	cout << date_string << endl;

	qstate = mysql_query(conn, "SELECT c.transactionid,a.ProductId, b.productName, a.quantity, c.date, b.productPrice,c.totalprice,a.price, IFNULL(0,0) FROM salesdetails a INNER JOIN product b on a.ProductId = b.productId INNER JOIN transaction c on a.transactionid = c.transactionid INNER JOIN (SELECT transactionid FROM transaction WHERE totalprice>1 AND DAY(date) = DAY(CURRENT_DATE()) AND MONTH(date) = MONTH(CURRENT_DATE()) AND YEAR(date) = YEAR(CURRENT_DATE()) ORDER BY transactionid ASC) d on c.transactionid = d.transactionid ORDER BY `c`.`date`");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(7) << "R. No."; cout << " | ";
		cout << left << setw(7) << "ID"; cout << " | ";
		cout << left << setw(30) << "Product Name"; cout << " | ";
		cout << left << setw(7) << "Qtty"; cout << " | ";
		cout << left << setw(20) << "Date" << " |  ";
		cout << left << setw(8) << "P.Price"; cout << " | ";
		cout << left << setw(8) << "T.T.Price"; cout << "|" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(7) << row[0]; cout << " | ";
			cout << left << setw(7) << row[1]; cout << " | ";
			cout << left << setw(30) << row[2]; cout << " | ";
			cout << left << setw(7) << row[3]; cout << " | ";
			cout << left << setw(20) << row[4]; cout << " |RM";
			cout << left << setw(8) << row[5]; cout << " |RM";
			cout << left << setw(8) << row[6]; cout << "|" << endl;

			storeTransId[storeIndex] = row[0];
			storeProdId[storeIndex] = row[1];
			storeProdName[storeIndex] = row[2];
			storeQuantity[storeIndex] = row[3];
			storeDate[storeIndex] = row[4];
			storeProdPrice[storeIndex] = row[5];
			storeTTPrice[storeIndex] = row[6];
			storeSDPrice[storeIndex] = row[7];
			
			storeIndex++;
		}
		cout << "_____________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	string select_query = "SELECT totalprice as price,SUM(totalprice) as totall FROM transaction WHERE totalprice>1 AND DAY(date) = DAY(CURRENT_DATE()) AND MONTH(date) = MONTH(CURRENT_DATE()) AND YEAR(date) = YEAR(CURRENT_DATE())";

	const char* k = select_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, k);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			cout << "*************************" << endl;
			cout << "Total : RM" << row[1] << endl;
			cout << "*************************" << endl;
		}
	}
	else
	{
		cout << "Failed To Calculate Total Sales" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'm' to Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminsales();
	}
	else
	{
		exit(0);
	}
}

//SALES>SALES REPORT
void AdminSalesReport()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	string storeSalesId[500];
	string storeProdName[500];
	string storeQuantity[500];
	string storeTransactions[500];
	string storeAmount[500];
	string storeDate[500];
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];
	char choose;
	time_t curr_time;
	tm* curr_tm;
	char date_string[100];
	double totalamount = 0;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;

	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(date_string, 50, "SALES REPORT FOR :  %B %Y", curr_tm);
	cout << date_string << endl << endl;

	cout << "Top 5 Selling :" << endl;

	qstate = mysql_query(conn, "SELECT a.productName as PRODUCT,SUM(b.quantity) as QUANTITY FROM salesdetails b INNER JOIN product a on a.productId = b.ProductId INNER JOIN transaction c on b.TransactionId = c.transactionid WHERE MONTH(c.date) = MONTH(CURRENT_DATE()) AND YEAR(c.date) = YEAR(CURRENT_DATE()) GROUP BY PRODUCT ORDER BY QUANTITY DESC LIMIT 5");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(30) << "Product"; cout << " | ";
		cout << left << setw(8) << "Quantity"; cout << "|  " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(30) << row[0]; cout << " | ";
			cout << left << setw(8) << row[1]; cout << "|" << endl;

			storeProdName[storeIndex] = row[0];
			storeQuantity[storeIndex] = row[1];
			storeIndex++;
		}
		cout << "___________________________________________" << endl << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "Sales By Week :" << endl;
	qstate = mysql_query(conn, "SELECT FROM_DAYS(TO_DAYS(date) -MOD(TO_DAYS(date) -2, 7)) AS WEEK_BEGIN, COUNT(*) AS TRANSACTIONS, SUM(totalprice) AS TOTAL FROM transaction WHERE totalprice>0 AND MONTH(date) = MONTH(CURRENT_DATE()) AND YEAR(date) = YEAR(CURRENT_DATE()) GROUP BY FROM_DAYS(TO_DAYS(date) -MOD(TO_DAYS(date) -2, 7)) ORDER BY FROM_DAYS(TO_DAYS(date) -MOD(TO_DAYS(date) -2, 7))");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(15) << "Week Begin"; cout << " | ";
		cout << left << setw(15) << "Transactions"; cout << " | ";
		cout << left << setw(15) << "Amount"; cout << " |" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(15) << row[0]; cout << " | ";
			cout << left << setw(15) << row[1]; cout << " |RM";
			cout << left << setw(15) << row[2]; cout << "|" << endl;

			storeDate[storeIndex] = row[0];
			storeTransactions[storeIndex] = row[1];
			storeAmount[storeIndex] = row[2];
			storeIndex++;
		}
		cout << "______________________________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	for (int i = 0; i < storeIndex; i++)
	{
		totalamount += strtof((storeAmount[i]).c_str(), 0);
	}

	cout << "******************************************************" << endl;
	cout << "Grand Total : RM" << totalamount << endl;
	cout << "******************************************************" << endl;

	// Exit Code
	cout << "Press 'm' to Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminsales();
	}
	else
	{
		exit(0);
	}
}

void YearlySales()
{
	// Initial Load
	system("cls");
	// Initial Load End

	//Variables
	string storeMonth[15];
	string storeAmount[15];
	int storeIndex = 0;
	int itemIndex = 0;
	bool itemFalse = false;
	string itemId[15];
	char choose;
	time_t curr_time;
	tm* curr_tm;
	char date_string[100];
	double totalamount = 0;
	int graphlength  = 0;

	cout << "******************************" << endl;
	cout << "GADGET STORE MANAGEMENT SYSTEM" << endl;
	cout << "******************************" << endl << endl;
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(date_string, 50, "SALES REPORT FOR :  %Y", curr_tm);
	cout << date_string << endl;

	cout << "Sales By Month:" << endl;

	qstate = mysql_query(conn, "SELECT MONTHNAME(date) as MONTH, SUM(totalprice) as AMOUNT FROM transaction WHERE totalprice>1 AND YEAR(date) = YEAR(CURRENT_DATE()) GROUP BY MONTH(date) ORDER BY AMOUNT DESC ");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|";
		cout << left << setw(10) << "Month"; cout << " |";
		cout << left << setw(20) << "Amount[Descending Order]"; cout << "| " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		while ((row = mysql_fetch_row(res)))
		{
			cout << "|";
			cout << left << setw(10) << row[0]; cout << " |RM ";
			cout << left << setw(20) << row[1]; cout << " | " << endl;

			storeMonth[storeIndex] = row[0];
			storeAmount[storeIndex] = row[1];
			storeIndex++;

		}
		cout << "______________________________________" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'm' to Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		adminsales();
	}
	else
	{
		exit(0);
	}
}
