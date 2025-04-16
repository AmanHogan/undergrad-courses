import sqlite3
from tkinter import *
from tkinter import ttk
import os
import rental_manager as r
import find_customer as f
import find_vehicle as v
import return_rental as g


object_list = []

root = Tk()
root.title('Car Rental Application')
root.geometry("300x300")
project_two_conn = sqlite3.connect('p2.db')
cursor = project_two_conn.cursor()




def select_statements():
    pass

def on_click_insert_rental():
    r.RentalManager()
    object_list.append(r)




def new_customer():
    def insert_new_customer():
        BASE_DIR = os.path.dirname(os.path.abspath(__file__))
        db_dir = (BASE_DIR + '\\p2.db')
        submit_conn = sqlite3.connect(db_dir)
        submit_cur = submit_conn.cursor()
        sql = f"INSERT INTO CUSTOMER (Name, Phone) VALUES ('{name_entry.get()}', '{phone_entry.get()}');"
        submit_cur.execute(sql)
        submit_conn.commit()
        submit_conn.close()
        print(f"Customer {name_entry.get()} : {phone_entry.get()} was successfully added to {db_dir}")
        customer_window.destroy()

    customer_window = Toplevel()
    customer_window.title('New Customer')
    customer_window.geometry("400x300")

    cust_menu = LabelFrame(customer_window, text="Customer Menu", padx=5, pady=10)
    cust_menu.grid(row = 0, column = 0)

    name_entry = Entry(cust_menu, width=30)
    name_entry.grid(row=0, column=1, padx=20)

    phone_entry = Entry(cust_menu, width=30)
    phone_entry.grid(row=1, column=1)

    name_label = Label(cust_menu, text='First Initial. Last Name: ')
    name_label.grid(row=0, column=0)

    phone_label = Label(cust_menu, text='Phone Number: ')
    phone_label.grid(row=1, column=0)

    submit_btn = Button(cust_menu, text='Add Customer', command=insert_new_customer)
    submit_btn.grid()


def new_vehicle():

    def insert_new_vehicle():
        BASE_DIR = os.path.dirname(os.path.abspath(__file__))
        db_dir = (BASE_DIR + '\\p2.db')
        submit_conn = sqlite3.connect(db_dir)
        submit_cur = submit_conn.cursor()
        sql = f"INSERT INTO VEHICLE (VehicleID, Description, Year, Type, Category) VALUES ('{vehicle_id_entry.get()}', '{description_entry.get()}', '{year_entry.get()}', {type_entry.get()}, {category_entry.get()});"
        submit_cur.execute(sql)
        submit_conn.commit()
        submit_conn.close()
        #print(f"Customer {name_entry.get()} : {phone_entry.get()} was successfully added to {db_dir}")
        vehicle_window.destroy()

    vehicle_window = Toplevel()
    vehicle_window.title('New Vehicle')
    vehicle_window.geometry("300x300")

    vehicle_menu = LabelFrame(vehicle_window, text="Customer Menu", padx=5, pady=10)
    vehicle_menu.grid(row=0, column=0)

    vehicle_id_entry = Entry(vehicle_menu, width=30)
    vehicle_id_entry.grid(row=0, column=1, padx=20)

    description_entry = Entry(vehicle_menu, width=30)
    description_entry.grid(row=1, column=1)

    year_entry = Entry(vehicle_menu, width=30)
    year_entry.grid(row=2, column=1, padx=20)

    type_entry = Entry(vehicle_menu, width=30)
    type_entry.grid(row=3, column=1)

    category_entry = Entry(vehicle_menu, width=30)
    category_entry.grid(row=4, column=1)

    vehicle_label = Label(vehicle_menu, text='Vehicle ID')
    vehicle_label.grid(row=0, column=0)

    description_label = Label(vehicle_menu, text='Description')
    description_label.grid(row=1, column=0)

    year_label = Label(vehicle_menu, text='Year')
    year_label.grid(row=2, column=0)

    type_label = Label(vehicle_menu, text='Type')
    type_label.grid(row=3, column=0)

    category_label = Label(vehicle_menu, text='Category')
    category_label.grid(row=4, column=0)

    submit_btn = Button(vehicle_menu, text='Add Vehicle', command=insert_new_vehicle)
    submit_btn.grid()



def car_returns():
    g.ReturnRental()
    object_list.append(g)



def find_customer():
    f.FindCustomer()
    object_list.append(f)



def find_vehicle():
    v.FindVehicle()
    object_list.append(v)


def main_func():
    mod_menu = LabelFrame(root, text="Modify", padx=5, pady=10)
    mod_menu.grid()


    insert_cust = Button(mod_menu, text="A New Customer", command=new_customer)
    insert_vehicle = Button(mod_menu, text="Add New Vehicle", command=new_vehicle)
    insert_rental = Button(mod_menu, text="Add New Rental", command=on_click_insert_rental)
    return_car = Button(mod_menu, text="Returns", command=car_returns)
    insert_cust.grid()
    insert_vehicle.grid()
    insert_rental.grid()
    return_car.grid()

    list_menu = LabelFrame(root, text="Find/List", padx=5, pady=10)
    list_menu.grid()

    find_cust = Button(list_menu, text="Find Customer", command=find_customer)
    find_veh = Button(list_menu, text="Find Vehicle", command=find_vehicle)
    find_cust.grid()
    find_veh.grid()


main_func()

root.mainloop()
project_two_conn.close()
