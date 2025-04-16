from tkinter import *
import sqlite3
import os
from datetime import date



scrollbars_contents = []
scrollbar_reference = []
startAndEndDates = []


class RentalManager:

    def __init__(self):

        # define rental window properties
        self.rental_window = Toplevel()
        self.rental_window.title('Find/Add Rentals')

        # define MENUS, FRAMES, LABELS, AND ENTRIES ##################################################################
        self.rental_menu = LabelFrame(self.rental_window, text="Rental Menu", padx=5, pady=10)
        self.rental_menu.pack()

        self.start_date_frame = LabelFrame(self.rental_window, text="Start date of desired Rental", padx=5, pady=10)
        self.start_date_frame.pack()
        self.start_date_label = Label(self.start_date_frame, text='Start Date (YYYY-MM-DD)')
        self.start_date_label.pack(side=LEFT)
        self.start_date_entry = Entry(self.start_date_frame, width=30)
        self.start_date_entry.pack(side=LEFT)

        self.return_date_frame = LabelFrame(self.rental_window, text="End Date of Desired Rental", padx=5, pady=10)
        self.return_date_frame.pack()
        self.return_date_label = Label(self.return_date_frame, text='End Date (YYYY-MM-DD)')
        self.return_date_label.pack(side=LEFT)
        self.return_date_entry = Entry(self.return_date_frame, width=30)
        self.return_date_entry.pack(side=LEFT)

        self.year_frame = LabelFrame(self.rental_window, text="Year of Desired Car", padx=5, pady=10)
        self.year_frame.pack()
        self.year_label = Label(self.year_frame, text='Year                                    ')
        self.year_label.pack(side=LEFT)
        self.year_entry = Entry(self.year_frame, width=30)
        self.year_entry.pack(side=LEFT)

        self.type_frame = LabelFrame(self.rental_window, text="Type of Desired Car", padx=5, pady=10)
        self.type_frame.pack()
        self.type_label = Label(self.type_frame, text='Type                                    ')
        self.type_label.pack(side=LEFT)
        self.type_entry = Entry(self.type_frame, width=30)
        self.type_entry.pack(side=LEFT)

        self.category_frame = LabelFrame(self.rental_window, text="Category of Desired Car", padx=5, pady=10)
        self.category_frame.pack()
        self.category_label = Label(self.category_frame, text='Category                            ')
        self.category_label.pack(side=LEFT)
        self.category_entry = Entry(self.category_frame, width=30)
        self.category_entry.pack(side=LEFT)

        # Define Button to find rentals with selected information
        self.find_cars_button = Button(self.rental_window, text='Find', command=self.find_rental)
        self.find_cars_button.pack(fill=BOTH)

        self.available_rents_label = Label(self.rental_window, text='Available Rentals ')
        self.available_rents_label.pack(side=LEFT)

        self.current_date = today = date.today()
        self.date = today.strftime("%Y-%m-%d")
        self.rental_type_value = 0
        self.qty = 0
        self.rate_value = 0
        self.total_amount_value = 0
        self.cust_id_value = 0


    def find_rental(self):

        # define the menu containing list of available menus
        available_rentals_menu = LabelFrame(self.rental_window, text="Available Rentals", padx=5, pady=10)
        available_rentals_menu.pack()

        # Refresh the scrollbar list each time it is called
        self.clear_scrollbar()

        # Perform Query to find available rentals that fit criteria
        db_connection_find_rentals = sqlite3.connect('p2.db')
        button_cursor = db_connection_find_rentals.cursor()

        find_rental_query = f"SELECT DISTINCT RENTAL.VehicleID, Category, Type, Year FROM RENTAL, VEHICLE WHERE RENTAL.VehicleID = " \
                            f" VEHICLE.VehicleID AND VEHICLE.TYPE = {self.type_entry.get()}  AND VEHICLE.Category = {self.category_entry.get()} AND Year = {self.year_entry.get()} " \
                            f" AND NOT (StartDate >= '{self.start_date_entry.get()}'  AND ReturnDate <= '{self.start_date_entry.get()}' OR StartDate <= '{self.start_date_entry.get()}'  AND (ReturnDate <= '{self.return_date_entry.get()}' AND ReturnDate > '{self.start_date_entry.get()}') OR " \
                            f"(StartDate >= '{self.start_date_entry.get()}' AND StartDate <= '{self.return_date_entry.get()}')  AND ReturnDate >= '{self.return_date_entry.get()}') " \
                            f"GROUP BY VEHICLE.VehicleID UNION SELECT VEHICLE.VehicleID, Category, Type, Year FROM VEHICLE WHERE " \
                            f"VEHICLE.VehicleID NOT IN (SELECT RENTAL.VehicleID FROM RENTAL) AND VEHICLE.TYPE = {self.type_entry.get()}  AND VEHICLE.Category = {self.category_entry.get()} AND Year = {self.year_entry.get()};"

        button_cursor.execute(find_rental_query)
        db_connection_find_rentals.commit()

        # Get dates and store them
        self.start_date_value = self.start_date_entry.get()
        self.return_date_value = self.return_date_entry.get()

        # Get number of days rented
        s1 = self.start_date_value.split("-")
        s2 = date(int(s1[0]), int(s1[1]), int(s1[2]))
        r1 = self.return_date_value.split("-")
        r2 = date(int(r1[0]), int(r1[1]), int(r1[2]))
        self.day_difference = (r2 - s2).days


        if self.day_difference >= 7:
            self.rental_type_value = 7
            self.qty = self.day_difference / 7
        else:
            self.rental_type_value = 1
            self.qty = self.rental_type_value



        # Get a list of return results of query
        find_rental_query_list = list(button_cursor)

        # Debug print statements
        for line in find_rental_query_list:
            print(str(line))

        # create scrollbar
        self.create_scrollbar(find_rental_query_list)

        # close database connection
        db_connection_find_rentals.close()

    def create_scrollbar(self, scrollbar_list_results):

        # Create scrollbar contents using the query results
        scrollbar = Scrollbar(self.rental_window)
        scrollbar.pack(side=LEFT, fill="y")
        scroll_list = Listbox(self.rental_window, yscrollcommand=scrollbar.set)
        scrollbars_contents.append(scroll_list)
        scrollbar_reference.append(scrollbar)
        scroll_list.bind('<<ListboxSelect>>', self.on_select_rental_item)

        # For each query insert it into the query list
        for row in scrollbar_list_results:
            scroll_list.insert(END, "Vehicle ID: " + str(row[0]) + ", Category: " + str(row[1]) + ", Type: " + str(
                row[2]) + ", Year: " + str(row[3]))

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

    def insert_new_rental(self):
        if int(self.payment_entry.get()) == self.total_amount_value:
            self.paid_amount = str(self.date)
        else:
            self.paid_amount= "NULL"

        submit_conn = sqlite3.connect('p2.db')
        submit_cur = submit_conn.cursor()
        insert_rental_query = f"INSERT INTO RENTAL VALUES( {int(self.cust_id_entry.get())}, '{self.vehicle_id_value}', '{self.start_date_value}', '{self.date}', {self.rental_type_value}, {self.qty}, '{self.return_date_value}', {int(self.total_amount_value)}, '{self.paid_amount}');"
        print(insert_rental_query)
        submit_cur.execute(insert_rental_query)
        submit_conn.commit()
        submit_conn.close()
        self.finalize_rental_window.destroy()






    def add_new_rental(self, value):

        value = value.replace("Category: ", "")
        value = value.replace("Type: ", "")
        value = value.replace("Year: ", "")
        value = value.replace("Vehicle ID: ", "")
        value_list = value.split(',')

        self.vehicle_id_value = value_list[0]
        self.category_value = value_list[1]
        self.type_value = value_list[2]
        self.year_value = value_list[3]

        self.finalize_rental_window = Toplevel()
        self.finalize_rental_window.title('Rental Confirmation')
        self.finalize_rental_window.geometry("300x300")

        find_rental_menu = LabelFrame(self.finalize_rental_window, text="Confirm Rental", padx=5, pady=10)
        find_rental_menu.grid(row=0, column=0)

        vehicle_id_entry = Entry(find_rental_menu, width=30)
        vehicle_id_entry.grid(row=0, column=1, padx=20)
        vehicle_id_entry.insert(END, self.vehicle_id_value)

        year_entry = Entry(find_rental_menu, width=30)
        year_entry.grid(row=1, column=1, padx=20)
        year_entry.insert(END, self.year_value)

        type_entry = Entry(find_rental_menu, width=30)
        type_entry.grid(row=2, column=1)
        type_entry.insert(END, self.type_value)

        category_entry = Entry(find_rental_menu, width=30)
        category_entry.grid(row=3, column=1)
        category_entry.insert(END, self.category_value)

        start_date_entry = Entry(find_rental_menu, width=30)
        start_date_entry.grid(row=4, column=1)
        start_date_entry.insert(END, self.start_date_value)

        return_date_entry = Entry(find_rental_menu, width=30)
        return_date_entry.grid(row=5, column=1)
        return_date_entry.insert(END, self.return_date_value)

        order_date = Entry(find_rental_menu, width=30)
        order_date.grid(row=6, column=1)
        order_date.insert(END, self.date)

        vehicle_label = Label(find_rental_menu, text='Vehicle ID')
        vehicle_label.grid(row=0, column=0)

        year_label = Label(find_rental_menu, text='Year')
        year_label.grid(row=1, column=0)

        type_label = Label(find_rental_menu, text='Type')
        type_label.grid(row=2, column=0)

        category_label = Label(find_rental_menu, text='Category')
        category_label.grid(row=3, column=0)

        start_date_label = Label(find_rental_menu, text='Start Date')
        start_date_label.grid(row=4, column=0)

        return_date_label = Label(find_rental_menu, text='Return Date')
        return_date_label.grid(row=5, column=0)

        order_date = Label(find_rental_menu, text='Order Date')
        order_date.grid(row=6, column=0)

        total_amount = Label(find_rental_menu, text= "Total Amount: " + str(self.find_total_amount()))
        total_amount.grid(row = 7, column=0)

        payment_label = Label(find_rental_menu, text="Customer Payment")
        payment_label.grid(row=8, column=0)

        self.payment_entry = Entry(find_rental_menu, width=30)
        self.payment_entry.grid(row=8, column=1)

        cust_id_label = Label(find_rental_menu, text='CustomerID')
        cust_id_label.grid(row=9, column=0)

        self.cust_id_entry = Entry(find_rental_menu, width=30)
        self.cust_id_entry.grid(row=9, column=1)

        insert_rental_button = Button(self.finalize_rental_window, text='Confirm', command=self.insert_new_rental)
        insert_rental_button.grid()


    def find_total_amount(self):
        # Perform Query to find available rentals that fit criteria
        db_connection_find_rentals = sqlite3.connect('p2.db')
        button_cursor = db_connection_find_rentals.cursor()
        find_weekly_daily = f"SELECT Weekly, Daily FROM RATE WHERE Type = {self.type_value} AND Category = {self.category_value};"
        button_cursor.execute(find_weekly_daily)
        db_connection_find_rentals.commit()

        find_weekly_daily_list = list(button_cursor)
        week_rate = 0
        day_rate = 0
        counter = 0

        print(find_weekly_daily_list[0])
        for rate in find_weekly_daily_list[0]:
            if counter == 0:
                week_rate = rate
            else:
                day_rate = rate
            counter = counter + 1

        if self.rental_type_value == 7:
            self.rate_value = int(week_rate)
        else:
            self.rate_value = int(day_rate)

        self.total_amount_value = self.qty * self.rate_value
        print(self.total_amount_value)

        return self.total_amount_value


    def on_select_rental_item(self, evt):
        w = evt.widget
        index = int(w.curselection()[0])
        value = w.get(index)
        print('You selected item %d: "%s"' % (index, value))
        self.add_new_rental(value)
