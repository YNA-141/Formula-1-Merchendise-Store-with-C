Formula-1 Merchandise Store Inventory and Billing System Project Report

1. Introduction
The project focuses on developing a program based on C-language that is intended to manage inventory and billing for a "Formula-1 Merchandise Store." The system is built around two primary user roles: Seller and Customer. The Seller has full administrative control over the store's inventory; including adding, editing, deleting and viewing items as well as viewing sales history. The Customer can register, log in, browse items, search, sort by price and purchase merchandise which also updates the inventory and generates a bill. 
2. Methodology
The project is structured using the C programming language and employs several key features:
Structure Definitions: Two main structures are defined:
struct Accounts: Stores user (seller/customer) details like name, email, password and birth year.
struct item: Stores merchandise details such as ID, name, color, description, stock quantity and price.
File Handling:
Inventory data is stored in a text file (shopitems.txt) using functions like loadItems and save. Data is read or written line by line using fscanf and fprintf.
User account data is stored in binary files (sellerID.dat, customerID.dat) using fwrite and fread to handle the login structure efficiently. The owner login email is: seller@f1.com and password is: admin.
Sales history is appended to a text file (billedCustomers.txt) using fprintf.
Modular Functions: The code is organized into distinct functions for each task, enhancing readability and maintainability:
Inventory Management: loadItems, save, viewITEMS, addITEM, editITEM, deleteITEM.
User Authentication: createacc, sellerlogin, customerlogin.
Shopping/Billing: billDetail, cart, search, sorting.
Sorting Algorithm: The sorting function implements the Bubble Sort algorithm to arrange items by price in ascending (low to high) or descending (high to low) order based on the user input.
Search Functionality: The search function utilizes the strstr function from <string.h> to perform a simple substring match against item names, providing basic search capability.
Discount Logic: A simple discount mechanism is implemented in billDetail: a 5% discount is applied generally and a higher 15% discount is applied for purchases of more than 5 units of an item.
Main Loop: The main function presents a clear initial menu for selecting either Seller or Customer login, managing the overall program flow.
3. Uses
The Formula-1 Merchandise Store system can be used for:
Inventory Control: Sellers can maintain an up to date record of product stock, prices and details, ensuring they know what is available.
Sales Management: Allows for the efficient processing of customer purchases, calculating totals, applying discounts and updating stock levels automatically.
Sales Tracking: The system logs a summary of every transaction to billedCustomers.txt, providing a basic sales history for the Seller to review.
Customer Experience: Customers can easily browse the inventory, search for specific items and sort products to find the best deals, improving the shopping experience.
4. Limitations
While functional, the current implementation has several significant limitations, especially for a real world application:
Security Flaws:
Plain Text Passwords: Passwords for both sellers and customers are stored directly in binary files (.dat) without any form of encryption. This is a critical security vulnerability.
Input Handling:
Buffer Overflow Risk: Many scanf does not specify the size. If a user enters a string longer than the allocated array size, it will lead to a buffer overflow, corrupting adjacent memory.
Whitespace Issues: The use of scanf instead of fgets for reading string inputs will only read up to the first whitespace. This prevents items, colors or details from having spaces. The use of underspace has to be resorted to instead of space.
Error Handling: The system does not check if the entered stock or price are negative values which would be illogical for an inventory system.
Data Management and Efficiency:
Full Inventory Reload or Save: The loadItems function reads the entire inventory into memory and the save function writes the entire inventory back to the file for every single operation. This is inefficient for large inventories and causes performance degradation.
Linear Search: The item search and ID lookups are done using a basic  for loop which is slow and inefficient.
Bubble Sort: The sorting function uses Bubble Sort which is one of the least efficient sorting algorithms, making the sorting operation slow for a high volume of items.
User Interface:
Lack of Readability: The details field of an item is not displayed anywhere in the Seller or Customer view, making it functionally useless.
5. Conclusion
The C program successfully implements a foundational menu driven store management and billing system. It demonstrates a solid understanding of C structures, file management and basic programming techniques. The separation of user roles (Seller and Customer) and the implementation of essential features like inventory (Create, Read, Update, Delete), searching, sorting and billing with discount logic are noteworthy achievements. However, working on the limitations will result in an even better experience for the users. The current project serves as an excellent proof of concept and good starting point for developing a more secure and efficient application.
Inspirations:  formula1.com and nike.com 
