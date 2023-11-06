def search_employee(employees, id):
    if id in employees:
        print(employees[id])
    else:
        print("ERROR: Employee not found.")

def add_employee():
    name = input("Enter the employee's name: ")
    id = input("Enter the employee's id: ")
    dept = input("Enter the employee's department: ")
    job = input("Enter the employee's job title: ")
    return Employee(name, id, dept, job)

def change_employee(employees, id):
    name = input("Update the employee's name: ")
    dept = input("Update the employee's department: ")
    job = input("Update the employee's job title: ")

    if id in employees:
        employees[id].set_name(name)
        employees[id].set_dept(dept)
        employees[id].set_job(job)

        print(f"Employee {id} updated.")
    else:
        print("ERROR: Employee not found.")


def delete_employee(employees, id):
    if id in employees:
        del employees[id]
        print(f"Employee {id} deleted.")
    else:
        print("ERROR: Employee not found.")

def main():
    employees = {}

    while True:
        option = input(
                        '''
                        1. Look up an employee in the dictionary\n
                        2. Add a new employee to the dictionary\n
                        3. Change an existing employee's name, department, and job title in the dictionary\n
                        4. Delete an employee from the dictionary\n
                        5. Quit the program\n'''
                    )
        
        if option == "1":
            id = input("Enter the employee's id: ")
            search_employee(employees, id)

        elif option == "2":
            new_employee = add_employee()
            employees[new_employee.id] = new_employee

        elif option == "3":
            id = input("Enter the employee's id: ")
            change_employee(employees, id)
        
        elif option == "4":
            id = input("Enter the employee's id: ")
            delete_employee(employees, id)

        elif option == "5":
            break
            exit(0)

        else:
            print("ERROR: Invalid option.")

main()