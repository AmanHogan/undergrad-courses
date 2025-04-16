from tkinter import *
import sqlite3
import os
from datetime import date


scrollbars_contents = []
scrollbar_reference = []
startAndEndDates = []

class FindVehicle:

    def __init__(self):

        # define rental window properties
        self.vehicle_window = Toplevel()
        self.vehicle_window.title('Find Vehicles')

        # define MENUS, FRAMES, LABELS, AND ENTRIES ##################################################################
        self.vehicle_menu = LabelFrame(self.vehicle_window, text="Vehicle Menu", padx=5, pady=10)
        self.vehicle_menu.pack()

        self.vehicle_id_frame = LabelFrame(self.vehicle_window, text="Vehicle ID", padx=5, pady=10)
        self.vehicle_id_frame.pack()
        self.vehicle_id_label = Label(self.vehicle_id_frame, text='Enter VIN')
        self.vehicle_id_label.pack(side=LEFT)
        self.vehicle_id_entry = Entry(self.vehicle_id_frame, width=30)
        self.vehicle_id_entry.pack(side=LEFT)

        self.vehicle_desc_frame = LabelFrame(self.vehicle_window, text="Vehicle Description", padx=5, pady=10)
        self.vehicle_desc_frame.pack()
        self.vehicle_desc_label = Label(self.vehicle_desc_frame, text='Enter Vehicle Description')
        self.vehicle_desc_label.pack(side=LEFT)
        self.vehicle_desc_entry = Entry(self.vehicle_desc_frame, width=30)
        self.vehicle_desc_entry.pack(side=LEFT)


        # Define Button to find rentals with selected information
        self.find_vehicles_button = Button(self.vehicle_window, text='Find', command=self.find_vehicles)
        self.find_vehicles_button.pack(fill=BOTH)

        self.vehicles_found_label = Label(self.vehicle_window, text='Vehicles Found ')
        self.vehicles_found_label.pack(side=LEFT)

    def find_vehicles(self):

        # define the menu containing list of available menus
        found_vehicle_frame = LabelFrame(self.vehicle_window, text="Found Vehicles", padx=5, pady=10)
        found_vehicle_frame.pack()

        # Refresh the scrollbar list each time it is called
        self.clear_scrollbar()

        # Perform Query to find available rentals that fit criteria
        db_connection_find_rentals = sqlite3.connect('p2.db')
        button_cursor = db_connection_find_rentals.cursor()


        self.desc_string = "%"
        find_cust_query = ""

        if self.vehicle_id_entry.get() and not self.vehicle_desc_entry.get():
            find_cust_query = f"SELECT VehicleID, Description, AVG(Daily) FROM VEHICLE, RATE WHERE VEHICLE.VehicleID = '{self.vehicle_id_entry.get()}'" \
                              f" AND VEHICLE.Category = RATE.Category AND VEHICLE.type = RATE.type GROUP BY VehicleID;"
            button_cursor.execute(find_cust_query)

        elif not self.vehicle_id_entry.get() and self.vehicle_desc_entry.get():
            self.desc_string = self.desc_string + str(self.vehicle_desc_entry.get()) + "%"
            find_cust_query = f"SELECT VehicleID, Description, AVG(Daily) FROM VEHICLE, RATE WHERE " \
                              f" VEHICLE.Description LIKE '{self.desc_string}' AND VEHICLE.Category = RATE.Category AND VEHICLE.type = RATE.type GROUP BY VehicleID;"
            button_cursor.execute(find_cust_query)

        elif not self.vehicle_id_entry.get() and not self.vehicle_desc_entry.get():
            find_cust_query = f"SELECT VehicleID, Description, AVG(Daily) FROM VEHICLE, RATE WHERE VEHICLE.Category = " \
                              f"RATE.Category AND VEHICLE.type = RATE.type GROUP BY VehicleID;"
            button_cursor.execute(find_cust_query)

        elif self.vehicle_id_entry.get() and self.vehicle_desc_entry.get():
            self.desc_string = self.desc_string + str(self.vehicle_desc_entry.get()) + "%"
            find_cust_query = f"SELECT VehicleID, Description, AVG(Daily) FROM VEHICLE, RATE WHERE " \
                              f" VEHICLE.Description LIKE '{self.desc_string}' AND VEHICLE.VehicleID = '{self.vehicle_id_entry.get()}' ANDVEHICLE.Category = RATE.Category AND VEHICLE.type = RATE.type GROUP BY VehicleID;"
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
        scrollbar = Scrollbar(self.vehicle_window)
        scrollbar.pack(side=LEFT, fill="y")
        scroll_list = Listbox(self.vehicle_window, yscrollcommand=scrollbar.set)
        scrollbars_contents.append(scroll_list)
        scrollbar_reference.append(scrollbar)
        scroll_list.bind('<<ListboxSelect>>', self.nothing())

        # For each query insert it into the query list
        for row in scrollbar_list_results:
            scroll_list.insert(END, "VIN: " + str(row[0]) + ", Description: " + str(row[1]) + ", AVG Daily Price: $" + str(row[2]))

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
