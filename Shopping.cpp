#include <iostream>
#include <string>
#include <iomanip>

struct StoreItems{	//This structure will contain information of store's products (item #, name of item, price of item)
	int itemNumber;
	std::string itemName;
	double price;
	
	StoreItems(): itemName(""), price(0) {}		/*Default constructor. When a StoreItems structure is declared without initialization,
												  these will be the default values. See figure 1*/ 

	StoreItems(int itemNum, std::string name, double cost): itemNumber(itemNum), itemName(name), price(cost){}
												/*Another constructor, but needs arguments to input values. See figure 2*/
};a

struct CustomerItems {	//This will be the node structure for the linked list of items 
	StoreItems cartItems;	//Data value
	CustomerItems* next;	//Pointer address
	CustomerItems* previous;

	CustomerItems(StoreItems* storeItems) : cartItems(*storeItems), next(NULL), previous(NULL){}
								//To create a new node, a storeItem should be passed as an argument, then assign the storeItem as cartItem (data value)
};								//See figure 3.

struct CustomerCart{	//Structure that will represent a customer cart. This struct will contain the linked list aka nodes of items
	CustomerItems* head;		//Create a head node
	CustomerCart() : head(NULL){}	//Default constructor. Creating a new cart initializes the head node to point to null

	void addToCart(StoreItems* storeItems){		//To call this function, a store item must be passed as argument
		CustomerItems* newItem = new CustomerItems(storeItems);		//Figure 3.
		if (head == NULL){		//Checks if head is pointing to null. If true, it means that the new node is the first node in the list
			head = newItem;		//Points the head to the very first added node.
		}
		else{		//If there is nodes already, add the new node at the last of the list
			CustomerItems* temp = head;		//Create a temp node pointing to head for traversing
			while(temp->next != NULL){		//Checks if the current node is the last node in the list
				temp = temp->next;			//If not, set the next node as current node
			}
			temp->next = newItem;	//When the temp reaches last node, point the last node's next pointer to the newly added node
		}
	}

	void viewCart(){	//Function for viewing the customer's cart
		CustomerItems* temp = head;		//Create a temp node again for traversal
		while(temp != NULL){	//As long as the node is not empty, print the contents.
			std::cout << std::setw(15) << std::left << temp->cartItems.itemName << temp->cartItems.price << '\n';
			temp = temp->next;	//Move on to the next node
		}
	}

	double computeTotal(){
		double totalPrice;
		CustomerItems* temp = head;
		while(temp != NULL){
			totalPrice += temp->cartItems.price;
			temp = temp->next;
		}
		return totalPrice;
	}
};

void pressContinue();
void displayProducts(StoreItems* storeItems, int numItems);	//Function to display store products
void selectAdd(CustomerCart* cart, StoreItems* storeItems);
void checkOut(CustomerCart* cart);

int main(){

	CustomerCart* cart = new CustomerCart;
	int numItems = 5;

	//Initialize the store products
	StoreItems* storeItems = new StoreItems[numItems];	//Figure 1. Struct array declared but no initialization. Item data takes default values
	storeItems[0] = StoreItems(1, "Apple", 23.4);
	storeItems[1] = StoreItems(2, "Banana", 4.21);
	storeItems[2] = StoreItems(3, "Cat", 88.2);
	storeItems[3] = StoreItems(4, "Dog", 32.74);
	storeItems[4] = StoreItems(5, "Eggplant", 19.05);	//Figure 2. Created new StoreItems with initalized values, then assigns it to each index.
	
	int option;
	
	do{
		displayProducts(storeItems, numItems);
		std::cout << "1 - Add item to cart\n"
				  << "2 - View cart\n"
				  << "3 - Check out\n"
				  << "Enter option: ";
		std::cin >> option;

		switch(option){
		case 1:
			selectAdd(cart, storeItems);
			pressContinue();
			break;
		case 2:
			system("cls");
			cart->viewCart();
			pressContinue();
			break;
		case 3:
			system("cls");
			checkOut(cart);
			pressContinue();
			break;
		}
	}while(option != 4);
	
	return 0;
}

void pressContinue(){
	std::cout << "Press any key to continue...\n";
	std::cin.ignore();
    std::cin.get();
	system("cls");
}
void displayProducts(StoreItems* storeItems, int numItems){
	for(int i = 0; i < numItems; i++){
		std::cout << "Item #" << i + 1
				  << ": " << std::setw(15) << std::left << storeItems[i].itemName 
                  << " Price: " << storeItems[i].price << '\n';
	}
	std::cout << '\n';
}
void selectAdd(CustomerCart* cart, StoreItems* storeItems){
	int itemNumber;
	std::cout << "Select item to add to cart: ";
	std::cin >> itemNumber;
	cart->addToCart(&storeItems[itemNumber - 1]);
	system("cls");
	std::cout << "Add success!\n";
}
void checkOut(CustomerCart* cart){
	double totalPrice = cart->computeTotal();
	std::cout << "Your total is P" << totalPrice << '\n';
}