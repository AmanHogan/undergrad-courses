from tkinter import *
import sqlite3
import os
from datetime import date


scrollbars_contents = []
scrollbar_reference = []
startAndEndDates = []

class ReturnRental:

    def __init__(self):

        # define rental window properties
        self.return_rental = Toplevel()
        self.return_rental.title('Find Vehicles')

        # define MENUS, FRAMES, LABELS, AND ENTRIES ##################################################################
        self.vehicle_menu = LabelFrame(self.return_rental, text="Vehicle Menu", padx=5, pady=10)
        self.vehicle_menu.pack()

        self.vehicle_id_frame = LabelFrame(self.return_rental, text="Vehicle ID", padx=5, pady=10)
        self.vehicle_id_frame.pack()
        self.vehicle_id_label = Label(self.vehicle_id_frame, text='Enter VIN')
        self.vehicle_id_label.pack(side=LEFT)
        self.vehicle_id_entry = Entry(self.vehicle_id_frame, width=30)
        self.vehicle_id_entry.pack(side=LEFT)

        self.return_date_frame = LabelFrame(self.return_rental, text="End Date of Desired Rental", padx=5, pady=10)
        self.return_date_frame.pack()
        self.return_date_label = Label(self.return_date_frame, text='End Date (YYYY-MM-DD)')
        self.return_date_label.pack(side=LEFT)
        self.return_date_entry = Entry(self.return_date_frame, width=30)
        self.return_date_entry.pack(side=LEFT)

        self.cust_name_frame = LabelFrame(self.return_rental, text="Customer Name", padx=5, pady=10)
        self.cust_name_frame.pack()
        self.cust_name_label = Label(self.cust_name_frame, text='Enter Customer Name')
        self.cust_name_label.pack(side=LEFT)
        self.cust_name_entry = Entry(self.cust_name_frame, width=30)
        self.cust_name_entry.pack(side=LEFT)



        # Define Button to find rentals with selected information
        self.find_returns = Button(self.return_rental, text='Find', command=self.find_vehicles)
        self.find_returns.pack(fill=BOTH)

        self.vehicles_found_label = Label(self.return_rental, text='Vehicles Found ')
        self.vehicles_found_label.pack(side=LEFT)

    def find_vehicles(self):

        # define the menu containing list of available menus
        found_returns = LabelFrame(self.return_rental, text="Found Returns", padx=5, pady=10)
        found_returns.pack()

        # Refresh the scrollbar list each time it is called
        self.clear_scrollbar()

        # Perform Query to find available rentals that fit criteria
        db_connection_find_rentals = sqlite3.connect('p2.db')
        button_cursor = db_connection_find_rentals.cursor()


        find_cust_query = f"SELECT Name, VEHICLE.VehicleID, SUM(TotalAmount) FROM VEHICLE, CUSTOMER, RENTAL WHERE " \
                          f"CUSTOMER.CustID = RENTAL.CustID AND VEHICLE.VehicleID = RENTAL.VehicleID AND ReturnDate = " \
                          f"'{self.return_date_entry.get()}' AND VEHICLE.VehicleID = '{self.vehicle_id_entry.get()}' " \
                          f"AND CUSTOMER.Name = '{self.cust_name_entry.get()}' GROUP BY Name, CUSTOMER.CustID;"

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
        scrollbar = Scrollbar(self.return_rental)
        scrollbar.pack(side=LEFT, fill="y")
        scroll_list = Listbox(self.return_rental, yscrollcommand=scrollbar.set)
        scrollbars_contents.append(scroll_list)
        scrollbar_reference.append(scrollbar)
        scroll_list.bind('<<ListboxSelect>>', self.on_click_confirm)

        # For each query insert it into the query list
        for row in scrollbar_list_results:
            scroll_list.insert(END,
                               "Name: " + str(row[0]) + ", VIN: " + str(row[1]) + ", Total Amount: $" + str(row[2]))

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



    def pay_rental(self, value):

        value = value.replace("Name: ", "")
        value = value.replace("VIN: ", "")
        value = value.replace("Total Amount: $", "")
        value_list = value.split(',')

        self.name_value = value_list[0]
        self.vin_value = value_list[1]
        self.total_value = value_list[2]


        self.finalize_rental_window = Toplevel()
        self.finalize_rental_window.title('Return Rental')
        self.finalize_rental_window.geometry("300x300")

        find_rental_menu = LabelFrame(self.finalize_rental_window, text="Confirm Return", padx=5, pady=10)
        find_rental_menu.grid(row=0, column=0)

        cust_name_entry = Entry(find_rental_menu, width=30)
        cust_name_entry.grid(row=0, column=1, padx=20)
        cust_name_entry.insert(END, self.name_value)
        cust_name_label = Label(find_rental_menu, text='Customer Name')
        cust_name_label.grid(row=0, column=0)


        vin_entry = Entry(find_rental_menu, width=30)
        vin_entry.grid(row=1, column=1)
        vin_entry.insert(END, self.vin_value)
        vin_label = Label(find_rental_menu, text='VIN')
        vin_label.grid(row=1, column=0)


        self.cust_payment = Entry(find_rental_menu, width=30)
        self.cust_payment.grid(row=2, column=1)
        self.cust_payment.insert(END, self.total_value)
        cust_payment_label = Label(find_rental_menu, text='Customer Payment Total')
        cust_payment_label.grid(row=2, column=0)

        confirm_return_button = Button(self.finalize_rental_window, text='Confirm', command=self.confirm_return)
        confirm_return_button.grid()

    def on_click_confirm(self, evt):
        w = evt.widget
        index = int(w.curselection()[0])
        value = w.get(index)
        print('You selected item %d: "%s"' % (index, value))
        self.pay_rental(value)

    def confirm_return(self):
        submit_conn = sqlite3.connect('p2.db')
        submit_cur1 = submit_conn.cursor()
        select_query = f"SELECT CustID FROM CUSTOMER WHERE Name = '{self.cust_name_entry.get()}';"
        submit_cur1.execute(select_query)
        cust_id_found = list(submit_cur1)

        temp = (str(cust_id_found[0])).strip(',()')
        self.cust_id_value = temp

        self.current_date = today = date.today()
        self.date = today.strftime("%Y-%m-%d")
        submit_cur2 = submit_conn.cursor()
        select_query = f"UPDATE RENTAL SET PaymentDate = '{self.date}', TotalAmount = " \
                       f"{int(self.total_value) - int(self.cust_payment.get())} WHERE CustID = " \
                       f"{self.cust_id_value} AND VehicleID = '{self.vehicle_id_entry.get()}' " \
                       f"AND ReturnDate = '{self.return_date_entry.get()}'; "
        submit_cur2.execute(select_query)

        submit_conn.commit()
        submit_conn.close()
        self.finalize_rental_window.destroy()

