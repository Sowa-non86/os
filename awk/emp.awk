#!/bin/awk -f

BEGIN {
 FS = ":"
 print "Enter Emp No:"
 getline emp_no < "/dev/tty"
 found = 0
}
{
 if ($1 == emp_no) {
 emp_name = $2
 basic_salary = $3
 DA = 0.5 * basic_salary
 HRA = 0.3 * basic_salary
 gross_salary = basic_salary + DA + HRA
 
 printf "Emp No: %s\nEmp Name: %s\nBasic Salary: %s\nDA: %s\nHRA: %s\nGross Salary: %s\n",
 emp_no, emp_name, basic_salary, DA, HRA, gross_salary
 found = 1
 exit
 }
}
END {
 if (found == 0) {
 print "Employee not found"
 }
}