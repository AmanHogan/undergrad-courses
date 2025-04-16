from tkinter import *
import sqlite3
import os
from datetime import date


scrollbars_contents = []
scrollbar_reference = []
startAndEndDates = []

class FindCustomer:

    def __init__(self):

        # define rental window properties
        self.customer_window = Toplevel()
        self.customer_window.title('Find Customers')

        # define MENUS, FRAMES, LABELS, AND ENTRIES ##################################################################
        self.rental_menu = LabelFrame(self.customer_window, text="Customer Menu", padx=5, pady=10)
        self.rental_menu.pack()

        self.cust_id_frame = LabelFrame(self.customer_window, text="Customer ID", padx=5, pady=10)
        self.cust_id_frame.pack()
        self.cust_id_label = Label(self.cust_id_frame, text='Enter ID Number')
        self.cust_id_label.pack(side=LEFT)
        self.cust_id_entry = Entry(self.cust_id_frame, width=30)
        self.cust_id_entry.pack(side=LEFT)

        self.cust_name_frame = LabelFrame(self.customer_window, text="Customer Name", padx=5, pady=10)
        self.cust_name_frame.pack()
        self.cust_name_label = Label(self.cust_name_frame, text='Enter Customer Name')
        self.cust_name_label.pack(side=LEFT)
        self.cust_name_entry = Entry(self.cust_name_frame, width=30)
        self.cust_name_entry.pack(side=LEFT)


        # Define Button to find rentals with selected information
        self.find_customers_button = Button(self.customer_window, text='Find', command=self.find_cust)
        self.find_customers_button.pack(fill=BOTH)

        self.cust_found_label = Label(self.customer_window, text='Customers Found ')
        self.cust_found_label.pack(side=LEFT)

    def find_cust(self):

        # define the menu containing list of available menus
        found_cust_frame = LabelFrame(self.customer_window, text="Found Customers", padx=5, pady=10)
        found_cust_frame.pack()

        # Refresh the scrollbar list each time it is called
        self.clear_scrollbar()

        # Perform Query to find available rentals that fit criteria
        db_connection_find_rentals = sqlite3.connect('p2.db')
        button_cursor = db_connection_find_rentals.cursor()

        find_cust_query = ""

        if self.cust_id_entry.get() and not self.cust_name_entry.get():
            find_cust_query = f"SELECT DISTINCT CUSTOMER.CustID, Name, SUM(TotalAmount) as 'Remaining Balance' " \
                              f"FROM RENTAL, CUSTOMER WHERE RENTAL.CustID = CUSTOMER.CustID AND CUSTOMER.CustID = {self.cust_id_entry.get()} GROUP BY CUSTOMER.CustID " \
                              f"UNION SELECT DISTINCT Customer.CustID, Name, SUM(0) as 'Remaining Balance' " \
                              f"FROM CUSTOMER WHERE CUSTOMER.CustID = {self.cust_id_entry.get()} GROUP BY CUSTOMER.CustID;"
            button_cursor.execute(find_cust_query)

        elif not self.cust_id_entry.get() and self.cust_name_entry.get():
            find_cust_query = f"SELECT DISTINCT CUSTOMER.CustID, Name, SUM(TotalAmount) as 'Remaining Balance' " \
                              f"FROM RENTAL, CUSTOMER WHERE RENTAL.CustID = CUSTOMER.CustID AND CUSTOMER.Name = '{self.cust_name_entry.get()}' GROUP BY CUSTOMER.CustID " \
                              f"UNION SELECT DISTINCT Customer.CustID, Name, SUM(0) as 'Remaining Balance' " \
                              f"FROM CUSTOMER WHERE CUSTOMER.Name = '{self.cust_name_entry.get()}' GROUP BY CUSTOMER.CustID;"
            button_cursor.execute(find_cust_query)

        elif not self.cust_id_entry.get() and not self.cust_name_entry.get():
            find_cust_query = f"SELECT DISTINCT CUSTOMER.CustID, Name, SUM(TotalAmount) as 'Remaining Balance' " \
                              f"FROM RENTAL, CUSTOMER WHERE RENTAL.CustID = CUSTOMER.CustID GROUP BY CUSTOMER.CustID " \
                              f"UNION SELECT DISTINCT Customer.CustID, Name, SUM(0) as 'Remaining Balance' " \
                              f"FROM CUSTOMER GROUP BY CUSTOMER.CustID;"
            button_cursor.execute(find_cust_query)

        elif self.cust_id_entry.get() and self.cust_name_entry.get():
            find_cust_query = f"SELECT DISTINCT CUSTOMER.CustID, Name, SUM(TotalAmount) as 'Remaining Balance' " \
                              f"FROM RENTAL, CUSTOMER WHERE RENTAL.CustID = CUSTOMER.CustID AND CUSTOMER.CustID = " \
                              f"{self.cust_id_entry.get()} AND CUSTOMER.Name = '{self.cust_name_entry.get()}' GROUP BY CUSTOMER.CustID, CUSTOMER.NAme " \
                              f"UNION SELECT DISTINCT Customer.CustID, Name, SUM(0) as 'Remaining Balance' " \
                              f"FROM CUSTOMER WHERE CUSTOMER.CustID = {self.cust_id_entry.get()} AND CUSTOMER.Name = '{self.cust_name_entry.get()}' GROUP BY CUSTOMER.CustID, CUSTOMER.Name ;"
            button_cursor.execute(find_cust_query)

        db_connection_find_rentals.commit()

        # Get a list of return results of query
        find_cust_query = list(button_cursor)

        # Debug print statements
        for line in find_cust_query:
            print(str(line))

        # create scrollbar
        self.create_scrollbar(find_cust_query)

        # close database connection
        db_connection_find_rentals.close()

    def create_scrollbar(self, scrollbar_list_results):

        # Create scrollbar contents using the query results
        scrollbar = Scrollbar(self.customer_window)
        scrollbar.pack(side=LEFT, fill="y")
        scroll_list = Listbox(self.customer_window, yscrollcommand=scrollbar.set)
        scrollbars_contents.append(scroll_list)
        scrollbar_reference.append(scrollbar)
        scroll_list.bind('<<ListboxSelect>>', self.nothing())

        # For each query insert it into the query list
        for row in scrollbar_list_results:
            scroll_list.insert(END, "Cust ID: " + str(row[0]) + ", Name: " + str(row[1]) + ", Remaining Balance: $" + str(
                row[2]))

        scroll_list.pack(side="left", fill="both", expand=True)
        scrollbar.config(command=scroll_list.yview)

    def clear_scrollbar(self):

        # clear scrollbar
        if scrollbars_contents:
            scroll_c = scrollbars_contents[0]
            scroll_c.destroy()
            scrollbars_contents.remove(scroll_c)

            scrollbar_r = scrollbar_reference[0]
            scrollbar_r.destroy()
            scrollbar_reference.remove(scrollbar_r)

    def nothing(self):
        pass
